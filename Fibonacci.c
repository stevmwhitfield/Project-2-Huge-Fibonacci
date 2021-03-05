#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Fibonacci.h"

void printHuge(HugeInteger *p) {
	int i;
	
	if (p == NULL || p->digits == NULL)
	{
		printf("(null pointer)\n");
		return;
	}
	
	for (i = 0; i < p->length; i++)
		printf("%d ", p->digits[i]);
	printf("\n");
}

HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q) {
    // if p or q are null, return null
    if (p == NULL || q == NULL) return NULL;

    // tlen is equal to the length of the larger HugeInteger + 1
    int tlen = 0;
    if (p->length > q->length || p->length == q->length) tlen = p->length + 1;
    else tlen = q->length + 1;

    // allocate memory for a temporary HugeInteger and check for null pointers
    HugeInteger *temp = (HugeInteger*) malloc(sizeof(HugeInteger));
    temp->length = tlen;
    temp->digits = (int*) calloc(temp->length, sizeof(int));
    if (temp == NULL || temp->digits == NULL) {
        free(temp->digits);
        free(temp);
        return NULL;
    }

    // add p to temp
    int i;
    for (i = 0; i < p->length; i++) {
        temp->digits[i] += p->digits[i];
    }

    // add q to temp
    int sum = 0, carry = 0;
    for (i = 0; i < q->length; i++) {
        if (i < p->length) {
            sum = q->digits[i] + p->digits[i];
        }

        int add = q->digits[i];

        if (sum > 9) {
            add -= 10;
        }

        temp->digits[i] += add + carry;
        carry = 0;

        if (sum > 9) {
            carry = 1;
        }
        sum = 0;
    }

    // remove trailing zeroes
    int slen = temp->length;
    while (temp->digits[slen-1] == 0) {
        slen--;
    }

    // allocate memory for HugeInteger result and check for null pointers
    HugeInteger *result = (HugeInteger*) malloc(sizeof(HugeInteger));
    result->length = slen;
    result->digits = (int*) calloc(result->length, sizeof(int));
    if (result == NULL || result->digits == NULL) {
        free(result->digits);
        free(result);
        return NULL;
    }

    // add temp to result to get final result
    for (i = 0; i < result->length; i++) {
        result->digits[i] = temp->digits[i];
    }

    return result;

}

HugeInteger *hugeDestroyer(HugeInteger *p) {
    if (p) {
        free(p->digits); // free int* digits
        free(p); // free HugeInteger* p
    }
    return NULL;
}

HugeInteger *parseString(char *str) {
    HugeInteger *hInt = (HugeInteger*) malloc(sizeof(HugeInteger)); // allocate HugeInteger

    if (str == NULL || hInt == NULL) {
        free(hInt);
        return NULL;
    }

    int slen = strlen(str); // get length of string
    hInt->digits = (int*) malloc(sizeof(int) * slen); // allocate int* digits
    hInt->length = slen; 

    if (strcmp(str, "") == 0) str = "0"; // if string is empty, then assign "0"

    int i, j;
    for (i = 0, j = slen - 1; i < slen; i++, j--) {
        hInt->digits[i] = str[j] - '0'; // for every char in string, convert to int and assign to digits
    }

    return hInt;
}

HugeInteger *parseInt(unsigned int n) {
    HugeInteger *hInt = (HugeInteger*) malloc(sizeof(HugeInteger)); // allocate HugeInteger
    
    if (hInt == NULL) {
        free(hInt);
        return NULL;
    }

    if (n == 0) {
        hInt->digits = (int*) malloc(sizeof(int));
        hInt->digits[0] = 0;
        hInt->length = 1;
    }
    else {
        int ilen = 0;
        unsigned int temp = n;
        while (temp > 0) { // while temp has digits, add to ilen (length of n)
            temp /= 10;
            ilen++;
        }
        hInt->digits = (int*) malloc(sizeof(int) * ilen); // allocate int* digits
        hInt->length = ilen;

        int i = 0;
        while (n > 0) { // while n has digits, assign them to hInt->digits
            hInt->digits[i++] = n % 10;
            n /= 10;
        }
    }

    return hInt;
}

unsigned int *toUnsignedInt(HugeInteger *p) {
    // check if input is null
    if (p == NULL) {
        free(p);
        return NULL;
    }

    // set HugeInteger for UINT_MAX
    HugeInteger *hugeUINT = parseInt(UINT_MAX);

    // allocate unsigned int
    unsigned int *uInt = (unsigned int*) malloc(sizeof(unsigned int));

    int i, j;

    // if input is longer than UINT, then return null
    if (uInt == NULL || p->length > hugeUINT->length) {
        free(hugeUINT);
        free(uInt);
        return NULL;
    }

    // if input is the same length but greater than UINT, then return null
    if (p->length == hugeUINT->length) {
        for (i = p->length-1 ; i >= 0; i--) {
            if (p->digits[i] > hugeUINT->digits[i]) return NULL;
          if (p->digits[i] < hugeUINT->digits[i]) break;
        } 
    }

    // convert HugeInteger to unsigned int
    unsigned int temp = 0;
    for (i = 0, j = p->length - 1; i < p->length; i++, j--) {
      temp = temp * 10 + p->digits[j];
    }

    // assign result to pointer and return
    uInt = &temp;
    return uInt;
}

HugeInteger *fib(int n) {
    //printf("---------------\n    fib    \n---------------\n");
    HugeInteger *fibResult;
    //HugeInteger *fibResult = (HugeInteger*) malloc(sizeof(HugeInteger));
    HugeInteger *h1 = (HugeInteger*) malloc(sizeof(HugeInteger));
    HugeInteger *h2 = (HugeInteger*) malloc(sizeof(HugeInteger));
    if (h1 == NULL || h2 == NULL) { 
        printf("HI malloc failed\n");
        //free(fibResult);
        free(h1);
        free(h2);
        return NULL;
    }
    //fibResult->digits = (int*) malloc(sizeof(int));
    h1->digits = (int*) malloc(sizeof(int));
    h2->digits = (int*) malloc(sizeof(int));
    /*if (fibResult->digits == NULL) {
        printf("int malloc failed - fib\n");
        free(fibResult->digits);
        return NULL;
    }*/
    if (h1->digits == NULL) {
        printf("int malloc failed - h1\n");
        free(h1->digits);
        return NULL;
    }
    if (h2->digits == NULL) {
        printf("int malloc failed - h2\n");
        free(h2->digits);
        return NULL;
    }

    h1->digits[0] = 0;
    h2->digits[0] = 1;

    h1->length = 1;
    h2->length = 1;
    //fibResult->length = 1;

    int i;
    if (n < 1) {
        fibResult = (HugeInteger*) malloc(sizeof(HugeInteger));
        fibResult->digits = (int*) malloc(sizeof(int));
        if (fibResult == NULL || fibResult->digits == NULL) {
            free(fibResult->digits);
            free(fibResult);
            return NULL;
        }
        fibResult->length = 1;
        fibResult->digits[0] = 0;
    }
    else if (n == 1) {
        fibResult = (HugeInteger*) malloc(sizeof(HugeInteger));
        fibResult->digits = (int*) malloc(sizeof(int));
        if (fibResult == NULL || fibResult->digits == NULL) {
            free(fibResult->digits);
            free(fibResult);
            return NULL;
        }
        fibResult->length = 1;
        fibResult->digits[0] = 1;
    }
    else {
        fibResult = (HugeInteger*) malloc(sizeof(HugeInteger));
        fibResult->digits = (int*) malloc(sizeof(int));
        for (i = 2; i <= n; i++) {
            //printf("fib i: %d\n", i);
            //printf("fibResult length: %d\n", fibResult->length);
            //printf("h1 length: %d\n", h1->length);
            //printf("h2 length: %d\n", h2->length);
            //fibResult->digits = (int*) realloc(fibResult->digits, sizeof(int) * (hugeAdd(h1,h2)->length+1));
            //fibResult->length = hugeAdd(h1,h2)->length;
            fibResult = hugeAdd(h1, h2);

            //h1->digits = (int*) realloc(h1, h2->length);
           // h1->length = h2->length;
            h1 = h2;

           // h2->digits = (int*) realloc(h2, fibResult->length);
           // h2->length = fibResult->length;
            h2 = fibResult;
            //printf("fibResult length: %d\n", fibResult->length);
            //printf("h1 length: %d\n", h1->length);
            //printf("h2 length: %d\n", h2->length);
        }
        
    }
    return fibResult;
}

double difficultyRating(void) {
    return 2.0;
}

double hoursSpent(void) {
    return 12;
}