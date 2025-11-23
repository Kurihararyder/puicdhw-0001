# Breast Ultrasound Image Enhancement (C Implementation)
### 乳房超音波影像特徵強化專案

本專案為 **[程式設計]** 之期末微專題。
專案利用 C 語言實作高效能矩陣卷積運算（Convolution），針對乳房超音波影像進行邊緣檢測，以強化潛在病灶的特徵。

## 📂 專案簡介 (Introduction)
乳房超音波（Breast Ultrasound）是早期發現乳癌的重要工具。然而，超音波影像常伴隨斑點雜訊，導致邊緣模糊。
本程式實作了 **Sobel 運算子 (Sobel Operator)**，透過計算影像梯度的強度，能夠有效標示出影像中的邊緣輪廓，模擬醫療影像處理中的特徵萃取過程。

這是一個展示 **C 語言高效能計算 (High Performance Computing)** 的範例，核心在於對大量像素數據進行快速的矩陣操作。

## 🚀 功能特色 (Features)
* **純 C 語言實作**：不依賴任何外部大型函式庫 (如 OpenCV)，展示底層實作能力。
* **矩陣卷積 (Convolution)**：實作 3x3 核心的空間濾波運算。
* **PGM 格式支援**：直接讀寫 ASCII PGM 影像格式，方便觀察數值變化。

## 🛠️ 如何編譯與執行 (Build & Run)

### 1. 編譯程式
使用 GCC 編譯器：
```bash
gcc main.c -o sobel_process -lm
