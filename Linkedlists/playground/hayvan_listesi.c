#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Hayvan veri tipi **/
typedef struct hayvan{
    int kayitno;
    int yas;
    char * isim;
    char * cins;
    char * sahibi;
    struct hayvan * sonraki; // Sonraki hayvanı gösteren pointer.
} hayvan;

/** Liste için Kök Düğüm **/
hayvan * baslangic;

/** Metot tanımlamaları **/

/** Hayvanı numarasına göre bul **/
hayvan * numarayaGoreBul(int no){
    hayvan * h = NULL;
    hayvan * iter = baslangic;
    while (iter != NULL){
        if(iter->kayitno == no){
            h = iter;
            break;
        }
        iter = iter->sonraki;
    }
    return h;
}
/** Hayvanı ismine göre bul **/
hayvan * isimeGoreBul(char * isim){
    hayvan * h = NULL;
    hayvan * iter = baslangic;
    while (iter != NULL){
        if(strcmp(iter->isim, isim) == 0){
            h = iter;
            break;
        }
        iter = iter->sonraki;
    }
    return h;
}
/** Hayvanı listeye kaydet **/
void kaydet(){
    printf("Hayvan kaydetmek istediniz.\n");

    hayvan * yeni = (hayvan *) malloc(sizeof(hayvan));

    yeni->kayitno = 0;
    yeni->yas = 0;
    yeni->isim = malloc(sizeof(char));
    yeni->cins = malloc(sizeof(char));
    yeni->sahibi = malloc(sizeof(char));
    yeni->sonraki = NULL;

    printf("Hayvanin kayit numarasini girin: ");
    scanf("%d", &yeni->kayitno);

    printf("Hayvanin yasini girin: ");
    scanf("%d", &yeni->yas);

    printf("Hayvanin adini girin: ");
    scanf("%s", yeni->isim);

    printf("Hayvanin cinsini girin: ");
    scanf("%s", yeni->cins);

    printf("Hayvanin sahibinin adini girin: ");
    scanf("%s", yeni->sahibi);


    /* Eğer liste boş ise en başına koy */
    if(baslangic == NULL){
        baslangic = yeni;
    }else if(yeni->kayitno <= baslangic->kayitno){ // Eğer kayıt no liste başındaki elemandan küçükse en başına koy.
        yeni->sonraki = baslangic;
        baslangic = yeni;
    }else{ // Liste boş değilse kayıt numarasına göre sıralı olarak ekle.
        hayvan * iter = baslangic;

        // Eklenecek hayvanın kayıt numarası listedeki elemandan büyükse ilerle.
        while(iter->sonraki != NULL && yeni->kayitno >= iter->sonraki->kayitno){
            iter = iter->sonraki;
        }
        yeni->sonraki = iter->sonraki;
        iter->sonraki = yeni;
    }

    printf("\n----- Hayvan eklendi. -----\n");

};
/** Liste içerisindeki hayvanı güncelle. **/
void guncelle(){
    printf("Hayvan guncellemek istediniz.\n");
    if(baslangic == NULL){
        printf("Listede herhangi bir hayvan yok, once hayvan ekleyin.\n");
        return;
    }
    printf("Guncellemek istediginiz hayvanin kayit numarasini girin:\n");
    int no;
    scanf("%d", &no);

    hayvan * h = numarayaGoreBul(no);

    if(h == NULL){
        printf("Aradiginiz kayit numarasi ile hayvan bulunamadi!\n");
        return;
    }

    printf("%1s\n%1s|%10s|%10s|%10s|%10s|\n", "---------Duzenlenecek Hayvan---------",
           "#NO", " #ISIM", "#YAS", "#CINS", "#SAHIBI");
    printf("%3d|%10s|%10d|%10s|%10s|\n", h->kayitno, h->isim, h->yas, h->cins, h->sahibi);

    printf("Hayvanin yasini girin: ");
    scanf("%d", &h->yas);

    printf("Hayvanin adini girin: ");
    scanf("%s", h->isim);

    printf("Hayvanin cinsini girin: ");
    scanf("%s", h->cins);

    printf("Hayvanin sahibinin adini girin: ");
    scanf("%s", h->sahibi);

    printf("\n----- Hayvan guncellendi. -----\n");

};
/** Listeyi göster **/
void listele(){
    printf("%1s\n%1s|%10s|%10s|%10s|%10s|\n", "---------HAYVAN LISTESI---------",
           "#NO", " #ISIM", "#YAS", "#CINS", "#SAHIBI");
    hayvan * iter = baslangic;
    while (iter != NULL){
        printf("%3d|%10s|%10d|%10s|%10s|\n", iter->kayitno, iter->isim, iter->yas, iter->cins, iter->sahibi);
        iter = iter->sonraki;
    }
};
/** Kayıt numarasına ve isime göre hayvan ara **/
void ara(){
    printf("Hayvan aramak istediniz.\n");
    if(baslangic == NULL){
        printf("Listede herhangi bir hayvan yok, once hayvan ekleyin.\n");
        return;
    }
    printf("Arama secenekleri:\n[1] - Kayit numarasina gore\n[2] - Isime gore\nArama tipi secin: ");

    int tip;

    scanf("%d", &tip);

    hayvan * h = NULL;
    if(tip == 1){
        printf("Kayit numarasi girin: ");
        int no;
        scanf("%d", &no);
        h = numarayaGoreBul(no);
    }else if(tip == 2){
        printf("Hayvan adi girin: ");
        char * isim = malloc(sizeof(char));
        scanf("%s", isim);
        h = isimeGoreBul(isim);
    }

    if(h == NULL){
        printf("Aradiginiz hayvan bulunamadi!\n");
        return;
    }

    printf("%1s\n%1s|%10s|%10s|%10s|%10s|\n", "---------Bulunan Hayvan---------",
           "#NO", " #ISIM", "#YAS", "#CINS", "#SAHIBI");
    printf("%3d|%10s|%10d|%10s|%10s|\n", h->kayitno, h->isim, h->yas, h->cins, h->sahibi);

};
/** Hayvan listesini dosyaya yazar **/
void yazdir(){
    printf("Listeyi dosyaya yazmak istediniz.\n");
    if(baslangic == NULL){
        printf("Listede herhangi bir hayvan yok, once hayvan ekleyin.\n");
        return;
    }

    FILE * dosya = fopen("liste.txt", "w");

    if(dosya == NULL){
        printf("Listeyi yazdirmak icin dosya acilamadi!\n");
        return;
    }

    fprintf(dosya, "%1s|%15s|%15s|%15s|%15s|\n", "#NO", " #ISIM", "#YAS", "#CINS", "#SAHIBI");

    hayvan * iter = baslangic;

    while (iter != NULL){
        fprintf(dosya, "%3d|%15s|%15d|%15s|%15s|\n", iter->kayitno, iter->isim, iter->yas, iter->cins, iter->sahibi);
        iter = iter->sonraki;
    }

    fclose(dosya);

    printf("\n----- Liste dosyaya yazdirildi. 'liste.txt' dosyasina bakin. -----\n");

}
/** Sahibine göre hayvanları listele **/
void sahibineGoreListele(){
    printf("Sahibine gore hayvan listelemek istediniz.\n");

    if(baslangic == NULL){
        printf("Listede herhangi bir hayvan yok, once hayvan ekleyin.\n");
        return;
    }

    printf("Listelemek istediginiz hayvanlarin sahibinin adini girin: ");

    char * sahibi = malloc(sizeof(char));
    scanf("%s", sahibi);

    if(baslangic == NULL){
        printf("Listede herhangi bir hayvan yok, once hayvan ekleyin.\n");
        return;
    }

    hayvan * iter = baslangic;
    printf("---------'%s' kisisinin Hayvanlari---------\n%1s|%10s|%10s|%10s|%10s|\n",
           sahibi,"#NO", " #ISIM", "#YAS", "#CINS", "#SAHIBI");

    while (iter != NULL){
        if(strcmp(iter->sahibi, sahibi) == 0){
            printf("%3d|%10s|%10d|%10s|%10s|\n", iter->kayitno, iter->isim, iter->yas, iter->cins, iter->sahibi);
        }
        iter = iter->sonraki;
    }
    printf("\n----- Hayvan listelendi. -----\n");
}
/** Panel girisi **/
void giris(){
    printf("%10s\n%s\n%s\n%s\n%s\n","------------------------------------------------------------",
           "Veteriner Hayvan Kayit Sistemine Hosgeldiniz!",
           "Lutfen yapmak istediginiz islemin komut numarasini yazin:",
           "[1] - Hayvan Kaydet\n[2] - Hayvan Guncelle\n[3] - Hayvanlari Listele\n[4] - Hayvan Ara\n[5] - Sahibine Gore Listele\n[6] - Listeyi Dosyaya Yaz\n[0] - Cikis",
           "-------------------------------------------------------------"
    );
}

int main(){

    while(1){
        giris();
        int komut;
        printf("Komut numarasi: ");
        scanf("%d", &komut);
        switch (komut){
            case 0:
                printf("Program sonlandiriliyor, iyi gunler dileriz...");
                exit(-1);
            case 1:
                kaydet();
                break;
            case 2:
                guncelle();
                break;
            case 3:
                listele();
                break;
            case 4:
                ara();
                break;
            case 5:
                sahibineGoreListele();
                break;
            case 6:
                yazdir();
                break;
            default:
                printf("Komut bulunamadi, tekrar deneyin!\n");
                break;
        }
    }
}