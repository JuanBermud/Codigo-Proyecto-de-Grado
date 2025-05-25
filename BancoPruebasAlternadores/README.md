# Banco de Pruebas para Alternadores

Este proyecto implementa un sistema de diagnóstico para alternadores automotrices, utilizando sensores de voltaje, corriente y temperatura controlados por un microcontrolador Mega 2560 Pro.

## Funcionalidades

- Medición de voltaje del alternador (0–25V)
- Medición de corriente de salida (sensor Hall ACS758)
- Medición de temperatura superficial (DS18B20)
- Visualización en pantalla LCD 20x4 vía I2C

## Estructura del proyecto

```
BancoPruebasAlternadores/
├── codigo/
│   └── monitor_alternador.ino
├── doc/
│   └── [Coloca aquí tu informe o PDF]
├── imagenes/
│   └── [Diagramas o fotos del banco de pruebas]
└── README.md
```

## Requisitos de hardware

- Arduino Mega 2560 Pro
- Sensor FZ0430 (voltaje)
- Sensor ACS758 (corriente)
- Sensor DS18B20 (temperatura)
- Pantalla LCD 20x4 con módulo I2C
- Regulador LM2596
- Bombillos H4 (como cargas)

## Licencia

MIT
