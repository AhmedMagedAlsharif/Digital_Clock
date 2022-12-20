#include "timer_basic.h"

void (*TOVF0_CallbackPtr)(void) = 0;
void (*OC0_CallbackPtr)(void) = 0;

void (*TOVF1_CallbackPtr)(void) = 0;
void (*OCA1_CallbackPtr)(void) = 0;
void (*OCB1_CallbackPtr)(void) = 0;
void (*IC1_CallbackPtr)(void) = 0;

void Timer0_init(Timer0_Mode_t Mode, Timer_Prescaler_t Prescaler)
{
    TCNT0 = 0;
    
    TCCR0 = (Mode|(Prescaler & 0x07));
}

void Timer0_Set_Preload_Value(uint8_t Value)
{
    TCNT0 = Value;
}
void Timer0_Set_OutputCompare_Value(uint8_t Value)
{
    OCR0 = Value;
}

uint8_t Timer0_Get_TimerCounter_Value(void)
{
    return TCNT0;
}

uint8_t Timer0_Get_Overflow_Flag(void)
{
    uint8_t ret;
    if(TIFR & 0x01)
    {
        /*clear flag*/
        TIFR |= (1<<TOV0);
        ret = 1;
    }
    else
    {
        ret = 0;
    }
    return ret;
}
uint8_t Timer0_Get_OutputCompare_Flag(void)
{
    uint8_t ret;
    if(TIFR & 0x02)
    {
        TIFR |= (1<<OCF0);
        ret = 1;
    }
    else
    {
        ret = 0;
    }
    return ret;
}

void Timer0_Enable_OutputCompare_Interrupt(void)
{
    TIMSK |= (1<<OCIE0);
}
void Timer0_Disable_OutputCompare_Interrupt(void)
{
    TIMSK &= ~(1<<OCIE0);
}
void Timer0_Enable_Overflow_Interrupt(void)
{
    TIMSK |= (1<<TOIE0);
}
void Timer0_Disable_Overflow_Interrupt(void)
{
    TIMSK &= ~(1<<TOIE0);
}

void Timer0_OverFlow_INT_Callback(void (*funPtr)(void))
{
    TOVF0_CallbackPtr = funPtr;
}

ISR (TIMER0_OVF_vect)
{
    if(TOVF0_CallbackPtr != 0)
        TOVF0_CallbackPtr();
}
void Timer0_OutputCompare_INT_Callback(void (*funPtr)(void))
{
    OC0_CallbackPtr = funPtr;
}

ISR (TIMER0_COMP_vect)
{
    if(OC0_CallbackPtr != 0)
        OC0_CallbackPtr();
}

void Timer1_init(Timer1_Mode_t Mode, Timer_Prescaler_t Prescaler)
{   
    TCNT1 = 0x0000;
    
    TCCR1A = (uint8_t)Mode;
    TCCR1B = (((uint8_t)(Mode >> 8))|(Prescaler & 0x07));
}

void Timer1_Set_Preload_Value(uint16_t Value)
{
    uint8_t sreg;
    sreg = SREG;
    cli();
    TCNT1 = Value;
    SREG = sreg;
}
void Timer1_Set_OutputCompareA_Value(uint16_t Value)
{
    uint8_t sreg;
    sreg = SREG;
    cli();
    OCR1A = Value;
    SREG = sreg;
}
void Timer1_Set_OutputCompareB_Value(uint16_t Value)
{
    uint8_t sreg;
    sreg = SREG;
    cli();
    OCR1B = Value;
    SREG = sreg;
}
void Timer1_Set_InputCapture_Value(uint16_t Value)
{
    uint8_t sreg;
    sreg = SREG;
    cli();
    ICR1 = Value;
    SREG = sreg;
}

uint16_t Timer1_Get_TimerCounter_Value(void)
{
    uint8_t sreg;
    uint16_t ret;
    sreg = SREG;
    cli();
    ret = TCNT1;
    SREG = sreg;
    return ret;
}

uint8_t Timer1_Get_Overflow_Flag(void)
{
    uint8_t ret;
    if(TIFR & 0x04)
    {
        TIFR |= (1<<TOV1);
        ret = 1;
    }
    else
    {
        ret = 0;
    }
    return ret;
}
uint8_t Timer1_Get_OutputCompareA_Flag(void)
{
    uint8_t ret;
    if(TIFR & 0x10)
    {
        TIFR |= (1<<OCF1A);
        ret = 1;
    }
    else
    {
        ret = 0;
    }
    return ret;
}
uint8_t Timer1_Get_OutputCompareB_Flag(void)
{
    uint8_t ret;
    if(TIFR & 0x08)
    {
        TIFR |= (1<<OCF1B);
        ret = 1;
    }
    else
    {
        ret = 0;
    }
    return ret;
}
uint8_t Timer1_Get_InputCapture_Flag(void)
{
    uint8_t ret;
    if(TIFR & 0x20)
    {
        TIFR |= (1<<ICF1);
        ret = 1;
    }
    else
    {
        ret = 0;
    }
    return ret;
}

void Timer1_Enable_Overflow_Interrupt(void)
{
    TIMSK |= (1<<TOIE1);
}
void Timer1_Disable_Overflow_Interrupt(void)
{
    TIMSK &= ~(1<<TOIE1);
}
void Timer1_Enable_OutputCompareA_Interrupt(void)
{
    TIMSK |= (1<<OCIE1A);
}
void Timer1_Disable_OutputCompareA_Interrupt(void)
{
    TIMSK &= ~(1<<OCIE1A);
}
void Timer1_Enable_OutputCompareB_Interrupt(void)
{
    TIMSK |= (1<<OCIE1B);
}
void Timer1_Disable_OutputCompareB_Interrupt(void)
{
    TIMSK &= ~(1<<OCIE1B);
}
void Timer1_Enable_InputCapture_Interrupt(void)
{
    TIMSK |= (1<<TICIE1);
}
void Timer1_Disable_InputCapture_Interrupt(void)
{
    TIMSK &= ~(1<<TICIE1);
}

void Timer1_OverFlow_INT_Callback(void (*funPtr)(void))
{
    TOVF1_CallbackPtr = funPtr;
}

ISR (TIMER1_OVF_vect)
{
    if(TOVF1_CallbackPtr != 0)
        TOVF1_CallbackPtr();
}

void Timer1_OutputCompareA_INT_Callback(void (*funPtr)(void))
{
    OCA1_CallbackPtr = funPtr;
}

ISR (TIMER1_COMPA_vect)
{
    if(OCA1_CallbackPtr != 0)
        OCA1_CallbackPtr();
}

void Timer1_OutputCompareB_INT_Callback(void (*funPtr)(void))
{
    OCB1_CallbackPtr = funPtr;
}

ISR (TIMER1_COMPB_vect)
{
    if(OCB1_CallbackPtr != 0)
        OCB1_CallbackPtr();
}

void Timer1_InputCapture_INT_Callback(void (*funPtr)(void))
{
    IC1_CallbackPtr = funPtr;
}

ISR (TIMER1_CAPT_vect)
{
    if(IC1_CallbackPtr != 0)
    {
        IC1_CallbackPtr();
    }
}
