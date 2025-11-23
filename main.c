#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 定義最大影像尺寸
#define MAX_WIDTH 2048
#define MAX_HEIGHT 2048

// 影像結構定義
typedef struct {
    int width;
    int height;
    unsigned char data[MAX_HEIGHT][MAX_WIDTH];
} Image;

// 讀取 PGM 影像 (ASCII P2 格式)
void readPGM(const char *filename, Image *img) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("無法開啟檔案");
        exit(1);
    }

    char format[3];
    fscanf(fp, "%s", format);
    if (format[0] != 'P' || format[1] != '2') {
        printf("錯誤：僅支援 P2 格式的 PGM 檔案。\n");
        exit(1);
    }

    int max_val;
    fscanf(fp, "%d %d", &img->width, &img->height);
    fscanf(fp, "%d", &max_val);

    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            int pixel;
            fscanf(fp, "%d", &pixel);
            img->data[i][j] = (unsigned char)pixel;
        }
    }
    fclose(fp);
    printf("成功讀取影像: %s (%dx%d)\n", filename, img->width, img->height);
}

// 寫入 PGM 影像
void writePGM(const char *filename, Image *img) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("無法寫入檔案");
        exit(1);
    }

    fprintf(fp, "P2\n");
    fprintf(fp, "%d %d\n", img->width, img->height);
    fprintf(fp, "255\n");

    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            fprintf(fp, "%d ", img->data[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    printf("成功輸出結果: %s\n", filename);
}

// 核心演算法：Sobel 邊緣檢測 (模擬高效能矩陣運算)
void sobelFilter(Image *src, Image *dest) {
    dest->width = src->width;
    dest->height = src->height;

    // Sobel 卷積核 (Kernels)
    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int Gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    // 遍歷每個像素 (忽略邊界以簡化計算)
    for (int y = 1; y < src->height - 1; y++) {
        for (int x = 1; x < src->width - 1; x++) {
            int sumX = 0;
            int sumY = 0;

            // 進行 3x3 矩陣卷積運算
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    sumX += src->data[y + i][x + j] * Gx[i + 1][j + 1];
                    sumY += src->data[y + i][x + j] * Gy[i + 1][j + 1];
                }
            }

            // 計算梯度大小 (Gradient Magnitude)
            int magnitude = (int)sqrt(sumX * sumX + sumY * sumY);
            
            // 限制數值在 0-255 之間
            if (magnitude > 255) magnitude = 255;
            if (magnitude < 0) magnitude = 0;

            dest->data[y][x] = (unsigned char)magnitude;
        }
    }
}

int main() {
    static Image inputImg, outputImg;

    // 1. 讀取原始乳房超音波影像 (input.pgm)
    // 請確保你的資料夾內有名為 input.pgm 的檔案
    readPGM("input.pgm", &inputImg);

    // 2. 執行高效能運算 (Sobel 濾波)
    printf("正在進行矩陣卷積運算...\n");
    sobelFilter(&inputImg, &outputImg);

    // 3. 輸出處理後的影像
    writePGM("output.pgm", &outputImg);

    printf("處理完成！請查看 output.pgm\n");
    return 0;
}