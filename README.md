# Welcome

Welcome to system solver app. System solver app is a personal application written after numerical analysis lectures, with the intent to apply to the real world the algorithms explained by the teacher.

# **You shouldn't ever use this code for different purposes than just learning** #

Since this is just a complement to the theoric lectures, you should use the code just for his purpose: understand how some numerical algorithms works.

## What do the app do?
1. Solve linear system in the form Ax=b ( where A is a NxN square matrix, b a vector of known terms and x a vector of unknows terms) with [the cramer rule](https://en.wikipedia.org/wiki/Cramer%27s_rule)
2. Solve linear system in the form Ax=b (where A is a triangular NxN matrix, b and x as previous) with the [back-substitution method](http://www.mathwords.com/b/back_substitution.htm) 
3. [Gauss elimination](https://en.wikipedia.org/wiki/Gaussian_elimination). Transform a Ax=b system into A'x=b', where A is a generic square matrix and A' is a triangular matrix. The algorithm can also provide the used permutation matrix
4. [Doolittle LU decomposition](https://en.wikipedia.org/wiki/LU_decomposition#Doolittle_algorithm). Decompose directly a square matrix A into L and U triangular matrixes.

## Build

The code is written with Code::blocks (under windows) ide and the build is managed by the ide. You can just open this project with it and press 'build and run' button to obtain an executable file.

Alternatively, you can write you own makefile. Writing it isn't a hard work since the app is composed by few .cpp and .h files. 
**There's a big probability i will write the makefile in a not-so-remote future**

## Usage

When launched, the app search for a definition file (the filename is passed by console parameter), then load it and run the command sequence issued under a specific file section.


```
linear_solver -f datafile.txt
```

A small documentation for the datafile.txt syntax can be found in this wiki: [Definition file structure](https://bitbucket.org/grisson/linear_solver/wiki/Definition%20file%20structure).

## License
This program is distribuited under the WTFPL license. You can use it without limitations, just remind this software is intended to learning purposes. Do yourself a favor and don't use it for professional uses.
