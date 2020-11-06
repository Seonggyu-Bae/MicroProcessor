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

### 마지막 프로젝트인 5X5 행렬 곱 연산, 성능개선

### 새로운 명령어를 만들고 그 명령어에 대한 적절한 소요클럭설정과 적절한 이유가 목표였는데

### 이해를 못해서 그냥 있는 명령어들만 사용했다

### 모든 행렬은 메모리에 저장되어 있어야하고

### JZ 명령어를 이용해 Loop 형태로 프로그램을 작성하여야함


### 수행해야할 행렬 연산
![architecture](https://postfiles.pstatic.net/MjAyMDExMDZfMjY5/MDAxNjA0NjY5NDQ0Mjg5.TInTcn8X4_YD_vmeGKVh245UBpiKUCvZARw7SUcAVe4g.7tCJEJwK8hJY549-BSNZCtAmUSHmf21vfrvAhs0rQZEg.PNG.qotjdrb6/image.png?type=w773)



### MOV3로 A행렬의 1행 B행렬의1열 입력 후 
### JZ를 구현하기위해 R14,R15에 0,1값을 입력하고 
### MOV4로 JZ를 구현할 R10~13의 값 을 0으로 바꾸어 준다
### 그 후에 메모리에 각 행렬 원소들의 백업을 해주고
### JZ명령어로 연산과정으로 점프하게 된다
![architecture](https://postfiles.pstatic.net/MjAyMDExMDZfMTUy/MDAxNjA0NjY5NTMzMzg4.pjpRKvQ5uACP2oJJFmDoxZDFsNGIcDG2s5WHPV_Kn8Eg.3Vvgom2GSStHiuoguvaLHunwbmrZkEV2O1VgeXvHfBIg.PNG.qotjdrb6/image.png?type=w773)



### MUL,ADD연산을 사용하여 C0항이 R5에 저장되었고 
### JZ명령어를 이용하기위해서 SUB명령어를 사용하여, JZ명령어 조건을 만족하게 만들고 있는 모습이다
### JZ명령어가 작동하게 되면 연산 된 C0항이 메모리에 저장되고 
### 다음 C1항 연산을 위한 준비를 하는 라인으로 점프하게 된다


![architecture](https://postfiles.pstatic.net/MjAyMDExMDZfOTQg/MDAxNjA0NjY5NTQ1MzA4.pJ6bqTqKrXWi5BOGXd4W0l9y1A7q2BQsGUDzWSwJeDwg.5zc7LUIltoV8FlRdgXK6D5yJpz2Tjyvm7TIHwNqCz3Ug.PNG.qotjdrb6/image.png?type=w773)


### 이후 C1~C4까지 연산 후 저장하는 과정이다.
### 이미 한번 작동한 JZ를 명령어를 작동시키지 않아야 
### 다음 JZ명령어가 작동하여 정상적인 연산을 하기에 
### MOV4를 이용하여 R15값인 1로 바꾸어 주고 연산 완료된 𝐶_𝑥 값을 메모리에 저장 후 
### 다음 𝐶_(𝑥+1) 값을 만들기 위하여 MOV3로 값을 입력, MOV1로 백업, JZ로 연산라인까지 반복하게 된다.

![architecture](https://postfiles.pstatic.net/MjAyMDExMDZfMTY5/MDAxNjA0NjY5NTUyNTMw.NpEZlNSlCVLsGOPV1Jivw0NbC0QJTucYELeXrpjPdrMg.fSeSwJQLYTGeqkQzPQ73FkGrYQy828t08FHGCX8ifpUg.PNG.qotjdrb6/image.png?type=w773)

The HW3Upgrade.bin 파일은 5X5 행렬 곱 연산을 tPU로 수행하기 위한 binary code 이다.
