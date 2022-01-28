/*
 * send_fun.c
 *
 * Created: 14/01/2022 09:28:52 م
 *  Author: ahmed essam
 */ 

#include "send_fun.h"

void send_start_bit()
{
	PORTC |= (1<<PORTC1); //  9ms High pulse
	start_tim1_ctc(9000);
	see_compare();
	
	PORTC &= ~(1<<PORTC1);  // 4.5ms Low pulse
	start_tim1_ctc(4500);
	see_compare();
}

void send_8bits(int a)
{
	for (char i = 0;i <= 7;i++)
	{
		if ((a & (1<<i)) == 0)   //send zero
		{
			PORTC |= (1<<PORTC1); //  562us High pulse
			start_tim1_ctc(562);
			see_compare();
			
			PORTC &= ~(1<<PORTC1);  // 562us Low pulse
			start_tim1_ctc(562);
			see_compare();	
		}
		else if ((a & (1<<i)) == 1)
		{
			PORTC |= (1<<PORTC1); //  562us High pulse
			start_tim1_ctc(562);
			see_compare();
			
			PORTC &= ~(1<<PORTC1);  // 1687us Low pulse
			start_tim1_ctc(1687);
			see_compare();			
		}
	}
}

void send_end_bit()
{
	PORTC |= (1<<PORTC1); //  562us High pulse
	start_tim1_ctc(562);
	see_compare();	
	PORTC &= ~(1<<PORTC1);
}