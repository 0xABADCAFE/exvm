#!/bin/sh

make -f Makefile.x64_ft_linux clean
make -f Makefile.x64_linux clean
make -f Makefile.x86_ft_linux clean
make -f Makefile.x86_linux clean
make -f Makefile_Vector.x64_linux clean
make -f Makefile_Vector.x64_ft_linux clean

make -f Makefile.x64_ft_linux
make -f Makefile.x64_linux
make -f Makefile.x86_ft_linux
make -f Makefile.x86_linux
make -f Makefile_Vector.x64_linux
make -f Makefile_Vector.x64_ft_linux
