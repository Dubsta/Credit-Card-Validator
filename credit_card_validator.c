// Asks user for a creditcard number.
// The number will be verified by checksum and the type of card will be printed.

#include <stdio.h>
#include <cs50.h> //GetLongLong()
#include <math.h> //pow()

int countLongLong(long long num);
int checker(long long ccnum);

/*********************
main
*********************/

// main will always return 0, May print either INVALID, VISA, MASTERCARD, AMEX
int main(void)
{
  // get the creditcard number from user
  printf("Number:");
  long long ccnum = GetLongLong();

  // initial check of length
  int cclength = countLongLong(ccnum);
  if (cclength > 16 || cclength < 13) {
    printf("INVALID\n");
    return 0;
  }
    
  // find the type of card --> checksum valiadation
  if (checker(ccnum)) {
    int dig1 = ccnum / pow(10, (cclength - 1));

    // Check if Mastercard
    if (dig1 == 5 && cclength == 16) {
      int dig2 = ccnum / (pow(10, 14));
      dig2 = dig2 % 10;
      if (dig2 <= 5 && dig2 >= 1) {
        printf("MASTERCARD\n");
        return 0;
      }
      else {
        printf("INVALID\n");
        return 0;
      }
    }

    // Check if Amex
    if (dig1 == 3 && cclength == 15) {
      int dig2 = ccnum / (pow(10, 13));
      dig2 = dig2 % 10;
      if (dig2 == 4 || dig2 == 7) {
        printf("AMEX\n");
        return 0;
      }
      else {
        printf("INVALID\n");
        return 0;
      }
    }

    // Check if Visa
    if (dig1 == 4 && (cclength == 13 || cclength == 16)) {
      printf("VISA\n");
      return 0;
    }

    // Not a matching card type
    else {
      printf("INVALID\n");
      return 0;
    }
  }
  //Failed checksum
  else {
    printf("INVALID\n");
    return 0;
  }
} 
//End of main


/*********************
function definitions
*********************/

// Count the numer of digits in a long long
int countLongLong(long long num) {
  int count = 0;
  while(num) {
    num /= 10;
    count++;
  }
    return count;
}

// Check the checksum. Returns 1 for true, 0 for false
int checker(long long ccnum) {
  int ccLength = countLongLong(ccnum);
  int valid = 0;
  int sumOf2nd = 0;
  int sumOfOther = 0;
  // put every second number into array starting from 2nd last
  long long tempNum = ccnum;
  tempNum /= 10;
  int digits[10];
  int indexcount = 0;
  for (int i = 0; i < (countLongLong(tempNum)); i += 2) {
    long long otherDigit = tempNum / (pow(10, i));
    otherDigit = otherDigit % 10;
    digits[indexcount] = otherDigit;
    indexcount++;
  }
  // mulitply each by 2
  for (int i = 0; i < indexcount; i++) {
    digits[i] *= 2;
  }
  // add the digits (not number) to find sumOf2nd
  for (int i = 0; i < indexcount; i++) {
    if (digits[i] > 9) {
      sumOf2nd++;
      sumOf2nd += (digits[i] % 10);
    }
    else {
      sumOf2nd += digits[i];
    }
  }
  // find sumOfOther
  for (int i = 0; i < (ccLength); i += 2) {
    long long otherDigit = ccnum / (pow(10, i));
    otherDigit = otherDigit % 10;
    sumOfOther += otherDigit;
  }
  // put it all together
  if ((sumOf2nd + sumOfOther) % 10 == 0) {
      valid = 1;
  }
  return valid;
}