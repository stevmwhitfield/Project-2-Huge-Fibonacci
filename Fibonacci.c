#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Fibonacci.h"

HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q) {
    //printf("-------------------\n      Huge Add      \n-------------------\n");
    if (p == NULL || q == NULL) return NULL; // return NULL if p or q are NULL

    HugeInteger *result = (HugeInteger*) malloc(sizeof(HugeInteger)); // allocate dynamic HugeInteger
    if (result == NULL) {
        free(result);
        return NULL;
    }

    int i; // declare iterator

    if (p->length > q->length) {
        //printf("p is greater than q\n");
        //printf("q size: %d\np size: %d\n", q->length, p->length);
		// create temp int array
		int temp_size = p->length + 1;
		int *temp = (int*) malloc(sizeof(int) * temp_size);

		// if temp is null, then free it and return null
        if (temp == NULL) {
            //printf("temp is null\n");
            free(temp);
            free(result);
            return NULL;
        }

		// init temp and add larger HugeInteger
        for (i = 0; i < temp_size; i++) {
            temp[i] = 0;
        }
        for (i = 0; i < temp_size - 1; i++) {
            temp[i] += p->digits[i];
        }
        //printf("init temp success\n");
		// add smaller HugeInteger
        for (i = 0; i < q->length; i++) {
            int add = p->digits[i] + q->digits[i]; 
            if (add < 10) {
                temp[i] = add;
            }
            else {
                if (i > 0 && (p->digits[i-1] + q->digits[i-1]) > 9) {
                    //printf("NEW CASE\n");
                    add = temp[i] + p->digits[i];
                }
                temp[i] = add - 10; 
                temp[i + 1] += 1; 
            }
        }
		//printf("added smaller huge int\n");
		// set new int array without extra zeroes
		if (temp[temp_size - 1] != 0) {
            result->length = temp_size;
        }
        else {
            result->length = temp_size - 1;
        }
        //printf("temp size: %d\n", temp_size);
        //printf("result length: %d\n", result->length);
        while (temp[result->length - 1] == 0) {
            //printf("temp value[%d]: %d\n", result->length - 1, temp[result->length - 1]);
            result->length -= 1;
        }
		//printf("trimmed result length\n");
		result->digits = (int*) malloc(sizeof(int) * result->length);
		if (result->digits == NULL) {
            //printf("result digits is null\n");
			free(result->digits);
			free(result);
            free(temp);
			return NULL;
		}
		
		for (i = 0; i < result->length; i++) {
			result->digits[i] = temp[i];
		}
        //printf("added values to result\n");
		free(temp);
    }
    else {
        //printf("q is greater than p\n");
		// create temp int array
		int temp_size = q->length + 1;
        //printf("q size: %d\np size: %d\n", q->length, p->length);
        //printf("temp size: %d\n", temp_size);
		int *temp = (int*) malloc(sizeof(int) * temp_size);
        
        // if temp is null, then free it and return null
        if (temp == NULL) {
            //printf("temp is null\n");
            free(temp);
            free(result);
            return NULL;
        }

        // init temp and add larger HugeInteger
        for (i = 0; i < temp_size; i++) {
            temp[i] = 0;
        }
        for (i = 0; i < temp_size - 1; i++) {
            temp[i] += q->digits[i];
        }
        //printf("init temp success\n");
        // add smaller HugeInteger
        for (i = 0; i < p->length; i++) {
            //printf("p: %d\nq: %d\n", p->digits[i], q->digits[i]);
            int add = p->digits[i] + q->digits[i];
            //printf("add value: %d\n", add); 
            if (add < 10) {
                //printf("before add - temp[%d]: %d\n", i, temp[i]);
                temp[i] = add;
                //printf("after add  - temp[%d]: %d\n", i, temp[i]);
            }
            else {
                if (i > 0 && (p->digits[i-1] + q->digits[i-1]) > 9) {
                    //printf("NEW CASE\n");
                    add = temp[i] + p->digits[i];
                }
                //printf("before add - temp[%d]: %d\n", i, temp[i]);
                temp[i] = add - 10; 
                //printf("after add  - temp[%d]: %d\n", i, temp[i]);
                //printf("before add - temp[%d]: %d\n", i + 1, temp[i + 1]);
                temp[i + 1] += 1;
                //printf("after add  - temp[%d]: %d\n", i + 1, temp[i + 1]);
            }
        }
		//printf("added smaller huge int\n");
        //printf("temp size: %d\n", temp_size);
		// set new int array without extra zeroes
		if (temp[temp_size - 1] != 0) {
            result->length = temp_size;
        }
        else {
            result->length = temp_size - 1;
        }
        //printf("temp size: %d\n", temp_size);
        //printf("result length: %d\n", result->length);
		while (temp[result->length - 1] == 0) {
            //printf("temp value[%d]: %d\n", result->length - 1, temp[result->length - 1]);
			result->length -= 1;
		}
		//printf("trimmed result length\nnew result length: %d\n", result->length);
		result->digits = (int*) malloc(sizeof(int) * result->length);
		if (result->digits == NULL) {
            //printf("result digits is null\n");
			free(result->digits);
			free(result);
            free(temp);
			return NULL;
		}
		
		for (i = 0; i < result->length; i++) {
			result->digits[i] = temp[i];
		}
        //printf("added values to result\n");
		free(temp);
    }
    //printf("ready to return result\n");
    //printf("--------------------\nResult: ");
    //for (i = 0; i < result->length; i++) {
    //    printf("%d", result->digits[i]);
    //}
    //printf("\n--------------------\n");
    return result;
}

/*HugeInteger *hugeAdd(HugeInteger *p, HugeInteger *q) {
    if (p == NULL || q == NULL) return NULL; // return NULL if p or q are NULL

    HugeInteger *result = (HugeInteger*) malloc(sizeof(HugeInteger)); // allocate dynamic HugeInteger
    if (result == NULL) {
        free(result);
        return NULL;
    }

    if (p->length > q->length) {
        result->length = p->length + 1;
    }
    else {
        result->length = q->length + 1;
    }

    int i; // declare iterator

    if (p->length > q->length) {

        result->digits = (int*) malloc(sizeof(int) * (result->length)); // allocate dynamic int array

        if (result->digits == NULL) {
            free(result->digits);
            free(result);
            return NULL;
        }

        for (i = 0; i < result->length; i++) {
            result->digits[i] = 0;
        }

        for (i = 0; i < p->length; i++) { // initialize array
            result->digits[i] += p->digits[i];
            //result->digits[p->length - 1] = 0;
        }
        
        for (i = 0; i < q->length; i++) {
            int add = p->digits[i] + q->digits[i]; 
            if (add < 10) {
                result->digits[i] = add;
            }
            else {
                result->digits[i] = add - 10; 
                result->digits[i + 1] += 1; 
            }
        }
    }
    else {

        result->digits = (int*) malloc(sizeof(int) * (result->length)); // allocate dynamic int array
        
        if (result->digits == NULL) {
            free(result->digits);
            free(result);
            return NULL;
        }

        for (i = 0; i < result->length; i++) {
            result->digits[i] = 0;
        }

        for (i = 0; i < q->length; i++) { // initialize array
            result->digits[i] += q->digits[i];
            //result->digits[q->length - 1] = 0;
        }

        for (i = 0; i < p->length; i++) {
            int add = p->digits[i] + q->digits[i]; 
            if (add < 10) {
                result->digits[i] = add;
            }
            else {
                result->digits[i] = add - 10; 
                result->digits[i + 1] += 1; 
            }
        }
    }
    return result;
}*/

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