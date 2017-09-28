# Common include for building the interpreter

OBJ      = obj/$(ARCH)/test_advanced.o \
           obj/$(ARCH)/machine.o \
           obj/$(ARCH)/op_control.o \
           obj/$(ARCH)/op_load.o \
           obj/$(ARCH)/op_store.o \
           obj/$(ARCH)/op_move.o \
           obj/$(ARCH)/op_jump.o  \
           obj/$(ARCH)/op_convert.o \
           obj/$(ARCH)/op_arithmetic.o \
           obj/$(ARCH)/op_logic.o \
           obj/$(ARCH)/op_advanced.o \
           obj/$(ARCH)/op_vector.o \
           obj/$(ARCH)/vm_core.o \
           obj/$(ARCH)/op_jump_table.o \
           obj/$(ARCH)/vm_symbol.o \
           obj/$(ARCH)/vm_linker.o \
           obj/$(ARCH)/vm_debug.o

$(BIN): $(OBJ) Makefile.$(MEXT)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(BIN)

obj/$(ARCH)/test_advanced.o: test_advanced.cpp include/vm_core.hpp include/vm.hpp include/machine.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/machine.o: machine.cpp include/machine.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/op_control.o: op_control.cpp include/vm_core.hpp include/vm.hpp include/machine.hpp include/vm_inline.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/op_load.o: op_load.cpp include/vm_core.hpp include/vm.hpp include/machine.hpp include/vm_inline.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/op_store.o: op_store.cpp include/vm_core.hpp include/vm.hpp include/machine.hpp include/vm_inline.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/op_move.o: op_move.cpp include/vm_core.hpp include/vm.hpp include/machine.hpp include/vm_inline.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/op_jump.o: op_jump.cpp include/vm_core.hpp include/vm.hpp include/machine.hpp include/vm_inline.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/op_convert.o:op_convert.cpp include/vm_core.hpp include/vm.hpp include/machine.hpp include/vm_inline.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/op_arithmetic.o: op_arithmetic.cpp include/vm_core.hpp include/vm.hpp include/machine.hpp include/vm_inline.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/op_logic.o: op_logic.cpp include/vm_core.hpp include/vm.hpp include/machine.hpp include/vm_inline.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/op_advanced.o: op_advanced.cpp include/vm_core.hpp include/vm.hpp include/machine.hpp include/vm_inline.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/op_vector.o: op_vector.cpp include/vm_core.hpp include/vm.hpp include/machine.hpp include/vm_inline.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/vm_core.o: vm_core.cpp include/vm_core.hpp include/vm.hpp include/machine.hpp include/vm_inline.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/op_jump_table.o: op_jump_table.cpp include/vm_core.hpp include/vm.hpp include/machine.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/vm_symbol.o: vm_symbol.cpp include/machine.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/vm_linker.o: vm_linker.cpp include/machine.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/vm_debug.o: vm_debug.cpp include/vm.hpp include/machine.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	$(RM) $(TARGET) obj/$(ARCH)/*.o *~ core


