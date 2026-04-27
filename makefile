CC = gcc
CFLAGS = -Wall -Wextra -g 
TARGET = shell

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

$(TARGET): shell.c main.c
	$(CC) $(CFLAGS) shell.c main.c -o $(TARGET)

clean:
	rm -f $(TARGET)

leak: $(TARGET)
	valgrind --leak-check=full --track-origins=yes ./$(TARGET)

