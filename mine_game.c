#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void Setup(char* pf, char* ps);
void Select(char* pf, char* ps);
void Reveal(int* pa, int* pb, char* pf, char* ps);

void Setup(char* pf,char*ps) {  //판 생성과 지뢰 매설.
	int i;
	for (i = 0; i < 121; i++) {
		*(pf + i) = 58;
		*(ps + i) = 58;
	}
	for (i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			*(pf + 11 * i + j) = 61;
			*(ps + 11 * i + j) = 61;
		}
	}
	*pf = 48;
	*ps = 48;
	for (i = 1; i < 10; i++) {
		*(pf + i) = i+48;
		*(pf+11*i) = i+48;
		*(ps + i) = i + 48;
		*(ps + 11 * i) = i + 48;
	}
	srand(time(NULL));
	for (i = 0; i < 15; i++) {
		int a = (rand() % 8) + 1;
		int b = (rand() % 8) + 1;
		if (*(pf + 11 * a + b) == '#') {
			i--;
			continue;
		}
		*(pf + 11 * a + b) = '#';
	}
}	
void Select(char* pf, char* ps) {  //지뢰찾기의 플레이 단계. 좌표를 a와b로 받는다.
	int a, b;

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			printf("%c ", *(ps + 11 * i + j));
		}
		printf("\n");
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			printf("%c ", *(pf + 11 * i + j));
		}
		printf("\n");
	}
	printf("좌표 지정(행 렬): ");
	scanf("%d %d", &a, &b);
	printf("\n");
	if ((a > 9 || a < 1) || (b > 9 || b < 1)) {
		printf("잘못된 좌표\n");
		return 0;
	}
	Reveal(&a, &b, pf, ps);
}

void Reveal(int* pa, int* pb, char* pf, char* ps) {  //지정한 좌표가 지뢰인지, 지뢰가 아니라면 주변에 지뢰가 몇개 있는지를 구현. 공백이면 재귀를 통해 주변 칸들에게 재실행.
	int n = 0,i,j;
	if (*(pf + *pa * 11 + *pb) != 61 && *(pf + *pa * 11 + *pb) != 35) return 0;
	else if (*(pf + *pa * 11 + *pb) == 35) {
		for (i = 0; i < 11; i++) {
			for (j = 0; j < 11; j++) {
				printf("%c ", *(pf + 11 * i + j));
			}
			printf("\n");
		}
		printf("GAME OVER\n");
		return 0;
	}
	*pa -= 1;
	*pb -= 1;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (*(pf + (*pa + i) * 11 + (*pb + j))=='#') {
				n++;
			}
		}
	}
	if (n == 0) {
		*(ps + (*pa + 1) * 11 + (*pb + 1)) = 46;
		for (i = 0; i < 3; i++) {
			for (j = 0; j < 3; j++) {
				Reveal(pa + i, pb + j, pf, ps);
			}
		}
	}
	for (i = 1; i < 9; i++) {
		if (n == i) *(ps + (*pa + 1) * 11 + (*pb + 1)) = 48+i;
	}
}


int main(void) {
	char field[11][11] = {0};
	char screen[11][11] = {0};
	Setup(field,screen);
	for (int i=0;i<5;i++) {
		Select(field, screen);
	}
	// 게임오버 구현
	return 0;
}