# MIPS Single Cycle Processing

- MIPS 프로그램의 구조
0. Initializing(Configuration) 
1. begin execution in a loop
   1. check terminal condition -> ex) check eof
   2. Single Cycles
      1. fetch
      2. decode
      3. execute
      4. memory access
      5. writeback
2. print out stats

- Single Cycle은 다음과 같이 구성된다.
  - Fetch
  - Decode
  - Execute
  - Write Back
- 각 단계의 동작은 하나의 함수로 실행되도록 한다.
  - Ex) Fetch Instruction에서는 PC 접근, Instruction Memory 접근, 명령어를 Data path에 전달
  - 부품은 다음과 같이 구현한다. 
    - Component : Function
    - Dataline : Variable -> according to dataline width
    - Architectural State : Global Variable
  - 각 Input Data에 따른 Component의 구동은 반드시 State가 Capturing된 상태에서 구동된다. 
    - Architectural State가 다른 파이프라인에서 영향을 받아서 비정상적인 동작이 발생되지 않도록 한다.
    - output이 specify되면 바로 변수로 저장하여, 싱글 사이클에서의 동작이 영향받지 않도록 한다. 