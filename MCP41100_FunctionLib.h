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
 * File:   MCP41100_FunctionLib.h
 * Author: Jiri Konecny
 * Comments:
 * Revision history: 1.0
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MCP41100_FUNCTION_LIB
#define	MCP41100_FUNCTION_LIB

#include "SPI_PICLIB.h"

#define CMD_WRITE_ALL_MCP41xxx 0b00010011
#define CMD_WRITE_PT0_MCP41xxx 0b00010001
#define CMD_WRITE_PT1_MCP41xxx 0b00010010

#define CMD_SHUTDOWN_MCP41xxx 0b00100000

unsigned char *PORT_CS=0x00; //PORT for CS
unsigned char PIN_CS=0x00; //PIN for CS 

void Init_MCP41100(unsigned char const *port_cs, unsigned char const cs_pin_value);
void Send_Data_MCP41100(unsigned char cmd,unsigned char data);
void Set_Resistence_MCP41100(unsigned long int resistence);
void ShutDown_MCP41100();

void Init_MCP41100(unsigned char const *port_cs, unsigned char const cs_pin_value){
    PORT_CS=port_cs;
    PIN_CS=cs_pin_value;
    
    //SPI_SET_CS(PORT_CS,PIN_CS,0);
    SPI_SET_CS(PORT_CS,PIN_CS,1);
    
    SPI_INIT();
    SPI_PAUSE(1000);
    
    Send_Data_MCP41100(CMD_WRITE_PT0_MCP41xxx,0x00);
}

void Send_Data_MCP41100(unsigned char cmd,unsigned char data){
    SPI_SET_CS(PORT_CS,PIN_CS,0);
    SPI_WRITE(cmd);
    SPI_WRITE(data);
    SPI_SET_CS(PORT_CS,PIN_CS,1);
    
    SPI_PAUSE(1000);
}

void Set_Resistence_MCP41100(unsigned long int resistence){
    float proc=0;
    unsigned char bit8_result=0;
    proc=((float)(resistence)/100000);
    bit8_result=(proc*0xFF);
    Send_Data_MCP41100(CMD_WRITE_PT0_MCP41xxx,bit8_result);
}

void ShutDown_MCP41100(){
    Send_Data_MCP41100(CMD_SHUTDOWN_MCP41xxx,0x00);
}

#endif	/* MCP41100_FUNCTION_LIB */

