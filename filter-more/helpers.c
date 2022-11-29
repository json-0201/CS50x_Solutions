#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gray_value = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            image[i][j].rgbtBlue = gray_value;
            image[i][j].rgbtGreen = gray_value;
            image[i][j].rgbtRed = gray_value;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // (width / 2) -> switch once to reflect
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];

            // Index [width - 1] -> if width is 50, last element is [49]
            image[i][j] = image[i][width -1 -j];
            image[i][width -1 - j] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copied array of image - for calculating average
    // Applying average will to original array will continuously change the values
    RGBTRIPLE image_copy[height][width];
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    int r, g, b;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0)
            {
                // Top left corner
                if (j == 0)
                {
                    r = round((image_copy[i][j].rgbtRed+image_copy[i][j+1].rgbtRed+image_copy[i+1][j].rgbtRed+image_copy[i+1][j+1].rgbtRed) / 4.0);
                    g = round((image_copy[i][j].rgbtGreen+image_copy[i][j+1].rgbtGreen+image_copy[i+1][j].rgbtGreen+image_copy[i+1][j+1].rgbtGreen) / 4.0);
                    b = round((image_copy[i][j].rgbtBlue+image_copy[i][j+1].rgbtBlue+image_copy[i+1][j].rgbtBlue+image_copy[i+1][j+1].rgbtBlue) / 4.0);
                }

                // Top right corner
                else if (j == width -1)
                {
                    r = round((image_copy[i][j-1].rgbtRed+image_copy[i][j].rgbtRed+image_copy[i+1][j-1].rgbtRed+image_copy[i+1][j].rgbtRed) / 4.0);
                    g = round((image_copy[i][j-1].rgbtGreen+image_copy[i][j].rgbtGreen+image_copy[i+1][j-1].rgbtGreen+image_copy[i+1][j].rgbtGreen) / 4.0);
                    b = round((image_copy[i][j-1].rgbtBlue+image_copy[i][j].rgbtBlue+image_copy[i+1][j-1].rgbtBlue+image_copy[i+1][j].rgbtBlue) / 4.0);
                }

                // In between
                else
                {
                    r = round((image_copy[i][j-1].rgbtRed+image_copy[i][j].rgbtRed+image_copy[i][j+1].rgbtRed+image_copy[i+1][j-1].rgbtRed+image_copy[i+1][j].rgbtRed+image_copy[i+1][j+1].rgbtRed) / 6.0);
                    g = round((image_copy[i][j-1].rgbtGreen+image_copy[i][j].rgbtGreen+image_copy[i][j+1].rgbtGreen+image_copy[i+1][j-1].rgbtGreen+image_copy[i+1][j].rgbtGreen+image_copy[i+1][j+1].rgbtGreen) / 6.0);
                    b = round((image_copy[i][j-1].rgbtBlue+image_copy[i][j].rgbtBlue+image_copy[i][j+1].rgbtBlue+image_copy[i+1][j-1].rgbtBlue+image_copy[i+1][j].rgbtBlue+image_copy[i+1][j+1].rgbtBlue) / 6.0);
                }
            }

            else if (i == height - 1)
            {
                // Bottom left corner
                if (j == 0)
                {
                    r = round((image_copy[i-1][j].rgbtRed+image_copy[i-1][j+1].rgbtRed+image_copy[i][j].rgbtRed+image_copy[i][j+1].rgbtRed) / 4.0);
                    g = round((image_copy[i-1][j].rgbtGreen+image_copy[i-1][j+1].rgbtGreen+image_copy[i][j].rgbtGreen+image_copy[i][j+1].rgbtGreen) / 4.0);
                    b = round((image_copy[i-1][j].rgbtBlue+image_copy[i-1][j+1].rgbtBlue+image_copy[i][j].rgbtBlue+image_copy[i][j+1].rgbtBlue) / 4.0);
                }

                // Bottom right corner
                else if (j == width -1)
                {
                    r = round((image_copy[i-1][j-1].rgbtRed+image_copy[i-1][j].rgbtRed+image_copy[i][j-1].rgbtRed+image_copy[i][j].rgbtRed) / 4.0);
                    g = round((image_copy[i-1][j-1].rgbtGreen+image_copy[i-1][j].rgbtGreen+image_copy[i][j-1].rgbtGreen+image_copy[i][j].rgbtGreen) / 4.0);
                    b = round((image_copy[i-1][j-1].rgbtBlue+image_copy[i-1][j].rgbtBlue+image_copy[i][j-1].rgbtBlue+image_copy[i][j].rgbtBlue) / 4.0);
                }

                // In between
                else
                {
                    r = round((image_copy[i-1][j-1].rgbtRed+image_copy[i-1][j].rgbtRed+image_copy[i-1][j+1].rgbtRed+image_copy[i][j-1].rgbtRed+image_copy[i][j].rgbtRed+image_copy[i][j+1].rgbtRed) / 6.0);
                    g = round((image_copy[i-1][j-1].rgbtGreen+image_copy[i-1][j].rgbtGreen+image_copy[i-1][j+1].rgbtGreen+image_copy[i][j-1].rgbtGreen+image_copy[i][j].rgbtGreen+image_copy[i][j+1].rgbtGreen) / 6.0);
                    b = round((image_copy[i-1][j-1].rgbtBlue+image_copy[i-1][j].rgbtBlue+image_copy[i-1][j+1].rgbtBlue+image_copy[i][j-1].rgbtBlue+image_copy[i][j].rgbtBlue+image_copy[i][j+1].rgbtBlue) / 6.0);
                }
            }

            else
            {
                // Left side (no corners)
                if (j == 0)
                {
                    r = round((image_copy[i-1][j].rgbtRed+image_copy[i-1][j+1].rgbtRed+image_copy[i][j].rgbtRed+image_copy[i][j+1].rgbtRed+image_copy[i+1][j].rgbtRed+image_copy[i+1][j+1].rgbtRed) / 6.0);
                    g = round((image_copy[i-1][j].rgbtGreen+image_copy[i-1][j+1].rgbtGreen+image_copy[i][j].rgbtGreen+image_copy[i][j+1].rgbtGreen+image_copy[i+1][j].rgbtGreen+image_copy[i+1][j+1].rgbtGreen) / 6.0);
                    b = round((image_copy[i-1][j].rgbtBlue+image_copy[i-1][j+1].rgbtBlue+image_copy[i][j].rgbtBlue+image_copy[i][j+1].rgbtBlue+image_copy[i+1][j].rgbtBlue+image_copy[i+1][j+1].rgbtBlue) / 6.0);
                }

                // Right side (no corners)
                else if (j == width - 1)
                {
                    r = round((image_copy[i-1][j-1].rgbtRed+image_copy[i-1][j].rgbtRed+image_copy[i][j-1].rgbtRed+image_copy[i][j].rgbtRed+image_copy[i+1][j-1].rgbtRed+image_copy[i+1][j].rgbtRed) / 6.0);
                    g = round((image_copy[i-1][j-1].rgbtGreen+image_copy[i-1][j].rgbtGreen+image_copy[i][j-1].rgbtGreen+image_copy[i][j].rgbtGreen+image_copy[i+1][j-1].rgbtGreen+image_copy[i+1][j].rgbtGreen) / 6.0);
                    b = round((image_copy[i-1][j-1].rgbtBlue+image_copy[i-1][j].rgbtBlue+image_copy[i][j-1].rgbtBlue+image_copy[i][j].rgbtBlue+image_copy[i+1][j-1].rgbtBlue+image_copy[i+1][j].rgbtBlue) / 6.0);
                }

                // In between
                else
                {
                    r = round((image_copy[i-1][j-1].rgbtRed+image_copy[i-1][j].rgbtRed+image_copy[i-1][j+1].rgbtRed+image_copy[i][j-1].rgbtRed+image_copy[i][j].rgbtRed+image_copy[i][j+1].rgbtRed+image_copy[i+1][j-1].rgbtRed+image_copy[i+1][j].rgbtRed+image_copy[i+1][j+1].rgbtRed) / 9.0);
                    g = round((image_copy[i-1][j-1].rgbtGreen+image_copy[i-1][j].rgbtGreen+image_copy[i-1][j+1].rgbtGreen+image_copy[i][j-1].rgbtGreen+image_copy[i][j].rgbtGreen+image_copy[i][j+1].rgbtGreen+image_copy[i+1][j-1].rgbtGreen+image_copy[i+1][j].rgbtGreen+image_copy[i+1][j+1].rgbtGreen) / 9.0);
                    b = round((image_copy[i-1][j-1].rgbtBlue+image_copy[i-1][j].rgbtBlue+image_copy[i-1][j+1].rgbtBlue+image_copy[i][j-1].rgbtBlue+image_copy[i][j].rgbtBlue+image_copy[i][j+1].rgbtBlue+image_copy[i+1][j-1].rgbtBlue+image_copy[i+1][j].rgbtBlue+image_copy[i+1][j+1].rgbtBlue) / 9.0);
                }
            }

            image[i][j].rgbtRed = r;
            image[i][j].rgbtGreen = g;
            image[i][j].rgbtBlue = b;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_copy[i][j] = image[i][j];
        }
    }

    // Define kernals for both directions
    int kernal_x[3][3] = {{-1,0,1}, {-2,0,2}, {-1,0,1}};
    int kernal_y[3][3] = {{-1,-2,-1}, {0,0,0}, {1,2,1}};

    int r_x, r_y;
    int g_x, g_y;
    int b_x, b_y;
    int r_total, g_total, b_total;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0)
            {
                // Top left corner
                if (j == 0)
                {
                    r_x = image_copy[i][j].rgbtRed * kernal_x[1][1] + image_copy[i+1][j].rgbtRed * kernal_x[2][1] + image_copy[i][j+1].rgbtRed * kernal_x[1][2] + image_copy[i+1][j+1].rgbtRed * kernal_x[2][2];
                    r_y = image_copy[i][j].rgbtRed * kernal_y[1][1] + image_copy[i+1][j].rgbtRed * kernal_y[2][1] + image_copy[i][j+1].rgbtRed * kernal_y[1][2] + image_copy[i+1][j+1].rgbtRed * kernal_y[2][2];
                    r_total = round(sqrt(r_x * r_x + r_y * r_y));

                    g_x = image_copy[i][j].rgbtGreen * kernal_x[1][1] + image_copy[i+1][j].rgbtGreen * kernal_x[2][1] + image_copy[i][j+1].rgbtGreen * kernal_x[1][2] + image_copy[i+1][j+1].rgbtGreen * kernal_x[2][2];
                    g_y = image_copy[i][j].rgbtGreen * kernal_y[1][1] + image_copy[i+1][j].rgbtGreen * kernal_y[2][1] + image_copy[i][j+1].rgbtGreen * kernal_y[1][2] + image_copy[i+1][j+1].rgbtGreen * kernal_y[2][2];
                    g_total = round(sqrt(g_x * g_x + g_y * g_y));

                    b_x = image_copy[i][j].rgbtBlue * kernal_x[1][1] + image_copy[i+1][j].rgbtBlue * kernal_x[2][1] + image_copy[i][j+1].rgbtBlue * kernal_x[1][2] + image_copy[i+1][j+1].rgbtBlue * kernal_x[2][2];
                    b_y = image_copy[i][j].rgbtBlue * kernal_y[1][1] + image_copy[i+1][j].rgbtBlue * kernal_y[2][1] + image_copy[i][j+1].rgbtBlue * kernal_y[1][2] + image_copy[i+1][j+1].rgbtBlue * kernal_y[2][2];
                    b_total = round(sqrt(b_x * b_x + b_y * b_y));

                    if (r_total > 255)
                        r_total = 255;
                    if (g_total > 255)
                        g_total = 255;
                    if (b_total > 255)
                        b_total = 255;
                }

                // Top right corner
                else if (j == width - 1)
                {
                    r_x = image_copy[i][j].rgbtRed * kernal_x[1][1] + image_copy[i+1][j].rgbtRed * kernal_x[2][1] + image_copy[i][j-1].rgbtRed * kernal_x[1][0] + image_copy[i+1][j-1].rgbtRed * kernal_x[2][0];
                    r_y = image_copy[i][j].rgbtRed * kernal_y[1][1] + image_copy[i+1][j].rgbtRed * kernal_y[2][1] + image_copy[i][j-1].rgbtRed * kernal_y[1][0] + image_copy[i+1][j-1].rgbtRed * kernal_y[2][0];
                    r_total = round(sqrt(r_x * r_x + r_y * r_y));

                    g_x = image_copy[i][j].rgbtGreen * kernal_x[1][1] + image_copy[i+1][j].rgbtGreen * kernal_x[2][1] + image_copy[i][j-1].rgbtGreen * kernal_x[1][0] + image_copy[i+1][j-1].rgbtGreen * kernal_x[2][0];
                    g_y = image_copy[i][j].rgbtGreen * kernal_y[1][1] + image_copy[i+1][j].rgbtGreen * kernal_y[2][1] + image_copy[i][j-1].rgbtGreen * kernal_y[1][0] + image_copy[i+1][j-1].rgbtGreen * kernal_y[2][0];
                    g_total = round(sqrt(g_x * g_x + g_y * g_y));

                    b_x = image_copy[i][j].rgbtBlue * kernal_x[1][1] + image_copy[i+1][j].rgbtBlue * kernal_x[2][1] + image_copy[i][j-1].rgbtBlue * kernal_x[1][0] + image_copy[i+1][j-1].rgbtBlue * kernal_x[2][0];
                    b_y = image_copy[i][j].rgbtBlue * kernal_y[1][1] + image_copy[i+1][j].rgbtBlue * kernal_y[2][1] + image_copy[i][j-1].rgbtBlue * kernal_y[1][0] + image_copy[i+1][j-1].rgbtBlue * kernal_y[2][0];
                    b_total = round(sqrt(b_x * b_x + b_y * b_y));

                    if (r_total > 255)
                        r_total = 255;
                    if (g_total > 255)
                        g_total = 255;
                    if (b_total > 255)
                        b_total = 255;
                }

                // In between
                else
                {
                    r_x = image_copy[i][j].rgbtRed * kernal_x[1][1] + image_copy[i][j-1].rgbtRed * kernal_x[1][0] + image_copy[i][j+1].rgbtRed * kernal_x[1][2] + image_copy[i+1][j-1].rgbtRed * kernal_x[2][0] + image_copy[i+1][j].rgbtRed * kernal_x[2][1] + image_copy[i+1][j+1].rgbtRed * kernal_x[2][2];
                    r_y = image_copy[i][j].rgbtRed * kernal_y[1][1] + image_copy[i][j-1].rgbtRed * kernal_y[1][0] + image_copy[i][j+1].rgbtRed * kernal_y[1][2] + image_copy[i+1][j-1].rgbtRed * kernal_y[2][0] + image_copy[i+1][j].rgbtRed * kernal_y[2][1] + image_copy[i+1][j+1].rgbtRed * kernal_y[2][2];
                    r_total = round(sqrt(r_x * r_x + r_y * r_y));

                    g_x = image_copy[i][j].rgbtGreen * kernal_x[1][1] + image_copy[i][j-1].rgbtGreen * kernal_x[1][0] + image_copy[i][j+1].rgbtGreen * kernal_x[1][2] + image_copy[i+1][j-1].rgbtGreen * kernal_x[2][0] + image_copy[i+1][j].rgbtGreen * kernal_x[2][1] + image_copy[i+1][j+1].rgbtGreen * kernal_x[2][2];
                    g_y = image_copy[i][j].rgbtGreen * kernal_y[1][1] + image_copy[i][j-1].rgbtGreen * kernal_y[1][0] + image_copy[i][j+1].rgbtGreen * kernal_y[1][2] + image_copy[i+1][j-1].rgbtGreen * kernal_y[2][0] + image_copy[i+1][j].rgbtGreen * kernal_y[2][1] + image_copy[i+1][j+1].rgbtGreen * kernal_y[2][2];
                    g_total = round(sqrt(g_x * g_x + g_y * g_y));

                    b_x = image_copy[i][j].rgbtBlue * kernal_x[1][1] + image_copy[i][j-1].rgbtBlue * kernal_x[1][0] + image_copy[i][j+1].rgbtBlue * kernal_x[1][2] + image_copy[i+1][j-1].rgbtBlue * kernal_x[2][0] + image_copy[i+1][j].rgbtBlue * kernal_x[2][1] + image_copy[i+1][j+1].rgbtBlue * kernal_x[2][2];
                    b_y = image_copy[i][j].rgbtBlue * kernal_y[1][1] + image_copy[i][j-1].rgbtBlue * kernal_y[1][0] + image_copy[i][j+1].rgbtBlue * kernal_y[1][2] + image_copy[i+1][j-1].rgbtBlue * kernal_y[2][0] + image_copy[i+1][j].rgbtBlue * kernal_y[2][1] + image_copy[i+1][j+1].rgbtBlue * kernal_y[2][2];
                    b_total = round(sqrt(b_x * b_x + b_y * b_y));

                    if (r_total > 255)
                        r_total = 255;
                    if (g_total > 255)
                        g_total = 255;
                    if (b_total > 255)
                        b_total = 255;
                }
            }

            else if (i == height - 1)
            {
                // Bottom left corner
                if (j == 0)
                {
                    r_x = image_copy[i][j].rgbtRed * kernal_x[1][1] + image_copy[i-1][j].rgbtRed * kernal_x[0][1] + image_copy[i][j+1].rgbtRed * kernal_x[1][2] + image_copy[i-1][j+1].rgbtRed * kernal_x[0][2];
                    r_y = image_copy[i][j].rgbtRed * kernal_y[1][1] + image_copy[i-1][j].rgbtRed * kernal_y[0][1] + image_copy[i][j+1].rgbtRed * kernal_y[1][2] + image_copy[i-1][j+1].rgbtRed * kernal_y[0][2];
                    r_total = round(sqrt(r_x * r_x + r_y * r_y));

                    g_x = image_copy[i][j].rgbtGreen * kernal_x[1][1] + image_copy[i-1][j].rgbtGreen * kernal_x[0][1] + image_copy[i][j+1].rgbtGreen * kernal_x[1][2] + image_copy[i-1][j+1].rgbtGreen * kernal_x[0][2];
                    g_y = image_copy[i][j].rgbtGreen * kernal_y[1][1] + image_copy[i-1][j].rgbtGreen * kernal_y[0][1] + image_copy[i][j+1].rgbtGreen * kernal_y[1][2] + image_copy[i-1][j+1].rgbtGreen * kernal_y[0][2];
                    g_total = round(sqrt(g_x * g_x + g_y * g_y));

                    b_x = image_copy[i][j].rgbtBlue * kernal_x[1][1] + image_copy[i-1][j].rgbtBlue * kernal_x[0][1] + image_copy[i][j+1].rgbtBlue * kernal_x[1][2] + image_copy[i-1][j+1].rgbtBlue * kernal_x[0][2];
                    b_y = image_copy[i][j].rgbtBlue * kernal_y[1][1] + image_copy[i-1][j].rgbtBlue * kernal_y[0][1] + image_copy[i][j+1].rgbtBlue * kernal_y[1][2] + image_copy[i-1][j+1].rgbtBlue * kernal_y[0][2];
                    b_total = round(sqrt(b_x * b_x + b_y * b_y));

                    if (r_total > 255)
                        r_total = 255;
                    if (g_total > 255)
                        g_total = 255;
                    if (b_total > 255)
                        b_total = 255;
                }

                // Bottom right corner
                else if (j == width - 1)
                {
                    r_x = image_copy[i][j].rgbtRed * kernal_x[1][1] + image_copy[i-1][j].rgbtRed * kernal_x[0][1] + image_copy[i][j-1].rgbtRed * kernal_x[1][0] + image_copy[i-1][j-1].rgbtRed * kernal_x[0][0];
                    r_y = image_copy[i][j].rgbtRed * kernal_y[1][1] + image_copy[i-1][j].rgbtRed * kernal_y[0][1] + image_copy[i][j-1].rgbtRed * kernal_y[1][0] + image_copy[i-1][j-1].rgbtRed * kernal_y[0][0];
                    r_total = round(sqrt(r_x * r_x + r_y * r_y));

                    g_x = image_copy[i][j].rgbtGreen * kernal_x[1][1] + image_copy[i-1][j].rgbtGreen * kernal_x[0][1] + image_copy[i][j-1].rgbtGreen * kernal_x[1][0] + image_copy[i-1][j-1].rgbtGreen * kernal_x[0][0];
                    g_y = image_copy[i][j].rgbtGreen * kernal_y[1][1] + image_copy[i-1][j].rgbtGreen * kernal_y[0][1] + image_copy[i][j-1].rgbtGreen * kernal_y[1][0] + image_copy[i-1][j-1].rgbtGreen * kernal_y[0][0];
                    g_total = round(sqrt(g_x * g_x + g_y * g_y));


                    b_x = image_copy[i][j].rgbtBlue * kernal_x[1][1] + image_copy[i-1][j].rgbtBlue * kernal_x[0][1] + image_copy[i][j-1].rgbtBlue * kernal_x[1][0] + image_copy[i-1][j-1].rgbtBlue * kernal_x[0][0];
                    b_y = image_copy[i][j].rgbtBlue * kernal_y[1][1] + image_copy[i-1][j].rgbtBlue * kernal_y[0][1] + image_copy[i][j-1].rgbtBlue * kernal_y[1][0] + image_copy[i-1][j-1].rgbtBlue * kernal_y[0][0];
                    b_total = round(sqrt(b_x * b_x + b_y * b_y));

                    if (r_total > 255)
                        r_total = 255;
                    if (g_total > 255)
                        g_total = 255;
                    if (b_total > 255)
                        b_total = 255;
                }

                // In between
                else
                {
                    r_x = image_copy[i][j].rgbtRed * kernal_x[1][1] + image_copy[i][j-1].rgbtRed * kernal_x[1][0] + image_copy[i][j+1].rgbtRed * kernal_x[1][2] + image_copy[i-1][j-1].rgbtRed * kernal_x[0][0] + image_copy[i-1][j].rgbtRed * kernal_x[0][1] + image_copy[i-1][j+1].rgbtRed * kernal_x[0][2];
                    r_y = image_copy[i][j].rgbtRed * kernal_y[1][1] + image_copy[i][j-1].rgbtRed * kernal_y[1][0] + image_copy[i][j+1].rgbtRed * kernal_y[1][2] + image_copy[i-1][j-1].rgbtRed * kernal_y[0][0] + image_copy[i-1][j].rgbtRed * kernal_y[0][1] + image_copy[i-1][j+1].rgbtRed * kernal_y[0][2];
                    r_total = round(sqrt(r_x * r_x + r_y * r_y));

                    g_x = image_copy[i][j].rgbtGreen * kernal_x[1][1] + image_copy[i][j-1].rgbtGreen * kernal_x[1][0] + image_copy[i][j+1].rgbtGreen * kernal_x[1][2] + image_copy[i-1][j-1].rgbtGreen * kernal_x[0][0] + image_copy[i-1][j].rgbtGreen * kernal_x[0][1] + image_copy[i-1][j+1].rgbtGreen * kernal_x[0][2];
                    g_y = image_copy[i][j].rgbtGreen * kernal_y[1][1] + image_copy[i][j-1].rgbtGreen * kernal_y[1][0] + image_copy[i][j+1].rgbtGreen * kernal_y[1][2] + image_copy[i-1][j-1].rgbtGreen * kernal_y[0][0] + image_copy[i-1][j].rgbtGreen * kernal_y[0][1] + image_copy[i-1][j+1].rgbtGreen * kernal_y[0][2];
                    g_total = round(sqrt(g_x * g_x + g_y * g_y));

                    b_x = image_copy[i][j].rgbtBlue * kernal_x[1][1] + image_copy[i][j-1].rgbtBlue * kernal_x[1][0] + image_copy[i][j+1].rgbtBlue * kernal_x[1][2] + image_copy[i-1][j-1].rgbtBlue * kernal_x[0][0] + image_copy[i-1][j].rgbtBlue * kernal_x[0][1] + image_copy[i-1][j+1].rgbtBlue * kernal_x[0][2];
                    b_y = image_copy[i][j].rgbtBlue * kernal_y[1][1] + image_copy[i][j-1].rgbtBlue * kernal_y[1][0] + image_copy[i][j+1].rgbtBlue * kernal_y[1][2] + image_copy[i-1][j-1].rgbtBlue * kernal_y[0][0] + image_copy[i-1][j].rgbtBlue * kernal_y[0][1] + image_copy[i-1][j+1].rgbtBlue * kernal_y[0][2];
                    b_total = round(sqrt(b_x * b_x + b_y * b_y));

                    if (r_total > 255)
                        r_total = 255;
                    if (g_total > 255)
                        g_total = 255;
                    if (b_total > 255)
                        b_total = 255;
                }
            }

            else
            {
                // Left side (no corners)
                if (j == 0)
                {
                    r_x = image_copy[i][j].rgbtRed * kernal_x[1][1] + image_copy[i][j+1].rgbtRed * kernal_x[1][2] + image_copy[i-1][j].rgbtRed * kernal_x[0][1] + image_copy[i-1][j+1].rgbtRed * kernal_x[0][2] + image_copy[i+1][j].rgbtRed * kernal_x[2][1] + image_copy[i+1][j+1].rgbtRed * kernal_x[2][2];
                    r_y = image_copy[i][j].rgbtRed * kernal_y[1][1] + image_copy[i][j+1].rgbtRed * kernal_y[1][2] + image_copy[i-1][j].rgbtRed * kernal_y[0][1] + image_copy[i-1][j+1].rgbtRed * kernal_y[0][2] + image_copy[i+1][j].rgbtRed * kernal_y[2][1] + image_copy[i+1][j+1].rgbtRed * kernal_y[2][2];
                    r_total = round(sqrt(r_x * r_x + r_y * r_y));

                    g_x = image_copy[i][j].rgbtGreen * kernal_x[1][1] + image_copy[i][j+1].rgbtGreen * kernal_x[1][2] + image_copy[i-1][j].rgbtGreen * kernal_x[0][1] + image_copy[i-1][j+1].rgbtGreen * kernal_x[0][2] + image_copy[i+1][j].rgbtGreen * kernal_x[2][1] + image_copy[i+1][j+1].rgbtGreen * kernal_x[2][2];
                    g_y = image_copy[i][j].rgbtGreen * kernal_y[1][1] + image_copy[i][j+1].rgbtGreen * kernal_y[1][2] + image_copy[i-1][j].rgbtGreen * kernal_y[0][1] + image_copy[i-1][j+1].rgbtGreen * kernal_y[0][2] + image_copy[i+1][j].rgbtGreen * kernal_y[2][1] + image_copy[i+1][j+1].rgbtGreen * kernal_y[2][2];
                    g_total = round(sqrt(g_x * g_x + g_y * g_y));

                    b_x = image_copy[i][j].rgbtBlue * kernal_x[1][1] + image_copy[i][j+1].rgbtBlue * kernal_x[1][2] + image_copy[i-1][j].rgbtBlue * kernal_x[0][1] + image_copy[i-1][j+1].rgbtBlue * kernal_x[0][2] + image_copy[i+1][j].rgbtBlue * kernal_x[2][1] + image_copy[i+1][j+1].rgbtBlue * kernal_x[2][2];
                    b_y = image_copy[i][j].rgbtBlue * kernal_y[1][1] + image_copy[i][j+1].rgbtBlue * kernal_y[1][2] + image_copy[i-1][j].rgbtBlue * kernal_y[0][1] + image_copy[i-1][j+1].rgbtBlue * kernal_y[0][2] + image_copy[i+1][j].rgbtBlue * kernal_y[2][1] + image_copy[i+1][j+1].rgbtBlue * kernal_y[2][2];
                    b_total = round(sqrt(b_x * b_x + b_y * b_y));

                    if (r_total > 255)
                        r_total = 255;
                    if (g_total > 255)
                        g_total = 255;
                    if (b_total > 255)
                        b_total = 255;
                }

                // Right side (no corners)
                else if (j == width - 1)
                {
                    r_x = image_copy[i][j].rgbtRed * kernal_x[1][1] + image_copy[i][j-1].rgbtRed * kernal_x[1][0] + image_copy[i-1][j].rgbtRed * kernal_x[0][1] + image_copy[i-1][j-1].rgbtRed * kernal_x[0][0] + image_copy[i+1][j].rgbtRed * kernal_x[2][1] + image_copy[i+1][j-1].rgbtRed * kernal_x[2][0];
                    r_y = image_copy[i][j].rgbtRed * kernal_y[1][1] + image_copy[i][j-1].rgbtRed * kernal_y[1][0] + image_copy[i-1][j].rgbtRed * kernal_y[0][1] + image_copy[i-1][j-1].rgbtRed * kernal_y[0][0] + image_copy[i+1][j].rgbtRed * kernal_y[2][1] + image_copy[i+1][j-1].rgbtRed * kernal_y[2][0];
                    r_total = round(sqrt(r_x * r_x + r_y * r_y));

                    g_x = image_copy[i][j].rgbtGreen * kernal_x[1][1] + image_copy[i][j-1].rgbtGreen * kernal_x[1][0] + image_copy[i-1][j].rgbtGreen * kernal_x[0][1] + image_copy[i-1][j-1].rgbtGreen * kernal_x[0][0] + image_copy[i+1][j].rgbtGreen * kernal_x[2][1] + image_copy[i+1][j-1].rgbtGreen * kernal_x[2][0];
                    g_y = image_copy[i][j].rgbtGreen * kernal_y[1][1] + image_copy[i][j-1].rgbtGreen * kernal_y[1][0] + image_copy[i-1][j].rgbtGreen * kernal_y[0][1] + image_copy[i-1][j-1].rgbtGreen * kernal_y[0][0] + image_copy[i+1][j].rgbtGreen * kernal_y[2][1] + image_copy[i+1][j-1].rgbtGreen * kernal_y[2][0];
                    g_total = round(sqrt(g_x * g_x + g_y * g_y));

                    b_x = image_copy[i][j].rgbtBlue * kernal_x[1][1] + image_copy[i][j-1].rgbtBlue * kernal_x[1][0] + image_copy[i-1][j].rgbtBlue * kernal_x[0][1] + image_copy[i-1][j-1].rgbtBlue * kernal_x[0][0] + image_copy[i+1][j].rgbtBlue * kernal_x[2][1] + image_copy[i+1][j-1].rgbtBlue * kernal_x[2][0];
                    b_y = image_copy[i][j].rgbtBlue * kernal_y[1][1] + image_copy[i][j-1].rgbtBlue * kernal_y[1][0] + image_copy[i-1][j].rgbtBlue * kernal_y[0][1] + image_copy[i-1][j-1].rgbtBlue * kernal_y[0][0] + image_copy[i+1][j].rgbtBlue * kernal_y[2][1] + image_copy[i+1][j-1].rgbtBlue * kernal_y[2][0];
                    b_total = round(sqrt(b_x * b_x + b_y * b_y));

                    if (r_total > 255)
                        r_total = 255;
                    if (g_total > 255)
                        g_total = 255;
                    if (b_total > 255)
                        b_total = 255;
                }

                // In between
                else
                {
                    r_x = image_copy[i][j].rgbtRed * kernal_x[1][1] + image_copy[i][j-1].rgbtRed * kernal_x[1][0] + image_copy[i][j+1].rgbtRed * kernal_x[1][2] + image_copy[i-1][j-1].rgbtRed * kernal_x[0][0] + image_copy[i-1][j].rgbtRed * kernal_x[0][1] + image_copy[i-1][j+1].rgbtRed * kernal_x[0][2] + image_copy[i+1][j-1].rgbtRed * kernal_x[2][0] + image_copy[i+1][j].rgbtRed * kernal_x[2][1] + image_copy[i+1][j+1].rgbtRed * kernal_x[2][2];
                    r_y = image_copy[i][j].rgbtRed * kernal_y[1][1] + image_copy[i][j-1].rgbtRed * kernal_y[1][0] + image_copy[i][j+1].rgbtRed * kernal_y[1][2] + image_copy[i-1][j-1].rgbtRed * kernal_y[0][0] + image_copy[i-1][j].rgbtRed * kernal_y[0][1] + image_copy[i-1][j+1].rgbtRed * kernal_y[0][2] + image_copy[i+1][j-1].rgbtRed * kernal_y[2][0] + image_copy[i+1][j].rgbtRed * kernal_y[2][1] + image_copy[i+1][j+1].rgbtRed * kernal_y[2][2];
                    r_total = round(sqrt(r_x * r_x + r_y * r_y));

                    g_x = image_copy[i][j].rgbtGreen * kernal_x[1][1] + image_copy[i][j-1].rgbtGreen * kernal_x[1][0] + image_copy[i][j+1].rgbtGreen * kernal_x[1][2] + image_copy[i-1][j-1].rgbtGreen * kernal_x[0][0] + image_copy[i-1][j].rgbtGreen * kernal_x[0][1] + image_copy[i-1][j+1].rgbtGreen * kernal_x[0][2] + image_copy[i+1][j-1].rgbtGreen * kernal_x[2][0] + image_copy[i+1][j].rgbtGreen * kernal_x[2][1] + image_copy[i+1][j+1].rgbtGreen * kernal_x[2][2];
                    g_y = image_copy[i][j].rgbtGreen * kernal_y[1][1] + image_copy[i][j-1].rgbtGreen * kernal_y[1][0] + image_copy[i][j+1].rgbtGreen * kernal_y[1][2] + image_copy[i-1][j-1].rgbtGreen * kernal_y[0][0] + image_copy[i-1][j].rgbtGreen * kernal_y[0][1] + image_copy[i-1][j+1].rgbtGreen * kernal_y[0][2] + image_copy[i+1][j-1].rgbtGreen * kernal_y[2][0] + image_copy[i+1][j].rgbtGreen * kernal_y[2][1] + image_copy[i+1][j+1].rgbtGreen * kernal_y[2][2];
                    g_total = round(sqrt(g_x * g_x + g_y * g_y));

                    b_x = image_copy[i][j].rgbtBlue * kernal_x[1][1] + image_copy[i][j-1].rgbtBlue * kernal_x[1][0] + image_copy[i][j+1].rgbtBlue * kernal_x[1][2] + image_copy[i-1][j-1].rgbtBlue * kernal_x[0][0] + image_copy[i-1][j].rgbtBlue * kernal_x[0][1] + image_copy[i-1][j+1].rgbtBlue * kernal_x[0][2] + image_copy[i+1][j-1].rgbtBlue * kernal_x[2][0] + image_copy[i+1][j].rgbtBlue * kernal_x[2][1] + image_copy[i+1][j+1].rgbtBlue * kernal_x[2][2];
                    b_y = image_copy[i][j].rgbtBlue * kernal_y[1][1] + image_copy[i][j-1].rgbtBlue * kernal_y[1][0] + image_copy[i][j+1].rgbtBlue * kernal_y[1][2] + image_copy[i-1][j-1].rgbtBlue * kernal_y[0][0] + image_copy[i-1][j].rgbtBlue * kernal_y[0][1] + image_copy[i-1][j+1].rgbtBlue * kernal_y[0][2] + image_copy[i+1][j-1].rgbtBlue * kernal_y[2][0] + image_copy[i+1][j].rgbtBlue * kernal_y[2][1] + image_copy[i+1][j+1].rgbtBlue * kernal_y[2][2];
                    b_total = round(sqrt(b_x * b_x + b_y * b_y));

                    if (r_total > 255)
                        r_total = 255;
                    if (g_total > 255)
                        g_total = 255;
                    if (b_total > 255)
                        b_total = 255;
                }
            }
            image[i][j].rgbtRed = r_total;
            image[i][j].rgbtGreen = g_total;
            image[i][j].rgbtBlue = b_total;
        }
    }
    return;
}