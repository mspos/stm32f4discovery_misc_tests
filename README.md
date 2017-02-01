File di esercizio per la creazione di progetti per la board Discovery (rev. C) con un STM32F407GVT a bordo. Progetti sia 
da SW4STM32 IDE sia compilati con CMAKE e toolchain GCC arm-none-eabi, entrambi inizializzati con CUBEMX

N.B. Per inizializzare correttamente il clock di tutte le periferiche e dei bus per DEBUGGARE tramite l'interfaccia ST-LINK utilizzare 
     il seguente setup : HSE (8 MHz su Discovery)/M 5 *N 210 /P 2 (use PLLCLK) AHB Presc /1 APB1 Presc /4 APB2 Presc /2

Files from tutorials, for exercise on creation of different project to test the Discovery board (rev. C) with STM32F407VGT
MCU. The projects are made both with SW4STM32 IDE and with CMAKE and GCC arm-none-eabi toolchani, both of them are
initialized with CUBEMX