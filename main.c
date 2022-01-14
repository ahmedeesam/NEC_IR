/*
 * external-INT-timer0.c
 *
 * Created: 14/12/2021 04:04:28 م
 * Author : ahmed essam
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "var.h"
#include "ext_int.h"
#include "timer0.h"
#include "timer1.h"
#include "lcd.h"




ISR (INT0_vect)
{
	if(puls_num == 0)
	{
		start_tim1_normal();
	}
	else if (puls_num != 0)
	{
		puls_time = read_tim1();
		start_tim1_normal();
		puls_num++;
		if (puls_num == 2)
		{
			if ((puls_time > 4400) && (puls_time < 4600) )
			{
				puls_comp.start2 = 1;
			}
		}
		if ((puls_comp.start1 == 1) && (puls_comp.start2 == 1) && (puls_num > 2))
		{
		if ((bit_num >= 0) && (bit_num <= 7))
		{
			if ((puls_time > 1100) && (puls_time < 1400) )  //1250 for LOW +- 50 timing error
			{
				puls_comp.address_ = (puls_comp.address_ << 1);
				/*puls_comp.address_ &= ~(1 << 7);
				puls_comp.address_ = (puls_comp.address_ >> 1);
				a++;*/
			}
			else if ((puls_time > 2200) && (puls_time < 2300) )  //2250 for HIGH +- 50 timing error
			{
				puls_comp.address_ = (puls_comp.address_ << 1)|(0x01);
				/*puls_comp.address_ |= (1 << 7);
				puls_comp.address_ = (puls_comp.address_ >> 1);
				a1++;*/
			}
			bit_num++;
			
		}
		else if ((bit_num > 7) && (bit_num <= 15))
		{
			if ((puls_time > 1100) && (puls_time < 1400) )  //1250 for LOW +- 50 timing error
			{
				puls_comp.address_INV = (puls_comp.address_INV << 1);
				/*puls_comp.address_INV &= ~(1 << 7);
				puls_comp.address_INV = (puls_comp.address_ >> 1);
				b++;*/
			}
			else if ((puls_time > 2200) && (puls_time < 2300) )  //2250 for HIGH +- 50 timing error
			{
				puls_comp.address_INV = (puls_comp.address_INV << 1)|(0x01);
				/*puls_comp.address_INV |= (1 << 7);
				puls_comp.address_INV = (puls_comp.address_ >> 1);
				b1++;*/
			}
			bit_num++;
			
		}
		else if ((bit_num > 15) && (bit_num <= 23))
		{
			if ((puls_time > 1100) && (puls_time < 1400) )  //1250 for LOW +- 50 timing error
			{
				puls_comp.command_ = (puls_comp.command_ << 1);
				/*puls_comp.command_ &= ~(1 << 7);
				puls_comp.command_ = (puls_comp.address_ >> 1);
				c++;*/
			}
			else if ((puls_time > 2200) && (puls_time < 2300) )  //2250 for HIGH +- 50 timing error
			{
				puls_comp.command_ = (puls_comp.command_ << 1)|(0x01);
				/*puls_comp.command_ |= (1 << 7);
				puls_comp.command_ = (puls_comp.address_ >> 1);
				c1++;*/
			}
			bit_num++;
			
		}
		else if ((bit_num > 23) && (bit_num <= 31))
		{
			if ((puls_time > 1100) && (puls_time < 1400) )  //1250 for LOW +- 50 timing error
			{
				puls_comp.command_INV = (puls_comp.command_INV << 1);
				/*puls_comp.command_INV &= ~(1 << 7);
				puls_comp.command_INV = (puls_comp.address_ >> 1);
				d++;*/
			}
			else if ((puls_time > 2200) && (puls_time < 2300) )  //2250 for HIGH +- 50 timing error
			{
				puls_comp.command_INV = (puls_comp.command_INV << 1)|(0x01);
				/*puls_comp.command_INV |= (1 << 7);
				puls_comp.command_INV = (puls_comp.address_ >> 1);
				d1++;*/
			}
			bit_num++;
			
		}
	}
}
}


ISR (INT1_vect)
{
	puls_time = read_tim1();
	puls_num++;
		if ((puls_time > 8950) && (puls_time < 9050 ) )
		{
			puls_comp.start1 = 1;
		}
	start_tim1_normal();
	int1_STOP();
}

ISR (TIMER0_COMPA_vect)
{
	g = ~g;
	if (g == 0)
	{
		PORTC &= ~(1<<PORTC0);
	}
	else if (g != 0)
	{
		PORTC |= (1<<PORTC0);
	}
	
}

void reverse(int *b) {
	*b = (((*b & 0xF0) >> 4) | ((*b & 0x0F) << 4));
	*b = (((*b & 0xCC) >> 2) | ((*b & 0x33) << 2));
	*b = (((*b & 0xAA) >> 1) | ((*b & 0x55) << 1));
}

int main(void)
{
	DDRC |= ((1<<PORTC0)|(1<<PORTC1));
	lcd_init();
	lcd_send_command(LCD_CMD_DISPLAY_NO_CURSOR);
	int0_START();
	int1_init();

	 
	while (1)
	{	
		int1_init();
		
		/*a = 0;
		b = 0;
		c = 0;
		d = 0;
		a1 = 0;
		b1 = 0;
		c1 = 0;
		d1 = 0;*/
		
		puls_comp.start1 = 0;
		puls_comp.start2 = 0;
		puls_comp.address_ = 0;
		puls_comp.address_INV = 0;
		puls_comp.command_ = 0;
		puls_comp.command_INV = 0;
		
		sei();
		lcd_clear();                         //open global interrupts
		lcd_goto_xy(0,0);
		lcd_write_word("signal:");
		signal_num++;
		itoa(signal_num,buffer2,9);	/* int to string conversion */
		lcd_write_word(buffer2);
		
		while(!(TIFR1 & (1<<TOV1)));     //wait until stop receiving, timer1 overflow works good
		cli();                            //disable global interrupts ,to not disrupting sending
		TIFR1 = (1<<TOV1);          //clear timer1 overflow flag
		trash =  read_tim1();                //stop timer1
		
		reverse(&puls_comp.address_);
		reverse(&puls_comp.address_INV);
		reverse(&puls_comp.command_);
		reverse(&puls_comp.command_INV);		
		
		for (char k = 0;k <= 5;k++)
		{
			if (k == 0)
			{
				lcd_clear();
				lcd_goto_xy(0,0);
				lcd_write_word("address");
				/*lcd_goto_xy(1,10);
				itoa(a,buffer2,9);
				lcd_write_word(buffer2);
				lcd_goto_xy(1,0);
				itoa(a1,buffer2,9);
				lcd_write_word(buffer2);*/
				lcd_goto_xy(1,0);
				itoa(puls_comp.address_,buffer1,13);
				lcd_write_word(buffer1);
				_delay_ms(500);	
			} 
			else if (k == 1)
			{
				lcd_clear();
				lcd_goto_xy(0,0);
				lcd_write_word("address_INV");
				/*lcd_goto_xy(1,10);
				itoa(b,buffer2,9);
				lcd_write_word(buffer2);
				lcd_goto_xy(1,0);
				itoa(b1,buffer2,9);
				lcd_write_word(buffer2);*/
				lcd_goto_xy(1,0);
				itoa(puls_comp.address_INV,buffer1,13);
				lcd_write_word(buffer1);
				_delay_ms(500);
			}
			else if (k == 2)
			{
				lcd_clear();
				lcd_goto_xy(0,0);
				lcd_write_word("command");
				/*lcd_goto_xy(1,10);
				itoa(c,buffer2,9);
				lcd_write_word(buffer2);
				lcd_goto_xy(1,0);
				itoa(c1,buffer2,9);
				lcd_write_word(buffer2);*/
				lcd_goto_xy(1,0);
				itoa(puls_comp.command_,buffer1,13);
				lcd_write_word(buffer1);
				_delay_ms(500);
			}
			else if (k == 3)
			{
				lcd_clear();
				lcd_goto_xy(0,0);
				lcd_write_word("command_INV");
				/*lcd_goto_xy(1,10);
				itoa(d,buffer2,9);
				lcd_write_word(buffer2);
				lcd_goto_xy(1,0);
				itoa(d1,buffer2,9);
				lcd_write_word(buffer2);*/
				lcd_goto_xy(1,0);
				itoa(puls_comp.command_INV,buffer1,13);
				lcd_write_word(buffer1);
				_delay_ms(500);
			}
			else if (k == 4)
			{
				lcd_clear();
				lcd_goto_xy(0,0);
				if (puls_comp.start1 == 1)
				{
					lcd_write_word("start1 here");
				} 
				else if (puls_comp.start1 == 0)
				{
					lcd_write_word("no start1");
				}
				_delay_ms(500);
			}
			else if (k == 5)
			{
				lcd_clear();
				lcd_goto_xy(0,0);
				if (puls_comp.start2 == 1)
				{
					lcd_write_word("start2 here");
				}
				else if (puls_comp.start2 == 0)
				{
					lcd_write_word("no start2");
				}
				_delay_ms(500);
			}
		}
		puls_num = 0;
		bit_num = 0;
	}
}


	/*	if (puls_comp.start1 == 1)
		{
			lcd_clear();
			lcd_goto_xy(0,0);
			lcd_write_word("start 1!");
		} 
		if (puls_comp.start2 == 1)
		{
			lcd_goto_xy(1,0);
			lcd_write_word("start 2!");
			_delay_ms(500);
		}*/