/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
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
#include "cmsis_os.h"
//#include "C:\Users\marcel\Documents\3_letnik\VGRS\lcd_rtos\lcd_rtos\Middlewares\Third_Party\src\ff.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f769i_discovery.h"
#include "stm32f769i_discovery_lcd.h"
#include "stm32f769i_discovery_ts.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "DefaultTask",
  .stack_size = 4096 * 4,
  .priority = (osPriority_t)  osPriorityNormal   ,
};

osThreadId_t task_led;
const osThreadAttr_t led_task_atributes = {
  .name = "Task_display",
  .stack_size = 128 * 4,
  .priority = (osPriority_t)  osPriorityNormal   ,
};

osThreadId_t task_led13;
const osThreadAttr_t led13_task_atributes = {
  .name = "Task_led",
  .stack_size = 128 * 4,
  .priority = (osPriority_t)  osPriorityNone   ,
};


/* USER CODE BEGIN PV */
uint8_t  lcd_status = LCD_OK;
uint32_t ts_status = TS_OK;
TS_StateTypeDef  TS_State = {0};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void StartDefaultTask(void *argument);
void Task_display(void *arg);
void Task_led(void *arg );
void one_image(void *arg);
/* USER CODE BEGIN PFP */
#define MAX_BMP_FILES 25
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
FATFS SD_FatFs;  /* File system object for SD card logical drive */
char SD_Path[4]; /* SD card logical drive path */
char* pDirectoryFiles[MAX_BMP_FILES];
uint8_t  ubNumberOfFiles = 0;
uint32_t uwBmplen = 0;
uint32_t counter = 0, transparency = 0;
		uint8_t str[30];

/* Internal Buffer defined in SDRAM memory */
uint8_t *uwInternalBuffer;


GPIO_InitTypeDef init_structure_A;
GPIO_InitTypeDef init_structure_D;

/* Private function prototypes -----------------------------------------------*/
static void MPU_Config(void);
static void LCD_Config(void);

static void CPU_CACHE_Enable(void);;

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */

int main(void)
{/*uint32_t  transparency = 0;
uint8_t str[30];
uwInternalBuffer = (uint8_t *)INTERNAL_BUFFER_START_ADDRESS;*/
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOJ_CLK_ENABLE();
	uwInternalBuffer = (uint8_t *)INTERNAL_BUFFER_START_ADDRESS;
  /* USER CODE BEGIN 1 */
	init_structure_A.Pin = GPIO_PIN_0 ;
	  init_structure_A.Mode = GPIO_MODE_INPUT;
	  init_structure_A.Pull = GPIO_NOPULL;
	  init_structure_A.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(GPIOA, &init_structure_A);


	  init_structure_D.Pin = GPIO_PIN_13 | GPIO_PIN_5 ;
	      init_structure_D.Mode = GPIO_MODE_OUTPUT_PP;
	      init_structure_D.Pull = GPIO_NOPULL;
	      init_structure_D.Speed = GPIO_SPEED_FREQ_LOW;
	      HAL_GPIO_Init(GPIOJ, &init_structure_D);

  /* USER CODE END 1 */

	 /* while(1){
		  if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)){
			  HAL_GPIO_TogglePin(GPIOJ,GPIO_PIN_13);

			  //HAL_Delay(1000);
			  //Error_Handler();
		  }

	}*/

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */

  MPU_Config();
  CPU_CACHE_Enable();
  HAL_Init();
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */
here:
  LCD_Config();

  // preverjanje kartice SD
  if(!BSP_SD_IsDetected())  {

	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_DisplayStringAtLine(8, (uint8_t*)"SD cart not inserted");
	while(1)
	{
	  if(BSP_SD_IsDetected())  {
		  BSP_LCD_Clear(LCD_COLOR_BLACK);
		  goto here;
	  }
	}
  }

  sd_init();


  one_image(1);
  //Task_display(1);
 // StartDefaultTask(1);*/

 /* BSP_LCD_Init();

  BSP_LCD_LayerDefaultInit(0, LCD_FB_START_ADDRESS);
  BSP_LCD_Clear(LCD_COLOR_WHITE);

  ts_status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
  while(ts_status != TS_OK);

  ts_status = BSP_TS_ITConfig();
  while(ts_status != TS_OK);

  uint8_t strptr[] = "Vesel bozic in srecno 2022!";
  BSP_LCD_SetFont(&Font24);
  BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
  BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
  BSP_LCD_DisplayStringAtLine(7, strptr);

  BSP_LCD_SetTextColor(LCD_COLOR_DARKRED);*/
  /* USER CODE END 2 */

  /* Init scheduler */
 // osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */

  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(one_image, NULL, &defaultTask_attributes);
  //task_led = osThreadNew(Task_display, NULL, &led_task_atributes);
  //task_led13 =osThreadNew(Task_led, NULL, &led13_task_atributes);
  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  //osKernelStart();
  vTaskStartScheduler();
  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */


    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;
  HAL_StatusTypeDef  ret = HAL_OK;

  /* Enable Power Control clock */
  __HAL_RCC_PWR_CLK_ENABLE();

  /* The voltage scaling allows optimizing the power consumption when the device is
	 clocked below the maximum system frequency, to update the voltage scaling value
	 regarding system frequency refer to product datasheet.  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /* Enable HSE Oscillator and activate PLL with HSE as source */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 432;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  RCC_OscInitStruct.PLL.PLLR = 7;

  ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
  if(ret != HAL_OK)
  {
	while(1) { ; }
  }

  /* Activate the OverDrive to reach the 216 MHz Frequency */
  ret = HAL_PWREx_EnableOverDrive();
  if(ret != HAL_OK)
  {
	while(1) { ; }
  }

  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);
  if(ret != HAL_OK)
  {
	while(1) { ; }
  }
}

void sd_init() {
	if(FATFS_LinkDriver(&SD_Driver, SD_Path) == 0)
		{
		  // incializacija kazalcev na slike
		  for (counter = 0; counter < MAX_BMP_FILES; counter++)
		  {
			pDirectoryFiles[counter] = malloc(MAX_BMP_FILE_NAME);
			if(pDirectoryFiles[counter] == NULL)
			{
			  // barva texta
			  BSP_LCD_SetTextColor(LCD_COLOR_RED);

			  BSP_LCD_DisplayStringAtLine(8, (uint8_t*)"Prevelika datoteka ");
			  while(1) { ; }
			}
		  }
		  // določanje števila datotek
		  ubNumberOfFiles = Storage_GetDirectoryBitmapFiles("/Media", pDirectoryFiles);

			  if (ubNumberOfFiles == 0)
			  {
				for (counter = 0; counter < MAX_BMP_FILES; counter++)
				{
				  free(pDirectoryFiles[counter]);
				}
				BSP_LCD_DisplayStringAtLine(8, (uint8_t*)" Ni bitnih slik  ");
				while(1) { ; }
			  }

		}
	return;
}
/* USER CODE BEGIN 4 */
void one_image(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */


  for(;;)
  {HAL_GPIO_TogglePin(GPIOJ,GPIO_PIN_5);
  //vTaskSuspendAll();
	  	  counter=0;
	      while ((counter) < ubNumberOfFiles)
	      {
	        /* brisanje lcd zaslona in formatiranje stringa oz. poti do slike*/
	    	BSP_LCD_Clear(LCD_COLOR_BLACK);
	        sprintf ((char*)str, "Media/%-11.11s", pDirectoryFiles[counter]);

	        if (Storage_CheckBitmapFile((const char*)str, &uwBmplen) == 0)
	        {
	        	 // formatiranje stringa

	        	sprintf ((char*)str, "Media/%-11.11s", pDirectoryFiles[counter]);



	          //aktivacina sloja zaslona
	          BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER_FOREGROUND);

	          // branje slike
	          Storage_OpenReadFile(uwInternalBuffer, (const char*)str);

	          // izris slike na zaslon
	          BSP_LCD_DrawBitmap(0, 0, uwInternalBuffer);


	          HAL_Delay(1000);



	            while(1) {
	            	// čakanje na gumb
	            	if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0))
	            		break;
	            	if(!BSP_SD_IsDetected())  {
	            		// v primeru izgube kartice
	            		BSP_LCD_Clear(LCD_COLOR_WHITE);
	            		BSP_LCD_SetTextColor(LCD_COLOR_RED);
	            		BSP_LCD_DisplayStringAtLine(8, (uint8_t*)"SD ni zaznana");

	            		while(1)
	            		{
	            			// v primeru vrnitve sd kartice
	            		  if(BSP_SD_IsDetected())  {
	            			  BSP_LCD_Clear(LCD_COLOR_BLACK);

	            			  NVIC_SystemReset();

	            		  }
	            		}
	            	  }
	            }
	            BSP_LCD_Clear(LCD_COLOR_BLACK);
	            HAL_Delay(1000);
	            counter++;
	          }
	          else if (Storage_CheckBitmapFile((const char*)str, &uwBmplen) == 0)
	          {
	            /* Barva izpisanega besedila */
	            BSP_LCD_SetTextColor(LCD_COLOR_RED);
	            // Prikaz texta
	            BSP_LCD_DisplayStringAtLine(7, (uint8_t *) str);
	            BSP_LCD_DisplayStringAtLine(8, (uint8_t*)"  Neveljaven tip datoteke");
	            while(1) { ; }
	          }

	      }
  }
  /* USER CODE END 5 */
}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */


void read_file(void *arg){

}
void Task_display(void *arg ){

	while(1){

		 HAL_GPIO_TogglePin(GPIOJ,GPIO_PIN_5);
			 osDelay(200);
	}

}

void Task_led(void *arg ){

	while(1){

		 HAL_GPIO_TogglePin(GPIOJ,GPIO_PIN_13);
			 osDelay(200);
	}

}

static void LCD_Config(void)
{
  uint8_t lcd_status = LCD_OK;

  /* LCD DSI initialization in mode Video Burst */
  /* Initialize DSI LCD */
  BSP_LCD_Init();
  while(lcd_status != LCD_OK);

  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER_BACKGROUND, LCD_FB_START_ADDRESS);

  /* Select the LCD Background Layer */
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER_BACKGROUND);

  /* Clear the Background Layer */
  BSP_LCD_Clear(LCD_COLOR_BLACK);

  BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER_FOREGROUND, LCD_BG_LAYER_ADDRESS);

  /* Select the LCD Foreground Layer */
  BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER_FOREGROUND);

  /* Clear the Foreground Layer */
  BSP_LCD_Clear(LCD_COLOR_BLACK);

  /* Configure the transparency for foreground and background :
  Increase the transparency */
  BSP_LCD_SetTransparency(LTDC_ACTIVE_LAYER_BACKGROUND, 0);
  BSP_LCD_SetTransparency(LTDC_ACTIVE_LAYER_FOREGROUND, 200);
}

static void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}

static void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct;

  /* Disable the MPU */
  HAL_MPU_Disable();

  /* Configure the MPU as Strongly ordered for not defined regions */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0x00;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Configure the MPU attributes as WT for SDRAM */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0xC0000000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_32MB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER1;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x00;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Configure the MPU attributes FMC control registers */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.BaseAddress = 0xA0000000;
  MPU_InitStruct.Size = MPU_REGION_SIZE_8KB;
  MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_BUFFERABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER2;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.SubRegionDisable = 0x0;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);

  /* Enable the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}
/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  BSP_LCD_Clear(LCD_COLOR_WHITE);
 	 	    	  BSP_LCD_SetTextColor(LCD_COLOR_RED);
 	 	    	  BSP_LCD_DisplayStringAtLine(8, (uint8_t*)"SD cart not inserted");
 	 	    	  while(1)
 	 	    	  {
 	 	    		  if(BSP_SD_IsDetected())  {
 	 	    			  BSP_LCD_Clear(LCD_COLOR_BLACK);
 	 	    			  return;
 	 	    		  }
 	 	    	  }
	    	  return;

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

