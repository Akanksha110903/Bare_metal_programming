#include <stdint.h>
//LED blinking from scrach, from register address without using any libraries

#define PERIPH_BASE          (0x40000000UL)
#define AHB1_PERIPH_OFFSET   (0x00020000UL)
#define AHB1_PERIPH_BASE     (PERIPH_BASE + AHB1_PERIPH_OFFSET)

#define GPIOA_OFFSET         (0x0000U)  //Ox0000 0000
#define GPIOA_BASE           (AHB1_PERIPH_BASE + GPIOA_OFFSET)

#define GPIOB_OFFSET         (0x00000400UL)
#define GPIOB_BASE           (AHB1_PERIPH_BASE + GPIOB_OFFSET)

#define GPIOC_OFFSET         (0x00000800UL)
#define GPIOC_BASE           (AHB1_PERIPH_BASE + GPIOC_OFFSET)

#define GPIOD_OFFSET         (0x00000C00UL)
#define GPIOD_BASE           (AHB1_PERIPH_BASE + GPIOD_OFFSET)

#define RCC_OFFSET           (0x00003800UL)
#define RCC_BASE             (AHB1_PERIPH_BASE +  RCC_OFFSET)

#define  GPIODEN             (1U<<3) //enable clock for PORTD (0b 0000 0000 0000 0000 0000 0000 0000 1000)

#define PIN12                (1U<<12)
#define PIN13                (1U<<13)
#define PIN14                (1U<<14)
#define PIN15                (1U<<15)

#define LED_RED              PIN14
#define LED_GREEN            PIN12
#define LED_BLUE             PIN15
#define LED_ORANGE           PIN13

#define _IO volatile // misra standards
//typedef struct
//{
//	_IO uint32_t MODER;    //mode register                                 offset: 0x00
//	_IO uint32_t OTYPER;   //output type register                          offset: 0x04
//	_IO uint32_t OSPEEDR;  //output speed regiseter                        offset: 0x08
//	_IO uint32_t PUPDR;    //pull up/down register                         offset: 0x0c
//	_IO uint32_t IDR;      //input data register                           offset: 0x10
//	_IO uint32_t ODR;      //output data register                          offset: 0x14
//	_IO uint32_t BSRR;     //bit set reset register                        offset: 0x18
//	_IO uint32_t LCKR;     //port configuration lock register              offset: 0x1C
//	_IO uint32_t AFR[2];   //alternate function register                   offset: 0x20 - 0x24
//}GPIO_TypeDef;

/* for now we only need moderegister and output data register but in structure register offset should be maintain
so between moder and odr we keep dummy data array so that register offset address should be maintained  */
typedef struct
{
	volatile  uint32_t MODER;    //mode register                                 offset: 0x00
    volatile uint32_t DUMMY[4];
	volatile  uint32_t ODR;      //output data register                          offset: 0x14

}GPIO_TypeDef;

//same with RCC , we are only using register which we need right now so we make other register as dummy array to maintain offset address
typedef struct
{
	volatile uint32_t DuMMY[12];
	volatile uint32_t AHB1ENR;
}RCC_Typedef;


#define RCC     ((RCC_Typedef *)RCC_BASE)
#define GPIOD   ((GPIO_TypeDef *)GPIOD_BASE)


int main(void)
{
	//enable clock access to GPIOD
	//RCC_AHB1EN_R |= GPIODEN ;
	RCC->AHB1ENR |= GPIODEN;

	//clean all the bits
	//GPIOD_MODER_R &= ~((3U<<(2*12)) | (3U<<(2*13)) | (3U<<(2*14)) | (3U<<(2*15)));
	GPIOD->MODER &= ~((3U<<(2*12)) | (3U<<(2*13)) | (3U<<(2*14)) | (3U<<(2*15)));

	//set pins as output
	//GPIOD_MODER_R |= ((1U<<(2*12)) | (1U<<(2*13)) | (1U<<(2*14)) |(1U<<(2*15)));
	GPIOD->MODER |= ((1U<<(2*12)) | (1U<<(2*13)) | (1U<<(2*14)) |(1U<<(2*15)));

	while(1)
	{
		//turn on the led
		//GPIOD_ODR_R  |= (LED_RED | LED_GREEN | LED_BLUE | LED_ORANGE);

		//TOGGLE LEDS
		//GPIOD_ODR_R  ^= (LED_RED | LED_GREEN | LED_BLUE | LED_ORANGE);
		GPIOD->ODR ^= (LED_RED | LED_GREEN | LED_BLUE | LED_ORANGE);
		for(int i=0;i<100000;i++){}

	}
}


