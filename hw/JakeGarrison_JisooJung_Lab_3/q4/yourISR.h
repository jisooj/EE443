/* Lab 3
 * Jisoo Jung, Jake Garrison
 * */

/*
 * yourISR.h
 *
 *  Created on: Mar 11, 2014
 *      Author: zhwj814
 *  Updated on : Mar 31, 2015 by jsup517
 */

#ifndef YOURISR_H_
#define YOURISR_H_


#endif /* YOURISR_H_ */
#include "system_init.h"

// --------------------------------------------
#define UART_BUFFER_SIZE 256
int UARTData[UART_BUFFER_SIZE];

int switch0Flag = 0;
int switch1Flag = 0;
int switch2Flag = 0;

static short mDelay = 0;
static short mDelay_1 = 0;
static short mDelay_2 = 0;
static int N = 0;
static int Goertzel_Value = 0;

/* NOTE: Frequency detection ranges are off by 50~70
 * Ranges for:
 *    2000 Hz works best at around 1954 Hz
 *    2400 Hz works best at around 2343 Hz
 *    2800 Hz works best at around 2732 Hz
 *
 * NOTE: negation for the negative hex numbers
 *
 * k values: 
 *    k1 = 51 
 *    k2 = 62
 *    k3 = 72
 * */
// with unrounded k values
short coef_1 = 0x0;         // For detecting 2000 Hz
short coef_2 = ~0x278E + 1; // For detecting 2400 Hz
short coef_3 = ~0x4B3D + 1; // For detecting 2800 Hz

// with rounded k values
/*
short coef_1 = 0xFB;         // For detecting 2000 Hz
short coef_2 = ~0x296A + 1; // For detecting 2400 Hz
short coef_3 = ~0x4C07 + 1; // For detecting 2800 Hz
*/

short coef = 0x0;
int prod1 = 0;
int prod2 = 0;
int prod3 = 0;
int input = 0;

void Goertzel(int R_in) {
	input = (short) R_in;
	input = input >> 4; // Scale down input to prevent overflow
	prod1 = (mDelay_1 * coef) >> 14;
	mDelay = input + (short)prod1 - mDelay_2;
	mDelay_2 = mDelay_1;
	mDelay_1 = mDelay;
	N++;
	if (N == 205) {
		prod1 = (mDelay_1 * mDelay_1);
		prod2 = (mDelay_2 * mDelay_2);
		prod3 = (mDelay_1 * coef) >> 14;
		prod3 = prod3 * mDelay_2;
		Goertzel_Value = (prod1 + prod2 - prod3) >> 15;
		Goertzel_Value <<= 4; // Scale up value for sensitivity
		N = 0;
		mDelay_1 = 0;
		mDelay_2 = 0;
		printf("Goertzel_Value = %d\n", Goertzel_Value);
	}
	IOWR_ALTERA_AVALON_PIO_DATA(LEFTSENDDATA_BASE, Goertzel_Value);
}

// --------------------------------------------

//Value for interrupt ID
extern alt_u32 switch0_id;
extern alt_u32 switch1_id;
extern alt_u32 switch2_id;
extern alt_u32 key0_id;
extern alt_u32 key1_id;
extern alt_u32 key2_id;
extern alt_u32 key3_id;
extern alt_u32 leftready_id;
extern alt_u32 rightready_id;
extern alt_u32 uart_id;

//leftChannel and rightChannel are the instant values of the value reading from ADC
extern int leftChannel;
extern int rightChannel;
extern int convResultBufferSize;
extern int convIndex;

//Default ADC Sampling frequency = 8k
extern int sampleFrequency;

//Buffer that store values from different channels
extern alt_16 leftChannelData[BUFFERSIZE];
extern alt_16 rightChannelData[BUFFERSIZE];
extern int convResultBuffer[CONVBUFFSIZE];
extern alt_16 datatest[256];
/*uart-global
 * RxHead: integer indicator tells you the index of where the
 * newest char data you received from host computer
 *
 * rx_buffer-> A ring buffer to collect uart data sent by host computer
 * */
extern unsigned short RxHead;
extern unsigned char rx_buffer[RX_BUFFER_SIZE];

/*Channel indicators: indicate the index of the most recent collected data*/
extern int leftCount;
extern int lefttestCount;
extern int rightCount;
extern int calBuffersize;
extern int leftBufferFull;

/*temporary use*/
extern int tempCount;

/*Send flag: 1->ok, now send data to the host
 *           0->ok, will not send any data to the host
 *Recv flag: 1->ok, now check and store data from the host
 *           0->ok, will not receive any data from the host
 */
extern int uartStartSendFlag;
extern int uartStartRecvFlag;
/*for uart receive purpose*/
extern int sr;

/*0->do not update sampling frequency*/
/*1->ok, update sampling frequency to AIC23*/
extern int setFreqFlag;

/*uart object*/
extern int uart;

static void handle_switch0_interrupt(void* context, alt_u32 id) {
	 volatile int* switch0ptr = (volatile int *)context;
	 *switch0ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH0_BASE);

	 /* Write to the edge capture register to reset it. */
	 IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH0_BASE, 0);

	 /*Perform Jobs*/
	 if (IORD_ALTERA_AVALON_PIO_DATA(SWITCH0_BASE)) {
		 coef = coef_1;
		 switch0Flag = 1;
	 }
}

static void handle_switch1_interrupt(void* context, alt_u32 id) {
	 volatile int* switch1ptr = (volatile int *)context;
	 *switch1ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH1_BASE);

	 /* Write to the edge capture register to reset it. */
	 IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH1_BASE, 0);

	 /*Perform Jobs*/
	 if (IORD_ALTERA_AVALON_PIO_DATA(SWITCH1_BASE)) {
		 coef = coef_2;
		 switch1Flag = 1;
	 }
}

static void handle_switch2_interrupt(void* context, alt_u32 id) {
	 volatile int* switch2ptr = (volatile int *)context;
	 *switch2ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH2_BASE);

	 /* Write to the edge capture register to reset it. */
	 IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH2_BASE, 0);

	 /*Perform Jobs*/
	 if (IORD_ALTERA_AVALON_PIO_DATA(SWITCH2_BASE)) {
		 coef = coef_3;
		 switch2Flag = 1;
	 }
}

/* Enable the flag to send recent
 * channel buffer to host computer.
 */
static void handle_key0_interrupt(void* context, alt_u32 id) {
	 volatile int* key0ptr = (volatile int *)context;
	 *key0ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(KEY0_BASE);

	 /* Write to the edge capture register to reset it. */
	 IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY0_BASE, 0);

	 uartStartSendFlag = 1;
}

/* Enable the flag to update the
 * ADC sampling frequency on AIC23.
 */
static void handle_key1_interrupt(void* context, alt_u32 id) {
	 volatile int* key1ptr = (volatile int *)context;
	 *key1ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(KEY0_BASE);

	 /* Write to the edge capture register to reset it. */
	 IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY1_BASE, 0);

	 //IOWR_ALTERA_AVALON_PIO_IRQ_MASK(SWITCH1_BASE, 0x01);
	 setFreqFlag = 1;
}

static void handle_key2_interrupt(void* context, alt_u32 id) {
	 volatile int* key2ptr = (volatile int *)context;
	 *key2ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(KEY2_BASE);

	 /* Write to the edge capture register to reset it. */
	 IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY2_BASE, 0);

}

static void handle_key3_interrupt(void* context, alt_u32 id) {
	 volatile int* key3ptr = (volatile int *)context;
	 *key3ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(KEY3_BASE);

	 /* Write to the edge capture register to reset it. */
	 IOWR_ALTERA_AVALON_PIO_EDGE_CAP(KEY3_BASE, 0);

	 IOWR_ALTERA_AVALON_PIO_DATA(LED_BASE, 0x10);
}

/*  Detect left channel ready interrupt and do:
 *  Collect data,
 *  store in buffer,
 *  instantly play back.
 *
 */

int unsigned2signed(alt_16 unsign){
	int result;
	if(unsign>32767)
		result = unsign - 65536;
	else
		result = unsign;
	return result;
}

alt_16 signed2unsigned(int sign){
	alt_16 result;
	if(sign<0)
		result = sign + 65536;
	else
		result = sign;
	return result;
}

static void handle_leftready_interrupt_test(void* context, alt_u32 id) {
	 volatile int* leftreadyptr = (volatile int *)context;
	 *leftreadyptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(LEFTREADY_BASE);
	 IOWR_ALTERA_AVALON_PIO_EDGE_CAP(LEFTREADY_BASE, 0);
	 /*******Read, playback, store data*******/
	 leftChannel = IORD_ALTERA_AVALON_PIO_DATA(LEFTDATA_BASE);

	 Goertzel(leftChannel);
	 UARTData[leftCount] = Goertzel_Value;
	 leftCount = (leftCount + 1) % UART_BUFFER_SIZE;
}


/*  Detect right channel ready interrupt and do:
 *  Collect data,
 *  store in buffer,
 *  instantly play back.
 */
static void handle_rightready_interrupt_test(void* context, alt_u32 id) {
	 volatile int* rightreadyptr = (volatile int *)context;
	 *rightreadyptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(RIGHTREADY_BASE);
	 IOWR_ALTERA_AVALON_PIO_EDGE_CAP(RIGHTREADY_BASE, 0);
	 /*******Read, playback, store data*******/
	 rightChannel = IORD_ALTERA_AVALON_PIO_DATA(RIGHTDATA_BASE);
	 IOWR_ALTERA_AVALON_PIO_DATA(RIGHTSENDDATA_BASE, rightChannel);
	 rightChannelData[rightCount] = rightChannel;
	 rightCount = (rightCount+1) % BUFFERSIZE;
	 /****************************************/
}
