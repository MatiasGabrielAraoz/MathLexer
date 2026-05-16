# MathLexer

A simple and efficient lexical analyzer (Lexer) written in pure C. This project takes an input string (such as a mathematical expression) and converts it into a stream of grouped and validated `Token` structures in memory.

The project is designed following modern C development standards, being fully **Type-Safe** (utilizing `size_t` for memory management) and **Memory-Safe** (thoroughly validated using AddressSanitizer).

## Features

- **Digit Grouping:** Capable of recognizing multi-digit numbers (e.g., `"15"`) as a single base-10 numeric token.
- **Exact Memory Management:** Implements a two-pass system (`GetTokensAmount` and `Tokenize`) to dynamically allocate via `calloc` the exact number of bytes required on the Heap.
- **Error Detection:** Resilient against unknown characters and whitespace.

## Token Structure

Each detected component is stored in the following structure:
```c
typedef enum{
	TOKEN_NUMBER,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_DIVIDE,
	TOKEN_MULTIPLY,
	TOKEN_PARENTESIS_O,
	TOKEN_PARENTESIS_C,
	TOKEN_EOF
}TokenType;

typedef struct {
    TokenType type;
    int value; // Stores the integer value if the type is TOKEN_NUMBER
} Token;
```

## Things to have in mind
The project is still in development and only works with ADDITION, SUBTRACTION, DIVISION, MULTIPLICATION, and NUMBERS.
Also, I will make it so it can evaluate the mathematical expression and return an answer
