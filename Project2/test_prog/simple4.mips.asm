
simple4.o:     file format elf32-tradbigmips


Disassembly of section .text:

00000000 <main>:
   0:	27bdffe0 	addiu	sp,sp,-32
   4:	afbf001c 	sw	ra,28(sp)
   8:	afbe0018 	sw	s8,24(sp)
   c:	03a0f021 	move	s8,sp
  10:	2404000a 	li	a0,10
  14:	0c000000 	jal	0 <main>
  18:	00000000 	nop
  1c:	03c0e821 	move	sp,s8
  20:	8fbf001c 	lw	ra,28(sp)
  24:	8fbe0018 	lw	s8,24(sp)
  28:	27bd0020 	addiu	sp,sp,32
  2c:	03e00008 	jr	ra
  30:	00000000 	nop

00000034 <foo>:                                 // ----> Recursive Start
  34:	27bdffd8 	addiu	sp,sp,-40           // Stack 할당
  38:	afbf0024 	sw	ra,36(sp)               // ra 저장
  3c:	afbe0020 	sw	s8,32(sp)               // fp 저장
  40:	03a0f021 	move	s8,sp               // fp := sp
  44:	afc40028 	sw	a0,40(s8)               // 매개 변수 Stack에 저장
  48:	8fc30028 	lw	v1,40(s8)               // v1 := 매개 변수
  4c:	24020001 	li	v0,1                    // v0 := 1
  50:	14620004 	bne	v1,v0,64 <foo+0x30>     // v1 != 1이면 64로 이동(if문 만족하지 않음)
  54:	00000000 	nop
  58:	24020001 	li	v0,1
  5c:	08000025 	j	94 <foo+0x60>           // 함수 리턴(*프로시저 prolog 준비)
  60:	00000000 	nop
  64:	8fc20028 	lw	v0,40(s8)               // ----> jump Destination from 50
  68:	00000000 	nop
  6c:	2442ffff 	addiu	v0,v0,-1
  70:	00402021 	move	a0,v0               // 매개변수 a - 1로 지정 (레지스터에 저장됨)
  74:	0c00000d 	jal	0xd <foo>               // 재귀 프로시저 호출
  78:	00000000 	nop
  7c:	00401821 	move	v1,v0               // v1 := v0
  80:	8fc20028 	lw	v0,40(s8)               // 지역 변수 a에 매개변수 저장
  84:	00000000 	nop
  88:	00621021 	addu	v0,v1,v0            // v0 := v1 + v0 (v0는 함수 반환 값으로 추정 중)
  8c:	afc20018 	sw	v0,24(s8)               // result 변수에 저장
  90:	8fc20018 	lw	v0,24(s8)               // 프로시저 반환 레지스터에 저장
  94:	03c0e821 	move	sp,s8               // 프로시저 prolog 진행 ----> jump Destination from 5C
  98:	8fbf0024 	lw	ra,36(sp)               // ra 복귀
  9c:	8fbe0020 	lw	s8,32(sp)               //
  a0:	27bd0028 	addiu	sp,sp,40            // 스택 할당 해제
  a4:	03e00008 	jr	ra                      // ----> main Loop extraction
  a8:	00000000 	nop
  ac:	00000000 	nop
