func_unmoved_mover: 
push 7 
popm [ax + 0] 
pushm [ax + 0] 
push 1 
pushr ax 
add 
popr ax 
call func_fact 
popm [ax + 0] 
pushm [ax + 0] 
out 
jmp quit 
func_fact: 
popm [ax + 0] 
pushm [ax + 0] 
push 1 
ja true_if_1 
jmp false_if_1 

true_if_1: 
push 1 
pushm [ax + 0] 
sub 
push 2 
pushr ax 
add 
popr ax 
call func_fact 
popm [ax + 1] 
pushm [ax + 0] 
pushm [ax + 1] 
mul 
popm [ax + 1] 
pushm [ax + 1] 
push 2 
pushr ax 
sub 
popr ax 
ret 
false_if_1: 
push 1 
push 2 
pushr ax 
sub 
popr ax 
ret 
quit: 
