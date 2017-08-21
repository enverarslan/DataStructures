#include <stdio.h>
#include <stdlib.h>

// Yatak kapasitesi.
const int KAPASITE = 10;

// Yatak veri tipi.
typedef struct yatak{
    int no;
    const char * isim;
    struct yatak * sonraki;
} yatak;

// Fonksiyon tanımlamaları
void yatir(const char *);
void taburcuEt(const char *);
void yatakOlustur(int);
void dolularListesiYazdir();
void boslarListesiYazdir();

// Dolu ve boş yatakların başlangıcını tutan işaretçiler.
yatak * dolular;
yatak * boslar;

/**
 * İsmi verilen hastanın yatış işlemini başlatır.
 * @param isim
 */
void yatir(const char * isim){

    if(boslar == NULL){
         printf("Bos yatak yok. Yatak ekleyin. Su anki kapasite %d", KAPASITE);
         exit(-1);
    }

    yatak * yatacak = boslar;

    yatacak->isim = isim;

    // sonraki boş yatağın adresini bellekte tutalım.
    yatak * sonraki_bos = yatacak->sonraki;

    // yatan hastayı dolular listesini gösterecek şekilde ayarlayalım ve bunu dolular listesinin başına atayalım.
    yatacak->sonraki = dolular;
    dolular = yatacak;

    boslar = sonraki_bos;

    printf("%s isimli hasta icin %d. nolu yatak tahsis edildi.\n", isim, yatacak->no);

}

/**
 * Hastayı taburcu edip, yatağı boşlar listesine gönder. dolular listesindeki bağı düzenle.
 * @param isim
 */
void taburcuEt(const char * isim){

    yatak * iter = dolular;
    yatak * hasta = NULL;

    // Hastayı bulana kadar dolular listesinde arama yap.
    while (iter != NULL){
        if(iter->isim == isim){
            hasta = iter;
            break;
        }
        iter = iter->sonraki;
    }

    // Hasta bulunduysa dolular listesinden sil ve boşlar listesine ekle.
    if(hasta !=NULL){
        printf("%d numarali yatakta yatan %s isimli hasta taburcu ediliyor...\n", hasta->no, hasta->isim);
        hasta->isim = "";

        /**
         * Hastanın yatağını gösteren bir önceki yatağı bularak
         * hastadan önceki ve sonraki yatağı birbirine bağlayıp hastayı aradan çıkaracağız.
        */

        // Hasta listenin en başında bulunuyor.
        if(hasta == dolular && hasta->sonraki != NULL){
            dolular = hasta->sonraki;
        }else{ // hasta listenin sonu ya da ortalarında bulunuyor.

            iter = dolular;
            while (iter && iter->sonraki != hasta){
                iter = iter->sonraki;
            }
            // iter şu an hastanın yatağından bir önceki yatağı tutuyor.

            if(iter){
                iter->sonraki = hasta->sonraki;
            }else{
                dolular = NULL;
            }
        }

        // Yatağı boşlar listesinin başına gönderelim.
        hasta->sonraki = boslar;
        boslar = hasta;
    }else{
        printf("%s isimli yatan hasta bulunamadi.\n", isim);
    }

}

/**
 * Verilen numara ile boş yatak oluşturur. Boşlar listesinin başına ekler.
 * @param no
 */
void yatakOlustur(int no){
    yatak * yeni = (yatak *) malloc(sizeof(yatak));
    yeni->no = no;
    yeni->isim = "";
    yeni->sonraki = NULL;

    // Eğer boşlar listesinde hiç yatak yoksa yeni yatağın adresini boşlara ver.
    if(boslar == NULL){
        boslar = yeni;
    }else{
        // Tersi durumda yeni yatağın adresine boşların adresini koy, boşların adresi yeni yatağı göstersin.
        yeni->sonraki = boslar;
        boslar = yeni;
    }
}
/**
 * Dolular listesini konsolda yazdırır.
 */
void dolularListesiYazdir(){
    yatak * iter = dolular;
    printf("%1s\n%1s|%10s|%10s|%10s|\n", "---------DOLULAR LISTESI---------", "#NO", " #ISIM", "#ADRES", "#SONRAKI");
    while (iter != NULL) {
        printf("%3d|%10s|%10p|%10p|\n", iter->no, iter->isim, iter, iter->sonraki);
        iter = iter->sonraki;
    }
    printf("------------------------------------\n");
}
/**
 * Boşlar listesini konsolda yazdırır.
 */
void boslarListesiYazdir(){
    yatak * iter = boslar;
    printf("%1s\n%1s|%10s|%10s|%10s|\n", "---------BOSLAR LISTESI---------", "#NO", " #ISIM", "#ADRES", "#SONRAKI");
    while (iter != NULL) {
        printf("%3d|%10s|%10p|%10p|\n", iter->no, iter->isim, iter, iter->sonraki);
        iter = iter->sonraki;
    }
    printf("------------------------------------\n");
}

// Başlayalım...
int main(){
    // KAPASITE kadar boş yatak oluşturalım.
    int i;
    for (i = 1; i <= KAPASITE; i++) {
        yatakOlustur(i);
    }
    printf("%d tane bos yatak olusturuldu.\n", KAPASITE);

    // Hiç hasta olmadığı durumda listeyi görelim.
    boslarListesiYazdir();

    // Birkaç hasta yatıralım.
    yatir("Ahmet");
    yatir("Veli");
    yatir("Zeliha");
    yatir("Ayse");

    // Boş ve Dolu listelerini kontrol edelim.
    dolularListesiYazdir();
    boslarListesiYazdir();

    // Birkaç hastayı taburcu edelim.
    taburcuEt("Zeliha");
    taburcuEt("Ayse");
    // Tekrar Boş ve Dolu listelerini kontrol edelim.
    boslarListesiYazdir();
    dolularListesiYazdir();

    // Birkaç hastayı taburcu edelim.
    taburcuEt("Veli");
    taburcuEt("Ahmet");

    // Tekrar Boş ve Dolu listelerini kontrol edelim.
    boslarListesiYazdir();
    dolularListesiYazdir();

    yatir("Gulsen");
    yatir("Elif");
    yatir("Murat");
    yatir("Furkan");
    yatir("Omer");
    yatir("Gamze");

    // Tekrar Boş ve Dolu listelerini kontrol edelim.
    boslarListesiYazdir();
    dolularListesiYazdir();

    taburcuEt("Murat");
    taburcuEt("Elif");
    taburcuEt("Gamze");

    // Tekrar Boş ve Dolu listelerini kontrol edelim.
    boslarListesiYazdir();
    dolularListesiYazdir();

    // Konsolu beklet...
    getchar();

    return 1;
}