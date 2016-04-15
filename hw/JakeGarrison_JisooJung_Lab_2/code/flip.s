.global flip
# void flip(int src[], int dst[], int N) 
# 	- Reverses src's elements and put them in dst 
#	- N is the number of elements in src and dst. 
#	- Length of src and dst must be equal
# r4 = src
# r5 = dst
# r6 = N

flip:
	muli r6, r6, 4			# N = N * 4
	add  r5, r5, r6			# dst += (initial N)
	subi r5, r5, 4			# dst--; Now dst points to the last element

	LOOP:
		ldw  r9, 0(r4)		# temp = *src
		stw  r9, 0(r5)		# *dst = temp
		addi r4, r4, 4		# src++
		subi r5, r5, 4		# dst--
		subi r6, r6, 4		# N -= 4
		bgt  r6, r0, LOOP	# if (N > 0) { LOOP } else { DONE }

	
	
# Try this for more efficient code 

# Change this 
	# ldw  r9, 0(r4)		# temp = *src
	# stw  r9, 0(r5)		# *dst = temp
# to this code:
	# stw 0(r4), 0(r5)		# *dst = *src