default: build run

build:
	mcs -debug -r:System.Data.dll -out:validator.exe src/*.cs

run:
	mono validator.exe
