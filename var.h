/*
 * var.h
 *
 * Created: 16/12/2021 08:34:07 م
 *  Author: ahmed essam
 */ 


#ifndef VAR_H_
#define VAR_H_

char a = 0;
char b = 0;
char c = 0;
char d = 0;
char a1 = 0;
char b1 = 0;
char c1 = 0;
char d1 = 0;
char g = 0;
char trash;
int bit_num = 0;
int puls_num = 0;                  //number of pulses of one signal
char buffer1[16],buffer2[10];
int  puls_time = 0;                  //array of time per pulses for one signal
int signal_num = 0;                //number of received signal

typedef struct
{
	char start1 ;
	char start2 ;
	int address_ ;
	int command_ ;
	int address_INV ;
	int command_INV ;
} puls_components;

puls_components puls_comp;



#endif /* VAR_H_ */