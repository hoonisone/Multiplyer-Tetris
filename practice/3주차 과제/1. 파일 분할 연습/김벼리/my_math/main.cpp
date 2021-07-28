#include <stdio.h>
#include "my_math.h"

int main() {
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	printf("%d", my_div(my_add(a, b), c));

	return 0;
}
