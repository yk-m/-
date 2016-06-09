/***  kadai4.c  ***/
/***  s12169  2J34  松尾祐佳  ***/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX_ARRAY 38

int GetnRow(char map[][MAX_ARRAY])
{
	int i=0;
	while (map[i][0] == '|' || map[i][0] == '*') i++;
	if(map[i][0] == '\0') {
		return i;
	} else {
		return -1;
	}
}

int GetnColumn(char map[][MAX_ARRAY])
{
	int i=0,j=0;
	while (map[0][i] != '\0' && i<MAX_ARRAY) {
		if (map[0][i] == '|') j++;
		if (map[0][i] == '*' && i%2==0) j++;
		i++;
	}
	if(map[0][i] == '\0' ) {
		return j;
	} else {
		return -1;
	}
}

void DisplayAmida(char map[][MAX_ARRAY])
{
	int i,j;
	for (i=0; i<GetnColumn(map); i++){
		printf("   %d",i);
	}
	printf("\n");
	for (i=0; i<GetnRow(map); i++) {
		printf("%2d ",i);
		for (j=0; j<GetnColumn(map)*2-1; j++) {
			if (map[i][j] == ' ') {
				printf("   ");
			} else if (map[i][j] == '-') {
				printf("---");
			} else if (map[i][j] == '*') {
				if (j%2 != 0) {
					printf("***");
				} else {
					printf("*");
				}
			} else if (map[i][j] == '|') {
				printf("|");
			}
		}
		printf("\n");
	}
	for (i=0; i<GetnColumn(map); i++){
		printf("   %c",'A'+i);
	}
	printf("\n");
}

int RemoveBarfromAmida(char map[][MAX_ARRAY],int rmrow,int rmcol)
{
	int row, col, i=-1;
	row = GetnRow(map);
	col = GetnColumn(map);
	if (rmcol >= 0 && rmrow > 0 && rmcol < col-1 && rmrow < row-1 && map[rmrow][2*rmcol+1] == '-') {
		map[rmrow][2*rmcol+1] = ' ';
		return 0;
	} else { 
		return -1;
	}
}

int AddBartoAmida(char map[][MAX_ARRAY],int addrow,int addcol)
{
	int row, col;
	row = GetnRow(map);
	col = GetnColumn(map);
	if (addcol >= 0 && addrow > 0 && addcol < col-1 && addrow < row-1 && map[addrow][2*addcol+1] == ' ' && map[addrow][2*addcol-1] != '-' && map[addrow][2*addcol+3] != '-') {
		map[addrow][2*addcol+1] = '-';
		return 0;
	} else {
		return -1;
	}
}

int GenerateAmida(char map[][MAX_ARRAY], int nrow,int ncol,int nbar)
{
	int i, j, r, c, res;
	if (nrow < 3 || nrow >= MAX_ARRAY || ncol < 2 || ncol > MAX_ARRAY / 2 || nbar < 0 || nbar > (nrow - 2)*(ncol - 1) / 2) return -1;
	for(i=0; i<nrow+1; i++) {
		for(j=0; j<2*ncol; j++) {
			if (j%2 == 0) {
				map[i][j] = '|';
			} else {
				map[i][j] = ' ';
			}
		}
		map[i][2*ncol+1] = '\0';
	}
	for(j=0; j<=2*ncol+1; j++) {
		map[nrow][j] = '\0';
	}
	for (i=0; i<nbar; i++) {
		do {
			r = rand()%(nrow-1) + 1;
			c = rand()%(ncol);
			res = AddBartoAmida(map, r, c);
		} while (res != 0);
	}
	
	return nbar;
}

void InitAmida(char map[][MAX_ARRAY])
{
	static char isRandInit=0;
	int i,j;
	time_t t;
	for(i=0;i<MAX_ARRAY;i++) {
		for(j=0;j<MAX_ARRAY;j++) {
			map[i][j]='\0';
		}
	}
	
	if(!isRandInit) {
		srand((unsigned)time(&t));
		isRandInit=1;
	}
}

int SolveAmida(char map[][MAX_ARRAY],int start)
{
	char solmap[MAX_ARRAY][MAX_ARRAY];
	int row, col;
	int i, j;
	
	row = GetnRow(map);
	col = GetnColumn(map);
	
	if (start < 0 || start > col-1) return -1;
	
	for (i=0; i<MAX_ARRAY; i++) {
		for (j=0; j<MAX_ARRAY; j++) {
			solmap[i][j] = map[i][j];
		}
	}
	
	i=0;
	j=2*start;
	
	while (solmap[i][j] != '\0') {
		solmap[i][j] = '*';
		if (i!=0 && i!=row-1 && j<col*2-2 && solmap[i][j+1] == '-') {
			solmap[i][j+1] = '*';
			solmap[i][j+2] = '*';
			j+=2;
		} else if (i!=0 && i!=row-1 && j!=0 && solmap[i][j-1] == '-') {
			solmap[i][j-1] = '*';
			solmap[i][j-2] = '*';
			j-=2;
		}
		i++;
	}
	DisplayAmida(solmap);
	return j/2;
}

int main(void)
{
	char map[MAX_ARRAY][MAX_ARRAY] = {
		{'|',' ','|',' ','|',' ','|',' ','|','\0'},
		{'|','-','|',' ','|','-','|',' ','|','\0'},
		{'|',' ','|',' ','|',' ','|','-','|','\0'},
		{'|',' ','|','-','|',' ','|',' ','|','\0'},
		{'|',' ','|','-','|',' ','|','-','|','\0'},
		{'|','-','|',' ','|','-','|',' ','|','\0'},
		{'|',' ','|',' ','|',' ','|',' ','|','\0'},
		{'|','-','|',' ','|',' ','|','-','|','\0'},
		{'|',' ','|','-','|',' ','|',' ','|','\0'},
		{'|',' ','|',' ','|','-','|',' ','|','\0'},
		{'|',' ','|','-','|',' ','|','-','|','\0'},
		{'|','-','|',' ','|','-','|',' ','|','\0'},
		{'|',' ','|',' ','|',' ','|',' ','|','\0'},
		{'|',' ','|','-','|',' ','|','-','|','\0'},
		{'|','-','|',' ','|',' ','|',' ','|','\0'},
		{'|',' ','|',' ','|',' ','|',' ','|','\0'},
		{'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'}
	};
	int start, fin;
	printf("始点の位置を入力([列番号])--->");
	scanf("%d", &start);
	fin = SolveAmida(map, start);
	if (fin != -1) printf("終点=%c\n",'A'+fin);
	return 0;
}

/* 実行結果 

始点の位置を入力([列番号])--->3
   0   1   2   3   4
 0 |   |   |   *   |
 1 |---|   *****   |
 2 |   |   *   |---|
 3 |   *****   |   |
 4 |   *****   |---|
 5 |---|   *****   |
 6 |   |   |   *   |
 7 |---|   |   *****
 8 |   |---|   |   *
 9 |   |   |---|   *
10 |   |---|   *****
11 |---|   *****   |
12 |   |   *   |   |
13 |   *****   |---|
14 *****   |   |   |
15 *   |   |   |   |
   A   B   C   D   E
終点=A

始点の位置を入力([列番号])--->-1

*/