#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // where do i find the height and with?
    // in the bmp.h file, in the BITMAPINFOHEADER struct the are two LONG attributes that are
    // respectively biwidth and and biheight

    // these LONG values are the number of rows (height) and the number of RGBTRIPLE's that i have
    // to transform
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];

            float average = round((pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed) / 3.0);

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];

            int new_blue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                                 .131 * image[i][j].rgbtBlue);
            int new_green = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                                  .168 * image[i][j].rgbtBlue);
            int new_red = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                                .189 * image[i][j].rgbtBlue);

            new_blue = (new_blue > 255) ? 255 : new_blue;
            new_green = (new_green > 255) ? 255 : new_green;
            new_red = (new_red > 255) ? 255 : new_red;

            image[i][j].rgbtBlue = new_blue;
            image[i][j].rgbtGreen = new_green;
            image[i][j].rgbtRed = new_red;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE original_pixel = image[i][j];
            // for a 4x4 grid, the last position has the index 3, and to keep iterating backwards,
            // we are substracting the j index
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = original_pixel;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blur_copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum_red = 0;
            int sum_blue = 0;
            int sum_green = 0;
            float count = 0;

            for (int x = i - 1; x <= i + 1; x++)
            {
                for (int y = j - 1; y <= j + 1; y++)
                {
                    if (x < height && x >= 0 && y < width && y >= 0)
                    {
                        sum_red += image[x][y].rgbtRed;
                        sum_blue += image[x][y].rgbtBlue;
                        sum_green += image[x][y].rgbtGreen;
                        count++;
                    }
                }
            }

            float average_red = sum_red / count;
            float average_blue = sum_blue / count;
            float average_green = sum_green / count;

            blur_copy[i][j].rgbtRed = round(average_red);
            blur_copy[i][j].rgbtBlue = round(average_blue);
            blur_copy[i][j].rgbtGreen = round(average_green);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = blur_copy[i][j].rgbtRed;
            image[i][j].rgbtBlue = blur_copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = blur_copy[i][j].rgbtGreen;
        }
    }
    return;
}
