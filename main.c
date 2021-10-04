#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXCHAR 1024

int main(int argc, char **argv){

    // char ip[15];
    int ip_csv[4] = {0};
    int ip_csv_compatible = 0;

    sscanf(argv[1], "%d.%d.%d.%d", &ip_csv[0], &ip_csv[1], &ip_csv[2], &ip_csv[3]);

    ip_csv_compatible = ip_csv[0] * 256 * 256 * 256 + ip_csv[1] * 256 * 256 + ip_csv[2] * 256 + ip_csv[3];

    printf("%ld", ip_csv_compatible);

    FILE *fp;
    char Ligne[MAXCHAR];
    char *Sortie;

    fp = fopen("geoip.csv/data","r");

    int ip_from_int = 0, ip_to_int = 0;
    char *ip_from, *ip_to;
    int exit_compteur = 1;


    while ( !feof(fp) )
    {
        fgets(Ligne, MAXCHAR, fp);
        printf("Ligne: %s\n", Ligne);

        Sortie = strtok(Ligne, ",");

        exit_compteur = 1;

        while(Sortie != NULL)
        {
            for(int i = 1; i < strlen(Sortie); i++){
                if(Sortie[i] == '"'){
                    Sortie[i] = Sortie[i+1];
                }
                Sortie[i-1] = Sortie[i];
            }
            printf("Compteur : %d ", exit_compteur);
            printf(" Sortie: %s\n", Sortie);
            Sortie = strtok(NULL, ",");

            if(ip_from_int == 0){
                printf("Sortie : %s \n", Sortie);
                ip_from = Sortie;
                ip_from_int++;
            }

            if(ip_to_int == 1){
                printf("Sortie : %s \n", Sortie);
                ip_to = Sortie;
                ip_to_int++;
            }

            if(exit_compteur == 2){
                printf("Compteur numéro 3");
                if(ip_csv_compatible >= ip_from && ip_csv_compatible <= ip_to){
                    printf("L'IP vient de : %s", Sortie);
                    exit(0);
                }
            } 
            
            exit_compteur++;
            ip_to_int++;

        }

    }

    printf("\n");

    return 0;

}