#include <stdio.h>
#include <string.h>
#include <dirent.h>

int menu(){
	int secim;
	printf("\n\tDOKUWiKi KOU\n\n") ;
	printf("\t1- ARAMA YAPMA \n") ;
	printf("\t2- GUNCELLEME \n") ;
	printf("\t3- YAZMA \n") ;
	printf("\t0- PROGRAMI KAPAT \n") ;
	printf("\t1- Seciminiz   :  ") ;
	scanf("%d", &secim) ;

	system("cls");

	return secim;

}

int main (){
    system("cls");
	int secim= menu();
	while( secim != 0 )
	{
		switch(secim )
		{
			case 1: arama();  break;
			//case 2: //guncelle();  break;
			//case 3: yazma();  break;
			case 0: break;
			default : printf("Hatali secim yaptiniz ! \n") ;

		}
		secim= menu();

	}
	printf("-Program Kapatıldı-\n") ;

	return 0;
}

void arama(){

    FILE *fp,*fp2;
    fp = fopen("textler.txt","w");
    fp2 = fopen("altklasorler.txt","w");
    char path[200];
    strcpy(path, "C:/Users/emirc/Desktop/codeblocks/alttan prolab 1/dokuwiki kou/universite");
    listFilesRecursively(path,fp,fp2);
    fclose(fp);
    fclose(fp2);

    //----------------------------------Textin içindeki txt file isimlerini char pointerina atýyoruz

    fp = fopen("textler.txt", "r");
    fseek(fp, 0, 2);
    int length = ftell(fp);
    fseek(fp, 0, 0);
    char *dizi2 = malloc(sizeof(char) * (length+1));
    char ch2;
    int t3 = 0;

    while ((ch2 = fgetc(fp)) != EOF) {
        dizi2[t3] = ch2;
        t3++;
    }
    fclose(fp);
    dizi2[t3] = '\0';
//....
    fp2 = fopen("altklasorler.txt", "r");
    fseek(fp2, 0, 2);
    int length2 = ftell(fp2);
    fseek(fp2, 0, 0);
    char *altklasorad0 = malloc(sizeof(char) * (length2+1));
    char adch;
    int t2 = 0;

    while ((adch = fgetc(fp2)) != EOF) {
        altklasorad0[t2] = adch;
        t2++;
    }
    fclose(fp2);
    altklasorad0[t2] = '\0';

//----------------------------------char pointerýndaki her bi txt dosyasý ismini 2d char arrayinin elemaný yapýyoruz

    char textadlari[20][40];
    const char *delp;
    int r = 0;

    delp = strtok (dizi2, "/");
    while (delp != NULL)  {
        strcpy(textadlari[r], delp);
        delp = strtok (NULL, "/");
        r++;
    }
    strcpy(textadlari[r], "$");
//.....
    char altklasorad[20][40];
    const char *delp2;
    int r2 = 0;

    delp2 = strtok (altklasorad0, "/");
    while (delp2 != NULL)  {
        strcpy(altklasorad[r2], delp2);
        delp2 = strtok (NULL, "/");
        r2++;
    }
    strcpy(altklasorad[r2], "$");

    //----------------------------------dosyalardaki etiketler cıkartılacak

    FILE *fptr;

    int d=0,f=0,i=0,i2=0,i3=0;
    char path2[200],buffer[10000],buff2[50000];
    char etiketler[20][40];

    while(strcmp(altklasorad[i], "$") != 0)
    {
        i2=0;
        while(strcmp(textadlari[i2], "$") != 0)
        {
            strcpy(path2, "C:/Users/emirc/Desktop/codeblocks/alttan prolab 1/dokuwiki kou/universite/");
            strcat(path2, altklasorad[i]);
            strcat(path2, "/");
            strcat(path2, textadlari[i2]);

            fptr = fopen(path2,"r");

            char buff[50000];

            while (fgets(buff, sizeof(buff), fptr) != NULL)
            {
                char buff2[500];
                size_t len = strlen(buff);

                if (len > 0 && buff[len - 1] == '\n')
                {
                    buff[len - 1] = '\0';
                }
                int k=0;
                int a=0,b=0;
                while (buff[k] != '\0') {

                    if(a==0){
                        memset(buff2, 0, sizeof buff2);
                        i3=0;
                    }
                    if(a==1){
                        buff2[i3]=buff[k];
                        i3++;
                    }
                    if(buff[k]=='[' && buff[k-1]=='['){
                            a=1;
                    }
                    else if(buff[k+1]==']' && buff[k+2]==']' && a==1){
                            a=0;
                            strcpy(etiketler[f], buff2);
                            f++;
                            memset(buff2, 0, sizeof buff2);
                            i3=0;
                            b++;
                    }
                k++;
                }
            }
        fclose(fptr);
        i2++;
        }
    i++;
    }
    strcpy(etiketler[f], "$");

/////////////////////////////////  yetim listeleme

    char yetimler[20][40];
    int w=0,w2=0,w3=0;
    char buff3[50000];
    while(strcmp(etiketler[w], "$") != 0)
    {
        int flag=0,flag2,w2=0;
        while(strcmp(textadlari[w2], "$") != 0)
        {
            flag2=0;
            char *s;
            s = strstr(textadlari[w2], etiketler[w]);
            if (s != NULL) flag = 1;
            w2++;
        }
        if (flag == 0){
            char *y;
            y = strstr(buff3, etiketler[w]);
            if (y == NULL) flag2 = 1;

            if(flag2 == 1){
                strcpy(yetimler[w3],etiketler[w]);
                strcat(buff3, etiketler[w]);
                w3++;
                strcpy(yetimler[w3],"$");
                flag2=0;
            }
        }
    w++;
    }
    printf("YETIM ETIKETLER :\n");
    int cmp=0;
    while(strcmp(yetimler[cmp], "$") != 0){
        printf("%s | ",yetimler[cmp]);
        cmp++;
    }


    printf("\n\nISTENEN ETIKETLER :\n");

    char istenenler[20][40];
    char temp[100];
    int wi=0,w2i=0,t=0;
    char buff3i[50000];
    while(strcmp(textadlari[wi], "$") != 0)
    {
        int flagi=0,flag2i,w2i=0;
        while(strcmp(etiketler[w2i], "$") != 0)
        {
            flag2i=0;
            char *s2;
            strcpy(temp,etiketler[w2i]);
            strcat(temp,".txt");
            s2 = strstr(temp, textadlari[wi]);
            if (s2 != NULL) flagi = 1;
            w2i++;
        }
        if (flagi == 0){
            char *y2;
            y2 = strstr(buff3i, textadlari[wi]);
            if (y2 == NULL) flag2i = 1;

            if(flag2i == 1){
                printf("%s | ",textadlari[wi]);
                strcpy(istenenler[t],textadlari[w2i]);
                strcat(buff3i, textadlari[w2i]);
                t++;
                strcpy(istenenler[t],"$");
                flag2i=0;
            }
        }
    wi++;
    }

    char wrd[256];
    int tmp;
    int p = 0;
    printf("\n\nAranacak İfade Kac Kelime  :  ");
    scanf("%d",&tmp);
    printf("           Kelimeyi Girin  :  ");
    scanf("%s",&wrd);

    etiketkontrol(textadlari,wrd,altklasorad);

}

void listFilesRecursively(char *basePath,FILE *fp, FILE *fp2){

    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            char *m = strstr(dp->d_name, ".txt");
            if(m != NULL)
            {
                fputs(dp->d_name, fp);
                fputs("/", fp);
            }

            char *m2 = strstr(dp->d_name, ".");
            if(m2 == NULL)
            {
                fputs(dp->d_name, fp2);
                fputs("/", fp2);
            }

            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            listFilesRecursively(path,fp,fp2);
        }
    }

    closedir(dir);
}

void etiketkontrol(char textadlari[20][40], char wrd[256], char altklasorad[20][40]){
    FILE *fp;
    char buffer[100000];;
    int n,m,j,line,col;
    int i=0;
    int p = 0;
    char path[200];

    m = strlen(wrd);

    while(strcmp(altklasorad[i], "$") != 0) {
        p=0;
        while(strcmp(textadlari[p], "$") != 0)
        {
            strcpy(path, "C:/Users/emirc/Desktop/codeblocks/alttan prolab 1/dokuwiki kou/universite/");
            strcat(path, altklasorad[i]);
            strcat(path, "/");
            strcat(path, textadlari[p]);

            fp = fopen(path,"r");

            if (fp == NULL)
            {
                //perror("Error while opening the file.\n");

            }

            char *y, *s, buff[500];
            int flag = 0;

            while (fgets(buff, sizeof(buff), fp) != NULL)
            {
                size_t len = strlen(buff);

                if (len > 0 && buff[len - 1] == '\n')
                {
                    buff[len - 1] = '\0';
                }

                y = strstr(buff, wrd);

                if (y != NULL)
                {

                    printf("        - kelimenin konumu -> %s \n",textadlari[p]);
                    flag = 1;
                }

            }
             fseek(fp, 0, 0);
            indexOf(fp, wrd, &line, &col);

            if (line != -1)
                printf("                              satır: %d, kolon: %d\n", wrd, line + 1, col + 1);
            else


    fclose(fp);
    p++;

    }

    i++;

    }
}

int indexOf(FILE *fptr, const char *word, int *line, int *col){
    char str[5000];
    char *pos;

    *line = -1;
    *col  = -1;

    while ((fgets(str, 5000, fptr)) != NULL)
    {
        *line += 1;

        pos = strstr(str, word);

        if (pos != NULL)
        {
            *col = (pos - str);
            break;
        }
    }

    if (*col == -1)
        *line = -1;

    return *col;
}

