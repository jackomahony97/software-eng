cmake_minimum_required(VERSION 3.15)
project(calc C)

set(CMAKE_C_STANDARD 99)

add_executable(calc main.c virtualmachine.h tokenizer.h codegenerator.c codegenerator.h infix2postfix.c infix2postfix.h tokenizer.c virtualmachine.c)