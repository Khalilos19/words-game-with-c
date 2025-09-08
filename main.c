#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define Max_Mots 336532
#define Max_Possible 336532
#define Max_Length 50
#define nbr_car 26

int saisie_taille() {
    char taille[50];
    do {
        fflush(stdin);
        printf("\nTaper la taille (7/8/9) du mot le plus long a retrouver: ");
        gets(taille);
        if(strlen(taille) != 1 || !(taille[0] == '7' || taille[0] == '8' || taille[0] == '9'))
            printf("La taille qui vous avez saisit taille invalide!\n");

    } while (strlen(taille) != 1 || !(taille[0] == '7' || taille[0] == '8' || taille[0] == '9'));
    return atoi(taille);
}

int saisie_mult() {
    char taille[50];
    do {
        printf("Taper la taille (nombre pair) du mot le plus long a retrouver: ");
        fgets(taille, sizeof(taille), stdin);
        if(!(atoi(taille) >= 2 && atoi(taille) <= 26 && atoi(taille) % 2 == 0 && atoi(taille) > 0 ))
            printf("la taille doit etre un entier inferieur a 26, paire, positive et non nul\n");

    } while (!(atoi(taille) >= 2 && atoi(taille) <= 26 && atoi(taille) % 2 == 0 && atoi(taille) > 0));

    return atoi(taille);
}

char Cons_Voy(int i) {
    char c[50];
    do {
        fflush(stdin);
        printf("Caractere %i consonne (c/C) ou voyelle (v/V) : ", i+1);
        gets(c);
    } while (strlen(c) != 1 || !(c[0] == 'C' || c[0] == 'c' || c[0] == 'V' || c[0] == 'v'));
    return c[0];
}
char Alea_caractere(char t) {
    char car;
    char voyelles[] = {'a', 'e', 'i', 'y', 'u', 'o'};
    char consonnes[] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n', 'p', 'q', 'r', 's', 't' ,'v', 'w' ,'x','z'};
    if (t == 'v' || t == 'V') {
        car = voyelles[rand() % 6];
    } else if (t == 'c' || t == 'C') {
        car = consonnes[rand() % 20];
    }
    return car;
}

void Supp_Accents(char Mots[Max_Mots][Max_Length],int i,int j){
            switch (Mots[i][j]) {
                case 'à':
                case 'â':
                case 'ä':
                    Mots[i][j] = 'a';
                    break;
                case 'é':
                case 'è':
                case 'ê':
                case 'ë':
                    Mots[i][j] = 'e';
                    break;
                case 'î':
                case 'ï':
                    Mots[i][j] = 'i';
                    break;
                case 'ô':
                case 'ö':
                    Mots[i][j] = 'o';
                    break;
                case 'ù':
                case 'û':
                case 'ü':
                    Mots[i][j] = 'u';
                    break;
                case 'ÿ':
                    Mots[i][j] = 'y';
                    break;
                case 'ç':
                    Mots[i][j] = 'c';
                    break;
                default:
                    break;
            }
}

void matrice(char Mots[Max_Mots][Max_Length]) {
    int nb_mots = 0, stop = 0, i, j;
    char line[Max_Length];
    FILE* file = fopen("dictionnaire.txt", "r");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier\n");
        return;
    } else {
        while (fgets(line, sizeof(line), file) != NULL && !stop) {
            char* token = strtok(line, " \n");
            while (token != NULL && !stop) {
                if (nb_mots < Max_Mots) {
                    strncpy(Mots[nb_mots], token, Max_Length - 1);
                    Mots[nb_mots][Max_Length - 1] = '\0';
                    nb_mots++;
                } else {
                    printf("Espace Insuffisant\n");
                    stop = 1;
                }
                token = strtok(NULL, " \n");
            }
        }
    }
    fclose(file);
    for (i = 0; i < nb_mots; i++) {
        for (j = 0; Mots[i][j] != '\0'; j++) {
                Supp_Accents(Mots,i,i);

        }
    }
    for (i = 0; i < nb_mots; i++) {
        for (j = 0; Mots[i][j] != '\0'; j++) {
                Mots[i][j] = toupper(Mots[i][j]);
        }}
}

void Mots_Possible(char Mots[Max_Mots][Max_Length], char Lettres[nbr_car], char Possible[Max_Possible][Max_Length], int taille_un,int *size) {
    int i, j, k, stop;
    char copy[nbr_car];
    for(k=0;k<Max_Mots;k++)
        strcpy(Possible[k],"")
        ;
    for (i = 0; i < Max_Mots; i++) {
        stop = 0;
        j = 0;
        for (k = 0; k < taille_un; k++) {
            copy[k] = Lettres[k];
        }
        while (j < strlen(Mots[i]) && stop == 0) {
            k = 0;
            stop = 1;
            while (k < taille_un && stop == 1) {
                if (Mots[i][j] == copy[k]) {
                    copy[k] = '*';
                    stop = 0;
                    j++;}
                else if (Mots[i][j] == '-'){
                    stop = 0;
                    j++;
                }
                else
                    k++;
            }
            if (k == taille_un) {
                stop = 1;
            }
        }
        if (stop == 0) {
            strcpy(Possible[*size], Mots[i]);
            (*size)++;
            }
    }
}

int valid (char *ch,char Possible[Max_Possible][Max_Length],int size){
    int i ,valid=0;
    for(i=0;i<size;i++){
        if (strcmp(Possible[i],ch) == 0)
            valid = 1;
    }
    return valid;
}

int plus_long (char *ch,char Possible[Max_Possible][Max_Length],int size){
    int i ,max=strlen(Possible[0]),valid=0;
    for(i=0;i<size;i++){
        if (strlen(Possible[i])>max)
            max = strlen(Possible[i]);
    }
        if (strlen(ch) == max)
            valid=1;
    return valid;
}

void test(int *won, int *attemp, char ch[Max_Length], char Possible[Max_Possible][Max_Length], int size, char mot[Max_Length]) {
    if (valid(ch, Possible, size) && plus_long(ch, Possible, size)) {
        printf("VOUS GAGNEZ! Le mot que vous avez saisi est correct et le plus long");
        *won = 1;
        strcpy(mot, ch);
    } else if (valid(ch, Possible, size) && !plus_long(ch, Possible, size)) {
        printf("Le mot que vous avez saisi est correect mais pas le plus long");
        (*attemp)++;
        strcpy(mot, ch);
    } else {
        printf("Le mot que vous avez saisi n'est pas correct");
        (*attemp)++;
        strcpy(mot,"");
    }
}

void Recherche(char J1[nbr_car][Max_Length], char J2[nbr_car][Max_Length], int j1, int j2, int *stop, char ch[Max_Length]) {
    int i;

    for (i=0; i<strlen(ch); i++) {
        ch[i] = toupper(ch[i]);
    }

    if (j1>=1 || j2>=1) {
        for (i=0; i<j2; i++) {
            if (strcmp(J2[i], ch) == 0) {
                *stop = 2;
                return;
            }}

        for(i=0;i<j1; i++) {
            if (strcmp(J1[i], ch) == 0) {
                *stop = 1;
                return;
            }}}
}

char continuer(){
    char r[50];
    int rejouer;
    do{
        fflush(stdin);
        printf("\nVous voulez continuer ? Repondez par 'o' si oui , 'n' sinon : ");
        gets(r);
    }while(strlen(r)!=1 || !(r[0] == 'o' || r[0] == 'O' || r[0] == 'n' || r[0] == 'N'));
        if (strcmp(r, "o") == 0 || strcmp(r, "O") == 0)
           rejouer = 1;
        else
           rejouer = 0;
    return rejouer;
}

int main() {
    char choix[2],ch1[Max_Length],ch2[Max_Length],ch[Max_Length];
    char Lettres[nbr_car];
    int taille_un,taille_deux,size=0;
    static char Mots[Max_Mots][Max_Length];
    static char Possible[Max_Possible][Max_Length];
    static char mot[Max_Length],Mots_Saisie[nbr_car][Max_Length];
    char J1[nbr_car][Max_Length],J2[nbr_car][Max_Length];
    int i=0,k=0,attemp = 1, won = 0, j = 0,max=0,max1=0,max2=0,j1=0,j2=0,manche=0,stop=0,rejouer,s1=0,s2=0;
    int J1_score[50],J2_score[50];
    int score_totale1=0,score_totale2=0;
    clock_t start, end;
    double seconds;
    double seconds_total = 0;

    printf("                                    J E U   D E   M O T S                               \n");
    printf("1. Jouer a un\n");
    printf("2. Jouer a un a un sous contrainte de temps\n");
    printf("3. Jouer a deux\n");
    printf("0. Quitter\n");
    do {
        fflush(stdin);
        printf("\n                Votre choix = ");
        gets(choix);
    } while (strlen(choix) != 1 || !(choix[0] == '0' || choix[0] == '1' || choix[0] == '2' || choix[0] == '3'));
    switch (atoi(choix)) {
        case 1:
            srand(time(NULL));
            taille_un = saisie_taille();
            for (i = 0 ; i < taille_un; i++) {
                Lettres[i] = Cons_Voy(i);
            }
            printf("\n");

            for (i = 0; i < taille_un; i++) {
                Lettres[i] = toupper(Alea_caractere(Lettres[i]));
                printf("  ||  %c", Lettres[i]);
            }
            printf("\n");

            matrice(Mots);
            Mots_Possible(Mots,Lettres ,Possible,taille_un,&size);

  while ((attemp<=taille_un) && (!won)) {
        stop=0;
        fflush(stdin);
        printf("\n %i-    ", attemp);
        gets(ch);
        for(i=0;i<strlen(ch);i++) {
            ch[i] =toupper(ch[i]);
        }
    for(i=0;i<j;i++){
        if(strcmp(Mots_Saisie[i],ch)==0)
                stop=1;
        }
        if(stop==1){
            printf("Le mot que vous avez saisi est correct mais vous l'avez deja tape!");
            attemp++;}
        else{
            test(&won, &attemp, ch, Possible, size, mot);
            if(!strcmp(mot,"")==0){
            strcpy(Mots_Saisie[j], mot);
            j++;}}}
            printf("\n\n");
    for (i = 0; i < j; i++) {
       printf("\n%s(%d)", Mots_Saisie[i], strlen(Mots_Saisie[i]));
}
    max = 0;
    for (i = 0; i < j; i++) {
      if (strlen(Mots_Saisie[i]) > max)
        max = strlen(Mots_Saisie[i]);
}
       printf("\n\n------------------------------ Votre Score = %i ------------------------------\n\n",max);
    for (i = 0; i < taille_un; i++) {
                printf("  ||  %c", Lettres[i]);
            }
            max = 0;
    for (i=0; i<size; i++){
       if (strlen(Possible[i])>max)
           max = strlen(Possible[i]);
    }
    printf("\n\n1.Afficher le/les mot(s) le/les plus long(s)\n");
    printf("2.Afficher tous les mots possibles\n");
    do {
        fflush(stdin);
        printf("\n                Votre choix = ");
        gets(choix);
    } while (strlen(choix) != 1 || !(choix[0] == '1' || choix[0] == '2'));
    switch(atoi(choix)){
        case 1:
            for (i=0; i<size; i++){
                if (strlen(Possible[i]) == max){
                    printf("%s\n",Possible[i]);
                }
            }
            break;
        case 2:
            for (i=0; i<size; i++){
                printf("%s\n",Possible[i]);
            }
            break;}
            break;
        case 2:
                        srand(time(NULL));
            taille_un = saisie_taille();
            for (i = 0 ; i < taille_un; i++) {
                Lettres[i] = Cons_Voy(i);
            }
            printf("\n");
            for (i = 0; i < taille_un; i++) {
                Lettres[i] = toupper(Alea_caractere(Lettres[i]));
                printf("  ||  %c", Lettres[i]);
            }
            printf("\n");
            matrice(Mots);
            Mots_Possible(Mots,Lettres ,Possible,taille_un,&size);

      while ((attemp<=taille_un) && (!won) && seconds_total < taille_un*taille_un) {
        stop=0;
        fflush(stdin);
        start = clock();
        printf("\n %i-    ", attemp);
        gets(ch);
        end = clock();
        seconds = ((double) (end - start)) / CLOCKS_PER_SEC;
        seconds_total = seconds_total + seconds;
        for(i=0;i<strlen(ch);i++) {
            ch[i] =toupper(ch[i]);
        }
       for(i=0;i<j;i++){
        if(strcmp(Mots_Saisie[i],ch)==0)
                stop=1;
        }
        if(stop==1){
            printf("Le mot que vous avez saisi est correct mais vous l'avez deja tape!");
            attemp++;}
        else{
          if(taille_un >= seconds){
             test(&won, &attemp, ch, Possible, size, mot);
             if(!strcmp(mot,"")==0){
               strcpy(Mots_Saisie[j], mot);
               j++;
            }}
        else if(seconds_total<taille_un*taille_un && !(taille_un >= seconds)){
            printf("vous avez depasse le temps permis pour une tentative qui est %f s",seconds);
            attemp++;
            }
        else
            printf("vous avez depasser le temps totale permis qui est %i\n",taille_un*taille_un);
        }}
        printf("\n\n");
    for (i=0; i<j; i++) {
    printf("\n%s(%d)", Mots_Saisie[i], strlen(Mots_Saisie[i]));
}
    for (i=0; i<j; i++){
    if (strlen(Mots_Saisie[i])>max)
        max = strlen(Mots_Saisie[i]);
    }
       printf("\n\n------------------------------ Votre Score = %i ------------------------------\n\n",max);
    for (i = 0; i < taille_un; i++) {
                printf("  ||  %c", Lettres[i]);
            }
    max = 0;
    for (i=0; i<size; i++){
       if (strlen(Possible[i])>max)
           max = strlen(Possible[i]);
    }
    printf("\n\n1.Afficher le/les mot(s) le/les plus long(s)\n");
    printf("2.Afficher tous les mots possibles\n");
    do {
        fflush(stdin);
        printf("\n                Votre choix = ");
        gets(choix);
    } while (strlen(choix) != 1 || !(choix[0] == '1' || choix[0] == '2'));
    switch(atoi(choix)){
        case 1:
            for (i=0; i<size; i++){
                if (strlen(Possible[i]) == max){
                    printf("%s\n",Possible[i]);
                }
            }
            break;
        case 2:
            for (i=0; i<size; i++){
                printf("%s\n",Possible[i]);
            }
            break;}
        break;
        case 3:
         while(manche==0 || continuer()){
                size=0;
                won = 0;
                stop=0;
                j1=0;
                j2=0;
                max1=0;
                max2=0;
                manche++;
                attemp=1;
                srand(time(NULL));
                printf("\n\nMANCHE %i ------------------------------------------------------\n\n",manche);
                for(i=0;i<nbr_car;i++){
                    for(j=0;j<Max_Length;j++){
                       strcpy(J1[i],"");
                }}
                for(i=0;i<nbr_car;i++){
                    for(j=0;j<Max_Length;j++){
                       strcpy(J2[j],"");
                }}
                taille_deux = saisie_mult();
            for (i = 0 ; i < taille_deux; i++) {
                Lettres[i] = Cons_Voy(i);
            }
            printf("\n");
            for (i = 0; i < taille_deux; i++) {
                Lettres[i] = toupper(Alea_caractere(Lettres[i]));
                printf("  ||  %c", Lettres[i]);
            }
            printf("\n");
            matrice(Mots);
            Mots_Possible(Mots,Lettres,Possible,taille_deux,&size);

            while((attemp<=taille_deux) && (!won)) {
                    stop=0;
                if(manche%2 == 0){
                    if((attemp %2) != 0){
                        printf("\nJ1-     ");
                        gets(ch1);
                        Recherche(J1,J2,j1,j2, &stop,ch1);
                        if (stop==1){
                          printf("Le mot que vous avez saisi est correct mais vous l'avez deja tape!");
                          attemp++;
                        }
                        else if (stop==2){
                          printf("Le mot que vous avez saisi a deja tape par le joueur 2!");

                          attemp++;
                                 }
                        else{
                        test(&won, &attemp, ch1, Possible, size, mot);
                        if(!strcmp(mot,"")==0){
                        strcpy(J1[j1], mot);
                        j1++;}}
                    }
                     else{
                        printf("\nJ2-     ");
                        gets(ch2);
                        Recherche(J1,J2,j1,j2, &stop,ch2);
                        if (stop==1){
                          printf("Le mot que vous avez saisi a deja tape par le joueur 1!");
                          attemp++;
                        }
                        else if (stop==2){
                          printf("Le mot que vous avez saisi est correct mais vous l'avez deja tape!");
                          attemp++;
                                 }
                        else{
                        test(&won, &attemp, ch2, Possible, size, mot);
                        if(!strcmp(mot,"")==0){
                        strcpy(J2[j2], mot);
                        j2++;
                        }}
                    }}
                else{
                    if((attemp %2) != 0){
                        printf("\nJ1-     ");
                        gets(ch1);
                        Recherche(J1,J2,j1,j2, &stop,ch1);
                        if (stop==1){
                          printf("Le mot que vous avez saisi est correct mais vous l'avez deja tape!");
                          attemp++;
                        }
                        else if (stop==2){
                          printf("Le mot que vous avez saisi a deja tape par le joueur 2!");

                          attemp++;
                                 }
                        else{
                        test(&won, &attemp, ch1, Possible, size, mot);
                        if(!strcmp(mot,"")==0){
                        strcpy(J1[j1], mot);
                        j1++;}}
                    }
                    else{
                        printf("\nJ2-     ");
                        gets(ch2);
                        Recherche(J1,J2,j1,j2, &stop,ch2);
                        if (stop==1){
                          printf("Le mot que vous avez saisi a deja tape par le joueur 1!");
                          attemp++;
                        }
                        else if (stop==2){
                          printf("Le mot que vous avez saisi est correct mais vous l'avez deja tape!");
                          attemp++;
                                 }
                        else{
                        test(&won, &attemp, ch2, Possible, size, mot);
                        if(!strcmp(mot,"")==0){
                        strcpy(J2[j2], mot);
                        j2++;
                        }}
                    }
                }}
    printf("\n\n");
    for (i=0; i<j1; i++) {
        printf("\n%s(%d)", J1[i], strlen(J1[i]));
}
    for (i = 0; i < j1; i++) {
       if (strlen(J1[i]) > max1)
          max1 = strlen(J1[i]);
}
    printf("\n-----------J1 Score: %i -----------\n\n", max1);
    J1_score[s1]=max1;
    s1++;
    for (j=0; j<j2; j++) {
        printf("\n%s(%d)", J2[j], strlen(J2[j]));}
    for (j = 0; j < j2; j++) {
       if (strlen(J2[j]) > max2)
         max2 = strlen(J2[j]);
}
        printf("\n-----------J2 Score: %i -----------\n\n", max2);
   J2_score[s2]=max2;
   s2++;
   if (max1 > max2)
     printf("Joueur 1 gagne la manche %i\n\n", manche);
   else
     printf("Joueur 2 gagne la manche %i\n\n", manche);

    for (i = 0; i < taille_deux; i++) {
                printf("  ||  %c", Lettres[i]);
            }

     max = 0;
   for (i=0; i<size; i++){
       if (strlen(Possible[i])>max)
           max = strlen(Possible[i]);
    }
    printf("\n\n1.Afficher le/les mot(s) le/les plus long(s)\n");
    printf("2.Afficher tous les mots possibles\n");
    do {
        fflush(stdin);
        printf("\n                Votre choix = ");
        gets(choix);
    } while (strlen(choix) != 1 || !(choix[0] == '1' || choix[0] == '2'));
    switch(atoi(choix)){
        case 1:
            for (i=0; i<size; i++){
                if (strlen(Possible[i]) == max){
                    printf("%s\n",Possible[i]);
                }
            }
            break;
        case 2:
            for (i=0; i<size; i++){
                printf("%s\n",Possible[i]);
            }
            break;}

    }
        printf("\n                            J1     J2");
    for(k=0;k<s1;k++){
        printf("\n-------------------------------------------\n");
        printf("score manche %i               %i      %i\n",k+1,J1_score[k],J2_score[k]);}
    for(k=0;k<s1;k++){
        score_totale1=score_totale1+J1_score[k];
        score_totale2=score_totale2+J2_score[k];

    }
        printf("\n-------------------------------------------\n");
        printf("Score Total                  %i      %i\n",score_totale1,score_totale2);
        if(score_totale1>score_totale2)
            printf("\nJoueur 1  Gagne");
        else if(score_totale1<score_totale2)
            printf("\nJoueur 2  Gagne");
        else
            printf("\nEgalite");
            break;
        case 0:
            printf("Au Revoir!\n");
}
    return 0;
}
