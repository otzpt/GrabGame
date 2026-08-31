CC = gcc
CFLAGS = -Wall -Wextra
LDLIBS = -lncurses
TARGET = grabgame

all: $(TARGET)

$(TARGET): GrabGame.c
	$(CC) $(CFLAGS) GrabGame.c -o $(TARGET) $(LDLIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all run clean
