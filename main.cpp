#include <stdio.h>
#include "STM32F7xx.h"

int hola[4] = {272,2,354,16};
int i=0;
int tiempo=1000;
int a=0;
int puls=1;

int main(void){
	
		RCC->AHB1ENR=0xE;
		RCC->APB2ENR |= (1UL<<14);
	
		GPIOB->MODER=0x11554;
		GPIOB->OTYPER=0;
		GPIOB->OSPEEDR=0x11554;
		GPIOB->PUPDR=0;
	
		GPIOD->MODER=0x5500;
		GPIOD->OTYPER=0;
		GPIOD->OSPEEDR=0X5500;
		GPIOD->PUPDR=0;
		
		GPIOC->MODER = 0x0; 
		GPIOC->OTYPER =0; 
		GPIOC->OSPEEDR =0x01;
		GPIOC->PUPDR=0x01;
	
		SystemCoreClockUpdate();
		SysTick_Config(SystemCoreClock/2);
	
		SYSCFG -> EXTICR[0]=0x2;// Bits 0, Puerto C.
		EXTI -> IMR |= (1UL<<0);//DESENMASCARA EL PIN D0
		EXTI -> RTSR |= (1UL<<0);//rising edge
		NVIC_EnableIRQ(EXTI0_IRQn);
			
		while(true){
			GPIOB->ODR=hola[a];
			GPIOD->ODR=(16<<i); //Habilitador se activa con uno
			i++;
			for(int c=0; c<tiempo; c++);
			a++;			
			if(a==4){a=0;}
			if(i==4){i=0;}
		}
}
extern "C" {
	void EXTI0_IRQHandler (void){
		for(int c=0; c<6000; c++);
		EXTI->PR|=(1UL<<0);
		puls++;
	}
	void SysTick_Handler (void){	
		while(i<3 && (puls%2==0)){
		i++;}
	}
}