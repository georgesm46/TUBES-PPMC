#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/*TIPE BENTUKAN STRUCT*/
typedef struct titik{
    char node;
    int x;
    int y;
}titik;

typedef struct komponen{
    char nama[100];
    titik kaki1;
    titik kaki2;
    titik kaki3;
}komponen;


//HEADER PROSEDUR DAN FUNGSI
void layoutingManual (struct komponen arrSkematik[40], int *jumlahKomponen, int x, int y);
void routeX(char sym, int x1, int x2, int y, char arrRoute[40][40]);
void routeY(char sym, int y1, int y2, int x, char arrRoute[40][40]);
void route(char sym, int x1, int y1, int x2, int y2, char arrRoute[40][40]);
void routingManual(char route[40][40], int jmlKomp, komponen arrKomp[40], int xi, int yi);
int cekInputan(char *input);
void getTitik(char *input, int *x, int *y);
void getNode(char node[40][40], int jmlKomp, komponen arrKomp[40]);
void cekDRC (komponen arrKomp[40],int jmlKomp);
void tampilkanLayout(komponen arrSkematik[40],char matSkematik [40][40][4],int jmlKompo, int N, int M);
void gantiNode(char node[40][40],int jmlKomp, komponen arrKomp[40]);
void tampilkanRouting (char routing[40][40], int N, int M);
void validasi (int *cx,int *cy,int *x,int *y);
void menu();
void menuUtama();
void saveFile(char nFileL[], int N, int M, char arrL[N][M][4], char arrR[N][M]);
void createFile(char nFile_L[], char nFile_R[], int N, int M, char arr_L[N][M][4], char arr_R[N][M]);
void loadFile(char nFileL[], char arrL[40][40][4], char arrR[40][40], int *N, int *M);
void getArr(char nFile_L[], char nFile_R[], int *i, int *j, char arr_L[*i][*j][4], char arr_R[*i][*j]);
