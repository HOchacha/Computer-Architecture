# MIPS Single Cycle Processing

# Pipelined Structure
구현 목표
1. 파이프라인 구조 vs 싱글 사이클 구조 간의 비교
- CPU clock cycle 횟수를 비교할 것
- 정확한 output을 제공할 것
2. Machine init.
- 처리 시작 전에, 메모리에 binary file을 입력할 것, 메모리 구조는 큰 배열 형태로 구현 가능
- RA를 제외한 모든 register는 0으로 초기화되며, RA는 FFFFFFFF으로 초기화된다. 
- PC가 FFFF:FFFF가 되면 프로그램을 종료한다. 
- 프로그램은 0x0에 로드되며, stack pointer는 0x10000000에 로드된다. 
3. Implementation requirement
- 5개의 pipeline stage 구현
- 각 Stage는 Latch를 통해서 값을 입력 받음
- Instruction Memory와 Data memory를 구분할 수 있음
- emulated clock을 구현해야 함 -> Clock cycle의 횟수를 알 수 있도록 하는 장치
- Data Dependency를 해결해야 함
  - stall
  - forwarding(basic)
  - register renaming
- Control Dependency를 해결해야 함
  - delayed branch
  - Invalidation
  - branch prediction(option)
4. Output
- Cycle의 끝에는 simulator가 micro-architecture state를 출력할 수 있도록 한다. 
- micro-architecture state에는 gp_register, PC, mem, latch, internal data structure 등을 포함한다. 
5. Terminal Condition
- end of execution, 최종적으로 연산된 값을 출력해야 한다. (이 때, branch miss로 인해 잘못 연산되는 경우에는 주의할 것)
- 최종 반환 값은 v2에 저장되어야 한다.
- 이전 프로젝트와 동일한 반환 값을 제공하도록 한다.
6. Evaluation
- HW에 기반한 technique을 보여줄 수록 높은 점수 부여
7. 직접 제작한 MIPS binary 사용 가능




