#include "my_math.h"

int main(void){
	int a, b, c;
	printf("a b c�� �Է��ϼ���\n>>");
	scanf("%d %d %d", &a, &b, &c);
	
	if(c==0){
		printf("0���� ���� �� �����ϴ�.\n");
		return 0;
	}
	else printf("(a+b)/c = %d\n", div(add(a, b), c));
}
