#include <xc.h>

#include "system.h"

#include "usb.h"
#include "usb_device.h"
#include "usb_device_cdc.h"

#include "spi.h"

#define _XTAL_FREQ 48000000

static uint8_t readBuffer[CDC_DATA_OUT_EP_SIZE];
static uint8_t writeBuffer[CDC_DATA_IN_EP_SIZE];
static uint8_t stanje[CDC_DATA_IN_EP_SIZE];


MAIN_RETURN main(void)
{    
//    stanje[0]='X';
//    stanje[2]=',';
//    stanje[3]=' ';
//    stanje[4]='Y';
//    stanje[6]=' ';
//    stanje[7]='i';
//    stanje[8]=' ';
//    stanje[9]='Z';
    
//        /**
//    LATx registers
//    */   
//    LATA = 0x00;    
//    LATB = 0x00;    
//    LATC = 0x00;    
//
//    /**
//    TRISx registers
//    */    
//    TRISA = 0x30;
//    TRISB = 0xF0;
//    TRISC = 0xFF;
//
//    /**
//    ANSELx registers
//    */   
//    ANSELC = 0x0F;
//    ANSELB = 0x00;
//    ANSELA = 0x10;
//
//    /**
//    WPUx registers
//    */ 
//    WPUB = 0xF0;
//    WPUA = 0x38;
//    OPTION_REGbits.nWPUEN = 0;
//
//    
//    /**
//    APFCONx registers
//    */
//    APFCON = 0x00;
    
    SYSTEM_Initialize(SYSTEM_STATE_USB_START);
    USBDeviceInit();
    USBDeviceAttach();
    CDCInitEP();
    CDCSetBaudRate(1200);
    
    //SPI_Init();

    // set RC5 == SYNC as output
    ANSC2 = 0; 
    ANSC3 = 0;
    TRISB7 = 0;
    TRISC2 = 0;
    TRISC3 = 0;
    TRISC4 = 0;
    TRISC5 = 0;
    
    RC2 = 0;
    RC3 = 0;
    RC4 = 0;
    RC5 = 0;
    RB7 = 1;
    while(1){
        
        if( USBUSARTIsTxTrfReady() == true){
            uint8_t numBytesRead, a;
            
            numBytesRead = getsUSBUSART(readBuffer, sizeof(readBuffer));
            if(numBytesRead > 0){

//              a=(readBuffer[0]-48)*10+readBuffer[1]-48;
                a=readBuffer[0];
                switch(a){
                    
                    case 10: //gasi A=>X0 je spojen
                        RC2=0;
                        RB7 = 0;
                        __delay_ms(1000);
                        RB7=1;
                        break;
                    case 11: //pali A=>X1 je spojen
                        RC2=1;
                        RB7 = 0;
                        __delay_ms(333);
                        RB7=1;
                        __delay_ms(333);
                        RB7 = 0;
                        __delay_ms(333);
                        RB7=1;
                        break;
                    case 20: //gasi B=>Y0 je spojen
                        RC3=0;
                        RB7 = 0;
                        __delay_ms(1000);
                        RB7=1;
                        break;
                    case 21: //pali B=>Y1 je spojen
                        RC3=1;
                        RB7 = 0;
                        __delay_ms(333);
                        RB7=1;
                        __delay_ms(333);
                        RB7 = 0;
                        __delay_ms(333);
                        RB7=1;
                        break;
                    case 30: //gasi C=>Z0 je spojen
                        RC4=0;
                        RB7 = 0;
                        __delay_ms(1000);
                        RB7=1;
                        break;
                    case 31: //pali C=>Z1 je spojen
                        RC4=1;
                        RB7 = 0;
                        __delay_ms(333);
                        RB7=1;
                        __delay_ms(333);
                        RB7 = 0;
                        __delay_ms(333);
                        RB7=1;
                        break;
                    default:
                        RB7 = 0;
                        __delay_ms(333);
                        RB7=1;
                        __delay_ms(333);
                        RB7 = 0;
                        __delay_ms(333);
                        RB7 = 0;
                        __delay_ms(333);
                        RB7=1;
                        __delay_ms(333);
                        RB7 = 0;
                        __delay_ms(333);
                        RB7=1;
                        break;
                }
//                for(i=0; i<numBytesRead; i++){
//                    a = readBuffer[i];
//                    SPI_Write(a);
//                    writeBuffer[i] = readBuffer[i];
//                }
//                writeBuffer[0]='a';
                // SYNC rising edge
               //RC5 = 1;
//                writeBuffer[0]='T';
//                writeBuffer[1]='e';
//                writeBuffer[2]='s';
//                writeBuffer[3]='t';
//                writeBuffer[4]='\0';
//                putUSBUSART(writeBuffer, numBytesRead);
            
//                stanje[1]=RC2+48;
//                stanje[5]=RC3+48;
//                stanje[10]=RC4+48;
//                stanje[11]='\0';
                stanje[0]=RC2;
                stanje[1]=RC3;
                stanje[2]=RC4;
                stanje[3]=a;
                putUSBUSART(stanje, 4);
            }
        }
        CDCTxService();
    }
}
