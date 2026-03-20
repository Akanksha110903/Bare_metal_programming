# Bare Metal LED Blinking (STM32F407)

## 📌 Overview

This project demonstrates **bare-metal programming** on the STM32F407 microcontroller by directly accessing hardware registers (without using HAL or any external libraries).

The program configures GPIO pins and toggles onboard LEDs using register-level programming.

---

## ⚙️ Hardware Used

* STM32F407 Discovery Board

---

## 🧠 Key Concepts Covered

* Peripheral base addresses
* Memory-mapped I/O
* RCC clock enabling
* GPIO configuration (MODER register)
* Output Data Register (ODR)
* Bitwise operations

---

## 📂 Project Structure

```
First/
├── Src/
│   ├── main.c
├── Startup/
│   ├── startup_stm32f407vgtx.s
├── STM32F407VGTX_FLASH.ld
├── STM32F407VGTX_RAM.ld
```

---

## 🚀 How it Works

### 1. Enable Clock for GPIOD

The AHB1 peripheral clock is enabled using RCC register:

```
RCC_AHB1ENR |= (1 << 3);
```

---

### 2. Configure Pins as Output

Pins PD12–PD15 are configured as output using MODER register:

```
MODER = 01 (Output mode)
```

---

### 3. Toggle LEDs

LEDs are toggled using XOR operation on ODR register:

```
GPIOD_ODR ^= (LED_RED | LED_GREEN | LED_BLUE | LED_ORANGE);
```

---

## 💡 LEDs Mapping

| LED Color | Pin  |
| --------- | ---- |
| Green     | PD12 |
| Orange    | PD13 |
| Red       | PD14 |
| Blue      | PD15 |

---

## ⚠️ Important Notes

* This project uses **direct register access** (no HAL/LL libraries)
* XOR-based toggling is **not atomic** (not safe in interrupt-heavy systems)
* Suitable for learning low-level embedded programming

---

## 🛠️ Build & Run

* Open project in STM32CubeIDE
* Build the project
* Flash to STM32 board
* Observe LEDs blinking

---

## 📚 Learning Outcome

* Understanding of MCU register-level programming
* Hands-on with GPIO and clock configuration
* Strong foundation for embedded firmware development

---

## 👩‍💻 Author

Akanksha Bhaisare
