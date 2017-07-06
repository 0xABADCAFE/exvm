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

int main()
{
  static VMCore vm;
  puts("\nBeginning Virtual Program\n-----------------------\n");

  vm.setPC(_VM_ENTRY(virtualProgram));
  vm.execute();
  puts("\n-----------------------\n");
  vm.dump();

  return 0;
}
