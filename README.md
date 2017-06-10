# exvm
Experimental Virtual Machine

A simple register based interpretive virtual machine, written as an old experiment. The default embedded hello world program generates a 512x512 greyscale mandelbrot and saves it to the current directory.

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
- Linux i386
- Linux x64
