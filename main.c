#include "project.h"

#define MIDI_Buffer_Size 4
int MIDI_Buffer[MIDI_Buffer_Size] = {0,0,0,0};

int bufferLength = 1;
int writeIndex = 0;

CY_ISR(MIDI_Interrupt)
{
    MIDI_Buffer[writeIndex] = UART_GetChar();
    writeIndex = (writeIndex + 1)&0x3;
    bufferLength = (bufferLength + 1)&0x3;
}

uint8 byte_1;  //Note on/off
uint8 byte_2;  //Note number
uint8 byte_3;  //Velocity
uint8 bit_Mask = 0xF0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    Clock_Start();
    UART_Start();
    Osc_Freq_Start();
    
    //interrupt initialization
    
    MIDI_Interrupt_Start();
    MIDI_Interrupt_StartEx(MIDI_Interrupt);
    MIDI_Interrupt_Enable();
    
    for(;;)
    {
        /* Place your application code here. */
        
        // Note on / Note off
        byte_1 = MIDI_Buffer[bufferLength];
        byte_2 = MIDI_Buffer[((bufferLength + 1)&0x3)];
        byte_3 = MIDI_Buffer[((bufferLength + 2)&0x3)];
        switch((byte_1 & bit_Mask))
        {
            case 0x80: Osc_Freq_StopBlock();
            break;
            case 0x90: Osc_Freq_Start();
            switch(byte_2)
            {
                case 60u: Osc_Freq_SetDivider(0x1AE7);
                break;
                case 61u: Osc_Freq_SetDivider(0x1964);
                break;
                case 62u: Osc_Freq_SetDivider(0x17F7);
                break;
                case 63u: Osc_Freq_SetDivider(0x169F);
                break;
                case 64u: Osc_Freq_SetDivider(0x155A);
                break;
                case 65u: Osc_Freq_SetDivider(0x1427);
                break;
                case 66u: Osc_Freq_SetDivider(0x1305);
                break;
                case 67u: Osc_Freq_SetDivider(0x11F4);
                break;
                case 68u: Osc_Freq_SetDivider(0x10F2);
                break;
                case 69u: Osc_Freq_SetDivider(0x0FFE);
                break;
                case 70u: Osc_Freq_SetDivider(0x0F19);
                break;
                case 71u: Osc_Freq_SetDivider(0x0E40);
                break;
                default: Osc_Freq_SetDivider(0x0000);
                break;
            }
            break;
        }
    }
}

/* [] END OF FILE */

