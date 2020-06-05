#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int grey = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            grey = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)*.3333333);
            image[i][j].rgbtRed = grey;
            image[i][j].rgbtGreen = grey;
            image[i][j].rgbtBlue = grey;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //figure out
    int switchWidth = 0;
    if (width%2 == 0)
    {
       switchWidth = width/2;
    }
    else
    {
        switchWidth = ((width - 1)/2);
    }
    for (int i = 0; i < height; i++)
    {

        int secondPixel = width - 1;
        for (int j = 0; j < switchWidth; j++)
        {
            RGBTRIPLE temp;
            temp = image[i][j];
            image[i][j] = image[i][secondPixel];
            image[i][secondPixel] = temp;

            secondPixel--;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //make copy of image
    RGBTRIPLE originalImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalImage[i][j] = image[i][j];
        }

    }



    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
        float numberOfPixelsToDivideBy = 0;
        //this has to be float or else it won't be accurate
        int newRed = 0;
        int newGreen = 0;
        int newBlue = 0;

        //add first pixel color values, which will happen in every case

        newRed += originalImage[i][j].rgbtRed;
        newGreen += originalImage[i][j].rgbtGreen;
        newBlue += originalImage[i][j].rgbtBlue;
        numberOfPixelsToDivideBy++;

        //skip or add upper left pixel
        if (i != 0 && j != 0)
        {
            newRed += originalImage[i - 1][j - 1].rgbtRed;
            newGreen += originalImage[i - 1][j - 1].rgbtGreen;
            newBlue += originalImage[i - 1][j - 1].rgbtBlue;
            numberOfPixelsToDivideBy++;
        }
        //skip or add upper right pixel
        if (i != 0 && j != width - 1)
        {
            newRed += originalImage[i - 1][j + 1].rgbtRed;
            newGreen += originalImage[i - 1][j + 1].rgbtGreen;
            newBlue += originalImage[i - 1][j + 1].rgbtBlue;
            numberOfPixelsToDivideBy++;
        }
        //skip or add pixel one row above
        if (i != 0)
        {
            newRed += originalImage[i - 1][j].rgbtRed;
            newGreen += originalImage[i - 1][j].rgbtGreen;
            newBlue += originalImage[i - 1][j].rgbtBlue;
            numberOfPixelsToDivideBy++;
        }
        //if NOT left edge, add pixel to left
        if (j != 0)
        {
            newRed += originalImage[i][j - 1].rgbtRed;
            newGreen += originalImage[i][j - 1].rgbtGreen;
            newBlue += originalImage[i][j - 1].rgbtBlue;
            numberOfPixelsToDivideBy++;
        }
        //if NOT right edge, add pixel to right
        if (j != width - 1)
        {
            newRed += originalImage[i][j + 1].rgbtRed;
            newGreen += originalImage[i][j + 1].rgbtGreen;
            newBlue += originalImage[i][j + 1].rgbtBlue;
            numberOfPixelsToDivideBy++;
        }
        //skip or add lower left pixel
        if (i != height - 1 && j != 0)
        {
            newRed += originalImage[i + 1][j - 1].rgbtRed;
            newGreen += originalImage[i + 1][j - 1].rgbtGreen;
            newBlue += originalImage[i + 1][j - 1].rgbtBlue;
            numberOfPixelsToDivideBy++;
        }
        //skip or add lower right pixel
        if (i != height - 1 && j != width - 1)
        {
            newRed += originalImage[i + 1][j + 1].rgbtRed;
            newGreen += originalImage[i + 1][j + 1].rgbtGreen;
            newBlue += originalImage[i + 1][j + 1].rgbtBlue;
            numberOfPixelsToDivideBy++;
        }
        //if NOT bottom edge, add pixel below
        if (i != height - 1)
        {
            newRed += originalImage[i + 1][j].rgbtRed;
            newGreen += originalImage[i + 1][j].rgbtGreen;
            newBlue += originalImage[i + 1][j].rgbtBlue;
            numberOfPixelsToDivideBy++;
        }

        //calculate the new values
        image[i][j].rgbtRed = round(newRed/numberOfPixelsToDivideBy);
        image[i][j].rgbtGreen = round(newGreen/numberOfPixelsToDivideBy);
        image[i][j].rgbtBlue = round(newBlue/numberOfPixelsToDivideBy);

        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    //make copy of image
    RGBTRIPLE originalImage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalImage[i][j] = image[i][j];
        }

    }
    //create the arrays
    int Gx[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1};
    int Gy[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
        //once again, we make the values
        float gxRed = 0;
        float gxGreen = 0;
        float gxBlue = 0;
        float gyRed = 0;
        float gyGreen = 0;
        float gyBlue = 0;
        //these will be the final values
        int edRed = 0;
        int edGreen = 0;
        int edBlue = 0;
        //num will be the counter that will go through both Gx and Gy
        int num = 0;

        //ugh something goes here for the formula
        //something like:
        //need to figure out how to iterate through Gx + Gy, iterate through image pixels, and more all at same time

        for (int a = -1; a < 2; a++)
        {
            for (int b = -1; b < 2; b++)
            {

        if (i + a < 0 || i + a > height - 1)
        {
           num++;
            //printf("%i ", num);
            continue;
        }

        if (j + b < 0 || j + b > width - 1)
        {
           num++;
           // printf("%i ", num);
            continue;
        }

        gxRed += (originalImage[i + a][j + b].rgbtRed * Gx[num]);
        gxGreen += (originalImage[i + a][j + b].rgbtGreen * Gx[num]);
        gxBlue += (originalImage[i + a][j + b].rgbtBlue * Gx[num]);

        gyRed += (originalImage[i + a][j + b].rgbtRed * Gy[num]);
        gyGreen += (originalImage[i + a][j + b].rgbtGreen * Gy[num]);
        gyBlue += (originalImage[i + a][j + b].rgbtBlue * Gy[num]);
        num++;
        //printf("%i ", num);
            }
        }

        edRed = round(sqrt((gxRed * gxRed) + (gyRed * gyRed)));
        edGreen = round(sqrt((gxGreen * gxGreen) + (gyGreen * gyGreen)));
        edBlue = round(sqrt((gxBlue * gxBlue) + (gyBlue * gyBlue)));

        //asigning values in the end
        if (edRed > 255)
        {
            edRed = 255;
        }

        if (edGreen > 255)
        {
            edGreen = 255;
        }
        if (edBlue > 255)
        {
            edBlue = 255;
        }

        image[i][j].rgbtRed = edRed;
        image[i][j].rgbtGreen = edGreen;
        image[i][j].rgbtBlue = edBlue;
        }
        }
            return;
    }


