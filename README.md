# Intro
경북대학교 전자공학부 박대진 교수님 마이크로프로세서 강의입니다. 

All of this contents is Lecture of School of Electronic Engineering, Kyungpook National University by ACES Lab. 

# Overall Architecture

Code Memory(program [0:1023])를 읽어와서

tCPU 내부에 있는 [Decode unit](https://github.com/Seonggyu-Bae/MicroProcessor/blob/master/CDecode.cpp) 을 사용해 프로그램을 해석하고 

[Execute Unit](https://github.com/Seonggyu-Bae/MicroProcessor/blob/master/CExecute.cpp) 을 통해 실행하는 기본적인? 16-bit CPU의 구조 

연산은 register[0:15] 에서 이루어지며 

register 의 저장공간이 모자랄 경우 

memory[0:255]에 저장을 해놓고 다시 가져다 사용하는 방식 


![architecture](https://postfiles.pstatic.net/MjAxOTExMDNfMTY1/MDAxNTcyNzY3ODMzNzc0.5Mz3m21dOhMzQAdHE9PVigBKasavHoi3RNSF9SAptXQg.xi4BIU14P3cpNUg2DvfNizFGUybfiY8bCILdPJontwEg.PNG.qotjdrb6/%EC%BA%A1%EC%B2%98.PNG?type=w773)

![architcture](https://postfiles.pstatic.net/MjAxOTExMDNfMjYx/MDAxNTcyNzY3ODMzODI1.DHLghTodL_Pwb5m13iPBA7wZPFCeNH7sPwIrwyZwspsg.gI83x70YjfD-oUnVLMBAco81O6K5N3fgFiGp8bTb23wg.PNG.qotjdrb6/%EC%BA%A1%EC%B2%981.PNG?type=w773)



# tPU Instruction Set Architecture

### tPU의 명령어들의 이름과 무엇을 수행하는지를 서술하였다.

### Example Structure
- Name(Opcode Operand1 Operand2)

   -description  


### Real Structure

[코드보기](https://github.com/Seonggyu-Bae/MicroProcessor/blob/master/CExecute.cpp)

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

### 마지막 프로젝트인 5X5 행렬 곱 연산, 성능개선

### 새로운 명령어를 만들고 그 명령어에 대한 적절한 소요클럭설정과 적절한 이유가 목표였는데

### 당시에는 기존에 있던 명령어들로 최소한의 클럭을 만들어야 한다고 이해해서 그냥 있는 명령어들만 사용했다

### 모든 행렬은 메모리에 저장되어 있어야하고

### JZ 명령어를 이용해 Loop 형태로 프로그램을 작성하여야함


### 수행해야할 행렬 연산
![architecture](https://postfiles.pstatic.net/MjAyMDExMDZfMjY5/MDAxNjA0NjY5NDQ0Mjg5.TInTcn8X4_YD_vmeGKVh245UBpiKUCvZARw7SUcAVe4g.7tCJEJwK8hJY549-BSNZCtAmUSHmf21vfrvAhs0rQZEg.PNG.qotjdrb6/image.png?type=w773)



### 연산 설명

![architecture](https://postfiles.pstatic.net/MjAyMDExMDZfMTI4/MDAxNjA0NjcxMzA5NjIy.diFjp3nHXm_cZtA-lvnfAp9pkFuJOgOL-1cjbP2vJ8Yg.oQV12HsHuymKeE_roNCVdHQQGePnjcJ9ISg09UoTC1og.PNG.qotjdrb6/image.png?type=w773)




![architecture](https://postfiles.pstatic.net/MjAyMDExMDZfNDgg/MDAxNjA0NjcxNDg1OTEz.1na2F_dkzv6IOrkIGY8xa86qAx0dV8mMLSApp13p-jsg.R9evqqPXUrTJfMNR_qKxdqUD_boA4avNhu2XbmTQNugg.PNG.qotjdrb6/image.png?type=w773)



![architecture](https://postfiles.pstatic.net/MjAyMDExMDZfMjEz/MDAxNjA0NjcxNjI5MTYy.RtyhxzgW1ydmN064Wi4qCgJvBwEXM-DlJy3qA5XveEQg.uKLZRPgPEU6xfwfYmz0t_0EeyEOELpT6j3-qA_c1RFwg.PNG.qotjdrb6/image.png?type=w773)


![architecture](https://postfiles.pstatic.net/MjAyMDExMDZfMjEw/MDAxNjA0NjcxNzQ4MDI0.P2nHTQvT6zQRwqVo1E3Nm2WkzDDZ03mxjlmsqieV0kgg.QBXrF62nKajXd81c_HP0T3WNrvFqXFNmqCbdRm5qsMAg.PNG.qotjdrb6/image.png?type=w773)


### [HW3Upgrade.bin](https://github.com/Seonggyu-Bae/MicroProcessor/blob/master/HW3Upgrade.bin) 파일은 5X5 행렬 곱 연산을 tPU로 수행하기 위한 binary code
### (위의 MOV,ADD, ... etc 들을 이진수로 바꿔놓은것임)
### (당연히 binary code 로 바꿔야 tPU가 알아먹고 실행을 해준다)
