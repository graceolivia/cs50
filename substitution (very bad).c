#include <cs50.h>
#include <stdio.h>
#include <string.h>

string key = 0;
int length = 0;
int main(int argc, string argv[])
{
    //if there isn't one arguement passed after the program, end program
    if (argc == 1 || argc > 2)
    {
        return 1;
    }
//if the key is invalid, print error message and end program:
    //get the length of the key
    key = argv[1];
    length = strlen(key);
    //check for length for 26 - if it's not 26, print error message and return 1
    if (length > 26 || length < 26)
    {
        printf("fail %i \n", length);
        return 1;
    }

    //check for non-alphabetic characters, print error message and return 1 if any are found
    for (int i = 0; i < length; i++)
    {
        if ((key[i] < 65 || key[i] > 90) && (key[i] < 97 || key[i] > 122))
        {
            printf("better fail %i \n", length);
            return 1;
        }
    }

    //check for repeats, print error message and return 1 if any are found
    //j will represent the character that is getting checked against everything else
    for (int j = 0; j < length; j++)
    {
        //k will represent the rest of the array of characters
        for (int k = 0; k < (length); k++)
        {
            //ignore if the current character being checked is being checked against itself
            if(k == j)
            {
            }

            else if (key[j] == key[k])
            {
                printf("better fail %i \n", length);
                return 1;
            }
        }
    }

    //this is just a checker to be deleted
    printf("good\n");

    //turn cipher text to all lowercase... because in my opinion that will be easier.
    for (int m = 0; m < 26; m++)
    {
        if (key[m] < 97)
        {
            key[m] = (key[m] + 32);
        }
    }

    //get plaintext from user
    string secretMessage = get_string("plaintext: ");


    //convert plaintext to ciphertext
    //interate through secretMessage
    for (int l = 0; l < strlen(secretMessage); l++)
    {
        //if the character isn't a letter, leave it.
        if ((secretMessage[l] < 65 || secretMessage[l] > 90) && (secretMessage[l] < 97 || secretMessage[l] > 122))
        {
        }
        //switch out the characters. The only way I can think to do this is by going through letter by letter.
        //A
        else if (secretMessage[l] == 65)
        {
            secretMessage[l] = (key[0] - 32);
        }
        else if (secretMessage[l] == 97)
        {
            secretMessage[l] = key[0];
        }
        //B
        else if (secretMessage[l] == 66)
        {
            secretMessage[l] = (key[1] - 32);
        }
        else if (secretMessage[l] == 98)
        {
            secretMessage[l] = key[1];
        }
        //C
        else if (secretMessage[l] == 67)
        {
            secretMessage[l] = (key[2] - 32);
        }
        else if (secretMessage[l] == 99)
        {
            secretMessage[l] = key[2];
        }
        //D
        else if (secretMessage[l] == 68)
        {
            secretMessage[l] = (key[3] - 32);
        }
        else if (secretMessage[l] == 100)
        {
            secretMessage[l] = key[3];
        }
        //E
        else if (secretMessage[l] == 69)
        {
            secretMessage[l] = (key[4] - 32);
        }
        else if (secretMessage[l] == 101)
        {
            secretMessage[l] = key[4];
        }
        //F
        else if (secretMessage[l] == 70)
        {
            secretMessage[l] = (key[5] - 32);
        }
        else if (secretMessage[l] == 102)
        {
            secretMessage[l] = key[5];
        }
        //G
        else if (secretMessage[l] == 71)
        {
            secretMessage[l] = (key[6] - 32);
        }
        else if (secretMessage[l] == 103)
        {
            secretMessage[l] = key[6];
        }
        //H
        else if (secretMessage[l] == 72)
        {
            secretMessage[l] = (key[7] - 32);
        }
        else if (secretMessage[l] == 104)
        {
            secretMessage[l] = key[7];
        }
        //I
        else if (secretMessage[l] == 73)
        {
            secretMessage[l] = (key[8] - 32);
        }
        else if (secretMessage[l] == 105)
        {
            secretMessage[l] = key[8];
        }
        //J
        else if (secretMessage[l] == 74)
        {
            secretMessage[l] = (key[9] - 32);
        }
        else if (secretMessage[l] == 106)
        {
            secretMessage[l] = key[9];
        }
        //K
        else if (secretMessage[l] == 75)
        {
            secretMessage[l] = (key[10] - 32);
        }
        else if (secretMessage[l] == 107)
        {
            secretMessage[l] = key[10];
        }
        //L
        else if (secretMessage[l] == 76)
        {
            secretMessage[l] = (key[11] - 32);
        }
        else if (secretMessage[l] == 108)
        {
            secretMessage[l] = key[11];
        }
        //M
        else if (secretMessage[l] == 77)
        {
            secretMessage[l] = (key[12] - 32);
        }
        else if (secretMessage[l] == 109)
        {
            secretMessage[l] = key[12];
        }
        //N
        else if (secretMessage[l] == 78)
        {
            secretMessage[l] = (key[13] - 32);
        }
        else if (secretMessage[l] == 110)
        {
            secretMessage[l] = key[13];
        }
        //O
        else if (secretMessage[l] == 79)
        {
            secretMessage[l] = (key[14] - 32);
        }
        else if (secretMessage[l] == 111)
        {
            secretMessage[l] = key[14];
        }
        //P
        else if (secretMessage[l] == 80)
        {
            secretMessage[l] = (key[15] - 32);
        }
        else if (secretMessage[l] == 112)
        {
            secretMessage[l] = key[15];
        }
        //Q
        else if (secretMessage[l] == 81)
        {
            secretMessage[l] = (key[16] - 32);
        }
        else if (secretMessage[l] == 113)
        {
            secretMessage[l] = key[16];
        }
        //R
        else if (secretMessage[l] == 82)
        {
            secretMessage[l] = (key[17] - 32);
        }
        else if (secretMessage[l] == 114)
        {
            secretMessage[l] = key[17];
        }
        //S
        else if (secretMessage[l] == 83)
        {
            secretMessage[l] = (key[18] - 32);
        }
        else if (secretMessage[l] == 115)
        {
            secretMessage[l] = key[18];
        }
        //T
        else if (secretMessage[l] == 84)
        {
            secretMessage[l] = (key[19] - 32);
        }
        else if (secretMessage[l] == 116)
        {
            secretMessage[l] = key[19];
        }
        //U
        else if (secretMessage[l] == 85)
        {
            secretMessage[l] = (key[20] - 32);
        }
        else if (secretMessage[l] == 117)
        {
            secretMessage[l] = key[20];
        }
        //V
        else if (secretMessage[l] == 86)
        {
            secretMessage[l] = (key[21] - 32);
        }
        else if (secretMessage[l] == 118)
        {
            secretMessage[l] = key[21];
        }
        //W
        else if (secretMessage[l] == 87)
        {
            secretMessage[l] = (key[22] - 32);
        }
        else if (secretMessage[l] == 119)
        {
            secretMessage[l] = key[22];
        }
        //X
        else if (secretMessage[l] == 88)
        {
            secretMessage[l] = (key[23] - 32);
        }
        else if (secretMessage[l] == 120)
        {
            secretMessage[l] = key[23];
        }
        //Y
        else if (secretMessage[l] == 89)
        {
            secretMessage[l] = (key[24] - 32);
        }
        else if (secretMessage[l] == 121)
        {
            secretMessage[l] = key[24];
        }
        //Z
        else if (secretMessage[l] == 90)
        {
            secretMessage[l] = (key[25] - 32);
        }
        else if (secretMessage[l] == 122)
        {
            secretMessage[l] = key[25];
        }

    }



    //print ciphertext
    printf("ciphertext: %s\n", secretMessage);

}
