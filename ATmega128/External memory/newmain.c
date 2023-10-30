


#include <xc.h>
#include "userdef.h"
#define F_CPU 1000000
#include<util/delay.h>

unsigned char SegCode[] = {0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XF8,
    0X80, 0X90, 0X88, 0X83, 0XC6, 0XA1, 0X86, 0X8E};

void SevenSegDisplay(unsigned int value){
    LED7D1 = SegCode[value%10];
    LED7D2 = SegCode[(value/10)%10];
    LED7D3 = SegCode[(value/100)%10];
    LED7D4 = SegCode[(value/1000)%10];
    
}
void SevenSegDisplayScan(unsigned int value){
    LED7IDDATA = SegCode[value%10];
    LED7IDCTR  = 0xFE;
    _delay_ms(50);
    LED7IDCTR  = 0xFF;
 /////////////////////////////////           
    LED7IDDATA = SegCode[(value/10)%10];
    LED7IDCTR  = 0xFD;
    _delay_ms(50);
    LED7IDCTR  = 0xFF;
//////////////////////////////////
    LED7IDDATA = SegCode[(value/100)%10];
    LED7IDCTR  = 0xFB;
    _delay_ms(50);
    LED7IDCTR  = 0xFF;
//////////////////////////////////
    LED7IDDATA = SegCode[(value/1000)%10];
    LED7IDCTR  = 0xF7;
    _delay_ms(50);
    LED7IDCTR  = 0xFF;
}
void MenuDisplay(Menu *x, unsigned char select){
    lcd_gotoxy(0,0,x->title);
    lcd_gotoxy(1,0,x->list1);
    lcd_gotoxy(2,0,x->list2);
    lcd_gotoxy(3,0,x->list3);
    lcd_gotoxy(select,0,">");
}
void main(void) {
    MCUCR |= 0x80;
    DDRG = 0b11111;
    unsigned char select = 1;
    //RELAYMAP = 0x55;
    SevenSegDisplay(4675);
    lcd_init();
    //char c[]="siuuuu";
  
    //RELAY_ACTIVATION;

   Menu *menu ;
   menu = &MainMenu;
 MenuDisplay(menu, select);
   while(1){
       READ_KEY;
       if(!buttons.DOWN)
       {
           while(!buttons.DOWN)READ_KEY; 
           select = (select==3)? 1 : select+1;
            MenuDisplay(menu, select);
       }
        if(!buttons.UP)
        {
            while(!buttons.UP)READ_KEY; 
            select = (select==1)? 3 : select-1;
             MenuDisplay(menu, select);
        }
        if(!buttons.RIGHT)
        {
            while(!buttons.RIGHT)READ_KEY; 
            switch(select)
            {
                case 1: menu =(menu->menulist1 == NULL)?menu: menu->menulist1;break;
                case 2: menu =(menu->menulist2 == NULL)?menu: menu->menulist2;break;
                case 3: menu =(menu->menulist3 == NULL)?menu: menu->menulist3;break;
            }
             MenuDisplay(menu, select);
        }
        if(!buttons.LEFT)
        {
            while(!buttons.LEFT)READ_KEY; 
            
            menu =(menu->pre == NULL)?menu: menu->pre;
            MenuDisplay(menu, select);
        }
       
         if(!buttons.GO)
        {
            while(!buttons.GO)READ_KEY; 
            switch(select)
            {
                case 1: if (menu->ActivationON!=NULL) menu->ActivationON(menu->MenuID,1);
                break;
                case 2: if (menu->ActivationOFF!=NULL) menu->ActivationOFF(menu->MenuID,0);
                break;
            } 

        }     
       if(!OneWire_Reset())
       lcd_gotoxy(0,0,"OK");
       else
           lcd_gotoxy(0,0,"Not found");
       
       
   }
    
   //LCD_DATA = 0x41;
    //LCD_HE; _delay_us(1); LCD_LE; _delay_us(1);

   /* while(1){
          READ_KEY;
    if(!buttons.GO){
        
        while(!buttons.GO) READ_KEY;
         
    motors.DC1 = 0x01;
            MOTOR_ACTIVATION;
    }
    if(!buttons.LEFT){
        while(!buttons.LEFT);
          
    motors.DC1 = 0x01;
            MOTOR_ACTIVATION;
    }

  }*/  
    
    
}
