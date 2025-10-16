/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "software_timer.h"
#include <stdbool.h>
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
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//int timer0_counter = 0;
//int timer0_flag = 0;
//int TIMER_CYCLE = 10;
//void setTimer0 ( int duration ) {
//	timer0_counter = duration / TIMER_CYCLE ;
//	timer0_flag = 0;
//}
//void timer_run () {
//	if ( timer0_counter > 0) {
//		timer0_counter--;
//		if ( timer0_counter == 0) timer0_flag = 1;
//	}
//}

void activeLedSEG(char str[], int length) {
  for (int i=0; i<length; ++i){
    switch (str[i])
    {
    case 'a':
      HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, RESET);
      break;
    case 'b':
      HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, RESET);
      break;
    case 'c':
      HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, RESET);
      break;
    case 'd':
      HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, RESET);
      break;
    case 'e':
      HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, RESET);
      break;
    case 'f':
      HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, RESET);
      break;
    case 'g':
      HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, RESET);
      break;
    default:
      break;
    }
  }
  return;
}
// function to control 7-led-segments, str[] is array contain segments to negative
// and length is length of str[]
void disableLedSEG(char str[], int length) {
  for (int i=0; i<length; ++i){
    switch (str[i])
    {
    case 'a':
      HAL_GPIO_WritePin(a_GPIO_Port, a_Pin, SET);
      break;
    case 'b':
      HAL_GPIO_WritePin(b_GPIO_Port, b_Pin, SET);
      break;
    case 'c':
      HAL_GPIO_WritePin(c_GPIO_Port, c_Pin, SET);
      break;
    case 'd':
      HAL_GPIO_WritePin(d_GPIO_Port, d_Pin, SET);
      break;
    case 'e':
      HAL_GPIO_WritePin(e_GPIO_Port, e_Pin, SET);
      break;
    case 'f':
      HAL_GPIO_WritePin(f_GPIO_Port, f_Pin, SET);
      break;
    case 'g':
      HAL_GPIO_WritePin(g_GPIO_Port, g_Pin, SET);
      break;
    default:
      break;
    }
  }
  return;
}
// function to control 7-led-segments
void display7SEG(int num){
	switch (num) {
		case 0:
			activeLedSEG("abcdef", 6);
			disableLedSEG("g", 1);
			break;
		case 1:
			activeLedSEG("bc", 2);
			disableLedSEG("adefg", 5);
			break;
		case 2:
			activeLedSEG("abdeg", 5);
			disableLedSEG("cf", 2);
			break;
		case 3:
			activeLedSEG("abcdg", 5);
			disableLedSEG("ef", 2);
			break;
		case 4:
			activeLedSEG("bcfg", 4);
			disableLedSEG("ade", 3);
			break;
		case 5:
			activeLedSEG("acdfg", 5);
			disableLedSEG("be", 2);
			break;
		case 6:
			activeLedSEG("acdefg", 6);
			disableLedSEG("b", 1);
			break;
		case 7:
			activeLedSEG("abc", 3);
			disableLedSEG("defg", 4);
			break;
		case 8:
			activeLedSEG("abcdefg", 7);
			break;
		case 9:
			activeLedSEG("abcdfg", 6);
			disableLedSEG("e", 1);
			break;
		default:
			disableLedSEG("abcdefg", 7);
			break;
	}
	return;
}
// function to control EN
void controlENs(int num){
	switch(num){
	case 0:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
		break;
	case 1:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
		break;
	case 2:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, RESET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
		break;
	case 3:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, RESET);
		break;
	default:
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
		break;
	}
}

//Exercise 3
const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4] = {1,2,3,4};
void update7SEG(int index){
	switch(index){
	case 0:
		display7SEG(led_buffer[0]);
		break;
	case 1:
		display7SEG(led_buffer[1]);
		break;
	case 2:
		display7SEG(led_buffer[2]);
		break;
	case 3:
		display7SEG(led_buffer[3]);
		break;
	default:
		break;
	}
}

void disableAllEN(){
	HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
	HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
	HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
}

int hour = 15, minute = 0, second = 15;
void updateClockBuffer() {
	led_buffer[0] = hour % 10;
	led_buffer[1] = hour / 10;
	led_buffer[2] = minute % 10;
	led_buffer[3] = minute / 10;
}


//ex9
// ROW ON
#define ROW0_ON() HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, RESET)
#define ROW1_ON() HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, RESET)
#define ROW2_ON() HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, RESET)
#define ROW3_ON() HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, RESET)
#define ROW4_ON() HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, RESET)
#define ROW5_ON() HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, RESET)
#define ROW6_ON() HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, RESET)
#define ROW7_ON() HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, RESET)
// ROW OFF
#define ROW0_OFF() HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, SET)
#define ROW1_OFF() HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, SET)
#define ROW2_OFF() HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, SET)
#define ROW3_OFF() HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, SET)
#define ROW4_OFF() HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, SET)
#define ROW5_OFF() HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, SET)
#define ROW6_OFF() HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, SET)
#define ROW7_OFF() HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, SET)
// COL OFF
#define COL0_OFF() HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, SET)
#define COL1_OFF() HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, SET)
#define COL2_OFF() HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, SET)
#define COL3_OFF() HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, SET)
#define COL4_OFF() HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, SET)
#define COL5_OFF() HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, SET)
#define COL6_OFF() HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, SET)
#define COL7_OFF() HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, SET)
//COL ON
#define COL0_ON() HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, RESET)
#define COL1_ON() HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, RESET)
#define COL2_ON() HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, RESET)
#define COL3_ON() HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, RESET)
#define COL4_ON() HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, RESET)
#define COL5_ON() HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, RESET)
#define COL6_ON() HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, RESET)
#define COL7_ON() HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, RESET)

void disableAllLEDMatrix(){
	// disable COLs (ENM)
	COL0_OFF();
	COL1_OFF();
	COL2_OFF();
	COL3_OFF();
	COL4_OFF();
	COL5_OFF();
	COL6_OFF();
	COL7_OFF();
	// disable ROWs
	ROW0_OFF();
	ROW1_OFF();
	ROW2_OFF();
	ROW3_OFF();
	ROW4_OFF();
	ROW5_OFF();
	ROW6_OFF();
	ROW7_OFF();
}

void activeRow(int num){
	switch(num){
	case 0:
		ROW0_ON();
		break;
	case 1:
		ROW1_ON();
		break;
	case 2:
		ROW2_ON();
		break;
	case 3:
		ROW3_ON();
		break;
	case 4:
		ROW4_ON();
		break;
	case 5:
		ROW5_ON();
		break;
	case 6:
		ROW6_ON();
		break;
	case 7:
		ROW7_ON();
		break;
	default:
		disableAllLEDMatrix();
		break;
	}
}
// function control led in col
void activeCol(int index){
	switch(index){
		case 0:
			COL0_ON();
			break;
		case 1:
			COL1_ON();
			break;
		case 2:
			COL2_ON();
			break;
		case 3:
			COL3_ON();
			break;
		case 4:
			COL4_ON();
			break;
		case 5:
			COL5_ON();
			break;
		case 6:
			COL6_ON();
			break;
		case 7:
			COL7_ON();
			break;
		default:
			disableAllLEDMatrix();
			break;

	}
}

const int MAX_LED_MATRIX = 8;
int index_led_matrix = 0;
// Buffer Animation
uint8_t Ani[4][8] = {
		{0x7E, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
		{0x66, 0x66, 0x66, 0x7E, 0x7E, 0x66, 0x66, 0x66},
		{0x18, 0x3C, 0x24, 0x24, 0x3C, 0x3C, 0x24, 0x24},
		{0x18, 0x3C, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18}
};
uint8_t matrix_buffer[8] = {0x18, 0x18, 0x18, 0x18, 0xFF, 0x7E, 0x3C, 0x18};
// update matrix_buffer to animation
int countBuffer = 0;
void updateBuffer(){
	for (int i =0; i< MAX_LED_MATRIX; i++){
		matrix_buffer[i] = Ani[countBuffer][i];
	}
	countBuffer++;
	if (countBuffer >= 4) {
		countBuffer = 0;
	}
}

void controlRowLed(uint8_t matrix_buffer){
	for (int i =0 ;i <MAX_LED_MATRIX; i++){
		bool statusLed = (matrix_buffer >> (7 - i)) & 1;
		if (statusLed == 1) {
			activeCol(i);
		}
	}
}
// function using maxtrix_buffer to control led in a Row
void updateLEDMatrix(int index){
	switch(index){
	case 0:
		controlRowLed(matrix_buffer[0]);
		break;
	case 1:
		controlRowLed(matrix_buffer[1]);
		break;
	case 2:
		controlRowLed(matrix_buffer[2]);
		break;
	case 3:
		controlRowLed(matrix_buffer[3]);
		break;
	case 4:
		controlRowLed(matrix_buffer[4]);
		break;
	case 5:
		controlRowLed(matrix_buffer[5]);
		break;
	case 6:
		controlRowLed(matrix_buffer[6]);
		break;
	case 7:
		controlRowLed(matrix_buffer[7]);
		break;
	default:
		disableAllLEDMatrix();
		break;
	}
}
// function display led_matrix
void displayLedMatrix() {
	if (index_led_matrix < 8) {
		// disable all led in led matrix before scan led
		disableAllLEDMatrix();
		// active Row follows index_led_matrix
		activeRow(index_led_matrix);
		// control Led index in Row follows matrix_buffer
		updateLEDMatrix(index_led_matrix);
	}
	index_led_matrix++;
	// check index of led, if it exceed MAX_LED_MATRIX, reset it
	if (index_led_matrix >= 8) {
		index_led_matrix = 0;
	}
}
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
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
    // timer for led matrix
  	setTimer0(10);
    // timer for LED_RED, this led show program running
    setTimer1(100);
    // counter to updateBuffer
    int counter = 0;
    while (1)
    {
  	  if (timer0_flag == 1){
  		  setTimer0(10);
  		  // TODO
  		  displayLedMatrix();
  		  counter++;
  		  if (counter >= 8){
  			  updateBuffer();
  			  counter = 0;
  		  }
  	  }
  	  if (timer1_flag == 1){
  		  setTimer1(100);
  		  // TODO
  		  HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
  	  }
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, a_Pin|b_Pin|c_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|d_Pin|e_Pin|f_Pin
                          |g_Pin|ROW0_Pin|ROW1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ENM0_Pin ENM1_Pin DOT_Pin LED_RED_Pin
                           EN0_Pin EN1_Pin EN2_Pin EN3_Pin
                           ENM2_Pin ENM3_Pin ENM4_Pin ENM5_Pin
                           ENM6_Pin ENM7_Pin */
  GPIO_InitStruct.Pin = ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : a_Pin b_Pin c_Pin ROW2_Pin
                           ROW3_Pin ROW4_Pin ROW5_Pin ROW6_Pin
                           ROW7_Pin d_Pin e_Pin f_Pin
                           g_Pin ROW0_Pin ROW1_Pin */
  GPIO_InitStruct.Pin = a_Pin|b_Pin|c_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|d_Pin|e_Pin|f_Pin
                          |g_Pin|ROW0_Pin|ROW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	timerRun();
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
