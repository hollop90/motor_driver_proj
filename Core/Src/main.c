/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "math.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>

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

/* USER CODE BEGIN PV */
int sine1_idx = 0;
int sine2_idx = 107;
int sine3_idx = 211;

int pwm_on = 1;
int pwmn_on = 0;

int pwm_on2 = 0;
int pwmn_on2 = 1;

int pwm_on3 = 1;
int pwmn_on3 = 0;

int sine_vals[] = {
    0,
    19,
    39,
    58,
    78,
    98,
    117,
    137,
    156,
    176,
    196,
    215,
    235,
    254,
    274,
    293,
    312,
    332,
    351,
    370,
    390,
    409,
    428,
    447,
    466,
    485,
    504,
    523,
    542,
    561,
    580,
    599,
    618,
    636,
    655,
    673,
    692,
    710,
    728,
    747,
    765,
    783,
    801,
    819,
    837,
    855,
    872,
    890,
    907,
    925,
    942,
    960,
    977,
    994,
    1011,
    1028,
    1044,
    1061,
    1078,
    1094,
    1111,
    1127,
    1143,
    1159,
    1175,
    1191,
    1207,
    1222,
    1238,
    1253,
    1268,
    1283,
    1298,
    1313,
    1328,
    1343,
    1357,
    1371,
    1386,
    1400,
    1414,
    1428,
    1441,
    1455,
    1468,
    1481,
    1495,
    1507,
    1520,
    1533,
    1546,
    1558,
    1570,
    1582,
    1594,
    1606,
    1618,
    1629,
    1640,
    1651,
    1662,
    1673,
    1684,
    1694,
    1705,
    1715,
    1725,
    1735,
    1744,
    1754,
    1763,
    1773,
    1782,
    1790,
    1799,
    1807,
    1816,
    1824,
    1832,
    1840,
    1847,
    1855,
    1862,
    1869,
    1876,
    1883,
    1889,
    1895,
    1902,
    1908,
    1913,
    1919,
    1924,
    1930,
    1935,
    1940,
    1944,
    1949,
    1953,
    1957,
    1961,
    1965,
    1968,
    1972,
    1975,
    1978,
    1981,
    1983,
    1986,
    1988,
    1990,
    1992,
    1993,
    1995,
    1996,
    1997,
    1998,
    1999,
    1999,
    1999,
    2000,
    1999,
    1999,
    1999,
    1998,
    1997,
    1996,
    1995,
    1993,
    1992,
    1990,
    1988,
    1986,
    1983,
    1981,
    1978,
    1975,
    1972,
    1968,
    1965,
    1961,
    1957,
    1953,
    1949,
    1944,
    1940,
    1935,
    1930,
    1924,
    1919,
    1913,
    1908,
    1902,
    1895,
    1889,
    1883,
    1876,
    1869,
    1862,
    1855,
    1847,
    1840,
    1832,
    1824,
    1816,
    1807,
    1799,
    1790,
    1782,
    1773,
    1763,
    1754,
    1744,
    1735,
    1725,
    1715,
    1705,
    1694,
    1684,
    1673,
    1662,
    1651,
    1640,
    1629,
    1618,
    1606,
    1594,
    1582,
    1570,
    1558,
    1546,
    1533,
    1520,
    1507,
    1495,
    1481,
    1468,
    1455,
    1441,
    1428,
    1414,
    1400,
    1386,
    1371,
    1357,
    1343,
    1328,
    1313,
    1298,
    1283,
    1268,
    1253,
    1238,
    1222,
    1207,
    1191,
    1175,
    1159,
    1143,
    1127,
    1111,
    1094,
    1078,
    1061,
    1044,
    1028,
    1011,
    994,
    977,
    960,
    942,
    925,
    907,
    890,
    872,
    855,
    837,
    819,
    801,
    783,
    765,
    747,
    728,
    710,
    692,
    673,
    655,
    636,
    618,
    599,
    580,
    561,
    542,
    523,
    504,
    485,
    466,
    447,
    428,
    409,
    390,
    370,
    351,
    332,
    312,
    293,
    274,
    254,
    235,
    215,
    196,
    176,
    156,
    137,
    117,
    98,
    78,
    58,
    39,
    19
};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
long adc_raw;
long tim_val;
char buff[50] = {};
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
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);

  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);

  HAL_TIM_OC_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_Base_Start_IT(&htim2);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
	  HAL_ADC_Start(&hadc1);
	  HAL_ADC_PollForConversion(&hadc1, 1000);
	  adc_raw = HAL_ADC_GetValue(&hadc1);
	  tim_val = uu_map(adc_raw, 0, 4095, 200, 2000);
	  TIM2->ARR = tim_val;
	  TIM2->EGR |= 1 <<(TIM_EGR_UG_Pos);

	  sprintf(buff, "adc: %d\r\n", adc_raw);
	  HAL_UART_Transmit(&huart2, buff, sizeof(buff), 1000);

	  sprintf(buff, "map: %d\r\n\n", tim_val);
	  HAL_UART_Transmit(&huart2, buff, sizeof(buff), 1000);

	  HAL_Delay(100);

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 16;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */


// Callback: timer has rolled over
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  // Check which version of the timer triggered this callback and toggle LED
  if (htim == &htim2)
  {
    sine1_idx++;
    sine2_idx++;
    sine3_idx++;

    // Overflow
    if (sine1_idx > 319)
    {
      // Reset
      sine1_idx = 0;
      // Toggle phases
      pwm_on = !pwm_on;
      pwmn_on = !pwmn_on;

      // Channel 1
      if (pwm_on)
      {
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
      }
      else
      {
        HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
      }

      if (pwmn_on)
      {
    	  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
      }
      else
      {
    	  HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);
      }
    }
    TIM1->CCR1 = sine_vals[sine1_idx];


    if (sine2_idx > 319)
    {
      sine2_idx = 0;
      pwm_on2 = !pwm_on2;
      pwmn_on2 = !pwmn_on2;

      // Channel 2
      if (pwm_on2)
      {
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
      }
      else
      {
        HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
      }

      if (pwmn_on2)
      {
    	  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
      }
      else
      {
    	  HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
      }
    }
    TIM1->CCR2 = sine_vals[sine2_idx];
    //return;

    if (sine3_idx > 319)
    {
      sine3_idx = 0;
      pwm_on3 = !pwm_on3;
      pwmn_on3 = !pwmn_on3;

      // Channel 3
      if (pwm_on3)
      {
        HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
      }
      else
      {
        HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
      }

      if (pwmn_on3)
      {
    	  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);
      }
      else
      {
    	  HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_3);
      }
    }
    TIM1->CCR3 = sine_vals[sine3_idx];
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
	  sprintf(buff, "ERROR\r\n");
	  HAL_UART_Transmit(&huart2, buff, sizeof(buff), 1000);
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
