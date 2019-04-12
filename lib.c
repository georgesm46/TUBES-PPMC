#include "lib.h"

//REALISASI FUNGSI DAN PROSEDUR
void route(char sym, int x1, int y1, int x2, int y2, char arrRoute[40][40]){
        routeX(sym,x1,x2,y1,arrRoute);
        routeY(sym,y1,y2,x2,arrRoute);
}

void routeX(char sym, int x1, int x2, int y, char arrRoute[40][40]){
    if(x1<x2){
        for(int i=(x1-1);i<x2;i++){
            arrRoute[y-1][i]=sym;
        }
    }else{
        for(int i=(x2-1);i<x1;i++){
            arrRoute[y-1][i]=sym;
        }
    }
}

void routeY(char sym, int y1, int y2, int x, char arrRoute[40][40]){
    if(y1<y2){
        for(int i=(y1-1);i<y2;i++){
            arrRoute[i][x-1]=sym;
        }
    }else{
        for(int i=(y2-1);i<y1;i++){
            arrRoute[i][x-1]=sym;
        }
    }
}

void routingManual(char routing[40][40], int jmlKomp, komponen arrKomp[40], int xi, int yi){
	char node[40][40]; 	//MATRIKS NODE
	char NamaNode='a'; 	//NAMA NODE
	char inputan[10]; 	//BUAT INPUT KOORDINAT
	char temp[3];  		//BUAT NGEREAD SATU LINE
	char sym;  			//SYMBOL MASUKAN USER
    int condition=0;    //BUAT CHECKING
    int xd,yd;  		//BUAT CHECKING INPUT
	int x1,x2,y1,y2;   	//BUAT ROUTING
	int count; 			//BUAT COUNTING JUMLAH TITIK YANG DIMASUKKAN

	for(int i=0;i<40;i++){			//Inisialisasi matriks Node
		for(int j=0;j<40;j++){
			node[i][j]=' ';
		}
	}

//	printf("\nMATRIKS NODE SEBELUM DIROUTE\n");
//	for(int j=0;j<15;j++){					//Testing Matriks Node sebelum diroute
//		for(int i=0;i<15;i++){
//			printf("%c\t",node[i][j]);
//		}
//		printf("\n");
//	}

	printf("[Mode Routing]\n");								//Print Display
	printf("Isi 'q' atau 'Q' untuk kembali ke menu\n");
	printf("Isi 'n' atau 'N' untuk memulai pada simpul (node) baru\n");

	/*Memulai proses Routing sampai pengguna memasukkan karakter q atau Q*/
	do{
		/*VALIDASI SIMBOL*/
		do{
			printf("Pilih Simbol (!,@,#,$,%,^,&,*,(,)): ");
			scanf("%s",temp);
			sym=temp[0];
			if((sym!='!')&&(sym!='@')&&(sym!='#')&&(sym!='$')&&(sym!='%')&&(sym!='^')&&(sym!='&')&&(sym!='*')&&(sym!='(')&&(sym!=')')){
				printf("Pilihan simbol tidak sesuai\n");
			}
		}while((sym!='!')&&(sym!='@')&&(sym!='#')&&(sym!='$')&&(sym!='%')&&(sym!='^')&&(sym!='&')&&(sym!='*')&&(sym!='(')&&(sym!=')'));

		count=1; //Inisialisasi awal Variabel counter jumlah koordinat yang sudah dimasukkan
		/*PROSES INPUT KOORDINAT UNTUK SATU NODE*/
		do{

            do{
                printf("Koordinat %d: ",count); //INPUT KOORDINAT
                scanf("%s",inputan);
                condition=cekInputan(inputan);      //Validasi input koordinat
                if(condition==0){
                    getTitik(inputan,&yd,&xd);      //Validasi input koordinat tidak boleh lebih dari ukuran PCB
                    if(xd>xi||yd>yi){
                        condition=1;
                    }
                }

                if(condition==1 &&((strcmp(inputan,"q")!=0) && (strcmp(inputan,"Q")!=0) && (strcmp(inputan,"n")!=0) && (strcmp(inputan,"N")!=0))){
                    printf("Masukan titik tidak sesuai, ulangi proses masukan\n");
                }
            }while(condition==1 && ((strcmp(inputan,"q")!=0) && (strcmp(inputan,"Q")!=0) && (strcmp(inputan,"n")!=0) && (strcmp(inputan,"N")!=0)));

			if((strcmp(inputan,"q")!=0) && (strcmp(inputan,"Q")!=0) && (strcmp(inputan,"n")!=0) && (strcmp(inputan,"N")!=0) && (count==1)){
				getTitik(inputan,&x1,&y1);
				count++;
			}else if((strcmp(inputan,"q")!=0) && (strcmp(inputan,"Q")!=0) && (strcmp(inputan,"n")!=0) && (strcmp(inputan,"N")!=0)){
				getTitik(inputan,&x2,&y2);
				count++;
				route(sym,x1,y1,x2,y2,routing);
				route(NamaNode,x1,y1,x2,y2,node);
				x1=x2;
				y1=y2;
			}
		}while((strcmp(inputan,"q")!=0) && (strcmp(inputan,"Q")!=0) && (strcmp(inputan,"n")!=0) && (strcmp(inputan,"N")!=0));
		NamaNode++;
		printf("\n");

	}while((strcmp(inputan,"q")!=0) && (strcmp(inputan,"Q")!=0));
    getNode(node,jmlKomp,arrKomp);
    gantiNode(node,jmlKomp,arrKomp);
    getNode(node,jmlKomp,arrKomp);

//	printf("\nMATRIKS NODE SETELAH DIROUTE\n");
//	for(int j=0;j<15;j++){					//TESTING Matriks Node setelah diroute
//		for(int i=0;i<15;i++){
//			printf("%c\t",node[i][j]);
//			//if (node[i][j]=='a' || node[i][j]=='b' || node[i][j]=='c' ){
//            //    printf("\nIni titik = (%d)(%d)",j,i);
//			//}
//		}
//		printf("\n");
//	}
}

int cekInputan(char *input){
/*FUNGSI INI DIGUNAKAN UNTUK MENGECEK APAKAN INPUTAN SUDAH SESUAI DENGAN FORMAT KOORDINAT*/
    int pos,leng;
    int kondisi=0;
    int koma=0;
    pos=0;
    leng=strlen(input);

    while((kondisi==0) && (pos<leng)){
        if(((input[pos]<'0')||(input[pos]>'9'))&&(input[pos]!=',')){
            kondisi=1;
            pos++;
        }else if((input[pos]==',') && (koma==0)){
            koma=1;
            pos++;
        }else if((input[pos]==',') && (koma!=0)){
            kondisi=1;
            pos++;
        }else{
            pos++;
        }
    }

    return(kondisi||(!koma));
}

void getTitik(char *input, int *x, int *y){
	char *token;
	char temp[10];
	strcpy(temp,input);

	token=strtok(input,",");	//Parsing string dengan batas ','
	*x=atoi(token);				//Convert ke Integer
	token=strtok(NULL,",");
	*y=atoi(token);

	strcpy(input,temp);
}

void getNode(char node[40][40], int jmlKomp, komponen arrKomp[40]){
    for(int i=0;i<jmlKomp;i++){
        char search[] = "T";
        char *ptr = strstr(arrKomp[i].nama, search);
        if(ptr != NULL){
            for(int j=0;j<3;j++){
                if(j==0){
                    if(node[arrKomp[i].kaki1.y-1][arrKomp[i].kaki1.x-1]!=' '){
                        arrKomp[i].kaki1.node=node[arrKomp[i].kaki1.y-1][arrKomp[i].kaki1.x-1];
                    }
                }else if(j==1){
                    if(node[arrKomp[i].kaki2.y-1][arrKomp[i].kaki2.x-1]!=' '){
                        arrKomp[i].kaki2.node=node[arrKomp[i].kaki2.y-1][arrKomp[i].kaki2.x-1];
                    }
                }else{
                    if(node[arrKomp[i].kaki3.y-1][arrKomp[i].kaki3.x-1]!=' '){
                        arrKomp[i].kaki3.node=node[arrKomp[i].kaki3.y-1][arrKomp[i].kaki3.x-1];
                    }
                }
            }
        }else {
            for(int j=0;j<2;j++){
                if(j==0){
                    if(node[(arrKomp[i].kaki1.y)-1][(arrKomp[i].kaki1.x)-1]!=' '){
                        arrKomp[i].kaki1.node=node[(arrKomp[i].kaki1.y)-1][(arrKomp[i].kaki1.x)-1];
                    }
                }else{
                    if(node[(arrKomp[i].kaki2.y)-1][(arrKomp[i].kaki2.x)-1]!=' '){
                        arrKomp[i].kaki2.node=node[(arrKomp[i].kaki2.y)-1][(arrKomp[i].kaki2.x)-1];
                    }
                }
            }
        }
    }

}

void layoutingManual (struct komponen arrSkematik[40], int *jumlahKomponen, int x, int y) {
    //DEKLARASI VARIABEL
    //arrSkematik berfungsi untuk menampung data semua komponen yang diinput user dan telah divalidasi
    int i,j;
    char temp1[10];//penampung sementara inputan koordinat kaki 1
    char temp2[10];//penampung sementara inputan koordinat kaki 2
    char temp3[10];//penampung sementara inputan koordinat kaki 3
    int coorX1,coorY1;
    int coorX2,coorY2;
    int coorX3,coorY3;
    printf("\n[Mode Layout]");
    printf("\nIsi 'q' atau 'Q' untuk kembali ke menu\n");

    //Catatan untuk R,C,J kaki ketiga diinisialisasi dengan nilai 999;
    //ASSIGNMENT
    i=0;j=0;
    *jumlahKomponen = i;

    //MENERIMA INPUTAN USER SEKALIGUS MEMVALIDASI INPUTAN;
    printf("Pilih Komponen (R,C,T,J) : ");
    scanf("%s",&temp1);
    while (!(temp1[0]=='q'||temp1[0]=='Q'))
    {
        strcpy(arrSkematik[i].nama,temp1);

        //JIKA MASUKAN BERUPA TRANSISTOR
        if (temp1[0] == 'T'||temp1[0] == 't')
        {
            printf("Koordinat Kaki 1 : ");
            scanf("%s",&temp1);
            getTitik(&temp1,&coorX1,&coorY1);
            validasi(&coorX1,&coorY1,&x,&y);

            printf("Koordinat Kaki 2 : ");
            scanf("%s",&temp2);
            getTitik(&temp2,&coorX2,&coorY2);
            validasi(&coorX2,&coorY2,&x,&y);

            printf("Koordinat Kaki 3 : ");
            scanf("%s",&temp3);
            getTitik(&temp3,&coorX3,&coorY3);
            validasi(&coorX3,&coorY3,&x,&y);
        }

        //SEMUA MASUKAN SELAIN TRANSISTOR
        else
        {
            printf("Koordinat Kaki 1 : ");
            scanf("%s",&temp1);
            getTitik(&temp1,&coorX1,&coorY1);
            validasi(&coorX1,&coorY1,&x,&y);

            printf("Koordinat Kaki 2 : ");
            scanf("%s",&temp2);
            getTitik(&temp2,&coorX2,&coorY2);
            validasi(&coorX2,&coorY2,&x,&y);

            //INISIALISASI NILAI KAKI KOSONG
            coorX3 = 999;
            coorY3 = 999;
        }

        //VALIDASI INPUTAN KAKI
        if (arrSkematik[i].nama[0] == 'R'||arrSkematik[i].nama[0] == 'r' )
        {
            while (sqrt((coorX1-coorX2)*(coorX1-coorX2)+(coorY1-coorY2)*(coorY1-coorY2))<3)
            {
                printf("Space kaki resitor minimal harus = 3 \n");
                printf("Masukkan Ulang Koordinat Komponen: \n");
                //Meminta ulang masukan koordinat kaki

                printf("Koordinat Kaki 1 : ");
                scanf("%s",&temp1);
                getTitik(&temp1,&coorX1,&coorY1);
                validasi(&coorX1,&coorY1,&x,&y);

                printf("Koordinat Kaki 2 : ");
                scanf("%s",&temp2);
                getTitik(&temp2,&coorX2,&coorY2);
                validasi(&coorX2,&coorY2,&x,&y);
            }
        }
        else if (arrSkematik[i].nama[0] == 'C'|| arrSkematik[i].nama[0] == 'c')
        {
            while (sqrt((coorX1-coorX2)*(coorX1-coorX2)+(coorY1-coorY2)*(coorY1-coorY2))<1)
            {
                printf("Space kaki kapasitor minimal harus = 1 \n");
                printf("Masukkan Ulang Koordinat Komponen: \n");
                //Meminta ulang masukan koordinat kaki
                 printf("Koordinat Kaki 1 : ");
                 scanf("%s",&temp1);
                 getTitik(&temp1,&coorX1,&coorY1);
                 validasi(&coorX1,&coorY1,&x,&y);

                 printf("Koordinat Kaki 2 : ");
                 scanf("%s",&temp2);
                 getTitik(&temp2,&coorX2,&coorY2);
                 validasi(&coorX2,&coorY2,&x,&y);
            }
        }
        else if (arrSkematik[i].nama[0] == 'T'||arrSkematik[i].nama[0] == 't')
        {
            while ((sqrt((coorX1-coorX2)*(coorX1-coorX2)+(coorY1-coorY2)*(coorY1-coorY2))<1)
                   ||(sqrt((coorX1-coorX3)*(coorX1-coorX3)+(coorY1-coorY3)*(coorY1-coorY3))<1)
                   ||(sqrt((coorX3-coorX2)*(coorX3-coorX2)+(coorY3-coorY2)*(coorY3-coorY2))<1))
            {
                printf("Space kaki transistor minimal harus = 1 \n");
                printf("Masukkan Ulang Koordinat Komponen: \n");
                //Meminta ulang masukan koordinat kaki
                 printf("Koordinat Kaki 1 : ");
                 scanf("%s",&temp1);
                 getTitik(&temp1,&coorX1,&coorY1);
                 validasi(&coorX1,&coorY1,&x,&y);

                 printf("Koordinat Kaki 2 : ");
                 scanf("%s",&temp2);
                 getTitik(&temp2,&coorX2,&coorY2);
                 validasi(&coorX2,&coorY2,&x,&y);

                 printf("Koordinat Kaki 3 : ");
                 scanf("%s",&temp3);
                 getTitik(&temp3,&coorX3,&coorY3);
                 validasi(&coorX3,&coorY3,&x,&y);

            }
        }

        arrSkematik[i].kaki1.x = coorX1;
        arrSkematik[i].kaki1.y = coorY1;
        arrSkematik[i].kaki2.x = coorX2;
        arrSkematik[i].kaki2.y = coorY2;
        arrSkematik[i].kaki3.x = coorX3;
        arrSkematik[i].kaki3.y = coorY3;

        printf("\n");
        //MENERIMA MASUKAN KEMBALI
        printf("Pilih Komponen (R,C,T,J) : ");
        scanf("%s",&temp1);
        i++;

    }
    *jumlahKomponen = i;
    //printf("%d",arrSkematik[0].kaki1.x);
}

void validasi (int *cx,int *cy,int *x,int *y){
    char input[100];
    char *token;
	char temp[10];
    while (*cx>*x||*cx<=0||*cy>*y||*cy<=0)
    {
        printf("koordinat yang anda masukkan tidak sesuai");
        printf("\nMasukkan koordinat baru: ");gets(input);
        strcpy(temp,input);
        token=strtok(input,",");		//Parsing string dengan batas ','
        *cx=atoi(token);				//Convert ke Integer
        token=strtok(NULL,",");
        *cy=atoi(token);
        strcpy(input,temp);

    }
}

void tampilkanLayout(komponen arrSkematik[40],char matSkematik [40][40][4], int jmlKompo, int N, int M){
    int i,j,k,l,m,o,p;
    char temp[]=" ";
    for (i=0;i<jmlKompo;i++)
    {
        char search[] = "T";
        char *ptr = strstr(arrSkematik[i].nama, search);
        //MEMINDAHKAN KONFIGURASI KEDALAM MATRIX //Dihapus nanti
        if(ptr==NULL){
            j=arrSkematik[i].kaki1.x;
            k=arrSkematik[i].kaki1.y;
            l=arrSkematik[i].kaki2.x;
            m=arrSkematik[i].kaki2.y;
            strcpy(matSkematik[k][j],arrSkematik[i].nama);
            strcpy(matSkematik[m][l],arrSkematik[i].nama);

        }else{
            j=arrSkematik[i].kaki1.x;
            k=arrSkematik[i].kaki1.y;
            l=arrSkematik[i].kaki2.x;
            m=arrSkematik[i].kaki2.y;
            o=arrSkematik[i].kaki3.x;
            p=arrSkematik[i].kaki3.y;
            strcpy(matSkematik[k-1][j-1],arrSkematik[i].nama);
            strcpy(matSkematik[m-1][l-1],arrSkematik[i].nama);
            strcpy(matSkematik[p-1][o-1],arrSkematik[i].nama);
        }

    }
    printf("\n");
    printf(" ");
    for (int k=1; k<=N;k++){
        printf("%d\t",k);
    }
    printf("\n");
    for (j=1;j<=M;j++){
        printf("%d ",j);
        for (i=1;i<=N;i++){
            printf("%s\t",matSkematik[i][j]);
        }
        printf("\n");
    }
}

void gantiNode(char node[40][40],int jmlKomp, komponen arrKomp[40]){
    char vcc,vin,vout,Tb,Te,Tc,gnd;

    for(int i=0;i<jmlKomp;i++){
        if(strcmp(arrKomp[i].nama,"J1")==0){
            vin=arrKomp[i].kaki1.node;
            gnd=arrKomp[i].kaki2.node;
        }else if(strcmp(arrKomp[i].nama,"J2")==0){
            vout=arrKomp[i].kaki1.node;
        }else if(strcmp(arrKomp[i].nama,"T1")==0){
            Tc=arrKomp[i].kaki1.node;
            Tb=arrKomp[i].kaki2.node;
            Te=arrKomp[i].kaki3.node;
        }else if(strcmp(arrKomp[i].nama,"J3")==0){
        	vcc=arrKomp[i].kaki1.node;
        }
    }

    for(int j=0;j<40;j++){
        for(int i=0;i<40;i++){
            if(node[i][j]==vin){
                node[i][j]='i';
            }else if(node[i][j]==vout){
                node[i][j]='o';
            }else if(node[i][j]==Tc){
                node[i][j]='c';
            }else if(node[i][j]==Tb){
                node[i][j]='b';
            }else if(node[i][j]==Te){
                node[i][j]='e';
            }else if(node[i][j]==gnd){
                node[i][j]='g';
            }else if(node[i][j]==vcc){
            	node[i][j]='v';
            }
        }
    }
}

void cekDRC (komponen arrKomp[40],int jmlKomp){
    char drc[20],arr[40][40][5];
    int countX,countY,i,j,k,cek,benar;
    printf("\n[DRC]\n");
    printf("Masukkan File DRC (dalam format .txt): ");
    scanf("%s",&drc);
    FILE *fload;
    fload = fopen(drc, "r");
    char temp1[5],temp2[5];
    char data[100];
    char *token;
    const char s[2]= " ";
    //countX=0;
    countX=0;

    while (!(feof(fload)))
    {
        //ambil 1 baris data dari file
        fgets(data, 225, (FILE*) fload);
        //printf("%s\n",data);
        countY=0;
        //ambil token dari data yang dipisahkan oleh " "
        token = strtok(data, s);
        //ambil token sampai data 1 baris habis
        while (token != NULL)
        {
            //printf("%s\n",token);
            //token dimasukan ke array
            strcpy(arr[countX][countY], token);
            //ambil token berikutnya
            token = strtok(NULL, s);
            countY++;
        }
        countX++;
    }
    fclose(fload);
    cek=0;
    for (i=0;i<countX;i++){
        for (j=0;j<jmlKomp;j++){
            benar=strcmp(arr[i][0],arrKomp[j].nama);
            if (benar==0){
                for (k=1;k<countY;k++){
                    if (strcmp(arr[i][1],"Vin")==0 && arrKomp[j].kaki1.node=='i'){
                        cek=cek+1;
                    } else if (strcmp(arr[i][1],"Vin")==0 && arrKomp[j].kaki2.node=='i'){
                        cek=cek+1;
                    }
                    if (strcmp(arr[i][1],"Vout")==0 && arrKomp[j].kaki1.node=='o'){
                        cek=cek+1;
                    } else if (strcmp(arr[i][1],"Vout")==0 && arrKomp[j].kaki2.node=='o'){
                        cek=cek+1;
                    }
                    if (strcmp(arr[i][1],"GND")==0 && arrKomp[j].kaki1.node=='g'){
                        cek=cek+1;
                    } else if (strcmp(arr[i][1],"GND")==0 && arrKomp[j].kaki2.node=='g'){
                        cek=cek+1;
                    }
                    if (strcmp(arr[i][1],"Tb")==0 && arrKomp[j].kaki1.node=='b'){
                        cek=cek+1;
                    } else if (strcmp(arr[i][1],"Tb")==0 && arrKomp[j].kaki2.node=='b'){
                        cek=cek+1;
                    } else if (strcmp(arr[i][1],"Tb")==0 && arrKomp[j].kaki3.node=='b'){
                    	cek=cek+1;
                    }
                    if (strcmp(arr[i][1],"Tc")==0 && arrKomp[j].kaki1.node=='c'){
                        cek=cek+1;
                    } else if (strcmp(arr[i][1],"Tc")==0 && arrKomp[j].kaki2.node=='c'){
                        cek=cek+1;
                    } else if (strcmp(arr[i][1],"Tc")==0 && arrKomp[j].kaki3.node=='c'){
                    	cek=cek+1;
                    }
                    if (strcmp(arr[i][1],"Te")==0 && arrKomp[j].kaki1.node=='e'){
                        cek=cek+1;
                    } else if (strcmp(arr[i][1],"Te")==0 && arrKomp[j].kaki2.node=='e'){
                        cek=cek+1;
                    } else if (strcmp(arr[i][1],"Te")==0 && arrKomp[j].kaki3.node=='e'){
                    	cek=cek+1;
                    }
                    if (strcmp(arr[i][1],"Vcc")==0 && arrKomp[j].kaki1.node=='v'){
                        cek=cek+1;
                    } else if (strcmp(arr[i][1],"Vcc")==0 && arrKomp[j].kaki2.node=='v'){
                        cek=cek+1;
                    }
                }
            }
        }
    }
    printf("\n%d/%d Rule is Checked\n",(cek/2),countX);
}

void tampilkanRouting (char routing[40][40],int N, int M){
    printf("\n[Layout Rangkaian pada PCB Dot Matriks]\n");
    printf(" ");
    for (int k=1;k<=N;k++){
            printf("%d\t",k);
    }
    printf("\n");
    for(int j=0;j<M;j++){
        printf("%d ",j+1);
        for(int i=0;i<N;i++){
            printf("%c\t",routing[i][j]);
        }
        printf("\n");
    }
}

void menu(){
    printf("Menu:\n");
    printf("\t1. Buat Proyek Baru\n");
    printf("\t2. Muat Proyek dari Berkas\n" );
    printf("\t3. Keluar\n");
    printf("Masukkan: ");
}

void menuUtama(){
    printf("\n[Menu utama]");
    printf("\nPilih Mode:\n");
    printf("\t1.Tampilkan Layout\n");
    printf("\t2.Layouting Manual\n");
    printf("\t3.Tampilkan Routing\n");
    printf("\t4.Routing Manual\n");
    printf("\t5.Layouting Otomatis\n");
    printf("\t6.Routing Otomatis\n");
    printf("\t7.Design Rule Checker\n");
    printf("\t8.Simpan Proyek dan Keluar\n");
    printf("Pilih Mode: ");
}

void saveFile(char nFileL[], int N, int M, char arrL[40][40][4], char arrR[40][40]) {
    //Membuat format file yang akan dibuat
    char fLayout[12];
    strcpy(fLayout, "_layout.csv");
    char fRouting[13];
    strcpy(fRouting, "_routing.csv");
    //Menggabungkan input nama file dengan format di atas
    char nFileR [200];
    strcpy(nFileR, nFileL);
    strcat(nFileL, fLayout);
    strcat(nFileR, fRouting);
    //save file dengan memindahkan array ke file yang diinginkan
    createFile(nFileL, nFileR, N, M, arrL, arrR);
    printf("\n");
    printf("Layout disimpan dalam berkas %s\n", nFileL);
    printf("Routing disimpan dalam berkas %s\n", nFileR);
}

void createFile(char nFile_L[], char nFile_R[], int M, int N, char arr_L[40][40][4], char arr_R[40][40]) {
    int i, j;
    FILE*fsaveL;
    fsaveL = fopen(nFile_L, "w");
    FILE*fsaveR;
    fsaveR = fopen(nFile_R, "w");
    for(i=0; i<N; i++)
    {
        for(j=0; j<M; j++)
        {
            if (j!=(M-1))
            {
                fprintf(fsaveL, "%s,", arr_L[j+1][i+1]);
                fprintf(fsaveR, "%c,", arr_R[j][i]);
            }
            else
            {
                fprintf(fsaveL, "%s\n", arr_L[j+1][i+1]);
                fprintf(fsaveR, "%c\n", arr_R[j][i]);
            }
        }
    }
    fclose(fsaveR);
    fclose(fsaveL);
}

void loadFile(char nFileL[], char arrL[40][40][4], char arrR[40][40], int *N, int *M) {
    //Membuat format file yang akan dibuat
    char fLayout[12];
    strcpy(fLayout, "_layout.csv");
    char fRouting[13];
    strcpy(fRouting, "_routing.csv");
    //Menggabungkan input nama file dengan format di atas
    char nFileR [200];
    strcpy(nFileR, nFileL);
    strcat(nFileL, fLayout);
    strcat(nFileR, fRouting);
    getArr(nFileL, nFileR, N, M, arrL, arrR);
}

void getArr(char nFile_L[], char nFile_R[], int *j, int *i, char arr_L[40][40][4], char arr_R[40][40]) {
    FILE *floadL;
    floadL = fopen(nFile_L, "r");
    FILE *floadR;
    floadR = fopen(nFile_R, "r");
    char temp[]= " ";
    char dataL[100];
    char *dataR[100];
    char *tokenL;
    char *tokenR;


    //load file : memasukan data dari file ke array layout
    printf("Mengambil data dari %s .....\n", nFile_L);
    int c;
    //ambil 1 baris data dari file
/*	do
    {
    	c=0;
    	*j=0;
    	*i=0;
    	fscanf(floadL,"%s", dataL);
    	printf("[%s]\n", dataL);
	    while (dataL[*i] != NULL)
	    {
	    	printf("ok1\n");
	    	if (dataL[*i] == ',')
	    		c++;
	    	printf("c = %d\n", c);
	    	*i = *i + 1;
	    }
	    if (c==1)
	    {
	    	//ambil token dari data yang dipisahkan oleh ","
        	tokenL = strtok(dataL, ",");
        	/*printf("<%s> {%s}\n",tokenL,dataL);
       		//ambil token sampai data 1 baris habis
	        if (tokenL != NULL)
	        {
	            //token dimasukan ke array
	            strcpy(arr_L[*i][*j] ,tokenL);
	            /*printf("[%s]\n",arr_L[*i][*j]);
	            //ambil token berikutnya
	            tokenL = strtok(NULL, ",");
	            *j = *j + 1;
	        }
	        strcpy(arr_L[*i][*j] , " ");
	        printf("[%s]\n",arr_L[*i][*j]);
	    }

	} while (c==1);*/

    *i=0;
    c=0;
    int k=0;
    *j=0;
    fgets(dataL ,40, floadL);
//    printf("[%s]\n", dataL);
    while (dataL[k] != NULL)
	{
//	    printf("ok1\n");
	    if (dataL[k] == ',')
	    	c++;
//	    printf("c = %d\n", c);
	    k++;
	}

    while (strlen(dataL)>1)
    {
        //*j=0;
        //ambil token dari data yang dipisahkan oleh ","
        tokenL = strtok(dataL, ",");
        /*printf("<%s> {%s}\n",tokenL,dataL);*/
        //ambil token sampai data 1 baris habis
        //while (tokenL != NULL)
        for(*j=0; *j<=c; *j=*j+1)
        {
            //token dimasukan ke array
            if (tokenL == NULL)
            	strcpy(arr_L[*j][*i] ," ");
            else
            	strcpy(arr_L[*j][*i] ,tokenL);
//            printf("%d.[%s]\n",*i, arr_L[*j][*i]);
            //ambil token berikutnya
            tokenL = strtok(NULL, ",");
        }
        fgets(dataL ,40, floadL);
//    	printf("[%s]\n", dataL);
        *i = *i + 1;
    }

    int cb= *i;
//    printf("cb= %d", cb);


    //load file : memasukan data dari file ke array routing
    printf("Mengambil data dari %s .....\n", nFile_R);
    *i=0;
    fgets(dataR ,40, floadR);
//    printf("[%s]\n", dataR);
    //fscanf(floadR, "%s", dataR);
    //while (!(feof(floadR)))
    for (*i=0; *i<cb; *i=*i+1)
    {
        //*j=0;
        //ambil token dari data yang dipisahkan oleh ","
        tokenR = strtok(dataR, ",");
        //ambil token sampai data 1 baris habis
        //while (tokenR != NULL)
        for (*j=0; *j<=c; *j=*j+1)
        {
            //token dimasukan ke array
            arr_R[*j][*i] = *tokenR;
//            printf("%d.[%c]\n",*j, arr_R[*j][*i]);
            //ambil token berikutnya
            tokenR = strtok(NULL, ",");
            //*j = *j + 1;
        }
        //ambil 1 baris data dari file
        fgets(dataR ,40, floadR);
//    	printf("[%s]\n", dataR);//fscanf(floadR, "%s", dataR);
        //*i = *i + 1;
    }

    fclose(floadR);
    fclose(floadL);
}
