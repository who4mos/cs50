#include "helpers.h"
#include <math.h>

// Return the lesse of two integers (helper to edges)
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) {
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

            int gx[3][3] = {
                {-1, 0, 1},
                {-2, 0, 2},
                {-1, 0, 1}
            };

            int gy[3][3] = {
                {-1, -2, -1},
                {0, 0, 0},
                {1, 2, 1}
            };

            int gx_red_sum, gx_green_sum, gx_blue_sum;
            gx_red_sum = gx_green_sum = gx_blue_sum = 0;

            int gy_red_sum, gy_green_sum, gy_blue_sum;
            gy_red_sum = gy_green_sum = gy_blue_sum = 0;

            for (int i = row - 1; i <= row + 1; i++) {
                for (int j = col - 1; j <= col + 1; j++) {
                    if (i < 0 || i == height || j < 0 || j == width)
                        continue;

                    gx_red_sum += (
                                   copy[i][j].rgbtRed
                                   * gx[i-row+1][j-col+1]
                                  );
                    gy_red_sum += (
                                   copy[i][j].rgbtRed
                                   * gy[i-row+1][j-col+1]
                                  );

                    gx_green_sum += (
                                     copy[i][j].rgbtGreen
                                     * gx[i-row+1][j-col+1]
                                    );
                    gy_green_sum += (
                                     copy[i][j].rgbtGreen
                                     * gy[i-row+1][j-col+1]
                                    );

                    gx_blue_sum += (
                                    copy[i][j].rgbtBlue
                                    * gx[i-row+1][j-col+1]
                                   );
                    gy_blue_sum += (
                                    copy[i][j].rgbtBlue
                                    * gy[i-row+1][j-col+1]
                                   );
                        
                }
            }
                
            int final_red, final_green, final_blue;

            final_red = round(sqrt(pow(gx_red_sum, 2) + pow(gy_red_sum, 2)));
            final_red = lesser(final_red, 0xff);

            final_green = round(sqrt(pow(gx_green_sum, 2) + pow(gy_green_sum, 2)));
            final_green = lesser(final_green, 0xff);

            final_blue = round(sqrt(pow(gx_blue_sum, 2) + pow(gy_blue_sum, 2)));
            final_blue = lesser(final_blue, 0xff);

            pixel->rgbtRed = final_red;
            pixel->rgbtGreen = final_green;
            pixel->rgbtBlue = final_blue;
        }
    }
}


int lesser(int a, int b) {
    if (a < b)
        return a;
    return b;
}
