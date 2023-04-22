# Writing a Compiler Using LLVM: Building a BigNum Calculator

* [ ] Introduction to IVY and document BigNumber calculator examples and syntax
* [ ] BNF grammar and language spec
* [ ] LLVM tool chain and howto
* [ ] Same compiler just using Go
* [ ] Handwritten lexer
* [ ] Handwritten parser
* [ ] Generated lexer + parser pair
* [ ] Compare performance with ivy implementation (https://pkg.go.dev/robpike.io/ivy#section-readme)
* [ ] Compare performance with Go, Rust, Python, C, C++, Java math libraries

## Unary Operators

| Name            | Operator | Description |
|-----------------|----------|------------|
| Index generator | iota B   | Vector of the first B integers |
| Paragraph       |          | Text       |


## Binary operators

`A`, `B` can be scalars or vectors, or multi-dimensional vectors (matrices).    

| Name     | Operator | Description       |
|----------|----------|-------------------|
| Add      | A + B    | Sum A and B       |
| Subtract | A - B    | A subtract B      |
| Multiply | A * B    | A multiplied by B |
   

## References
* [ivy](https://pkg.go.dev/robpike.io/ivy#section-readme)
* [Implementing a bignum calculator with Rob Pike](https://www.youtube.com/watch?v=PXoG0WX0r_E&t=1121s)
* [Lexical Scanning in Go - Rob Pike](https://www.youtube.com/watch?v=HxaD_trXwRE)
