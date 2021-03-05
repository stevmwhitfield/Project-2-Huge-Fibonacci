#include <stdio.h>
#include <stdlib.h>
#include "Fibonacci.h"

void hugePrint(HugeInteger *p);
HugeInteger *testHugeAdd(int n1, int n2);

int main(void) {

    HugeInteger *result = testHugeAdd(1807, 92);
    printf("expected: %d\n", 1807 + 92);
    printf("result: ");
    hugePrint(result);

    result = testHugeAdd(1899, 2065);
    printf("\nexpected: %d\n", 1899 + 2065);
    printf("result: ");
    hugePrint(result);

    result = testHugeAdd(36, 179);
    printf("\nexpected: %d\n", 36 + 179);
    printf("result: ");
    hugePrint(result);

}

HugeInteger *testHugeAdd(int n1, int n2) {
    HugeInteger *a, *b;
    a = parseInt(n1);
    b = parseInt(n2);
    //hugePrint(a);
    //hugePrint(b);
    return hugeAdd(a, b);
}

void hugePrint(HugeInteger *p) {
	int i;
	
	if (p == NULL || p->digits == NULL)
	{
		printf("(null pointer)\n");
		return;
	}
	
	for (i = p->length - 1; i >= 0; i--)
		printf("%d", p->digits[i]);
	printf("\n");
}