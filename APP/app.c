
//Write your task hear

/* Includes ------------------------------------------------------------------*/
#include "includes.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/*����һЩ����TCB��ջ�ռ�����ÿ������

����TCB��uCOS-III���ڹ��������һ���ṹ�壬ÿ�����������һ��������TCB

����ջ�ռ����ڴ洢�������е���Ϣ�������񱻴��ʱ����ǰ��Ϣȫ���洢��ջ�У��´�
�ظ�������̬ʱ�ٰ���Щ��Ϣ��ԭ��������

�������ǽ����ĸ����񣬷ֱ�����ʼ����Start_Up����������LED��˸������LED1,LED2,LED3
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
	//����һ�����ڴ洢ϵͳ������Ϣ�ı���
	//�������е�uCOS-III�������ö��᷵��һ��������Ϣ���ô�����Ϣ���Ը������Ǻ����ĵ������
	//���û�д���һ�㷵��OS_ERR_NONE
	
	//��ʼ��ϵͳ��
	OSInit(&err);

	//����uCOS-III��ϰ��һ���Ƚ���һ����ʼ�����ڸ������н���������������ɳ�ʼ����						
	OSTaskCreate((OS_TCB     *)&StartUp_TCB,//һ������TCBָ�룬ָ�����������TCB
							 (CPU_CHAR   *)"Start",//���Ը�������һ������
							 (OS_TASK_PTR )Task_Start,//һ������ָ�룬ָ�������ִ�еĺ���
							 (void       *)0,//һ�����Ӳ���ָ�룬ָ��һ�����Ը��Ӵ��ݸ�����Ĳ���
							 (OS_PRIO     )1,//����������ȼ���ע�ⲻͬ�������ȼ�������ͬ�����Ϊ0
							 (CPU_STK    *)&StartUp_Stk[0],//������������ջ�ռ�Ļ���ַ
							 (CPU_STK_SIZE)8,//ջ�ռ�ʣ������λ�����ڼ���ȷ����ջ�ռ䲻�����
							 (CPU_STK_SIZE)80,//ջ�ռ��С
							 (OS_MSG_QTY  )0,//��������ӵ�е���Ϣ���г���
							 (OS_TICK     )0,//ʱ��Ƭ���ȣ�����ʹ��ʱ��Ƭ��ת����ʱ��Ч
							 (void       *)0,//�û�����Ĵ洢����������չ����TCB
							 (OS_OPT      )(OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR),//ָ�����񴴽�ѡ�
														 //�˴�����Ϊ�����������ջ������ʱ����ջ���
							 (OS_ERR     *)&err);//����������Ĵ�����Ϣ���ݸ�err
							 
	//��ʼϵͳ���У�ϵͳ��ʼ��������
	OSStart(&err);
}

//��ʼ�����������ڴ�����������ִ�г�ʼ��
void Task_Start(void *p_arg)
{
	//ͬ������һ���洢�������ô���ı���
	OS_ERR err;
	(void)p_arg;
	
	//����������ͬ�ķ�ʽ��������LED��������
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
							 
	//��ʼ�����裬����Ϊ��ʼ��ʱ�Ӻ�Ҫʹ�õ�GPIO��
	Our_Sys_Init();
							 
	//����ִ����ϣ�ɾ���Լ����Ӵ˲���ִ��
	//����һ��ֻ����һ�ε������������Ͳ���ʹ�ã�Ӧ�ü�ʱɾ��
	OSTaskDel(&StartUp_TCB,&err);
}

//LED1���ƺ�����ӵ�п���LED1��200ms��������˸
void Task_LED1(void *p_arg)
{
	OS_ERR err;
	(void)p_arg;
	//����һ������ִ�еĺ�������˷���һ��while(1)�����ظ�ִ�У�����ɾ������
	while(1)
	{
		//�˴�����ʱ���õ���ϵͳ�ṩ����ʱ��������������ʱ��ʱ��Ϳ���ִ������������
		OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_HMSM_STRICT,&err);
		GPIO_SetBits(GPIOC,GPIO_Pin_13);
		OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_HMSM_STRICT,&err);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);
		
		
	}
		
}

//LED2���ƺ�����ӵ�п���LED1��400ms��������˸
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

//LED3���ƺ�����ӵ�п���LED1��600ms��������˸
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

