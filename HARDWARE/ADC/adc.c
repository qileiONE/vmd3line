#include "adc.h"

#define ADC1_DR_Address    ((u32)0x4001244C)

__IO u16 ADC_ConvertedValue[10][2];  


 void ADC1_GPIO_Config(void)
{ 
	GPIO_InitTypeDef GPIO_InitStructure;    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		    //
	GPIO_Init(GPIOA, &GPIO_InitStructure);   

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		    //
	GPIO_Init(GPIOA, &GPIO_InitStructure);   
}



 void ADC1_Mode_Config(void)
{
  DMA_InitTypeDef DMA_InitStructure;
  ADC_InitTypeDef ADC_InitStructure;	
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //
	/* DMA channel1 configuration */
  DMA_DeInit(DMA1_Channel1);  //
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address;//
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue;	//
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //
  DMA_InitStructure.DMA_BufferSize = 2*10;	//
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
  /* Enable DMA channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);  //

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);	//
     
  /* ADC1 configuration */
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; //
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; //
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 2;  // 
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC1 regular channel11 configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5); //
  ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5); //

  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);	 //
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE); //

  /* Enable ADC1 reset calibaration register */   
  ADC_ResetCalibration(ADC1);
  /* Check the end of ADC1 reset calibration register */
  while(ADC_GetResetCalibrationStatus(ADC1));

  /* Start ADC1 calibaration */
  ADC_StartCalibration(ADC1);
  /* Check the end of ADC1 calibration */
  while(ADC_GetCalibrationStatus(ADC1));
     
  /* Start ADC1 Software Conversion */ 
  ADC_SoftwareStartConvCmd(ADC1, ENABLE);  //
}


void ADC1_Init(void)
{
	ADC1_GPIO_Config();
	ADC1_Mode_Config();
}

unsigned int wendu[126][2]={
1020,9534,
1019,9006,
1018,8510,
1017,8044,
1016,7607,
1015,7196,
1014,6809,
1013,6645,
1012,6103,
1011,5780,
1010,5477,
1009,5191,
1008,4922,
1007,4668,
1006,4229,
1005,4203,
1004,3990,
1003,3889,
1002,3599,
1001,3420,
0,3274,//0 32.74k
1,3111,//1 31.11k
2,2957,//2 29.57k
3,2812,//
4,2674,//
5,2545,
6,2422,
7,2306,
8,2196,
9,2092,
10,1993,
11,1900,
12,1811,
13,1728,
14,1648,
15,1573,
16,1501,
17,1433,
18,1369,
19,1308,
20,1250,
21,1194,
22,1142,
23,1092,
24,1045,
25,1000,//25 10k                
26,957,//26 9.57k
27,916,
28,877,
29,840,
30,805,
31,771,
32,739,
33,709,
34,679,
35,652,
36,625,
37,600,
38,576,
39,553,
40,531,
41,510,
42,490,
43,471,
44,453,
45,435,
46,418,
47,402,
48,387,
49,372,
50,358,
51,345,
52,332,
53,320,
54,308,
55,297,
56,286,
57,276,
58,266,
59,256,
60,247,
61,238, 
62,230,
63,222,
64,214,
65,207,
66,199,
67,193,
68,186,
69,180,
70,174,
71,168,
72,162,
73,157,
74,152,
75,147,
76,142,
77,137,
78,133,
79,128,
80,124,
81,120,
82,116,
83,113,
84,109,
85,106,
86,102,//86 1.02k
87,99,//87 0.99k
88,96,
89,93,
90,90,
91,88,
92,85,
93,82,
94,80,
95,78,
96,75,
97,73,
98,71,
99,69,
100,67,
101,65,
102,63,
103,61, 
104,59,
105,58//105 0.58k
          
};   

unsigned int Get_temp1(void)
{
	unsigned char i;
	unsigned int ad_sum;
	u32 AD_value;	
	unsigned int dat,r_value;
	for(i=0;i<10;i++)
	{
		ad_sum += ADC_ConvertedValue[i][0];	
	}
	AD_value  = 3000000/4096*ad_sum/1000/10;
	r_value = (AD_value*470)/(5100-AD_value);

	for(i=0;i<126;i++)  
	{
		if((r_value <= wendu[i][1]) && (r_value > wendu[i+1][1]))
		{ //
			dat=(wendu[i][0]);//dat2		
			i=0;
			break;
		}else{dat=0;}
	}
	return 	dat;	
}

unsigned int Get_temp2(void)
{
	unsigned char i;
	unsigned int ad_sum;
	u32 AD_value;	
	unsigned int dat,r_value;
	for(i=0;i<10;i++)
	{
		ad_sum += ADC_ConvertedValue[i][1];	
	}
	AD_value  = 3000000/4096*ad_sum/1000/10;
	r_value = (AD_value*470)/(5100-AD_value);

	for(i=0;i<126;i++)  
	{
		if((r_value <= wendu[i][1]) && (r_value > wendu[i+1][1]))
		{ //
			dat=(wendu[i][0]);//dat2		
			i=0;
			break;
		}else{dat=0;}
	}
	return 	dat;	
}

