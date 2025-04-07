# Writing a Compiler Using LLVM: Building a BigNum Calculator

This tutorial walks through how to implement a compiler using LLVM for a scientific calculator. An introduction to LLVM and it's tool chain is 
available [here](https://github.com/rajikak/rajikak/blob/master/llvm-tool-chain.md).

## Build and Run 
[Compile and run](https://github.com/rajikak/rajikak/blob/master/llvm-install.md) LLVM from the source and add the `bin` folder into `$PATH`. 

### Using System Default
Reference: https://andreasfertig.blog/2021/02/clang-and-gcc-on-macos-catalina-finding-the-include-paths/
```
$ export SDKROOT="`xcrun --show-sdk-path`"
$ clang++ -std=c++20  src/*.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -g -o bignum1 
$ ./bignum1 "2 + 7" | llc -filetype=obj -o=bignum1.o 
$ clang -o bignum bignum1.o src/rtcalc.c
$ ./bignum
result: 9
```

### Passing Header and Library Paths Externally
This produced missing headers although header and library locations are passed externally. Just record here for reference.

```
$ clang++ \
		-I/Users/kumarasiri/work/intbricks/llvm-project-llvmorg-14.0.0/install/include/c++/v1 \
		-I/Library/Developer/CommandLineTools/SDKs/MacOSX13.1.sdk/usr/include/ \
		-I/Users/kumarasiri/work/intbricks/llvm-project-llvmorg-14.0.0/install/include \
		-L/Library/Developer/CommandLineTools/SDKs/MacOSX13.1.sdk/usr/lib \
		-L/Users/kumarasiri/work/intbricks/llvm-project-llvmorg-14.0.0/install/lib \
		 -std=c++20  src/*.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core` -g -o bignum1
$ ./bignum1 "2 + 7" | llc -filetype=obj -o=bignum1.o
$ clang -o bignum bignum1.o src/rtcalc.c
$ ./bignum 
result: 9
```

```
./bignum1 "2 + 3" | llc -filetype=obj -o=bignum1.o
$LLVM_DIR/bin/clang -cc1 src/rtcalc.c -o bignum1.o bignum
./bignum
```

## Unary Operators

| Name                    | Operator | Description |
|-------------------------|----------|------------|
| Index generator         | `iota B` | Vector of the first B integers |
| Random number generator | `?B`     | Random number between 0 and B  |


## Binary operators

`A`, `B` can be scalars or vectors, or multi-dimensional vectors (matrices).    

| Name    | Operator | Description       |
|---------|----------|-------------------|
| Add     | `A + B`    | Sum `A` and `B`       |
| Subtract | `A - B`    | `A` subtract `B`      |
| Multiply | `A * B`    | `A` multiplied by `B` |
| Shift   | `n << A`   |  Shift `A` by `n` times|
   
## Examples

| Expression                         | Result                                                            |
|------------------------------------|-------------------------------------------------------------------|
| `23`                               | `23`                                                              |
| `23 + 45`                          | `68`                                                              |
| `1e10`                             | `10000000000`                                                     |
| `1e100`                            | `1e100`                                                           |
| `2 ** 64`                          | `1.8446744e+19`                                                   |
| `2 ** 640`                         | `4.562441e+192`                                                   |
| `2.1 + 3.2`                        | `5.3`                                                             |
| `2.121212122121 + 3.1212121212`    | `5.24242424332`|
| `1 2 3 4 5 6`                      | `[1 2 3 4 5 6]` (Vector)                                          |
| `1 2 3 + 4 5 6`                    | `[5 7 9]`                                                         |
| `itoa 10`                          | `[1 2 3 4 5 6 7 8 9 10]`                                          |
| `2 ** itoa 10`                     | `[2 4 8 16 32 64]`                                                |
| `(2 ** itoa 100) == (1<<itoa 100)` ||
| `5 rho 1`                          | `[1 1 1 1 1]`                                                     |
| `5 5 rho 1`                        | `5x5 matrix of values 1`                                          |
| `5 5 itoa 1`                       | `5x5 matrix of 1..25`                                             |
| `?100`                             | Random number between 0 and 100                                   |
| `?10 rho 100`                      | Vector of size `(1x100)` of random numbers below between 0 and 10 |
| `1 << 1 2 3 4 5`                   | `[2 4 8 16 32]`                                                   |
| `2 * log(10)`                      | `4.605170185988092`|
| `+/itoa 15`		                 | `120` (add first 15 numbers together)|
| `1 * 2 * 3`						 | `6` (3!)|
| `*/itoa 3`						 | `6`|
| `2*itoa 2 + 3`					 | `2 4 6 8 10`|
 
## Grammar
```
Statement      -> Expression
               
Expression     -> Operand
                | Operand BinaryOp Expression
               
Operand        -> ( Expression )
               | Operand
               | Number
               | Rational
               | Vector
               | Operand [ Expression ]
               | UnaryOperator Expression

BinaryOperator | +
               | -  
               | /  
               | *
               | **
               | e
               | rho
               | itoa
               | shift

UnaryOperator  | itoa
               | ?
               | << 
```

## Parsing Rules
* Unary operators apply to the rest of the line
* Binary operators apply to the operand on left, rest of the line on right
* Associative to the right

## References
* [LLVM for Grad Students](https://www.cs.cornell.edu/~asampson/blog/llvm.html)
* [Life of an instruction in LLVM](https://eli.thegreenplace.net/2012/11/24/life-of-an-instruction-in-llvm)
* [An Introduction to APL](https://www.youtube.com/watch?v=UltnvW83_CQ)
* [APL demonstration 1975](https://www.youtube.com/watch?v=_DTpQ4Kk2wA)
* [ivy](https://pkg.go.dev/robpike.io/ivy#section-readme)
* [Implementing a bignum calculator with Rob Pike](https://www.youtube.com/watch?v=PXoG0WX0r_E&t=1121s)
* [Lexical Scanning in Go - Rob Pike](https://www.youtube.com/watch?v=HxaD_trXwRE)
