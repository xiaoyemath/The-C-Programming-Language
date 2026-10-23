CC = gcc
CFLAGS = -Wall -Wextra
LDLIBS = -lm
TARGET = rpn
SRCS = $(wildcard *.c)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ '1_getop.c' '2_(un)getch.c' '3_getop(line).c' '4_stack.c' 'rpnmain.c' $(LDLIBS)

clean:
	rm -f $(TARGET)

.PHONY: clean
