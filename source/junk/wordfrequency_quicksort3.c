
/*
  Karlos moobunny challenge 21 Dec 2012, Stab #3

  Pure vanilla C, No regex, stringbuffer libraries, containers etc.

  Improvements over original version
   * Replaced ultra-sucky getc() + setvbuf() implementation with genuine block reads
   * Discarded list based sorting for trie nodes all together. Instead, the addresses of terminating nodes are stored
     in a vector. We occasionally have to realloc() this, but it's a trade-off,
   * No longer separate block allocators for Primary and Secondary nodes. As the list implementation was stripped from
     PrimaryNode, the two structures are very similar sizes and are now allocated together. This also improves cache
     locality for successive Primary->Secondary->Primary allocations on insertion.
   * Replaced qsort() with an inlined adaptation that supports sorting a vector of PrimaryNode pointers directly. This
     saves a few clock cycles in the sorting compared to the generic library version.
   * Roughly 12-18x faster than V1 on my machine.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NODE_BLOCK_SIZE   8192
#define READ_BUFFER_SIZE  131072
#define PTR_BUFFER_SIZE   16384

/*#define TEST_MODE*/

/*
  Forward references
*/
struct PrimaryNode_t;
struct PrimaryNodeBlock_t;
struct SecondaryNode_t;
struct SecondaryNodeBlock_t;
struct NodeBlock_t;

/*
  Primary Trie node
*/
struct PrimaryNode_t {
  struct SecondaryNode_t* children[4]; /* pointers to fanout SecondaryNode nodes */
  struct PrimaryNode_t*   parentNode;  /* parent (for path retracing) */
  int count;                           /* number of strings that terminated on this node */
  int charCode;                        /* character value associated with this node */
};

/*
  Secondary trie node
*/
struct SecondaryNode_t {
  struct PrimaryNode_t* children[7];
};

/*
  Unified node block block. For a 32-bit system, Primary and secondary nodes are likely to be the same size.
  For a 64-bit system with 32-bit integers, secondary block will be 8 bytes longer. To increase cache locality
  we forego these 8 bytes to get successive pair allocations together in the same block wherever possible.
*/
struct NodeBlock_t {
  union {
    struct PrimaryNode_t   primary;
    struct SecondaryNode_t secondary;
  }                        nodes[NODE_BLOCK_SIZE];
  struct NodeBlock_t*      prevBlock;
  int                      nextFree;
};


/*
  Word Counter
*/
struct WordCounter_t {
  struct NodeBlock_t*      nodeBlock;       /* Points to the most recently allocated NodeBlock*/
  struct PrimaryNode_t*    rootNode;        /* Points to the root of the trie */
  struct PrimaryNode_t**   terminatorNodes; /* Vector of pointers to word termination nodes */
  size_t                   totalChars;      /* Total number of characters inserted into trie */
  size_t                   totalWords;      /* Total number of words in trie */
  size_t                   terminatorSize;
  int                      maxWordLength;
};

/*
  typeef shortcuts
*/
typedef struct PrimaryNode_t     PrimaryNode;
typedef struct SecondaryNode_t   SecondaryNode;
typedef struct NodeBlock_t       NodeBlock;
typedef struct WordCounter_t     WordCounter;

/**********************************************************************************************************************/

WordCounter* createWordCounter(void);
void         destroyWordCounter(WordCounter* wordCounter);
void         printStats(WordCounter* wordCounter);
size_t       readTextFileIntoCounter(WordCounter* wordCounter, const char* fileName);
void         sortWordList(WordCounter* wordCounter);
void         printWordList(WordCounter* wordCounter);

#ifdef TEST_MODE
int testInsertWord(WordCounter* wordCounter, const char* text);
#endif

/**********************************************************************************************************************/

/*
  Main program
*/

int main(int numArgs, char** argStrings) {
  WordCounter* wordCounter;
  const char*  fileName;
  if (numArgs > 1) {
    fileName = argStrings[1];
    if ((wordCounter = createWordCounter())) {
#ifdef TEST_MODE
      testInsertWord(wordCounter, "and");
      testInsertWord(wordCounter, "and");
      testInsertWord(wordCounter, "anchor");
      testInsertWord(wordCounter, "moo");
      testInsertWord(wordCounter, "MooBunny");
      testInsertWord(wordCounter, "AMOS-Sucks");
      printStats(wordCounter);
#else
      if (readTextFileIntoCounter(wordCounter, fileName)) {
        printStats(wordCounter);
        sortWordList(wordCounter);
        printWordList(wordCounter);
      }
      else {
        printf("No text could be read from file '%s'\n", fileName);
      }
#endif
      destroyWordCounter(wordCounter);
    }
  } else {
    printf("Usage %s filename.txt\n", argStrings[0]);
  }
  return 0;
}

/**********************************************************************************************************************/

static PrimaryNode*   allocPrimaryNode(WordCounter* wordCounter, PrimaryNode* parentNode, int charCode);
static SecondaryNode* allocSecondaryNode(WordCounter* wordCounter);

/**********************************************************************************************************************/

/*
  Create WordCounter context
*/
WordCounter* createWordCounter(void) {
  /* Allocate raw storage and if successful, initialise it */
  WordCounter* wordCounter = (WordCounter*)calloc(1, sizeof(WordCounter));
  if (wordCounter) {
    wordCounter->rootNode = allocPrimaryNode(wordCounter, NULL, 0);
    if ( (wordCounter->terminatorNodes = malloc(PTR_BUFFER_SIZE*sizeof(PrimaryNode*))) ) {
      wordCounter->terminatorSize = PTR_BUFFER_SIZE;
    }
  }
  return wordCounter;
}

/**********************************************************************************************************************/

/*
  Destroy WordCounter context, freeing up all allocated resources
*/
void destroyWordCounter(WordCounter* wordCounter) {
  if (wordCounter) {
    NodeBlock*   pBlock = wordCounter->nodeBlock;

    /* Free the block list */
    while (pBlock) {
      void* ptr = (void*) pBlock;
      pBlock    = pBlock->prevBlock;
      free(ptr);
    }

    if (wordCounter->terminatorNodes) {
      free(wordCounter->terminatorNodes);
    }

    /* Finally, free the counter itself */
    free(wordCounter);
  }
}

/**********************************************************************************************************************/

/*
  Allocate a new PrimaryNode. This performs several tasks. It tries to allocate the next free PrimaryNode from the
  currently active NodeBlock, If the block is not yet allocated or is full, it tries to allocate a new one. If
  successful the newly allocated NodeBlock is made active and the first node taken. The NodeBlocks are chained
  such that they can all be freed later.
  Once a PrimaryNode is obtained, it is filled in with the parentNode and charCode values supplied.
*/
static PrimaryNode* allocPrimaryNode(WordCounter* wordCounter, PrimaryNode* parentNode, int charCode) {

  PrimaryNode* primaryNode = NULL;

  /* Check if we need to allocate a new block of nodes */
  if (!wordCounter->nodeBlock || wordCounter->nodeBlock->nextFree == NODE_BLOCK_SIZE) {
    NodeBlock* newBlock = (NodeBlock*)calloc(1, sizeof(NodeBlock));
    if (!newBlock) {
      fprintf(stderr, "Unable to allocate NodeBlock of %lu bytes\n", (unsigned long)sizeof(NodeBlock));
      return NULL;
    }

    /* Make the newly allocated block the active one */
    newBlock->prevBlock    = wordCounter->nodeBlock;
    wordCounter->nodeBlock = newBlock;
  }

  /* get the next Primary node from the block and populate it */
  primaryNode = &wordCounter->nodeBlock->nodes[wordCounter->nodeBlock->nextFree++].primary;
  primaryNode->parentNode = parentNode;
  primaryNode->charCode   = charCode;

  return primaryNode;
}


/**********************************************************************************************************************/

/*
  Allocate a new SecondaryNode. This performs several tasks. It tries to allocate the next free SecondaryNode from the
  currently active NodeBlock, If the block is not yet allocated or is full, it tries to allocate a new one. If
  successful the newly allocated NodeBlock is made active and the first node taken. The NodeBlocks are chained
  such that they can all be freed later.
*/
static SecondaryNode* allocSecondaryNode(WordCounter* wordCounter) {

  SecondaryNode* secondaryNode = NULL;

  /* Check if we need to allocate a new block of nodes */
  if (!wordCounter->nodeBlock || wordCounter->nodeBlock->nextFree == NODE_BLOCK_SIZE) {
    NodeBlock* newBlock = (NodeBlock*)calloc(1, sizeof(NodeBlock));
    if (!newBlock) {
      fprintf(stderr, "Unable to allocate NodeBlock of %lu bytes\n", (unsigned long)sizeof(NodeBlock));
      return NULL;
    }

    /* Make the newly allocated block the active one */
    newBlock->prevBlock    = wordCounter->nodeBlock;
    wordCounter->nodeBlock = newBlock;
  }

  /* get the next Primary node from the block and populate it */
  secondaryNode = &wordCounter->nodeBlock->nodes[wordCounter->nodeBlock->nextFree++].secondary;

  return secondaryNode;
}

/**********************************************************************************************************************/

/*
  At the end of string insertion, increment the counter on the PrimaryNode and move it to the front of the list.
*/
static int markPrimaryNodeAsTerminator(WordCounter* wordCounter, PrimaryNode* primaryNode) {
  /* Take the final PrimaryNode, increment the counter and move to the head of the list */

  /*
    If this is the first time the node counter is incremented, bump the total word count to record that we added a
    new unique word.
  */
  if (!primaryNode->count++) {
    if (wordCounter->totalWords == wordCounter->terminatorSize) {
      wordCounter->terminatorSize <<= 1;
      if (!(wordCounter->terminatorNodes = (PrimaryNode**)realloc(wordCounter->terminatorNodes, wordCounter->terminatorSize*sizeof(PrimaryNode*)))) {
        return 0; /* reallocation failure */
      }
    }
    wordCounter->terminatorNodes[wordCounter->totalWords++] = primaryNode;
  }
  return 1;
}

/**********************************************************************************************************************/

#ifdef TEST_MODE

/*
  Basic test of trie functionality,
*/

int testInsertWord(WordCounter* wordCounter, const char* text) {
  PrimaryNode* primaryNode;
  SecondaryNode* secondaryNode;
  int charCode, index, indexPrimary, indexSecondary, wordLength;

  wordLength = 0;
  primaryNode = wordCounter->rootNode;
  while ( (charCode = *text++) ) {
    /* ignore quotes and hyphens */
    if (charCode=='\'' || charCode=='-') {
      continue;
    }

    /* Quick way to ensure lower case (breaks all non-letter characters, but we don't care about them anyway */
    charCode |= 32; /* ASCII table - all a-z codes are corresponding A-Z code | 32 */

    if (charCode < 'a' || charCode > 'z') {
      return 0;
    }
    /* convert character code to index */
    index          = charCode - 'a';
    indexPrimary   = index & 3;
    indexSecondary = index >> 2;

    if (!primaryNode->children[indexPrimary]) {
      if (!(primaryNode->children[indexPrimary] = allocSecondaryNode(wordCounter))) {
        return 0;
      }
    }

    secondaryNode = primaryNode->children[indexPrimary];

    if (!secondaryNode->children[indexSecondary]) {
      if (!(secondaryNode->children[indexSecondary] = allocPrimaryNode(wordCounter, primaryNode, charCode))) {
        return 0;
      }
    }
    primaryNode = secondaryNode->children[indexSecondary];
    wordLength++;
  }

  markPrimaryNodeAsTerminator(wordCounter, primaryNode);

  if (wordLength > wordCounter->maxWordLength) {
    wordCounter->maxWordLength = wordLength;
  }

  wordCounter->totalChars += wordLength;

  return 1;
}
#endif

/**********************************************************************************************************************/

/*
  Inserts a single character into the trie, returning the next PrimaryNode.
*/

static PrimaryNode* insertCharacter(WordCounter* wordCounter, PrimaryNode* primaryNode, int charCode) {
  SecondaryNode* secondaryNode;
  int index, indexPrimary, indexSecondary;

  /* convert character code to index */
  index          = charCode - 'a';
  indexPrimary   = index & 3;
  indexSecondary = index >> 2;

  if (!primaryNode->children[indexPrimary]) {
    if (!(primaryNode->children[indexPrimary] = allocSecondaryNode(wordCounter))) {
      return 0;
    }
  }

  secondaryNode = primaryNode->children[indexPrimary];

  if (!secondaryNode->children[indexSecondary]) {
    if (!(secondaryNode->children[indexSecondary] = allocPrimaryNode(wordCounter, primaryNode, charCode))) {
      return 0;
    }
  }
  return secondaryNode->children[indexSecondary];
}

/**********************************************************************************************************************/

/*
  This function reads a text file character by character into the trie. As lame as this strategy is, it means we don't
  have to wory about maximum line length. In order to suck less, we increase the file IO buffer.
*/
size_t readTextFileIntoCounter(WordCounter* wordCounter, const char* fileName) {
  PrimaryNode* primaryNode;
  FILE*        fileHandle;
  char*        readBuffer;
  int          wordLength;
  int          readChar;
  int          charsLeft;
  int          readPos;

  if ( (readBuffer = (char*)malloc(READ_BUFFER_SIZE)) ) {
    if ( fileName && (fileHandle = fopen(fileName, "r"))) {

      primaryNode = wordCounter->rootNode;
      wordLength  = 0;
      readPos     = 0;
      charsLeft   = 1;
      readChar    = 0;

      /*
        Here, we implement a simple state machine. The two possible states are reading characters into the trie or
        skipping read characters that are outside the target range. When we flip from the first state to the second, we
        mark the currently inserted word as complete using the markPrimaryNodeAsTerminator() call, reset the node pointer
        back to the root node and then continue to skip unwanted characters until we find another good one.
      */

      while (readChar != EOF) {
        if (!(--charsLeft) && (!(charsLeft = fread(readBuffer, 1, READ_BUFFER_SIZE, fileHandle)))) {
          break;
        }
        readChar = charsLeft ? readBuffer[readPos++] : EOF;
        readPos &= (READ_BUFFER_SIZE-1);

        /* ignore quotes and hyphens */
        if (readChar=='\'' || readChar=='-') {
          continue;
        }

        /* Quick way to ensure lower case (breaks all non-letter characters, but we don't care about them anyway */
        readChar |= 32; /* ASCII table - all a-z codes are corresponding A-Z code | 32 */

        /*
          As long as the character is in our target range, keep adding it as the next letter in the current word,
          otherwise, terminate
        */
        if (readChar >= 'a' && readChar <= 'z') {
          if (!(primaryNode = insertCharacter(wordCounter, primaryNode, readChar))) {
            /* Something went very wrong, we can't continue */
            fprintf(stderr, "Failed to insert character \'%c\' into trie, aborting\n", readChar);
            break;
          }
          wordLength++;
        }
        else if (primaryNode != wordCounter->rootNode) {
          /*
            primaryNode will be the last PrimaryNode inserted for the current word. We need to mark it as a terminating
            node. After that, we can just re assign it to the rootNode, ready for the next word that comes along.
          */
          markPrimaryNodeAsTerminator(wordCounter, primaryNode);
          primaryNode = wordCounter->rootNode;

          /*
            Update a few stats
          */
          wordCounter->totalChars += wordLength;
          if (wordLength > wordCounter->maxWordLength) {
            wordCounter->maxWordLength = wordLength;
          }
          wordLength  = 0;
        }
      }
      fclose(fileHandle);
    }
    free(readBuffer);
  }
  return wordCounter->totalChars;
}
/**********************************************************************************************************************/

void printStats(WordCounter* wordCounter) {
  printf(
    "Total chars  : %lu\n"
    "Unique words : %lu\n"
    "Longest text : %d\n",
    (unsigned long)wordCounter->totalChars,
    (unsigned long)wordCounter->totalWords,
    wordCounter->maxWordLength
  );
}

/**********************************************************************************************************************/

/*
  Output the strings stored in the trie
*/
void printWordList(WordCounter* wordCounter) {
  size_t        numWords = wordCounter->totalWords;
  char*         buffer;
  char*         wordPtr;
  PrimaryNode** terminatorList = wordCounter->terminatorNodes;

  if (!(buffer = (char*)malloc(wordCounter->maxWordLength+1))) {
    fprintf(stderr, "Couldn't allocate %d bytes for output buffer\n", wordCounter->maxWordLength+1);
    return;
  }
  buffer[wordCounter->maxWordLength] = 0;

  while (numWords--) {
    PrimaryNode*  primaryNode = *terminatorList++;
    int           count       = primaryNode->count;
    wordPtr     = buffer + wordCounter->maxWordLength;
    while (primaryNode != wordCounter->rootNode) {
      *(--wordPtr) = primaryNode->charCode;
      primaryNode = primaryNode->parentNode;
    }
    printf("%4d %s\n", count, wordPtr);
  }

  free(buffer);
}

/**********************************************************************************************************************/

static __inline int compareNodes(const PrimaryNode* a, const PrimaryNode* b) {
  return b->count - a->count;
}

void sortPrimaryNodePtrArray(PrimaryNode** nodePointers, size_t numNodes);

void sortWordList(WordCounter* wordCounter) {
  sortPrimaryNodePtrArray(wordCounter->terminatorNodes, wordCounter->totalWords);
}

/**********************************************************************************************************************/

/*
  Sort implementation. Based on libc6 qsort(), adapted to directly sort a vector of PrimaryNode pointers based on the
  values of the counts in the nodes themselves
*/

#define min(a, b) (a) < (b) ? a : b

#define swapPair(ptrI, ptrJ) { \
  PrimaryNode* tmp = *(ptrI);     \
  *(ptrI)   = *(ptrJ);     \
  *(ptrJ)   = tmp;         \
}

static __inline void swapBlock(PrimaryNode** ptrA, PrimaryNode** ptrB, size_t num) {
  while (num--) {
    PrimaryNode* tmp = *ptrA;
    *ptrA++ = *ptrB;
    *ptrB++ = tmp;
  }
}

static __inline PrimaryNode** partition(PrimaryNode** a, PrimaryNode** b, PrimaryNode** c) {
  return compareNodes(*a, *b) < 0 ? (
    compareNodes(*b, *c) < 0 ?
      b
      : (
        compareNodes(*a, *c) < 0 ?
        c : a
      )
  )
  : (
    compareNodes(*b, *c) > 0 ?
      b : (
        compareNodes(*a, *c) < 0 ?
        a : c
      )
  );
}


void sortPrimaryNodePtrArray(PrimaryNode** nodePointers, size_t numNodes) {
  int d, swapCount;
  int r;

  PrimaryNode** ptrA;
  PrimaryNode** ptrB;
  PrimaryNode** ptrC;
  PrimaryNode** ptrD;
  PrimaryNode** ptrL;
  PrimaryNode** ptrM;
  PrimaryNode** ptrN;

/* Nasty goto jump target to avoid recursion */
loop:
  swapCount = 0;


  if (numNodes < 7) {
    for (ptrM = nodePointers+1; ptrM < nodePointers+numNodes; ptrM++) {
      for (ptrL = ptrM; ptrL > nodePointers && compareNodes(*(ptrL - 1), *ptrL) > 0; ptrL--) {
        swapPair(ptrL, ptrL - 1);
      }
    }
    return;
  }

  ptrM = nodePointers + (numNodes >> 1);

  if (numNodes > 7) {
    ptrL = nodePointers;
    ptrN = nodePointers + numNodes - 1;
    if (numNodes > 40) {
      d = (numNodes >> 3);
      ptrL = partition(ptrL,          ptrL + d, ptrL + (d<<1));
      ptrM = partition(ptrM - d,      ptrM,     ptrM + d);
      ptrN = partition(ptrM - (d<<1), ptrN - d, ptrN);
    }
    ptrM = partition(ptrL, ptrM, ptrN);
  }

  swapPair(nodePointers, ptrM);

  ptrA = ptrB = nodePointers + 1;
  ptrC = ptrD = nodePointers + numNodes - 1;

  for (;;) {
    while (ptrB <= ptrC && (r = compareNodes(*ptrB, *nodePointers)) <= 0) {

      if (r == 0) {
        swapCount = 1;
        swapPair(ptrA, ptrB);
        ptrA++;
      }
      ptrB++;
    }

    while (ptrB <= ptrC && (r = compareNodes(*ptrC, *nodePointers)) >= 0) {
      if (r == 0) {
        swapCount = 1;
        swapPair(ptrC, ptrD);
        ptrD--;
      }
      ptrC--;
    }

    if (ptrB > ptrC) {
      break;
    }

    swapPair(ptrB, ptrC);
    swapCount = 1;
    ptrB++;
    ptrC--;
  }

  if (swapCount == 0) {  /* Switch to insertion sort */
    for (ptrM = nodePointers + 1; ptrM < nodePointers + numNodes; ptrM++) {
      for (ptrL = ptrM; ptrL > nodePointers && compareNodes(*(ptrL - 1), *ptrL) > 0; ptrL--) {
        swapPair(ptrL, ptrL - 1);
      }
    }
    return;
  }

  ptrN = nodePointers + numNodes;
  r    = min(ptrA - nodePointers, ptrB - ptrA);
  swapBlock(nodePointers, ptrB - r, r);
  r    = min((size_t)(ptrD - ptrC), ptrN - ptrD - 1);
  swapBlock(ptrB, ptrN - r, r);

  if ((size_t)(r = ptrB - ptrA) > 1) {
    sortPrimaryNodePtrArray(nodePointers, r);
  }

  if ((size_t)(r = ptrD - ptrC) > 1) {
    /* Iterate rather than recurse to save stack space */
    nodePointers =  ptrN - r;
    numNodes = r;
    goto loop;
  }
}
