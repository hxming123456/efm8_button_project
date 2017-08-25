
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8BB1_Register_Enums.h>                  // SFR declarations
#include "InitDevice.h"
#include "stdio.h"

sbit led = P1^5;
sbit button = P1^4;
unsigned char flashing_flag=0;
unsigned char key_status=1;
unsigned char key_old = 1;
unsigned int flashing_time = 1000;
unsigned char longkey = 0;
// $[Generated Includes]
// [Generated Includes]$

//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
void LED_gpio_init(void)
{
	P1MDIN |= 0x20;
	P1MDOUT |= 0x20;
	P1SKIP |= 0x20;
	XBR2 |= 0X40;

	led = 0;
}

void button_gpio_init(void)
{
	P1MDIN |= 0x10;
	P1MDOUT |= 0x00;
	P1SKIP |= 0x10;

	button = 1;
}

void system_clock_set(void)
{
	CLKSEL = 0x00;
}

void T0_init(void)
{
	CKCON0 |= 0x04;
	TMOD |= 0x01;
	XBR1 |= 0x08;
	TH0 = 0xA0;
	TL0 = 0x4C;
	TCON |= 0x10;

	IE |= 0x02;
}

void T1_init(void)
{
	CKCON0 = 0x08;
	TMOD = 0x20;
	TH1 = 0x96;
	TL1 = 0x96;
	TCON = 0x40;
}

void UART0_init(void)
{
	XBR0 |= 0x01;
	SCON0 = 0x50;
	//IE = 0x90;
}

uint32_t usart_sendbyte(unsigned char c)
{
	SBUF0 = c;
	while(!SCON0_TI);
	SCON0_TI = 0;

	return 1;
}

uint32_t usart_send(unsigned char *buf)
{
	uint32_t sendlen=0;

	while(*buf != '\0')
	{
		usart_sendbyte(*buf);
		buf++;
		sendlen++;
	}

	return sendlen;
}

void disable_WDT(void)
{
	IE = 0x00;
	WDTCN = 0xDE;
	WDTCN = 0xAD;
	IE = 0x90;
}

int main (void)
{
	// Call hardware initialization routine
	//enter_DefaultMode_from_RESET();
	unsigned char buf[20] = {"hello world"};
	unsigned int cnt = 0;

	system_clock_set();
	LED_gpio_init();
	button_gpio_init();
	T1_init();
	UART0_init();
	disable_WDT();
	T0_init();

	while (1) 
   {
		if(!longkey)
		{
			if(key_status != key_old)
			{
				if(key_status == 1)
				{
					if(flashing_time <= 50)
					{
						flashing_time = 50;
					}
					else
					{
						flashing_time -= 50;
					}
				}
				key_old = key_status;
			}
		}
		if(flashing_flag)
		{
			flashing_flag=0;
			led = ~led;
		}
   }                             
}

SI_INTERRUPT (UART0_ISR, UART0_IRQn)
{

}

void keyscan(void)
{
	static unsigned char key_down_time=0;
	static unsigned char key_up_time = 0;
	static unsigned int key_long_time = 0;
	static unsigned char repeat_cnt = 1;

	if(button==0)
	{
		key_down_time++;
		key_long_time++;
	}
	else
	{
		key_up_time++;
	}
	if(key_long_time > 2000)
	{
		longkey=1;
		if((key_long_time-2000)>(repeat_cnt*500))
		{
			repeat_cnt++;
			flashing_time += 50;
		}
	}
	if(key_down_time>=20)
	{
		key_down_time = 0;
		key_status = 0;
	}
	else if(key_up_time>=20)
	{
		key_up_time = 0;
		key_status = 1;
		if(longkey)
		{
			key_long_time = 0;
			repeat_cnt = 1;
			longkey = 0;
			key_old = 1;
		}
	}
}

SI_INTERRUPT (TIME0_ISR, TIMER0_IRQn)
{
	static unsigned int cnt=0;

	TH0 = 0xA0;
	TL0 = 0x4C;
	keyscan();
	cnt++;
	if(cnt >= flashing_time)
	{
		cnt = 0;
		flashing_flag=1;
	}
}
