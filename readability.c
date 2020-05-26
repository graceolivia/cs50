#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void length_getter();
int letters = 0;
int words = 1;
int sentences = 0;
float l = 0;
float s = 0;
int index = 0;
float numerator = 0;

int main(void)
{

    string Text = get_string("Text: \n");
    length_getter(Text);
}

void length_getter(string stringy)
{

    for (int i = 0; i < strlen(stringy); i++)
    {
        if (stringy[i] == 32)
        {
            letters += 0;
            words += 1;
        }
        else if ((stringy[i] >= 65 && stringy[i] <= 90) || (stringy[i] >= 97 && stringy[i] <= 122))
        {
            letters += 1;
            words += 0;
        }

        else if (stringy[i] == 33 || stringy[i] == 46 || stringy[i] == 63)
        {
            sentences += 1;
        }


    }

//get L and S

//get the index where L is the average number of letters per 100 words in the text,
// and S is the average number of sentences per 100 words in the text.

    numerator = words * .01;

    l = (letters / numerator);
    s = (sentences / numerator);

    index = roundf(0.0588 * l - 0.296 * s - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }




//printf("Letters: %i \n", letters);
//printf("Words: %i \n", words);
//printf("Sentences: %i \n", sentences);
//printf("num: %f \n", numerator);
//printf("l: %f \n", l);
//printf("s: %f \n", s);

}
