# Ref: Graphviz Examples: https://graphs.grevian.org/example
# Ref: Graphviz CLI: https://www.graphviz.org/doc/info/command.html

C_FILES := $(wildcard src/*.cpp)
O_FILES := $(patsubst src/%.cpp, bin/%.o, $(C_FILES))
TESTS := bin/trig_test

.PHONY: clean test-trig
	
all: $(O_FILES) $(TESTS)
	
clean:
	rm -f bin/*

test-trig: bin/trig_test
	bin/trig_test

bin/%.o: src/%.cpp src/arduino.h Makefile
	cc -c -o $@ -DDEV_TEST=1 $<

bin/trig_test: bin/trig.o
	cc bin/trig.o -o bin/trig_test

