/*** kadai6.c PNM ヘッダ出力プログラム ***/ 
/*** s12169 2J34 松尾祐佳 ***/ 
#include<stdio.h> 
#include<stdlib.h> 
 
#define MAX_FNAME 256 /* ファイル名の最大長 */ 
 
/* PNM ヘッダ構造体 */ 
typedef struct { 
	int Magic; /* マジックナンバー：整数部のみ */ 
	int HSize; /* 横画素数 */ 
	int VSize; /* 縦画素数 */ 
	int MaxY; /* 最大輝度 */ 
} PNMHeader; 
 
 
int main(void) 
{ 
	PNMHeader head; /* PNM ヘッダ */ 
	char fname[MAX_FNAME]; /* 出力ファイル名 */ 
	FILE *out;
	
	printf("出力ファイル名:");
	gets(fname);
	out=fopen(fname,"wb");

	if(out==NULL) {
		printf("ファイルを開けませんでした\n");
		exit(-1);
	}
	
	printf("マジックナンバー(数字のみ): ");
	scanf("%d", &head.Magic);
	printf("横画素数: ");
	scanf("%d", &head.HSize);
	printf("縦画素数: ");
	scanf("%d", &head.VSize);
	
	fprintf(out,"P%d\n%d %d", head.Magic, head.HSize, head.VSize);
	
	if (head.Magic != 1 && head.Magic != 4) {
		printf("最大輝度: ");
		scanf("%d", &head.MaxY);
		fprintf(out,"\n%d", head.MaxY);
	}
	
	fclose(out);
	return 0; 
} 