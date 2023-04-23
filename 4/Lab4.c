#include "stm32l4xx.h"
#include "stm32l496xx.h"

#define TIME 300
#define DELAY 10
//to z wykladu struct
typedef struct
{
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

void SysClock_Init(void){
    RCC->CR |= RCC_CR_MSION;//wlaczenie zegara msi
    RCC->CFGR &= ~RCC_CFGR_SW;//SW rejestr 00 ustawiamy czyli MSI strona 228-229 ogolnie sluzy do wskazanie co jest zegarem
    while ((RCC->CR & RCC_CR_MSIRDY) == 0);//czekamy az zegar bd gotowy
    RCC->APB1ENR1 |= RCC_APB1ENR1_PWREN;//to na podstawie HALA
    PWR->CR1 |= PWR_CR1_VOS_0; //na podstawie HALA ogólnie bez tego nie odpala ekran

    RCC->CR &= ~RCC_CR_MSIRANGE; //czyscimy range
    RCC->CR |= RCC_CR_MSIRANGE_6; // ustawiamy na 4MHz strona 225 z innymi dostepnymi
    RCC->CR |= RCC_CR_MSIRGSEL; //ustawiamy na 1 bo CR 225strona
    while ((RCC->CR & RCC_CR_MSIRDY) == 0); //czekamy az zegar bd gotowy
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
		mGPIOG->ODR = (1<<0 | 1<<1 | 1<<2 | 1<<3 | 1<<4 | 1<<5);
	}
	else if(number==1)
	{
		mGPIOG->ODR = (1<<1 | 1<<2);
	}
	else if(number==2)
	{
		mGPIOG->ODR = (1<<0 | 1<<1 | 1<<3 | 1<<4 | 1<<6);
	}
	else if(number==3)
	{
		mGPIOG->ODR = (1<<0 | 1<<1 | 1<<2 | 1<<3 | 1<<6);
	}
	else if(number==4)
	{
		mGPIOG->ODR = (1<<1 | 1<<2 | 1<<5 | 1<<6);
	}
	else if(number==5)
	{
		mGPIOG->ODR = (1<<0 | 1<<2 | 1<<3 | 1<<5 | 1<<6);
	}
	else if(number==6)
	{
		mGPIOG->ODR = (1<<0 | 1<<2 | 1<<3 | 1<<4 | 1<<5 | 1<<6);
	}
	else if(number==7)
	{
		mGPIOG->ODR = (1<<0 | 1<<1 | 1<<2);
	}
	else if(number==8)
	{
		mGPIOG->ODR = (1<<0 | 1<<1 | 1<<2 | 1<<3 | 1<<4 | 1<<5 | 1<<6);
	}
	else if(number==9)
	{
		mGPIOG->ODR = (1<<0 | 1<<1 | 1<<2 | 1<<3 | 1<<5 | 1<<6);
	}
}

int main(void)
{
	SysClock_Init();
	//Poczatek ustawiania LED0-LED7
	RCC->AHB2ENR |= (1<<2);//wlaczamy zegar dla GPIOC 2gi bit odpowiada akurat temu 251strona pdf
	//pin nr 6 w gpioc to dioda nr0 potrzebujemy output czyli 01 MODER strona 303
	mGPIOC->MODER |= (1<<12);
	mGPIOC->MODER &= ~(1<<13);

	RCC->AHB2ENR |= (1<<3);
	mGPIOD->MODER |= (1<<6);
	mGPIOD->MODER &= ~(1<<7);

	RCC->AHB2ENR |= (1<<4);
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
	RCC->AHB2ENR |= (1<<1); //wlaczamy dla GPIOB
	SET_BIT(PWR->CR2, PWR_CR2_IOSV); // to na podstawie HALA wraz z 2 linijkami w initClock "uruchamia nam ekran"
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
	RCC->AHB2ENR |= (1<<6); //wlaczamy dla GPIOG
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

	uint16_t i = 0;
	uint16_t first=0;
	uint16_t second=0;
	uint16_t third=0;
	uint16_t fourth=0;
	while(1)
	{
		for(int j=0;j<=DELAY;j++)
		{
			dispDigitOff();
			if(i<=10)
			{
				first = i%10;
				for(uint16_t j=0;j<TIME;j++)
				{
					dispDigit(1);
					myDisplay(first);
				}
			}
			else if(i<=100)
			{
				first = i%10;
				second = i%100/10;
				for(uint16_t j=0;j<TIME/2;j++)
				{
					dispDigit(1);
					myDisplay(first);
				}
				dispDigitOff();
				for(uint16_t j=0;j<TIME/2;j++)
				{
					dispDigit(2);
					myDisplay(second);
				}
			}
			else if(i<=1000)
			{
				first = i%10;
				second = i%100/10;
				third = i%1000/100;
				for(uint16_t j=0;j<TIME/3;j++)
				{
					dispDigit(1);
					myDisplay(first);
				}
				dispDigitOff();
				for(uint16_t j=0;j<TIME/3;j++)
				{
					dispDigit(2);
					myDisplay(second);
				}
				dispDigitOff();
				for(uint16_t j=0;j<TIME/3;j++)
				{
					dispDigit(3);
					myDisplay(third);
				}
			}
			else if(i<=10000)
			{
				first = i%10;
				second = i%100/10;
				third = i%1000/100;
				fourth = i%10000/1000;
				for(uint16_t j=0;j<TIME/4;j++)
				{
					dispDigit(1);
					myDisplay(first);
				}
				dispDigitOff();
				for(uint16_t j=0;j<TIME/4;j++)
				{
					dispDigit(3);
					myDisplay(third);
				}
				dispDigitOff();
				for(uint16_t j=0;j<TIME/4;j++)
				{
					dispDigit(2);
					myDisplay(second);
				}
				dispDigitOff();
				for(uint16_t j=0;j<TIME/4;j++)
				{
					dispDigit(4);
					myDisplay(fourth);
				}
			}
		}
		i++;
		if(i>=10000)
		{
			i=0;
		}
		;
	}
}
