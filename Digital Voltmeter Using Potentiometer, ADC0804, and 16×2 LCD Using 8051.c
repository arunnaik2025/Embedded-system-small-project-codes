#include<reg51.h>
sbit ADC_WR=P3^6;
sbit ADC_RD=P3^7;
sbit ADC_INTR=P3^5;
sbit RS=P1^0;
sbit RW=P1^1;
sbit EN=P1^2;
unsigned char potentiometer;
void ADC_init(void);
void delay(void);
unsigned char ADC_Read(void);
void LCD_command(unsigned char cmd);
void LCD_data(unsigned char potentiometer);
void LCD_string(char *str);
void LCD_init(void);
void ADC_init(void){
	ADC_WR=1;
	ADC_RD=1;
}
void delay(void){
	unsigned int i;
	unsigned int j;
	for(i=0; i<500; i++){
		for(j=0; j<1275; j++);
	}
}
unsigned char ADC_Read(void){
	ADC_WR=0;
	delay();
	ADC_WR=1;
	while(ADC_INTR==1);
	ADC_RD=0;
	potentiometer=P2;
	ADC_RD=1;
	return potentiometer;
}
void LCD_command(unsigned char cmd){
	RS=0;
	RW=0;
	P0=cmd;
	EN=1;
	delay();
	EN=0;
}
void LCD_data(unsigned char potentiometer){
	RS=1;
	RW=0;
	P0=potentiometer;
	EN=1;
	delay();
	EN=0;
}
void LCD_string(char *str){
	while(*str!='\0'){
		LCD_data(*str);
		str++;
	}
}
void LCD_init(void){
	LCD_command(0x38);
	LCD_command(0x0C);
	LCD_command(0x06);
	LCD_command(0x01);
}
void main(void){
	ADC_init();
	LCD_init();
	while(1){
	LCD_command(0x01);
	LCD_command(0x80);
	LCD_string("potentiometer:");
	LCD_command(0xC0);
  potentiometer=ADC_Read();
	LCD_data((potentiometer/100)+'0');//example=156/100=1
	LCD_data(((potentiometer/10)%10)+'0');//156/10=15%10=5
	LCD_data((potentiometer%10)+'0');//156%10=6
	}
}

	
