CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11 -pedantic -fsanitize=address
CHECK_FLAGS=$(shell pkg-config --cflags --libs check)
SOURCES=s21_cat.c ../common/get_size_file.c
OBJECTS=$(SOURCES:.c=.o)
GOAL=s21_cat

all:s21_grep

s21_cat: $(OBJECTS)
	 $(CC) $(CHECK_FLAGS) $(CFLAGS) $(OBJECTS) -o $@

%.o: %.c	 s21_cat.h Makefile
	gcc $(CFLAGS) -c $< -o $@
clean:
	rm -rf ../common/*.o ./*.o s21_cat