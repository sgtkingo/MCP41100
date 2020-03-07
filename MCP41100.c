#include "PICF18LF46K22_ConfigSFR.h"
#include "MCP41100_FunctionLib.h"

//declared init fce
void InitDevice(){
    OSCCON=0b01111100; //osc setting, 16 MHz, internal by FOSCH
    OSCTUNE=0x00; //PLLx4 OFF
    ANSELD=0x00;
    TRISD=0x00;
    
    //CS for 8x8LEDMATRIX
    ANSELAbits.ANSA0=0;
    TRISAbits.RA0=0;
    PORTAbits.RA0=1;
    
    //CS for MCP41100
    ANSELAbits.ANSA1=0;
    TRISAbits.RA1=0;
    PORTAbits.RA1=1;
}
//declared clear fce
void ClearDevice(){
    PORTD=0;
    LATD=0;
}
//declared test fce
void TestDevice(){
    delay_ms(1000);
    LATD=0xFF;
    delay_ms(1000);
    LATD=0x00;
}

void main(void) {
    InitDevice();
    ClearDevice();
    TestDevice();

    SPI_SET_CS(&PORTA,0b00000001,1); //RA0, 8x8LEDMATRIX
    SPI_SET_CS(&PORTA,0b00000010,1); //RA1, MCP41100
    
    Init_MCP41100(&PORTA,CS_PIN); //Set PORTA as CS manage port,pin
    //Send_Data_MCP41100(CMD_WRITE_PT0_MCP41xxx,0x7F);
    Set_Resistence_MCP41100(80000);
    delay_ms(5000);
    for(unsigned char val=0x00;val<0xFF;val++){
        Send_Data_MCP41100(CMD_WRITE_PT0_MCP41xxx,val);
        delay_ms(250);
    }
    LATD=0xFF;
    while(1){
        NOP();
    }
    return;
}
