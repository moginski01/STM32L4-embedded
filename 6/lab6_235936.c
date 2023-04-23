#include "stm32l4xx.h"
#include "stm32l496xx.h"
#include <string.h>

//LPUART1,                RSC232
//1.POWER PORT CLOCK
//2.-||- LPUART1
//3.MODER
//4.AFR 16,17(tabela) plik coś tam datasheet
//TDX rejestr do wysyłania danych               0x00000088
//TX RX

typedef struct
{//rozpiska strona 1180
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t reserved1;
	volatile uint32_t DIER; //interrupt enable reg
	volatile uint32_t SR; //status register
	volatile uint32_t EGR;
	volatile uint32_t reserved2[3];
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
}TIMx_Struct, *TIMx_Struct_ptr;

typedef struct
{
	  volatile uint32_t CR;          /*!< RCC clock control register,                                              Address offset: 0x00 */
	  volatile uint32_t ICSCR;       /*!< RCC internal clock sources calibration register,                         Address offset: 0x04 */
	  volatile uint32_t CFGR;        /*!< RCC clock configuration register,                                        Address offset: 0x08 */
	  volatile uint32_t PLLCFGR;     /*!< RCC system PLL configuration register,                                   Address offset: 0x0C */
	  volatile uint32_t PLLSAI1CFGR; /*!< RCC PLL SAI1 configuration register,                                     Address offset: 0x10 */
	  volatile uint32_t PLLSAI2CFGR; /*!< RCC PLL SAI2 configuration register,                                     Address offset: 0x14 */
	  volatile uint32_t CIER;        /*!< RCC clock interrupt enable register,                                     Address offset: 0x18 */
	  volatile uint32_t CIFR;        /*!< RCC clock interrupt flag register,                                       Address offset: 0x1C */
	  volatile uint32_t CICR;        /*!< RCC clock interrupt clear register,                                      Address offset: 0x20 */
	  volatile uint32_t RESERVED0;   /*!< Reserved,                                                                Address offset: 0x24 */
	  volatile uint32_t AHB1RSTR;    /*!< RCC AHB1 peripheral reset register,                                      Address offset: 0x28 */
	  volatile uint32_t AHB2RSTR;    /*!< RCC AHB2 peripheral reset register,                                      Address offset: 0x2C */
	  volatile uint32_t AHB3RSTR;    /*!< RCC AHB3 peripheral reset register,                                      Address offset: 0x30 */
	  volatile uint32_t RESERVED1;   /*!< Reserved,                                                                Address offset: 0x34 */
	  volatile uint32_t APB1RSTR1;   /*!< RCC APB1 peripheral reset register 1,                                    Address offset: 0x38 */
	  volatile uint32_t APB1RSTR2;   /*!< RCC APB1 peripheral reset register 2,                                    Address offset: 0x3C */
	  volatile uint32_t APB2RSTR;    /*!< RCC APB2 peripheral reset register,                                      Address offset: 0x40 */
	  volatile uint32_t RESERVED2;   /*!< Reserved,                                                                Address offset: 0x44 */
	  volatile uint32_t AHB1ENR;     /*!< RCC AHB1 peripheral clocks enable register,                              Address offset: 0x48 */
	  volatile uint32_t AHB2ENR;     /*!< RCC AHB2 peripheral clocks enable register,                              Address offset: 0x4C */
	  volatile uint32_t AHB3ENR;     /*!< RCC AHB3 peripheral clocks enable register,                              Address offset: 0x50 */
	  volatile uint32_t RESERVED3;   /*!< Reserved,                                                                Address offset: 0x54 */
	  volatile uint32_t APB1ENR1;    /*!< RCC APB1 peripheral clocks enable register 1,                            Address offset: 0x58 */
	  volatile uint32_t APB1ENR2;    /*!< RCC APB1 peripheral clocks enable register 2,                            Address offset: 0x5C */
	  volatile uint32_t APB2ENR;     /*!< RCC APB2 peripheral clocks enable register,                              Address offset: 0x60 */
	  volatile uint32_t RESERVED4;   /*!< Reserved,                                                                Address offset: 0x64 */
	  volatile uint32_t AHB1SMENR;   /*!< RCC AHB1 peripheral clocks enable in sleep and stop modes register,      Address offset: 0x68 */
	  volatile uint32_t AHB2SMENR;   /*!< RCC AHB2 peripheral clocks enable in sleep and stop modes register,      Address offset: 0x6C */
	  volatile uint32_t AHB3SMENR;   /*!< RCC AHB3 peripheral clocks enable in sleep and stop modes register,      Address offset: 0x70 */
	  volatile uint32_t RESERVED5;   /*!< Reserved,                                                                Address offset: 0x74 */
	  volatile uint32_t APB1SMENR1;  /*!< RCC APB1 peripheral clocks enable in sleep mode and stop modes register 1, Address offset: 0x78 */
	  volatile uint32_t APB1SMENR2;  /*!< RCC APB1 peripheral clocks enable in sleep mode and stop modes register 2, Address offset: 0x7C */
	  volatile uint32_t APB2SMENR;   /*!< RCC APB2 peripheral clocks enable in sleep mode and stop modes register, Address offset: 0x80 */
	  volatile uint32_t RESERVED6;   /*!< Reserved,                                                                Address offset: 0x84 */
	  volatile uint32_t CCIPR;       /*!< RCC peripherals independent clock configuration register,                Address offset: 0x88 */
	  volatile uint32_t RESERVED7;   /*!< Reserved,                                                                Address offset: 0x8C */
	  volatile uint32_t BDCR;        /*!< RCC backup domain control register,                                      Address offset: 0x90 */
	  volatile uint32_t CSR;         /*!< RCC clock control & status register,                                     Address offset: 0x94 */
	  volatile uint32_t CRRCR;       /*!< RCC clock recovery RC register,                                          Address offset: 0x98 */
	  volatile uint32_t CCIPR2;
}mRCC_Struct,*mRCC_Struct_ptr;


typedef struct
{
  volatile uint32_t CR1;   /*!< PWR power control register 1,        Address offset: 0x00 */
  volatile uint32_t CR2;   /*!< PWR power control register 2,        Address offset: 0x04 */
  volatile uint32_t CR3;   /*!< PWR power control register 3,        Address offset: 0x08 */
  volatile uint32_t CR4;   /*!< PWR power control register 4,        Address offset: 0x0C */
  volatile uint32_t SR1;   /*!< PWR power status register 1,         Address offset: 0x10 */
  volatile uint32_t SR2;   /*!< PWR power status register 2,         Address offset: 0x14 */
  volatile uint32_t SCR;   /*!< PWR power status reset register,     Address offset: 0x18 */
  volatile uint32_t RESERVED;   /*!< Reserved,                            Address offset: 0x1C */
  volatile uint32_t PUCRA; /*!< Pull_up control register of portA,   Address offset: 0x20 */
  volatile uint32_t PDCRA; /*!< Pull_Down control register of portA, Address offset: 0x24 */
  volatile uint32_t PUCRB; /*!< Pull_up control register of portB,   Address offset: 0x28 */
  volatile uint32_t PDCRB; /*!< Pull_Down control register of portB, Address offset: 0x2C */
  volatile uint32_t PUCRC; /*!< Pull_up control register of portC,   Address offset: 0x30 */
  volatile uint32_t PDCRC; /*!< Pull_Down control register of portC, Address offset: 0x34 */
  volatile uint32_t PUCRD; /*!< Pull_up control register of portD,   Address offset: 0x38 */
  volatile uint32_t PDCRD; /*!< Pull_Down control register of portD, Address offset: 0x3C */
  volatile uint32_t PUCRE; /*!< Pull_up control register of portE,   Address offset: 0x40 */
  volatile uint32_t PDCRE; /*!< Pull_Down control register of portE, Address offset: 0x44 */
  volatile uint32_t PUCRF; /*!< Pull_up control register of portF,   Address offset: 0x48 */
  volatile uint32_t PDCRF; /*!< Pull_Down control register of portF, Address offset: 0x4C */
  volatile uint32_t PUCRG; /*!< Pull_up control register of portG,   Address offset: 0x50 */
  volatile uint32_t PDCRG; /*!< Pull_Down control register of portG, Address offset: 0x54 */
  volatile uint32_t PUCRH; /*!< Pull_up control register of portH,   Address offset: 0x58 */
  volatile uint32_t PDCRH; /*!< Pull_Down control register of portH, Address offset: 0x5C */
  volatile uint32_t PUCRI; /*!< Pull_up control register of portI,   Address offset: 0x60 */
  volatile uint32_t PDCRI; /*!< Pull_Down control register of portI, Address offset: 0x64 */
} mPWR_Struct,*mPWR_Struct_ptr;


typedef struct
{//613 linijka hal tak samo rozpisana
    volatile uint32_t MODER;//ustawiamy input lub output
    volatile uint32_t OTYPER;//ustawiamy push-pull lub open-drain ale raczej zawsze push-pull
    volatile uint32_t OSPEEDR;//predkosc
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;//input reg
    volatile uint32_t ODR;//output reg
    volatile uint32_t BSRR;//set reset reg
    volatile uint32_t LCKR;//lock register
    volatile uint32_t AFR[2];//
    volatile uint32_t BRR;//port reset reg
}GPIO_Struct, *GPIO_Struct_ptr;


#define mTIM6 ((TIMx_Struct_ptr) 0x40001000)
#define mRCC ((mRCC_Struct_ptr) 0x40021000)
#define mPWR ((mPWR_Struct_ptr) 0x40007000)
//wszystkie strony są z z dokumentacji
//strona 77 rozpiska adresow
#define mGPIOA ((GPIO_Struct_ptr) 0x48000000)
#define mGPIOB ((GPIO_Struct_ptr) 0x48000400)
#define mGPIOC ((GPIO_Struct_ptr) 0x48000800)
#define mGPIOD ((GPIO_Struct_ptr) 0x48000C00)
#define mGPIOE ((GPIO_Struct_ptr) 0x48001000)
#define mGPIOF ((GPIO_Struct_ptr) 0x48001400)
#define mGPIOG ((GPIO_Struct_ptr) 0x48001800)
#define mGPIOH ((GPIO_Struct_ptr) 0x48001C00)
#define mGPIOI ((GPIO_Struct_ptr) 0x48002000)

void PowerConfig(void){
	mRCC->APB1ENR1 |= (1 << 28);
	mPWR->CR1 |= (1 << 9);
	mPWR->CR2 |= (1 << 9);
}

void dispDigit(uint16_t digit)
{
	if(digit==1)
	{
		mGPIOB->ODR |= (1<<5);
	}
	else if(digit==2)
	{
		mGPIOB->ODR |= (1<<(4));
	}
	else if(digit==3)
	{
		mGPIOB->ODR |= (1<<3);
	}
	else if(digit==4)
	{
		mGPIOB->ODR |= (1<<2);
	}
	else
	{
		mGPIOB->ODR &= ~(1<<5);
		mGPIOB->ODR &= ~(1<<4);
		mGPIOB->ODR &= ~(1<<3);
		mGPIOB->ODR &= ~(1<<2);
	}
}

void dispDigitOff()
{
	mGPIOG->ODR &= ~(1<<0 | 1<<1 | 1<<2 | 1<<3 | 1<<4 | 1<<5 | 1<<6);//wylaczamy segmenty
	//wylaczamy poszczegolne cyfry
	mGPIOB->ODR &= ~(1<<5);
	mGPIOB->ODR &= ~(1<<4);
	mGPIOB->ODR &= ~(1<<3);
	mGPIOB->ODR &= ~(1<<2);
}

//ustawianie segmentow danej cyfry
static void myDisplay(uint16_t number)
{
	if(number==0)
	{
		GPIOG->ODR = (1<<0 | 1<<1 | 1<<2 | 1<<3 | 1<<4 | 1<<5);
	}
	else if(number==1)
	{
		GPIOG->ODR = (1<<1 | 1<<2);
	}
	else if(number==2)
	{
		GPIOG->ODR = (1<<0 | 1<<1 | 1<<3 | 1<<4 | 1<<6);
	}
	else if(number==3)
	{
		GPIOG->ODR = (1<<0 | 1<<1 | 1<<2 | 1<<3 | 1<<6);
	}
	else if(number==4)
	{
		GPIOG->ODR = (1<<1 | 1<<2 | 1<<5 | 1<<6);
	}
	else if(number==5)
	{
		GPIOG->ODR = (1<<0 | 1<<2 | 1<<3 | 1<<5 | 1<<6);
	}
	else if(number==6)
	{
		GPIOG->ODR = (1<<0 | 1<<2 | 1<<3 | 1<<4 | 1<<5 | 1<<6);
	}
	else if(number==7)
	{
		GPIOG->ODR = (1<<0 | 1<<1 | 1<<2);
	}
	else if(number==8)
	{
		GPIOG->ODR = (1<<0 | 1<<1 | 1<<2 | 1<<3 | 1<<4 | 1<<5 | 1<<6);
	}
	else if(number==9)
	{
		GPIOG->ODR = (1<<0 | 1<<1 | 1<<2 | 1<<3 | 1<<5 | 1<<6);
	}
}

void timer_Config(void)
{
    mRCC->APB1ENR1 |= (1<<4);//uruchomienie zegara 253strona
    mTIM6->CR1 |= (1<<0);//uruchomienie timera 1176 strona
    mTIM6->PSC = 3u;//prescaler 1179 strona na "4 aka 3+1" ustawiamy, ponieważ liczymy co 4 takt procesora
    mTIM6->ARR = 999U;//liczymy do 1000
}
//Update Event = TIM clk/((PSC+1) * (ARR+1)) - wzór wartość w hz a 1000hz odpowiada 1ms f=1/T

static void delay(uint32_t miliseconds)
{
    uint32_t i = 0; // ilość milisekund już wykonanych

    while (i < miliseconds)
    {
        if (mTIM6->SR & (1<<0)) // sprawdzenie flagi UIF --1178strona oraz 1171
        {
            mTIM6->SR &= ~(1<<0); // ustawienie flagi UIF na 0
            i++;
        }
    }
}

static void LPUART_Config(void)
{
	mRCC->APB1ENR2 |= 1<<0;//włączenie zegara dla LPUART1 strona 256
	LPUART1->CR1 &= ~(1<<28); //ustawienie ilości bitów przy wysyłaniu
	LPUART1->CR1 &= ~(1<<12); //wyzerowanie bitów po to by mieć 8 bitów na data
	LPUART1->BRR = 256*4000000/57600; //ustawienie baud rate na 57600
	//	LPUART1->CR1 |= 1<<3; //włączamy wysyłanie
	LPUART1->CR1 |= 1<<0;//włączenie LPUART
	LPUART1->CR1 |= 1<<3;//transmitter enable
	LPUART1->CR1 |= 1<<2;//receiver enable
}

static void gpio_Config(void)
{
	mRCC->AHB2ENR |= (1<<2);//wlaczamy zegar dla GPIOC 2gi bit odpowiada akurat temu 251strona pdf
	mGPIOC->MODER &= ~(1<<2); //ustawiamy na 1-0 żeby było na "alternate function mode"
	mGPIOC->MODER |= (1<<3); //2gi i 3ci bit ponieważ pc1 ma być
	//4,5,6,7
//	mGPIOC->AFR[0] = 0x00000088;
	mGPIOC->AFR[0] |= 1<<7;
	mGPIOC->AFR[0] &= ~(1<<6);
	mGPIOC->AFR[0] &= ~(1<<5);
	mGPIOC->AFR[0] &= ~(1<<4);//ustawienie alternatywnej funkcji LPUART1_TX dla PC1
}

int main(void)
{
//	SysClock_Init();
	PowerConfig();
	//Poczatek ustawiania LED0-LED7

	mRCC->AHB2ENR |= (1<<2);//wlaczamy zegar dla GPIOC 2gi bit odpowiada akurat temu 251strona pdf
	mGPIOC->MODER |= (1<<12); //ustawiamy na 10 żeby było na "alternate function mode"
	mGPIOC->MODER &= ~(1<<13);

	mRCC->AHB2ENR |= (1<<3);
	mGPIOD->MODER |= (1<<6);
	mGPIOD->MODER &= ~(1<<7);

	mRCC->AHB2ENR |= (1<<4);
	mGPIOE->MODER |= (1<<8);
	mGPIOE->MODER &= ~(1<<9);

	mGPIOE->MODER |= (1<<10);
	mGPIOE->MODER &= ~(1<<11);

	mGPIOE->MODER |= (1<<12);
	mGPIOE->MODER &= ~(1<<13);

	mGPIOC->MODER |= (1<<14);
	mGPIOC->MODER &= ~(1<<15);

	mGPIOC->MODER |= (1<<16);
	mGPIOC->MODER &= ~(1<<17);

	mGPIOC->MODER |= (1<<18);
	mGPIOC->MODER &= ~(1<<19);

	//Ustawianie dla wyswietlacza
	mRCC->AHB2ENR |= (1<<1); //wlaczamy dla GPIOB
	//cyfra nr 1 od prawej strony
	mGPIOB->MODER |= (1<<10);
	mGPIOB->MODER &= ~(1<<11); //output

	//cyfra 2
	mGPIOB->MODER |= (1<<8);
	mGPIOB->MODER &= ~(1<<9); //output

	//cyfra 3
	mGPIOB->MODER |= (1<<6);
	mGPIOB->MODER &= ~(1<<7); //output

	//cyfra 4
	mGPIOB->MODER |= (1<<4);
	mGPIOB->MODER &= ~(1<<5); //output

	//segmenty
	mRCC->AHB2ENR |= (1<<6); //wlaczamy dla GPIOG
	//0
	mGPIOG->MODER |= (1<<0);
	mGPIOG->MODER &= ~(1<<1); //output

	//1
	mGPIOG->MODER |= (1<<2);
	mGPIOG->MODER &= ~(1<<3); //output

	//2
	mGPIOG->MODER |= (1<<4);
	mGPIOG->MODER &= ~(1<<5); //output

	//3
	mGPIOG->MODER |= (1<<6);
	mGPIOG->MODER &= ~(1<<7); //output

	//4
	mGPIOG->MODER |= (1<<8);
	mGPIOG->MODER &= ~(1<<9); //output

	//5
	mGPIOG->MODER |= (1<<10);
	mGPIOG->MODER &= ~(1<<11); //output

	//6
	mGPIOG->MODER |= (1<<12);
	mGPIOG->MODER &= ~(1<<13); //output

	//disp
	mGPIOG->MODER |= (1<<18);
	mGPIOG->MODER &= ~(1<<19); //output

	timer_Config();
	//KONIEC POPRZEDNIEGO ZADANIA



	gpio_Config();
	LPUART_Config();
	char *str = "Systemy wbudowane\n\r";
	while(1)
	{
		for(uint32_t i=0;i<(uint32_t)strlen(str);)
		{
			//to po to żeby TDR mógl wysłać bo wymaga TXE=1
			if(LPUART1->ISR>>7 & (1<<0))//sprawdzenie flagi TXE czyli 7 bit czy == 1
			{
				LPUART1->TDR = str[i];//rejestr do wysłania danych
				i++;
			}
		}
		delay(1000);
	}
}
