
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H
#include<util/delay.h>
#include <stddef.h>

#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef   __cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef   __cplusplus
}
#endif /* __cplusplus */

#endif   /* XC_HEADER_TEMPLATE_H */

// define
#define EXMEM_ADD 0x1100
// CS offset
#define CS0 0
#define CS1 1
#define CS2 2
#define CS3 3
#define CS4 4
#define CS5 5
#define CS6 6
#define CS7 7
#define CS8 8
#define CS9 9
#define CS10 10
#define CS11 11
#define CS12 12
#define CS13 13
#define CS14 14
#define CS15 15
#define CS16 16
#define CS17 17
#define CS18 18
#define CS19 19

// define external device
#define LED0 *(unsigned char *) (EXMEM_ADD+CS0)
#define LED1 *(unsigned char *) (EXMEM_ADD+CS1)
#define LED2 *(unsigned char *) (EXMEM_ADD+CS2)
#define LED3 *(unsigned char *) (EXMEM_ADD+CS3)

#define LED7D1 *(unsigned char *) (EXMEM_ADD+CS4)
#define LED7D2 *(unsigned char *) (EXMEM_ADD+CS5)
#define LED7D3 *(unsigned char *) (EXMEM_ADD+CS6)
#define LED7D4 *(unsigned char *) (EXMEM_ADD+CS7)

#define LED7IDCTR *(unsigned char *) (EXMEM_ADD+CS8)//Open/Close transistor siuu
#define LED7IDDATA *(unsigned char *) (EXMEM_ADD+CS9)// ASCII for 7SEG

#define RELAYMAP *(unsigned char *) (EXMEM_ADD+CS10)
#define RELAY_ACTIVATION (*(volatile unsigned char *) (EXMEM_ADD+CS10) = *(unsigned char*)(&rl))
#define MOTOR_ACTIVATION (*(volatile unsigned char *) (EXMEM_ADD+CS13) = *(unsigned char*)(&motors))
#define READ_KEY (*(unsigned char*)(&buttons) = *(volatile unsigned char *) (EXMEM_ADD+CS14))

#define LCD_DATA *(unsigned char *) (EXMEM_ADD+CS11)
#define LCD_COMMAND *(unsigned char *) (EXMEM_ADD+CS12)

#define LCD_HE (PORTG|=(1<<3))
#define LCD_LE (PORTG&=~(1<<3))

#define DS18B20 0
#define OneWire_High (PORTB|=(1<<DS18B20)) //Output High
#define OneWire_LOW (PORTB&=~(1<<DS18B20)) //Output Low
#define OneWire_Master (DDRB|=(1<<DS18B20))//Configure Out
#define OneWire_Free (DDRB&=~(1<<DS18B20)) // Configure In
#define OneWire_Status (PINB&(1<<DS18B20))

char OneWire_Reset(void){
    char Presence;
    OneWire_Master;
    OneWire_LOW;
    __delay_us(480);
    OneWire_Free;
    __delay_us(80);
    Presence = OneWire_Status;
}



struct bits{
    unsigned char RL0 :1;
    unsigned char RL1 :1;
    unsigned char RL2 :1;
    unsigned char RL3 :1;
    unsigned char RL4 :1;
    unsigned char RL5 :1;
    unsigned char RL6 :1;
    unsigned char RL7 :1;
}relays;

union rls_full{
    unsigned char relayall;
    struct bits relays;
}rl;
struct buts{
    unsigned char DC1 : 2 ;
    unsigned char DC2 : 2 ;
   // unsigned char DCFREE : 4 ;
}motors;

struct bats{
    unsigned char LEFT  :1;
    unsigned char RIGHT :1;
    unsigned char UP    :1;
    unsigned char DOWN  :1;
    unsigned char GO    :1;
    unsigned char BTN1  :1;
    unsigned char BTN2  :1;
    unsigned char BTN3  :1;
}buttons;

void lcd_init(){
LCD_COMMAND = 0x38; LCD_HE; _delay_us(1); LCD_LE; _delay_us(1);//Function Set
//LCD_COMMAND = 0x3C; LCD_HE; _delay_us(1); LCD_LE; _delay_us(1);//Function Set
_delay_us(200);
LCD_COMMAND = 0x0C; LCD_HE; _delay_us(1); LCD_LE; _delay_us(1);//Display ON/OFF Control
_delay_us(200);
LCD_COMMAND = 0x06; LCD_HE; _delay_us(1); LCD_LE; _delay_us(1);//Entry Mode Set
_delay_us(200);
LCD_COMMAND = 0x01; LCD_HE; _delay_us(1); LCD_LE; _delay_us(1);//Clear Display
_delay_ms(20);
}
void lcd_gotoxy( unsigned x, unsigned y, const char *str)
{
    unsigned char address;
    int i=0;
    switch (x)
    {
        case 0: address = 0x80; break;
        case 1: address = 0xC0; break;
        case 2: address = 0x94; break;
        case 3: address = 0xD4; break;
    }
    LCD_COMMAND = address + y; LCD_HE ; _delay_us(1) ; LCD_LE ; _delay_us(50) ;
    while(*(str)!= '\0')
    {
        LCD_DATA = *str; LCD_HE ; _delay_us(1) ; LCD_LE ; _delay_us(50) ;
        *(++str);
        //*str='a';
    }
}


typedef struct Linker{
    char MenuID;
    struct Linker *pre;
    char title[20];
//-------------------
    char list1[20];
    struct Linker *menulist1;void (*ActivationON)(char, char);
    
    char list2[20];
    struct Linker *menulist2;void (*ActivationOFF)(char, char);
    
    char list3[20];
    struct Linker *menulist3;
    
    




}Menu;
Menu MainMenu,
        SensorMenu, TemperatureMenu,HumidityMenu,
            ActuatorMenu,
                RelaysMenu,
                MotorsMenu,Motor1Menu,Motor2Menu,
                LedMenu, LedsetMenu,
        SettingMenu;

/*----------------------------------------------------------------------------*/

#define ON 1
#define OFF 0

#define Device_Relay  0
#define Device_Motor1 1
#define Device_Motor2 2
#define Device_Led    3

void ActuatorActivation(char Device, char Status)
{
    switch(Device)
    {
        case Device_Relay: if(Status) rl.relayall=0xff;
                           else rl.relayall=0x00;
                           RELAY_ACTIVATION;
                           break;
        case Device_Motor1:if(Status) motors.DC1 = 0x01;
                           else motors.DC1 = 0;
                           MOTOR_ACTIVATION;
                           break;
        case Device_Motor2:if(Status) motors.DC2 = 2;
                           else motors.DC2 = 0;
                           MOTOR_ACTIVATION;
                           break;
        case Device_Led :  if(Status) LED0=0xff;
                           else LED0=0x55;
                           break;
        
    }
}
/*----------------------------------------------------------------------------*/


Menu MainMenu={
    NULL,
    NULL,
    "     MAIN MENU   ",
    "   SENSORS       ",&SensorMenu,NULL,
    "   ACTUATOR      ",&ActuatorMenu,NULL,
    "   SETTING       ",&SettingMenu,


};
/*----------------------------------------------------------------------------*/
Menu SensorMenu={
    NULL,
    &MainMenu,
    "     SENSORS     ",
    "   Temperature   ",&TemperatureMenu,NULL,
    "   Humidity      ",&HumidityMenu,NULL,
    "   Date & Time   ",NULL


};
Menu TemperatureMenu={
    NULL,
    &SensorMenu,
    "     TEMPERATURE  ",
    "   ON             ",NULL,NULL,
    "   OFF            ",NULL,NULL,
    "   Setup          ",NULL


};
Menu HumidityMenu={
    NULL,
    &SensorMenu,
    "     Humidity     ",
    "   ON             ",NULL,NULL,
    "   OFF            ",NULL,NULL,
    "   Setup          ",NULL


};

/*----------------------------------------------------------------------------*/
Menu ActuatorMenu={
    NULL,
    &MainMenu,
    "     Actuators   ",
    "   Relays        ",&RelaysMenu,NULL,
    "   Motors        ",&MotorsMenu,NULL,
    "   LEDs          ",&LedMenu


};

Menu RelaysMenu={
    Device_Relay,
    &ActuatorMenu,
    "     Relays      ",
    "   ON            ",NULL,&ActuatorActivation,
    "   OFF           ",NULL,&ActuatorActivation,
    "                 ",NULL


};
/*----------------------*/
Menu MotorsMenu={
    NULL,
    &ActuatorMenu,
    "     Motors      ",
    "   Motor 1       ",&Motor1Menu,NULL,
    "   Motor 2       ",&Motor2Menu,NULL,
    "                 ",NULL


};
Menu Motor1Menu={
    Device_Motor1,
    &MotorsMenu,
    "     Motor1      ",
    "   ON            ",NULL,&ActuatorActivation,
    "   OFF           ",NULL,&ActuatorActivation,
    "                 ",NULL


};
Menu Motor2Menu={
    Device_Motor2,
    &MotorsMenu,
    "     Motor2      ",
    "   ON            ",NULL,&ActuatorActivation,
    "   OFF           ",NULL,&ActuatorActivation,
    "                 ",NULL


};
//--------------------------
Menu LedMenu={
    Device_Led,
    &ActuatorMenu,
    "     LEDs        ",
    "   ON            ",NULL,&ActuatorActivation,
    "   OFF           ",NULL,&ActuatorActivation,
    "                 ",NULL


};
/*----------------------------------------------------------------------------*/
Menu SettingMenu={
    NULL,
    &MainMenu,
    "     Setting     ",
    "   SPEED         ",NULL,NULL,
    "   CHANNEL       ",NULL,NULL,
    "   TIME          ",NULL


};
