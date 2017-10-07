#!/bin/sh

make -f Makefile.x64_linux clean
make -f Makefile.x86_linux clean

make -j4 -f Makefile.x64_linux
make -j4 -f Makefile.x86_linux
make -j4 -f Makefile_Vector.x64_linux
make -j4 -f Makefile_Advanced.x64_linux
make -j4 -f Makefile_Tests.x64_linux
