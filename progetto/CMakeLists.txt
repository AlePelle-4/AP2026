cmake_minimum_required(VERSION 3.20)
project(progetto)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wshadow -Werror=vla")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_executable(prova_main_de_pina main_de_Pina.cpp timecounter.cpp)

add_executable(prova_main_cicli_fond main_cicli_fondamentali.cpp timecounter.cpp)

add_executable(test_circuito_de_pina test_circuito_de_pina.cpp)
add_executable(test_circuito_cicli_fond test_circuito_cicli_fond.cpp)

enable_testing()
add_test(NAME TestCircuito_de_Pina COMMAND test_circuito_de_pina "${CMAKE_SOURCE_DIR}/Netlist_test.txt")
add_test(NAME TestCircuito_cicli_fond COMMAND test_circuito_cicli_fond "${CMAKE_SOURCE_DIR}/Netlist_test.txt")
