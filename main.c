#include "stm32f4xx.h"
#include "delay.h"
#include "usart.h"
#include "adc.h"
#include <stdlib.h>



//Cooler
void CoolerON(void);
void CoolerOFF(void);


int main(void)
{
        uint16_t temp;
	uint16_t max_temp = 30;

	initADC1Temp();

	initUSART2(USART2_BAUDRATE_115200);
	

	//ENABLE D PORT, PINs 12, 13, 14 and 15 for internal LED use
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; 								
	GPIOD->MODER |= 0x55000000;  								
	GPIOD->OSPEEDR |= 0x55000000 ;
	GPIOD->ODR &= ~(0x55000000);

	//ENABLE C PORT, PINs 12, 13, 14 and 15 for external LED use
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
        GPIOC->MODER |= 0x55000000;
        GPIOC->OSPEEDR |= 0x55000000 ;
	GPIOC->ODR &= ~(0x55000000);


	
	while(1)
	{
		
		temp = getADC1Temp();	
		delay_ms(3000);

		
		if (temp < max_temp)
			{	printUSART2("Temperatura MCU je : %d C \n", temp);
				printUSART2("Temperatura MCU je manja od maksimalne dozvoljene temperature, Cooler je isključen. \n \n \n \n \n \n \n");
				CoolerON();
			}
			
			else
			{
				printUSART2("Temperatura MCU je : %d C \n", temp);  //Printanje očitane vrijednosti temperature na ekranu
				printUSART2("Temperatura MCU je veća od maksimalne dozvoljene temperature, uključujemo Cooler. \n \n \n \n \n \n \n");
				CoolerOFF();
			}

	}	
}





void CoolerON(void)
{
	GPIOD->ODR &= 0x0FFF; //reset D port
	GPIOC->ODR &= 0x0FFF; //reset C port

        GPIOD->ODR ^= (0<<14); //iskljuci zelenu na pločici
	GPIOD->ODR ^= (1<<12); //ukljuci crvenu na plocici

	GPIOC->ODR ^= (0<<15); //iskljuci crvenu eksternu
	GPIOC->ODR ^= (1<<14); //ukljuci zelenu eksternu
}



void CoolerOFF(void)
{
	GPIOD->ODR &= 0x0FFF; //reset D port
        GPIOC->ODR &= 0x0FFF; //reset C port

        GPIOD->ODR ^= (0<<12); //iskljuci crvenu na pločici
        GPIOD->ODR ^= (1<<14); //ukljuci zelenu na plocici

        GPIOC->ODR ^= (0<<14); //iskljuci zelenu eksternu
        GPIOC->ODR ^= (1<<15); //ukljuci crvenu eksternu


}
