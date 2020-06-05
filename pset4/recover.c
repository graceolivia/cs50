#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

//typedef uint8_t BYTE;
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //check if they put in something
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    //open file
    FILE *memoryCard = fopen(argv[1], "r");
    if (!memoryCard)
    {
        printf("File cannot be opened");
        return 2;
    }

    //making buffer
    BYTE buffer[512];
    //this will be used for naming the jpegs
    int fileCounter = 0;
    //this is the filename
    char jpegz[9];
    //this is for making the jpegs
    FILE *jpegMaker = NULL;
    

    bool firstJpegFound = false;

    for (;;)
    {
        //this is to make my 'if' statements easier to write
        bool isJpegStarter = false;

        //read into buffer
        unsigned int theBytes = fread(buffer, sizeof(BYTE), 512, memoryCard);

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            isJpegStarter = true;
        }
        //catch the first few rounds of blank card
        if (isJpegStarter == false && firstJpegFound == false)
        {
            continue;
        }
        
        if (isJpegStarter == true)
        {
            if (firstJpegFound == true)
            {
                //close last file
                fclose(jpegMaker);
                //make sure it's reset
                jpegMaker = NULL;
            }

            if (firstJpegFound == false)
            {
                //set it to true
                firstJpegFound = true;
                
            }
            sprintf(jpegz, "%03i.jpg", fileCounter);
            jpegMaker = fopen(jpegz, "w");
            fileCounter++;
            
        }
        
        fwrite(&buffer, sizeof(BYTE), theBytes, jpegMaker);
        
        if (theBytes < 512)
        {
            break;
        }
    }
    //close the jpegMaker
    fclose(jpegMaker);
    fclose(memoryCard);
    return 0;

}
