#include <stdio.h>

int convolve(int x[], int h[], int N, int i);
void testConv();
void conv(int value);

#define N 5
int convIndex = 0;
int convBuffer[N];
int x[N];// = {1,2,3,4,5};
int h[] = {1,3,5,7,9};
int x_i = 0; // starting index of x

int main(int argc, char** argv) {	
	testConv();
	return 0;
}

void testConv() {
	int index;
	for (index = 0; index < N; index++) {
		conv(index + 1);
		printf("i = %d, convResult = %d\n", index, convBuffer[index]);
	}
}

void conv(int value) {
	x[x_i] = value;
	x_i = (x_i + 1) % N;
	convBuffer[convIndex] = convolve(x, h, N, x_i);
	convIndex = (convIndex + 1) % N;
}

int convolve(int x[], int h[], int size, int i){
	int count;
	int convResult = 0;
	for(count = 0; count < size; count++){
		convResult += (h[(size - 1 - count)] * x[i % size]);
		i++;
	}
	return convResult;
}
