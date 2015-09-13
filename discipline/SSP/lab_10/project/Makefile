BIN_ARITHM=arithmetic.exe

default: build-arithmetic

build-plus:
	mcs -out:plus.exe src/Plus.cs

build-arithmetic:
	mcs -out:$(BIN_ARITHM) src/Arithmetic.cs
	./$(BIN_ARITHM) +
	./$(BIN_ARITHM) -2
	./$(BIN_ARITHM) -22	
	./$(BIN_ARITHM) 2+2
	./$(BIN_ARITHM) -2+22
	./$(BIN_ARITHM) -22
	./$(BIN_ARITHM) -22+12-32*12/12
	./$(BIN_ARITHM) -22+12-32*12/12+
	./$(BIN_ARITHM) 22+12-32*12/12+
