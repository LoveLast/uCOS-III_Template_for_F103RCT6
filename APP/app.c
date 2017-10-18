
//Write your task hear

/* Includes ------------------------------------------------------------------*/
#include "includes.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/*建立一些任务TCB和栈空间分配给每个任务

任务TCB是uCOS-III用于管理任务的一个结构体，每个任务必须有一个单独的TCB

任务栈空间用于存储任务运行的信息，当任务被打断时任务当前信息全部存储到栈中，下次
回复到运行态时再把这些信息复原继续运行

这里我们建立四个任务，分别是起始任务Start_Up，三个控制LED闪烁的任务LED1,LED2,LED3
*/
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

	OS_ERR err;
	//这是一个用于存储系统错误信息的变量
	//几乎所有的uCOS-III函数调用都会返回一个错误信息，该错误信息可以告诉我们函数的调用情况
	//如果没有错误，一般返回OS_ERR_NONE
	
	//初始化系统，
	OSInit(&err);

	//按照uCOS-III的习惯一般先建立一个开始任务，在该任务中建立其他的任务并完成初始化。						
	OSTaskCreate((OS_TCB     *)&StartUp_TCB,//一个任务TCB指针，指向管理该任务的TCB
							 (CPU_CHAR   *)"Start",//可以给该任务一个名字
							 (OS_TASK_PTR )Task_Start,//一个函数指针，指向该任务执行的函数
							 (void       *)0,//一个附加参数指针，指向一个可以附加传递给任务的参数
							 (OS_PRIO     )1,//该任务的优先级，注意不同任务优先级可以相同，最高为0
							 (CPU_STK    *)&StartUp_Stk[0],//分配给该任务的栈空间的基地址
							 (CPU_STK_SIZE)8,//栈空间剩余量限位，用于检测和确保堆栈空间不会溢出
							 (CPU_STK_SIZE)80,//栈空间大小
							 (OS_MSG_QTY  )0,//该任务所拥有的消息队列长度
							 (OS_TICK     )0,//时间片长度，仅在使能时间片轮转调度时有效
							 (void       *)0,//用户补充的存储区，用于扩展任务TCB
							 (OS_OPT      )(OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR),//指定任务创建选项，
														 //此处设置为允许检测任务堆栈并创建时将堆栈清空
							 (OS_ERR     *)&err);//将创建任务的错误信息传递给err
							 
	//开始系统运行，系统开始调度任务
	OSStart(&err);
}

//开始任务函数，用于创建其他任务并执行初始化
void Task_Start(void *p_arg)
{
	//同样创建一个存储函数调用错误的变量
	OS_ERR err;
	(void)p_arg;
	
	//用与上面相同的方式创建三个LED控制任务
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
							 
	//初始化外设，具体为初始化时钟和要使用的GPIO等
	Our_Sys_Init();
							 
	//任务执行完毕，删除自己，从此不再执行
	//这是一个只调用一次的任务，运行完后就不再使用，应该及时删除
	OSTaskDel(&StartUp_TCB,&err);
}

//LED1控制函数，拥有控制LED1以200ms的周期闪烁
void Task_LED1(void *p_arg)
{
	OS_ERR err;
	(void)p_arg;
	//这是一个反复执行的函数，因此放在一个while(1)当中重复执行，不会删除自身
	while(1)
	{
		//此处的延时调用的是系统提供的延时函数，这样在延时的时候就可以执行其他的任务
		OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_HMSM_STRICT,&err);
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_HMSM_STRICT,&err);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		
		
	}
		
}

//LED2控制函数，拥有控制LED1以400ms的周期闪烁
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

//LED3控制函数，拥有控制LED1以600ms的周期闪烁
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

