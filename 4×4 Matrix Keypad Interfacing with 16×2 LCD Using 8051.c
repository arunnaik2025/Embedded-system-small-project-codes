#include<reg51.h>
#define KEYPAD P1
sbit RS=P0^1;
sbit RW=P0^2;
sbit EN=P0^3;
sbit C1=P1^4;
sbit C2=P1^5;
sbit C3=P1^6;
sbit C4=P1^7;
void delay(void){
	unsigned int i;
	unsigned int j;
	for(i=0; i<500; i++){
		for(j=0; j<1275; j++);
	}
}
unsigned char keypad_Read(void){
	KEYPAD=0xFE;
	if(C1==0){
		return '1';
	}
	if(C2==0){
		return '2';
	}
	if(C3==0){
		return '3';
	}
	if(C4==0){
		return 'A';
	}
	KEYPAD=0xFD;
	if(C1==0){
		return '4';
	}
	if(C2==0){
		return '5';
	}
	if(C3==0){
		return '6';
	}
	if(C4==0){
		return 'B';
	}
	KEYPAD=0xFB;
	if(C1==0){
		return '7';
	}
	if(C2==0){
		return '8';
	}
	if(C3==0){
		return '9';
	}
	if(C4==0){
		return 'C';
	}
	KEYPAD=0xF7;
	if(C1==0){
		return '*';
	}
	if(C2==0){
		return '0';
	}
	if(C3==0){
		return '#';
	}
	if(C4==0){
		return 'D';
	}
	return 0;
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
void LCD_init(void){
	LCD_command(0x38);
	LCD_command(0x0C);
	LCD_command(0x06);
	LCD_command(0x01);
}
void main(void){
	unsigned char value;
	LCD_init();
	while(1){
	  LCD_command(0x80);
		value=keypad_Read();
		if(value !=0){
		LCD_data(value);
	}
}
}
		 
	
	
