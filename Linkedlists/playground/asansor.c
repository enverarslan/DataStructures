#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// kat veri yapısı
struct kat{
    int no;
    struct kat * sonraki;
};
// Kat veri tanımı
typedef struct kat Kat;

// Pano liste başını tutan işaretçi olacak.
Kat * pano = NULL;

/**
 * Asansörün yönünü tutan değişken.
 * Yukarı = 1
 * Aşağı = 0
 */
int asansor_yonu=1;

void yonDegistir(){
    asansor_yonu = !asansor_yonu;
    pano = NULL;
    printf("### Asansor yonu degisti, tekrar dugmelere basin. ###\n");
}


void guzergah(){

    const char *yon = (asansor_yonu == 1) ? "Yukari" : "Asagi";

    printf("----------------------------------------\nASANSOR HAREKET SIRASI\n#Sira | #Kat | Hareket Yonu: %s\n----------------------------------------\n", yon);

    if(pano == NULL){
        printf("Hareket edilecek bir kat yok.\n");
        return;
    }

    Kat * iter = pano;
    int i = 1;
    while(iter){
        printf("%5d | %3d %1s|\n", i++, iter->no, "");
        iter = iter->sonraki;
    }
    printf("----------------------------------------\n");
}

/**
 * Listeye bir eleman ekler ve başlangıç adresini geri döndürür.
 * @param baslangic
 * @param no
 * @return
 */
void dugmeyeBas(int no){

    if(no < 0 || no > 30){
        printf("0-30 araliginda bir dugmeye basin.\n");
        return;
    }

    Kat * yeni = (Kat *) malloc(sizeof(Kat));
    yeni->no = no;
    yeni->sonraki = NULL;

    // Hiç eleman yoksa oluşturulanı döndür.
    if(pano == NULL){
        pano = yeni;
        return;
    }

    /**
     * Burada bir iterasyon ile liste üzerinde gezinip kat numarasını ekleyeceğimiz yeri bulalım.
     * Bulduğumuzda ekleyip duralım.
     */
    Kat * iter = pano;

    // Asansör yönüne göre elemanları ekleyelim.
    if(asansor_yonu == 1){
        // Sonraki elemandan büyük oldukça ilerle.
        while( iter->sonraki != NULL && (yeni->no > iter->sonraki->no) ){
            iter = iter->sonraki;
        }
        // Zaten varsa ekleme, sil.
        if(yeni->no == iter->no || (iter->sonraki != NULL && yeni->no == iter->sonraki->no)){
            free(yeni);
        }else if(yeni->no < iter->no){
            yeni->sonraki = iter;
            pano = yeni;
        }else if(iter->sonraki != NULL){
            yeni->sonraki = iter->sonraki;
            iter->sonraki = yeni;
        }else{
            iter->sonraki = yeni;
        }

    }else{
        // Sonraki elemandan küçük oldukça ilerle.
        while( iter->sonraki != NULL && (yeni->no < iter->sonraki->no) ){
            iter = iter->sonraki;
        }
        // Zaten varsa ekleme, sil.
        if(yeni->no == iter->no || (iter->sonraki != NULL && yeni->no == iter->sonraki->no)){
            free(yeni);
        }else if(yeni->no > iter->no){
            yeni->sonraki = iter;
            pano = yeni;
        }else if(iter->sonraki != NULL){
            yeni->sonraki = iter->sonraki;
            iter->sonraki = yeni;
        }else{
            iter->sonraki = yeni;
        }
    }
}

void hareketEt(){
    if(pano == NULL){
        printf("Asansorun gidecegi bir kat yok.\n");
        return;
    }
    Kat * gelinen = pano;
    pano = pano->sonraki;
    printf("Asansor %d. kata geldi.\n", gelinen->no);
    free(gelinen);
}



int main(){

    /**
     * Asansörün yukarı çıktığı durumu ele alalım.
     * İstediğimiz kata çıkmak için düğmelere basalım.
     */
    dugmeyeBas(12);
    dugmeyeBas(4);
    dugmeyeBas(27);
    dugmeyeBas(15);
    dugmeyeBas(6);
    dugmeyeBas(25);
    dugmeyeBas(18);

    // Asansörün duracağı katları görelim.
    guzergah();

    // Asansörü hareket ettirelim.
    hareketEt();
    hareketEt();
    hareketEt();
    hareketEt();
    hareketEt();
    hareketEt();
    hareketEt();
    hareketEt();

    // Asansörün duracağı katları görelim.
    guzergah();

    /**
     * Asansörün aşağı indiği durumu ele alalım.
     * İstediğimiz kata inmek için düğmelere basalım.
     */

    // Öncelikle asansörün yönünü değiştirelim, aşağı insin.
    yonDegistir();

    // Aşağı inecek asansöre durması gereken katların bilgilerini verelim.
    dugmeyeBas(12);
    dugmeyeBas(4);
    dugmeyeBas(27);
    dugmeyeBas(15);
    dugmeyeBas(6);
    dugmeyeBas(25);
    dugmeyeBas(18);

    // Asansörün duracağı katları görelim.
    guzergah();

    // Asansörü hareket ettirelim.
    hareketEt();
    hareketEt();
    hareketEt();
    hareketEt();
    hareketEt();
    hareketEt();
    hareketEt();
    hareketEt();
    hareketEt();

    // Asansörün duracağı katları tekrar görelim.
    guzergah();

    dugmeyeBas(6);
    dugmeyeBas(25);
    dugmeyeBas(18);

    // Asansörün duracağı katları tekrar görelim.
    guzergah();

    // Asansörü hareket ettirelim.
    hareketEt();
    hareketEt();

    // Asansörün duracağı katları tekrar görelim.
    guzergah();

    // Konsolu beklet...
    getchar();

    return 1;

}