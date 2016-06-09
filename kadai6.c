/*** kadai6.c PNM �w�b�_�o�̓v���O���� ***/ 
/*** s12169 2J34 �����S�� ***/ 
#include<stdio.h> 
#include<stdlib.h> 
 
#define MAX_FNAME 256 /* �t�@�C�����̍ő咷 */ 
 
/* PNM �w�b�_�\���� */ 
typedef struct { 
	int Magic; /* �}�W�b�N�i���o�[�F�������̂� */ 
	int HSize; /* ����f�� */ 
	int VSize; /* �c��f�� */ 
	int MaxY; /* �ő�P�x */ 
} PNMHeader; 
 
 
int main(void) 
{ 
	PNMHeader head; /* PNM �w�b�_ */ 
	char fname[MAX_FNAME]; /* �o�̓t�@�C���� */ 
	FILE *out;
	
	printf("�o�̓t�@�C����:");
	gets(fname);
	out=fopen(fname,"wb");

	if(out==NULL) {
		printf("�t�@�C�����J���܂���ł���\n");
		exit(-1);
	}
	
	printf("�}�W�b�N�i���o�[(�����̂�): ");
	scanf("%d", &head.Magic);
	printf("����f��: ");
	scanf("%d", &head.HSize);
	printf("�c��f��: ");
	scanf("%d", &head.VSize);
	
	fprintf(out,"P%d\n%d %d", head.Magic, head.HSize, head.VSize);
	
	if (head.Magic != 1 && head.Magic != 4) {
		printf("�ő�P�x: ");
		scanf("%d", &head.MaxY);
		fprintf(out,"\n%d", head.MaxY);
	}
	
	fclose(out);
	return 0; 
} 