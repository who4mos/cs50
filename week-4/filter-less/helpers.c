#include "helpers.h"
#include <math.h>

// Return the lesse of two integers (helper to sepia)
int lesser(int a, int b);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col ++) {
            RGBTRIPLE *pixel = &image[row][col];

            int red   = pixel->rgbtRed;
            int green = pixel->rgbtGreen;
            int blue  = pixel->rgbtBlue;

            int avg = round((red + green + blue) / 3.0);

            pixel->rgbtRed = avg;
            pixel->rgbtGreen = avg;
            pixel->rgbtBlue = avg;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            RGBTRIPLE *pixel = &image[row][col];

            int ogRed = pixel->rgbtRed;
            int ogGreen = pixel->rgbtGreen;
            int ogBlue = pixel->rgbtBlue;

            int sepiaRed = round(.393 * ogRed + .769 * ogGreen + .189 * ogBlue);
            sepiaRed = lesser(sepiaRed, 0xff);
            
            int sepiaGreen = round(.349 * ogRed + .686 * ogGreen + .168 * ogBlue);
            sepiaGreen = lesser(sepiaGreen, 0xff);

            int sepiaBlue = round(.272 * ogRed + .534 * ogGreen + .131 * ogBlue);
            sepiaBlue = lesser(sepiaBlue, 0xff);
            
            pixel->rgbtRed = sepiaRed;
            pixel->rgbtGreen = sepiaGreen;
            pixel->rgbtBlue = sepiaBlue;
        }
    }
}

int lesser(int a, int b) {
    if (a < b)
        return a;
    return b;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width / 2; col++) {
            RGBTRIPLE tmp = image[row][col];
            image[row][col] = image[row][width - 1 - col];
            image[row][width - 1 - col] = tmp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE copy[height][width];
    int row, col;

    for (row = 0; row < height; row++) {
        for (col = 0; col < width; col++) {
            copy[row][col] = image[row][col];
        }
    }

    for (row = 0; row < height; row++) {
        for (col = 0; col < width; col++) {
            RGBTRIPLE *pixel = &image[row][col];

            int count, red_sum, green_sum, blue_sum;
            count = red_sum = green_sum = blue_sum = 0;
            
            for (int i = row - 1; i <= row + 1; i++) {
                for (int j = col - 1; j <= col + 1; j++) {
                    if (i >= 0 && i < height && j >= 0 && j < width) {
                        red_sum += copy[i][j].rgbtRed;
                        green_sum += copy[i][j].rgbtGreen;
                        blue_sum += copy[i][j].rgbtBlue;
                        count++;
                    }
                }
            }

            int red_avg = round(red_sum / (float) count);
            int green_avg = round(green_sum / (float) count);
            int blue_avg = round(blue_sum / (float) count);

            pixel->rgbtRed = red_avg;
            pixel->rgbtGreen = green_avg;
            pixel->rgbtBlue = blue_avg;
        }
    }
}

