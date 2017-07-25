# Common include for the linker test

OBJ      =  obj/$(ARCH)/vm_symbol.o \
            obj/$(ARCH)/vm_linker.o \
            obj/$(ARCH)/vm_debug.o \
            obj/$(ARCH)/test_linker.o

$(BIN): $(OBJ) Makefile_Linker.$(MEXT)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(BIN)

obj/$(ARCH)/vm_symbol.o: vm_symbol.cpp include/machine.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/vm_linker.o: vm_linker.cpp include/machine.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/vm_debug.o: vm_debug.cpp include/vm.hpp include/machine.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/test_linker.o: test_linker.cpp include/machine.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	$(RM) $(TARGET) obj/$(ARCH)/*.o *~ core

