/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "stdio.h"
#include "string.h"

#include "Ethernet/wizchip_conf.h"
#include "Ethernet/socket.h"
#include "Application/loopback.h"
#include "Ethernet/w5500_spi.h"

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
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
static void PHYStatusCheck(void);
static void PrintPHYConf(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

//void W5500_Select(void) {
//    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
//}
//
//void W5500_Unselect(void) {
//    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
//}
//
//void W5500_ReadBuff(uint8_t* buff, uint16_t len) {
//    HAL_SPI_Receive(&hspi1, buff, len, HAL_MAX_DELAY);
//}
//
//void W5500_WriteBuff(uint8_t* buff, uint16_t len) {
//    HAL_SPI_Transmit(&hspi1, buff, len, HAL_MAX_DELAY);
//}
//
//uint8_t W5500_ReadByte(void) {
//    uint8_t byte;
//    W5500_ReadBuff(&byte, sizeof(byte));
//    return byte;
//}
//
//void W5500_WriteByte(uint8_t byte) {
//    W5500_WriteBuff(&byte, sizeof(byte));
//}

	wiz_NetInfo gWIZNETINFO = {
			.mac = { 0x80, 0x34, 0x28, 0x74, 0xA5, 0xCB },//MSB - LSB
			.ip ={ 192, 168, 1, 112 },
			.sn = { 255, 255, 255, 0 },
			.gw ={ 192, 168, 1, 1 },
			.dns = { 8, 8, 8, 8 },
			.dhcp = NETINFO_STATIC };

	uint8_t destination_ip[]={192,168,1,137};
	uint16_t destination_port=5000;


void PHYStatusCheck(void)
{
	uint8_t tmp;

	do
	{
		printf("\r\nChecking Ethernet Cable Presence ...");
		ctlwizchip(CW_GET_PHYLINK, (void*) &tmp);

		if(tmp == PHY_LINK_OFF)
		{
			printf("NO Cable Connected!");
			HAL_Delay(1500);
		}
	}while(tmp == PHY_LINK_OFF);

	printf("Good! Cable got connected!");

}

void PrintPHYConf(void)
{
	wiz_PhyConf phyconf;

	ctlwizchip(CW_GET_PHYCONF, (void*) &phyconf);

	if(phyconf.by==PHY_CONFBY_HW)
	{
		printf("\n\rPHY Configured by Hardware Pins");
	}
	else
	{
		printf("\n\rPHY Configured by Registers");
	}

	if(phyconf.mode==PHY_MODE_AUTONEGO)
	{
		printf("\n\rAutonegotiation Enabled");
	}
	else
	{
		printf("\n\rAutonegotiation NOT Enabled");
	}

	if(phyconf.duplex==PHY_DUPLEX_FULL)
	{
		printf("\n\rDuplex Mode: Full");
	}
	else
	{
		printf("\n\rDuplex Mode: Half");
	}

	if(phyconf.speed==PHY_SPEED_10)
	{
		printf("\n\rSpeed: 10Mbps");
	}
	else
	{
		printf("\n\rSpeed: 100Mbps");
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

//	uint8_t retVal, sockStatus;
//	int16_t rcvLen;
//	uint8_t rcvBuff[20];
//	uint8_t bufSize[] = {2, 2, 2, 2, 2, 2, 2, 2};



  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  setbuf(stdout, NULL);

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  //MX_GPIO_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

  W5500Init();

  HAL_Delay(1000);

  ctlnetwork(CN_SET_NETINFO, (void*)&gWIZNETINFO);

  HAL_Delay(1000);

  wiz_PhyConf phyConf;

  phyConf.by = PHY_CONFBY_SW;
  phyConf.duplex = PHY_DUPLEX_FULL;
  phyConf.speed = PHY_SPEED_10;
  phyConf.mode = PHY_MODE_AUTONEGO;

  ctlwizchip(CW_SET_PHYCONF, (void*)&phyConf);

  HAL_Delay(1000);

  PHYStatusCheck();

  HAL_Delay(1000);

  PrintPHYConf();
  HAL_Delay(1000);


  if( socket(1, Sn_MR_TCP, 0, 0) )
  {
	  printf("\r\nSocket created successfully..");
  }
  else
  {
	  printf("\r\nSocket cannot created..");
	  //while(1);
  }

  if(connect( 1, destination_ip, destination_port ) == SOCK_OK )
  {
	  printf("Connected with server");
  }
  else
  {
	  printf("Cannot connect");
  }

  //HAL_Delay(1000);




//  reg_wizchip_cs_cbfunc(W5500_Select, W5500_Unselect);
//  reg_wizchip_spi_cbfunc(W5500_ReadByte, W5500_WriteByte);
//  reg_wizchip_spiburst_cbfunc(W5500_ReadBuff, W5500_WriteBuff);
//
//  wizchip_init(bufSize, bufSize);
//  wiz_NetInfo netInfo = {
//		  .mac = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED},
//		  .ip = {192, 168, 1, 177},
//		  .sn = {255, 255, 255, 0},
//		  .gw = {192, 168, 1, 1},
//		  .dns = {8, 8, 8, 8},
//		  .dhcp = NETINFO_STATIC
//
//  };
//
//  wizchip_setnetinfo(&netInfo);
//  HAL_Delay(1000);
//
//
//  wizchip_getnetinfo(&netInfo);
//
//  uint8_t s = 0, serverip[4] = {192, 168, 1, 137};
//  uint8_t baglan;
//  uint8_t tx[] = "Enes Cicek";
//  uint8_t txSize = 11;
//
//  uint16_t received_len;
//  uint8_t RSR_len;
//  uint8_t data_buf[30];
//  uint8_t Kop;


char *txt = "Hello everyone, what's up...................................enes is onlineee anymore...\n\r";


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

	  if( send(1, (uint8_t*)txt, strlen(txt))<SOCK_ERROR )
	  {
		  printf("Sending fail");
		  //while(1);
	  }
	  else
	  {
		  printf("SEnding success");
	  }

	  HAL_Delay(1000);

//	  socket(s, Sn_MR_TCP, 5656, SF_TCP_NODELAY);
//
//	  while(baglan != SOCK_OK)
//	  {
//		  baglan = connect(s, serverip, 5656);
//	  }
//	  baglan = 0;
//	  send(s, tx, txSize);
//
//	  while(received_len == 0)
//	  {
//		  if( (RSR_len = getSn_RX_RSR(s) ) > 0)
//			  received_len = recv(s, data_buf, RSR_len);
//	  }
//
//	  while(SOCK_OK != Kop)
//	  Kop=close(s);
//	  Kop=0;
//
//	  HAL_Delay(2500);
//	  received_len = 0;

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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */
  __HAL_SPI_ENABLE(&hspi1);
  /* USER CODE END SPI1_Init 2 */

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_10, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA4 PA10 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
