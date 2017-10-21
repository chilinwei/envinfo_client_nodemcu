# **使用 Raspberry Pi 3 進行感測器資料蒐集 (NodeMCU client)**

本範例使用 Raspberry Pi 3 (RPi) 與 NodeMCU 建構一環境資訊蒐集系統，範例分為3部份
- [envinfo_server](https://github.com/chilinwei/envinfo_server)：使用RPi作為主機接收所有感測器回傳的資料
- [envinfo_client_rpi](https://github.com/chilinwei/envinfo_client_rpi)：使用RPi作為感測器的示範
- [envinfo_client_nodemcu](https://github.com/chilinwei/envinfo_client_nodemcu)：使用NodeMCU作為感測器的示範

## **目錄**
0. [系統架構說明](#0-系統架構說明)
1. [使用 Arduino IDE 進行 NodeMCU(esp8266) 開發](#1-使用-arduino-ide-進行-nodemcuesp8266-開發)
2. [NodeMCU 安裝感測器](#2-nodemcu-安裝感測器)
3. [安裝與部署本範例程式](#3-安裝與部署本範例程式)

### **0. 系統架構說明**
本範例使用 Raspberry Pi 3 (RPi) 與 NodeMCU 建構一環境資訊蒐集系統。設計上client以無線網路方式透過master提供的RESTful api將感測器的數值與PiCamera拍攝的照片儲存於其中，使用者可透過瀏覽器查詢。
![](/pic/pic1.png)

### **1. 使用 Arduino IDE 進行 NodeMCU(esp8266) 開發**
(1) 安裝 Arduino IDE
請參考 [Getting Started with Arduino and Genuino products](https://www.arduino.cc/en/Guide/HomePage)  
參閱 "Install the Arduino Desktop IDE" 部份  
**請安裝 1.6.4 以上版本**

(2) 安裝 esp8266 硬體套件   
請參考 [Arduino core for ESP8266 WiFi chip](https://github.com/esp8266/Arduino)  
建議使用 Boards Manager 安裝，請參閱 [Installing with Boards Manager](https://github.com/esp8266/Arduino#installing-with-boards-manager)

### **2. NodeMCU 安裝感測器**
本範例為使用 NodeMCU 作為 client 將感測器數據上傳到 server，安裝的感測器有以下幾種

類型 | 規格 | 訊號
--- | --- | ---
溫度與濕度感測器 | DHT11 | 數位
光敏電阻 | CD5592, 5M/M | 電壓

我們使用的感測器輸出的訊號包含數位與類比(電壓)，參考NodeMCU各腳位定義，光敏電阻電壓量測使用 A0 腳位，DHT11 訊號使用 D1 腳位。

![](/pic/NODEMCU-DEVKIT-INSTRUCTION-EN.png)

(1) 將感測器接到 NodeMCU  
參考下圖
![](/pic/pic2.png)

### **3. 安裝與部署本範例程式**
(1) 使用 Git 或下載方始取得範例程式碼  
程式碼網址
[https://github.com/chilinwei/envinfo_client_nodemcu](https://github.com/chilinwei/envinfo_client_nodemcu)

(2) 使用 Arduino IDE 開啟  
**注意：讀取 DHT11 需要 include 相關的插件 [DHT-sensor-library](https://github.com/adafruit/DHT-sensor-library) 與 [Adafruit_Sensor](https://github.com/adafruit/Adafruit_Sensor)**

(3) 使用 Arduino IDE 寫入