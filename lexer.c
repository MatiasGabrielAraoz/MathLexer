#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>


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

typedef struct{
	TokenType type;
	int value;
}Token;

typedef struct {
	const char* src;
	Token* tokens;
	size_t tokensAmount;
	size_t srcLen;
	size_t cursor;
	char currentChar;
}Lexer;

bool InitLexer(Lexer* lexer, char* text){
	if (lexer == NULL || text == NULL) return false;
	lexer->src = text;
	lexer->srcLen = 0;
	lexer->cursor = 0;
	do{
		lexer->currentChar = lexer->src[lexer->cursor];
		lexer->cursor++;
		lexer->srcLen++;
	}while (lexer->currentChar != '\0');

	lexer->cursor = 0;
	lexer->currentChar = lexer->src[lexer->cursor];

	return true;

}

char GetCurrentChar(Lexer* lexer){
	lexer->currentChar = lexer->src[lexer->cursor];
	return lexer->currentChar;
}

bool LexerPrev(Lexer* lexer){
	if (lexer->cursor <= 0) return false;

	lexer->cursor--;
	lexer->currentChar = GetCurrentChar(lexer);
	return true;

}

bool LexerNext(Lexer* lexer){
	if (lexer->currentChar == '\0') return false;

	lexer->cursor++;
	lexer->currentChar = GetCurrentChar(lexer);

	return true;
}

size_t GetTokensAmount(Lexer* lexer){
	size_t tokensAmount = 0;

	while (lexer->currentChar != '\0'){
		switch (lexer->currentChar){
			case '+':
				tokensAmount++;
				LexerNext(lexer);
				break;
			case '-':
				tokensAmount++;
				LexerNext(lexer);
				break;
			case '0' ... '9':
				tokensAmount++;
				while (lexer->currentChar >= '0' && lexer->currentChar <= '9'){
					LexerNext(lexer);
				}
				break;
			default:
				LexerNext(lexer);
				break;
		}
	}

	tokensAmount++;

	lexer->cursor = 0;
	lexer->currentChar = GetCurrentChar(lexer);
	return tokensAmount;
}

Token* Tokenize(Lexer* lexer){
	lexer->tokensAmount = GetTokensAmount(lexer);
	Token* tokens = (Token*)calloc(lexer->tokensAmount, sizeof(Token));

	lexer->cursor = 0;
	size_t i = 0;
	while (i < lexer->tokensAmount){
		switch (lexer->currentChar){
			case ' ':
				LexerNext(lexer);
				break;
			case '+':
				tokens[i].type = TOKEN_PLUS;
				LexerNext(lexer);
				i++;
				break;
			case '-':
				tokens[i].type = TOKEN_MINUS;
				LexerNext(lexer);
				i++;
				break;
			case '0' ... '9':
				tokens[i].type = TOKEN_NUMBER;
				tokens[i].value = 0;
				size_t numLen = 1;
				while (lexer->currentChar >= '0' && lexer->currentChar <= '9'){
					tokens[i].value = (tokens[i].value * 10) + (lexer->currentChar - '0') ;
					numLen++;
					LexerNext(lexer);
				}

				i++;
				break;


			case '\0':
				tokens[i].type = TOKEN_EOF;
				i++;
				break;
			default:
				i++;
				break;

		}
	}
	return tokens;
}

void PrintTokens(Lexer* lexer){
	for (size_t i = 0; i < lexer->tokensAmount; i++){
		switch (lexer->tokens[i].type) {
			case TOKEN_NUMBER:
				printf("NUMBER: %d\n", lexer->tokens[i].value);
				break;
			case TOKEN_PLUS:
				printf("+\n");
				break;
			case TOKEN_MINUS:
				printf("-\n");
				break;
			case TOKEN_MULTIPLY:
				printf("x\n");
				break;
			case TOKEN_DIVIDE:
				printf("/\n");
				break;
			default:
				break;
		
		}
	}
}


int main(int argc, char* argv[]){
	char* texto = "1+1";
	if (argc < 2){
		fprintf(stderr, "No se indicó ningun texto para tokenizar, uso: %s \"texto\" \n", argv[0]);
		return -1;
	}
	texto = argv[1];

	Lexer lexer;
	InitLexer(&lexer, texto);
	lexer.tokens = Tokenize(&lexer);
	PrintTokens(&lexer);


	free(lexer.tokens);
}
