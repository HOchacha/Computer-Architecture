//
// Created by user on 2024-04-02.
//
#include "register.h"
extern Register reg;


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


// if I type Instruction kicks in, we can call this function with garbage-filled read_target parameter
Reg_out get_value_from_input(uint32_t read_source, uint32_t read_target, uint32_t read_destination, uint32_t is_write, uint32_t write_data){

    Reg_out temp = {0,};

    // this kind of operation is brutally critical for whole system.
    // if it is possible, you must check what the argument kicks in not to refer wrong memory
    // Especially, read_target.
    uint32_t* return_reg1 = get_register_from_integer(read_source);
    uint32_t* return_reg2 = get_register_from_integer(read_target);
    uint32_t* write_reg = get_register_from_integer(read_destination);

    if (is_write == 1){
        *write_reg = write_data;
    }

    return temp;
}

uint32_t* get_register_from_integer(uint32_t reg_integer){
    return &reg.reg[reg_integer];
}