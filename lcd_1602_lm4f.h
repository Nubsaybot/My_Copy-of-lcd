/***********************************
*
* www.fatihinanc.com
*
* Muhammed Fatih �NAN�
* 09.12.2012
*
* LM4F120 i�in 2x16 LCD K�t�phanesi
* Stellaris LaunchPad
*
***********************************/
/*
D4 -> PE0 0x01
D5 -> PE1 0x02
D6 -> PE2 0x04
D7 -> PE3 0x08

RS -> PE4 0x10
EN -> PE5 0x20

      PE6 0x40
      PE7 0x80
*/

#define RS 0x10
#define EN 0x20

#define delay_us(x)     systick_delay_us(x)
#define delay_ms(x)     systick_delay_ms(x)

#define LCD_DATA        GPIO_PORTE_DATA_R
#define LCD_CONTROL     GPIO_PORTE_DATA_R
//#define	EN_STROB()		LCD_EN(1),LCD_EN(0) //�������� EN-�� (�������� � ���������) //����� ������� ����� �������� �������� >140nS ��� 80 MHz systick_delay(12) '

#define	LCD_RS(x)       ( (x) ? (LCD_CONTROL |= RS) : (LCD_CONTROL &= ~RS) ) //if (x) then (LCD_CONTROL |= 0x01) else (LCD_CONTROL &= ~0x01)
#define LCD_EN(x)       ( (x) ? (LCD_CONTROL |= EN) : (LCD_CONTROL &= ~EN) ) //if (x) then (LCD_CONTROL |= 0x02) else (LCD_CONTROL &= ~0x02)


void lcd_cmd  		(unsigned char); // ��� �������� ��� ������ LCD
void lcd_clear		(void);          // ������� LCD
void lcd_puts   	(char*);   		 // ����� ������ �� LCD
void lcd_goto   	(char,char);     // ���������� ������� �������
void lcd_init   	(void);          // ��������� ������������� LCD
void lcd_putch  	(char);          // ����� ������� �� LCD
void lcd_en_strob 	(void);          // �������� EN-�� (�������� � ���������)
