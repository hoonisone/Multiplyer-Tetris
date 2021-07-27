#include "my_math.h"

int main(void){
	int a, b, c;
	printf("a b c를 입력하세요\n>>");
	scanf("%d %d %d", &a, &b, &c);
	
	if(c==0){
		printf("0으로 나눌 수 없습니다.\n");
		return 0;
	}
	else printf("(a+b)/c = %d\n", div(add(a, b), c));
}
