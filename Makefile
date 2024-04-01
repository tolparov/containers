LIBS_LINUX=
ADD_LIB=
LIBNAME=
CMD_OPEN= open


UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Linux)

	ADD_LIB=-l:s21_containers.a
	LIBNAME= s21_containers.a
	CMD_OPEN = xdg-open

	Linux_type := $(shell cat /etc/issue | sed -n '1p' | awk '{print $$1}')

	ifeq ($(Linux_type), Arch)
		LIBS_LINUX =
	endif

	ifeq ($(Linux_type), Ubuntu)
		LIBS_LINUX =  -pthread 
	endif

	ifeq ($(Linux_type), Debian)
		LIBS_LINUX = -pthread 
	endif

endif

ifeq ($(UNAME_S), Darwin)
    ADD_LIB= -ls21_containers
	LIBNAME= libs21_containers.a
endif


CC=g++
CFLAGS=-Wall -Werror -Wextra -g -std=c++17 $(LIBS_LINUX)
OBJS=s21*.o
SRCS_OBJ=s21*.tpp
TESTS_OBJ=*.cpp

TARGET=s21_containers
TEST_TARG=test_s21_containers

SRCS_DIR=libs
TESTS_DIR=tests

SRCS_H =s21*.h

LIBS =-lgtest

ALL_SRC_OBJ = $(shell find $(SRCS_DIR) -type f -name "$(SRCS_OBJ)")
ALL_TESTS_OBJ = $(shell find $(TESTS_DIR) -type f -name "$(TESTS_OBJ)")

ALL_SRC_H = $(shell find $(SRCS_DIR) -type f -name "$(SRCS_H)")
ALL_TESTS_H = $(shell find $(TESTS_DIR) -type f -name "*.h")

all: test gcov_report

test: 
	$(CC) $(CFLAGS) $(ALL_TESTS_OBJ) $(LIBS) -o $(TEST_TARG) 
	./$(TEST_TARG)

test_val: test
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes -s ./$(TEST_TARG)

gcov_report: 
	$(CC) --coverage $(ALL_SRC_OBJ) $(ALL_TESTS_OBJ) $(LIBS) -o $(TEST_TARG)
	./$(TEST_TARG)
	lcov -t "$(TEST_TARG)" -o $(TEST_TARG).info -c -d .
	lcov --remove $(TEST_TARG).info '/usr*' -o $(TEST_TARG).info
	genhtml -o report $(TEST_TARG).info
	rm -f *.gcda *.gcno *.info $(TEST_TARG)
	cd report && $(CMD_OPEN) index.html

check_linters:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -n $(ALL_SRC_OBJ) $(ALL_SRC_H) $(ALL_TESTS_OBJ) $(ALL_TESTS_H)
	rm -rf .clang-format

fix_linters:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -i $(ALL_SRC_OBJ) $(ALL_SRC_H) $(ALL_TESTS_OBJ) $(ALL_TESTS_H)
	rm -rf .clang-format

clean_lib:
	rm -f *.[oa]

clean_cov:
	rm -f *.gcno *.gcda *.info *.gcov $(TEST_TARG)

clean: clean_lib clean_cov
	rm -f $(TEST_TARG)
	rm -rf report *.dSYM

rebuild: clean all
