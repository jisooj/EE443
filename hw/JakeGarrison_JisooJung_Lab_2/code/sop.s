.global sop
/*
r4 - data (x)
r5 - coefficients (h)
r6 - N
*/
sop:
	add r2, r0, r0
	LOOP:
		ldw r9, 0(r4)
		ldw r10, 0(r5)
		mul r8, r9, r10
		add r2, r2, r8
		addi r4, r4, 4
		addi r5, r5, 4
		subi r6, r6, 1
		bgt r6, r0, LOOP
	ret