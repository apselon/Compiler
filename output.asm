func_unmoved_mover: 
in 
popm [ax + 0] 
in 
popm [ax + 1] 
in 
popm [ax + 2] 
pushm [ax + 0] 
pushm [ax + 1] 
pushm [ax + 2] 
push 3 
pushr ax 
add 
popr ax 
call func_solve_square 
popm [ax + 0] 
jmp quit 
func_solve_linear: 
popm [ax + 0] 
popm [ax + 1] 
pushm [ax + 0] 
push 0 
je true_if_0 
jmp false_if_0 

true_if_0: 
push 666 
out 
push 0 
push 2 
pushr ax 
sub 
popr ax 
ret 
false_if_0: 
pushm [ax + 0] 
pushm [ax + 1] 
div 
push 0 
sub 
out 
push 0 
push 2 
pushr ax 
sub 
popr ax 
ret 
func_solve_square: 
popm [ax + 0] 
popm [ax + 1] 
popm [ax + 2] 
pushm [ax + 0] 
push 0 
je true_if_1 
jmp false_if_1 

true_if_1: 
pushm [ax + 1] 
pushm [ax + 2] 
push 7 
pushr ax 
add 
popr ax 
call func_solve_linear 
popm [ax + 5] 
push 0 
push 7 
pushr ax 
sub 
popr ax 
ret 
false_if_1: 
pushm [ax + 1] 
pushm [ax + 1] 
mul 
popm [ax + 3] 
pushm [ax + 2] 
pushm [ax + 0] 
mul 
popm [ax + 4] 
pushm [ax + 4] 
push 4 
mul 
pushm [ax + 3] 
sub 
popm [ax + 3] 
pushm [ax + 3] 
push 0 
ja true_if_2 
jmp false_if_2 

true_if_2: 
pushm [ax + 3] 
sqrt 
popm [ax + 3] 
pushm [ax + 0] 
pushm [ax + 0] 
add 
popm [ax + 0] 
pushm [ax + 3] 
pushm [ax + 1] 
sub 
popm [ax + 5] 
pushm [ax + 0] 
pushm [ax + 5] 
div 
popm [ax + 5] 
pushm [ax + 5] 
push 0 
sub 
out 
pushm [ax + 3] 
pushm [ax + 1] 
add 
popm [ax + 6] 
pushm [ax + 0] 
pushm [ax + 6] 
div 
popm [ax + 6] 
pushm [ax + 6] 
push 0 
sub 
out 
push 0 
push 7 
pushr ax 
sub 
popr ax 
ret 
false_if_2: 
pushm [ax + 3] 
push 0 
je true_if_3 
jmp false_if_3 

true_if_3: 
pushm [ax + 0] 
pushm [ax + 0] 
add 
popm [ax + 0] 
pushm [ax + 0] 
pushm [ax + 1] 
div 
popm [ax + 5] 
pushm [ax + 5] 
push 0 
sub 
out 
push 0 
push 7 
pushr ax 
sub 
popr ax 
ret 
false_if_3: 
push 777 
push 0 
sub 
out 
push 0 
push 7 
pushr ax 
sub 
popr ax 
ret 
quit: 
