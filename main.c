#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ogrenci{
		char ad[20];             //OGRENCILERIN BILGILERININ TUTULDUGU YAPIDIR.                  
		char soyad[20];
		char id[5];                
		char tc[20];
		char cinsiyet[2];
		char dogum_tarihi[20];
        char tel[20];
        char eposta[30];
    }ogrcim;

void ogrenciGuncelle();                  
void ogrenciEkle();                    //FONKSIYONLARIN TANIMI
void ogrenciListele();
void ogrenciSil();
void menu();

int main()
{
	menu();

}

void ogrenciEkle()
{
    int sinir,i=1;
	ogrcim *ogrenciobj,*ogrenciobj1;
	ogrenciobj=(ogrcim*)calloc(1,sizeof(ogrcim));               //OGRENCILERIN BILGILERINI ICIN BELLEK TALEBI YAPIYORUZ.
    ogrenciobj1=(ogrcim*)calloc(1,sizeof(ogrcim));             // Bellekte int değer icin yer tutar.
	FILE *ogrencidb;
	ogrencidb=fopen("userfile.txt","a+");                     //Okumak ve yazmak için dosya açar.
	fflush(stdin);                                           //Çıkış akışları için, akışın arabelleğindeki yazılmamış veriyi ilgili çıkış aygıtına yazar.
	printf("Ogrencinin adini giriniz :");
    gets((*ogrenciobj).ad);
	printf("Ogrencinin soyadini giriniz :");
	scanf("%s",(*ogrenciobj).soyad);
	printf("Ogrencinin idsini giriniz :");
	scanf("%s",(*ogrenciobj).id);
	printf("Ogrencinin tcsini giriniz :");
    scanf("%s",(*ogrenciobj).tc);
    
    
    fseek(ogrencidb,0,SEEK_END);
    sinir=ftell(ogrencidb)/sizeof(ogrcim);         //BU KOD ILE KAC ADET OGRENCI OLDUGUNU BULUYORUZ.
    rewind(ogrencidb);
	while(i<=sinir)                                //BU DONGU ARACILIGIYLA KAYDIN DOSYADA OLUP OLMADIGINA BAKIYORUZ.
    {
        fread(ogrenciobj1,sizeof(ogrcim),1,ogrencidb);    
        fseek(ogrencidb,2,SEEK_CUR);       //2 bayt kaydirmamizin sebebi dosyada kisi bilgileri alt alta siralanmasi "\n" hafizada 2 bayt yer kaplar.
        if(strcmp(ogrenciobj1->id,ogrenciobj->id)==0)   // IKI DIZI ARASINDA KARSILASTIRMA
        {
            printf("\ngirilen ogrenci numarasi daha onceden bulundugu icin kaydiniz yapilamadi...\n");
            menu();
        }
        i++;
    }
    rewind(ogrencidb);         //dosyayı okuma modunda acar.
	printf("Ogrencinin dogum tarihi giriniz(G.A.Y) :");
    scanf("%s",(*ogrenciobj).dogum_tarihi);
    printf("Ogrencinin cinsiyetini giriniz (E/K) :");
	scanf("%s",(*ogrenciobj).cinsiyet);
	printf("Ogrencinin telefon numarasini giriniz :");
	scanf("%s",(*ogrenciobj).tel);
	printf("Ogrencinin e-postasini giriniz :");
	scanf("%s",(*ogrenciobj).eposta);
	fwrite(ogrenciobj,sizeof(ogrcim),1,ogrencidb);
	fprintf(ogrencidb,"\n");
	printf("\nkayit basari ile eklendi...\n");
	fclose(ogrencidb);
    free(ogrenciobj1);        //tahsis edilen bellek bosaltiliyor.
	free(ogrenciobj);
	menu();
}
void ogrenciSil()
{
	ogrcim *ogrenciobj;
	char num[10];
	int say=0,j=0;
	FILE  *ogrencidb;
	FILE  *tempogrencidb;                            //geçici bir dosya oluşturup üstüne yazmak için dosya tanımı. 
	ogrencidb=fopen("userfile.txt","r+");           //dosyayı okuma için acılır ve aynı zamanda yazma da yapılır.
	ogrenciobj=(ogrcim*)calloc(1,sizeof(ogrcim));
	tempogrencidb=fopen("tempuserfile.txt","w+");   //dosyayı yazma modunda açılır ve okuma da yapılır.
	if(ogrencidb==NULL)
    {
        printf("dosya acilamadi.\n");
        exit(1);
    }
    printf("Silinecek ogrencinin idsini girin : ");
    scanf("%s",num);
    int sinir,i=1;
    fseek(ogrencidb,0,SEEK_END);                  //dosya konum göstericisini istediğimiz miktarda ileri veya geri götürmemizi sağlar.
    sinir=ftell(ogrencidb)/sizeof(ogrcim);       //bu kod vasitasiyla dosya kac adet ogrenci oldugunu buluyoruz.//dosyanın sonuna giderek...
    rewind(ogrencidb);
    while(i<=sinir)
    {
        fread(ogrenciobj,sizeof(ogrcim),1,ogrencidb);
        fseek(ogrencidb,2,SEEK_CUR);
        if(strcmp((*ogrenciobj).id,num))
        {
            fwrite(ogrenciobj,sizeof(ogrcim),1,tempogrencidb);
            fprintf(tempogrencidb,"\n");
        }
        if(strcmp((*ogrenciobj).id,num)==0)
        {
            say++;                        // bu sayac vasitasiyla kaydin dosyada bulunup bulunmadigini kontrol ediyoruz.
        }
            i++;
    }

	free(ogrenciobj);

  if(say==0)  //kayit dosyada bulunamadiysa olustudurdugumuz ikinci dosyayi siliyoruz.
  {
      fclose(ogrencidb);
      fclose(tempogrencidb);
      remove("tempuserfile.txt");
      printf("kayit bulunamadi...\n");
      free(ogrenciobj);
      menu();
  }
  else if(say!=0)  //kayit dosyada bulunduysa asil dosyayi silip olusturdumuz ikinci dosyanin asil dosya olarak degistirip silme islemini tamamliyoruz.
  {
      fclose(ogrencidb);
      fclose(tempogrencidb);
      remove("userfile.txt");
      rename("tempuserfile.txt","userfile.txt");
      printf("kayit bulundu...\n");
      printf("kayit basari ile silindi...\n");
      free(ogrenciobj);
      menu();

  }

}

void menu()
{
	int tercih;
	printf("\n********************\n");
	printf("1-Ogreci Kaydi Ekle\n");
	printf("2-Ogrenci Bilgi Duzenle\n");
	printf("3-Ogrenci Kaydi Sil\n");
	printf("4-Ogrenci Listele\n");
	printf("5-Programdan Cik\n");
	printf("6-Ekrani Temizle\n");
    printf("\n********************\n");
    printf("Seciminiz?[1-5] : ");
    scanf("%d",&tercih);
	if(tercih==6)
    {
        system("cls");
        menu();
    }
	if(tercih==5)
	exit(0);
	while(tercih!=5)
	{
		switch(tercih)
		{
           case 1:{ogrenciEkle();break;}
           case 2:{ogrenciGuncelle();break;}
           case 3:{ogrenciSil();break;}
           case 4:{ogrenciListele();break;}
		}
	}
}

void ogrenciListele()
{
    ogrcim *ogrenciobj;
    FILE *ogrencidb;
    ogrencidb=fopen("userfile.txt","r+");
    if(ogrencidb==NULL)
    {
        printf("dosya acilamadi.\n");
        exit(1);
    }
    ogrenciobj=calloc(1,sizeof(ogrcim));
    int i=0,sinir,j=1;
    fseek(ogrencidb,0,SEEK_END);
    sinir=ftell(ogrencidb)/sizeof(ogrcim); //bu kod vasitasiyla dosyada kac adet ogrenci oldugunu buluyoruz.
    rewind(ogrencidb);
    printf(" AD                     |SOYAD              |ID                  |TC               |CINSIYET            |TELEFON                |DOGUMTARIHI            |E-POSTA                |            ");
    printf("\n***********************************************************************************************************************************************************************************\n");
    while((i/sizeof(ogrcim))<sinir)
       {
          fseek(ogrencidb,i,SEEK_SET);
          fread(ogrenciobj,sizeof(ogrcim),1,ogrencidb);
          printf("%d- %-20s %-20s %7s %27s %5s %30s %25s %30s ",j,(*ogrenciobj).ad,(*ogrenciobj).soyad,(*ogrenciobj).id,(*ogrenciobj).tc,(*ogrenciobj).cinsiyet,(*ogrenciobj).tel,(*ogrenciobj).dogum_tarihi,(*ogrenciobj).eposta);
          printf("\n-----------------------------------------------------------------------------------------------------------------------------\n");
          i+=sizeof(ogrcim)+2;
          j++;
       }
if(sinir==0)
    printf("listelenecek herhangi bir kayit bulunmamaktadir...\n");
    free(ogrenciobj);
    fclose(ogrencidb);
    menu();
}


void ogrenciGuncelle()
{
    char num[10],guncel;
    int secim,kontr=0;
    FILE *ogrencidb,*tempogrencidb;    //bilgileri guncellemek icin iki farkli dosya kullaniyoruz.
    ogrcim *ogrenciobj;
    tempogrencidb=fopen("tempuserfile.txt","w+");   
    ogrencidb=fopen("userfile.txt","a+");
    ogrenciobj=calloc(1,sizeof(ogrcim));
    printf("\nGuncellemek istediginiz idsini numarasini girin :");
    scanf("%s",&num);
    int sinir,i=1;
    fseek(ogrencidb,0,SEEK_END);
    sinir=ftell(ogrencidb)/sizeof(ogrcim);  //bu kod vasitasiyla dosyada kac adet ogrenci oldugunu buluyoruz.
    rewind(ogrencidb); //yazma islemi bittikten sonra kapattık ve okumak icin geri actık.

    while(i<=sinir)
    {

        fread(ogrenciobj,sizeof(ogrcim),1,ogrencidb);
        fseek(ogrencidb,2,SEEK_CUR);
        if(strcmp(ogrenciobj->id,num)!=0)
        {
            fwrite(ogrenciobj,sizeof(ogrcim),1,tempogrencidb);
            fprintf(tempogrencidb,"\n");
        }
        if(strcmp(ogrenciobj->id,num)==0)
        {
            printf("Ogrenci bulunmustur...\n\n");
            back: printf("Guncellemek istediginiz ogrencinin bilgileri>>\n\n");
            printf("\nAD :%s ",(*ogrenciobj).ad);
            printf("\nSOYAD :%s ",(*ogrenciobj).soyad);
            printf("\nID: %s",(*ogrenciobj).id);
            printf("\nTC :%s",(*ogrenciobj).tc);
            printf("\nTELEFON :%s",(*ogrenciobj).tel);
            printf("\nCINSIYET :%s",(*ogrenciobj).cinsiyet);
            printf("\nD.T :%s",(*ogrenciobj).dogum_tarihi);
            printf("\nEPOSTA :%s",(*ogrenciobj).eposta);
            printf("\n-----------------------\n");
           back2: printf("\nisim[1] || soyisim[2] || tc[3] || id[4] || tel[5] || cinsiyet[6] || ||dogumtarihi[7] || || eposta[8] || tum bigiler[9]\n");
            printf("\nSecimiminizi giriniz...");
            scanf("%d",&secim);
            switch(secim)    //switch-case yardimiyla guncelenmek istenen kullanicinin hangi bilgisi uzerinde degisiklik yapilmasi gerektigini ogreniyoruz.
            {
            case 1:{
                printf("Ogrencinin adini girin :");
	            scanf("%s",(*ogrenciobj).ad);
	            break;
              }
            case 2:{
                 printf("Ogrencinin soyadini girin :");
	             scanf("%s",(*ogrenciobj).soyad);
	             break;
            }
            case 3:{
                printf("Ogrencinin tcsini girin :");
                scanf("%s",(*ogrenciobj).tc);
                break;
            }
            case 4:{
                printf("Ogrencinin idsini girin :");
	            scanf("%s",(*ogrenciobj).id);
	            break;
            }
            case 5:{
                 printf("Ogrencinin telefon numarasini girin :");
	             scanf("%s",(*ogrenciobj).tel);
	             break;
            }
            case 6:{
                
                printf("Ogrencinin cinsiyetini girin :");
	            scanf("%s",(*ogrenciobj).cinsiyet);
	            break;
            }
            case 7:{
                 printf("Ogrencinin dogum tarihi girin :");
                 scanf("%s",(*ogrenciobj).dogum_tarihi);
                 break;
            }
            case 8:{
               printf("Ogrencinin epostasini girin :");
               scanf("%s",(*ogrenciobj).eposta);
               break;     
            }    
            case 9:{
                printf("Ogrencinin adini girin :");
	             scanf("%s",(*ogrenciobj).ad);
	             printf("Ogrencinin soyadini girin :");
                 scanf("%s",(*ogrenciobj).soyad);
                 printf("Ogrencinin tcsini girin :");
                 scanf("%s",(*ogrenciobj).tc);
                 printf("Ogrencinin idsini girin :");
	             scanf("%s",(*ogrenciobj).id);
	             printf("Ogrencinin telefon numarasini girin :");
	             scanf("%s",(*ogrenciobj).tel);
                 printf("Ogrencinin cinsiyetini girin :");
	             scanf("%s",(*ogrenciobj).cinsiyet);
	             printf("Ogrencinin dogum tarihi girin :");
                 scanf("%s",(*ogrenciobj).dogum_tarihi);
                 printf("Ogrencinin epostasini girin :");
                 scanf("%s",(*ogrenciobj).eposta);
	             break;
            }
            
            
            default :{
                system("cls");
            printf("yanlis secim yaptiniz!!!\n");
            goto back;}       //eger kullanici yanlis bir secim yaparsa onu uyarip goto komutuyla tekrar secim yapmasini sagliyoruz.

            }
            printf("\nGuncelleme islemine devam etmek icin 1'e ,islemi sonlandirmak icin herhangi bir tusa basiniz\n");
            guncel=getch();  //bu kod arailigiyla kullanicinin guncelleme islemine devam etmek isteyip istemedigini kontrol ediyoruz.
            if(guncel=='1') //Girilen karakteri okuma işlemi için ENTER tuşuna basılması gerekir
            {
                goto back2;
            }
             fwrite(ogrenciobj,sizeof(ogrcim),1,tempogrencidb);
             fprintf(tempogrencidb,"\n");
             kontr++;        //bu sayac araciligiyla guncellenmek istenen kullanicinin bulunup bulunmadigini kontrol ediyoruz.


            }
            i++;
        }

    if(kontr==0)
    {
        printf("\nguncellemek istediginiz ogrenci bulunamamistir.\n");
        fclose(ogrencidb);
        fclose(tempogrencidb);
        free(ogrenciobj);
        remove("tempuserfile.txt");
        menu();
    }
    if(kontr!=0)
    {
            fclose(ogrencidb);
             fclose(tempogrencidb);
             remove("userfile.txt");
             rename("tempuserfile.txt","userfile.txt");
             free(ogrenciobj);
             printf("\nkayit basariyla guncellenmistir...\n");
             menu();
    }
}
