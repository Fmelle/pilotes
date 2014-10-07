drivers/pilotes
===============
(Driver files serving the Sailboat Automation Project  // Fichiers pilotes servant le Projet Automatisation d'un Voilier)

Battery-driven sailboat model equipped with motorized direction control and sails supervised by a HF remote with wind and inclination sensors, and a HF transmitter that enables reading of battery status and sensor values as well as transmission of alerts for boat inclination and battery-level.

Functionality enabled and controlled with devices connected through a ARM Cortex-M3 STM32F103RB MCU.

Purpose-specific application layer of device drivers include:
(applications/)
- Direction control
- Sails control
- Alert control

Device drivers include:
(services/)
- Accelerometer
- Battery
- HF Transmitter
- HF Receiver
- Incremental encoder (wind sensor)
- DC motor
- Servo motor

MCU Peripherals customized drivers include:
- gpio
- timer
- adc
- usart
