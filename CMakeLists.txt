/**
* Main acts as an intrface to all the components of the calculator
* @author Jack O Mahony (117498152)
* @date 13/11/2019
*/

cmake_minimum_required(VERSION 3.15)
project(calc C)

set(CMAKE_C_STANDARD 99)

add_executable(calc main.c virtualmachine.h tokenizer.h codegenerator.c codegenerator.h infix2postfix.c infix2postfix.h tokenizer.c virtualmachine.c)
