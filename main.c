// либа работает проверил 08,06,14
#include "inc/lm4f120h5qr.h"

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "lcd_1602_lm4f.h"
#include "systick.h"
#include "pll.h"

unsigned long cpu_freq;

int main(void)
{

  pll_init();
  systick_init();

  set_cpu_freq(2,0);         // 80 MHz
  cpu_freq = get_cpu_freq();

  lcd_init();
  delay_ms(1000);

  lcd_goto(1,1);
  lcd_puts("LM4F120LaunchPad");
  lcd_goto(2,5);
  lcd_puts("POBEDA");

  while(1);
}

