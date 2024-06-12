cmake_minimum_required(VERSION 3.22)
project(Computer_Architecture)

set(CMAKE_CXX_STANDARD 17)

add_executable(Project3 main.c
        component/register/register.h
        component/register/register_impl.c
        single_cycle/execute/execute_instruction.c
        single_cycle/execute/execute_instruction.h
        single_cycle/fetch/fetch_instruction.c
        single_cycle/fetch/fetch_instruction.h
        single_cycle/writeback/write_back_instruction.c
        single_cycle/writeback/write_back_instruction.h
        single_cycle/decode/decode_instruction.c
        single_cycle/decode/decode_instruction.h
        component/memory/memory.h
        component/control_unit/control_unit.c
        component/alu/alu.c
        component/miscelenous/path_variable.h
        component/memory/memory.c
        component/control_unit/control_unit.h
        util/utils.c
        component/latch/latch.h
        component/latch/latch.c
        single_cycle/memory_access/memory_access.h
        single_cycle/memory_access/memory_access.c
        component/forwarding_unit/forwarding_unit.c
        component/forwarding_unit/forwarding_unit.h
        component/miscelenous/decode_type.h
        single_cycle/decode/decode_pipe.h
        single_cycle/decode/decode_pipe.c
        component/last_branch_prediction/last_branch_predictor.c
        component/last_branch_prediction/last_branch_predictor.h
)
