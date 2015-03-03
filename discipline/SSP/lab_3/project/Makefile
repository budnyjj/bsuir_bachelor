default: build run

build:
	mcs -debug -pkg:glade-sharp-2.0 -resource:resources/ui.glade -r:System.Data.dll -r:Mono.Data.Sqlite.dll -out:bin/books.exe src/*.cs

run:
	mono bin/books.exe
