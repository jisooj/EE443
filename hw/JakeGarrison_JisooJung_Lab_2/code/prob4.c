// -------------------------------------------------------------------
// Solution 1: This approach doesn't involve circular buffer. Instead, 
// older values in the buffer gets shifted whenever new input comes in. 
// The provided SoP function can be used but it's less efficient than
// the solution that uses circular buffer.

#define M 4
#define L 3
// b_m = [1 3 3 1] * (4.29 * 10^-3) = [0.0043 0.0129 0.0129 0.0043]
// a_l = [-2.439 2.122 -0.6488] 
float b[M] = {0.0043, 0.0129, 0.0129, 0.0043};
float a[L] = {-2.439, 2.122, -0.6488};

float x[M];
float y[L];

// Shift the buffer's elements such that the last element gets removed.
// Then put the given input (current sample) at index 0
void shiftInsert(float input, float buffer[], short length) {
	short i;
	for (i = length - 1; i > 0; i--) {
		buffer[i] = buffer[i - 1]; 
	}
	buffer[0] = input;	
}

// Order of computation in IIR filter 
// 1. store input data
// 2. update x buffer 
// 3. compute y_n 
// 4. update y buffer 
// 5. output y_n
static void handle_leftready_interrupt_test(void* context, alt_u32 id) {
	volatile int* leftreadyptr = (volatile int *)context;
	*leftreadyptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(LEFTREADY_BASE);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(LEFTREADY_BASE, 0);

	/******* Apply Filter *******/
	float input = (float) unsigned2signed(IORD_ALTERA_AVALON_PIO_DATA(LEFTDATA_BASE));
	
	shiftInsert(input, x, M);

	// yn = - (sum from i = 1 to L - 1(a_i * y(n - i)))
	//      + (sum from i = 1 to M - 1(b_i * x(n - i)))
	float yn = SoP(x, b, M) - SoP(y, a, L);

	shiftInsert(yn, y, L);
	//scale output (shift right 15 bits)
	IOWR_ALTERA_AVALON_PIO_DATA(LEFTSENDDATA_BASE, yn >> 15);
}

// -------------------------------------------------------------------
// Solution 2: This approach involves using circular buffer. Thus, more 
// efficient than solution 1. However, the provided SoP function can't 
// be used by itself because buffer's elements are not always located 
// in line with the corresponding coefficients. 
// New input value gets stored in the later index in the x buffer. Then 
// wraps around to index 0. Same idea applies to y buffer as well.

#define M 4
#define L 3
// b_m = [1 3 3 1] * (4.29 * 10^-3) = [0.0043 0.0129 0.0129 0.0043]
// a_l = [-2.439 2.122 -0.6488] 
float b[M] = {0.0043, 0.0129, 0.0129, 0.0043};
float a[L] = {-2.439, 2.122, -0.6488};

float x[M];
float y[L];

short x_i = 0; // current x index
short y_i = 0; // current y index

static void updateX() {
	x_i = (x_i + 1) % M;
}

static void updateY() {
	y_i = (y_i + 1) % L;
}

static void circularInsertX(int input) {
	x[x_i] = input;
	updateX();
}

static void circularInsertY(int input) {
	y[y_i] = input;
	updateY();
}

// Order of computation in IIR filter 
// 1. store input data
// 2. update x buffer 
// 3. compute y_n 
// 4. update y buffer 
// 5. output y_n
static void handle_leftready_interrupt_test(void* context, alt_u32 id) {
	volatile int* leftreadyptr = (volatile int *)context;
	*leftreadyptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(LEFTREADY_BASE);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(LEFTREADY_BASE, 0);
	
	/******* Apply Filter *******/
	float input = (float) IORD_ALTERA_AVALON_PIO_DATA(LEFTDATA_BASE);
	
	// shift data and put the current sample at index 0
	circularInsertX(input);

	// yn = - (sum from i = 1 to L - 1(a_i * y(n - i)))
	//      + (sum from i = 1 to M - 1(b_i * x(n - i)))
	// x_i and y_i here are pointing at the least recently put input
	float yn = circularSoP(x, b, M, x_i) - circularSoP(y, a, L, y_i);

	circularInsertY(yn);
	//scale output (shift right 15 bits)
	IOWR_ALTERA_AVALON_PIO_DATA(LEFTSENDDATA_BASE, yn >> 15);
}

// NOTE: need circularSoP(x1, x2, size, start);
// x1 = fixed, x2 = circular
// x1's index always starts at 0
// x1's index decrements by 1 from size to 0
// start = starting index of x2
// x2's index increments by 1 then mod by size
// iterate 'size' many times