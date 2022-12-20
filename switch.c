#include "switch.h"

void SW_Init(void)
{
    GPIO_Init(GPIOC, GPIO_PIN0 | GPIO_PIN1 | GPIO_PIN2, GPIO_Mode_IN_PU);
    
    UP_SW_Pressed = 0;
    SET_SW_Pressed = 0;
    DOWN_SW_Pressed = 0;
}

void SW_Update(void)
{
    static uint8_t UP_SW_Duration = 0;
    static uint8_t SET_SW_Duration = 0;
    static uint8_t DOWN_SW_Duration = 0;
    
    if(!GPIO_Get_Pin(GPIOC, GPIO_PIN0))
    {
        UP_SW_Duration++;
        if(UP_SW_Duration > 2)
        {
            UP_SW_Duration = 2;
            UP_SW_Pressed = 1;
            return;
        }
        UP_SW_Pressed = 0;
        return;
    }
    else if(!GPIO_Get_Pin(GPIOC, GPIO_PIN1))
    {
        SET_SW_Duration++;
        if(SET_SW_Duration > 2)
        {
            SET_SW_Duration = 2;
            SET_SW_Pressed = 1;
            return;
        }
        SET_SW_Pressed = 0;
        return;
    }
    else if(!GPIO_Get_Pin(GPIOC, GPIO_PIN2))
    {
        DOWN_SW_Duration++;
        if(DOWN_SW_Duration > 2)
        {
            DOWN_SW_Duration = 2;
            DOWN_SW_Pressed = 1;
            return;
        }
        DOWN_SW_Pressed = 0;
        return;
    }
    UP_SW_Pressed = 0;
    SET_SW_Pressed = 0;
    DOWN_SW_Pressed = 0;
    
    UP_SW_Duration = 0;
    SET_SW_Duration = 0;
    DOWN_SW_Duration = 0;
}
