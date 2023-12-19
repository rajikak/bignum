# https://stackoverflow.com/questions/48369566/clang-stdio-h-file-not-found
# https://andreasfertig.blog/2021/02/clang-and-gcc-on-macos-catalina-finding-the-include-paths/

#  with having LLVM/bin in PATH, and c headers and math library is required
#  work with lot of warnings
default:
	clang++ \
		-I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/ \
		-I/Users/kumarasiri/work/intbricks/llvm-project-llvmorg-14.0.0/install/include/c++/v1 \
		-I/Users/kumarasiri/work/intbricks/llvm-project-llvmorg-14.0.0/install/include \
		-L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib \
		-L/Users/kumarasiri/work/intbricks/llvm-project-llvmorg-14.0.0/install/lib \
		-std=c++20  src/*.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -g -o bignum1
	./bignum1 "2 + 7" | llc -filetype=obj -o=bignum1.o
	 clang \
		 -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/ \
		 -L/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/lib \
		 -o bignum bignum1.o src/rtcalc.c
	./bignum

# run export SDKROOT="`xcrun --show-sdk-path`" in the shell or add to .bash_profile
l:
	clang++ -std=c++20  src/*.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -g -o bignum1
	./bignum1 "2 + 7" | llc -filetype=obj -o=bignum1.o
	clang -o bignum bignum1.o src/rtcalc.c
	./bignum
