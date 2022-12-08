#include <stdio.h>
#include <stdlib.h>
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

                bos_olasilik=rand()%101;
                if(bos_olasilik<=B*100)//
                    ogrenci_cevaplari[i][j]='X';

                else{//soruyu bos birakmazsa
                    dogru_olasilik=rand()%101;//0 ile 100 arasinda sayi uretir (100 dahil)

                    if(dogru_olasilik<=D*100)//cevabin olasilik dahilinde dogru olma durumu
                        ogrenci_cevaplari[i][j]=cevap_anahtari[j];

                    else{//cevabin yanlis olma durumu
                        while(1){//random olusturulan cevabin dogru cevap olmamasini saglayan sonsuz dongu
                            c=(char)(rand()%5+65);
                            if(c != cevap_anahtari[j]){//eger olusan random cevap, dogru cevapla ayni degilse
                                rand_cevap=c;
                                break;
                            }
                        }
                        ogrenci_cevaplari[i][j]=rand_cevap;//rastgele cevap ataniyor
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

    int dogru_sayisi,yanlis_sayisi;
    double soru_puani=100/S;
    for(int i=0;i<N;i++){
        dogru_sayisi=0,yanlis_sayisi=0;
        for(int j=0;j<S;j++){
            if(ogrenci_cevaplari[i][j]==cevap_anahtari[j])
                dogru_sayisi++;
            else if(ogrenci_cevaplari[i][j]!=cevap_anahtari[j] && ogrenci_cevaplari[i][j]!='X')
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

    printf("Sinif Duzeyi: ");//Ternary ifadelerle sinif duzeyi belirleme
    (ortalama>80.0 && ortalama<=100.0)? printf("Ustun Basari\n"):(ortalama>70.0 && ortalama<=80.0)? printf("Mukemmel\n"):(ortalama>62.5 && ortalama<=70.0)? printf("Cok Iyi\n"):
    (ortalama>57.5 && ortalama<=62.5)? printf("Iyi\n"):(ortalama>52.5 && ortalama<=57.5)? printf("Ortanin Ustu\n"):(ortalama>47.5 && ortalama<=52.5)? printf("Orta\n"):
    (ortalama>42.5 && ortalama<=47.5)? printf("Zayif\n"):printf("Kotu\n");
}

void harf_notu_hesapla(double ortalama,double T_skoru[],char harf_notu[][3],int N){

    for(int i=0;i<N;i++){
        if(ortalama>80.0 && ortalama<=100.0)//Ternary ifadelerle harf notu hesaplama
            (T_skoru[i]>=67.0)? strcpy(harf_notu[i],"AA"):(T_skoru[i]>=62.0 && T_skoru[i]<=66.99)? strcpy(harf_notu[i],"BA"):(T_skoru[i]>=57.0 && T_skoru[i]<=61.99)? strcpy(harf_notu[i],"BB"):
            (T_skoru[i]>=52.0 && T_skoru[i]<=56.99)? strcpy(harf_notu[i],"CB"):(T_skoru[i]>=47.0 && T_skoru[i]<=51.99)? strcpy(harf_notu[i],"CC"):(T_skoru[i]>=42.0 && T_skoru[i]<=46.99)? strcpy(harf_notu[i],"DC"):
            (T_skoru[i]>=37.0 && T_skoru[i]<=41.99)? strcpy(harf_notu[i],"DD"):(T_skoru[i]>=32.0 && T_skoru[i]<=36.99)? strcpy(harf_notu[i],"FD"):strcpy(harf_notu[i],"FF");

        else if(ortalama>70.0 && ortalama<=80.0)
            (T_skoru[i]>=67.0)? strcpy(harf_notu[i],"AA"):(T_skoru[i]>=62.0 && T_skoru[i]<=66.99)? strcpy(harf_notu[i],"BA"):(T_skoru[i]>=57.0 && T_skoru[i]<=61.99)? strcpy(harf_notu[i],"BB"):
            (T_skoru[i]>=52.0 && T_skoru[i]<=56.99)? strcpy(harf_notu[i],"CB"):(T_skoru[i]>=47.0 && T_skoru[i]<=51.99)? strcpy(harf_notu[i],"CC"):(T_skoru[i]>=42.0 && T_skoru[i]<=46.99)? strcpy(harf_notu[i],"DC"):
            (T_skoru[i]>=37.0 && T_skoru[i]<=41.99)? strcpy(harf_notu[i],"DD"):(T_skoru[i]>=32.0 && T_skoru[i]<=36.99)? strcpy(harf_notu[i],"FD"):strcpy(harf_notu[i],"FF");

        else if(ortalama>62.5 && ortalama<=70.0)
            (T_skoru[i]>=67.0)? strcpy(harf_notu[i],"AA"):(T_skoru[i]>=62.0 && T_skoru[i]<=66.99)? strcpy(harf_notu[i],"BA"):(T_skoru[i]>=57.0 && T_skoru[i]<=61.99)? strcpy(harf_notu[i],"BB"):
            (T_skoru[i]>=52.0 && T_skoru[i]<=56.99)? strcpy(harf_notu[i],"CB"):(T_skoru[i]>=47.0 && T_skoru[i]<=51.99)? strcpy(harf_notu[i],"CC"):(T_skoru[i]>=42.0 && T_skoru[i]<=46.99)? strcpy(harf_notu[i],"DC"):
            (T_skoru[i]>=37.0 && T_skoru[i]<=41.99)? strcpy(harf_notu[i],"DD"):(T_skoru[i]>=32.0 && T_skoru[i]<=36.99)? strcpy(harf_notu[i],"FD"):strcpy(harf_notu[i],"FF");

        else if(ortalama>57.5 && ortalama<=62.5)
            (T_skoru[i]>=67.0)? strcpy(harf_notu[i],"AA"):(T_skoru[i]>=62.0 && T_skoru[i]<=66.99)? strcpy(harf_notu[i],"BA"):(T_skoru[i]>=57.0 && T_skoru[i]<=61.99)? strcpy(harf_notu[i],"BB"):
            (T_skoru[i]>=52.0 && T_skoru[i]<=56.99)? strcpy(harf_notu[i],"CB"):(T_skoru[i]>=47.0 && T_skoru[i]<=51.99)? strcpy(harf_notu[i],"CC"):(T_skoru[i]>=42.0 && T_skoru[i]<=46.99)? strcpy(harf_notu[i],"DC"):
            (T_skoru[i]>=37.0 && T_skoru[i]<=41.99)? strcpy(harf_notu[i],"DD"):(T_skoru[i]>=32.0 && T_skoru[i]<=36.99)? strcpy(harf_notu[i],"FD"):strcpy(harf_notu[i],"FF");

        else if(ortalama>52.5 && ortalama<=57.5)
            (T_skoru[i]>=67.0)? strcpy(harf_notu[i],"AA"):(T_skoru[i]>=62.0 && T_skoru[i]<=66.99)? strcpy(harf_notu[i],"BA"):(T_skoru[i]>=57.0 && T_skoru[i]<=61.99)? strcpy(harf_notu[i],"BB"):
            (T_skoru[i]>=52.0 && T_skoru[i]<=56.99)? strcpy(harf_notu[i],"CB"):(T_skoru[i]>=47.0 && T_skoru[i]<=51.99)? strcpy(harf_notu[i],"CC"):(T_skoru[i]>=42.0 && T_skoru[i]<=46.99)? strcpy(harf_notu[i],"DC"):
            (T_skoru[i]>=37.0 && T_skoru[i]<=41.99)? strcpy(harf_notu[i],"DD"):(T_skoru[i]>=32.0 && T_skoru[i]<=36.99)? strcpy(harf_notu[i],"FD"):strcpy(harf_notu[i],"FF");

        else if(ortalama>47.5 && ortalama<=52.5)
            (T_skoru[i]>=67.0)? strcpy(harf_notu[i],"AA"):(T_skoru[i]>=62.0 && T_skoru[i]<=66.99)? strcpy(harf_notu[i],"BA"):(T_skoru[i]>=57.0 && T_skoru[i]<=61.99)? strcpy(harf_notu[i],"BB"):
            (T_skoru[i]>=52.0 && T_skoru[i]<=56.99)? strcpy(harf_notu[i],"CB"):(T_skoru[i]>=47.0 && T_skoru[i]<=51.99)? strcpy(harf_notu[i],"CC"):(T_skoru[i]>=42.0 && T_skoru[i]<=46.99)? strcpy(harf_notu[i],"DC"):
            (T_skoru[i]>=37.0 && T_skoru[i]<=41.99)? strcpy(harf_notu[i],"DD"):(T_skoru[i]>=32.0 && T_skoru[i]<=36.99)? strcpy(harf_notu[i],"FD"):strcpy(harf_notu[i],"FF");

        else if(ortalama>42.5 && ortalama<=47.5)
            (T_skoru[i]>=67.0)? strcpy(harf_notu[i],"AA"):(T_skoru[i]>=62.0 && T_skoru[i]<=66.99)? strcpy(harf_notu[i],"BA"):(T_skoru[i]>=57.0 && T_skoru[i]<=61.99)? strcpy(harf_notu[i],"BB"):
            (T_skoru[i]>=52.0 && T_skoru[i]<=56.99)? strcpy(harf_notu[i],"CB"):(T_skoru[i]>=47.0 && T_skoru[i]<=51.99)? strcpy(harf_notu[i],"CC"):(T_skoru[i]>=42.0 && T_skoru[i]<=46.99)? strcpy(harf_notu[i],"DC"):
            (T_skoru[i]>=37.0 && T_skoru[i]<=41.99)? strcpy(harf_notu[i],"DD"):(T_skoru[i]>=32.0 && T_skoru[i]<=36.99)? strcpy(harf_notu[i],"FD"):strcpy(harf_notu[i],"FF");

        else
            (T_skoru[i]>=67.0)? strcpy(harf_notu[i],"AA"):(T_skoru[i]>=62.0 && T_skoru[i]<=66.99)? strcpy(harf_notu[i],"BA"):(T_skoru[i]>=57.0 && T_skoru[i]<=61.99)? strcpy(harf_notu[i],"BB"):
            (T_skoru[i]>=52.0 && T_skoru[i]<=56.99)? strcpy(harf_notu[i],"CB"):(T_skoru[i]>=47.0 && T_skoru[i]<=51.99)? strcpy(harf_notu[i],"CC"):(T_skoru[i]>=42.0 && T_skoru[i]<=46.99)? strcpy(harf_notu[i],"DC"):
            (T_skoru[i]>=37.0 && T_skoru[i]<=41.99)? strcpy(harf_notu[i],"DD"):(T_skoru[i]>=32.0 && T_skoru[i]<=36.99)? strcpy(harf_notu[i],"FD"):strcpy(harf_notu[i],"FF");
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
