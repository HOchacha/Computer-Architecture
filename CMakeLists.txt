cmake_minimum_required(VERSION 3.22)
project(Computer_Architecture)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project1 Project1/main.c
        Project1/instruction_cycle.c
        Project4/component/cache/cache_memory.c
        Project4/component/cache/cache_memory.h
)

add_executable(Project2 Project2/main.c
        Project2/component/register/register.h
        Project2/component/register/register_impl.c
        Project2/single_cycle/execute/execute_instruction.c
        Project2/single_cycle/execute/execute_instruction.h
        Project2/single_cycle/fetch/fetch_instruction.c
        Project2/single_cycle/fetch/fetch_instruction.h
        Project2/single_cycle/writeback/write_back_instruction.c
        Project2/single_cycle/writeback/write_back_instruction.h
        Project2/single_cycle/decode/decode_instruction.c
        Project2/single_cycle/decode/decode_instruction.h
        Project2/component/memory/memory.h
        Project2/component/control_unit/control_unit.c
        Project2/component/alu/alu.c
        Project2/component/miscelenous/path_variable.h
        Project2/component/memory/memory.c
        Project2/component/control_unit/control_unit.h
)

add_executable(Project4 Project4/main.c
        Project4/component/register/register.h
        Project4/component/register/register_impl.c
        Project4/single_cycle/execute/execute_instruction.c
        Project4/single_cycle/execute/execute_instruction.h
        Project4/single_cycle/fetch/fetch_instruction.c
        Project4/single_cycle/fetch/fetch_instruction.h
        Project4/single_cycle/writeback/write_back_instruction.c
        Project4/single_cycle/writeback/write_back_instruction.h
        Project4/single_cycle/decode/decode_instruction.c
        Project4/single_cycle/decode/decode_instruction.h
        Project4/component/memory/memory.h
        Project4/component/control_unit/control_unit.c
        Project4/component/alu/alu.c
        Project4/component/miscelenous/path_variable.h
        Project4/component/memory/memory.c
        Project4/component/control_unit/control_unit.h
        Project4/component/cache/cache_memory.c
        Project4/component/cache/cache_memory.h
        Project4/component/cache/cache_memory.c
        Project4/component/cache/history_buffer.c
        Project4/component/cache/history_buffer.h
        Project4/component/cache/history_buffer.c
)
