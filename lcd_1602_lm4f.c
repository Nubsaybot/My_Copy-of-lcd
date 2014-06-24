
#include "inc/lm4f120h5qr.h"
#include "lcd_1602_lm4f.h"
#include "systick.h"

void lcd_en_strob(void)
{
	LCD_EN(1);
	systick_delay_ms(12);
	LCD_EN(0);
}

void lcd_putch(char c)
{
  LCD_RS(1);

  delay_ms(2);

  LCD_DATA = ((c & 0xF0) >> 4);
  lcd_en_strob();
  LCD_DATA =  (c & 0x0F);
  lcd_en_strob();
}

void lcd_cmd(unsigned char c)
{
  LCD_RS(0);

  LCD_DATA = ((c & 0xF0) >> 4);
  lcd_en_strob();
  LCD_DATA =  (c & 0x0F);
  lcd_en_strob();
}

void lcd_clear(void)
{
  lcd_cmd(0x01);
  delay_ms(10);
}

void lcd_puts(char* s)
{
  while(*s)
    lcd_putch(*s++);
}

void lcd_goto(char x, char y)
{
  if(x==1)
    lcd_cmd(0x80+((y-1)%16));
  else
    lcd_cmd(0xC0+((y-1)%16));
}

void lcd_init()
{
  volatile unsigned long delay;
  SYSCTL_RCGC2_R     |=  SYSCTL_RCGC2_GPIOE;	//включаем порт E
  delay = SYSCTL_RCGC2_R;
  GPIO_PORTE_AMSEL_R &= ~0xFF;					//отменяем аналоговые функции
  GPIO_PORTE_PCTL_R  &= ~0xFFFFFFFF;			//очищаем биты PCTL обычный порт ввода выводв
  GPIO_PORTE_DIR_R   |=  0xFF;					//направление
  GPIO_PORTE_AFSEL_R &= ~0xFF;					//отменяем альтернативные функции на порту
  GPIO_PORTE_DEN_R   |=  0xFF;					//просто включает конкретную ножку в работу

  systick_delay_ms(40);

  lcd_cmd(0x30);  // 4 Bit , Зift Satэr LCD
  lcd_cmd(0x0C);  // Эmleз Gizleniyor
  lcd_cmd(0x06);  // Saрa doрru yazma aktif
  lcd_cmd(0x80);  // LCD Birinci Satэr Konumunda
  lcd_cmd(0x28);  // 4 Bit , Зift Satэr LCD
  lcd_clear();    // Ekran clearniyor
}
