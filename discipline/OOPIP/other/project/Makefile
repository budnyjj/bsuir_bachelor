SRC_DIR = src
BIN_DIR = bin

TEST_SRC_DIR = tests
TEST_BIN_DIR = tests/bin

COMPILER = g++
COMPILE_OPTS = -g
TEST_LIBS = -lboost_unit_test_framework
BOOST_TEST_OPTS = --log_level=test_suite --report_level=short

default: main main_run

tests_compile:
	${COMPILER} ${COMPILE_OPTS} -o ${TEST_BIN_DIR}/node_test.o ${TEST_LIBS} ${TEST_SRC_DIR}/node_test.cpp
	${COMPILER} ${COMPILE_OPTS} -o ${TEST_BIN_DIR}/tree_test.o ${TEST_LIBS} ${TEST_SRC_DIR}/tree_test.cpp

tests_run:
	${TEST_BIN_DIR}/node_test.o ${BOOST_OPTS}
	${TEST_BIN_DIR}/tree_test.o ${BOOST_OPTS}

test: tests_compile tests_run

main:
	${COMPILER} ${COMPILE_OPTS} -o ${BIN_DIR}/main.o  ${SRC_DIR}/main.cpp

main_run:
	${BIN_DIR}/main.o
