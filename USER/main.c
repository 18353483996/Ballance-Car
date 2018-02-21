#include "sys.h"
#include "pwm.h"
#include "dianji.h"
#include "encoder.h"
#include "oled.h"
#include "hwjs.h"
#include "show.h"
#include "key.h"
/**************************************************************************
��������   λ�û�����
**************************************************************************/
u8 Way_Angle=2 ; 
float Angle_Balance; 
u16 CCR3_Val=0;
u16 CCR4_Val=0;
int Encoder_Left;             //����������������
int Encoder_Right;             //�ұ��������������
int Position;
float Angle_PID_Out;
float Speed_PID_Out;
float Position_PID_Out;
float Zong_PID_Out;
u8 flag1=1,flag2,flag3,flag4,flag5,flag6,flag7,flag8,flag9;

float Set_Angle=1.7;    //�趨����ֵ�Ƕ�2.0

/***********************************************/
float Kp1=11;               //   ������12      ��������90    28
float Ki1=0;                //
float Kd1=33;            //      ������19     ��������160     60

float Kp2=0.35;               //   3.03`
float Ki2=0;                //
float Kd2=0;            //

float Kp3=0;              // 0.5
float Ki3=0;             //
float Kd3=0;              //
/***********************************************/

int main(void)
{ 
	
	Stm32_Clock_Init(9);            //ϵͳʱ������
	delay_init(72);                 //��ʱ��ʼ��
	OLED_Init();			//��ʼ��OLED  
	OLED_Clear();
	uart_init(72,115200);           //��ʼ������1
	TIM3_PWM_Init(&CCR3_Val,&CCR4_Val);
	Encoder_Init_TIM2();            //��ʼ��������1 
	Encoder_Init_TIM4();            //��ʼ��������2 
	IIC_Init();                     //ģ��IIC��ʼ��
  MPU6050_initialize();           //=====MPU6050��ʼ��
  DMP_Init();	
	DIANJI_Init();
  hwjs_init();   //����ӿڳ�ʼ��
  Timer1_Init(49,7199);           //=====5MS��һ���жϷ�����	
	while(1)
		{
			  
			   HongWai_Scan();
	       Key_Scan();	
         printf("��������� %d\r\n",1234);	//��ӡ
//         TIM_SetCompare3(TIM3,700);        //����       
//         TIM_SetCompare4(TIM3,600);	      //����
//	     printf("�� �� �� �� �� �� Pitch:  %f\r\n  ",Angle_Balance);  //y      3
//       printf("�� �� �� �� �� �� �� Pitch:  %f\r\n  ",Angle_Balance);  //y   2  
//			if(Way_Angle==1)                     //DMPû���漰���ϸ��ʱ�����⣬����������ȡ
//				{
//					Read_DMP();                      //===��ȡ���ٶȺ����
//					Angle_Balance=Pitch;             //===����ƽ�����
//     	                         printf("Roll:%f  ",Roll);  //X                                      1
//			                         printf("Pitch:%f  ",Pitch); //Y
// 			                         printf("Yaw:%f\r\n",Yaw);   //Z	
//				}
//                               printf("Encoder_Left=%d,Encoder_Right%d\n",Encoder_Left,Encoder_Right);
//			if(hw_jsbz==1)	//���������յ�
//		{
//			hw_jsbz=0;	   //����
//			                         printf("��������� %0.8X\r\n",hw_jsm);	//��ӡ
//			                        
//			hw_jsm=0;					//����������
//		}
		} 
}
