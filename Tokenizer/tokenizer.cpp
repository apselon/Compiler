#pragma once
#include "tokenizer.hpp"

void skip_spaces(const char** text){
	
	Assert(text != NULL);
	
	while (isspace(**text)){
		++(*text);
	}
}


const char** splited_text(const char* text, int* size = NULL){
	
	Assert(text != NULL);

	const char** splited = new const char* [MAX_BUFF_SIZE];
	int offset = 0;
	int len = 0;

	skip_spaces(&text);

	while(*text){
		skip_spaces(&text);
		if (!*text) break;

		sscanf(text, "%ms%n", splited, &offset);
		printf("new token: (%s) \n", *splited);
		splited += 1;
		text += offset;
		len += 1;
	}

	if (size != NULL) *size = len;

	return splited - len;
}

Operator::op_codes get_opcode(const char* lexem){

	Assert(lexem != NULL);

	for (int i = 0; i < Operator::NUM_OPS; ++i){
		if (strcmp(lexem, Operator::op_names[i]) == 0){
			return (Operator::op_codes)i;
		}
	}

	for (int i = 0; i < Operator::NUM_BRACKS; ++i){
		if (strcmp(lexem, Operator::o_brack_names[i]) == 0){
			return Operator::O_BRACK;
		}

		if (strcmp(lexem, Operator::c_brack_names[i]) == 0){
			return Operator::C_BRACK;
		}
	}

	return Operator::NOT_OP;
}

Token::token_t generate_token(const char* lexem){

	Assert(lexem != nullptr);

	Token::token_t token = {};
	token.lexem = lexem;

	Operator::op_codes code = get_opcode(lexem);


	printf("%d ", code);
	if (code >= 0) printf("%s\n", Operator::op_code_strs[code]);
	else token.lexem = "";

	if (code != Operator::NOT_OP){
		token.token_type = Token::OP;
		token.op_code = code;

		return token;
	}

	if (isdigit(*lexem)){
		token.op_code = Operator::NOT_OP;
		token.token_type = Token::NUM;
		token.lexem = lexem;

		return token;
	}

	token.token_type = Token::ID;
	token.op_code = Operator::NOT_OP;
	token.lexem = lexem;

	return token;
}

int tokenize(Token::token_t* t_buff, const char* text){
	
	Assert(t_buff != NULL);
	Assert(text != NULL);

	int size = 0;
	const char** splited = splited_text(text, &size);

	printf("size: %d\n", size);
	for (int i = 0; i < size; ++i){
		t_buff[i] = generate_token(splited[i]);
	}
		
//	delete [] splited;
	
	return 0;
}
