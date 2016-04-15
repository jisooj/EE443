/* HW1 QUESTION 3
 * Jake and Jisoo
 */

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

#define UART_BUFFER_SIZE 512

//Value for interrupt ID
extern alt_u32 switch0_id;
extern alt_u32 switch1_id;
extern alt_u32 switch2_id;
extern alt_u32 switch3_id;
extern alt_u32 switch4_id;
extern alt_u32 switch5_id;
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
extern alt_16 datatest[UART_BUFFER_SIZE];
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

// ------------------------------------------------------------
#define LEN1 10
#define LEN2 20
#define LEN3 4
short alpha = 0;
short beta  = 0;
short gamm = 0;
short sine_f1[LEN1]={0,588,951,951,588,0,-588,-951,-951,-588};
short sine_f2[LEN2]={0, 809, 951, 309,-588,-1000,-588, 309, 951, 809,
					 0,-809,-951,-309, 588, 1000, 588,-309,-951,-809};
short sine_f3[LEN3]={0,1000,0,-1000};
// ------------------------------------------------------------

// ----------- switch handlers --------------
// switch 0,1 controls alpha
// switch 2,3 controls beta
// switch 4,5 controls gamma
// Bit convention:
// e.g. switch1 = 1, switch0 = 0 will make alpha = 2
static void handle_switch0_interrupt(void* context, alt_u32 id) {
	 volatile int* switch0ptr = (volatile int *)context;
	 *switch0ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH0_BASE);

	 /* Write to the edge capture register to reset it. */
	 IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH0_BASE, 0);

	 /*Perform Jobs*/
	 alpha = (IORD_ALTERA_AVALON_PIO_DATA(SWITCH1_BASE) << 1) |
			 IORD_ALTERA_AVALON_PIO_DATA(SWITCH0_BASE);
	 printf("alpha = %d\n", alpha);
}

static void handle_switch1_interrupt(void* context, alt_u32 id) {
	 volatile int* switch1ptr = (volatile int *)context;
	 *switch1ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH1_BASE);

	 /* Write to the edge capture register to reset it. */
	 IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH1_BASE, 0);

	 /*Perform Jobs*/
	 alpha = (IORD_ALTERA_AVALON_PIO_DATA(SWITCH1_BASE) << 1) |
			  IORD_ALTERA_AVALON_PIO_DATA(SWITCH0_BASE);
	 printf("alpha = %d\n", alpha);
}

static void handle_switch2_interrupt(void* context, alt_u32 id) {
	 volatile int* switch2ptr = (volatile int *)context;
	 *switch2ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH2_BASE);

	 /* Write to the edge capture register to reset it. */
	 IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH2_BASE, 0);

	 /*Perform Jobs*/
	 beta = (IORD_ALTERA_AVALON_PIO_DATA(SWITCH3_BASE) << 1) |
			 IORD_ALTERA_AVALON_PIO_DATA(SWITCH2_BASE);
	 printf("beta = %d\n", beta);
}

static void handle_switch3_interrupt(void* context, alt_u32 id) {
	 volatile int* switch3ptr = (volatile int *)context;
	 *switch3ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH3_BASE);

	 /* Write to the edge capture register to reset it. */
	 IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH3_BASE, 0);

	 /*Perform Jobs*/
	 beta = (IORD_ALTERA_AVALON_PIO_DATA(SWITCH3_BASE) << 1) |
			 IORD_ALTERA_AVALON_PIO_DATA(SWITCH2_BASE);
	 printf("beta = %d\n", beta);
}

static void handle_switch4_interrupt(void* context, alt_u32 id) {
	 volatile int* switch4ptr = (volatile int *)context;
	 *switch4ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH4_BASE);

	 /* Write to the edge capture register to reset it. */
	 IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH4_BASE, 0);

	 /*Perform Jobs*/
	 gamm = (IORD_ALTERA_AVALON_PIO_DATA(SWITCH5_BASE) << 1)|
			 IORD_ALTERA_AVALON_PIO_DATA(SWITCH4_BASE);
	 printf("gamm = %d\n", gamm);
}

static void handle_switch5_interrupt(void* context, alt_u32 id) {
	 volatile int* switch5ptr = (volatile int *)context;
	 *switch5ptr = IORD_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH5_BASE);

	 /* Write to the edge capture register to reset it. */
	 IOWR_ALTERA_AVALON_PIO_EDGE_CAP(SWITCH5_BASE, 0);

	 /*Perform Jobs*/
	 gamm = (IORD_ALTERA_AVALON_PIO_DATA(SWITCH5_BASE) << 1)|
			 IORD_ALTERA_AVALON_PIO_DATA(SWITCH4_BASE);
	 printf("gamm = %d\n", gamm);
}

// ---------------------------------------------------------------

/* Enable the flag to send recent
 * channel buffer to host computer.
 */
int reset = 0;
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
	 int normFactor = (alpha != 0) +
			 	 	  (beta  != 0) +
			 	 	  (gamm  != 0);
	 if (!normFactor) {
		 normFactor = 1;
	 }
	 int x_t = (alpha*sine_f1[leftCount % LEN1] +
				beta *sine_f2[leftCount % LEN2] +
				gamm *sine_f3[leftCount % LEN3]) / normFactor;
	 IOWR_ALTERA_AVALON_PIO_DATA(LEFTSENDDATA_BASE,x_t);
	 datatest[leftCount] = x_t;
	 // reset leftCount to zero if it reaches 512*/
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
