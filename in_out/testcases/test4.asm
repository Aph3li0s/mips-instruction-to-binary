addi $s0, $s0, 1
sll $s0, $s0, 2 #$s0 = 4
label: 
addi $s3, $s3, 4
beq $s3, $s3 jump
jump: srl $s0, $s0, 2