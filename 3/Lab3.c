/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TIME 50
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
static void displayOff();
static void my_display(uint8_t number);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

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
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  uint16_t counter=0;
  displayOff();
  uint8_t flag = 1;
  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_3,GPIO_PIN_RESET);//reset diod pod wyswietlaczem
  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_4,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_5,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_6,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_8,GPIO_PIN_RESET);
  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_9,GPIO_PIN_RESET);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    while (1)
    {
		displayOff();
		my_display(counter);
    	for(uint8_t i = 0;i<20;i++)
		{
			HAL_Delay(TIME);
			if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_15)==GPIO_PIN_RESET)
			{
				while(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_15)==GPIO_PIN_RESET)
				{

				}
				if(flag<=0)
				{
					flag = 1;
				}
				else
				{
					flag = 0;
				}
			}
		}

		if(flag==1)
		{
			if(counter >= 9)
			{
				//flag = 0;
				counter = 0;
				continue;
			}
			counter++;
		}
		else
		{
			if(counter <= 0)
			{
				//flag = 1;
				counter = 9;
				continue;
			}
			counter--;
		}
    }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  HAL_PWREx_EnableVddIO2();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE4 PE5 PE6 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PB2 PB3 PB4 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PG0 PG1 PG2 PG3
                           PG4 PG5 PG6 PG9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : PE15 */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PC6 PC7 PC8 PC9 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PD3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
static void displayOff(){
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_0,GPIO_PIN_RESET); 	//gora
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_1,GPIO_PIN_RESET); 	//prawagora
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,GPIO_PIN_RESET);		//prawadol
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_3,GPIO_PIN_RESET);		//dol
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_4,GPIO_PIN_RESET);		//lewydol
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_5,GPIO_PIN_RESET);		//lewagora
	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_RESET);		//srodek
}
static void my_display(uint8_t number){
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_3,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_4,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_SET);

	if(number==0)
	{
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_0,GPIO_PIN_SET); 	//gora
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_1,GPIO_PIN_SET); 	//prawagora
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,GPIO_PIN_SET);	//prawadol
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_3,GPIO_PIN_SET);	//dol
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_4,GPIO_PIN_SET);	//lewydol
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_5,GPIO_PIN_SET);	//lewagora
	}
	else if(number==1)
	{
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_1,GPIO_PIN_SET); 	//prawagora
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,GPIO_PIN_SET);	//prawadol
	}
	else if(number==2)
	{
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_0,GPIO_PIN_SET); 	//gora
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_1,GPIO_PIN_SET); 	//prawagora
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_3,GPIO_PIN_SET);	//dol
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_4,GPIO_PIN_SET);	//lewydol
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_SET);	//srodek
	}
	else if(number==3)
	{
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_0,GPIO_PIN_SET); 	//gora
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_1,GPIO_PIN_SET); 	//prawagora
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,GPIO_PIN_SET);	//prawadol
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_3,GPIO_PIN_SET);	//dol
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_SET);	//srodek
	}
	else if(number==4)
	{
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_1,GPIO_PIN_SET); 	//prawagora
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,GPIO_PIN_SET);	//prawadol
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_5,GPIO_PIN_SET);	//lewagora
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_SET);	//srodek
	}
	else if(number==5)
	{
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_0,GPIO_PIN_SET); 	//gora
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,GPIO_PIN_SET);	//prawadol
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_3,GPIO_PIN_SET);	//dol
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_5,GPIO_PIN_SET);	//lewagora
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_SET);	//srodek
	}
	else if(number==6)
	{
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_0,GPIO_PIN_SET); 	//gora
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,GPIO_PIN_SET);	//prawadol
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_3,GPIO_PIN_SET);	//dol
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_4,GPIO_PIN_SET);	//lewydol
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_5,GPIO_PIN_SET);	//lewagora
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_SET);	//srodek
	}
	else if(number==7)
	{
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_0,GPIO_PIN_SET); 	//gora
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_1,GPIO_PIN_SET); 	//prawagora
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,GPIO_PIN_SET);	//prawadol
	}
	else if(number==8)
	{
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_0,GPIO_PIN_SET); 	//gora
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_1,GPIO_PIN_SET); 	//prawagora
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,GPIO_PIN_SET);	//prawadol
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_3,GPIO_PIN_SET);	//dol
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_4,GPIO_PIN_SET);	//lewydol
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_5,GPIO_PIN_SET);	//lewagora
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_SET);	//srodek
	}
	else if(number==9)
	{
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_0,GPIO_PIN_SET); 	//gora
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_1,GPIO_PIN_SET); 	//prawagora
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,GPIO_PIN_SET);	//prawadol
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_3,GPIO_PIN_SET);	//dol
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_5,GPIO_PIN_SET);	//lewagora
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_6,GPIO_PIN_SET);	//srodek
	}

}
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

