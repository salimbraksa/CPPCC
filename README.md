# CppCodingChallenge
C++ Coding Challenge for United Remote
## Intro
This is a C++ program to evaluate arithmetic expression, and also detect if there an error* in the syntax of expression, or messing something.
*Each error in input, will generate an exception content:
- the invalid expression
- index of error in the expression
- short message to explain the error
- code of error for other use

## Supported Input:
- +,-,*,/, and parentheses.
- Positive and negative numbers**.

** Each number can have only one sign or without e.g. +A, -A, A,
Input like this is acceptable: A*-B, A-+B, A++B, the first sign for operation and the second is the sign of number.

### Example input:
- 3+(5+(4*3))-12
- +3+(5+(-4*+3))--12

## the structure of project:
```
CppCodingChallenge
|
|---- Others files for Microsoft Visual Studio and Git
|
|---- CppCodingChallenge
|     |
|     |---- Others files for Microsoft Visual Studio
|     |
|     |---- CMakeLists.txt : to build project with cmake
|     |
|     |---- CppCodingChallenge.cpp : the main of project
|     |
|     |---- src
|     |     |
|     |     |---- ArithmeticExpression.h : header of ArithmeticExpression class
|     |     |
|     |     |---- ArithmeticExpression.cpp : source code of ArithmeticExpression class
|     |     |
|     |     |---- ArithmeticExpressionException.h : for exception manage
|     |     |
|     |     |---- CharStat.h : an Enum structure to define the status of an character in the expression
|     |
|     |---- libs
|     |       |
|     |       |---- GeneralItem : content some general uses functions
|     |
|     |
|     |---- tests : some example to use the features of project
```
## How to build and execute the project?
- With Microsoft Visual Studio, required Microsoft visual studio with g++ compiler
  - Clone the repository and open CppCodingChallenge.sln file with Microsoft visual studio, or open the project directly from Git-hub.
- Use cMake, required cmake and g++ compiler
  1. clone the repository
  2. `cd CppCodingChallenge/CppCodingChallenge`
  3. `mkdir build`
  4. `cd build`
  5. `cmake ..`
  6. `make`
  7. `./CppCodingChallenge.exe`
- Manual compilation, required g++ compiler
  1. clone the repository
  2. `cd CppCodingChallenge/CppCodingChallenge`
  3. `mkdir build`
  4. `cd build`
  5. `g++ -o CppCodingChallenge.exe ../CppCodingChallenge.cpp ../src/ArithmeticExpression.cpp`
  6. `./CppCodingChallenge.exe`
## Notes
- The explication of code and how the program work it in the comments in the code.
- This project is only to perform how I write the codes and how I structured the projects, not performed on calculation speed.

## Author
- FAIRADI Mouhcine mouhcinefd@outlook.com
