
.POSIX:

SRC = ./src/main.cpp
CC = clang++
CPPFLAGS = -Wall -Wextra -pedantic
DEBUG = ./build/debug/a.out
RELEASE = ./build/release/game

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

