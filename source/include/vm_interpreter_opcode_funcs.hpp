//****************************************************************************//
//**                                                                        **//
//** File:         vm.hpp                                                   **//
//** Description:  Virtual Machine definitions                              **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-14                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//

// Opcode handlers that require sufficient code to be realised as discrete
// functions
static void doBCALL8(CLASS* vm, uint16 op);
static void doBCALL16(CLASS* vm, uint16 op);
static void doCALL(CLASS* vm, uint16 op);
static void doCALLN(CLASS* vm, uint16 op);
static void doICALL(CLASS* vm, uint16 op);
static void doICALLN(CLASS* vm, uint16 op);
static void doSV(CLASS* vn, uint16 op);
static void doRS(CLASS* vn, uint16 op);
static void doPUSH_8(CLASS* vm, uint16 op);
static void doPUSH_16(CLASS* vm, uint16 op);
static void doPUSH_32(CLASS* vm, uint16 op);
static void doPUSH_64(CLASS* vm, uint16 op);
static void doPOP_8(CLASS* vm, uint16 op);
static void doPOP_16(CLASS* vm, uint16 op);
static void doPOP_32(CLASS* vm, uint16 op);
static void doPOP_64(CLASS* vm, uint16 op);
static void doSALLOC(CLASS* vm, uint16 op);
static void doSFREE(CLASS* vm, uint16 op);
static void doVEC1(CLASS* vm, uint16 op);
static void doADV(CLASS* vm, uint16 op);
