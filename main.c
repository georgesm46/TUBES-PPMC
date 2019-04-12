#include "lib.h"

/*TIPE BENTUKAN STRUCT*/
/*******************MAIN PROGRAM UNTUK TESTING*************************/
int main(){
    int pilihan,n,m,mode,k,i,j;
    int *g;
    int *f;
    int jmlKomp;
    char temp[]= " ";
    char layout[40][40][4];
    for(int p=0;p<40;p++){
        for(int h=0;h<40;h++){
            strcpy(layout[p][h],temp);
        }
    }
    char sf[20],lf[20];
    char routing[40][40];
    for (int s=0;s<40;s++){
        for (int q=0;q<40;q++){
            routing[s][q]=' ';
        }
    }
    komponen arrKomp[40];
    menu();
    scanf("%d",&pilihan);
    if (pilihan != 1 && pilihan != 2 && pilihan != 3){
        printf("Pilihan tidak valid harap masukan ulang\n");
        do {
            menu();
            scanf("%d",&pilihan);
        } while (pilihan != 1 && pilihan != 2 && pilihan != 3);
    }
         while (pilihan != 3){
            if (pilihan == 1){
                for(int p=0;p<40;p++){
                    for(int h=0;h<40;h++){
                        strcpy(layout[p][h],temp);
                    }
                }
                for (int s=1;s<40;s++){
                    for (int q=0;q<40;q++){
                        routing[s][q]=' ';
                    }
                }
                printf("\n====== Membuat Proyek Baru ======\n");
                printf("Masukkan nama proyek: ");
                scanf("%s",&sf); ///nama file
                printf("Masukkan ukuran PCB NxM (N,M<40): ");
                scanf("%d %d", &n, &m);
                printf("\n");
                menuUtama();
                scanf("%d",&mode);
                int cek=1;
                do {
                    if (mode==1){
                        printf("\n[Layout Rangkaian pada PCB Dot Matriks]\n");
                        if (cek == 1){
                            printf(" ");
                            for (k=1; k<=n;k++){
                                printf("%d\t",k);
                            }
                            printf("\n");
                            for (j=1;j<=m;j++){
                                printf("%d ",j);
                                printf("\n");
                            }
                        } else {
                            tampilkanLayout(arrKomp,layout,jmlKomp,n,m);
                        }
                        menuUtama();
                        scanf("%d",&mode);
                    }
                    else if (mode==2){
                        layoutingManual(arrKomp,&jmlKomp,m,n);
                        cek=2;
                        menuUtama();
                        scanf("%d",&mode);
                    }
                    else if (mode==3){
                        if (cek != 4){
                            printf("\n[Routing Rangkaian pada PCB Dot Matriks]\n");
                            printf(" ");
                            for (k=1;k<=n;k++){
                                printf("%d\t",k);
                            }
                            printf("\n");
                            for(j=0;j<m;j++){
                                printf("%d ",j+1);
                                for(i=0;i<=n;i++){
                                    printf("%c\t",routing[i][j]);
                                }
                                printf("\n");
                            }
                        } else {
                            tampilkanRouting(routing,n,m);
                        }
                        cek=3;
                        menuUtama();
                        scanf("%d",&mode);
                    }
                    else if (mode==4){
                        routingManual(routing,jmlKomp,arrKomp,n,m);
                        cek=4;
                        menuUtama();
                        scanf("%d",&mode);
                    }
                    else if (mode==5){
                        strcpy(lf,"autoCE");
                        loadFile(lf, layout, routing, &g, &f);
                        cek=5;
                        menuUtama();
                        scanf("%d",&mode);
                    }
                    else if (mode==6){
                        strcpy(lf,"autoCE");
                        if(cek!=5){
                            loadFile(lf, layout, routing, &g, &f);
                        }
                        cek=6;
                        menuUtama();
                        scanf("%d",&mode);
                    }
                    else if (mode==7){
                        cekDRC (arrKomp,jmlKomp);
                        cek=7;
                        menuUtama();
                        scanf("%d",&mode);
                    }
                    else if (mode < 0 || mode >8) {
                        printf("\ninput tidak valid\n");
                        menuUtama();
                        scanf("%d",&mode);
                    }
                } while (mode != 8);
                saveFile(sf, n, m, layout, routing);
            } else if (pilihan == 2){
                printf("\n====== Memngubah Proyek Lama ======\n");
                printf("Masukkan nama proyek: ");
                scanf("%s",&lf); ///nama file
                loadFile(lf, layout, routing, &g, &f);
                printf("<%d %d>",g,f);
                printf("\n");
                int count=-1;
                for (j=0;j<=f;j++){
                    for (i=0;i<=g;i++){
                        if (strcmp(layout[i][j]," ")!= 0){
                            printf("X");
                            count=count+1;
                            strcpy(arrKomp[count].nama,layout[i][j]);
                            char search[] = "T";
                            char *ptr = strstr(arrKomp[i].nama, search);
                            if(ptr != NULL){
                                if (arrKomp[count].kaki1.x == NULL && arrKomp[count].kaki1.y == NULL){
                                    arrKomp[count].kaki1.x=i;
                                    arrKomp[count].kaki1.y=j;
                                } else if (arrKomp[count].kaki2.x == NULL && arrKomp[count].kaki2.y == NULL){
                                    arrKomp[count].kaki2.x=i;
                                    arrKomp[count].kaki2.y=j;
                                } else {
                                    arrKomp[count].kaki3.x=i;
                                    arrKomp[count].kaki3.y=j;
                                }
                            }else {
                                if (arrKomp[count].kaki1.x == NULL && arrKomp[count].kaki1.y == NULL){
                                    arrKomp[count].kaki1.x=i;
                                    arrKomp[count].kaki1.y=j;
                                } else {
                                    arrKomp[count].kaki2.x=i;
                                    arrKomp[count].kaki2.y=j;
                                }

                            }
                        }
                    }
                }
                getNode(routing,count,arrKomp);
                gantiNode(routing,count,arrKomp);
                jmlKomp=count;
                menuUtama();
                scanf("%d",&mode);
                do {
                    if (mode==1){
                        printf("\n[Layout Rangkaian pada PCB Dot Matriks]\n");
                        printf("\n");
    					printf(" ");
    					for (k=1; k<=g;k++){
        					printf("%d\t",k);
    					}
    					printf("\n");
    					for (j=1;j<=f;j++){
        					printf("%d ",j);
        					for (i=0;i<g;i++){
            					printf("%s\t",layout[i][j-1]);
        					}
        					printf("\n");
    					}
                        menuUtama();
                        scanf("%d",&mode);
                    }
                    else if (mode==2){
                        layoutingManual(arrKomp,&jmlKomp,g,f);
                        menuUtama();
                        scanf("%d",&mode);
                    }
                    else if (mode==3){
                        printf("\n[Routing Rangkaian pada PCB Dot Matriks]\n");
                        tampilkanRouting(routing,g,f);
                        menuUtama();
                        scanf("%d",&mode);
                    }
                    else if (mode==4){
                        routingManual(routing,jmlKomp,arrKomp,g,f);

                        menuUtama();
                        scanf("%d",&mode);
                    }
                    else if (mode==7){
                        cekDRC (arrKomp,jmlKomp);
                        menuUtama();
                        scanf("%d",&mode);
                    }
                    else{
                        printf("\ninput tidak valid\n");
                        menuUtama();
                        scanf("%d",&mode);
                    }
                } while (mode != 8);
                saveFile(lf, g, f, layout, routing);
            }
            menu();
            scanf("%d",&pilihan);
        }
        return (0);
}
