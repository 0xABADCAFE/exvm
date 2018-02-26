# Common include for building the interpreter

OBJ      = obj/$(ARCH)/exception_tests.o \
           obj/$(ARCH)/machine.o \
           obj/$(ARCH)/op_scalar.o \
           obj/$(ARCH)/op_advanced.o \
           obj/$(ARCH)/op_vector.o \
           obj/$(ARCH)/vm_core.o \
           obj/$(ARCH)/vm_symbol.o \
           obj/$(ARCH)/vm_linker.o \
           obj/$(ARCH)/vm_debug.o

$(BIN): $(OBJ) Makefile.$(MEXT)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(BIN)

obj/$(ARCH)/exception_tests.o: exception_tests.cpp include/vm_core.hpp include/vm.hpp include/machine.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/machine.o: machine.cpp include/machine.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/op_scalar.o: op_scalar.cpp include/vm_core.hpp include/vm.hpp include/machine.hpp include/vm_inline.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/op_advanced.o: op_advanced.cpp include/vm_core.hpp include/vm.hpp include/machine.hpp include/vm_inline.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/op_vector.o: op_vector.cpp include/vm_core.hpp include/vm.hpp include/machine.hpp include/vm_inline.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/vm_core.o: vm_core.cpp include/vm_core.hpp include/vm.hpp include/machine.hpp include/vm_inline.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/vm_symbol.o: vm_symbol.cpp include/machine.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/vm_linker.o: vm_linker.cpp include/machine.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/vm_debug.o: vm_debug.cpp include/vm.hpp include/machine.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	$(RM) $(TARGET) obj/$(ARCH)/*.o *~ core
