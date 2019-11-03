# Intro
All of this contents is Lecture of School of Electronic Engineering, Kyungpook National University 
# MicroProcessor

The every smart systems and internet connection of things (IoT) are based on microcontrollers/microprocessors, which are powered by specially-designed firmware and dedicated hardware. In this lecture, I studied MCU-based approach to program everything around us.  

* learn both hardware and software aspects of integrating digital devices (such as memory and I/O interfaces) into microprocessor-based systems.

* get practical experience in applied digital logic design and 8051, ARM (cortex-m) assembly-language programming.
# Overall Architecture
![architecture](https://postfiles.pstatic.net/MjAxOTExMDNfMTY1/MDAxNTcyNzY3ODMzNzc0.5Mz3m21dOhMzQAdHE9PVigBKasavHoi3RNSF9SAptXQg.xi4BIU14P3cpNUg2DvfNizFGUybfiY8bCILdPJontwEg.PNG.qotjdrb6/%EC%BA%A1%EC%B2%98.PNG?type=w773)

![architcture](https://postfiles.pstatic.net/MjAxOTExMDNfMjYx/MDAxNTcyNzY3ODMzODI1.DHLghTodL_Pwb5m13iPBA7wZPFCeNH7sPwIrwyZwspsg.gI83x70YjfD-oUnVLMBAco81O6K5N3fgFiGp8bTb23wg.PNG.qotjdrb6/%EC%BA%A1%EC%B2%981.PNG?type=w773)



# tPU Instruction Set Architecture
Example Structure
- Name(Opcode Operand1 Operand2)

   -description  


Real Structure

* MOV0 (0000 R(n) direct)

  -R(n) <- Mem(direct)
 
  -PC <- PC + 1
 
* MOV1 (0001 R(n) direct)

  -Mem(direct) <- R(n)
 
  -PC <- PC + 1
 
 * MOV2 (0010 R(n) 0000R(m))
 
  -Mem(R(n)) <- R(m)
 
  -PC <- PC + 1
 
 * MOV3 (0011 Rn #immed)
 
    -R(n) <- #immed
 
    -PC <- PC + 1
 
 * ADD (0100 Rn Rm0000)
 
    -R(n) <- Mem(direct)
 
    -PC <- PC + 1
 
 * SUB (0101 R(n) R(m)0000)
 
    -R(n) <- R(n)-{R(m) >> 4}
 
    -PC <- PC + 1
 
 * JZ (0110 R(n) (signed)relative)
 
    -If R(n) == 0
 
    -PC <- PC + 1 + relative
 
 * MUL (0111 R(n) R(m)0000)
 
    -R(n) <- R(n)*R(m)
 
    -PC <- PC + 1
 
 * MOV4 (1000 R(n) R(m)0000)
 
    -R(n) <- R(m)
 
    -PC <- PC + 1
 
 * MOV5 (1001 R(n) 0000R(m))
 
    -R(n) <- Mem{R(m)}
 
    -PC <- PC + 1
