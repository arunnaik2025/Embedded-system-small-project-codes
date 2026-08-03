#include<reg51.h>
sbit ADC_WR=P3^6;
sbit ADC_RD=P3^7;
sbit ADC_INTR=P3^5;
sbit FAN=P1^0;
unsigned count=0;
bit send_data=0;
unsigned char Temparature;
void ADC_init(void){
	ADC_WR=1;
	ADC_RD=1;
}
void UART_init(void){
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
void Timer0_ISR(void)interrupt 1{
	TH0=0xFC;
	TL0=0x66;
	count++;
	if(count>=1000){
		count=0;
		send_data=1;
	}
}
unsigned char ADC_Read(void){
	ADC_WR=0;
	delay();
	ADC_WR=1;
	while(ADC_INTR==1){
	}
	ADC_RD=0;
	Temparature=P2;
	ADC_RD=1;
	return Temparature;
}
void UART_Tx(unsigned char Temparature){
	SBUF=Temparature;
	while(TI==0){
	}
	TI=0;
}
void INT0_ISR(void)interrupt 0{
	TR0=0;
}
void main(void){
	unsigned char idel_value=20;
	ADC_init();
	TMOD=0x21;
	TH0=0xFC;
	TL0=0x66;
	EA=1;
	EX0=1;
	IT0=1;
	ET0=1;
	TR0=1;
	UART_init();
	while(1){
		if(send_data==1){
			send_data=0;
			Temparature=ADC_Read();
			UART_Tx(Temparature);
		}
		if(Temparature>idel_value){
			FAN=0;//on
	}
		else{
			FAN=1;//off
		}
  }
}
			
	
	