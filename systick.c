/*
* systick.c
*
* M.Fatih INANC
* fatihinanc.com
*
* 09.12.2012
*/


#include "inc/lm4f120h5qr.h"
#include "systick.h"

unsigned long systick_count = 0;

void systick_init(void)
{
  NVIC_ST_CTRL_R = 0;
  NVIC_ST_RELOAD_R = NVIC_ST_RELOAD_M;
  NVIC_ST_CURRENT_R = 0;

  NVIC_ST_CTRL_R = NVIC_ST_CTRL_ENABLE + NVIC_ST_CTRL_CLK_SRC;
}

// На 50 MHz каждый тик равен 20nS, на 80 MHz 12,5nS
void systick_delay(unsigned long delay)
{
  volatile unsigned long remaining_time;
  unsigned long start_time  = NVIC_ST_CURRENT_R;

  do
  {
	  remaining_time = (start_time - NVIC_ST_CURRENT_R) & 0x00FFFFFF;
  }
  while(remaining_time <= delay);
}

void systick_delay_us(unsigned long delay)
{
  unsigned long i;

  for(i=0; i<delay; i++)
    systick_delay(80); 		//1uS для 80 MHz
}

void systick_delay_ms(unsigned long delay)
{
  unsigned long i;

  for(i=0; i<delay; i++)
    systick_delay(80000);  // 1mS для 80 MHz
}
