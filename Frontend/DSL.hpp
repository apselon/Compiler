#define NODE(t, left, right) Tree::create_node(t->op_code, t->token_type, t->lexem, left, right);
#define ATTACHL(n,p) Tree::attach_left(

