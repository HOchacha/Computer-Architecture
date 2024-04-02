# MIPS Single Cycle Processing

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
