#pragma once
#define Assert(...) ;

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "operators.hpp"

namespace Token {
	enum type_t {
		NUM,
		ID,
		OP,
		SPEC,
	};
	
	struct token_t {
		const char* lexem;
		type_t token_type;	
		Operator::op_codes op_code;
	};

};

const int MAX_BUFF_SIZE = 4096;
