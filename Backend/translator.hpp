#pragma once

#include <stdio.h>
#include <stdlib.h>

FILE* output = fopen("output.asm", "w"); 
int cur_l = 0;
int cur_if = 0;

struct var_list_t {
	const char** names = new const char* [4096];
	int num_args = 0;
	int shift = 0;
};


namespace trans_glob {
	var_list_t* locals = new var_list_t [4096];
}

void add_arg(var_list_t* local_vars, const char* name){

	Assert(local_vars != NULL);
	Assert(name != NULL);

	local_vars->names[(local_vars->num_args)++] = name;
}

void add_var(var_list_t* local_vars, const char* name){
	
	Assert(local_vars != NULL);
	Assert(name != NULL);

	local_vars->names[(local_vars->shift)++] = name;
}

int get_var_id(var_list_t* local_vars, const char* name){
	
	Assert(local_vars != NULL);
	Assert(name != NULL);

	printf("GETTING VAR ID: %s\n", name);
	printf("shift = %d\n", local_vars->shift);

	for (int i = 0; i < local_vars->shift; ++i){
		if (strcmp(local_vars->names[i], name) == 0){
			return i;
		}
	}

	return -1;
}

const char* str_tolower(const char* str){

	Assert(str != NULL);

	char* lower = strdup(str);
	int i = 0;

	while (*str){
		*(lower + i++) = tolower(*str++);
	}

	return lower;
}
