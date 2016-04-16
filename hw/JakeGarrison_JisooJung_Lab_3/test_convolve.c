#include <stdio.h>

int convolve(int x[], int h[], int N, int i);


int main(int argc, char** argv) {
	int N = 5;
	int x[] = {1,2,3,4,5};
	int h[] = {1,3,5,7,9};
	int i = 0;
	
	int index;
	for (index = 0; index < N; index++) {
		printf("i = %d, convResult = %d\n", i, convolve(x, h, N, i));
		i++;
	}
	return 0;
}

int convolve(int x[], int h[], int N, int i){
	int count;
	int convResult = 0;
	for(count = 0; count < N; count++){
		convResult += (h[(N - 1 - count)] * x[i % N]);
		i++;
	}
	return convResult;
	// convResultBuffer[convIndex] = convResult;
	// convIndex = (convIndex + 1) % (CONVBUFFSIZE);
}
