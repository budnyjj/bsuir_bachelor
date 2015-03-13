CLIENT_SRCS=src/client/MsgClientApp.cs src/client/MsgClient.cs src/service/IMsgService.cs src/common/Message.cs
SERVER_SRCS=src/server/MsgServer.cs src/server/MsgDB.cs src/common/Message.cs src/service/IMsgService.cs
TEST_SRCS=tests/MsgDBTest.cs src/server/MsgDB.cs src/common/Message.cs

default: build-all

build-client:
	mcs -debug -pkg:wcf -pkg:glade-sharp-2.0 -resource:resources/ui.glade -out:bin/client.exe ${CLIENT_SRCS}

run-client: build-client
	mono bin/client.exe

build-server:
	mcs -pkg:wcf -r:System.Data.dll -r:Mono.Data.Sqlite.dll -out:bin/server.exe ${SERVER_SRCS}

run-server: build-server
	mono bin/server.exe 

build-test:
	mcs -t:library -pkg:wcf -r:nunit.framework.dll -r:System.Data.dll -r:Mono.Data.Sqlite.dll -out:tests/dll/MsgDBTest.dll ${TEST_SRCS}

run-test: build-test
	nunit-console4 tests/dll/MsgDBTest.dll

build-all: build-client build-server

run-all: run-client run-server
