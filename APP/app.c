
//Write your task hear

/* Includes ------------------------------------------------------------------*/
#include "includes.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
OS_TCB StartUp_TCB;
CPU_STK StartUp_Stk[80];

static OS_TCB LED1_TCB;
static CPU_STK LED1_Stk[128];

static OS_TCB LED2_TCB;
static CPU_STK LED2_Stk[128];

static OS_TCB LED3_TCB;
static CPU_STK LED3_Stk[128];



/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
int main(void)
{
	//Start with board specific hardware init.
	OS_ERR err;
	
	
	
	
	OSInit(&err);

							
	OSTaskCreate((OS_TCB     *)&StartUp_TCB,
							 (CPU_CHAR   *)"Start",
							 (OS_TASK_PTR )Task_Start,
							 (void       *)0,
							 (OS_PRIO     )1,
							 (CPU_STK    *)&StartUp_Stk[0],
							 (CPU_STK_SIZE)8,
							 (CPU_STK_SIZE)80,
							 (OS_MSG_QTY  )0,
							 (OS_TICK     )0,
							 (void       *)0,
							 (OS_OPT      )(OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR),
							 (OS_ERR     *)&err);
	
	OSStart(&err);
	//Infinite loop to deal with your project.
	/*while(1)
	{
		
	}*/
}

void Task_Start(void *p_arg)
{
	OS_ERR err;
	(void)p_arg;
	
	OSTaskCreate((OS_TCB     *)&LED1_TCB,
							 (CPU_CHAR   *)"LED1",
							 (OS_TASK_PTR )Task_LED1,
							 (void       *)0,
							 (OS_PRIO     )4,
							 (CPU_STK    *)&LED1_Stk[0],
							 (CPU_STK_SIZE)12,
							 (CPU_STK_SIZE)128,
							 (OS_MSG_QTY  )0,
							 (OS_TICK     )0,
							 (void       *)0,
							 (OS_OPT      )(OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR),
							 (OS_ERR     *)&err);
							 
	OSTaskCreate((OS_TCB     *)&LED2_TCB,
							 (CPU_CHAR   *)"LED2",
							 (OS_TASK_PTR )Task_LED2,
							 (void       *)0,
							 (OS_PRIO     )5,
							 (CPU_STK    *)&LED2_Stk[0],
							 (CPU_STK_SIZE)12,
							 (CPU_STK_SIZE)128,
							 (OS_MSG_QTY  )0,
							 (OS_TICK     )0,
							 (void       *)0,
							 (OS_OPT      )(OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR),
							 (OS_ERR     *)&err);
							 
	OSTaskCreate((OS_TCB     *)&LED3_TCB,
							 (CPU_CHAR   *)"LED3",
							 (OS_TASK_PTR )Task_LED3,
							 (void       *)0,
							 (OS_PRIO     )6,
							 (CPU_STK    *)&LED3_Stk[0],
							 (CPU_STK_SIZE)12,
							 (CPU_STK_SIZE)128,
							 (OS_MSG_QTY  )0,
							 (OS_TICK     )0,
							 (void       *)0,
							 (OS_OPT      )(OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR),
							 (OS_ERR     *)&err);
							 

	Our_Sys_Init();
	OSTaskDel(&StartUp_TCB,&err);
}

void Task_LED1(void *p_arg)
{
	OS_ERR err;
	(void)p_arg;
	
	while(1)
	{
		
		OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_HMSM_STRICT,&err);
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_HMSM_STRICT,&err);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		
		
	}
		
}


void Task_LED2(void *p_arg)
{
	OS_ERR err;
	(void)p_arg;
	
	while(1)
	{
		OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err);
		GPIO_SetBits(GPIOB,GPIO_Pin_14);
		OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err);
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);
		
		
	}
		
}


void Task_LED3(void *p_arg)
{
	OS_ERR err;
	(void)p_arg;
	
	while(1)
	{
		OSTimeDlyHMSM(0,0,0,300,OS_OPT_TIME_HMSM_STRICT,&err);
		GPIO_SetBits(GPIOB,GPIO_Pin_15);
		OSTimeDlyHMSM(0,0,0,300,OS_OPT_TIME_HMSM_STRICT,&err);
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);
		
		
	}
		
}

