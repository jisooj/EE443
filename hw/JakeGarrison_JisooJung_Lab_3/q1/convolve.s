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
#	r7 = After startIndex is used to move x pointer,
#	it's set to 4*N to be used in MOD.
#	r8 = one element past the x[N - 1]
#	r9 = temp1 = *x
#	r10 = temp2 = *h
#	r11 = temp3 = temp1 * temp2

# Return value:
#	r2 = sum

convolve:
	add  r2, r0, r0		# sum = 0
	muli r6, r6, 4		# N *= 4
	add  r5, r5, r6 	# h += N. r5 = one element past h[N - 1]
	subi r5, r5, 4		# h--. r5 = h[N - 1]
	add  r8, r6, r4		# r8 = one element past the x[N - 1]
	muli r7, r7, 4		# startIndex *= 4
	add  r4, r4, r7		# x += startIndex
	add  r7, r0, r6		# r7 = N. Used in MOD

	LOOP:
		ldw  r9,  0(r4)		# temp1 = *x
		ldw  r10, 0(r5)		# temp2 = *h
		mul  r11, r9, r10	# temp3 = temp1 * temp2 = h(n) * x(n - k)
		add  r2, r2, r11	# sum += temp
		addi r4, r4, 4		# x++
		subi r5, r5, 4		# h--
		subi r6, r6, 4		# N -= 4
		bge  r4, r8, MOD	# if (x >= r8) { MOD } else { CONDITION }
		jmpi CONDITION		# jump to loop condition

	MOD:
		sub  r4, r4, r7		# x = first element address
		jmpi CONDITION		# jump to loop condition

	CONDITION:
		bgt  r6, r0, LOOP	# if (N > 0) { LOOP } else { END }
		jmpi END			# jump to return statement

	END:
		ret					# return sum
