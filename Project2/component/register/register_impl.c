//
// Created by user on 2024-04-02.
//
#include "register.h"
#define LOG
extern Register general_reg;


// TODO: 음, 함수를 적절히 분리시키지 못하면, 나중에 파이프라이닝에서 골치 아파질 가능성이 존재한다.
//       현재 머릿속으로 생각중인 것은, 입력, 출력을 모두 전역 변수를 이용하여 선언하는 것이다.
//       이러면 데이터 지역 종속성에서 자유로울 수 있으며, 파이프라이닝 동작 시에 더욱 유리할 수 있다.

// TODO: 아니면, 어짜피 회로 연결 방식으로 동작하기 때문에 Don't care로 동작할 것이다.
//       모든 함수를 호출한다고 생각하고, 그냥 사용하자.

// 유연성 측면에서는 함수의 인자와 반환 값을 제거하고 전역 변수를 이용하여 시스템을 구축하는 것이 적절해보인다.
// 하지만, 시스템의 안전성.,....은 걱정되긴 한다. 그리고 누가 내 코드 보자마자 쌍욕 박을 것이 분명하다.
// 객체 지향 관점에서 동작시키는 것도 나쁘지 않을 것 같음

// TODO : 1. 각 컴포넌트 별로, 모듈화하여 각각의 동작을 만들 것
//        2. Major 컴포넌트에 해당되지 않는 MUX, Extender는 간단한 함수 구현 혹은 If 문으로 처리한다.
//        3. Control Signal은 전역 변수로 관리한다.
//        4. 어떠한 일이 있어도, 일단은 변수가 32비트를 사용하지 않더라도 uint32_t로 구현한다.

/*
// if I type Instruction kicks in, we can call this function with garbage-filled read_target parameter
Reg_out get_value_from_input(Reg_in reg_in){

    Reg_out temp = {0,};

    // this kind of operation is brutally critical for whole system.
    // if it is possible, you must check what the argument kicks in not to refer wrong memory
    // Especially, read_target could be given a large value to exceed the limit of the memory.
    uint32_t* return_reg1 = get_register_from_integer(read_source);
    uint32_t* return_reg2 = get_register_from_integer(read_target);
    uint32_t* write_reg = get_register_from_integer(read_destination);


    return temp;
}
*/

//해당 함수는 실제 회로가 정보를 전달하는 방식으로 동작한다.
// 내부에 Control Logic 처리 로직을 포함한다.
void set_register_with_write_data(uint32_t data_path, uint32_t regWrite){

}

//해당 함수는 실제 회로를 모방한 것이 아닌, 단순히 함수, 즉 행동에 초점을 맞춰서 매개 변수를 전달한다.
void set_register_with_write_data_as_behavior(){

}

// TODO: write_address에서 값이 0일 때, 입력된 값을 무시하도록 한다.
void set_register_from_input(uint32_t write_data, uint32_t write_address, uint32_t is_write){
    if(write_address == 0 || is_write == 0){
        return;
    }
#ifdef LOG
    printf("REG WRITE BACK : REG[%d] = %08x\n", write_address, write_data);
#endif
    general_reg.reg[write_address] = write_data;
}

Reg_out get_value_from_decoded_values(Decoded_values decoded_values, CU_output control_signal){
    Reg_out reg_out = {0,};
    reg_out.reg1 = general_reg.reg[decoded_values.rs];
    reg_out.reg2 = general_reg.reg[decoded_values.rt];


    printf("return 1 : [%08x], return 2 : [%08x]\n", reg_out.reg1, reg_out.reg2);

    return reg_out;
}