/**
 * This module tokenizes input.  It is responsible for reading from stdin, 
 * discarding comments, discarding comments, and returning one string at
 * time (super simple).
 */

#define 		TOKEN_TYPE_LABEL		1
#define			TOKEN_TYPE_NUM			2

typedef struct Token {
	int type;
	char *st;
	int val;
} Token;

/**
 * GetToken grabs a single word from stdin and puts a pointer to it in |token|.
 * It returns 0 normally, 1 in case of error (idk what kind of errors
 * there'd be), and -1 in case of EOF.
 */
int GetToken(Token *token);
