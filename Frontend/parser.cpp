#include "../Tokenizer/tokenizer.cpp"
#include "../Tree/Tree.cpp"
#include "../Tokenizer/operators.hpp"
#include "parser.hpp"
#include "DSL.hpp"

namespace Parser {
Token::token_t* cur = {};

Tree::node_t* get_N();
Tree::node_t* get_ID();
Tree::node_t* get_P();
Tree::node_t* get_T();
Tree::node_t* get_E();
Tree::node_t* get_WHILE();
Tree::node_t* get_IF();
Tree::node_t* get_BLCK();
Tree::node_t* get_OP();
Tree::node_t* get_SET_VAR();
Tree::node_t* get_CALL();
Tree::node_t* get_PRINT();

Tree::node_t* get_N(){

	Assert(cur->token_type == Token::NUM);

	Token::token_t* val = cur;
	++cur;

	return NODE(val, NULL, NULL);
}

Tree::node_t* get_ID(){
	
	Assert(cur->token_type == Token::ID);

	Token::token_t* val = cur;
	++cur;

	return NODE(val, NULL, NULL);
}

Tree::node_t* get_P(){

	Tree::node_t* val = {};

	if (cur->op_code == Operator::O_BRACK){
		++cur;
		val = get_E();
		Assert(cur++->op_code == Operator::C_BRACK);

		return val;
	}

	if (cur->token_type == Token::ID){
		return get_ID();
	}
	
	return get_N();
}

Tree::node_t* get_T(){
	
	Tree::node_t* val = get_P();
	Tree::node_t* val2 = {};
	Token::token_t* sgn = {};
	
	while (cur->op_code == Operator::MUL || cur->op_code == Operator::DIV){
		sgn = cur++;
		val2 = get_P();
		val = NODE(sgn, val, val2);
	}

	return val;
}

Tree::node_t* get_E(){

	Tree::node_t* val = get_T();
	Token::token_t* sgn = cur;
	Tree::node_t* val2 = {};

	while (cur->op_code == Operator::ADD || cur->op_code == Operator::SUB 
	    || cur->op_code == Operator::EQL || cur->op_code == Operator::LESS
		|| cur->op_code == Operator::MORE || cur->op_code == Operator::EQLESS
		|| cur->op_code == Operator::EQMORE){
		sgn = cur;
		++cur;
		val2 = get_T();
		val = NODE(sgn, val, val2);
	}

	return val;
}

Tree::node_t* get_BLCK(){
	printf("BLOCK started\n");
	
	printf("%s, %d\n", cur->lexem, cur->op_code);
	Assert(cur++->op_code == Operator::O_BRACK);

	Tree::node_t* block = Tree::create_node(Operator::BLOCK, Token::SPEC, "B", NULL, NULL);
	Tree::node_t* new_block = {};
	Tree::node_t* val = block;


	while (cur->op_code != Operator::C_BRACK){
		printf("{%s, %d, %d}\n", cur->lexem, cur->op_code, cur->token_type);
		Tree::attach_right(NULL, block, get_OP());
		new_block = Tree::create_node(Operator::BLOCK, Token::SPEC, "B", NULL, NULL);
		Tree::attach_left(NULL, block, new_block);

		block = new_block;

	}
	++cur;
	printf("BLOCK finished\n");
	return val;
}


Tree::node_t* get_WHILE(){

	Assert(cur++->op_code == Operator::WHILE);

	Tree::node_t* cond_left = get_E();
	Tree::node_t* cond = get_OP();
	Tree::node_t* cond_right = get_E();

	Tree::attach_left(NULL, cond, cond_left);
	Tree::attach_right(NULL, cond, cond_right);

	Tree::node_t* body = get_BLCK();

	return Tree::create_node(Operator::WHILE, Token::OP, "WHILE", cond, body);
}


Tree::node_t* get_COMMA(){
	Assert(cur++->op_code == Operator::COMMA);
}

Tree::node_t* get_VARLIST(){

	Assert(cur++->op_code == Operator::O_BRACK);

	Tree::node_t* comma = Tree::create_node(Operator::COMMA, Token::OP, ",", NULL, NULL);	
	Tree::node_t* new_comma = {};	
	Tree::node_t* val = comma;


	while (cur->op_code != Operator::C_BRACK){
		Tree::attach_right(NULL, comma, get_E());
		new_comma = Tree::create_node(Operator::COMMA, Token::OP, ",", NULL, NULL);
		Tree::attach_left(NULL, comma, new_comma);

		comma = new_comma;
	}

	++cur;

	return val;
}


Tree::node_t* get_IF(){
	
	Assert(cur++->op_code == Operator::IF);

	Tree::node_t* cond = get_E();
	
	printf("171: %s \n", cur->lexem);

	Tree::node_t* body = get_BLCK();
	Tree::node_t* els  = get_BLCK();

	Tree::node_t* link = Tree::create_node(Operator::CONNECT, Token::SPEC, "C", els, body);

	return Tree::create_node(Operator::IF, Token::OP, "IF", cond, link);
}

Tree::node_t* get_DEC_VAR(){

	printf("DEC_VAR:\t");

	Assert(cur++->op_code == Operator::DEC_VAR);

	Tree::node_t* var = get_ID();
	printf("%s\n", var->data.lexem);
	
	/*
	if (cur->op_code == Operator::ASSGN){
		Tree::node_t* val = get_SET_VAR();

		return Tree::create_node(Operator::DEC_VAR, Token::OP, "DEC_VAR", val, var);
	}
	*/

	return Tree::create_node(Operator::DEC_VAR, Token::SPEC, "DEC_VAR", NULL, var);
}

Tree::node_t* get_SET_VAR(){

	Assert(cur++->op_code == Operator::ASSGN);

	Tree::node_t* var = get_ID();
	Tree::node_t* val = {}; 

	if (cur->op_code == Operator::CALL){
		val = get_CALL();
	} else {
		val = get_E();
	}

	return Tree::create_node(Operator::ASSGN, Token::SPEC, "=", var, val);

}

Tree::node_t* get_DEC_FUNC(){

	Assert(cur++->op_code == Operator::DEC_FUNC);

	Tree::node_t* name = get_ID();
	Tree::node_t* args = get_VARLIST();
	Tree::node_t* body = get_BLCK();
	

	Tree::attach_right(NULL, name, body);

	return Tree::create_node(Operator::DEC_FUNC, Token::SPEC, "DEF", args, name);

}

Tree::node_t* get_CALL(){
	
	Assert(cur++->op_code == Operator::CALL);

	Tree::node_t* name = get_ID();
	Tree::node_t* args = get_VARLIST();

	return Tree::create_node(Operator::CALL, Token::OP, "CALL", args, name);
}

Tree::node_t* get_RETURN(){

	Assert(cur++->op_code == Operator::RETURN);
	
	Tree::node_t* val = get_E();

	return Tree::create_node(Operator::RETURN, Token::OP, "RET", NULL, val);
}

Tree::node_t* get_PRINT(){
	
	Assert(cur++->op_code == Operator::WRITE);

	Tree::node_t* val = get_E();

	return Tree::create_node(Operator::WRITE, Token::OP, "OUT", NULL, val);

}

Tree::node_t* get_SQRT(){
	
	Assert(cur++->op_code == Operator::SQRT);

	Tree::node_t* val = get_E();

	return Tree::create_node(Operator::SQRT, Token::OP, "SQRT", NULL, val);
}

Tree::node_t* get_EXIT(){
	
	Assert(cur++->op_code == Operator::EXIT);

	return Tree::create_node(Operator::EXIT, Token::OP, "EXIT", NULL, NULL);
}

Tree::node_t* get_OP(){

	Tree::node_t* val = {};

	switch (cur->op_code){
		case Operator::IF:
			val = get_IF();
			break;
		case Operator::WHILE:
			val = get_WHILE();
			break;
		case Operator::DEC_VAR:
			val = get_DEC_VAR();
			break;
		case Operator::DEC_FUNC:
			val = get_DEC_FUNC();
			break;
		case Operator::ASSGN:
			val = get_SET_VAR();
			break;
		case Operator::CALL:
			val = get_CALL();
			break;
		case Operator::RETURN:
			val = get_RETURN();
			break;
		case Operator::WRITE:
			val = get_PRINT();
			break;
		case Operator::SQRT:
			val = get_SQRT();
			break;
		case Operator::EXIT:
			val = get_EXIT();
		default:
			printf("OP %d (%s) can not be parsed\n", cur->op_code, Operator::op_code_strs[cur->op_code]);
			break;
	}

	return val;
}
}
