/* 
 * File:   sch.h
 * Author: ahmed
 *
 * Created on May 18, 2022, 11:26 AM
 */

#ifndef SCH_H
#define	SCH_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <avr/interrupt.h>
#include<avr/sleep.h>


#define SCH_MAX_TASKS (4)

#define ERROR_SCH_TOO_MANY_TASKS (1)
#define ERROR_SCH_CANNOT_DELETE_TASK (2)

#define RETURN_NORMAL (uint8_t) 0
#define RETURN_ERROR (uint8_t) 1

typedef struct
{
// Pointer to the task (must be a 'void (void)' function)
void (* pTask)(void);
// Delay (ticks) until the function will (next) be run
// - see SCH_Add_Task() for further details
uint16_t Delay;
// Interval (ticks) between subsequent runs.
// - see SCH_Add_Task() for further details
uint16_t Period;
// Incremented (by scheduler) when task is due to execute
uint16_t RunMe;

uint16_t Repeat;
} sTask;

void SCH_Init_T0(void);
void SCH_Start(void);

uint8_t SCH_Add_Task(void (* pFunction)(), const uint16_t DELAY, const uint16_t PERIOD, const uint16_t Repeat);
uint8_t SCH_Delete_Task(const uint8_t TASK_INDEX);

void SCH_Report_Status(void);
void SCH_Update(void);
void SCH_Dispatch_Tasks(void);
void SCH_Go_To_Sleep();


#ifdef	__cplusplus
}
#endif

#endif	/* SCH_H */

