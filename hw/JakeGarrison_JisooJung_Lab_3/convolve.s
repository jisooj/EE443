.global convolve
# int convolve(int x[], int h[], int N, int startIndex)
# 	- convolution with x being a circular buffer. h's elements 
#	- remain still. 
# 	- N is the number of elements in x and h.
#	- Length of x and h must be equal
#	- startIndex indicates the most recent sample index in x
#	- startIndex must be from 0 to N - 1, inclusive.

# Parameters:
#	r4 = x
#	r5 = h
#	r6 = N
#	r7 = startIndex

# Local variables:
#	r2 = sum, return value
#	r8 = counter, will decremented by 1. Used in looping condition.
#	r9 = points one word past the last element of x, used for MOD purpose
#	r10 = temp storage for multiplied elements

# Return value:
#	r2 = sum

convolve:
	add r2, r0, r0		# sum = 0
	stw r6, r8 			# counter = N, decr by 1

	muli r6, r6, 4		# N *= 4
	add  r5, r5, r6 	# h += N. h points one word past the last element 
	subi r5, r5, 4		# h--. h now points to the last element

	add r9, r4, r6		# r9 = x + N 
						# Points to one word past the last element of x. 
						# Used for MOD purpose

	muli r7, r7, 4		# i *= 4
	add  r4, r4, r7		# x += startIndex
	
	LOOP:
		mul  r10, 0(r4), 0(r5)	# temp = h(n) * x(n - k)
		add  r2, r2, r10		# sum += temp
		
		addi r4, r4, 4			# x++
		subi r5, r5, 4			# h--
		subi r8, r8, 1			# counter--
		bge  r4, r9, MOD		# if (x >= counter)
		jmp CONDITION
		
	CONDITION:
		bgt  r8, r0, LOOP		# if (counter > 0) { LOOP } else { DONE }
		
	MOD:
		sub r4, r4, r6
		jmp CONDITION
		
	END:
		ret 
