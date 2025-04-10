# STM32 + esp32
STM32 and esp32 components

1. board  
STM32f103C8T6 + esp32s

2. tool chain  
    - STM32: STM32CUBEMX + MDK-ARM + STLink
    - esp32: vscode + espidf  

## STM32

### Led
Led：PC13  

### OTA
Upgrade the STM32 OTA using wifi(esp32s)

### OTA
1. Led  
Use LED on and off as a debugging method.

2. UART1 
- Use UART as a debugging medtho.  
- Please mark the "use micro-lib" when the printf is not avalaiable

3. UART2
- connect to esp32
- rx: PA3
- tx: PA2

## esp32

### OTA_esp32
1. blink
Use LED on and off as a debugging method.  

2. uart
Use UART as a debugging medtho.  

3. wifi
The wifi feature of esp32 is used as the communication protocol.