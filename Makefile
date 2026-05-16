CC = clang
CFLAGS = -fsanitize=address -Wall -Wextra -g
SRC = lexer.c
TARGET = lexer

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
	@echo "Compilado correctamente"

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)


.PHONY: all clean run

