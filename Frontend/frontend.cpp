#include "parser.cpp"

Tree::tree_t* generated_AST(const char* text){

	Assert(text != NULL);
	
	Token::token_t* tok_buff = new Token::token_t [MAX_BUFF_SIZE];
	int tok_flag = tokenize(tok_buff, text);

	Parser::cur = tok_buff;
	
	Tree::tree_t* AST = new Tree::tree_t;
	Token::token_t start = {"START", Token::SPEC, Operator::BLOCK};

	Tree::construct(AST, start);
	Tree::attach_right(AST, AST->root, Parser::get_BLCK());

	AST->size += 1000;

	return AST;
 }

int count_chars(FILE* file){

	Assert(file != NULL);

	int num_chars = 0;

	fseek(file, 0L, SEEK_END);
	num_chars = ftell(file);
	rewind(file);

	return num_chars;
}


char* read_text(FILE* file, long int num_chars){

	Assert(file != NULL);
	Assert(num_chars > 0);

	char* whole_text = ( char* )calloc(num_chars + 1, sizeof(char));

	fread(whole_text, sizeof(char), num_chars + 1, file);

	return whole_text;
}

