# Common include for building the Symbol Test

OBJ      =  obj/$(ARCH)/vm_symbol.o \
            obj/$(ARCH)/vm_debug.o \
            obj/$(ARCH)/test_symbol.o

$(BIN): $(OBJ) Makefile_Symbol.$(MEXT)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(BIN)

obj/$(ARCH)/vm_symbol.o: vm_symbol.cpp include/machine.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/vm_debug.o: vm_debug.cpp include/vm.hpp include/machine.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

obj/$(ARCH)/test_symbol.o: test_symbol.cpp include/machine.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

clean:
	$(RM) $(TARGET) obj/$(ARCH)/*.o *~ core

