#pragma once

#include "translator.hpp"

void gen_DEF_FUNC(Tree::node_t*);
void gen_E(Tree::node_t*);
void gen_RET(Tree::node_t*);
void gen_OP(Tree::node_t*);
void gen_BODY(Tree::node_t*);
void gen_SET_VAR(Tree::node_t*);
void gen_CALL(Tree::node_t*);

void gen_DEF_FUNC(Tree::node_t* cur){

	printf("LINE %d\n", __LINE__);
	Assert(cur != NULL);
	Assert(cur->data.op_code == Operator::DEC_FUNC);

	var_list_t* locals = new var_list_t;	

	Tree::node_t* comma = cur->left;
	
	while (comma->right){
		add_arg(locals, comma->right->data.lexem);
		comma = comma->left;
	}
	locals->shift = locals->num_args;

	trans_glob::locals = locals;
	
	cur = cur->right;
	fprintf(output, "func_%s: \n", cur->data.lexem);
	cur = cur->right;

	for (int i = 0; i < trans_glob::locals->shift; ++i){
		fprintf(output, "popm [ax + %d] \n", i);
	}

	gen_BODY(cur);


	printf("LINE %d\n", __LINE__);
}


void gen_BODY(Tree::node_t* cur){

	printf("LINE %d\n", __LINE__);
	Assert(cur != NULL);
	
	while (cur->right){
		gen_OP(cur->right);

		cur = cur->left;
	}
	printf("LINE %d\n", __LINE__);
}

void gen_DEC_VAR(Tree::node_t* cur){

	printf("LINE %d\n", __LINE__);
	Assert(cur != NULL);
	Assert(cur->data.op_code == Operator::DEC_VAR);

	add_var(trans_glob::locals, cur->right->data.lexem);

	printf("LINE %d\n", __LINE__);
}

void gen_RET(Tree::node_t* cur){
	
	printf("LINE %d\n", __LINE__);
	Assert(cur != NULL);
	Assert(cur->data.op_code == Operator::RETURN);

	gen_E(cur->right);

	fprintf(output, "push %d \n", trans_glob::locals->shift);
	fprintf(output, "pushr ax \n");
	fprintf(output, "sub \n");
	fprintf(output, "popr ax \n"); 
	fprintf(output, "ret \n");

	printf("LINE %d\n", __LINE__);
}

void gen_E(Tree::node_t* cur){
	
	printf("LINE %d\n", __LINE__);
	Assert(cur != NULL);

	if (cur->right) gen_E(cur->right);
	if (cur->left) gen_E(cur->left);

	if (cur->data.token_type == Token::NUM){
	printf("LINE %d\n", __LINE__);
		fprintf(output, "push %s \n", cur->data.lexem);
		return;
	}

	if(cur->data.token_type == Token::ID){
	printf("LINE %d\n", __LINE__);
		fprintf(output, "pushm [ax + %d] \n", get_var_id(trans_glob::locals, cur->data.lexem));
	printf("LINE %d\n", __LINE__);
		return;
	}

	if (cur->data.token_type == Token::OP && cur->data.op_code != Operator::COMMA){
	printf("LINE %d\n", __LINE__);
		fprintf(output, "%s \n", str_tolower(Operator::op_code_strs[cur->data.op_code]));
	}

	printf("LINE %d\n", __LINE__);
	return;
}

void gen_COND(Tree::node_t* cur){

	printf("LINE %d\n", __LINE__);
	Assert(cur != NULL);

	gen_E(cur->left);
	gen_E(cur->right);
	
	fprintf(output, "%s true_if_%d \n", str_tolower(Operator::op_code_strs[cur->data.op_code]), cur_if);
	fprintf(output, "jmp false_if_%d \n", cur_if);

	printf("LINE %d\n", __LINE__);
}

void gen_CALL(Tree::node_t* cur){
	
	printf("LINE %d\n", __LINE__);
	Assert(cur != NULL);
	Assert(cur->data.op_code == Operator::CALL);
	
	const char* func_name = cur->right->data.lexem;

	cur = cur->left;
	while (cur->right){

		gen_E(cur->right);
		cur = cur->left;
	}

	fprintf(output, "push %d \n", trans_glob::locals->shift);
	fprintf(output, "pushr ax \n");
	fprintf(output, "add \n");
	fprintf(output, "popr ax \n");


	fprintf(output, "call func_%s \n", func_name);
	printf("LINE %d\n", __LINE__);
}

void gen_SET_VAR(Tree::node_t* cur){
	
	printf("LINE %d\n", __LINE__);
	Assert(cur != NULL);
	Assert(cur->data.op_code == Operator::ASSGN);

	int id = get_var_id(trans_glob::locals, cur->left->data.lexem);
	//if (id == -1) id = get_var_id(trans_glob::globals, cur->left->data.lexem);
	if (cur->right->data.op_code == Operator::CALL){
		gen_CALL(cur->right);
	} else {
		gen_E(cur->right);
	}

	fprintf(output, "popm [ax + %d] \n", id);
	printf("LINE %d\n", __LINE__);

}

void gen_IF(Tree::node_t* cur){

	printf("LINE %d\n", __LINE__);
	Assert(cur != NULL);

	int remember_if = cur_if;
	gen_COND(cur->left);
	++cur_if;
	fprintf(output, "\n");	
	fprintf(output, "true_if_%d: \n", remember_if);
	gen_BODY(cur->right->right);
	fprintf(output, "false_if_%d: \n", remember_if);
	gen_BODY(cur->right->left);
	//fprintf(output, ":end_if_%d \n", cur_if);
	printf("LINE %d\n", __LINE__);
}

void gen_PRINT(Tree::node_t* cur){
	printf("LINE %d\n", __LINE__);
	Assert(cur != NULL);	
	Assert(cur->data.op_code == Operator::WRITE);
	gen_E(cur->right);

	fprintf(output, "out \n");
	printf("LINE %d\n", __LINE__);
}

void gen_EXIT(Tree::node_t* cur){
	
	Assert(cur != NULL);
	Assert(cur->data.op_code == Operator::EXIT);
	fprintf(output, "jmp quit \n");
}

void gen_SQRT(Tree::node_t* cur){

	Assert(cur != NULL);
	Assert(cur->data.op_code == Operator::SQRT);

	fprintf(output, "pushm [ax + %d] \n", get_var_id(trans_glob::locals, cur->right->data.lexem));
	fprintf(output, "sqrt \n");
	fprintf(output, "popm [ax + %d] \n", get_var_id(trans_glob::locals, cur->right->data.lexem));
}

void gen_INPUT(Tree::node_t* cur){

	Assert(cur != NULL);
	Assert(cur->data.op_code == Operator::READ);

	fprintf(output, "in \n");
	fprintf(output, "popm [ax + %d] \n", get_var_id(trans_glob::locals, cur->right->data.lexem));
}

void gen_OP(Tree::node_t* cur){

	printf("LINE %d\n", __LINE__);
	Assert(cur != NULL);

	switch (cur->data.op_code){
		case Operator::IF:
			gen_IF(cur);
			break;
		case Operator::DEC_VAR:
			gen_DEC_VAR(cur);
			break;
		case Operator::ASSGN:
			gen_SET_VAR(cur);
			break;
		case Operator::RETURN:
			gen_RET(cur);
			break;
		case Operator::DEC_FUNC:
			gen_DEF_FUNC(cur);
			break;
		case Operator::WRITE:
			gen_PRINT(cur);
			break;
		case Operator::EXIT:
			gen_EXIT(cur);
			break;
		case Operator::READ:
			gen_INPUT(cur);
			break;
		case Operator::SQRT:
			gen_SQRT(cur);
			break;
		default:
			printf("!!!\n");
			break;
	}
	printf("LINE %d\n", __LINE__);
		
}
