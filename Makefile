default: c
	./bignum "2 + 3" | llc -filetype=obj -o=expor.o
	
c: # compile
	clang++ -I/Library/Developer/CommandLineTools/SDKs/MacOSX13.0.sdk/usr/include/c++/v1/ \
			-I/Library/Developer/CommandLineTools/SDKs/MacOSX13.0.sdk/usr/include/ \
			-I/opt/homebrew/include \
			-L/Library/Developer/CommandLineTools/SDKs/MacOSX13.0.sdk/usr/lib/ \
			-L/opt/homebrew/lib/ \
		    -std=c++20 src/*.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -g -o bignum

r: # run
	./bignum "2 + 3" | llc -filetype=obj -o=expor.o
f: # format
	clang-format -i src/*.cpp src/*.h
