#include <cs50.h>
#include <stdio.h>

int main(void)

{
    //declare all the variables that will be used
    int height, spaces, blocks;
      do

    {
        height = get_int("Height: \n");
        }
    while (height < 1 || height > 8);

    //set values to these variables. spaces is height - 1 because on the first line, there will be only 1 block and the rest of the line is taken up with spaces.
    spaces = height - 1;
    blocks = 1;


    for (int g = 0; g < height; g++)
    //loop through this as many times as the "height" value given
    {

        for (int j = 0; j < spaces; j++)
        //print spaces before the pyramid, starting with the initial value, equal to "height -1" as established above
        {
       printf(" ");
        }
        for (int i = 0; i < blocks; i++)
        //print the rows of blocks, starting with 1 as established above
        {
            printf("#");
        }

printf("  ");
    //add the middle section
        for (int h = 0; h < blocks; h++)
    //repeat
        {
            printf("#");
        }

        printf("\n");
        spaces--;
        blocks++;
        //new line is set, and thenb the values of spaces go down by 2 and the value of blocks goes up by one to create the pyramind shape! :)
    }

}
