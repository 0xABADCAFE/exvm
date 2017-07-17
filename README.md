# exvm

## Experimental Virtual Machine

A simple register based interpretive virtual machine, written as an old experiment.

There are 16 64-bit general purpose registers that can contain any 8, 16, 32 or 64 bit integer (signed or unsigned), a 32 or 64 bit IEEE754 float or an address value.

The machine implements a load/store architecture in which almost all operations are register to register. The contents of the register are implied by the instruction. Operations on sizes smaller than 64-bit always affect the least significant portion of the register. Operations directly on memory operands are not supported.

The load/store operations support register indirect, postincrement, predecrement, displacement and scaled index modes.

In addition to the general purpose register, there are separate stacks for user data, register save/restore and function call/return.

There are no condition codes. Conditional branches are performed on the basis of a type inferred comparison between two register operands. There is an explicit single register comparison to zero and branch. Branching based on less/less-equal comparisons are not supported. There are modelled as the corresponding greater/greater-equal with the register operands inverted.

The default embedded hello world program generates a 512x512 greyscale mandelbrot and saves it to the current directory.

Supported modes:
- Switch Case interpreter
  - The fetch-execute cycle is modelled using a switch/case construct for the opcode number.
  - For most machines this is the fastest method. Code for handling each opcode is inlined into the case statement.
- Jump Table interpeter
  - The fetch-execute cycle is modelled using a function table that is indexed by the opcode.
  - Implemented as an experiment for comparison with the switch case method. Code for handling each opcode is implemented in a function that is pointed to by a jump table, indexed by the opcode number.
  
Supported platforms:
- Amiga OS 3.x 680x0
- Amiga OS 3.x WarpOS (PPC)
  - Each requires StormC4 (gcc 2.95.3 compatible) to compile the project
- Amiga OS 4.x
- MorphOS 3.x
- Linux arm32, arm64, i386, x64

## Work in progress
The current effort geared towards building a runtime loader and linker, defining a fully portable object code format and an assembler tool for writing virtual code.

## Stuff for later
Port to vanilla C and provide a basic C++ frontend bindings to replace the current C++ code. The main reason for this is to increase portability (i.e more languages and more readily implemented as host native libraries) and hopefully allow for more aggressive optimisation of the interpreter. In any event, the present implementation, which remains compatible with m68k 2.95.x versions of GCC is very much "C with Classes" rather than modern C++ and only makes minimal use of modern C++ language features.
