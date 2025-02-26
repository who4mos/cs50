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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int sepiaRed = (int) round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
      int sepiaGreen = (int) round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
      int sepiaBlue = (int) round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

      
      image[i][j].rgbtRed = sepiaRed > 255 ? 255: sepiaRed;
      image[i][j].rgbtGreen = sepiaGreen > 255 ? 255: sepiaGreen;
      image[i][j].rgbtBlue = sepiaBlue > 255 ? 255: sepiaBlue;
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
