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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
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
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */
uint16_t timer_value;
char  *limit_message_y="X EKSENI SINIRDA!!!!!!!\n";
int stepNumber_x,stepNumber_e,stepNumber_d,stepNumber_c,rx_for_set[15];
float current_angel_x=0,current_angel_e=0,current_angel_c=0,current_angel_d=0;
int x_direction_flag_forward=0,x_direction_flag_backward=0,e_direction_flag_forward=0,e_direction_flag_backward=0,d_direction_flag_forward=0,d_direction_flag_backward=0,c_direction_flag_forward=0,c_direction_flag_backward=0;
uint8_t rx_tem_buffer[15],rx_buffer[15];
int interup_counter=0,tem_interup_counter=0;
int rx_step_x_int[2],rx_step_x_angel=0,step_num_check_x=0,step_num_check_e=0,step_num_check_d=0,step_num_check_c=0,for_counter_1=0,set_for_i_yeni_3=0,rx_for_set_int[5],rx_for_set_integer=0;
int rx_step_e_angel=0,rx_step_d_angel=0,rx_step_c_angel=0,rx_step_e_int[2],rx_step_d_int[2],rx_step_c_int[2];
int switch_konum_x=0,switch_konum_d=0,switch_konum_c=0,switch_konum_e=0;

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void delay_us (uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&htim1,0);  // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(&htim1) < us);  // wait for the counter to reach the us input in the parameter
	timer_value=__HAL_TIM_GET_COUNTER(&htim1);
}
//MOTOR X KONTROL SWITCH CASE
void fullStepRotate_x(int step){


			switch(step){


			case 0:
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);


			break;
		  case 1:
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);

			break;
		}

	}
void move_function(){
	for(int i=0;i<5;i++){
//base motor function
	for(int seq=0; seq<=1500; seq++){
		if(HAL_GPIO_ReadPin(e_limit_GPIO_Port, e_limit_Pin)){
			break;
		}
		  HAL_GPIO_WritePin(GPIOC,dir_e_Pin,GPIO_PIN_SET);

		HAL_GPIO_WritePin(step_e_GPIO_Port,step_e_Pin ,GPIO_PIN_SET);
		delay_us(5000);
		HAL_GPIO_WritePin(step_e_GPIO_Port,step_e_Pin ,GPIO_PIN_RESET);
		delay_us(5000);
	}
	// motor d function

	for(int i=0;i<2000;i++){
		if(HAL_GPIO_ReadPin(d_limit_GPIO_Port, d_limit_Pin)){
			break;
		}

		HAL_GPIO_WritePin(dir_d_GPIO_Port,dir_d_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(step_d_GPIO_Port,step_d_Pin ,GPIO_PIN_SET);
		delay_us(1000);
		HAL_GPIO_WritePin(step_d_GPIO_Port,step_d_Pin ,GPIO_PIN_RESET);
		delay_us(1000);
	}
	// motor x function
	for(int i=0;i<3400;i++){
		if(HAL_GPIO_ReadPin(x_limit_GPIO_Port, x_limit_Pin)){
			break;
		}
		HAL_GPIO_WritePin(dir_x_GPIO_Port,dir_x_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(step_x_GPIO_Port,step_x_Pin ,GPIO_PIN_SET);
		delay_us(1000);
		HAL_GPIO_WritePin(step_x_GPIO_Port,step_x_Pin ,GPIO_PIN_RESET);
		delay_us(1000);
	}

	// motor x function


	// motor x function
	for(int i=0;i<1500;i++){
		if(HAL_GPIO_ReadPin(e_limit_GPIO_Port, e_limit_Pin)){
			break;
		}
		  HAL_GPIO_WritePin(GPIOC,dir_e_Pin,GPIO_PIN_RESET);

		HAL_GPIO_WritePin(step_e_GPIO_Port,step_e_Pin ,GPIO_PIN_SET);
		delay_us(5000);
		HAL_GPIO_WritePin(step_e_GPIO_Port,step_e_Pin ,GPIO_PIN_RESET);
		delay_us(5000);
	}
		for(int i=0;i<3400;i++){
		if(HAL_GPIO_ReadPin(x_limit_GPIO_Port, x_limit_Pin)){
			break;
		}
		HAL_GPIO_WritePin(dir_x_GPIO_Port,dir_x_Pin,GPIO_PIN_SET);

		HAL_GPIO_WritePin(step_x_GPIO_Port,step_x_Pin ,GPIO_PIN_SET);
		delay_us(1000);
		HAL_GPIO_WritePin(step_x_GPIO_Port,step_x_Pin ,GPIO_PIN_RESET);
		delay_us(1000);
	}
	//GERİ DÖNÜŞ
	for(int seq=0; seq<=1500; seq++){
		if(HAL_GPIO_ReadPin(e_limit_GPIO_Port, e_limit_Pin)){
			break;
		}
		  HAL_GPIO_WritePin(GPIOC,dir_e_Pin,GPIO_PIN_SET);

		HAL_GPIO_WritePin(step_e_GPIO_Port,step_e_Pin ,GPIO_PIN_SET);
		delay_us(5000);
		HAL_GPIO_WritePin(step_e_GPIO_Port,step_e_Pin ,GPIO_PIN_RESET);
		delay_us(5000);
	}
	// motor d function

	for(int i=0;i<2000;i++){
		if(HAL_GPIO_ReadPin(d_limit_GPIO_Port, d_limit_Pin)){
			break;
		}
		HAL_GPIO_WritePin(dir_d_GPIO_Port,dir_d_Pin,GPIO_PIN_SET);

		HAL_GPIO_WritePin(step_d_GPIO_Port,step_d_Pin ,GPIO_PIN_SET);
		delay_us(1000);
		HAL_GPIO_WritePin(step_d_GPIO_Port,step_d_Pin ,GPIO_PIN_RESET);
		delay_us(1000);
	}
	// motor x function
	for(int i=0;i<3400;i++){
		if(HAL_GPIO_ReadPin(x_limit_GPIO_Port, x_limit_Pin)){
			break;
		}
		HAL_GPIO_WritePin(dir_x_GPIO_Port,dir_x_Pin,GPIO_PIN_SET);

		HAL_GPIO_WritePin(step_x_GPIO_Port,step_x_Pin ,GPIO_PIN_SET);
		delay_us(1000);
		HAL_GPIO_WritePin(step_x_GPIO_Port,step_x_Pin ,GPIO_PIN_RESET);
		delay_us(1000);
	}

	// motor x function


	// motor e function
	for(int i=0;i<1500;i++){
		HAL_GPIO_WritePin(step_e_GPIO_Port,step_e_Pin ,GPIO_PIN_SET);
		delay_us(5000);
		HAL_GPIO_WritePin(step_e_GPIO_Port,step_e_Pin ,GPIO_PIN_RESET);
		delay_us(5000);
	}
	for(int i=0;i<3000;i++){
		if(HAL_GPIO_ReadPin(x_limit_GPIO_Port, x_limit_Pin)){
			break;
		}
		HAL_GPIO_WritePin(dir_d_GPIO_Port,dir_d_Pin,GPIO_PIN_RESET);

		HAL_GPIO_WritePin(step_x_GPIO_Port,step_x_Pin ,GPIO_PIN_SET);
		delay_us(1000);
		HAL_GPIO_WritePin(step_x_GPIO_Port,step_x_Pin ,GPIO_PIN_RESET);
		delay_us(1000);
	}


	}
}
void setStepper_x(int angle,int direction,int speed){
	float perAngle=1.8;//  360/200=1.8(per step angle)
	stepNumber_x=(int)(angle/perAngle);

	for(int seq=0; seq<=stepNumber_x; seq++){

		if(current_angel_x>8000){
			if(direction==1){// saat yonunun tersi
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
				for(int step=4; step>=0; step--){
					if(HAL_GPIO_ReadPin(x_limit_GPIO_Port,x_limit_Pin)){
								current_angel_x=0;
								break;
							}


					fullStepRotate_x(step);
					x_direction_flag_backward=1;
					x_direction_flag_forward=0;
					delay_us(1000);
				}
				current_angel_x-=1.8;


		}
			break;
		}

		if(current_angel_x<8000){



			if(direction==0){
				HAL_GPIO_WritePin(GPIOA, dir_x_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_RESET);


				for(int step=0; step<2; step++){//saat yonunde

					fullStepRotate_x(step);
					x_direction_flag_forward=1;
					x_direction_flag_backward=0;

					delay_us(1000);
				}
				current_angel_x+=1.8;


			}else if(direction==1){// saat yonunun tersi
				HAL_GPIO_WritePin(GPIOA, dir_x_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12, GPIO_PIN_SET);


				for(int step=0; step<2; step++){
					if(HAL_GPIO_ReadPin(x_limit_GPIO_Port,x_limit_Pin)){
								current_angel_x=0;

								break;


					}			fullStepRotate_x(step);
								x_direction_flag_backward=1;
								x_direction_flag_forward=0;
								delay_us(1000);



				}
				current_angel_x-=1.8;



			}

		}
		else{
			HAL_UART_Transmit(&huart1, (uint8_t*)limit_message_y,strlen(limit_message_y),100);

			if(direction==1){
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);

				for(int step=0; step<2; step++){
					fullStepRotate_x(step);
					delay_us(5000);
					x_direction_flag_backward=1;
					x_direction_flag_forward=0;
			}
				current_angel_x-=1.8;


		}
	}

}
	if(x_direction_flag_forward==1&&x_direction_flag_backward==0){
		//current_angel_x+=angle;
		x_direction_flag_forward=0;
		x_direction_flag_backward=0;
	}
	else if (x_direction_flag_forward==0&&x_direction_flag_backward==1){
		//current_angel_x-=angle;
		x_direction_flag_forward=0;
		x_direction_flag_backward=0;
	}
}


//MOTOR E KONTROL SWITCH CASE
void fullStepRotate_e(int step){

		switch(step){

			case 0:
				HAL_GPIO_WritePin(step_e_GPIO_Port,step_e_Pin, GPIO_PIN_SET);


			break;
		  case 1:
				HAL_GPIO_WritePin(step_e_GPIO_Port,step_e_Pin, GPIO_PIN_RESET);

			break;
		}

	}
//MOTOR D KONTROL SWITCH CASE

void fullStepRotate_d(int step){

		switch(step){

			case 0:
				HAL_GPIO_WritePin(GPIOA, step_d_Pin, GPIO_PIN_SET);


			break;
		  case 1:
				HAL_GPIO_WritePin(GPIOA, step_d_Pin, GPIO_PIN_RESET);

			break;
		}

	}
//MOTOR C KONTROL SWITCH CASE

void fullStepRotate_c(int step){

		switch(step){

			case 0:
				HAL_GPIO_WritePin(GPIOA, step_c_Pin, GPIO_PIN_SET);

			break;
		  case 1:
				HAL_GPIO_WritePin(GPIOA, step_c_Pin, GPIO_PIN_RESET);

			break;
		}

	}
void setStepper_e(int angle,int direction,int speed){
	float perAngle=1.8;//  360/200=1.8(per step angle)
	stepNumber_e=(int)(angle/perAngle);

	for(int seq=0; seq<=stepNumber_e; seq++){

		if(current_angel_e>18300){
			if(direction==1){// saat yonunun tersi
				HAL_GPIO_WritePin(dir_e_GPIO_Port, dir_e_Pin, GPIO_PIN_SET);

				for(int step=0; step<2; step++){
					fullStepRotate_e(step);
					e_direction_flag_backward=1;
					e_direction_flag_forward=0;
					delay_us(5000);
				}
				current_angel_e-=1.8;

		}
			break;
		}

		if(current_angel_e<18300){

			if(direction==0){
				HAL_GPIO_WritePin(dir_e_GPIO_Port, dir_e_Pin, GPIO_PIN_RESET);

				for(int step=0; step<2; step++){//saat yonunde
					fullStepRotate_e(step);
					e_direction_flag_forward=1;
					e_direction_flag_backward=0;

					delay_us(5000);
				}
				current_angel_e+=1.8;

			}else if(direction==1){// saat yonunun tersi
				HAL_GPIO_WritePin(dir_e_GPIO_Port, dir_e_Pin, GPIO_PIN_SET);

				for(int step=0; step<2; step++){
					fullStepRotate_e(step);
					e_direction_flag_backward=1;
					e_direction_flag_forward=0;
					delay_us(5000);
				}
				current_angel_e+=1.8;


			}

		}
		else{
			HAL_UART_Transmit(&huart2, (uint8_t*)limit_message_y,strlen(limit_message_y),100);

			if(direction==1){
				HAL_GPIO_WritePin(dir_e_GPIO_Port, dir_e_Pin, GPIO_PIN_SET);

				for(int step=0; step<2; step++){
					fullStepRotate_e(step);
					delay_us(5000);
					e_direction_flag_backward=1;
					e_direction_flag_forward=0;
			}
				current_angel_e-=1.8;

		}
	}

}
	if(e_direction_flag_forward==1&&e_direction_flag_backward==0){
		//current_angel_x+=angle;
		e_direction_flag_forward=0;
		e_direction_flag_backward=0;
	}
	else if (e_direction_flag_forward==0&&e_direction_flag_backward==1){
		//current_angel_x-=angle;
		e_direction_flag_forward=0;
		e_direction_flag_backward=0;
	}
}
//MOTOR D
void setStepper_d(int angle,int direction,int speed){
	float perAngle=1.8;//  360/200=1.8(per step angle)
	stepNumber_d=(int)(angle/perAngle);

	for(int seq=0; seq<=stepNumber_d; seq++){

		if(current_angel_d>5000){

			if(direction==1){// saat yonunun tersi
				HAL_GPIO_WritePin(GPIOA, dir_d_Pin, GPIO_PIN_SET);

				for(int step=0; step<2; step++){
					if(HAL_GPIO_ReadPin(d_limit_GPIO_Port,d_limit_Pin)){
						current_angel_d=0;
						break;


					}
					fullStepRotate_d(step);
					d_direction_flag_backward=1;
					d_direction_flag_forward=0;
					delay_us(600);
				}
				current_angel_d-=1.8;



		}
			break;
		}

		if(current_angel_d<5000){



			if(direction==0){
				HAL_GPIO_WritePin(GPIOA, dir_d_Pin, GPIO_PIN_RESET);

				for(int step=0; step<2; step++){//saat yonunde

					fullStepRotate_d(step);
					d_direction_flag_forward=1;
					d_direction_flag_backward=0;

					delay_us(600);
				}
				current_angel_d+=1.8;



				  char message[10];
				  sprintf(message, "Deger -D-: %d\r\n", (int)current_angel_d);
				  HAL_UART_Transmit(&huart2, (uint8_t*)message, strlen(message), 10);


			}else if(direction==1){// saat yonunun tersi
				HAL_GPIO_WritePin(GPIOA, dir_d_Pin, GPIO_PIN_SET);


				for(int step=0; step<2; step++){
					if(HAL_GPIO_ReadPin(GPIOB,d_limit_Pin)){
						current_angel_d=0;
						break;


					}
					fullStepRotate_d(step);
					d_direction_flag_backward=1;
					d_direction_flag_forward=0;
					delay_us(600);
				}
				current_angel_d-=1.8;

				  char message[10];
				  sprintf(message, "deger -D-: %d\r\n", (int)current_angel_d);
				  HAL_UART_Transmit(&huart2, (uint8_t*)message, strlen(message), 10);
			}

		}
		else{
			HAL_UART_Transmit(&huart1, (uint8_t*)limit_message_y,strlen(limit_message_y),100);

			if(direction==1){
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
				if(HAL_GPIO_ReadPin(d_limit_GPIO_Port,d_limit_Pin)){
					current_angel_d=0;
					break;


				}

				for(int step=0; step<2; step++){
					fullStepRotate_d(step);
					delay_us(600);
					d_direction_flag_backward=1;
					d_direction_flag_forward=0;
			}
				current_angel_d-=1.8;

		}
	}

}
	if(d_direction_flag_forward==1&&d_direction_flag_backward==0){
		//current_angel_x+=angle;
		d_direction_flag_forward=0;
		d_direction_flag_backward=0;
	}
	else if (d_direction_flag_forward==0&&d_direction_flag_backward==1){
		//current_angel_x-=angle;
		d_direction_flag_forward=0;
		d_direction_flag_backward=0;
	}
}
//MOTOR C KONTROL
void setStepper_c(int angle,int direction,int speed){
	float perAngle=1.8;//  360/200=1.8(per step angle)
	stepNumber_c=(int)(angle/perAngle);

	for(int seq=0; seq<=stepNumber_c; seq++){

		if(current_angel_c>5000){

			if(direction==1){// saat yonunun tersi

				HAL_GPIO_WritePin(GPIOA, dir_c_Pin, GPIO_PIN_SET);

				for(int step=0; step<2; step++){

					fullStepRotate_c(step);
					c_direction_flag_backward=1;
					c_direction_flag_forward=0;
					delay_us(600);
				}
				current_angel_c-=1.8;



		}
			break;
		}

		if(current_angel_c<5000){



			if(direction==0){
				HAL_GPIO_WritePin(GPIOA, dir_c_Pin, GPIO_PIN_RESET);
				if(HAL_GPIO_ReadPin(c_limit_GPIO_Port,c_limit_Pin)){
					current_angel_c=0;
					break;
				}

				for(int step=0; step<2; step++){//saat yonunde
					fullStepRotate_c(step);
					c_direction_flag_forward=1;
					c_direction_flag_backward=0;

					delay_us(600);
				}
				current_angel_c+=1.8;


			}else if(direction==1){// saat yonunun tersi
				HAL_GPIO_WritePin(GPIOA, dir_c_Pin, GPIO_PIN_SET);


				for(int step=0; step<2; step++){
					fullStepRotate_c(step);
					c_direction_flag_backward=1;
					c_direction_flag_forward=0;
					delay_us(600);
				}
				current_angel_c-=1.8;

				step_num_check_c--;

		}
		else{
			HAL_UART_Transmit(&huart1, (uint8_t*)limit_message_y,strlen(limit_message_y),100);

			if(direction==1){
				HAL_GPIO_WritePin(GPIOA, dir_c_Pin, GPIO_PIN_SET);


				for(int step=0; step<2; step++){
					fullStepRotate_c(step);
					delay_us(600);
					c_direction_flag_backward=1;
					c_direction_flag_forward=0;
			}
				current_angel_c-=1.8;

		}
	}

}
	if(c_direction_flag_forward==1&&c_direction_flag_backward==0){
		//current_angel_x+=angle;
		c_direction_flag_forward=0;
		c_direction_flag_backward=0;
	}
	else if (c_direction_flag_forward==0&&c_direction_flag_backward==1){
		//current_angel_x-=angle;
		c_direction_flag_forward=0;
		c_direction_flag_backward=0;
	}
}}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart==&huart2){
		rx_buffer[interup_counter]=rx_tem_buffer[0];
		interup_counter++;
	}
		HAL_UART_Receive_IT(&huart2, rx_tem_buffer, 1);
		if(rx_buffer[interup_counter-4]=='F'&&rx_buffer[interup_counter-3]=='F'&&rx_buffer[interup_counter-2]=='F'&&rx_buffer[interup_counter-1]=='F')
		{
			for_counter_1=0;
											for (int i=4;i<interup_counter;i++){
												for_counter_1++;
												if(rx_buffer[i]=='F'){
													break;
												}


											}
											for_counter_1=for_counter_1-1;

											for(int i=0; i<for_counter_1; i++){
											rx_for_set[set_for_i_yeni_3]=rx_buffer[i+4];
											rx_for_set_int[i]=0;
											rx_for_set_int[i]=atoi((char*)&rx_for_set[set_for_i_yeni_3]);

											set_for_i_yeni_3++;
											}

												if(for_counter_1==1){
												rx_for_set_integer=0;
												rx_for_set_integer=rx_for_set_integer+rx_for_set_int[0];
												}
												else if (for_counter_1==2){
												rx_for_set_integer=0;
												rx_for_set_integer=rx_for_set_integer+rx_for_set_int[0]*10;
												rx_for_set_integer=rx_for_set_integer+rx_for_set_int[1];
												}
												else if (for_counter_1==3){
												rx_for_set_integer=0;
												rx_for_set_integer=rx_for_set_integer+(rx_for_set_int[0]*100);
												rx_for_set_integer=rx_for_set_integer+(rx_for_set_int[1]*10);
												rx_for_set_integer=rx_for_set_integer+rx_for_set_int[2];
												}
												else if (for_counter_1==4){
												rx_for_set_integer=0;
												rx_for_set_integer=rx_for_set_integer+(rx_for_set_int[0]*1000);
												rx_for_set_integer=rx_for_set_integer+(rx_for_set_int[1]*100);
												rx_for_set_integer=rx_for_set_integer+(rx_for_set_int[2]*10);

												rx_for_set_integer=rx_for_set_integer+rx_for_set_int[3];

												}
												else if (for_counter_1==5){
												rx_for_set_integer=0;
												rx_for_set_integer=rx_for_set_integer+(rx_for_set_int[0]*10000);
												rx_for_set_integer=rx_for_set_integer+(rx_for_set_int[1]*1000);
												rx_for_set_integer=rx_for_set_integer+(rx_for_set_int[2]*100);
												rx_for_set_integer=rx_for_set_integer+(rx_for_set_int[3]*10);


												rx_for_set_integer=rx_for_set_integer+rx_for_set_int[3];

												}
												else if (for_counter_1==6){
												rx_for_set_integer=0;
												rx_for_set_integer=rx_for_set_integer+(rx_for_set_int[0]*100000);
												rx_for_set_integer=rx_for_set_integer+(rx_for_set_int[1]*10000);
												rx_for_set_integer=rx_for_set_integer+(rx_for_set_int[2]*100);
												rx_for_set_integer=rx_for_set_integer+(rx_for_set_int[3]*10);


												rx_for_set_integer=rx_for_set_integer+rx_for_set_int[4];

												}
			if(rx_buffer[0]=='8'&&rx_buffer[1]=='0'&&rx_buffer[2]=='E'&&rx_buffer[3]=='5')
			{




				for(int i=0;i<2;i++){
					rx_step_x_int[i]=atoi((char*)&rx_buffer[i+4]);

				}
				rx_step_x_angel=rx_step_x_int[0];
				setStepper_x(rx_for_set_integer,0,0);
			}
			else if(rx_buffer[0]=='8'&&rx_buffer[1]=='0'&&rx_buffer[2]=='E'&&rx_buffer[3]=='4')
						{
							for(int i=0;i<2;i++){
								rx_step_x_int[i]=atoi((char*)&rx_buffer[i+4]);

							}
							rx_step_x_angel=rx_step_x_int[0];
							setStepper_x(rx_for_set_integer,1,0);

						}
			else if(rx_buffer[0]=='8'&&rx_buffer[1]=='0'&&rx_buffer[2]=='D'&&rx_buffer[3]=='5')
						{
							for(int i=0;i<2;i++){
								rx_step_d_int[i]=atoi((char*)&rx_buffer[i+4]);

							}
							rx_step_d_angel=rx_step_d_int[0];
							setStepper_d(rx_for_set_integer,0,0);

						}
			else if(rx_buffer[0]=='8'&&rx_buffer[1]=='0'&&rx_buffer[2]=='D'&&rx_buffer[3]=='4')
						{
							for(int i=0;i<2;i++){
								rx_step_d_int[i]=atoi((char*)&rx_buffer[i+4]);

							}
							rx_step_d_angel=rx_step_d_int[0];
							setStepper_d(rx_for_set_integer,1,0);

						}
			else if(rx_buffer[0]=='8'&&rx_buffer[1]=='0'&&rx_buffer[2]=='C'&&rx_buffer[3]=='5')
						{
							for(int i=0;i<2;i++){
								rx_step_c_int[i]=atoi((char*)&rx_buffer[i+4]);

							}
							rx_step_c_angel=rx_step_c_int[0];
							setStepper_c(rx_for_set_integer,0,0);

						}
			else if(rx_buffer[0]=='8'&&rx_buffer[1]=='0'&&rx_buffer[2]=='C'&&rx_buffer[3]=='4')
						{
							for(int i=0;i<2;i++){
								rx_step_c_int[i]=atoi((char*)&rx_buffer[i+4]);

							}
							rx_step_c_angel=rx_step_c_int[0];
							setStepper_c(rx_for_set_integer,1,0);

						}
			else if(rx_buffer[0]=='8'&&rx_buffer[1]=='0'&&rx_buffer[2]=='X'&&rx_buffer[3]=='5')
						{
							for(int i=0;i<2;i++){
								rx_step_e_int[i]=atoi((char*)&rx_buffer[i+4]);

							}
							rx_step_e_angel=rx_step_e_int[0];
							setStepper_e(rx_for_set_integer,0,0);

						}
			else if(rx_buffer[0]=='8'&&rx_buffer[1]=='0'&&rx_buffer[2]=='X'&&rx_buffer[3]=='4')
						{
							for(int i=0;i<2;i++){
								rx_step_e_int[i]=atoi((char*)&rx_buffer[i+4]);

							}
							rx_step_e_angel=rx_step_e_int[0];
							setStepper_e(rx_for_set_integer,1,0);

						}
			else if(rx_buffer[0]=='8'&&rx_buffer[1]=='0'&&rx_buffer[2]=='S'&&rx_buffer[3]=='4')
						{

							move_function();

						}
			for(int z=0;z<10;z++){
				rx_buffer[z]=' ';
			}
			interup_counter=0;
		}

	}
void servo_control(int angle){
	if(angle<0){
		angle=0;
	}
	if(angle>180){
		angle=180;
		angle+=angle+45;
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
  MX_USART1_UART_Init();
  MX_TIM1_Init();
  MX_USART2_UART_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start(&htim1);
  HAL_UART_Receive_IT(&huart2, rx_tem_buffer, 1);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
  // MOTOR E HOME

  for(int i=0;i<5000;i++){
	  HAL_GPIO_WritePin(GPIOC,dir_e_Pin,GPIO_PIN_RESET);
	  if(HAL_GPIO_ReadPin(e_limit_GPIO_Port,e_limit_Pin)){
		  current_angel_e=0;
		  for (int i=0;i<50;i++){
			  HAL_GPIO_WritePin(GPIOC,dir_e_Pin,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOC,step_e_Pin, GPIO_PIN_SET);
			  delay_us(3000);
			  HAL_GPIO_WritePin(GPIOC,step_e_Pin, GPIO_PIN_RESET);
			  delay_us(3000);


		  }
		  break;

		  }


	  HAL_GPIO_WritePin(GPIOC,step_e_Pin, GPIO_PIN_SET);
	  delay_us(3000);
	  HAL_GPIO_WritePin(GPIOC,step_e_Pin, GPIO_PIN_RESET);
	  delay_us(3000);
  }
  //motor 1home function
  for(int i=0;i<5000;i++){
	  HAL_GPIO_WritePin(GPIOA,dir_x_Pin,GPIO_PIN_SET);
	  if(HAL_GPIO_ReadPin(x_limit_GPIO_Port,x_limit_Pin)){
		  current_angel_x=0;
		  for (int i=0;i<50;i++){
			  HAL_GPIO_WritePin(GPIOA,dir_x_Pin,GPIO_PIN_RESET);
			  HAL_GPIO_WritePin(GPIOA,step_x_Pin, GPIO_PIN_SET);
			  delay_us(3000);
			  HAL_GPIO_WritePin(GPIOA,step_x_Pin, GPIO_PIN_RESET);
			  delay_us(3000);


		  }
		  break;

	  }
	  HAL_GPIO_WritePin(GPIOA,step_x_Pin, GPIO_PIN_SET);
	  delay_us(3000);
	  HAL_GPIO_WritePin(GPIOA,step_x_Pin, GPIO_PIN_RESET);
	  delay_us(3000);
	}
	 //MOTOR_D HOME
  for(int i=0;i<5000;i++){
	  HAL_GPIO_WritePin(GPIOA,dir_d_Pin,GPIO_PIN_SET);
	  if(HAL_GPIO_ReadPin(d_limit_GPIO_Port,d_limit_Pin)){
		  current_angel_d=0;

			  while(HAL_GPIO_ReadPin(d_limit_GPIO_Port,d_limit_Pin)){
				  HAL_GPIO_WritePin(GPIOA,step_d_Pin, GPIO_PIN_SET);
				  delay_us(600);
				  HAL_GPIO_WritePin(GPIOA,step_d_Pin, GPIO_PIN_RESET);
				  delay_us(600);


			  HAL_GPIO_WritePin(GPIOA,dir_d_Pin,GPIO_PIN_RESET);


		  }
		  break;

		  }


	  HAL_GPIO_WritePin(GPIOA,step_d_Pin, GPIO_PIN_SET);
	  delay_us(800);
	  HAL_GPIO_WritePin(GPIOA,step_d_Pin, GPIO_PIN_RESET);
	  delay_us(800);
  }

  //MOTOR C HOME
  for(int i=0;i<5000;i++){
	  HAL_GPIO_WritePin(GPIOA,dir_c_Pin,GPIO_PIN_RESET);
	  if(HAL_GPIO_ReadPin(c_limit_GPIO_Port,c_limit_Pin)){
		  current_angel_c=0;
		  for (int i=0;i<10;i++){
			  HAL_GPIO_WritePin(GPIOA,dir_c_Pin,GPIO_PIN_SET);
			  HAL_GPIO_WritePin(GPIOA,step_c_Pin, GPIO_PIN_SET);
			  delay_us(600);
			  HAL_GPIO_WritePin(GPIOA,step_c_Pin, GPIO_PIN_RESET);
			  delay_us(600);


		  }
		  break;

		  }


	  HAL_GPIO_WritePin(GPIOA,step_c_Pin, GPIO_PIN_SET);
	  delay_us(600);
	  HAL_GPIO_WritePin(GPIOA,step_c_Pin, GPIO_PIN_RESET);
	  delay_us(600);
  }



  //move_function();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5);
	  switch_konum_x=HAL_GPIO_ReadPin(x_limit_GPIO_Port, x_limit_Pin);
	  switch_konum_d=HAL_GPIO_ReadPin(d_limit_GPIO_Port, d_limit_Pin);
	  switch_konum_c=HAL_GPIO_ReadPin(c_limit_GPIO_Port,c_limit_Pin);
	  switch_konum_e=HAL_GPIO_ReadPin(e_limit_GPIO_Port, e_limit_Pin);





	  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12,GPIO_PIN_SET);





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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 72-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 0xffff-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_OC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_OC_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 0;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 65535;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_OC_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_OC_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */
  HAL_TIM_MspPostInit(&htim4);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, step_x_Pin|dir_x_Pin|step_d_Pin|dir_d_Pin
                          |dir_c_Pin|step_c_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, step_e_Pin|dir_e_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|led_Pin|GPIO_PIN_14, GPIO_PIN_RESET);

  /*Configure GPIO pins : PE5 e_limit_Pin */
  GPIO_InitStruct.Pin = GPIO_PIN_5|e_limit_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : step_x_Pin dir_x_Pin step_d_Pin dir_d_Pin
                           dir_c_Pin step_c_Pin */
  GPIO_InitStruct.Pin = step_x_Pin|dir_x_Pin|step_d_Pin|dir_d_Pin
                          |dir_c_Pin|step_c_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : step_e_Pin dir_e_Pin */
  GPIO_InitStruct.Pin = step_e_Pin|dir_e_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : x_limit_Pin d_limit_Pin c_limit_Pin */
  GPIO_InitStruct.Pin = x_limit_Pin|d_limit_Pin|c_limit_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 led_Pin PD14 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|led_Pin|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

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
