#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>



// TEXT FONKSIYONLARI:

void x1(){
    printf("  *   *  ");
}
void x2(){
    printf("   * *   ");
}
void x3(){
    printf("    *    ");
}


void o1(){
    printf("   ***   ");
}
void o2(){
    printf("  *   *  ");
}


// GLobal Fonksiyon:
char matris[3][3];  // matrislere bir şey yazdırılmadığı sürecek NULL karakterini gösterecek (Decimal:0)


void yazdirma();
void matris_yazidrma(int konun,char karakter);
int kontrol();

int main(){

    int x,y;
    for (x=0;x<3;x++){
        for (y=0;y<3;y++){
            matris[x][y] = 32;
        }
    }


    printf("\n\nOyuna hosgeldiniz. Lutfen herhangi bir tusa basiniz.\n");
    getchar();
    printf("\n");


    printf(" ----------------------------- \n");
    printf("|         |         |         |\n");
    printf("|         |         |         |\n");
    printf("|         |         |         |\n");
    printf("|         |         |         |\n");
    printf("|        1|        2|        3|\n");
    printf(" ----------------------------- \n");
    printf("|         |         |         |\n");
    printf("|         |         |         |\n");
    printf("|         |         |         |\n");
    printf("|         |         |         |\n");
    printf("|        4|        5|        6|\n");
    printf(" ----------------------------- \n");
    printf("|         |         |         |\n");
    printf("|         |         |         |\n");
    printf("|         |         |         |\n");
    printf("|         |         |         |\n");
    printf("|        7|        8|        9|\n");
    printf(" ----------------------------- \n");


    int i;
    int konum1,konum2;
    int kontrol_sonuc;
    char karakter1 = 'x';
    char karakter2 = 'o';

    for (i=0;i<4;i++){
        printf("\nIlk oyuncu karakterini nereye yazacak: ");
        scanf("%d", &konum1);
        matris_yazidrma(konum1, karakter1); // x
        yazdirma(matris);

        kontrol_sonuc = kontrol();
        if (kontrol_sonuc == 1){
            printf("\n\n\tOyunu x kazandı\n\n");
            return 0;
        }
        else if (kontrol_sonuc == 2){
            printf("\n\n\tOyunu o kazandı\n\n");
            return 0;
        }


        printf("\nIkıncı oyuncu karakterini nereye yazacak: ");
        scanf("%d", &konum2);
        matris_yazidrma(konum2, karakter2); // o
        yazdirma(matris);

        kontrol_sonuc = kontrol();
        if (kontrol_sonuc == 1){
            printf("\n\n\tOyunu x kazandı\n\n\n");
            return 0;
        }
        else if (kontrol_sonuc == 2){
            printf("\n\n\tOyunu o kazandı\n\n\n");
            return 0;
        }
    }
    printf("\nIlk oyuncu karakterini nereye yazacak: ");
    scanf("%d", &konum1);
    matris_yazidrma(konum1, karakter1);
    yazdirma(matris);

    kontrol_sonuc = kontrol();
    if (kontrol_sonuc == 1){
        printf("\n\n\tOyunu x kazandı\n\n\n");
        return 0;
    }
    else if (kontrol_sonuc == 2){
        printf("\n\n\tOyunu o kazandı\n\n\n");
        return 0;
    }


    printf("\nOyunu kazanan olmadi\n\n");


    return 0;
}



int kontrol(){
    // 3 satır kontrol
    // 3 sütun kontrol
    // 2 çapraz kontrol

    int sayi_matris[3][3];
    int i;

    for (i=0;i<3;i++){
        for (int j=0;j<3;j++){
            sayi_matris[i][j] = matris[i][j];
        }
    }

    // 3 satır kontrol
    for (i=0;i<3;i++){ // satir kontrol
        //printf("\n %c  %c  %c",sayi_matris[i][0], sayi_matris[i][1], sayi_matris[i][2]);

        if (sayi_matris[i][0] == sayi_matris[i][1]) {
            if (sayi_matris[i][1] == sayi_matris[i][2]) {
                //printf("\nBuraya girdi 1");

                if (sayi_matris[i][0] != 32 && sayi_matris[i][1] != 32 && sayi_matris[i][2] != 32) {
                    // kazanan var !!!
                    //printf("\n\n! Kazanan var SATIR !\n\n");

                    if (sayi_matris[i][0] == 'x') {
                        return 1; // kazanan x
                    }
                    if (sayi_matris[i][0] == 'o'){
                        return 2; // kazanan o
                    }
                }
            }
        }
    }

    // 3 sütun kontrol
    for (i=0;i<3;i++){
        //printf("\n %c %c %c \n",sayi_matris[0][i], sayi_matris[1][i], sayi_matris[2][i]);

        if (sayi_matris[0][i] == sayi_matris[1][i]){
            if (sayi_matris[1][i] == sayi_matris[2][i]){
                if (sayi_matris[0][i] != 32 && sayi_matris[1][i] != 32 && sayi_matris[2][i] != 32) {
                    // kazanan var !!!
                    //printf("\n\n! Kazanan var SUTUN !\n\n");

                    if (sayi_matris[0][i] == 'x') {
                        return 1; // kazanan x
                    }
                    if (sayi_matris[0][i] == 'o'){
                        return 2; // kazanan o
                    }
                }
            }
        }
    }

    // 2 capraz kontrol
    if (sayi_matris[0][0] == sayi_matris[1][1]){
        if (sayi_matris[1][1] == sayi_matris[2][2]) {
            if (sayi_matris[0][0] != 32 && sayi_matris[1][1] != 32 && sayi_matris[2][2] != 32) {
                // kazanan var !!!
                //printf("\n\n! Kazanan var CAPRAZ-SOL !\n\n");

                if (sayi_matris[0][0] == 'x') {
                    return 1; // kazanan x
                }
                if (sayi_matris[0][0] == 'o'){
                    return 2; // kazanan o
                }
            }
        }
    }

    // 2 capraz kontrol
    if (sayi_matris[0][2] == sayi_matris[1][1]){
        if (sayi_matris[1][1] == sayi_matris[2][0]) {
            if (sayi_matris[0][2] != 32 && sayi_matris[1][1] != 32 && sayi_matris[2][0] != 32) {
                // kazanan var !!!
                //printf("\n\n! Kazanan var CAPRAZ-SAG !\n\n");

                if (sayi_matris[0][2] == 'x') {
                    return 1; // kazanan x
                }
                if (sayi_matris[0][2] == 'o'){
                    return 2; // kazanan o
                }
            }
        }
    }


    return 0;
}








void matris_yazidrma(int konum,char karakter){
    int mod,bolum;
    mod = konum %3;
    bolum = konum /3;

    if (mod == 0){
        matris[bolum-1][2] = karakter;
    }
    else {
        matris[bolum][mod-1] = karakter;
    }
}



void yazdirma(){
    int a,b;
    int i,j;
    int kutu_no=1;

    printf("\n\n ----------------------------- \n");

    a=0;
    for (i=0;i<3;i++){

        b=0;
        for (j=0;j<3;j++){ // 1. satır
            printf("|");
            if (matris[a][b] == 'x') {
                x1();
            } else if (matris[a][b] == 'o') {
                o1();
            } else if (matris[a][b] == 0 || matris[a][b] == 16 || matris[a][b] == 32){
                printf("         ");
            }
            b++;
        }
        printf("|\n");

        b=0;
        for (j=0;j<3;j++){ // 2. satır
            printf("|");
            if (matris[a][b] == 'x') {
                x2();
            } else if (matris[a][b] == 'o') {
                o2();
            } else if (matris[a][b] == 0 || matris[a][b] == 16 || matris[a][b] == 32){
                printf("         ");
            }
            b++;
        }
        printf("|\n");

        b=0;
        for (j=0;j<3;j++){ // 3. satır
            printf("|");
            if (matris[a][b] == 'x') {
                x3();
            } else if (matris[a][b] == 'o') {
                o2();
            } else if (matris[a][b] == 0 || matris[a][b] == 16 || matris[a][b] == 32){
                printf("         ");
            }
            b++;
        }
        printf("|\n");

        b=0;
        for (j=0;j<3;j++){ // 4. satır
            printf("|");
            if (matris[a][b] == 'x') {
                x2();
            } else if (matris[a][b] == 'o') {
                o2();
            } else if (matris[a][b] == 0 || matris[a][b] == 16 || matris[a][b] == 32){
                printf("         ");
            }
            b++;
        }
        printf("|\n");

        b=0;
        for (j=0;j<3;j++){ // 5. satır
            printf("|");
            if (matris[a][b] == 'x') {
                printf("  *   * %d",kutu_no);
            }
            else if (matris[a][b] == 'o') {
                printf("   ***  %d",kutu_no);
            }
            else if (matris[a][b] == 0 || matris[a][b] == 16 || matris[a][b] == 32){
                printf("        %d",kutu_no);
            }
            b++;
            kutu_no++;
        }
        printf("|\n");
        printf(" ----------------------------- \n");
        a++;
    }

}






