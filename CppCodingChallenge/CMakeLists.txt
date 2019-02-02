cmake_minimum_required( VERSION 3.0 )

project( CppCodingChallenge )

include_directories( ./lib ./src )

add_executable( CppCodingChallenge.exe ./CppCodingChallenge.cpp ./src/ArithmeticExpression.cpp )
