all:
	g++ -o tpu CCode.cpp CDecode.cpp CRegister.cpp CExecute.cpp CMemory.cpp  main.cpp
	./tpu HW3.bin 410
	./tpu HW3Upgrade.bin 352
