#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int avg = (int) round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

      image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = avg;
    }
  }
  
  return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < (width / 2); j++) {
      RGBTRIPLE tmp = image[i][j];
      image[i][j] = image[i][width - 1 - j];
      image[i][width - 1 - j] = tmp;
    }
  }
  return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
  RGBTRIPLE copy[height][width];

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      copy[i][j] = image[i][j];
    }
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {

      int inGrid = 0; 
      int avgRed, avgGreen, avgBlue;
      avgRed = avgGreen = avgBlue = 0;
      
      for (int k = i - 1; k <= i + 1; k++) {
        for (int l = j - 1; l <= j + 1; l++) {
          if (k >= 0 && k < height && l >= 0 && l < width) {
	    inGrid++;
            avgRed += copy[k][l].rgbtRed;
            avgGreen += copy[k][l].rgbtGreen;
            avgBlue += copy[k][l].rgbtBlue;
          }
        }
      }

      image[i][j].rgbtRed = (int)round((double)avgRed / inGrid);
      image[i][j].rgbtGreen = (int)round((double)avgGreen / inGrid);
      image[i][j].rgbtBlue = (int)round((double)avgBlue / inGrid);
      
    }
  }
  
  return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
  RGBTRIPLE copy[height][width];

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      copy[i][j] = image[i][j];
    }
  }
  
  int gx[3][3] = {
    {-1, 0, 1},
    {-2, 0, 2},
    {-3, 0, 3}
  };

  int gy[3][3] = {
    {-1, -2, -1},
    {0, 0, 0},
    {1, 2, 1}
  };

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int xSumRed, xSumGreen, xSumBlue;
      int ySumRed, ySumGreen, ySumBlue;

      xSumRed = xSumGreen = xSumBlue = 0;
      ySumRed = ySumGreen = ySumBlue = 0;
      
      for (int k = i - 1; k <= i + 1; k++) {
	for (int l = j - 1; l <= j + 1; l++) {
	  if (k >= 0 && k < height && l >= 0 && l < width) {
            xSumRed += copy[k][l].rgbtRed * gx[k - i + 1][l - j + 1];
            ySumRed += copy[k][l].rgbtRed * gy[k - i + 1][l - j + 1];

            xSumGreen += copy[k][l].rgbtGreen * gx[k - i + 1][l - j + 1];
            ySumGreen += copy[k][l].rgbtGreen * gy[k - i + 1][l - j + 1];

            xSumBlue += copy[k][l].rgbtBlue * gx[k - i + 1][l - j + 1];
            ySumBlue += copy[k][l].rgbtBlue * gy[k - i + 1][l - j + 1];
          }
	}
      }

      int red = round(sqrt(pow(xSumRed,2) + pow(ySumRed, 2)));
      red = red > 255 ? 255 : red;

      int green = round(sqrt(pow(xSumGreen, 2) + pow(ySumGreen, 2)));
      green = green > 255 ? 255 : green;

      int blue = round(sqrt(pow(xSumBlue, 2) + pow(ySumBlue, 2)));
      blue = blue > 255 ? 255 : blue;

      image[i][j].rgbtRed = red;
      image[i][j].rgbtGreen = green;
      image[i][j].rgbtBlue = blue;
    }
  }
  
  return;
}
