cmake_minimum_required(VERSION 3.29)
project(AutoVendas C)

set(CMAKE_C_STANDARD 99)

add_executable(AutoVendas AutoVendas.c
        carros.h
        carros.c
        cadastro.h
        clientes.h
        clientes.c
        vendas.h
        vendas.c
        cadastro.c

)
