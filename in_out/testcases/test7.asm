addi $s0,,,, $s1,    5 ##$s0 = 5
addi $s1, $s1, 4
	sub $s1, $s1, $s0 
	slt $s2, $s1, $s0
									#$%$*!(%*^&)???<>":",.{}_+
fake_label:
sll $s2, $s2, 2
beq $s1, $s2, jump
fake2:
addi $s0, $s0, 1

###Nothing in here,,

jump:
lw $s3, 0($s2)
jr $s3
