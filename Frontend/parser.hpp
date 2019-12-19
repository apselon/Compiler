#pragma once

#define NUMBER(i) Tree::create_node(0, Token::NUM, 0, i, dtoa(i), NULL, NULL)

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "../Tokenizer/tokenizer.cpp"
#include "../Tree/Tree.cpp"


const char* dtoa(double d){
	char* buff = new char [64];
	sprintf(buff, "%lg", d);

	return buff;
}

