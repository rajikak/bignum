# Writing a Compiler Using LLVM: Building a BigNum Calculator

This tutorial walks through how to implement a compiler using LLVM for a scientific calculator. An introduction to LLVM and it's tool chain is 
available [here](https://github.com/rajikak/rajikak/blob/master/llvm-tool-chain.md).


* [ ] Introduction to IVY and document BigNumber calculator examples and syntax
* [ ] BNF grammar and language spec
* [ ] LLVM tool chain and howto
* [ ] Same compiler just using Go
* [ ] Handwritten lexer
* [ ] Handwritten parser
* [ ] Generated lexer + parser pair
* [ ] Compare performance with ivy implementation (https://pkg.go.dev/robpike.io/ivy#section-readme)
* [ ] Compare performance with Go, Rust, Python, C, C++, Java math libraries
* [ ] Extend the compiler to support [Discreate mathematics](https://a.co/d/abDKSbE)

## Unary Operators

| Name            | Operator | Description |
|-----------------|----------|------------|
| Index generator | iota B   | Vector of the first B integers |
| Random number generator| ?B| Random number between 0 and B  |


## Binary operators

`A`, `B` can be scalars or vectors, or multi-dimensional vectors (matrices).    

| Name     | Operator | Description       |
|----------|----------|-------------------|
| Add      | A + B    | Sum A and B       |
| Subtract | A - B    | A subtract B      |
| Multiply | A * B    | A multiplied by B |
   
## Examples

| Expression                         | Result                                                            |
|------------------------------------|-------------------------------------------------------------------|
| `23`                               | `23`                                                              |
| `23 + 45`                          | `68`                                                              |
| `1e10`                             | `10000000000`                                                     |
| `1e100`                            | `1e100`                                                           |
| `2^64`                             | `1.8446744e+19`                                                   |
| `2^640`                            | `4.562441e+192`                                                   |
| `1 2 3 4 5 6`                      | `[1 2 3 4 5 6]` (Vector)                                          |
| `1 2 3 + 4 5 6`                    | `[5 7 9]`                                                         |
| `itoa 10`                          | `[1 2 3 4 5 6 7 8 9 10]`                                          |
| `2 ** itoa 100`                    | `[2 4 8 16 32 64]`                                                |
| `(2 ** itoa 100) == (1<<itoa 100)` ||
| `5 rho 1`                          | `[1 1 1 1 1]`                                                     |
| `5 5 rho 1`                        | `5x5 matrix of values 1`                                          |
| `5 5 itoa 1`                       | `5x5 matrix of 1..25`                                             |
| `?100`                             | Random number between 0 and 100                                   |
| `?10 rho 100`                      | Vector of size `(1x100)` of random numbers below between 0 and 10 |
| `1 << 1 2 3 4 5`                   | `[2 4 8 16 32]`                                                   |
 
## GRAMMAR
|BNF| Description |
|----|-------------|
|||

## References
* [ivy](https://pkg.go.dev/robpike.io/ivy#section-readme)
* [Implementing a bignum calculator with Rob Pike](https://www.youtube.com/watch?v=PXoG0WX0r_E&t=1121s)
* [Lexical Scanning in Go - Rob Pike](https://www.youtube.com/watch?v=HxaD_trXwRE)
