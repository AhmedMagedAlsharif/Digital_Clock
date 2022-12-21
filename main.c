#include "main.h"

static int8_t Sec = 0;
static int8_t Min = 0;
static int8_t Hor = 12;

static uint8_t Hor_Blink = 0;
static uint8_t Min_Blink = 0;

void Clock_Update(void);
void Setting_Task(void);

int main(void)
{
    SSD_Init();
    SW_Init();
    SCH_Init_T0();

	SCH_Add_Task(&Clock_Update, 0, 1, 500);
    SCH_Add_Task(&SW_Update, 0, 1, 20);
    SCH_Add_Task(&Setting_Task, 0, 1, 250);
    SCH_Add_Task(&SSD_Update, 0, 1, 5);

	SCH_Start();
    while(1)
    {
        SCH_Dispatch_Tasks();
    }
    return 0;
}

void Clock_Update(void)
{
    static uint8_t time_temp = 0;
    
    time_temp++;
    if(time_temp >= 2)
    {
        time_temp = 0;
        Sec++;
        if(Sec > 59)
        {
            Sec = 0;
            Min++;
            if(Min > 59)
            {
                Min = 0;
                Hor++;
                if(Hor > 12)
                {
                    Hor = 1;
                }
            }
        }
    }
    SSD_Dottoggle(2);
    SSD_SetInt(Hor, 1, 2);
    SSD_SetInt(Min, 3, 2);
    if(Hor_Blink == 1)
    {
        SSD_Hourtoggle();
    }
    else if(Min_Blink == 1)
    {
        SSD_Minuttoggle();
    }
    
}

void Setting_Task(void)
{
    static uint8_t state = 0;
   
    switch(state)
    {
        case 0:
            
            if(SET_SW_Pressed == 1)
            {
                state = 1;
                Hor_Blink = 1;
                Min_Blink = 0;
                Minut_Mask = 0xff;
            }
        break;
        case 1:
            
            if(UP_SW_Pressed == 1)
            {
                Hor++;
                if(Hor > 12)
                {
                    Hor = 1;
                }
            }
            else if (DOWN_SW_Pressed == 1)
            {
                Hor--;
                if(Hor < 1)
                {
                    Hor = 12;
                }
            }
            else if(SET_SW_Pressed == 1)
            {
                state = 2;
                Min_Blink = 1;
                Hor_Blink = 0;
                Hour_Mask = 0xff;
            }
        break;
        case 2:
            
            if(UP_SW_Pressed == 1)
            {
                Min++;
                if(Min > 59)
                {
                    Min = 0;
                }
            }
            else if (DOWN_SW_Pressed == 1)
            {
                Min--;
                if(Min < 0)
                {
                    Min = 59;
                }
            }
            else if(SET_SW_Pressed == 1)
            {
                Hor_Blink = 0;
                Min_Blink = 0;
                Hour_Mask = 0xff;
                Minut_Mask = 0xff;
                state = 0;
            }
        break;
            
            
    }
}
