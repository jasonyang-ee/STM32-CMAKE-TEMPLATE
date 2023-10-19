/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "iwdg.h"
#include "rtc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "LCD.h"
#include "menu.h"
#include "stm32f1xx_hal.h"
#include "EVENT_SAVE.h"
#include "string.h"
#include "stdio.h"
extern uint8_t RxBuf1[100]; 
extern DMA_HandleTypeDef hdma_usart1_rx;
 #define res        IWDG->KR  = 0xAAAA;

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#include "tim.h"
extern uint8_t CR ; 
extern uint8_t TUI;
extern int sige;
uint8_t p2=0;
extern  uint8_t dg;
extern uint8_t FGK;
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define relay_on    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_13, GPIO_PIN_SET)
#define relay_off    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_13, GPIO_PIN_RESET)
#define MANUAL_ON    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_3, GPIO_PIN_SET)
#define MANUAL_OFF    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_3, GPIO_PIN_RESET)
#define AUTOPILOT_ON    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_2, GPIO_PIN_SET)
#define AUTOPILOT_OFF    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_2, GPIO_PIN_RESET)
#define PIR_ON    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_8, GPIO_PIN_SET)
#define PIR_OFF    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_8, GPIO_PIN_RESET)
#define INTERNAL_ON    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_4, GPIO_PIN_SET)
#define INTERNAL_OFF    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_4, GPIO_PIN_RESET)
#define EXT_ON    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_14, GPIO_PIN_SET)
#define EXT_OFF    HAL_GPIO_WritePin(GPIOB,  GPIO_PIN_14, GPIO_PIN_RESET)
#define manu  HAL_GPIO_ReadPin( GPIOB,GPIO_PIN_0  )


extern uint8_t TIMO;
uint8_t WARN=0;
uint8_t WARN1=0;
uint8_t WARN2=0;
uint8_t WARN3=0;

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
UART_HandleTypeDef huart1;
/* USER CODE END PM */
extern uint8_t TX_Buffer7[1];
	uint8_t pervious_second=0;
	float AD_AC=0;
  float AD_DC=0;
  RTC_TimeTypeDef sTime2 = {0};
  RTC_DateTypeDef DateToUpdate2 = {0}; 

uint8_t REP=0;
uint8_t REP1=0;
uint8_t REP2=0;
uint8_t REP3=0;
uint8_t REP4=0;
uint8_t minu=30;
uint8_t sec=0; 
char time[20];
RTC_DateTypeDef DateToUpdate1;

/* Private variables ---------------------------------------------------------*/
 


	uint8_t mj2;
 
UART_HandleTypeDef huart1;

extern TIM_HandleTypeDef htim4;
 TIM_HandleTypeDef htim3;
 TIM_HandleTypeDef htim2;
uint8_t hg=0;
extern int rese;
extern int rese;
  extern uint16_t KEY;
extern char MENU[20];
extern uint16_t gpi;
extern float frequency ;
extern uint16_t KEY ;
 uint8_t JU =0;
 uint8_t JI =0;
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart1;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint32_t lev;
uint32_t silent=0;
void first_buzzer(void){
	
if(lev%2==0){	
	INTERNAL_ON;
	TX_Buffer7[0]=~((~TX_Buffer7[0])|0x20);//LED ON
	HAL_I2C_Master_Transmit(&hi2c1,0x41,TX_Buffer7,1,10);

}
else{
	INTERNAL_OFF;
 TX_Buffer7[0]=((TX_Buffer7[0])|0x20);//LED OFF
 HAL_I2C_Master_Transmit(&hi2c1,0x41,TX_Buffer7,1,10);

	
}
	 

     
}
void second_buzzer(void){
	INTERNAL_OFF;
	EXT_ON;
if(lev%2==0){	
	TX_Buffer7[0]=((TX_Buffer7[0])|0x20);
	 HAL_I2C_Master_Transmit(&hi2c1,0x41,TX_Buffer7,1,100);
 
}
else{
 
 TX_Buffer7[0]=~((~TX_Buffer7[0])|0x20);
			  HAL_I2C_Master_Transmit(&hi2c1,0x41,TX_Buffer7,1,100);

}
	
}
void lk(void){

 	    HAL_FLASH_Lock(); 
     	mj2 =   *( uint8_t *)(0x0801ff22);
				// lcd_clear();
  			 if(mj2==0x30){
				  minu=30;
					 mj2=30;
			 }
      else if(mj2==0x20){			 
			 minu=20;
			  mj2=20;}
      else if(mj2==0x15){			 
			 minu=15;
			  mj2=15;}			
      else if(mj2==0x10){			 
			 minu=10;
			mj2=10;}
      else if(mj2==0x05){			 
			 minu=5;
			 mj2=5;}	
      else if(mj2==0xff){
				minu=30;
				mj2=30;
			}
				
 			 sec=0;
		 }
  #define pir_check    HAL_GPIO_ReadPin(GPIOA,  GPIO_PIN_12 )
  RTC_TimeTypeDef  current_time22;
/* USER CODE END 0 */
void AUTOPILOT(void){ 
	 
	
								 AUTOPILOT_ON;
									MANUAL_OFF;
									KEY=0;	
                  CR=1;
								  minu=5;
                  mj2=5;
 								  sec=0;
	                TUI=1;
	
	
}
void manual(void){
	
	
								 AUTOPILOT_OFF;
								 MANUAL_ON;
									KEY=0;	
                  CR=0;
 
 								  sec=0;
	                TUI=0;
	                  lk();
	
	
}
  void ADC_CHECK(void){
		    HAL_ADC_Start(&hadc2);
        HAL_ADC_PollForConversion(&hadc2, 1);
        AD_DC = HAL_ADC_GetValue(&hadc2);
			     HAL_ADC_Start(&hadc1);
        HAL_ADC_PollForConversion(&hadc1, 1);
	      AD_AC = HAL_ADC_GetValue(&hadc1);

		   if(AD_AC<0XeaA  && AD_DC>0Xeaa ){
               relay_on;
				       WARN1=1;
				        WARN=0;
			 }
			   
				else if(AD_AC>0Xeea && AD_DC<0Xeea) {
					 relay_off; 
				   WARN=1;
					  WARN1=0;
				}			 

					else if(AD_AC>0Xeea && AD_DC>0Xeea ) {
					  relay_off; 
						WARN1=0;
						WARN=0;

				}		
 
 					else if(AD_AC<0Xeea && AD_DC<0Xeea ) {
					  relay_off; 
						WARN1=1;
						WARN=1;

				}	      	
	
	
	
}
	
/**
  * @brief  The application entry point.
  * @retval int
  */

int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
   HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */
   /* Initialize all configured peripherals */
	//2
  MX_GPIO_Init();
	INTERNAL_OFF;
	MANUAL_ON;
	AUTOPILOT_OFF;
 	MX_RTC_Init();
  MX_ADC2_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_I2C1_Init();
  MX_TIM3_Init();
	MX_TIM2_Init();
	MX_TIM4_Init();
  MANUAL_ON;
  lcd_init() ;
	lk();
	  HAL_UARTEx_ReceiveToIdle_DMA(&huart1, (uint8_t *) RxBuf1, 10);
   __HAL_DMA_DISABLE_IT(&hdma_usart1_rx, DMA_IT_HT);
   //MX_IWDG_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
   res;
			  //RELAY_VIN_ON;
		   	//HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);
  
	  HAL_RTC_GetTime(&hrtc,&current_time22,RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc,&DateToUpdate1,RTC_FORMAT_BIN);
		
		if(sige==1){
			  HAL_I2C_DeInit(&hi2c1);

		  MX_I2C1_Init();
			 lcd_init() ;

		  HAL_Delay(500);
					 lcd_clear();
			     HAL_Delay(500);
				   lcd_init() ;
			     lcd_clear();
				   sige=0;
    }
 
   else{
	 


				//lcd_write_string("---------");
		if(pervious_second!=current_time22.Seconds){
			 

		 
			lcd_set_cursor(0, 5);
			 //ADC_CHECK();
			 sprintf(time,"%02d:%02d:%02d",current_time22.Hours,current_time22.Minutes,current_time22.Seconds);
			 
			lcd_write_string(time);
			pervious_second=current_time22.Seconds;

        lcd_set_cursor(1, 5);
			//ADC_CHECK();
			   sprintf(time,"20%02d/%02d/%02d",DateToUpdate1.Year,DateToUpdate1.Month,DateToUpdate1.Date);
			  
 		     lcd_write_string(time);      
         lcd_set_cursor(3, 0);
          //ADC_CHECK();
			   sprintf(time,"   timer: %02d:%02d",minu,sec);
			 
 		     lcd_write_string(time); 
         if(WARN==1 |WARN1==1|WARN2==1|WARN3==1 && REP1==1){

         lcd_set_cursor(2, 0);
 		     lcd_write_string("!"); 						 
					 REP1=0;
				 }
				 else{
           lcd_set_cursor(2, 0);
 		     lcd_write_string(" ");            
					  REP1=1;
				 }
 


 			if(minu==0 && sec==0){

				if(lev==0){
				 lcd_clear();
    		 lcd_write_string("    EVENT SAVE"); 
			   KEY=0;
			   HAL_Delay(1000);
			   event_save(0);
			   lcd_clear();
					
				}
					lev+=1;
								 if(KEY==reset_Pin){
            silent++;
					   KEY=0;
					 						
					    TX_Buffer7[0]=((TX_Buffer7[0])|0x20);
             
			}
				if(silent>=1){
 		    	minu=mj2 ;
				  sec=60;
				  minu-=1;
				  silent=0;
			    INTERNAL_OFF;
	        EXT_OFF;
				  lev=0;

				}
        else if(lev<60){
			   	first_buzzer();

				}
				else if(lev>=60){
					second_buzzer();

				}

			}
			else{
			 if(sec==0){
				sec=60;
				minu-=1;
				
			}
	
			sec-=1;
				
		}

			 if(pir_check==0){
					 minu=mj2;
				   sec=0;
					PIR_ON;
					
				}
			 else{
				 PIR_OFF;
				 
			 }
	}
				 	if(KEY==page_Pin && lev==0){

             dg=1;
           page1_menu( );
					
			}
		}   
		    // HAL_Delay(200);
		// HAL_I2C_Master_Transmit(&hi2c1,0x41,TX_Buffer7,1,100); //Sending in Blocking mode

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  
  /* USER CODE END 3 */
}
}
/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE
                              |RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_ADC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
