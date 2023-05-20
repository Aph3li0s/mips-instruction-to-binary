addi $s1, $s1, 4
ori $s2, $s1, 0
srl $s1, $s1, 2     #$s1 = 1
beq $s1, $s2 jump
###some random cmt
fake: 
addi $s0, $s1, -2
jump:
    add $s0,,,,, $s1,   $s2
