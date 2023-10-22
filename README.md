# Writing a Compiler Using LLVM: Building a BigNum Calculator

This tutorial walks through how to implement a compiler using LLVM for a scientific calculator. An introduction to LLVM and it's tool chain is 
available [here](https://github.com/rajikak/rajikak/blob/master/llvm-tool-chain.md).


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
 
## Grammar
```
Program        -> Statements
               
Statements     -> Statement ; Statement
                | Statement
                
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

## References
* [An Introduction to APL](https://www.youtube.com/watch?v=UltnvW83_CQ)
* [APL demonstration 1975](https://www.youtube.com/watch?v=_DTpQ4Kk2wA)
* [ivy](https://pkg.go.dev/robpike.io/ivy#section-readme)
* [Implementing a bignum calculator with Rob Pike](https://www.youtube.com/watch?v=PXoG0WX0r_E&t=1121s)
* [Lexical Scanning in Go - Rob Pike](https://www.youtube.com/watch?v=HxaD_trXwRE)
