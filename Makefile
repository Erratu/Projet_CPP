.PHONY: all doc clean

all:
	mkdir -p build && cd build && cmake .. && make

doc:
	mkdir -p build && cd build && cmake .. && make doc

clean:
	rm -rf build docu