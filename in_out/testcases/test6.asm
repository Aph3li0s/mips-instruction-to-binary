add $t1, $t2, $t1
addi $t1, $a0, 0
bne $a1, $t1, exit
lw $a3, 4($t1)
exit:
