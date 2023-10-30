/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include<util/delay.h>
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

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */


#define DS18B20 0 // Connect PortB pin "B0" to DS18B20 pin "OUT"
#define OneWire_High (PORTB|=(1<<DS18B20)) //Output High
#define OneWire_LOW (PORTB&=~(1<<DS18B20)) //Output Low
#define OneWire_Master (DDRB|=(1<<DS18B20))//Configure Out
#define OneWire_Free (DDRB&=~(1<<DS18B20)) // Configure In
#define OneWire_Status (PINB&(1<<DS18B20))//Input Data Register
char OneWire_Reset(void){
    char Presence;
    OneWire_Master;
    OneWire_LOW;
    _delay_us(480);
    OneWire_Free;
    _delay_us(80);
    Presence = OneWire_Status;
    _delay_us(60);
    return Presence;
}
void Write1Byte(unsigned char byte){
    unsigned char i;
    for(i=0;i<8;i++)
    {
        OneWire_Master;
        if(byte&0x01)
        {
            OneWire_LOW;// Master Write 1
            _delay_us(15);
            OneWire_Free;
            _delay_us(45);
            _delay_us(50);//End Writing
        }
        else
        {
            OneWire_LOW;// Master Write 0
            _delay_us(60);
            OneWire_Free;
            _delay_us(30);
            
            
        }
        byte = byte>>1;
    }



}

char Read1Byte(void){
    unsigned char i, byte;
    for(i=0;i<8;i++)
    {
        OneWire_Master;
        OneWire_LOW;
        _delay_us(15);
        OneWire_Free;
        _delay_us(15);
         byte = byte>>1;
        byte =byte | (OneWire_Status<<7);
        _delay_us(30);
    
    
    }
    return byte;


}
unsigned int ReadTemp(void){
    unsigned char data[2];
    if(!OneWire_Reset())
    {
        Write1Byte(0xCC);//Skip ROM
        Write1Byte(0x44);//Convert Temp
        OneWire_Free;
        _delay_ms(750);
        OneWire_Reset();// Reset and Read [OneWire_Status]
        Write1Byte(0xCC);//Skip ROM
        Write1Byte(0xBE);//Read SCATCHPAD
        data[0]=Read1Byte();
        data[1]=Read1Byte();
        return (data[0]+data[1]*256)*0.0625;
        
    }
    else 
        return 0;
}