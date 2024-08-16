# PIC based capacitive divider touch sensor circuit
This is a touch sensing circuit based on the principle of capacitive voltage division. It employs differential measurement techniques, which effectively reduce interference from environmental noise, thereby enhancing detection accuracy. When a finger touches or approaches the sensing area, the capacitance of the sensor changes, causing a variation in the voltage division ratio. The PIC microcontroller, using its built-in ADC, detects and processes these changes to accurately identify touch actions.

這是一個依據電容分壓原理的觸控感應電路，採用了差分測量技術，可以有效減少環境噪聲對觸控偵測的干擾，提升感應準確度。
當手指接觸或靠近感應區域時，感應器的電容值會改變，導致電壓分壓比的變動。PIC 微處理器以內建的 ADC 檢測並處理這些變化，進而精確識別觸控動作。

## CVD 的優點
1. 低溫度依賴性：在 -20°C 至 +60°C 範圍內，信號偏移通常只有 1-3%。通常根據傳感器值的緩慢變化在軟體補償此偏移量。
2. 低 $`V_{DD}`$ 依賴性：因為感應器的電荷與 ADC 的參考電壓相同，因此 $`V_{DD}`$ 的低頻變化對信號影響不大，但高頻干擾可能會產生噪聲。
3. 硬體需求低：只需簡單的硬體配置，如串聯電阻即可降低噪聲，如果噪聲不重要，甚至不需要外部元件。
4. 低頻噪聲抑制：CVD 波形的兩次 ADC 取樣會因為差分方法而互相抵消低頻噪聲，同時放大有效信號。

## 工作原理
![CVD差分波形](picture/%E5%9C%96%E4%BA%8C_%E5%B7%AE%E5%88%86CVD%E6%B3%A2%E5%BD%A2.jpg)


步骤1：预充电电容将两个电容充电至相反的电压。第一次执行为“采样A”。第二次（在步骤 4-6 中介绍）为“采样 B”。如图4所示。采样A：• 外部传感器放电至VSS。• 内部传感器充电至VDD。采样B：• 外部传感器充电至VDD。• 内部传感器放电至VSS。
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
