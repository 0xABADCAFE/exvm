
#define TEST_BUFFER_SIZE (1<<18)
uint16*     testBuffer = 0;
VMCore*     vm;
MilliClock  timeMS;

void timeNOP()
{
  printf("Benchmarking fetch/execute code\n\n");
  for (sint32 e=0; e<16; e++) {
    float64 elapsed = 0.0;
    uint16* p = testBuffer;
    sint32 i;
    if (e>0) {
      printf("Exception per %4ld ops : ", e);
      for (i=TEST_BUFFER_SIZE; i>0; i--) {
        if ((i%e)==0)
          *p++ = _iset(0);
        else
          *p++ = _nop|0x69;
      }
    } else {
      printf("Zero exceptional ops   : ");
      for (i=TEST_BUFFER_SIZE; i>0; i--) {
        *p++ = _nop|0xAB;
      }
    }
    testBuffer[TEST_BUFFER_SIZE] = _brk;

    for (i=0; i<4; i++) {
      vm->setPC(testBuffer);
      timeMS.set();
      vm->execute();
      elapsed += timeMS.elapsedFrac();
    }

    sint32 insts = i*TEST_BUFFER_SIZE;
    printf("%ld, %7.4f, %7.4f\n", insts, 0.001*elapsed, (0.001*(float64)insts)/elapsed );
  }
  printf("-------------------------------\n\n");
}

_VM_CODE(callTestReturn)
{
  _ret
};

_VM_CODE(callTest)
{
  _call(callTestReturn)
};

void timeCALL()
{
  printf("Benchmarking call/return pair\n\n");
  float64 elapsed = 0.0;
  uint16* p = testBuffer;
  sint32 i;
  for (i=0; i<TEST_BUFFER_SIZE; i++) {
    *p++ = _VM_ENTRY(callTest)[0];
    *p++ = _VM_ENTRY(callTest)[1];
    *p++ = _VM_ENTRY(callTest)[2];
  }

  testBuffer[(3*TEST_BUFFER_SIZE)] = _brk;

  for (i=0; i<4; i++) {
    vm->setPC(testBuffer);
    timeMS.set();
    vm->execute();
    elapsed += timeMS.elapsedFrac();
  }

  sint32 insts = i*TEST_BUFFER_SIZE;
  printf("%ld, %7.4f, %7.4f\n", insts, 0.001*elapsed, (0.001*(float64)insts)/elapsed );
  printf("-------------------------------\n\n");
}

void benchmark()
{
  testBuffer = new(nothrow) uint16[(3*TEST_BUFFER_SIZE)+2];
  if (testBuffer) {
    timeNOP();
    timeCALL();
    delete testBuffer;
  }
}