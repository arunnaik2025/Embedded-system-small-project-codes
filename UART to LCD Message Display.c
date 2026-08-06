#include<reg51.h>
sbit RW=P1^0;
sbit RS=P1^1;
sbit EN=P1^2;
void UART_init(void);
void delay(void);
void LCD_command(unsigned char cmd);
void LCD_data(unsigned char ch);
unsigned char UART_Rx(void);
void UART_String_Rx(char *str);
void LCD_string(char *str);
void LCD_init(void);
void UART_init(void){
	TMOD=0x20;
	SCON=0x50;
	TH1=0xFD;
	TL1=0xFD;
	TR1=1;
}
void delay(void){
	unsigned int i;
	unsigned int j;
	for(i=0; i<500; i++){
		for(j=0; j<1275; j++);
	}
}
void LCD_command(unsigned char cmd){
	RS=0;
	RW=0;
	P2=cmd;
	EN=1;
	delay();
	EN=0;
}
void LCD_data(unsigned char ch){
	RS=1;
	RW=0;
	P2=ch;
	EN=1;
	delay();
	EN=0;
}
unsigned char UART_Rx(void){
	unsigned char ch;
	while(RI==0);
	ch=SBUF;
	RI=0;
	return ch;
}
void UART_String_Rx(char *str){
	while(1){
		*str=UART_Rx();
		if(*str=='\r'){
			break;
		}
		str++;
	}
	*str='\0';
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
	unsigned char value[20]="Hello Arun";
	UART_init();
	LCD_init();
	LCD_command(0x80);
	UART_String_Rx(value);
	LCD_string(value);
	while(1){
	}
}
	
		