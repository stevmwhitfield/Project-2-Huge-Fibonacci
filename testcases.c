#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Fibonacci.h"

void hugePrint(HugeInteger *p);
void hugePrint2(HugeInteger *p);
void t1();
void t2();
void t3();
void t4();
void t5();
void t6();

int main(void) {
    //t1();
    //t2();
    //t3();
    //t4();
	int i;
	HugeInteger *p, *q, *r;

	p = parseInt(10946);
	q = parseInt(17711);
	r = hugeAdd(p, q);

	hugePrint(r);

}

// print a HugeInteger (followed by a newline character)
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

// print a HugeInteger (without a newline character)
void hugePrint2(HugeInteger *p) {
	int i;

	if (p == NULL || p->digits == NULL)
	{
		printf("(null pointer)");
		return;
	}

	for (i = p->length - 1; i >= 0; i--)
		printf("%d", p->digits[i]);
}

void t1() {
	HugeInteger *p;

	hugePrint(p = parseString("12345"));
	hugeDestroyer(p);
	
	hugePrint(p = parseString("354913546879519843519843548943513179"));
	hugeDestroyer(p);

	hugePrint(p = parseString(NULL));
	hugeDestroyer(p);
	
	hugePrint(p = parseInt(246810));
	hugeDestroyer(p);

	hugePrint(p = parseInt(0));
	hugeDestroyer(p);

	hugePrint(p = parseInt(INT_MAX));
	hugeDestroyer(p);

	hugePrint(p = parseInt(UINT_MAX));
	hugeDestroyer(p);
}

void t2() {
	unsigned int *temp;
	HugeInteger *p;

	hugePrint(p = parseString("12345"));
	printf("%u\n", *(temp = toUnsignedInt(p)));
	free(temp);
	hugeDestroyer(p);

	hugePrint(p = parseString("354913546879519843519843548943513179"));
	temp = toUnsignedInt(p);
	if (temp == NULL)
		printf("Good work.\n");
	else
		printf("Uh oh...\n");
	free(temp);
	hugeDestroyer(p);

	hugePrint(p = parseString(NULL));
	temp = toUnsignedInt(p);
	if (temp == NULL)
		printf("Good work.\n");
	else
		printf("Uh oh...\n");
	free(temp);
	hugeDestroyer(p);

	hugePrint(p = parseInt(246810));
	printf("%u\n", *(temp = toUnsignedInt(p)));
	free(temp);
	hugeDestroyer(p);

	hugePrint(p = parseInt(0));
	printf("%u\n", *(temp = toUnsignedInt(p)));
	free(temp);
	hugeDestroyer(p);

	hugePrint(p = parseInt(INT_MAX));
	printf("%u\n", *(temp = toUnsignedInt(p)));
	free(temp);
	hugeDestroyer(p);

	hugePrint(p = parseInt(UINT_MAX));
	printf("%u\n", *(temp = toUnsignedInt(p)));
	free(temp);
	hugeDestroyer(p);
}

void t3() {
	int i;
	HugeInteger *p, *q, *r;

	// calculate INT_MAX + 1
	p = parseInt(INT_MAX);
	q = parseInt(1);
	r = hugeAdd(p, q);

	// demonstrate overflow
	//printf("Overflow style:\n%d + %d = %d\n\n", INT_MAX, 1, INT_MAX + 1);

	// print result of INT_MAX + 1 with HugeIntegers
	printf("HugeInteger style:\n");
	hugePrint2(p);
	printf(" + ");
	hugePrint2(q);
	printf(" = ");
	hugePrint2(r);
	printf("\n\n");

	// free memory
	hugeDestroyer(p);
	hugeDestroyer(q);
	hugeDestroyer(r);


	// now calculate UINT_MAX + 1
	p = parseInt(UINT_MAX);
	q = parseInt(1);
	r = hugeAdd(p, q);

	// demonstrate overflow
	printf("Overflow style:\n%u + %u = %u\n\n", UINT_MAX, 1, UINT_MAX + 1);

	// print result of UINT_MAX + 1 with HugeIntegers
	printf("HugeInteger style:\n");
	hugePrint2(p);
	printf(" + ");
	hugePrint2(q);
	printf(" = ");
	hugePrint2(r);
	printf("\n");

	// free memory
	hugeDestroyer(p);
	hugeDestroyer(q);
	hugeDestroyer(r);
}

void t4() {
    int i;
	HugeInteger *p;

	for (i = 0; i <= 20; i++)
	{
		printf("F(%d) = ", i);
		hugePrint(p = fib(i));
		hugeDestroyer(p);
	}
}

void t5() {
	if (difficultyRating() < 1.0 || difficultyRating() > 5.0)
		printf("difficultyRating() test: **fail**\n");
	else
		printf("difficultyRating() test: PASS\n");

	if (hoursSpent() <= 0.0)
		printf("hoursSpent() test: **fail**\n");
	else
		printf("hoursSpent() test: PASS\n");
}