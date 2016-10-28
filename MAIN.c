/*
LCD Interfacing with TRK-KEA128 in 8 bit mode...
Connection : 

D0-D7 = PTF0-PTF7 (GPIOB)
RS = PTE4 GPIOB)
RW = PTE5 GPIOB)
EN = PTE6 (GPIOB)

*/

#include "SKEAZ1284.h"


#define LCD_PORT 0x0000FF00
#define RS  0x00010000
#define RW  0x00020000
#define EN  0x00040000
#define LCD_SHIFT 8

void delay(unsigned int);
void lcd_init();
void lcd_cmd(char);
void lcd_data(char);
void lcd_string(char *ch);
//void latch();

char str[] = "SANDIP MULE";
char str1[] = "BE_E&TC69";

int main()
{
WDOG_CS1 = 0x0;
GPIOB_PDDR = 0x0007FF00;
GPIOB_PIDR = 0x0007FF00;
lcd_init();
while(1)
{
lcd_cmd(0x01);
delay(500);
lcd_cmd(0x80);
delay(500);
lcd_string(str);
delay(500);
lcd_cmd(0xC0);
delay(500);
lcd_string(str1);
delay(500);
/*
lcd_data('S');
delay(10);
lcd_data('A');
delay(10);
lcd_data('N');
delay(10);
lcd_data('D');
delay(10);
lcd_data('I');
delay(10);
lcd_data('P');
delay(10);
*/
}
}

void delay(unsigned int itime)
{
unsigned int i,j;
for(i=0;i<=itime;i++)
for(j=0;j<=3000;j++);
}

void lcd_init()
{
//GPIOA_PCOR = EN;
//delay(100);//0.1 Sec delay
lcd_cmd(0x38);
delay(500);
lcd_cmd(0x0F); //for making LCD ON, cursor ON and cursor blinking ON.
delay(500);
lcd_cmd(0x06);  //for incrementing cursor position.
delay(100);
lcd_cmd(0x01);  //for clearing the display and return the cursor.
delay(100);
}

void lcd_cmd(char cmd)
{
GPIOB_PCOR = LCD_PORT;
GPIOB_PSOR = cmd << LCD_SHIFT;
GPIOB_PCOR = 0x00010000;
GPIOB_PCOR = 0x00020000;
GPIOB_PSOR = 0x00040000;
delay(100);
GPIOB_PCOR = 0x00040000;
delay(200);
}

void lcd_data(char data)
{
GPIOB_PCOR = LCD_PORT;
GPIOB_PSOR = data << LCD_SHIFT;
GPIOB_PSOR = 0x00010000;
GPIOB_PCOR = 0x00020000;
GPIOB_PSOR = 0x00040000;
delay(100);
GPIOB_PCOR = 0x00040000;
delay(100);
}

void lcd_string(char *ch)
{
	while(*ch != '\0')
	{
		lcd_data(*ch++);
	}
}

/*
void latch()				   //Enable pulse
{
	delay(100);
	GPIOB_PSOR = EN;
	delay(100);
	GPIOB_PCOR= EN;
	delay(100);
}
*/