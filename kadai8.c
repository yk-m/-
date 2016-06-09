/*** kadai8.c PNM ファイル出力プログラム ***/
/*** s12169 2J34 松尾祐佳 ***/ 
#include<stdio.h> 
#include<stdlib.h> 

#define MAX_FNAME 256 /* ファイル名の最大長 */ 
#define MAX_PIXEL 256 /* 扱える最大画素数 */ 

/* PNM ヘッダ構造体 */ 
typedef struct { 
	int Magic; /* マジックナンバー：整数部のみ */ 
	int HSize; /* 横画素数 */ 
	int VSize; /* 縦画素数 */ 
	int MaxY; /* 最大輝度 */ 
} PNMHeader; 

int WritePNMMonoFile(char fname[],PNMHeader head,unsigned char y[][MAX_PIXEL]) 
{
	int i, j;
	FILE *out;
	out = fopen(fname,"wb");
	if (out==NULL) return -1;
	if (head.Magic != 1 && head.Magic != 2) return -1;
	if (head.HSize <= 0 || head.VSize <= 0 || head.HSize > MAX_PIXEL || head.VSize > MAX_PIXEL) return -1;
	
	fprintf(out,"P%d\n%d %d\n", head.Magic, head.HSize, head.VSize);
	
	if (head.Magic != 1 && head.Magic != 4) fprintf(out,"%d\n", head.MaxY);
	
	for (i=0; i<head.VSize; i++) {
		for (j=0; j<head.HSize; j++) {
			fprintf(out,"%d\n", y[i][j]);
		}
	}
	
	fclose(out);
	return 0;
}

PNMHeader GenHLineB(int Height,int nHLine,int Width,unsigned char y[][MAX_PIXEL]) {
	PNMHeader ret = {-1,-1,-1,-1};
	int picHeight;
	int i,j;
	picHeight = Height * nHLine;
	if (Height<=0 || Height>MAX_PIXEL) return ret;
	if (nHLine<=0 || nHLine>MAX_PIXEL) return ret;
	if (Width <=0 || Width >MAX_PIXEL) return ret;
	if (picHeight<=0 || picHeight>MAX_PIXEL) return ret;

	ret.Magic = 1;
	ret.HSize = Width;
	ret.VSize = picHeight;

	for (i=0; i<ret.VSize; i++) {
		if (i==0 || i % (Height*2) < Height) {
			for (j=0; j<ret.HSize; j++) y[i][j] = 0;
		} else {
			for (j=0; j<ret.HSize; j++) y[i][j] = 1;
		}
	}
	return ret;
}


/* 2 値市松模様画像の生成 */
/* Size:ます目の 1 辺の画素数 */
/* nVTile:縦方向のます目の数 */
PNMHeader GenCheckerB(int Size,int nHTile,int nVTile,unsigned char y[][MAX_PIXEL]) {
	PNMHeader ret = {-1,-1,-1,-1};
	int picHeight, picWidth;
	int i,j;
	picHeight  = nVTile * Size;
	picWidth   = nHTile * Size;
	if (Size  <=0 || Size  >MAX_PIXEL) return ret;
	if (nHTile<=0 || nHTile>MAX_PIXEL) return ret;
	if (nVTile<=0 || nVTile>MAX_PIXEL) return ret;
	if (picHeight<=0 || picHeight>MAX_PIXEL) return ret;
	if (picWidth <=0 || picWidth >MAX_PIXEL) return ret;
	
	ret.Magic = 1;
	ret.HSize = picWidth;
	ret.VSize = picHeight;

	for (i=0; i<ret.VSize; i++) {
		if (i%(Size*2) < Size) {
			for (j=0; j<ret.HSize; j++) {
				if (j%(Size*2) < Size) y[i][j] = 0;
				else y[i][j] = 1;
			}
		} else {
			for (j=0; j<ret.HSize; j++) {
				if (j%(Size*2) < Size) y[i][j] = 1;
				else y[i][j] = 0;
			}
		}
	}

	return ret;
}


PNMHeader GenVLineG(int Width,int nVLine,int Height,unsigned char y[][MAX_PIXEL]) {
	PNMHeader ret = {-1,-1,-1,-1};
	int picWidth;
	int i,j,k,l;
	picWidth = nVLine * Width;
	if (Width <=0 || Width >MAX_PIXEL) return ret;
	if (nVLine<=0 || nVLine>MAX_PIXEL) return ret;
	if (Height<=0 || Height>MAX_PIXEL) return ret;
	if (picWidth<=0 || picWidth>MAX_PIXEL) return ret;
	
	ret.Magic = 2;
	ret.HSize = picWidth;
	ret.VSize = Height;
	ret.MaxY  = 255;

	if (nVLine==1) {
		for (i=0; i<ret.VSize; i++) {
			for (j=0; j<ret.HSize; j++) y[i][j] = 255;
		}
	} else {
		for (i=0; i<ret.VSize; i++) {
			for (j=0; j<ret.HSize; j++) {
				for (k=nVLine-1, l=0; k>=0, l<nVLine; k--, l++) {
					if (j/Width == l) y[i][j] = 255*k/(nVLine-1);
				}
			}
		}
	}

	return ret;
}


int main(void) 
{
	PNMHeader head;
	char fname[MAX_FNAME];
	unsigned char y[MAX_PIXEL][MAX_PIXEL];
	int kind=0, a, b, c;
	
	while (kind!=1 && kind!=2 && kind!=3) {
		printf("生成画像の種類を入力\n1:2値横縞 2:2値市松模様 3:濃淡縦縞 : ");
		scanf("%d", &kind);
	}

	if (kind == 1) {
		printf("1本の横縞の縦画素数: ");
		scanf("%d", &a);
		printf("        横縞の本数: ");
		scanf("%d", &b);
		printf("          横画素数: ");
		scanf("%d", &c);
		head = GenHLineB(a, b, c, y);
	} else if (kind == 2) {
		printf("ます目の1辺の画素数: ");
		scanf("%d", &a);
		printf(" 横方向のます目の数: ");
		scanf("%d", &b);
		printf(" 縦方向のます目の数: ");
		scanf("%d", &c);
		head = GenCheckerB(a, b, c, y);
	} else {
		printf("1本の縦縞の横画素数: ");
		scanf("%d", &a);
		printf("        縦縞の本数: ");
		scanf("%d", &b);
		printf("          縦画素数: ");
		scanf("%d", &c);
		head = GenVLineG(a, b, c, y);
	}

	if (head.Magic == -1) printf("*****指定されたパラメータの画像を生成できませんでした*****\n");
	else {
		printf("     出力ファイル名: ");
		scanf("%s",fname);
		WritePNMMonoFile(fname, head, y);
		printf("-----指定されたパラメータの画像を生成しました-----\n");
	}
	
	return 0; 
} 

/* 実行結果 


*/