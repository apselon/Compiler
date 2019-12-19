#include "asm.hpp"

const char* read_text(FILE* file, int* num_chars){

      Assert(file != NULL);
      fseek(file, 0L, SEEK_END);
      *num_chars = ftell(file);
      rewind(file);

      char* whole_text = (char* )calloc(*num_chars, sizeof(char));

      fread(whole_text, sizeof(char), *num_chars, file);

      return whole_text;
  }

void skip_spaces(const char** text){
      
      Assert(text != NULL);
      
      while (isspace(**text)){
          ++(*text);
      }   
  }


const char** split_text(const char* text, int* len){
	
	Assert(text != NULL);
	Assert(len != NULL);

	int offset = 0;
	const char** splited = (const char**)calloc(4096, sizeof(char*));

	while (*text){
		skip_spaces(&text);
		if (!*text) break;

		sscanf(text, "%ms%n", splited, &offset);

		++splited;
		++(*len);
		text += offset;
	}

	return splited;
}

commands::cmd_t cmd_code(const char* lexem){
	for (int i = 0; i < commands::num; ++i){
		if (strcmp(commands::names[i], lexem)){
			return (commands::cmd_t)i;
		}
	}

	return commands::VOID;
}

token generate_token(const char* lexem){
	
	Assert(lexem != NULL);
	
	token t = {};

	if (isdigit(*lexem)){
		t.type = NUM;
		sscanf(lexem, "%d", &t.val);
	}

	if (*lexem == ':'){
		t.type = LAB;
		t.val = num_lables;
		sscanf(lexem, "%ms", &lables[num_lables]);
		++num_lables;
	}

	if (*lexem == 'X'){
		t.type = REG;
		t.val = *(lexem + 1) - 'A';
	}

	if (cmd_code(lexem) != commands::VOID){
		
	}

	return t;
}
