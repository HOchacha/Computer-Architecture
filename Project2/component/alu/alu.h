//
// Created by user on 2024-04-02.
//
#ifndef STDINT
#define STDINT
#include <stdint.h>
#endif

#ifndef COMPUTER_ARCHITECTURE_ALU_H
#define COMPUTER_ARCHITECTURE_ALU_H
typedef struct _alu_input{

}Alu_input;
// TODO: 유교수님께, 상태 레지스터에 대한 정보를 따로 저장하지 않는지 질문
//       누적기 또한 사용하지 않는지 질문
//       ALU에서 bcondition이 따로출력이 있는 것 같은데, 해당 부분은 어떻게 구현해야 하는가?
typedef struct _alu_output{

}Alu_output;

typedef struct _alu_control{
    uint32_t funct;
}ALU_funct;
#endif //COMPUTER_ARCHITECTURE_ALU_H
