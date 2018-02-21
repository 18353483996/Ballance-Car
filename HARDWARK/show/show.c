#include "show.h"
#include "oled.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
unsigned char i;          //��������
unsigned char Send_Count; //������Ҫ���͵����ݸ���
extern int Encoder_Left;             //���ұ��������������
extern int Encoder_Right;             //���ұ��������������
extern float Kp1;               //
extern float Ki1;                //
extern float Kd1;            //
extern float Kp2;              // 
extern float Ki2;              //
extern float Kd2;              //
int Kp2_Bai,Kp2_Shi,Kp2_Ge,Kd2_Bai,Kd2_Shi,Kd2_Ge;
extern float Set_Angle;
/**************************************************************************
�������ܣ�OLED��ʾ
��ڲ�������
����  ֵ����
**************************************************************************/

void oled_show1(void)
{
		OLED_Display_On();  //��ʾ����
		//=============��ʾ�˲���=======================//
		   	                  OLED_ShowString(0,0,"WAY :",16);
	        if(Way_Angle==1)	OLED_ShowString(50,0,"DMP",16);
		else if(Way_Angle==2)	OLED_ShowString(50,0,"Kalman",16);
		else if(Way_Angle==3)	OLED_ShowString(50,0,"Hubu",16);
		//=============��ʾ������1=======================//	
		                      OLED_ShowString(0,2,"Lspeed:",16);
		if( Encoder_Left<0)		OLED_ShowString(55,2,"-",16),
			                    OLED_ShowNum(65,2, -Encoder_Left,3,16);
		if( Encoder_Left>0)   OLED_ShowString(55,2,"+",16),
		                      OLED_ShowNum(65,2, Encoder_Left,3,16);
  	//=============��ʾ������2=======================//		
		                      OLED_ShowString(0,4,"Rspeed:",16);
		if(Encoder_Right<0)		OLED_ShowString(55,4,"-",16),
		                      OLED_ShowNum(65,4,-Encoder_Right,3,16);
		if( Encoder_Left>0)   OLED_ShowString(55,4,"+",16),
		                      OLED_ShowNum(65,4,Encoder_Right,3,16);	
		//=============��ʾ�Ƕ�=======================//
		                      OLED_ShowString(0,6,"Angle:",16);
		if(Angle_Balance<0)		OLED_ShowString(55,6,"-",16),
			                    OLED_ShowNum(65,6,(int)(-Angle_Balance*10)/100,1,16),
													OLED_ShowNum(75,6,((int)(-Angle_Balance*10)/10)%10,1,16),
													OLED_ShowString(85,6,".",16),
                          OLED_ShowNum(95,6,(int)(-Angle_Balance*10)%10,1,16);													
			                  
		else					        OLED_ShowString(55,6,"+",16),
			                    OLED_ShowNum(65,6,(int)(Angle_Balance*10)/100,1,16),
													OLED_ShowNum(75,6,((int)(Angle_Balance*10)/10)%10,1,16),
													OLED_ShowString(85,6,".",16),
                          OLED_ShowNum(95,6,(int)(Angle_Balance*10)%10,1,16);													
			                  
		//=============ˢ��=======================//
		//OLED_Clear();	
	}

	
	void oled_show2(void)
	{
		  
//	    OLED_ShowString(0,0,"Kp1:",16);
//	       OLED_ShowNum(40,0, Kp1,3,16);
//	    OLED_ShowString(0,3,"Set_Angle:",16);
//	       OLED_ShowNum(90,3, (int)(Set_Angle*10)/10,1,16);
//		     OLED_ShowString(100,3,".",16);
//		     OLED_ShowNum(110,3, (int)(Set_Angle*10)%10,1,16);	   
//	    OLED_ShowString(0,5,"Kd1:",16);
//	       OLED_ShowNum(40,5, Kd1,3,16);     //����������ʾ����
		
		
		   OLED_ShowString(0,0,"Kp1:",16);
		     OLED_ShowNum(40,0, (int)(Kp1*10)/100,1,16);
		     OLED_ShowNum(50,0, ((int)(Kp1*10)/10)%10,1,16);
		     OLED_ShowString(60,0,".",16);
		     OLED_ShowNum(70,0, (int)(Kp1*10)%10,1,16);
		
	    OLED_ShowString(0,3,"Set_Angle:",16);
		   if(Set_Angle>=0)
				 OLED_ShowString(81,3,"+",16),
	       OLED_ShowNum(90,3, (int)(Set_Angle*10)/10,1,16),
		     OLED_ShowString(100,3,".",16),
		     OLED_ShowNum(110,3, (int)(Set_Angle*10)%10,1,16);
			 if(Set_Angle<0)
				 OLED_ShowString(81,3,"-",16),
		     OLED_ShowNum(90,3, (int)(-Set_Angle*10)/10,1,16),
		     OLED_ShowString(100,3,".",16),
		     OLED_ShowNum(110,3, (int)(-Set_Angle*10)%10,1,16);
			
				 
	    OLED_ShowString(0,6,"Kd1:",16);
		     OLED_ShowNum(40,6, (int)(Kd1*10)/100,1,16);
		     OLED_ShowNum(50,6, ((int)(Kd1*10)/10)%10,1,16);
		     OLED_ShowString(60,6,".",16);
		     OLED_ShowNum(70,6, (int)(Kd1*10)%10,1,16);     //��������ʾ����
		
	}
  void oled_show3(void)
{
		  Kp2_Bai=(int)(Kp2*100)/100;
		  Kp2_Shi=(int)(Kp2*100)%100/10;
	    Kp2_Ge=(int)(Kp2*100)%10;
	
		  Kd2_Bai=(int)(Kd2*100)/100;
		  Kd2_Shi=(int)(Kd2*100)%100/10;
	    Kd2_Ge=(int)(Kd2*100)%10;
	       OLED_ShowString(0,0,"Kp2:",16);
	       OLED_ShowNum(40,0,Kp2_Bai,1,16);
		     OLED_ShowString(49,0,".",16);
		     OLED_ShowNum(57,0,Kp2_Shi,1,16);
	       OLED_ShowNum(65,0,Kp2_Ge,1,16);
		
	    OLED_ShowString(0,2,"Ki2:",16);
	       OLED_ShowNum(40,2, Ki2,1,16);
		  
	       OLED_ShowString(0,4,"Kd2:",16);
	       OLED_ShowNum(40,4,Kd2_Bai,1,16);
		     OLED_ShowString(49,4,".",16);
		     OLED_ShowNum(57,4,Kd2_Shi,1,16);
	       OLED_ShowNum(65,4,Kd2_Ge,1,16);
	
//	    OLED_ShowString(0,4,"Kd2:",16);
//		     OLED_ShowNum(40,4,Kd2_Qian,1,16);
//	       OLED_ShowString(49,4,".",16); 
//		     OLED_ShowNum(57,4,Kd2_Hou,1,16);
}


