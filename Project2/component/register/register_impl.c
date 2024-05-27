//
// Created by user on 2024-04-02.
//
#include "register.h"
#define LOG
extern Register general_reg;


// TODO: 음, 함수를 적절히 분리시키지 못하면, 나중에 파이프라이닝에서 골치 아파질 가능성이 존재한다.
//       현재 머릿속으로 생각중인 것은, 입력, 출력을 모두 전역 변수를 이용하여 선언하는 것이다.
//       이러면 데이터 지역 종속성에서 자유로울 수 있으며, 파이프라이닝 동작 시에 더욱 유리할 수 있다.

void set_register_from_input(uint32_t write_data, uint32_t write_address, uint32_t is_write, uint32_t is_upper_access){
    if(write_address == 0 || is_write == 0){
        return;
    }
#ifdef LOG
    printf("REG WRITE BACK : REG[%d] = %08x\n", write_address, write_data);
#endif
    if(write_address < 32){
        general_reg.reg[write_address] = write_data;
    }
}

Reg_out get_value_from_decoded_values(Reg_in register_in){
    Reg_out reg_out = {0,};
    if(register_in.read_source < 32 && register_in.read_target < 32){
        reg_out.reg1 = general_reg.reg[register_in.read_source];
        reg_out.reg2 = general_reg.reg[register_in.read_target];
    }

    //printf("return 1 : [%08x], return 2 : [%08x]\n", reg_out.reg1, reg_out.reg2);

    return reg_out;
}