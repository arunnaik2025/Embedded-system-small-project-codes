#include<reg51.h>
sbit MOSI=P1^0;
sbit SS=P1^1;
sbit SCK=P1^2;
sbit MISO=P1^3;
void SPI_init(void);
void delay(void);
unsigned char SPI_Rx(void);
void SPI_String_Rx(char *str);
void SPI_Tx(unsigned char txdata);
void SPI_String_Tx(char *str);
bit passwordcheck(char *password,char *correct);
void SPI_init(void){
	SS=1;
	MOSI=0;
	SCK=0;
}
void delay(void){
	unsigned int i;
	unsigned int j;
	for(i=0; i<500; i++){
		for(j=0; j<1275; j++);
	}
}
unsigned char SPI_Rx(void){
	unsigned char rdata=0;
	unsigned char i=0;
	for(i=0; i<8; i++){
		SCK=1;
		delay();
		rdata<<=1;
		if(MISO){
			rdata|=0x01;
		}
		SCK=0;
		delay();
	}
	return rdata;
}
void SPI_String_Rx(char *str){
	while(1){
		*str=SPI_Rx();
		if(*str=='\r'){
			break;
		}
		str++;
	}
	*str='\0';
}
void SPI_Tx(unsigned char txdata){
	unsigned char i=0;
	for(i=0; i<8; i++){
		if(txdata&0x80){
			MOSI=1;
		}
		else{
			MOSI=0;
		}
		SCK=1;
		delay();
		SCK=0;
		delay();
		txdata<<=1;
	}
}
void SPI_String_Tx(char *str){
	while(*str!='\0'){
		SPI_Tx(*str);
		str++;
	}
}
bit  passwordcheck(char *password,char *correct){
	while(*password!='\0'&&*correct!='\0'){
		if(*password!=*correct){
			return 0;
		}
		password++;
		correct++;
	}
		if(*password=='\0'&&*correct=='\0'){
			return 1;
		}
		return 0;
}
void main(void){
unsigned char password[10];
unsigned char correct[]="1234";
	SPI_init();
	while(1){
		SPI_String_Rx(password);
		if(passwordcheck(password,correct)){
			SPI_String_Tx("Allow");
		}
		else{
			SPI_String_Tx("Not Allow");
		}
	}
}
			

			

	