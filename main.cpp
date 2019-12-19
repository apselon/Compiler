#include "Frontend/frontend.cpp"
#include "Backend/translator.cpp"

int main(int argc, char* argv[]){

	const char* filename = (argc - 1 >= 1)?(argv[1]):("test.socrat");
	FILE* input_f = fopen(filename, "r");
	
	int len = count_chars(input_f);
	char* text = read_text(input_f, len);


	Tree::tree_t* AST = generated_AST(text);

	Tree::draw(AST, 1);
		
	gen_BODY(AST->root->right);

	fprintf(output, "quit: \n");

	fclose(input_f);
	fclose(output);
}
