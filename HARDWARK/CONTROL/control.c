#include "control.h"
#include "filter.h"
#include "encoder.h"
#include "dianji.h"
extern int Encoder_Left;             //���ұ��������������
extern int Encoder_Right;             //���ұ��������������
extern int Position;
u8 Flag_Target;
float Real_Angle;
extern float Set_Angle;

extern float Angle_PID_Out;
extern float Speed_PID_Out;
extern float Position_PID_Out;
extern float Zong_PID_Out;
/**************************/
float err1=0;
float err_last1=0;
extern float Kp1;               //
extern float Ki1;                //
extern float Kd1;            //
float PID_I1=0;              //�ǶȻ�
/********************************/
/**************************/
float err2=0;
float err_last2=0;
extern float Kp2;              // 
extern float Ki2;              //
extern float Kd2;              //
float PID_I2=0;              //�ٶȻ�
/********************************/
/**************************/
float err3=0;
float err_last3=0;
extern float Kp3;              // 
extern float Ki3;              //
extern float Kd3;              //
float PID_I3=0;                //  λ�û�
/********************************/
int TIM1_UP_IRQHandler(void)  
{    
	if(TIM1->SR&0X0001)//5ms��ʱ�ж�
	{   
		  TIM1->SR&=~(1<<0);		//===�����ʱ��1�жϱ�־λ
      Flag_Target=!Flag_Target;
		  if(Flag_Target==1)                                       //5ms��ȡһ�������Ǻͼ��ٶȼƵ�ֵ�����ߵĲ���Ƶ�ʿ��Ը��ƿ������˲��ͻ����˲���Ч��
			{
			Get_Angle(Way_Angle);                                    //===������̬	
			return 0;	
			}   
      Encoder_Right=Read_Encoder(2);                            //===��ȡ��������ֵ
			Encoder_Left=Read_Encoder(4);                           //===��ȡ��������ֵ			
	  	Get_Angle(Way_Angle);                                    //===������̬			
		  Zong_PID_Out=Angle_PID()+Speed_PID(0)+Position_PID(0);
	//	printf("Angle_PID_Out=%f\r\r\r\rPosition_PID_Out=%f\n",Angle_PID_Out,Position_PID_Out);
			Set_Pwm();
	}       	
	 return 0;	  
} 

/**************************************************************************
�������ܣ���ȡ�Ƕ�
��ڲ�������ȡ�Ƕȵ��㷨 1����  2�������� 3�������˲�
����  ֵ����
**************************************************************************/
void Get_Angle(u8 way)
{ 
	    float Accel_Y,Accel_X,Accel_Z,Gyro_Y;
	    if(way==1)                                      //DMPû���漰���ϸ��ʱ�����⣬����������ȡ
			{	
			}			
      else
      {
			Gyro_Y=(I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_YOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_GYRO_YOUT_L);    //��ȡY��������
			Accel_Z=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_ZOUT_L);    //��ȡZ��������
		  Accel_X=(I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_XOUT_H)<<8)+I2C_ReadOneByte(devAddr,MPU6050_RA_ACCEL_XOUT_L); //��ȡX����ٶȼ�
	 		if(Gyro_Y>32768)  Gyro_Y-=65536;     //��������ת��  Ҳ��ͨ��shortǿ������ת��
			if(Accel_Z>32768)  Accel_Z-=65536;     //��������ת��
	  	if(Accel_X>32768) Accel_X-=65536;    //��������ת��
	   	Accel_Y=atan2(Accel_X,Accel_Z)*180/PI;                 //���������ļн�	
		  Gyro_Y=Gyro_Y/16.4;                                    //����������ת��	
      if(Way_Angle==2)		  	Kalman_Filter(Accel_Y,-Gyro_Y);//�������˲�	
			else if(Way_Angle==3)   Yijielvbo(Accel_Y,-Gyro_Y);    //�����˲�
	    Angle_Balance=angle;                                   //����ƽ�����
	  	}
}

float Angle_PID()
     {
			      
	           Real_Angle=Angle_Balance;
			           err1 = (Set_Angle-Real_Angle);
			              if(err1>=0.8||err1<=-0.8)
													 Angle_PID_Out = Kp1*err1 + Ki1* PID_I1 + Kd1*(err1-err_last1);
                   	else Angle_PID_Out=0;										
										err_last1= err1;
										        PID_I1 += err1;
								return 		Angle_PID_Out;
//			 printf("Angle_PID_Out=%f\n",Angle_PID_Out);
				       
			}

float Speed_PID(float Set_Speed)
    {
	       err2=Set_Speed-(Encoder_Right+Encoder_Left);  //===��ȡ�����ٶ�ƫ��==�����ٶȣ����ұ�����֮�ͣ�-Ŀ���ٶȣ��˴�Ϊ�㣩 
	   	   Speed_PID_Out+=Kp2*(err2-err_last2)+Ki2*err2;                        //===�ٶ�PI����
			    err_last2=err2; 
	      return Speed_PID_Out;
    }
float Position_PID(float Set_Position)
{
        Position+=Encoder_Right+Encoder_Left;        //===���ٶȽ��л��֣��õ�λ����Ϣ  
        err3=Position;
           PID_I3=err3;
   //     if(PID_I3>1500000)   PID_I3=1500000;   //�����޷�
	 //     if(PID_I3<-1500000)  PID_I3=-1500000; //�����޷� 
	      Position_PID_Out=Kp3*err3+Ki3*PID_I3;
	        return Position_PID_Out;
	      //   printf("Position_PID_Out=%f\n",Position_PID_Out);
}
		
		
void Set_Pwm(void)
{
	      int duty;
      	if(Zong_PID_Out>=269)   Zong_PID_Out=269;
				if(Zong_PID_Out<=-269)	Zong_PID_Out=-269;	//819
						       if(Zong_PID_Out>=0) 
			                  {
				                            L1 = 0;
			                              L2 = 1;
			                              R1 = 0;
			                              R2 = 1;
													               duty= (int)Zong_PID_Out;
													          TIM_SetCompare3(TIM3,630+duty);        //��������600       
                                    TIM_SetCompare4(TIM3,615+duty);	      //��������615
			                  }
			             else if (Zong_PID_Out<0)
			                  {
				                          Zong_PID_Out= -Zong_PID_Out;
													          L1 = 1;
			                              L2 = 0;
			                              R1 = 1;
			                              R2 = 0;
													          duty= (int)Zong_PID_Out;	   
 													          TIM_SetCompare3(TIM3,630+duty);        //��������600       
                                    TIM_SetCompare4(TIM3,615+duty);	      //��������615
					              }
}









