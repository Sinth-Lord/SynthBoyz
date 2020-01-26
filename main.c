#include "project.h"

//uint8 Status; 
uint16 byte_1;
uint16 byte_2;
uint16 bit_Mask = 0xFFF0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Start();
    UART_Clock_Start();

    for(;;)
    {
        // Get byte 1 (status message)
        byte_1 = UART_GetByte();
        
        // Note-On Messages
        if ((byte_1 & bit_Mask) == 0x90u)
        {
            UART_ClearRxBuffer();
            byte_2 = UART_GetByte();
            
            if (byte_2 == 60u)
            {
                LED_Write(1);    
            }
            else
            {
                LED_Write(0);    
            }
        }
        
        //Note_Off Messages
        else if ((byte_1 & bit_Mask) == 0x80u)
        {
            LED_Write(0);
        }
                
//        if((Status &= z) == 0x90u)
//        {
//            LED_Write(1);   
//        }
//        else if((Status &= z) == 0x80u)
//        {
//            LED_Write(0);    
//        }
    }
}

/* [] END OF FILE */
