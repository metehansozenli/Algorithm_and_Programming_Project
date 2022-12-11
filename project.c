#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define MAX 100

///////////////////////////////////////MODUL 1//////////////////////////////////////////////////////////////////
void cevap_anahtari_uret(char cevap_anahtari[], int S){

    srand(time(NULL));
    for(int i=0;i<S;i++){
        char cevap = rand()%5+65;//65-69 -> ASCII(A-E)
        cevap_anahtari[i]=cevap;
    }
}

void cevap_anahtari_yazdir(char cevap_anahtari[], int S){

    printf("\nCevap Anahtari:\n");
    for(int i=0;i<S;i++)
        printf("%03d:%c | ",i+1,cevap_anahtari[i]);
    printf("\n");
}

void sinavi_uygula(char ogrenci_cevaplari[][100], char cevap_anahtari[], int N, int S, double B,double D){

    int bos_olasilik,dogru_olasilik;
    char rand_cevap,c;
    srand(time(NULL));

    for(int i=0;i<N;i++){
            for(int j=0;j<S;j++){
                bos_olasilik=rand()%101+1;//1-100 kapali araliginda random sayi olusturuluyor
                if(bos_olasilik<=B*100)//cevabin olasilik dahilinde bos birakilma durumu
                    ogrenci_cevaplari[i][j]='X';
                else{//sorunun bos birakilma ihtimali gerceklesmezse
                    dogru_olasilik=rand()%101+1;//1-100 kapali araliginda random sayi olusturuluyor
                    if(dogru_olasilik<=D*100)//cevabin olasilik dahilinde dogru olma durumu
                        ogrenci_cevaplari[i][j]=cevap_anahtari[j];
                    else{//cevabin yanlis olma durumu
                        while(1){//burda amac sonsuz dongu ile dogru cevaptan baska bir random cevap olusturmak
                            c=rand()%5+65;//random cevap olusturuluyor
                            if(c != cevap_anahtari[j]){//eger olusan random cevap, dogru cevapla ayni degilse
                                rand_cevap=c;
                                break;//kosul gerceklesince sonsuz dongunun sonlanmasi icin
                            }
                        }
                        ogrenci_cevaplari[i][j]=rand_cevap;
                    }
                }
            }
    }
}

void ogrenci_cevabini_yazdir(char ogrenci_cevaplari[][100], int ogrenci_ID, int S){

    printf("\n%03d.Ogrencinin Cevaplari:\n",ogrenci_ID+1);
    for(int i=0;i<S;i++)
        printf("%03d:%c | ",i+1,ogrenci_cevaplari[ogrenci_ID][i]);
}

///////////////////////////////////////MODUL 2//////////////////////////////////////////////////////////////////
void ogrencileri_puanla(char ogrenci_cevaplari[][100], char cevap_anahtari[], double HBN[],int N, int S){

    int dogru_sayisi,yanlis_sayisi;//HBN hesaplanmasi icin kullanilacak dogru ve yanlis cevap sayilarini tutan degiskenler
    double soru_puani=100/S;//sinavdaki her bir sorunun puan degeri
    for(int i=0;i<N;i++){
        dogru_sayisi=0,yanlis_sayisi=0;//her ogrenci icin dogru yanlis sayilari sifirlanmali
        for(int j=0;j<S;j++){
            if(ogrenci_cevaplari[i][j]==cevap_anahtari[j])//ogrencinin cevabi cevap anahtari ile uyusuyorsa
                dogru_sayisi++;
            else if(ogrenci_cevaplari[i][j]!=cevap_anahtari[j] && ogrenci_cevaplari[i][j]!='X')//ogrencinin cevabi dogru degilse ve bos degilse
                yanlis_sayisi++;
        }
        HBN[i]=(dogru_sayisi*soru_puani)-(yanlis_sayisi*soru_puani/4.0);//HBN hesaplanmasi
    }
}

double sinif_ortalamasi_hesapla(double HBN[], int N){

    double toplam=0.0;
    for(int i=0;i<N;i++)
        toplam+=HBN[i];
    return toplam/N;
}

double standart_sapma_hesapla(double ortalama, double HBN[], int N){

    double sonuc=0.0;
    for(int i=0;i<N;i++)
        sonuc+=pow(HBN[i]-ortalama,2);

    return sqrt(sonuc/N);
}

void T_skoru_hesapla(double ortalama, double HBN[], int N, double std, double T_skoru[]){

    for(int i=0;i<N;i++)
        T_skoru[i]=60+(10*(HBN[i]-ortalama)/std);
}

void sinif_duzeyi_belirle(double ortalama){

    printf("Sinif Duzeyi: ");//Ternary ifadelerle sinif duzeyi belirleyip yazdirma
    (ortalama>80.0 && ortalama<=100.0)? printf("Ustun Basari\n"):(ortalama>70.0 && ortalama<=80.0)? printf("Mukemmel\n"):(ortalama>62.5 && ortalama<=70.0)? printf("Cok Iyi\n"):
    (ortalama>57.5 && ortalama<=62.5)? printf("Iyi\n"):(ortalama>52.5 && ortalama<=57.5)? printf("Ortanin Ustu\n"):(ortalama>47.5 && ortalama<=52.5)? printf("Orta\n"):
    (ortalama>42.5 && ortalama<=47.5)? printf("Zayif\n"):printf("Kotu\n");
}

void harf_notu_hesapla(double ortalama,double T_skoru[],char harf_notu[][3],int N){

    for(int i=0;i<N;i++){
        if(ortalama>80.0 && ortalama<=100.0)//Ternary ifadelerle sinif ortalamasina ve t skora gore harf notu hesaplama
            (T_skoru[i]>=67.0)? strcpy(harf_notu[i],"AA"):(T_skoru[i]>=62.0 && T_skoru[i]<=66.99)? strcpy(harf_notu[i],"BA"):(T_skoru[i]>=57.0 && T_skoru[i]<=61.99)? strcpy(harf_notu[i],"BB"):
            (T_skoru[i]>=52.0 && T_skoru[i]<=56.99)? strcpy(harf_notu[i],"CB"):(T_skoru[i]>=47.0 && T_skoru[i]<=51.99)? strcpy(harf_notu[i],"CC"):(T_skoru[i]>=42.0 && T_skoru[i]<=46.99)? strcpy(harf_notu[i],"DC"):
            (T_skoru[i]>=37.0 && T_skoru[i]<=41.99)? strcpy(harf_notu[i],"DD"):(T_skoru[i]>=32.0 && T_skoru[i]<=36.99)? strcpy(harf_notu[i],"FD"):strcpy(harf_notu[i],"FF");

        else if(ortalama>70.0 && ortalama<=80.0)
            (T_skoru[i]>=69.0)? strcpy(harf_notu[i],"AA"):(T_skoru[i]>=64.0 && T_skoru[i]<=68.99)? strcpy(harf_notu[i],"BA"):(T_skoru[i]>=59.0 && T_skoru[i]<=63.99)? strcpy(harf_notu[i],"BB"):
            (T_skoru[i]>=54.0 && T_skoru[i]<=58.99)? strcpy(harf_notu[i],"CB"):(T_skoru[i]>=49.0 && T_skoru[i]<=53.99)? strcpy(harf_notu[i],"CC"):(T_skoru[i]>=44.0 && T_skoru[i]<=48.99)? strcpy(harf_notu[i],"DC"):
            (T_skoru[i]>=39.0 && T_skoru[i]<=43.99)? strcpy(harf_notu[i],"DD"):(T_skoru[i]>=34.0 && T_skoru[i]<=38.99)? strcpy(harf_notu[i],"FD"):strcpy(harf_notu[i],"FF");

        else if(ortalama>62.5 && ortalama<=70.0)
            (T_skoru[i]>=71.0)? strcpy(harf_notu[i],"AA"):(T_skoru[i]>=66.0 && T_skoru[i]<=70.99)? strcpy(harf_notu[i],"BA"):(T_skoru[i]>=61.0 && T_skoru[i]<=65.99)? strcpy(harf_notu[i],"BB"):
            (T_skoru[i]>=56.0 && T_skoru[i]<=60.99)? strcpy(harf_notu[i],"CB"):(T_skoru[i]>=51.0 && T_skoru[i]<=55.99)? strcpy(harf_notu[i],"CC"):(T_skoru[i]>=46.0 && T_skoru[i]<=50.99)? strcpy(harf_notu[i],"DC"):
            (T_skoru[i]>=41.0 && T_skoru[i]<=45.99)? strcpy(harf_notu[i],"DD"):(T_skoru[i]>=36.0 && T_skoru[i]<=40.99)? strcpy(harf_notu[i],"FD"):strcpy(harf_notu[i],"FF");

        else if(ortalama>57.5 && ortalama<=62.5)
            (T_skoru[i]>=73.0)? strcpy(harf_notu[i],"AA"):(T_skoru[i]>=68.0 && T_skoru[i]<=72.99)? strcpy(harf_notu[i],"BA"):(T_skoru[i]>=63.0 && T_skoru[i]<=67.99)? strcpy(harf_notu[i],"BB"):
            (T_skoru[i]>=58.0 && T_skoru[i]<=62.99)? strcpy(harf_notu[i],"CB"):(T_skoru[i]>=53.0 && T_skoru[i]<=57.99)? strcpy(harf_notu[i],"CC"):(T_skoru[i]>=48.0 && T_skoru[i]<=52.99)? strcpy(harf_notu[i],"DC"):
            (T_skoru[i]>=43.0 && T_skoru[i]<=47.99)? strcpy(harf_notu[i],"DD"):(T_skoru[i]>=38.0 && T_skoru[i]<=42.99)? strcpy(harf_notu[i],"FD"):strcpy(harf_notu[i],"FF");

        else if(ortalama>52.5 && ortalama<=57.5)
            (T_skoru[i]>=75.0)? strcpy(harf_notu[i],"AA"):(T_skoru[i]>=70.0 && T_skoru[i]<=74.99)? strcpy(harf_notu[i],"BA"):(T_skoru[i]>=65.0 && T_skoru[i]<=69.99)? strcpy(harf_notu[i],"BB"):
            (T_skoru[i]>=60.0 && T_skoru[i]<=64.99)? strcpy(harf_notu[i],"CB"):(T_skoru[i]>=55.0 && T_skoru[i]<=59.99)? strcpy(harf_notu[i],"CC"):(T_skoru[i]>=50.0 && T_skoru[i]<=54.99)? strcpy(harf_notu[i],"DC"):
            (T_skoru[i]>=45.0 && T_skoru[i]<=49.99)? strcpy(harf_notu[i],"DD"):(T_skoru[i]>=40.0 && T_skoru[i]<=44.99)? strcpy(harf_notu[i],"FD"):strcpy(harf_notu[i],"FF");

        else if(ortalama>47.5 && ortalama<=52.5)
            (T_skoru[i]>=77.0)? strcpy(harf_notu[i],"AA"):(T_skoru[i]>=72.0 && T_skoru[i]<=76.99)? strcpy(harf_notu[i],"BA"):(T_skoru[i]>=67.0 && T_skoru[i]<=71.99)? strcpy(harf_notu[i],"BB"):
            (T_skoru[i]>=62.0 && T_skoru[i]<=66.99)? strcpy(harf_notu[i],"CB"):(T_skoru[i]>=57.0 && T_skoru[i]<=61.99)? strcpy(harf_notu[i],"CC"):(T_skoru[i]>=52.0 && T_skoru[i]<=56.99)? strcpy(harf_notu[i],"DC"):
            (T_skoru[i]>=47.0 && T_skoru[i]<=51.99)? strcpy(harf_notu[i],"DD"):(T_skoru[i]>=42.0 && T_skoru[i]<=46.99)? strcpy(harf_notu[i],"FD"):strcpy(harf_notu[i],"FF");

        else if(ortalama>42.5 && ortalama<=47.5)
            (T_skoru[i]>=79.0)? strcpy(harf_notu[i],"AA"):(T_skoru[i]>=74.0 && T_skoru[i]<=78.99)? strcpy(harf_notu[i],"BA"):(T_skoru[i]>=69.0 && T_skoru[i]<=73.99)? strcpy(harf_notu[i],"BB"):
            (T_skoru[i]>=64.0 && T_skoru[i]<=68.99)? strcpy(harf_notu[i],"CB"):(T_skoru[i]>=59.0 && T_skoru[i]<=63.99)? strcpy(harf_notu[i],"CC"):(T_skoru[i]>=54.0 && T_skoru[i]<=58.99)? strcpy(harf_notu[i],"DC"):
            (T_skoru[i]>=49.0 && T_skoru[i]<=53.99)? strcpy(harf_notu[i],"DD"):(T_skoru[i]>=44.0 && T_skoru[i]<=48.99)? strcpy(harf_notu[i],"FD"):strcpy(harf_notu[i],"FF");

        else
            (T_skoru[i]>=81.0)? strcpy(harf_notu[i],"AA"):(T_skoru[i]>=76.0 && T_skoru[i]<=80.99)? strcpy(harf_notu[i],"BA"):(T_skoru[i]>=71.0 && T_skoru[i]<=75.99)? strcpy(harf_notu[i],"BB"):
            (T_skoru[i]>=66.0 && T_skoru[i]<=70.99)? strcpy(harf_notu[i],"CB"):(T_skoru[i]>=61.0 && T_skoru[i]<=65.99)? strcpy(harf_notu[i],"CC"):(T_skoru[i]>=56.0 && T_skoru[i]<=60.99)? strcpy(harf_notu[i],"DC"):
            (T_skoru[i]>=51.0 && T_skoru[i]<=55.99)? strcpy(harf_notu[i],"DD"):(T_skoru[i]>=46.0 && T_skoru[i]<=50.99)? strcpy(harf_notu[i],"FD"):strcpy(harf_notu[i],"FF");

    harf_notu[i][2]='\0';
    }
}

int main()
{
    int N,S;
    double B,D,ortalama,std,HBN[MAX],T_skoru[MAX];
    char cevap_anahtari[MAX],ogrenci_cevaplari[MAX][MAX],harf_notu[MAX][3];

    printf("Sinav Simulasyonu Uygulamasina Hosgeldiniz!\n");
    printf("-------------------------------------------\n");
    printf("\nOgrenci sayisini giriniz(Max 100): ");scanf("%d",&N);
    printf("Soru sayisini giriniz(Max 100): ");scanf("%d",&S);
    printf("Herhangi bir sorunun bos birakilma ihtimalini giriniz(0.0 ~ 1.0): ");scanf("%lf",&B);
    printf("Herhangi bir sorunun dogru cevaplanma ihtimalini giriniz(0.0 ~ 1.0): ");scanf("%lf",&D);

    cevap_anahtari_uret(cevap_anahtari,S);
    cevap_anahtari_yazdir(cevap_anahtari,S);
    sinavi_uygula(ogrenci_cevaplari,cevap_anahtari,N,S,B,D);

    for(int i=0;i<N;i++)
        ogrenci_cevabini_yazdir(ogrenci_cevaplari,i,S);
    printf("\n\n");

    ogrencileri_puanla(ogrenci_cevaplari,cevap_anahtari,HBN,N,S);
    ortalama=sinif_ortalamasi_hesapla(HBN,N);
    std=standart_sapma_hesapla(ortalama,HBN,N);
    printf("Sinif Ortalamasi:%.2lf, Standart Sapma:%.2lf\n",ortalama,std);
    sinif_duzeyi_belirle(ortalama);
    T_skoru_hesapla(ortalama,HBN,N,std,T_skoru);
    harf_notu_hesapla(ortalama,T_skoru,harf_notu,N);

    printf("\nOgrenci Notlari:\n");
    for(int i=0;i<N;i++)
        printf("%03d. Ogrencinin HBN: %.2lf, T Skoru: %.2lf, Harf Notu: %s\n",i+1,HBN[i],T_skoru[i],harf_notu[i]);

}
