# Intro
경북대학교 전자공학부 박대진 교수님 마이크로프로세서 강의입니다. 

All of this contents is Lecture of School of Electronic Engineering, Kyungpook National University by ACES Lab. 

# Overall Architecture

### Code Memory(program [0:1023])를 읽어와서 
### tCPU 내부에 있는 Decode unit 을 사용해 프로그램을 해석하고 
### Execute Unit 을 통해 실행하는 기본적인? 16-bit CPU의 구조 
### 연산은 register[0:15] 에서 이루어지며 
### register 의 저장공간이 모자랄 경우 
## memory[0:255]에 저장을 해놓고 다시 가져다 사용하는 방식 

![architecture](https://postfiles.pstatic.net/MjAxOTExMDNfMTY1/MDAxNTcyNzY3ODMzNzc0.5Mz3m21dOhMzQAdHE9PVigBKasavHoi3RNSF9SAptXQg.xi4BIU14P3cpNUg2DvfNizFGUybfiY8bCILdPJontwEg.PNG.qotjdrb6/%EC%BA%A1%EC%B2%98.PNG?type=w773)

![architcture](https://postfiles.pstatic.net/MjAxOTExMDNfMjYx/MDAxNTcyNzY3ODMzODI1.DHLghTodL_Pwb5m13iPBA7wZPFCeNH7sPwIrwyZwspsg.gI83x70YjfD-oUnVLMBAco81O6K5N3fgFiGp8bTb23wg.PNG.qotjdrb6/%EC%BA%A1%EC%B2%981.PNG?type=w773)



# tPU Instruction Set Architecture

### tPU의 명령어들의 이름과 무엇을 수행하는지를 서술하였다.

### Example Structure
- Name(Opcode Operand1 Operand2)

   -description  


### Real Structure

* MOV0 (0000 R(n) direct)


  -register[n] 에 Memory[direct] 에 있는값을 써주는 명령어

  -R(n) <- Mem(direct)
 
  -PC <- PC + 1
  
 
 
* MOV1 (0001 R(n) direct)


  -Memory[direct] 에 register[n] 에 있는값을 써주는 명령어

  -Mem(direct) <- R(n)
 
  -PC <- PC + 1
  

 
 * MOV2 (0010 R(n) 0000R(m))
 
 
   -Memory[R(n)] 에 register[m] 에 있는값을 써주는 명령어
 
   -Mem(R(n)) <- R(m)
 
   -PC <- PC + 1
   

 
 * MOV3 (0011 Rn #immed)
 
 
    -register[m] 에 원하는 값(#immed)을 써주는 명령어
 
    -R(n) <- #immed
 
    -PC <- PC + 1
    

 
 * ADD (0100 Rn Rm0000)
 
 
    -register[n] 에 register[n] + register[m]의 값을 써주는 명령어
 
    -R(n) <- R(n) + R(m)
 
    -PC <- PC + 1
    
 
 * SUB (0101 R(n) R(m)0000)
 
 
    -register[n] 에 register[n] - register[m]의 값을 써주는 명령어
 
    -R(n) <- R(n)-{R(m) >> 4}
 
    -PC <- PC + 1
    
    
 * JZ (0110 R(n) (signed)relative)
 
 
    -이 명령어를 만나면 R(n)의 값이 0 이라면 (singned)relative 값 만큼 뛰어넘어서 명령어를 실행한다
 
    -If R(n) == 0
 
    -PC <- PC + 1 + relative
    
    
 * MUL (0111 R(n) R(m)0000)
 
 
    -register[n] 에 register[n] X register[m]의 값을 써주는 명령어
 
    -R(n) <- R(n) X R(m)
 
    -PC <- PC + 1
    
   
 * MOV4 (1000 R(n) R(m)0000)
 
 
    -register[n] 에 register[m]의 값을 써주는 명령어
 
    -R(n) <- R(m)
 
    -PC <- PC + 1
    
 
 * MOV5 (1001 R(n) 0000R(m))
 
 
    -register[n] 에 memory[R(m)] 의 값을 써주는 명령어
 
    -R(n) <- Mem{R(m)}
 
    -PC <- PC + 1
    
   
    
    
# tPU 사용 예시

![architecture](https://postfiles.pstatic.net/MjAyMDExMDZfMjY5/MDAxNjA0NjY5NDQ0Mjg5.TInTcn8X4_YD_vmeGKVh245UBpiKUCvZARw7SUcAVe4g.7tCJEJwK8hJY549-BSNZCtAmUSHmf21vfrvAhs0rQZEg.PNG.qotjdrb6/image.png?type=w773)

The HW3Upgrade.bin 파일은 5X5 행렬 곱 연산을 tPU로 수행하기 위한 binary code 이다.
