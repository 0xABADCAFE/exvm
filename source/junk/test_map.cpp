#include <string>
#include <unordered_map>
#include <map>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/time.h>
#include <time.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Target options
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __LP64__
  typedef signed char sint8;
  typedef signed short int sint16;
  typedef signed int sint32;
  typedef signed long int sint64;
  typedef unsigned char uint8;
  typedef unsigned short int uint16;
  typedef unsigned int uint32;
  typedef unsigned long int uint64;
  typedef float float32;
  typedef double float64;
  #define FS16 "hd"
  #define FU16 "hu"
  #define FS32 "d"
  #define FU32 "u"
  #define FS64 "ld"
  #define FU64 "lu"
#else
  typedef signed char sint8;
  typedef signed short int sint16;
  typedef signed long int sint32;
  typedef signed long long int sint64;
  typedef unsigned char uint8;
  typedef unsigned short int uint16;
  typedef unsigned long int uint32;
  typedef unsigned long long int uint64;
  typedef float float32;
  typedef double float64;
  #define FS16 "hd"
  #define FU16 "hu"
  #define FS32 "ld"
  #define FU32 "lu"
  #define FS64 "lld"
  #define FU64 "llu"
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Clock
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Clock {
  private:
    static struct timezone  tz;
    timeval mark;

  public:
    void set() {
      gettimeofday(&mark, &tz);
    }
    float64 elapsed();

  public:
    Clock() {
      set();
    }
};

struct timezone Clock::tz = { 0, 0 };

float64 Clock::elapsed() {
  timeval current;
  gettimeofday(&current, &tz);
  if (current.tv_sec == mark.tv_sec) {
    return 1.0e-6 * (current.tv_usec - mark.tv_usec);
  }
  return (current.tv_sec - mark.tv_sec) + (1.0e-6 * (current.tv_usec - mark.tv_usec));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  MapEnumerator
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MapEnumerator {

  private:
    std::map<std::string, int> map;
    int nextID;
  public:
    int enumerate(const char* symbol);
    MapEnumerator() : nextID(0) {}
};

int MapEnumerator::enumerate(const char* symbol) {
  std::string key = symbol;
  int val = map[key];
  if (val == 0) {
    val = ++nextID;
    map[key] = val;
  }
  return val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  UnorderdMapEnumerator
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class UnorderedMapEnumerator {

  private:
    std::unordered_map<std::string, int> map;
    int nextID;
  public:
    int enumerate(const char* symbol);
    UnorderedMapEnumerator() : nextID(0) {}
};

int UnorderedMapEnumerator::enumerate(const char* symbol) {
  std::string key = symbol;
  int val = map[key];
  if (val == 0) {
    val = ++nextID;
    map[key] = val;
  }
  return val;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class TrieEnumerator {

  public:
    enum {
      SUCCESS             = 0,
      ILLEGAL_ARGUMENT    = -1,
      OUT_OF_MEMORY       = -2,
      ILLEGAL_SYMBOL_CHAR = -3, // A symbol contained an illegal character.
      TABLE_FULL          = -4,             // We have reached the maximum number of allowed symbol ID entries.
      UNKNOWN_SYMBOL      = -5,             // The requested symbol is not in the table.
      DUPLICATE_SYMBOL    = -6,             // An attempt to register the same symbol was made.
    };
    explicit TrieEnumerator(uint32 maxID);
    ~TrieEnumerator();

    // Add a new symbol to the table. Will return the uniquely assigned ID value for the symbol if successful, or
    // one of the enumerated error constants if not.
    int enumerate(const char* name);

    // Get the ID value of a previously registered symbol.
    int getID(const char* name) const;

    // Return the ID of the next symbol
    uint32 getNextID() const {
      return nextSymbolID;
    }

    // Get the maximum allowed Enumerated ID
    uint32 getMaxID() const {
      return maxSymbolID;
    }

    // Check if the enumerated set has been filled
    int isFull() const {
      return nextSymbolID == maxSymbolID;
    }

  private:
    enum {
      PNODE_TO_SNODE = 8,
      SNODE_TO_PNODE = 8,
      NODE_BLOCKSIZE = 1024
    };
    // Trie implementation:
    // Rather than  defining a trie with a wide fan out (64 node pointers per node), instead we use two nodes per mapped
    // cahr, each of which has 8 children. This gives us a range of 8x8=64, sufficient to cover the entire set of valid
    // characters but with a lot less memory wasted on unused pointers.

    // Primary node type
    struct PNode;

    // Secondary node type
    struct SNode;

    // Block of allocated nodes, linked together.
    struct Block;

    // We map the allowed symbol name characters 0-9A-Za-z@_ to the range 0-63 . This function maps a single input
    // character. If the input character is out of range, reuturns ERR_ILLEGAL_SYMBOL_CHAR
    int     mapChar(int c) const;

    // Allocate a new PNode. Allocations will be from the remainder of the current Block or from a new Block if the
    // existing one is full.
    PNode*  allocPNode();

    // Allocate a new SNode. Allocations will be from the remainder of the current Block of from a new Block if the
    // existing one is full.
    SNode*  allocSNode();

    // Check if a Block is available.
    int     checkBlock();

    // Data ////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Location of the current Block.
    Block* nodeBlock;

    // Root of the trie
    PNode* rootNode;

    // Table size, set on construction
    uint32 maxSymbolID;

    // The next ID we will allocate
    uint32 nextSymbolID;

};



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Primary node structure
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct TrieEnumerator::PNode {
  TrieEnumerator::SNode* children[PNODE_TO_SNODE];
  int symbolID;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Secondary node structure
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct TrieEnumerator::SNode {
  TrieEnumerator::PNode* children[SNODE_TO_PNODE];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Node block structure
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct TrieEnumerator::Block {
  union {
    PNode primary;
    SNode secondary;
  } nodes[NODE_BLOCKSIZE];
  Block* prevBlock;
  int    nextFree;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Constructor
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TrieEnumerator::TrieEnumerator(uint32 maxID) :
  nodeBlock(0),
  rootNode(0),
  maxSymbolID(maxID),
  nextSymbolID(0)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Destructor
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TrieEnumerator::~TrieEnumerator() {
  Block*   pBlock = nodeBlock;

  /* Free the block list */
  while (pBlock) {
    void* ptr = (void*) pBlock;
    pBlock    = pBlock->prevBlock;
    std::free(ptr);
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Convert an ASCII character code from the set 0-9A-Za-z@_ to a mapped code 0-63
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int TrieEnumerator::mapChar(int c) const {
  if (c >= '0' && c <= '9') {
    return c - '0';
  }
  if (c >= 'A' && c <= 'Z') {
    return 10 + c - 'A';
  }
  if (c >= 'a' && c <= 'z') {
    return 38 + c - 'a';
  }
  if (c == '@') {
    return 62;
  }
  if (c == '_') {
    return 63;
  }

  return ILLEGAL_SYMBOL_CHAR;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Confirm we have a node block and attempt to allocate one if not, or if full
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int TrieEnumerator::checkBlock() {
  // Check if we need to allocate a new block of nodes
  if (!nodeBlock || nodeBlock->nextFree == NODE_BLOCKSIZE) {
    Block* newBlock = (Block*)std::calloc(1, sizeof(Block));
    if (!newBlock) {
      return 0;
    }

    // Make the newly allocated block the active one
    newBlock->prevBlock    = nodeBlock;
    nodeBlock = newBlock;
  }
  return 1;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Allocate the next available PNode
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TrieEnumerator::PNode* TrieEnumerator::allocPNode() {
  if (!checkBlock()) {
    return 0;
  }

  // Get the next free PNode and set it's symbol ID to -1 so that we can properly detect when terminating on this
  // node that it does not mark the end of an existing symbol
  PNode* pNode = &nodeBlock->nodes[nodeBlock->nextFree++].primary;
  pNode->symbolID = -1;
  return pNode;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Allocate the next available SNode
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TrieEnumerator::SNode* TrieEnumerator::allocSNode() {
  if (!checkBlock()) {
    return 0;
  }

  // Get the next free SNode from the block
  return &nodeBlock->nodes[nodeBlock->nextFree++].secondary;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Attempt to find the ID associated with a symbol
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int TrieEnumerator::getID(const char* name) const {

  // Protect against null
  if (!name) {
    return ILLEGAL_ARGUMENT;
  }

  // If there is no rootNode, then no symbols have been added. Ipso facto, cannot be known!
  if (!rootNode) {
    return UNKNOWN_SYMBOL;
  }

  PNode* primaryNode;
  SNode* secondaryNode;
  int charCode, indexPrimary, indexSecondary;

  // Walk down the trie, one PNode and one SNode per mapped character
  primaryNode  = rootNode;
  while ( (charCode = *name++) ) {
    int code = mapChar(charCode);
    if (code < 0) {
      return code;
    }

    // Convert mapped code to index pair for our primary and secondary nodes.
    indexPrimary   = code & 7;
    indexSecondary = code >> 3;
    if (!primaryNode->children[indexPrimary]) {
      return UNKNOWN_SYMBOL;
    }
    secondaryNode = primaryNode->children[indexPrimary];
    if (!secondaryNode->children[indexSecondary]) {
      return UNKNOWN_SYMBOL;
    }
    primaryNode = secondaryNode->children[indexSecondary];
  }

  return primaryNode->symbolID;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Attempt to add a new symbol and obtain the associated ID.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int TrieEnumerator::enumerate(const char* name) {

  // Protect against null
  if (!name) {
    return ILLEGAL_ARGUMENT;
  }

  // Check we haven't reached the table size limit
  if (isFull()) {
    return TABLE_FULL;
  }

  // If we haven't allocated the root of our trie yet, we better do it.
  if (!rootNode && !(rootNode = allocPNode())) {
    return OUT_OF_MEMORY;
  }

  const char* pChar = name;
  PNode* primaryNode;
  SNode* secondaryNode;
  int charCode, indexPrimary, indexSecondary;

  // Walk down the trie, one PNode and one SNode per mapped character
  primaryNode  = rootNode;
  while ( (charCode = *pChar++) ) {

    int code = mapChar(charCode);

    if (code < 0) {
      return code;
    }

    // Convert mapped code to index pair for our primary and secondary nodes
    indexPrimary   = code & 7;
    indexSecondary = code >> 3;

    // Ensure there is a child SNode instance for the PNode
    if (
      !primaryNode->children[indexPrimary] &&
      !(primaryNode->children[indexPrimary] = allocSNode())
    ) {
      return OUT_OF_MEMORY;
    }
    secondaryNode = primaryNode->children[indexPrimary];

    // Ensure there is a child PNode instance for the SNode
    if (
      !secondaryNode->children[indexSecondary] &&
      !(secondaryNode->children[indexSecondary] = allocPNode())
    ) {
      return OUT_OF_MEMORY;
    }
    primaryNode = secondaryNode->children[indexSecondary];
  }

  // If this is the first time we landed on this particular PNode, it's a new symbol
  if (primaryNode->symbolID < 0) {
    return primaryNode->symbolID = (int)nextSymbolID++;
  } else {
    return DUPLICATE_SYMBOL;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const int MAX_INSERTS = 5000000;
const int MAX_LOOKUPS = 50000000;

const char* createKey(char* buffer, int i) {
  std::sprintf(buffer, "Key_%d", i);
  return buffer;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
  MapEnumerator          enumerator0;
  UnorderedMapEnumerator enumerator1;
  TrieEnumerator         enumerator2(MAX_INSERTS);
  Clock timer;

  int sum1 = 0, sum2 = 0, sum3 = 0, sum4 = 0;
  char buffer[32];

  std::printf("Calibrating for %d iterations...\n", MAX_INSERTS);
  timer.set();
  for (int i = 0; i < MAX_INSERTS; i++) {
    sum1 += i;
    createKey(buffer, i);
  }
  float64 calibrationTime = timer.elapsed();

  std::printf("Testing std::map<std::string, int> based implementation...\n");
  timer.set();
  for (int i = 0; i < MAX_INSERTS; i++) {
    sum2 += enumerator0.enumerate(createKey(buffer, i));
  }
  float64 mapTime = timer.elapsed() - calibrationTime;

  std::printf("Testing std::unordered_map<std::string, int> based implementation...\n");
  timer.set();
  for (int i = 0; i < MAX_INSERTS; i++) {
    sum3 += enumerator1.enumerate(createKey(buffer, i));
  }
  float64 unorderedMapTime = timer.elapsed() - calibrationTime;

  std::printf("Testing custom trie based implementation...\n");
  timer.set();
  for (int i = 0; i < MAX_INSERTS; i++) {
    sum4 += enumerator2.enumerate(createKey(buffer, i));
  }
  float64 trieTime = timer.elapsed() - calibrationTime;

  std::printf(
    "Calibration Checksum   %d, time %f s\n"
    "Simple map             %d, time %f s\n"
    "Unordered map          %d, time %f s\n"
    "Custom Trie            %d, time %f s\n",
    sum1,
    calibrationTime,
    sum2,
    mapTime,
    sum3,
    unorderedMapTime,
    sum4,
    trieTime
  );
  return 0;
}
