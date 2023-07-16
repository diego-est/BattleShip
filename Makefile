
.POSIX:

SRC = ./src/main.cpp ./src/functions.cpp ./src/classes.cpp
CC = clang++
CPPFLAGS = -Wall -Wextra -pedantic -lncursesw
DEBUG = ./build/debug
RELEASE = ./build/release

all: options build

options:
	@echo game build options:
	@echo "CC	= $(CC)"
	@echo "CPPFLAGS	= $(CPPFLAGS)"

run: build
	$(DEBUG)

build: format
	$(CC) $(CPPFLAGS) -Og $(SRC) -o $(DEBUG)

release: format
	$(CC) $(CPPFLAGS) -O2 $(SRC) -o $(RELEASE)

format:
	clang-format -i $(SRC)

