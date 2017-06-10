////////////////////////////////////////////////////////////////////////////////
//
//  test app
//
////////////////////////////////////////////////////////////////////////////////


#include <new>
#include <cstdio>
#include <cstdlib>
#include "vmcore.hpp"
#include "vminline.hpp"
#include "vm_codemacros.hpp"

using namespace std;

////////////////////////////////////////////////////////////////////////////////

_VM_EXTERN(virtualProgram);

int main(int argc, char *argv[])
{
  static VMCore vm;
  puts("\nBeginning Virtual Program\n-----------------------\n");

  vm.setPC(_VM_ENTRY(virtualProgram));
  MilliClock t;
  vm.execute();
  printf("Time taken :%0.3fms\n", t.elapsedFrac());
  puts("\n-----------------------\n");
  vm.dump();

  return 0;
}
