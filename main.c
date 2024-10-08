#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <unistd.h>



// TEXT FONKSIYONLARI:

void x1(void){
    printf("  *   *  ");
}
void x2(void){
    printf("   * *   ");
}
void x3(void){
    printf("    *    ");
}


void o1(void){
    printf("   ***   ");
}
void o2(void){
    printf("  *   *  ");
}


// Global Fonksiyonlar:
char matris[3][3];  // matrislere bir şey yazdırılmadığı sürecek NULL karakterini gösterecek (Decimal:0)
int matris_doluluk[10]; // dolu olan matrislerin yerine 1 yazılacak. Boş olan yerlerde 0.
// matris_doluluk dizisinin 0. indisi boş. 1. indisten başlayarak dolduruluyor.
int matris_bos=0;
char karakter_secim;
char pc_karakter;
int baslayan; // 1 ise bilgisayar, 2 ise oyuncu başlayacak


void yazdirma(void);
void matris_yazidirma(int konum,char karakter);
int kontrol(void);
int matris_doluluk_kontrol(int konum);
int basit_yapay_zeka(void);

int main(){
    srand(time(NULL));

    int x,y;
    for (x=0;x<3;x++){
        for (y=0;y<3;y++){
            matris[x][y] = 32;
        }
    }
    for (x=1;x<10;x++){
        matris_doluluk[x] = 0;
    }


    printf("\n\nOyuna hosgeldiniz. Lutfen ENTER'a basiniz.\n CapsLock'un kapali oldugundan emin oldun.\n");
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


    int i,secim;
    int konum1,konum2;
    int kontrol_sonuc;
    char karakter1 = 'x';
    char karakter2 = 'o';


    printf("\n\n[1] Bilgisayara Karsi\n");
    printf("[2] Cift Kisilik");
    printf("\n Oyun modunu seciniz: ");
girdi:
    scanf("%d",&secim);

    // ------------ Iki kisilik oyun algoritmasi ------------
    if (secim == 2){
        getchar();
        for (i=0;i<4;i++){
girdi3:
            printf("\nIlk oyuncu karakterini nereye yazacak: ");
            scanf("%d", &konum1);
            if (konum1 < 1 || konum1 > 9) {
                printf("\nHatali giris!\nLütfen tekrar giriniz.\n");
                goto girdi3;
            }
            
            if (matris_doluluk_kontrol(konum1) == 1){
                printf("\nBu hucre dolu. Tekrar giriniz: ");
                goto girdi3;
            }
            matris_doluluk[konum1] = 1;
            matris_yazidirma(konum1, karakter1); // x
            yazdirma();

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
            girdi4:
            scanf("%d", &konum2);
            if (matris_doluluk_kontrol(konum2) == 1){
                printf("\nBu hucre dolu. Tekrar giriniz: ");
                goto girdi4;
            }
            matris_doluluk[konum2] = 1;
            matris_yazidirma(konum2, karakter2); // o
            yazdirma();

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
        girdi5:
        scanf("%d", &konum1);
        if (matris_doluluk_kontrol(konum1) == 1){
            printf("\nBu hucre dolu. Tekrar giriniz: ");
            goto girdi5;
        }
        matris_doluluk[konum1] = 1;
        matris_yazidirma(konum1, karakter1);
        yazdirma();

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

        // ------------ Bilgisayara karşı oyun algoritması ------------
    else if (secim == 1){
        getchar();
        // bilgisayara karşı oynama algoritması:
        printf("\n\tHangi karakter ile oynamak istersiniz [X/O]: ");
        girdi2:
        scanf("%c",&karakter_secim);
        if (karakter_secim != 'x'){
            if (karakter_secim != 'o'){
                printf("\n\nYanlis karakter girdiniz! Tekrar deneyiniz: ");
                getchar();
                goto girdi2; // 6 satır yukarı gönderiyor.
            }
        }
        if (karakter_secim == 'x') pc_karakter = 'o';
        else if (karakter_secim == 'o') pc_karakter = 'x';
        else printf("\n\nPROGRAMDA HATA VAR SATIR 180-190\n\n");

        baslayan = rand()%2+1; // 1 veya 2 atanacak.
        if (baslayan == 1) printf("\n\n\tBilgisayar baslayacak.\n");
        else if (baslayan == 2) printf("\n\n\tSiz baslayacaksiniz.\n");
        else{
            printf("\n\nBURADA BİR HATA VAR - SATIR 150-160\n\n");
            return 0;
        }

        // Baslayan belirlendi ve kaydedildi. "baslayan" değişkeninde [1/2] [pc/oyuncu]

//----------------------------------------------------------------------------------------------------------------------
        // OYUN BASLATILIYOR:
        if (baslayan == 2){

            for (i=0;i<5;i++){ // ilk olarak kullanıcı başlayacak (konum2->kullanıcı konum1->pc)
                printf("\n\n\t\tKULLANICI BASLAYACAK BLOK'UNA GİRDİ\n\n");

                matris_bos++;

                girdi9:
                printf("\n\nKarakterinizi nereye yazacaksiniz: ");
                scanf("%d",&konum2);
                if (matris_doluluk_kontrol(konum2) == 1){
                    printf("\n\nKARAKTERİNİZİ DOLU BİR YERE YAZMAYA CALISTINIZ. \nLutfen tekrar deneyiniz.\n");
                    goto girdi9;
                }

                matris_doluluk[konum2] = 1;
                matris_yazidirma(konum2,karakter_secim);
                yazdirma();
                kontrol_sonuc = kontrol();
                // kazandınız veya kaybettiniz yazdıracak !
                if (kontrol_sonuc == 1 && karakter_secim == 'x'){
                    printf("\n\n\t Oyunu siz kazandiniz !\n\n");
                    return 0;
                }
                else if (kontrol_sonuc == 1 && karakter_secim == 'o'){
                    printf("\n\n\t Kaybettiniz !\n\n");
                    return 0;
                }
                else if (kontrol_sonuc == 2 && karakter_secim == 'x'){
                    printf("\n\n\t Kaybettiniz !\n\n");
                    return 0;
                }
                else if (kontrol_sonuc == 2 && karakter_secim == 'o'){
                    printf("\n\n\t Oyunu siz kazandiniz !\n\n");
                    return 0;
                }// kazanan kontrolü bitti.
                // burdan sonrasına bilgisayar algoritması yazılacak

                // ------------------------------------------------------------

                /* BİLGİSAYAR KONUM1'e KONUM BİLDİRİSİ YAPACAK */
                int hata_sayac = 0;

                girdi6:
                konum1 = basit_yapay_zeka();
                if (matris_doluluk_kontrol(konum1) == 1){ // matris dolu ise
                    matris_bos--;
                    printf("\n\nPROGRAMDA HATA VAR. DOLU YERE PC KARAKTER YAZMAYA CALISTI\n");
                    printf("Bilgisayardan tekrar konum istenecek\n");
                    hata_sayac++;
                    if (matris_bos == 9){
                        printf("\n\nOYUN BITTI KAZANAN OLMADI\n\n");
                        return 0;
                    }
                    else if (hata_sayac <3) goto girdi6;
                    else {
                        printf("\n - BURAYA GİRDİ 13 - \n");
                        girdi7:
                        konum1 = rand()%9+1;
                        if (matris_doluluk[konum1] == 1){
                            goto girdi7;
                        }
                    }
                }
                matris_doluluk[konum1] = 1;
                matris_yazidirma(konum1,pc_karakter);
                yazdirma();
                kontrol_sonuc = kontrol();
                // Kazanan kontrol algoritması:
                if (kontrol_sonuc == 1 && pc_karakter == 'o'){
                    printf("\n\n\t Oyunu siz kazandiniz !\n\n");
                    return 0;
                }
                else if (kontrol_sonuc == 1 && pc_karakter == 'x'){
                    printf("\n\n\t Kaybettiniz !\n\n");
                    return 0;
                }
                else if (kontrol_sonuc == 2 && pc_karakter == 'o'){
                    printf("\n\n\t Kaybettiniz !\n\n");
                    return 0;
                }
                else if (kontrol_sonuc == 2 && pc_karakter == 'x'){
                    printf("\n\n\t Oyunu siz kazandiniz !\n\n");
                    return 0;
                }// kazanan kontrolü bitti.
                printf("\n------- satır 285'e geldi\n");
            }
        }

        else if (baslayan == 1){
            for (i=0;i<5;i++){ // ilk olarak pc başlayacak
                printf("\n\n\t\tPC BASLAYACAK BLOK'UNA GİRDİ\n\n");

                int hata_sayac=0;
                printf("\n\nBilgisayar karakterini yaziyor.\n\n");
                /* BİLGİSAYAR KONUM1'e KONUM BİLDİRİSİ YAPACAK */

                konum1 = basit_yapay_zeka();
                if (matris_doluluk_kontrol(konum1) == 1){ // matris dolu ise
                    //matris_bos--;
                    printf("\n\nPROGRAMDA HATA VAR. DOLU YERE PC KARAKTER YAZMAYA CALISTI\n");
                    printf("Bilgisayardan tekrar konum istenecek\n");
                    hata_sayac++;
                    if (matris_bos == 9){
                        printf("\n\nOYUN BITTI KAZANAN OLMADI\n\n");
                        return 0;
                    }
                    if (hata_sayac <3) goto girdi6;
                    else {
                        printf("\n - BURAYA GİRDİ 14 - \n");
                        girdi8:
                        konum1 = rand()%9+1;
                        if (matris_doluluk[konum1] == 1){
                            goto girdi8;
                        }
                    }
                }
                matris_doluluk[konum1] = 1;
                matris_yazidirma(konum1,pc_karakter);
                yazdirma();
                kontrol_sonuc = kontrol();

                // Kazanan kontrol algoritması:
                if (kontrol_sonuc == 1 && pc_karakter == 'o'){
                    printf("\n\n\t Oyunu siz kazandiniz !\n\n");
                    return 0;
                }
                else if (kontrol_sonuc == 1 && pc_karakter == 'x'){
                    printf("\n\n\t Kaybettiniz !\n\n");
                    return 0;
                }
                else if (kontrol_sonuc == 2 && pc_karakter == 'o'){
                    printf("\n\n\t Kaybettiniz !\n\n");
                    return 0;
                }
                else if (kontrol_sonuc == 2 && pc_karakter == 'x'){
                    printf("\n\n\t Oyunu siz kazandiniz !\n\n");
                    return 0;
                }
                // kazanan kontrolü bitti.

                // Kullanıcı aşamasına geçiliyor:..
                matris_bos++;
                girdi10:
                printf("\n\nKarakterini nereye yazacaksiniz: ");
                scanf("%d",&konum2);
                if (matris_doluluk_kontrol(konum2) == 1){
                    printf("\n\nKARAKTERİNİZİ DOLU BİR YERE YAZMAYA CALISTINIZ. \nLutfen tekrar deneyiniz.\n");
                    goto girdi10;
                }
                matris_doluluk[konum2] = 1;
                matris_yazidirma(konum2,karakter_secim);
                yazdirma();
                kontrol_sonuc = kontrol();

                // kazandınız veya kaybettiniz yazdıracak !
                if (kontrol_sonuc == 1 && karakter_secim == 'x'){
                    printf("\n\n\t Oyunu siz kazandiniz !\n\n");
                    return 0;
                }
                else if (kontrol_sonuc == 1 && karakter_secim == 'o'){
                    printf("\n\n\t Kaybettiniz !\n\n");
                    return 0;
                }
                else if (kontrol_sonuc == 2 && karakter_secim == 'x'){
                    printf("\n\n\t Kaybettiniz !\n\n");
                    return 0;
                }
                else if (kontrol_sonuc == 2 && karakter_secim == 'o'){
                    printf("\n\n\t Oyunu siz kazandiniz !\n\n");
                    return 0;
                }
                // kazanan kontrolü bitti.
            }
        }

        return 0;
    }



    else {
        printf("\nHatali giris yaptiniz. Lutfen tekrar deneyiniz: ");
        goto girdi;
    }

    return 0;
}




int basit_yapay_zeka(void){ // bilgisayar nereye harf koyacağına karar verdikten sonra oranın konumunu geriye döndürecek.
//  matris global değişken
    int i;

    for (i=1;i<10;i++){
        printf("%d ",matris_doluluk[i]);
    }
    printf("\nMatris_bos degiskeni: %d\n",matris_bos);


// Matris komple boş ise:
    if (matris_bos == 0){
        printf("\nBuraya girdi 1\n");
        matris_bos++;
        return rand()%9+1; // 1-9 arasında sayı üretecek. /random bir konum gönderiyor
    }

// Matriste 1 tane dolu yer var ise:
    else if (matris_bos == 1){
        matris_bos++;
        if (matris_doluluk[5] == 0){ // ortadaki hücre boş ise;
            printf("\nBuraya girdi 2\n");                           // 3'te 2 ihtimalle ortaya koyacak (boş ise)
            int anlik_karar = rand()%3+1; // 1 ile 3 arasında
            if (anlik_karar %2 == 1) return 5; // ortaya karakteri yazacak
            else return rand()%9+1;
        }
        else if (matris_doluluk[5] == 1){ // Ortadaki hücre dolu ise:
            return rand()%9+1; // Rastgele bir yere sayı yazacak
        }
    }

// matriste 2 hücre dolu ise:
    else if (matris_bos == 2){
        matris_bos++;
        // 1. hücrede kendi karakteri var ise:
        if (matris[0][0] == pc_karakter){
            if (matris_doluluk[5] == 0) return 5;
            else if (matris_doluluk[2] == 0) return 2;
            else if (matris_doluluk[4] == 0) return 4;
        }
            // 2. hücerede kendi elemanı var ise:
        else if (matris[0][1] == pc_karakter){
            if (matris_doluluk[5] == 0) return 5;
            else if (matris_doluluk[1] == 0) return 1;
            else if (matris_doluluk[3] == 0) return 3;
        }
            // 3. hücerede kendi elemanı var ise:
        else if (matris[0][2] == pc_karakter){
            if (matris_doluluk[5] == 0) return 5;
            else if (matris_doluluk[2] == 0) return 2;
            else if (matris_doluluk[6] == 0) return 6;
        }
            // 4. hücerede kendi elemanı var ise:
        else if (matris[1][0] == pc_karakter){
            if (matris_doluluk[5] == 0) return 5;
            else if (matris_doluluk[1] == 0) return 1;
        }
            // 5. hücerede kendi elemanı var ise:
        else if (matris[1][1] == pc_karakter){
            if (matris_doluluk[3] == 0) return 3;
            else if (matris_doluluk[1] == 0) return 1;
            else if (matris_doluluk[4] == 0) return 4;
            else if (matris_doluluk[2] == 0) return 2;
        }
            // 6. hücerede kendi elemanı var ise:
        else if (matris[1][2] == pc_karakter){
            if (matris_doluluk[5] == 0) return 5;
            else if (matris_doluluk[3] == 0) return 3;
            else if (matris_doluluk[9] == 0) return 9;
        }
            // 7. hücrede kendi elemanı var ise:
        else if (matris[2][0] == pc_karakter){
            if (matris_doluluk[5] == 0) return 5;
            else if (matris_doluluk[4] == 0) return 4;
            else if (matris_doluluk[8] == 0) return 8;
        }
            // 8. hücrede kendi elemanı var ise:
        else if (matris[2][1] == pc_karakter){
            if (matris_doluluk[5] == 0) return 5;
            else if (matris_doluluk[7] == 0) return 7;
            else if (matris_doluluk[9] == 0) return 9;
        }
            // 9. hücrede kendi elemanı var ise:
        else if (matris[2][2] == pc_karakter){
            if (matris_doluluk[5] == 0) return 5;
            else if (matris_doluluk[8] == 0) return 8;
            else if (matris_doluluk[6] == 0) return 6;
        }
    }




// matriste 3 hücre dolu ise:
    else if (matris_bos >= 3){
        matris_bos++;
        printf("\nBURAYA GİRDİ 3\n");

        // 1. hücrede kendi karakteri var ise:
        if (matris[0][0] == pc_karakter){
            if (matris[2][2] == pc_karakter){
                if (matris_doluluk[5] == 0) return 5;
            }
            else if (matris[0][1] == pc_karakter){
                if (matris_doluluk[3] == 0) return 3;
            }
            else if (matris[1][0] == pc_karakter){
                if (matris_doluluk[7] == 0) return 7;
            }
            else if (matris[1][1] == pc_karakter){
                if (matris_doluluk[9] == 0) return 9;
            }
            else if (matris[0][2] == pc_karakter){ // ||
                if (matris_doluluk[2] == 0) return 2;
            }
            else if (matris[2][0] == pc_karakter){
                if (matris_doluluk[4] == 0) return 4;
            }
            /*
            else if (matris_doluluk[5] == 0) return 5;
            else if (matris_doluluk[4] == 0) return 4;
            else if (matris_doluluk[2] == 0) return 2;
            else return rand()%9+1;
            */
        }
            // 2. hücerede kendi elemanı var ise:
        else if (matris[0][1] == pc_karakter){
            if (matris[2][1] == pc_karakter){
                if (matris_doluluk[5] == 0) return 5;
            }
            else if (matris[0][0] == pc_karakter){
                if (matris_doluluk[3] == 0) return 3;
            }
            else if (matris[0][2] == pc_karakter){
                if (matris_doluluk[1] == 0) return 1;
            }
            else if (matris[1][1] == pc_karakter){
                if (matris_doluluk[8] == 0) return 8;
            }
            /*
            else if (matris_doluluk[5] == 0) return 5;
            else if (matris_doluluk[1] == 0) return 1;
            else if (matris_doluluk[3] == 0) return 3;
            else return rand()%9+1;
            */
        }
            // 3. hücerede kendi elemanı var ise:
        else if (matris[0][2] == pc_karakter){
            if (matris[2][0] == pc_karakter){
                if (matris_doluluk[5] == 0) return 5;
            }
            else if (matris[0][0] == pc_karakter){
                if (matris_doluluk[2] == 0) return 2;
            }
            else if (matris[0][1] == pc_karakter){
                if (matris_doluluk[1] == 0) return 1;
            }
            else if (matris[1][1] == pc_karakter) {
                if (matris_doluluk[7] == 0) return 7;
            }
            else if (matris[1][2] == pc_karakter){
                if (matris_doluluk[9] == 0) return 9;
            }
            else if (matris[2][2] == pc_karakter){
                if (matris_doluluk[6] == 0) return 6;
            }
            /*
            else if (matris_doluluk[5] == 0) return 5;
            else if (matris_doluluk[2] == 0) return 2;
            else if (matris_doluluk[6] == 0) return 6;
            else return rand()%9+1;
            */
        }
            // 4. hücerede kendi elemanı var ise:
        else if (matris[1][0] == pc_karakter){
            if (matris[1][1] == pc_karakter){
                if (matris_doluluk[6] == 0) return 6;
            }
            else if (matris[1][2] == pc_karakter){
                if (matris_doluluk[5] == 0) return 5;
            }
            else if (matris[0][0] == pc_karakter){
                if (matris_doluluk[7] == 0) return 7;
            }
            else if (matris[2][0] == pc_karakter){
                if (matris_doluluk[1] == 0) return 1;
            }
            /*
            else if (matris_doluluk[5] == 0) return 5;
            else if (matris_doluluk[1] == 0) return 1;
            else if (matris_doluluk[7] == 0) return 7;
            else return rand()%9+1;
            */
        }
            // 5. hücerede kendi elemanı var ise:
        else if (matris[1][1] == pc_karakter){
            if (matris[0][0] == pc_karakter){
                if (matris_doluluk[9] == 0) return 9;
            }
            else if (matris[2][2] == pc_karakter){
                if (matris_doluluk[1] == 0) return 1;
            }
            else if (matris[0][2] == pc_karakter){
                if (matris_doluluk[7] == 0) return 7;
            }
            else if (matris[2][0] == pc_karakter){
                if (matris_doluluk[3] == 0) return 3;
            }
            else if (matris[0][1] == pc_karakter){
                if (matris_doluluk[8] == 0) return 8;
            }
            else if (matris[2][1] == pc_karakter){
                if (matris_doluluk[2] == 0) return 2;
            }
            else if (matris[1][0] == pc_karakter){
                if (matris_doluluk[6] == 0) return 6;
            }
            else if (matris[1][2] == pc_karakter){
                if (matris_doluluk[4] == 0) return 4;
            }
            /*
            else if (matris_doluluk[7] == 0) return 7;
            else if (matris_doluluk[4] == 0) return 4;
            else if (matris_doluluk[9] == 0) return 9;
            else if (matris_doluluk[8] == 0) return 8;
            else if (matris_doluluk[6] == 0) return 6;
            else if (matris_doluluk[3] == 0) return 3;
            else if (matris_doluluk[1] == 0) return 1;
            else if (matris_doluluk[2] == 0) return 2;
            else printf("\nBOS YER YOK - SATIR 509\n");
            */
        }
            // 6. hücerede kendi elemanı var ise:
        else if (matris[1][2] == pc_karakter){
            if (matris[0][2] == pc_karakter){
                if (matris_doluluk[9] == 0) return 9;
            }
            else if (matris[2][2] == pc_karakter){
                if (matris_doluluk[3] == 0) return 3;
            }
            else if (matris[1][0] == pc_karakter){
                if (matris_doluluk[5] == 0) return 5;
            }
            else if (matris[1][1] == pc_karakter){
                if (matris_doluluk[4] == 0) return 4;
            }
            /*
            else if (matris_doluluk[5] == 0) return 5;
            else if (matris_doluluk[3] == 0) return 3;
            else if (matris_doluluk[9] == 0) return 9;
            else return rand()%9+1;
            */
        }
            // 7. hücrede kendi elemanı var ise:
        else if (matris[2][0] == pc_karakter){
            if (matris[1][1] == pc_karakter){
                if (matris_doluluk[3] == 0) return 3;
            }
            else if (matris[0][2] == pc_karakter){
                if (matris_doluluk[5] == 0) return 5;
            }
            else if (matris[0][0] == pc_karakter){
                if (matris_doluluk[4] == 0) return 4;
            }
            else if (matris[1][0] == pc_karakter){
                if (matris_doluluk[1] == 0) return 1;
            }
            else if (matris[2][1] == pc_karakter){
                if (matris_doluluk[9] == 0) return 9;
            }
            else if (matris[2][2] == pc_karakter){
                if (matris_doluluk[8] == 0) return 8;
            }
            /*
            else if (matris_doluluk[5] == 0) return 5;
            else if (matris_doluluk[4] == 0) return 4;
            else if (matris_doluluk[8] == 0) return 8;
            else return rand()%9+1;
            */
        }
            // 8. hücrede kendi elemanı var ise:
        else if (matris[2][1] == pc_karakter){
            if (matris[0][1] == pc_karakter){
                if (matris_doluluk[5] == 0) return 5;
            }
            else if (matris[1][1] == pc_karakter){
                if (matris_doluluk[2] == 0) return 2;
            }
            else if (matris[2][0] == pc_karakter){
                if (matris_doluluk[9] == 0) return 9;
            }
            else if (matris[2][2] == pc_karakter){
                if (matris_doluluk[7] == 0) return 7;
            }
            /*
            else if (matris_doluluk[5] == 0) return 5;
            else if (matris_doluluk[7] == 0) return 7;
            else if (matris_doluluk[9] == 0) return 9;
            else return rand()%9+1;
            */
        }
            // 9. hücrede kendi elemanı var ise:
        else if (matris[2][2] == pc_karakter){
            if (matris[0][0] == pc_karakter){
                if (matris_doluluk[5] == 0) return 5;
            }
            else if (matris[1][1] == pc_karakter){
                if (matris_doluluk[1] == 0) return 1;
            }
            else if (matris[2][0] == pc_karakter){
                if (matris_doluluk[8] == 0) return 8;
            }
            else if (matris[2][1] == pc_karakter){
                if (matris_doluluk[7] == 0) return 7;
            }
            else if (matris[0][2] == pc_karakter){
                if (matris_doluluk[6] == 0) return 6;
            }
            else if (matris[1][2] == pc_karakter){
                if (matris_doluluk[3] == 0) return 3;
            }
            /*
            else if (matris_doluluk[5] == 0) return 5;
            else if (matris_doluluk[8] == 0) return 8;
            else if (matris_doluluk[6] == 0) return 6;
            else return rand()%9+1;
            */
        }
        else {
            printf("\n\nRandom fonksiyonuna girdi.\n");
            return rand()%9+1;
        }
    }







//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
    // Karşı koyma algoritması:

    if (baslayan == 2 && matris_bos >= 3){ // ilk once kullanıcı başlıyor ise
        if (matris[0][0] == karakter_secim){
            if (matris[0][1] == karakter_secim){
                if (matris_doluluk[3] == 0) return 3;
            }
            else if (matris[1][0] == karakter_secim){
                if (matris_doluluk[7] == 0) return 7;
            }
            else if (matris[1][1] == karakter_secim){
                if (matris_doluluk[9] == 0) return 9;
            }
            else if (matris[0][2] == karakter_secim){
                if (matris_doluluk[2] == 0) return 2;
            }
            else if (matris[2][0] == karakter_secim){
                if (matris_doluluk[4] == 0) return 4;
            }
            else if (matris[2][2] == karakter_secim){
                if (matris_doluluk[5] == 0) return 5;
            }
            else;
        }
        else if (matris[0][1] == karakter_secim){
            if (matris[0][0] == karakter_secim){
                if (matris_doluluk[3] == 0) return 3;
            }
            else if (matris[0][2] == karakter_secim){
                if (matris_doluluk[1] == 0) return 1;
            }
            else if (matris[1][1] == karakter_secim){
                if (matris_doluluk[8] == 0) return 8;
            }
            else if (matris[2][1] == karakter_secim){
                if (matris_doluluk[5] == 0) return 5;
            }
            else;
        }
        else if (matris[0][2] == karakter_secim){
            if (matris[0][0] == karakter_secim){
                if (matris_doluluk[2] == 0) return 2;
            }
            else if (matris[0][1] == karakter_secim){
                if (matris_doluluk[1] == 0) return 1;
            }
            else if (matris[1][1] == karakter_secim){
                if (matris_doluluk[7] == 0) return 7;
            }
            else if (matris[2][0] == karakter_secim){
                if (matris_doluluk[5] == 0) return 5;
            }
            else if (matris[1][2] == karakter_secim){
                if (matris_doluluk[9] == 0) return 9;
            }
            else if (matris[2][2] == karakter_secim){
                if (matris_doluluk[6] == 0) return 6;
            }
            else;
        }
        else if (matris[1][0] == karakter_secim){
            if (matris[0][0] == karakter_secim){
                if (matris_doluluk[7] == 0) return 7;
            }
            else if (matris[2][0] == karakter_secim){
                if (matris_doluluk[1] == 0) return 1;
            }
            else if (matris[1][1] == karakter_secim){
                if (matris_doluluk[6] == 0) return 6;
            }
            else if (matris[1][2] == karakter_secim){
                if (matris_doluluk[5] == 0) return 5;
            }
            else;
        }
        else if (matris[1][1] == karakter_secim){
            if (matris[0][0] == karakter_secim){
                if (matris_doluluk[9] == 0) return 9;
            }
            else if (matris[2][2] == karakter_secim){
                if (matris_doluluk[1] == 0) return 1;
            }
            else if (matris[0][1] == karakter_secim){
                if (matris_doluluk[8] == 0) return 8;
            }
            else if (matris[2][1] == karakter_secim){
                if (matris_doluluk[2] == 0) return 2;
            }
            else if (matris[0][2] == karakter_secim){
                if (matris_doluluk[7] == 0) return 7;
            }
            else if (matris[2][0] == karakter_secim){
                if (matris_doluluk[3] == 0) return 3;
            }
            else if (matris[1][0] == karakter_secim){
                if (matris_doluluk[6] == 0) return 6;
            }
            else if (matris[1][2] == karakter_secim){
                if (matris_doluluk[4] == 0) return 4;
            }
            else;
        }
        else if (matris[1][2] == karakter_secim){
            if (matris[0][2] == karakter_secim){
                if (matris_doluluk[9] == 0) return 9;
            }
            else if (matris[2][2] == karakter_secim){
                if (matris_doluluk[3] == 0) return 3;
            }
            else if (matris[1][1] == karakter_secim){
                if (matris_doluluk[4] == 0) return 4;
            }
            else if (matris[1][0] == karakter_secim){
                if (matris_doluluk[5] == 0) return 5;
            }
            else;
        }
        else if (matris[2][0] == karakter_secim){
            if (matris[0][0] == karakter_secim){
                if (matris_doluluk[4] == 0) return 4;
            }
            else if (matris[1][0] == karakter_secim){
                if (matris_doluluk[1] == 0) return 1;
            }
            else if (matris[1][1] == karakter_secim){
                if (matris_doluluk[3] == 0) return 3;
            }
            else if (matris[0][2] == karakter_secim){
                if (matris_doluluk[5] == 0) return 5;
            }
            else if (matris[2][1] == karakter_secim){
                if (matris_doluluk[9] == 0) return 9;
            }
            else if (matris[2][2] == karakter_secim){
                if (matris_doluluk[8] == 0) return 8;
            }
            else;
        }
        else if (matris[2][1] == karakter_secim){
            if (matris[1][1] == karakter_secim){
                if (matris_doluluk[2] == 0) return 2;
            }
            else if (matris[0][1] == karakter_secim){
                if (matris_doluluk[5] == 0) return 5;
            }
            else if (matris[2][0] == karakter_secim){
                if (matris_doluluk[9] == 0) return 9;
            }
            else if (matris[2][2] == karakter_secim){
                if (matris_doluluk[7] == 0) return 7;
            }
            else;
        }
        else if (matris[2][2] == karakter_secim){
            if (matris[0][0] == karakter_secim){
                if (matris_doluluk[5] == 0) return 5;
            }
            else if (matris[1][1] == karakter_secim){
                if (matris_doluluk[1] == 0) return 1;
            }
            else if (matris[0][2] == karakter_secim){
                if (matris_doluluk[6] == 0) return 6;
            }
            else if (matris[1][2] == karakter_secim){
                if (matris_doluluk[3] == 0) return 3;
            }
            else if (matris[2][0] == karakter_secim){
                if (matris_doluluk[8] == 0) return 8;
            }
            else if (matris[2][1] == karakter_secim){
                if (matris_doluluk[7] == 0) return 7;
            }
            else;
        }
    }

    else if (baslayan == 1 && matris_bos >= 4){ // ilk önce pc başlıyor ise
        if (matris[0][0] == karakter_secim){
            if (matris[0][1] == karakter_secim){
                if (matris_doluluk[3] == 0) return 3;
            }
            else if (matris[1][0] == karakter_secim){
                if (matris_doluluk[7] == 0) return 7;
            }
            else if (matris[1][1] == karakter_secim){
                if (matris_doluluk[9] == 0) return 9;
            }
            else if (matris[0][2] == karakter_secim){
                if (matris_doluluk[2] == 0) return 2;
            }
            else if (matris[2][0] == karakter_secim){
                if (matris_doluluk[4] == 0) return 4;
            }
            else if (matris[2][2] == karakter_secim){
                if (matris_doluluk[5] == 0) return 5;
            }
            else;
        }
        else if (matris[0][1] == karakter_secim){
            if (matris[0][0] == karakter_secim){
                if (matris_doluluk[3] == 0) return 3;
            }
            else if (matris[0][2] == karakter_secim){
                if (matris_doluluk[1] == 0) return 1;
            }
            else if (matris[1][1] == karakter_secim){
                if (matris_doluluk[8] == 0) return 8;
            }
            else if (matris[2][1] == karakter_secim){
                if (matris_doluluk[5] == 0) return 5;
            }
            else;
        }
        else if (matris[0][2] == karakter_secim){
            if (matris[0][0] == karakter_secim){
                if (matris_doluluk[2] == 0) return 2;
            }
            else if (matris[0][1] == karakter_secim){
                if (matris_doluluk[1] == 0) return 1;
            }
            else if (matris[1][1] == karakter_secim){
                if (matris_doluluk[7] == 0) return 7;
            }
            else if (matris[2][0] == karakter_secim){
                if (matris_doluluk[5] == 0) return 5;
            }
            else if (matris[1][2] == karakter_secim){
                if (matris_doluluk[9] == 0) return 9;
            }
            else if (matris[2][2] == karakter_secim){
                if (matris_doluluk[6] == 0) return 6;
            }
            else;
        }
        else if (matris[1][0] == karakter_secim){
            if (matris[0][0] == karakter_secim){
                if (matris_doluluk[7] == 0) return 7;
            }
            else if (matris[2][0] == karakter_secim){
                if (matris_doluluk[1] == 0) return 1;
            }
            else if (matris[1][1] == karakter_secim){
                if (matris_doluluk[6] == 0) return 6;
            }
            else if (matris[1][2] == karakter_secim){
                if (matris_doluluk[5] == 0) return 5;
            }
            else;
        }
        else if (matris[1][1] == karakter_secim){
            if (matris[0][0] == karakter_secim){
                if (matris_doluluk[9] == 0) return 9;
            }
            else if (matris[2][2] == karakter_secim){
                if (matris_doluluk[1] == 0) return 1;
            }
            else if (matris[0][1] == karakter_secim){
                if (matris_doluluk[8] == 0) return 8;
            }
            else if (matris[2][1] == karakter_secim){
                if (matris_doluluk[2] == 0) return 2;
            }
            else if (matris[0][2] == karakter_secim){
                if (matris_doluluk[7] == 0) return 7;
            }
            else if (matris[2][0] == karakter_secim){
                if (matris_doluluk[3] == 0) return 3;
            }
            else if (matris[1][0] == karakter_secim){
                if (matris_doluluk[6] == 0) return 6;
            }
            else if (matris[1][2] == karakter_secim){
                if (matris_doluluk[4] == 0) return 4;
            }
            else;
        }
        else if (matris[1][2] == karakter_secim){
            if (matris[0][2] == karakter_secim){
                if (matris_doluluk[9] == 0) return 9;
            }
            else if (matris[2][2] == karakter_secim){
                if (matris_doluluk[3] == 0) return 3;
            }
            else if (matris[1][1] == karakter_secim){
                if (matris_doluluk[4] == 0) return 4;
            }
            else if (matris[1][0] == karakter_secim){
                if (matris_doluluk[5] == 0) return 5;
            }
            else;
        }
        else if (matris[2][0] == karakter_secim){
            if (matris[0][0] == karakter_secim){
                if (matris_doluluk[4] == 0) return 4;
            }
            else if (matris[1][0] == karakter_secim){
                if (matris_doluluk[1] == 0) return 1;
            }
            else if (matris[1][1] == karakter_secim){
                if (matris_doluluk[3] == 0) return 3;
            }
            else if (matris[0][2] == karakter_secim){
                if (matris_doluluk[5] == 0) return 5;
            }
            else if (matris[2][1] == karakter_secim){
                if (matris_doluluk[9] == 0) return 9;
            }
            else if (matris[2][2] == karakter_secim){
                if (matris_doluluk[8] == 0) return 8;
            }
            else;
        }
        else if (matris[2][1] == karakter_secim){
            if (matris[1][1] == karakter_secim){
                if (matris_doluluk[2] == 0) return 2;
            }
            else if (matris[0][1] == karakter_secim){
                if (matris_doluluk[5] == 0) return 5;
            }
            else if (matris[2][0] == karakter_secim){
                if (matris_doluluk[9] == 0) return 9;
            }
            else if (matris[2][2] == karakter_secim){
                if (matris_doluluk[7] == 0) return 7;
            }
            else;
        }
        else if (matris[2][2] == karakter_secim){
            if (matris[0][0] == karakter_secim){
                if (matris_doluluk[5] == 0) return 5;
            }
            else if (matris[1][1] == karakter_secim){
                if (matris_doluluk[1] == 0) return 1;
            }
            else if (matris[0][2] == karakter_secim){
                if (matris_doluluk[6] == 0) return 6;
            }
            else if (matris[1][2] == karakter_secim){
                if (matris_doluluk[3] == 0) return 3;
            }
            else if (matris[2][0] == karakter_secim){
                if (matris_doluluk[8] == 0) return 8;
            }
            else if (matris[2][1] == karakter_secim){
                if (matris_doluluk[7] == 0) return 7;
            }
            else;
        }
    }
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

    printf("\n\nBİR HATA OLUSTU ~1084\n\n");
    return 0;
}





int matris_doluluk_kontrol(int konum){
    if (matris_doluluk[konum] == 1) return 1; // konum dolu bildirisi.
    else return 0; // konum boş bildirisi.
}



int kontrol(){
    // 3 satır kontrol
    // 3 sütun kontrol
    // 2 çapraz kontrol

    int sayi_matris[3][3];
    int i;

    /* sil
    for (i=1;i<10;i++){
        printf("%d",matris_doluluk[i]);
    }*/


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








void matris_yazidirma(int konum,char karakter){
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



void yazdirma (void){
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


