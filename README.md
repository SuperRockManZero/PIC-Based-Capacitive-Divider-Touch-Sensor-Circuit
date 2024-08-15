# PIC based capacitive divider touch sensor circuit
This is a capacitive touch sensing circuit based on the principle of capacitive voltage division, controlled by a PIC microcontroller. When a finger touches or approaches the sensing area, the capacitance of the sensor changes, which causes a shift in the voltage division ratio. The PIC microcontroller detects these changes using its internal ADC (Analog-to-Digital Converter) to recognize touch actions.

這是一個根據電容分壓原理的觸控感應電路，使用了 PIC 微處理器進行控制。當手指接觸或接近感應區域時，會改變感應器的電容值，這引起了電壓分壓比的變化。PIC 微處理器通過內部的 ADC 來檢測這些變化，從而識別觸控動作。
## 工作原理
![CVD差分波形](picture/%E5%9C%96%E4%BA%8C_%E5%B7%AE%E5%88%86CVD%E6%B3%A2%E5%BD%A2.jpg)
![預充電階段](picture/%E5%9C%96%E5%9B%9B_%E9%A0%90%E5%85%85%E9%9B%BB%E9%9A%8E%E6%AE%B5.jpg)
![採樣階段](picture/%E5%9C%96%E4%BA%94_%E6%8E%A1%E6%A8%A3%E9%9A%8E%E6%AE%B5.jpg)
![CVD差分結果](picture/%E5%9C%96%E5%85%AD_CVD%E5%B7%AE%E5%88%86%E7%B5%90%E6%9E%9C.jpg)
![CVD信號](picture/%E5%9C%96%E4%B8%83_CVD%E4%BF%A1%E8%99%9F.jpg)

## Schematic 電路圖
![CVD verB](sch/CVD%20ver%20B.jpg)
## 參考資料
- Microchip AN1478 mTouch™ Sensing Solution Acquisition Methods                                         Capacitive Voltage Divider

## Prototype 樣機展示

*ver A*
[![Prototype verA](https://img.youtube.com/vi/0q65-RAXcD0/0.jpg)](https://youtu.be/0q65-RAXcD0)

*ver B*  
[![Prototype verA](https://img.youtube.com/vi/ckIhD4DM1XI/0.jpg)](https://youtu.be/ckIhD4DM1XI)
