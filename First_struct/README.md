# 🔴 Bare-Metal LED Blinking (STM32F4 – Register Level)

## 📌 Overview
This project demonstrates bare-metal programming on an STM32 microcontroller (STM32F4 series) by directly accessing hardware registers without using any vendor libraries (HAL/LL).

The program configures GPIOD pins (PD12–PD15) as output and toggles onboard LEDs using memory-mapped register access.

## 🎯 Objectives
- Understand memory-mapped I/O
- Work with peripheral base addresses
- Learn bit manipulation for hardware control
- Build firmware without HAL or CMSIS abstraction

## ⚙️ Hardware Used
- STM32F4 Discovery Board
- Onboard LEDs:
  - PD12 → Green
  - PD13 → Orange
  - PD14 → Red
  - PD15 → Blue

## 🧠 Key Concepts

### 1. Memory-Mapped Registers
PERIPH_BASE → 0x40000000  
AHB1_PERIPH_BASE → 0x40020000  
GPIOD_BASE → 0x40020C00  
RCC_BASE → 0x40023800  

### 2. Clock Enable (RCC)
RCC->AHB1ENR |= (1U << 3);

### 3. GPIO Mode Configuration
Each pin uses 2 bits in MODER:
- 00 → Input
- 01 → Output

### 4. LED Toggle
GPIOD->ODR ^= (LED_RED | LED_GREEN | LED_BLUE | LED_ORANGE);

## 🚀 Program Flow
1. Enable clock for GPIOD  
2. Configure pins PD12–PD15 as output  
3. Continuously toggle LEDs  
4. Add delay using a simple loop  

## ⏱️ Delay Mechanism
for(int i=0;i<100000;i++){}

Note: Not accurate, depends on CPU speed.

## 🧪 Build & Flash
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -o main.elf main.c

## ⚠️ Limitations
- No abstraction layer
- Delay not precise
- No interrupt handling

## 🔥 Improvements
- Use SysTick timer
- Use BSRR instead of ODR
- Add button input
- Create reusable driver

## 📌 Author
Akanksha Bhaisare
