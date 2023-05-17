.text
add $t1, $zero, 5 # This is test case 2
add $t2, $zero, 2 ## Which is more harder
sub $t3, $t1, $t2
bne $t6, $t3, test
bne $t1, $t2, adorable
bne $t5, $t1, cute
cute: ## Randomly add some random things
	add $t1, $t1, 1

adorable:
	add $t1, $t1, 2

test:
	add $t1, $t1, $t2
	
	
