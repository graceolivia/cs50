#include <cs50.h>
#include <stdio.h>
#include <math.h>

//declare global variables:
//the credit card number you put in
long creditcard;
//the array of a credit card
int creditCardNumberLength;
long creditArray [16];


//declare my new functions at the top
void lengthchecker();
void digitgetter();
void cardchecker();
void validitychecker();

//main function
int main(void)
{


    creditcard = get_long("Enter Credit Card Number: \n");
    lengthchecker(creditcard);

}

//get the number and  check if it's a valid length
void lengthchecker(long length)
{
    if (length < 100000000000 || length > 9999999999999999)
    {
        printf("INVALID\n");
        return;
    }
    else if (length >= 1000000000000000)
    {
        creditCardNumberLength = 16;
    }

    else if (length >= 100000000000000)
    {
        creditCardNumberLength = 15;
    }
    else if (length >= 10000000000000)
    {
        creditCardNumberLength = 14;
    }

    else if (length >= 1000000000000)
    {
        creditCardNumberLength = 13;
    }
//go on to turn it into array
    digitgetter(creditcard);
}


//get the digits of the card
void digitgetter(long digits)
{

    long mod = 100;
    //get the first digit
    long a = digits % 10;
    creditArray[(creditCardNumberLength - 1)] = a;

    long remain = a;
    //get all the digits
    for (int i = (creditCardNumberLength - 2); i >= 0; i--)
    {

        long b = (digits % mod - remain) / (mod / 10);
        remain = digits % mod;
        creditArray[i] = b;
        mod = mod * 10;

        //printf("%li ", b);
        //printf("remainder : %li", remain);
        //print("\n");


    }


//print out the array to make sure it's working correctly
// for(int loop = 0; loop <= (creditCardNumberLength - 1); loop++)
//  printf("%ld ", creditArray[loop]);

//go on to finding the credit card type

    validitychecker(creditcard);
}

//do that validity-checking math problems
void validitychecker(validity)
{

    int firsthalf = 0;
    int secondhalf = 0;
    int sum = 0;
    int boop = 0;
//get every other digit, starting with the number's second-to-last digit

    for (int i = (creditCardNumberLength - 2); i >= 0; i -= 2)
    {
        boop = (creditArray[i]);
        //printf("%i ", (boop*2));

        if ((creditArray[i] * 2) > 9)
        {
            firsthalf += (creditArray[i] * 2) % 10;
            firsthalf += ((creditArray[i] * 2) - (creditArray[i] * 2) % 10) / 10;
        }
        else
        {
            firsthalf += (creditArray[i] * 2);
        }

    }
//printf("Here is the first half: %i \n", firsthalf);

//do the second half
    for (int i = (creditCardNumberLength - 1); i >= 0; i -= 2)
    {

        secondhalf += (creditArray[i]);
        boop = (creditArray[i]);
        //printf("%i ", (boop));
    }
//printf("Here is the second half: %i \n", secondhalf);
    sum = firsthalf + secondhalf;
//printf("Here is the sum: %i \n", sum);



    if (sum % 10 == 0)
    {
        cardchecker(creditcard);
    }
    else
    {
        printf("INVALID\n");
        return;
    };



//here will check if numbers are valid
//if firsthalf + secondhalf = last digit is 0, go on to cardchecker, otherwise, return invalid


};


//find out if the card is a amex/visa/mastercard
void cardchecker(long arr[])
{
    if (creditArray[0] == 3 && (creditArray[1] == 4 || creditArray[1] == 7))
    {
        printf("AMEX\n");
    }
    else if (creditArray[0] == 5 && (creditArray[1] > 0 &&  creditArray[1] < 6))
    {
        printf("MASTERCARD\n");
    }
    else if (creditArray[0] == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
};
