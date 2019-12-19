#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define Assert(cond) assert(cond)


enum type_t {
	VOID = -1,
	CMD,
	LAB,
	REG,
	NUM,
};

struct token {
	type_t type = VOID;
	int val = 0;
};

int num_cmds = 0;

namespace commands {
int num = 20;
enum cmd_t {
	VOID = -1,
	PUSH,
	POP,
	ADD,
	SUB,
	MULT,
	DIV,
	SQRT,
	JMP,
	JE,
	JNE,
	JA,
	JB,
	JAE,
	JBE,
	LAB,
	PUSHRM,
	POPRM,
	IN,
	OUT,
};

const char* names [] = {
	"PUSH",
	"POP",
	"ADD",
	"SUB",
	"MULT",
	"DIV",
	"SQRT",
	"JMP",
	"JE",
	"JNE",
	"JA",
	"JB",
	"JAE",
	"JBE",
	"LABL",
	"PUSHRM",
	"POPRM",
	"IN",
	"OUT",
};
}

int regs [256] = {};

const char** lables = (const char**)calloc(4096, sizeof(char*));
int num_lables = 0;

int ram [1024] = {};
