BIN_ARITHM=arithmetic.exe
BIN_PLUS=arithmetic.exe

default: build-arithmetic build-plus

build-plus:
	mcs -out:$(BIN_PLUS) src/Plus.cs
	./$(BIN_PLUS) 1
	./$(BIN_PLUS) 0.1
	./$(BIN_PLUS) 0,1
	./$(BIN_PLUS) +0.1
	./$(BIN_PLUS) +0,1


build-arithmetic:
	mcs -r:mcs.exe -r:System.Data.dll -out:$(BIN_ARITHM) src/Arithmetic.cs
	./$(BIN_ARITHM) +
	./$(BIN_ARITHM) -2
	./$(BIN_ARITHM) -22	
	./$(BIN_ARITHM) 2+2
	./$(BIN_ARITHM) -2+22
	./$(BIN_ARITHM) -22
	./$(BIN_ARITHM) -22+12-32*12/12
	./$(BIN_ARITHM) -22+12-32*12/12+
	./$(BIN_ARITHM) 22+12-32*12/12+
