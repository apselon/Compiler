func_unmoved_mover: 
in 
popm [ax + 0] 
pushm [ax + 0] 
push 2 
pushr ax 
add 
popr ax 
call func_fact 
popm [ax + 1] 
pushm [ax + 1] 
out 
jmp quit 
func_fact: 
popm [ax + 0] 
pushm [ax + 0] 
push 1 
ja true_if_0 
jmp false_if_0 

true_if_0: 
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
false_if_0: 
push 1 
push 2 
pushr ax 
sub 
popr ax 
ret 
quit: 
