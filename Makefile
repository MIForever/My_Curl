CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
SOURCES = main.c src/*.c
TARGET = my_curl

$(TARGET):$(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: fclean

fclean:
	@rm -r $(TARGET)