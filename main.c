#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <dirent.h>
struct Etiket
{
    char etiketadi[50][100];
    int tekrarsayi[50];
};

void etiket_bul(int tmp,char dosyalar[tmp][100],int tmp2,char yertutucu[tmp2][100])
{
    char aranan_etiket[50];
    char input_etiket[50];
    char yertut[45];
    char tekrar_eden_dosya[5][35];
    int siratut[5];
    int k=0;
    int kontrol_sayac=0;
    printf("Lutfen aramak istediginiz kelimeyi giriniz:");
    gets(input_etiket);
    fflush(stdin);
    strcpy(aranan_etiket,"[[");
    strcat(aranan_etiket,input_etiket);
    strcat(aranan_etiket,"]]");
    char satir_yrd[150];
    char satir_list[100][100];
    for(int i=0; i<tmp; i++)
    {
        FILE *dosya_ac=fopen(dosyalar[i],"r");
        int j=0;
        while(fgets(satir_yrd,100,dosya_ac)!=NULL)
        {
            strcpy(satir_list[j],satir_yrd);
            j++;
        }
        for(int l=0; l<j; l++)
        {
            if(strstr(satir_list[l],aranan_etiket))
            {
                for(int m=0; m<tmp2; m++)
                {
                    if(strstr(dosyalar[i],yertutucu[m]))
                    {
                        strcpy(yertut,yertutucu[m]);
                    }
                }
                siratut[k]=l+1;
                strcpy(tekrar_eden_dosya[k],yertut);
                k++;
            }
        }
        for(int i=0; i<tmp; i++)
        {
            char etiket_kontrol[35];
            strcpy(etiket_kontrol,input_etiket);
            strcat(etiket_kontrol,".txt");
            if(strstr(dosyalar[i],etiket_kontrol))
            {
                kontrol_sayac++;
            }
        }
        fclose(dosyalar[i]);
    }
    if(k>0)
    {
        if(kontrol_sayac>0)
            printf("Aranan etiket:%s\nARADIGINIZ KELIME ETIKET OLARAK BULUNDU!.\n",aranan_etiket);
        else
            printf("Aranan etiket:%s\nARADIGINIZ KELIME -YETIM- ETIKET OLARAK BULUNDU!!\n",aranan_etiket);
        printf("BULUNDUGU DOSYALAR:");
        for(int t=0; t<k; t++)
        {
            printf("%d.Dosya=%s ",t+1,tekrar_eden_dosya[t]);
        }
        printf("\nBULUNDUGU SATIRLAR:");
        for(int z=0; z<k; z++)
        {
            printf("\n%s dosyasinda bulundugu satir=%d ",tekrar_eden_dosya[z],siratut[z]);
        }
    }
    else
    {
        printf("ISTEDIGINIZ KELIME ETIKET OLARAK BULUNAMADI!.");
    }
    exit(1);
}
void guncelle(int tmp,char dosyalar[tmp][100],int tmp2,char yertutucu[tmp2][100],int tmp3,char etiketler[tmp3][50],struct Etiket etk)
{
    int calisma_durumu=0,b=0;
    char satir_yrd[100];
    char satir_list[50][100];
    char cumlecik[10][50];
    char girilen_etiket[35];
    char girilen_etiket_txt[50];
    char girilen_etiket_ikinci[35];
    char degisecek_etiket[35];
    char degisecek_etiket_ikinci[35];
    char *ayrac_ikinci="\\";
    char rename_matris[10][50];
    char degisecek_etiket_txt[50];
    int y=0,donus=0,i,j,k;
    char *ayrac="[]";
    printf("Fonksiyondan cikmak icin \"-1\"e basiniz!!.\n");
    while(1)
    {

        printf("Lutfen guncellemek istediniz etiketi giriniz:");
        gets(girilen_etiket);
        fflush(stdin);
        if(strstr(girilen_etiket,"-1"))
        {
            printf("\nFonksiyondan cikis yapildi!!.");
            exit(1);
        }
        strcpy(girilen_etiket_txt,girilen_etiket);
        strcat(girilen_etiket_txt,".txt");
        strcpy(girilen_etiket_ikinci,"[[");
        strcat(girilen_etiket_ikinci,girilen_etiket);
        strcat(girilen_etiket_ikinci,"]]");
        printf("Etiketin yeni halini giriniz:");
        gets(degisecek_etiket);
        fflush(stdin);
        // if ile degisecek stringin icerisinde bosluk bulursan onu _ buna cevir.strchr ile yap
        strcpy(degisecek_etiket_txt,degisecek_etiket);
        strcat(degisecek_etiket_txt,".txt");
        strcpy(degisecek_etiket_ikinci,"[[");
        strcat(degisecek_etiket_ikinci,degisecek_etiket);
        strcat(degisecek_etiket_ikinci,"]]");
        for(i=0; i<tmp; i++)
        {
            int z=0,donus=0;
            FILE *dosya_ac=fopen(dosyalar[i],"r");
            j=0;
            while(fgets(satir_yrd,100,dosya_ac)!=NULL)
            {
                strcpy(satir_list[j],satir_yrd);
                j++;
            }
            fclose(dosya_ac);
            for(k=0; k<j; k++)
            {
                if(strstr(satir_list[k],girilen_etiket_ikinci))
                {
                    fflush(stdin);
                    char *kelime = strtok(satir_list[k], ayrac);
                    while (kelime != NULL)
                    {
                        strcpy(cumlecik[z],kelime);
                        kelime = strtok(NULL,ayrac);
                        z++;
                    }
                    for(int n=0; n<z; n++)
                    {
                        if(strstr(cumlecik[n],girilen_etiket))
                        {
                            strcpy(cumlecik[n],degisecek_etiket_ikinci);
                            donus=n;
                        }
                    }
                    for(int dondur=0; dondur<tmp3; dondur++)
                    {
                        for(int b=0; b<z; b++)
                        {
                            if(strstr(etiketler[dondur],cumlecik[b])&&b!=donus)
                            {
                                char degisken[35];
                                strcpy(degisken,cumlecik[b]);
                                strcpy(cumlecik[b],"[[");
                                strcat(cumlecik[b],degisken);
                                strcat(cumlecik[b],"]]");
                                break;
                            }
                        }
                    }
                    strcpy(satir_list[k],cumlecik[0]);
                    for(int u=1; u<z; u++)
                    {
                        strcat(satir_list[k],cumlecik[u]);
                        fflush(stdin);
                    }
                    dosya_ac=fopen(dosyalar[i],"w+");
                    for(int x1=0; x1<j; x1++)
                    {
                        fputs(satir_list[x1],dosya_ac);
                    }
                    fclose(dosya_ac);
                    calisma_durumu++;
                }
            }
        }
        if(calisma_durumu>0)
        {
            char eski_dosya[100];
            char eski_dosya_ikinci[100];
            char yeni_dosya[100];
            char yeni_dosya1[100];
            char *tutucu;
            int index;
            for(int t=0; t<tmp; t++)
            {
                if(strstr(dosyalar[t],girilen_etiket_txt))
                {
                    strcpy(eski_dosya,dosyalar[t]);
                    strcpy(eski_dosya_ikinci,eski_dosya);
                    fflush(stdin);
                    tutucu=strstr(eski_dosya,girilen_etiket_txt);
                    index=tutucu-eski_dosya;
                    memmove(eski_dosya+index,degisecek_etiket_txt,30);
                    strcpy(yeni_dosya,eski_dosya_ikinci);
                    strcpy(yeni_dosya1,eski_dosya);
                    for(int don=0; don<tmp; don++)
                    {
                        if(strstr(dosyalar[don],girilen_etiket_txt))
                            strcpy(dosyalar[don],yeni_dosya1);
                    }
                    rename(yeni_dosya,yeni_dosya1);
                }
            }
            printf("ISLEM BASARILI BIR SEKILDE GERCEKLESTI.!\n");
        }
        else
            printf("ISLEM BASARISIZ!!");
        char abc[50];
        int gecici;
        int sonuc;
        for(i=0; i<tmp3; i++)
        {
            sonuc=strcmp(etk.etiketadi[i],girilen_etiket);
            if(sonuc==0)
            {
                strcpy(etk.etiketadi[i],degisecek_etiket);
            }
        }
        for(i=0; i<tmp3; i++)
        {
            for(j=i+1; j<tmp3; j++)
            {
                sonuc=strcmp(etk.etiketadi[i],etk.etiketadi[j]);
                if(sonuc==0)
                {
                    etk.tekrarsayi[j]=etk.tekrarsayi[j]+etk.tekrarsayi[i];
                    for(k=i; k<tmp3-1; k++)
                    {
                        strcpy(abc,etk.etiketadi[k]);
                        strcpy(etk.etiketadi[k],etk.etiketadi[k+1]);
                        gecici=etk.tekrarsayi[k];
                        etk.tekrarsayi[k]=etk.tekrarsayi[k+1];
                    }
                    tmp3--;
                }
            }
        }
        char etiketisim[30];
        char yetimetiket[30][100];
        int sayac=0,yetsayisi=0;
        for(i=0; i<tmp3; i++)
        {
            strcpy(etiketisim,etk.etiketadi[i]);
            for(j=0; j<tmp; j++)
            {
                sonuc=strstr(dosyalar[j],etiketisim);
                if(sonuc!=NULL)
                {
                    sayac++;
                    break;
                }
            }
            if(sayac==0)
            {
                strcpy(yetimetiket[yetsayisi],etiketisim);
                yetsayisi++;
            }
            sayac=0;
        }
        char adres[]="C:\\Users\\Furkan\\Desktop\\Universite";
        char outadres[100];
        strcpy(outadres,adres);
        strcat(outadres,"\\");
        strcat(outadres,"output.txt");
        FILE *output=fopen(outadres, "a+");
        fputs("[[Guncellenmis Etiketler]]    Tekrar Sayisi\n",output);
        for(k=0; k<tmp3; k++)
        {
            if(etk.tekrarsayi[k]==0)
                break;
            fprintf(output,"%-30s--> %-5d\n",etk.etiketadi[k],etk.tekrarsayi[k]);
        }
        fprintf(output,"\n\n\n");
        if(output==NULL)
        {
            printf("Dosya acilmadi.");
            exit(1);
        }
        fputs("Yetim Etiketler:\n",output);
        for(k=0; k<yetsayisi; k++)
        {
            fprintf(output,"%-30s\n",yetimetiket[k]);
        }
        fprintf(output,"\n");
    }
}

void yetim_etiket_guncelle(int tmp,char dosyalar[tmp][100],int tmp2,char yertutucu[tmp2][100],struct Etiket etk,int etiketsayisi)
{
    int i,j,sonuc,sayac=0,yetsayisi=0,k,istetiketsay=0;
    char etiketisim[50];
    char gecistetiket[50][100];
    char istenenetiket[50][100];
    char yetimetiket[50][100];
    char adres[]="C:\\Users\\Furkan\\Desktop\\Universite";
    for(i=0; i<etiketsayisi; i++)
    {
        strcpy(etiketisim,etk.etiketadi[i]);
        for(j=0; j<tmp; j++)
        {
            sonuc=strstr(dosyalar[j],etiketisim);
            if(sonuc!=NULL)
            {
                sayac++;
                break;
            }
        }
        if(sayac==0)
        {
            strcpy(yetimetiket[yetsayisi],etiketisim);
            yetsayisi++;
        }
        sayac=0;
    }
    char outadres[100];
    strcpy(outadres,adres);
    strcat(outadres,"\\");
    strcat(outadres,"output.txt");
    FILE *output=fopen(outadres, "a+");
    if(output==NULL)
    {
        //printf("Dosya acilmadi.");
        exit(1);
    }
    fputs("Yetim Etiketler:\n",output);
    for(k=0; k<yetsayisi; k++)
    {
        fprintf(output,"%-50s\n",yetimetiket[k]);
    }
    fprintf(output,"\n");
    sayac=0;
    for(i=0; i<tmp2; i++)
    {
        for(j=0; j<etiketsayisi; j++)
        {
            strcpy(etiketisim,etk.etiketadi[j]);
            sonuc=strstr(yertutucu[i],etiketisim);
            if(sonuc!=NULL)
            {
                sayac++;
                break;
            }
        }
        if(sayac==0)
        {
            strcpy(gecistetiket[istetiketsay],yertutucu[i]);
            istetiketsay++;
        }
        sayac=0;
    }
    char geckelime[40];
    char *tutucu;
    int index;
    for(k=0; k<istetiketsay; k++)
    {
        tutucu=strstr(gecistetiket[k],".txt");
        index=tutucu-gecistetiket[k];
        for(int l=0; l<index; l++)
        {
            geckelime[l]=gecistetiket[k][l];
        }
        geckelime[index]='\0';
        strcpy(istenenetiket[k],geckelime);
    }
    fputs("Istenen Etiketler:\n",output);
    for(k=0; k<istetiketsay; k++)
    {
        fprintf(output,"%-50s\n",istenenetiket[k]);
    }
    fprintf(output,"\n");
    char dersleradres[100];
    char dersleradr2[100];
    int derskodu=200;
    strcpy(dersleradres,adres);
    strcat(dersleradres,"\\");
    strcat(dersleradres,"Dersler");
    strcat(dersleradres,"\\");
    strcpy(dersleradr2,dersleradres);
    int sayac1=0;
    char gecicikelime[50];
    for(j=0; j<yetsayisi; j++)
    {
        strcpy(gecicikelime,yetimetiket[j]);
        for(k=0; k<strlen(gecicikelime); k++)
        {
            if(isupper(gecicikelime[k]))
                sayac1++;
        }
        if(sayac1<4)
        {
            strcat(dersleradres,yetimetiket[j]);
            strcat(dersleradres,".txt");
            FILE *yetime=fopen(dersleradres,"w");
            fprintf(yetime,"Dersin Kodu: BLM%d\n\n",derskodu);
            derskodu++;
            fprintf(yetime,"Dersin Adi: %s\n\n",yetimetiket[j]);
            fprintf(yetime,"Dersi Icerigi:");
            strcpy(dersleradres,dersleradr2);
        }
        sayac1=0;
    }
    derskodu=200;
}

int main()
{
    setlocale(LC_ALL, "Turkish");

    struct dirent *klasor;
    DIR *dir;
    char adres[]="C:\\Users\\Furkan\\Desktop\\Universite";
    char adres1[]="C:\\Users\\Furkan\\Desktop\\Universite";

    dir=opendir(adres);
    int var,sayi;
    char dosya[20];
    char nokta='.';
    char txt[]=".txt";

    struct dirent *klasor1;
    DIR *dir1;
    int tmp=0;
    int tmp2=0;
    char dosyalar[50][100];
    char yertutucu[20][100];
    while( (klasor=readdir(dir)) )
    {
        if(strchr(klasor->d_name,nokta)==0)
        {

            strcpy(dosya,klasor->d_name);
            strcat(adres,"\\");
            strcat(adres,dosya);
            dir1=opendir(adres);
            while((klasor1 = readdir(dir1)))
            {
                if(strstr(klasor1->d_name,txt))
                {
                    strcpy(dosyalar[tmp],adres);
                    strcat(dosyalar[tmp],"\\");
                    strcat(dosyalar[tmp],dosya);
                    strcat(dosyalar[tmp],"\\");
                    strcat(dosyalar[tmp],klasor1->d_name);
                    strcpy(yertutucu[tmp2],klasor1->d_name);
                    tmp++;
                    tmp2++;
                }
                strcpy(adres,adres1);
            }
        }
    }

    int i,k=0,l=0,m=0,n;
    char kelime[50];
    char satir_yrd[200];
    char satir_list[200][200];
    char etiketisim[50][100];
    int etiketsayisi=0;
    char etiketduzen[50][100];
    struct Etiket etk;

    for(i=0; i<tmp; i++)
    {
        FILE *dosya_ac=fopen(dosyalar[i],"r");
        if(dosya_ac==NULL)
            printf("acilmadi");
        int j=0;
        while(fgets(satir_yrd,100,dosya_ac)!=NULL)
        {
            strcpy(satir_list[j],satir_yrd);
            j++;

        }
        for(int p=0; p<j; p++)
        {
            int parantez1[20];
            int parantez2[20];
            char *sayma=strstr(satir_list[p],"[[");
            char *sayac=strstr(satir_list[p],"]]");
            char *adrestutucu=strstr(satir_list[p],"[[");
            char *adrestutucu1=strstr(satir_list[p],"]]");
            while(adrestutucu!=NULL)
            {
                if(adrestutucu1!=NULL)
                {
                    while(sayma!=NULL)
                    {
                        parantez1[k]=sayma-satir_list[p];
                        sayma=strstr(sayma+1,"[[");
                        k++;
                    }
                    while(sayac!=NULL)
                    {
                        parantez2[l]=sayac-satir_list[p];
                        sayac=strstr(sayac+1,"]]");
                        l++;
                    }
                    if(k==l)
                    {
                        for(m=0; m<l; m++)
                        {
                            n=parantez2[m]-parantez1[m]-2;
                            strncpy(kelime,satir_list[p]+parantez1[m]+2,n);
                            kelime[n]='\0';
                            strcpy(etiketisim[etiketsayisi],kelime);
                            etiketsayisi++;
                        }

                    }
                    k=0;
                    l=0;
                    adrestutucu1=strstr(adrestutucu1+1,"]]");
                }
                adrestutucu=strstr(adrestutucu+1,"[[");
            }
        }
        fclose(dosya_ac);
    }
    int num=0,sonuc;

    strcpy(etiketduzen[num],etiketisim[0]);
    num++;
    for(k=1; k<etiketsayisi; k++)
    {
        strcpy(etiketduzen[num],etiketisim[k]);
        num++;
        for(l=0; l<k; l++)
        {
            sonuc=strcmp(etiketduzen[num-1],etiketisim[l]);
            if(sonuc==0)
            {
                num--;
                memset(etiketduzen[num],0,sizeof(char)*100);
                break;
            }
        }
    }
    int tekrar;
    for(k=0; k<num; k++)
    {
        strcpy(etk.etiketadi[k],etiketduzen[k]);
        tekrar=0;
        for(l=0; l<etiketsayisi; l++)
        {
            sonuc=strcmp(etiketduzen[k],etiketisim[l]);
            if(sonuc==0)
                tekrar++;
        }
        etk.tekrarsayi[k]=tekrar;
    }
    char outadres[100];
    strcpy(outadres,adres1);
    strcat(outadres,"\\");
    strcat(outadres,"output.txt");
    FILE *output=fopen(outadres, "w");
    if(output==NULL)
    {
        printf("Dosya acilmadi.main");
        exit(1);
    }
    fputs("[[Etiketler]]                 Tekrar Sayisi\n",output);

    for(k=0; k<num; k++)
    {
        fprintf(output,"%-30s--> %-5d\n",etk.etiketadi[k],etk.tekrarsayi[k]);
    }
    fprintf(output,"\n\n\n");
    int switch_counter;
    printf("Dokuwiki Kocaeli Üniversitesi Projesi\n--ISLEM MENUSU--\n1.ETIKET ARAMA\n2.GUNCELLEME\n");
    printf("Lutfen yapmak istediginiz islemi seciniz:");
    scanf("%d",&switch_counter);
    fflush(stdin);
    switch(switch_counter)
    {
    case 1:
        etiket_bul(tmp,dosyalar,tmp2,yertutucu);
    case 2:
    {
        int guncelleme_switch_counter;
        printf("--GUNCELLEME MENUSU--\n1.ETIKET GUNCELLEME\n2.YETIM ETIKET GUNCELLEME\n");
        printf("Lutfen Guncelleme menusunde yapmak istediginiz islemi seciniz:");
        scanf("%d",&guncelleme_switch_counter);
        fflush(stdin);
        switch(guncelleme_switch_counter)
        {
        case 1:
        {
            guncelle(tmp,dosyalar,tmp2,yertutucu,etiketsayisi,etiketisim,etk);
        }

        case 2:

        {
            yetim_etiket_guncelle(tmp,dosyalar,tmp2,yertutucu,etk,num);
            printf("Yetim etiketler basariyla etikete donusturuldu!!.");
        }
        }
    }
    }
    return 0;

}
