//****************************************************************************//
//**                                                                        **//
//** File:         main.cpp                                                 **//
//** Description:  Test Application                                         **//
//** Comment(s):   Internal developer version only                          **//
//** Library:                                                               **//
//** Created:      2001-08-29                                               **//
//** Author(s):    Karl Churchill                                           **//
//** Note(s):                                                               **//
//** Copyright:    (C)1996 - , eXtropia Studios                             **//
//**               All Rights Reserved.                                     **//
//**                                                                        **//
//****************************************************************************//


#include <new>
#include <cstdio>
#include <cstdlib>

using namespace std;

extern void runTestExample(int type);

int main(int argc, const char** argv) {

  int type = argc > 1 ? 1 : 0;

  runTestExample(type);
  return 0;
}
