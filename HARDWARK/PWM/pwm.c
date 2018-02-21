#include "pwm.h"
void TIM3_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

	                                             /* TIM3 clock enable */
	                                             //PCLK1����2��Ƶ����ΪTIM3��ʱ��Դ����72MHz
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); 

                                              /* GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); 

                                                 /*GPIOA Configuration: TIM3 channel 1 and 2 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*
 * ��������TIM2_Mode_Config
 * ����  ������TIM2�����PWM�źŵ�ģʽ�������ڡ����ԡ�ռ�ձ�
 * ����  ����
 * ���  ����
 * ����  ���ڲ�����
 */
	
void TIM3_Mode_Config(u16 CCR3_Val,u16 CCR4_Val)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	/* PWM�źŵ�ƽ����ֵ */
	

/* -----------------------------------------------------------------------
    TIM2 Configuration: generate 4 PWM signals with 4 different duty cycles:
    TIM2CLK = 72 MHz, Prescaler = 0x0, TIM2 counter clock = 72 MHz
    TIM2 ARR Register = 999 => TIM2 Frequency = TIM2 counter clock/(ARR + 1)
    TIM2 Frequency = 72 KHz.
    TIM2 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR)* 100 = 50%
    TIM2 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR)* 100 = 37.5%
    TIM2 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR)* 100 = 25%
    TIM2 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR)* 100 = 12.5%
  ----------------------------------------------------------------------- */

  /* Time base configuration */		 
  TIM_TimeBaseStructure.TIM_Period = 899;       //����ʱ����0������899����Ϊ900�Σ�Ϊһ����ʱ����2.5ms
  TIM_TimeBaseStructure.TIM_Prescaler =3;	    //����Ԥ��Ƶ����Ԥ��Ƶ����Ϊ72MHz/72=1MHz
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;	//����ʱ�ӷ�Ƶϵ��������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ

  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

                                                     /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1

  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR3_Val;	  //����ͨ��3�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM

  TIM_OC3Init(TIM3,&TIM_OCInitStructure);	  //ʹ��ͨ��3

  TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

                                                     /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	
  TIM_OCInitStructure.TIM_Pulse = CCR4_Val;	//����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM

  TIM_OC4Init(TIM3,&TIM_OCInitStructure);	 //ʹ��ͨ��2

  TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);

                                            /* PWM1 Mode configuration: Channel4 */
 
  TIM_ARRPreloadConfig(TIM3, ENABLE);			 // ʹ��TIM3���ؼĴ���ARR

  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);                   //ʹ�ܶ�ʱ��3	
}

/*
 * ��������TIM2_PWM_Init
 * ����  ��TIM2 ���PWM�źų�ʼ����ֻҪ�����������
 *         TIM2���ĸ�ͨ���ͻ���PWM�ź����
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */

void TIM3_PWM_Init(u16 * CCR3_Val,u16 * CCR4_Val)
{
	TIM3_GPIO_Config();
	TIM3_Mode_Config( * CCR3_Val,* CCR4_Val);
                                    
}




