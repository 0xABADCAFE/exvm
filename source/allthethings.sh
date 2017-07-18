#!/bin/sh

make -f Makefile.x64_ft_linux clean
make -f Makefile.x64_linux clean
make -f Makefile.x86_ft_linux clean
make -f Makefile.x86_linux clean
make -f Makefile_Linker.x64_linux clean
make -f Makefile_Linker.x86_linux clean
make -f Makefile_Symbol.x64_linux clean
make -f Makefile_Symbol.x86_linux clean

make -f Makefile.x64_ft_linux
make -f Makefile.x64_linux
make -f Makefile.x86_ft_linux
make -f Makefile.x86_linux
make -f Makefile_Linker.x64_linux
make -f Makefile_Linker.x86_linux
make -f Makefile_Symbol.x64_linux
make -f Makefile_Symbol.x86_linux
