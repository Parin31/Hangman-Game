#pragma large
#include <at89c5131.h>
#include <stdlib.h>
#include "lcd.h"		//Header file with LCD interfacing functions
#include "serial.c"	//C file with UART interfacing functions

unsigned int Randoms(unsigned int lower, unsigned int upper)
{
    unsigned int num;
		num	= (rand() % (upper - lower + 1)) + lower;
	return num;
        
    
}
unsigned int index( unsigned char temp[], unsigned int idx[], unsigned char ch)
{
	unsigned int i;
	unsigned int k=1;
	unsigned int len=0;
		for(i=1;i<=7;i++)
	{
		if(temp[i] == ch)
		{
			idx[k]=i;
			k=k+1;
			len = len +1;
		}
	}
	return len;
}


//Main function
void main(void)
{
	unsigned char ch=0;
	unsigned char temp[8];
	unsigned int idx[7]={0};
 code unsigned char str[100][8]= {"0acid111","0army111","0ball111","0beer111",
		"0boat111","0cash111","0city111","0door111","0drug111","0evil111","0farm111","0goal111","0hole111",
		"0iron111","0john111","0kent111","0logo111","0mass111","0nine111","0oral111","0pain111","0pubg111","0pure111","0race111","0rain111",
		"0snow111","0tank111","0user111","0vote111","0walk111","0yard111","0zero111","0zone111","0jazzy11","0pizza11","0adult11","0alarm11","0apple11","0bitch11","0beach11","0chair11","0china11","0death11","0earth11",
		"0flash11","0green11","0harry11","0input11","0japan11","0known11","0laugh11","0magic11","0money11","0noice11","0ocean11",
		"0paper11","0parin11","0phone11","0queen11","0roger11","0scope11","0teeth11","0urban11","0virus11","0wheel11","0world11","0yield11","0youth11",
		"0aniket1","0ayush11","0shaan11","0vineet1","0abroad1","0author1","0beauty1","0coffee1","0design1","0energy1","0father1","0french1","0global1",
		"0honest1","0island1","0jersey1","0lesson1","0matter1","0number1","0oxford1","0palace1","0planet1","0rating1","0school1","0twelve1","0unique1","0vision1",
		"0wholly1","0yellow1","0writer1","0switch1","0tender1"};
		
	
		
	unsigned int a;
	unsigned int i,j;
	unsigned int b;
	unsigned int c ;
	unsigned char cha;
	unsigned int corrguess, wrongguess,length;
  
	while(1)
	{
	 a = Randoms(0,99);
	 corrguess=0;
		wrongguess=0;
		length=0;
		for(j=0;j<=7;j++)
		{
			temp[j]=str[a][j];
		}
	
	for(i=1;i<=7;i++)
	{
		if(temp[i] !='1')
		{
			length= length +1;
		}
		else
		{
		break;
		}
	}
	
	//Call initialization functions
	lcd_init();
	uart_init();
	lcd_cmd(1);
	msdelay(10);
	lcd_cmd(133);
	msdelay(10);
	for(i=1;i<=length;i++)
	{
		lcd_write_char('_');
	}
	lcd_cmd(192);
	msdelay(10);
	lcd_write_string("WrongGuesses - 0");
	
	
	while(corrguess!=length && wrongguess!=6)
	{
			
			ch = receive_char();
		 
			idx[0]= index(temp,idx,ch);
		
		
		
		 if(idx[0]!=0)
		 {
			 for(i=1;i<=idx[0];i++)
			 {
			 corrguess= corrguess +1;
				 b= idx[i];
			 
			 c= 132 + b;
			 lcd_cmd(c);
			 lcd_write_char(ch);
			 transmit_char(ch);
			 temp[b] = '0';
			 }
		 }
		 else
		 {
			 wrongguess= wrongguess +1;
			 lcd_cmd(207);
			  cha = '0' + wrongguess;
			 lcd_write_char(cha);
		 }
			 
		
			msdelay(1000);
	}
	if(corrguess==length)
	{
		lcd_cmd(1);
		msdelay(10);
		lcd_cmd(132);
		lcd_write_string("You Won");
		
	}
	else if(wrongguess==6)
	{
		lcd_cmd(1);
		msdelay(10);
		lcd_cmd(132);
		lcd_write_string("You Lost");
		
	}
	for(j=0;j<7;j++)
	{
		idx[j]=0;
	}
	
	msdelay(5000);
}
	}
