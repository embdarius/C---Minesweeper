#include <stdio.h>
#include <stdlib.h>
#include "minesweeper.h"
#include <string.h>

typedef struct
{
    char tip;
    char coloana;
    int rand;

} comanda;

int main()
{
    int h,w,nr_bombs;
    printf("Height/Width: ");
    scanf("%d %d", &h, &w);


    fflush(stdin);




    char t[h][w];
    nr_bombs = 14;
    char cols[] = {'B','D','F','Z','G','H','L','a','g','z','f','h','w','x'};
    int rows[] = {1,3,5,7,9,2,14,15,20,10,6,13,25,11};

    create(nr_bombs, cols, rows, h, w, t);
    printf("\n");
    print(h,w,t);
    printf("\n");
    char** s = init_state(h,w);
    discover(1,5,h,w,t,s);
    printf("\n");
    char legendaColoane[1000];
    char legendaTip[1000];
    int legendaRand[1000];
    int l = 0;
    player_view(h,w,t,s);

    int celule = 0,celuleJucator = 0;
    for(int i = 0; i<h; i++)
    {
        for(int j = 0; j<w; j++)
            if(s[i][j] != 'X')
                celule++;
    }

    comanda structuri[100];
    printf("\n");
    printf("\n");
    printf("\n");
    char str[100];
    char tip, coloana;
    int rand;
    int nr = 0;
    int gameOver = 0;
    while(gameOver != 1)
    {
        nr = 0;
        int k = 0;
        scanf("%s", str);
        int n = strlen(str)-1;
        while(k <= n)
        {
            int r = sscanf(str, "%c%c%i\n", &tip, &coloana, &rand);
            if(r == 3 && (tip == '!' || tip == '.'))
            {
                printf("%c %c %i\n", tip, coloana, rand);
                k++;
                structuri[nr].rand = rand;
                structuri[nr].tip = tip;
                structuri[nr].coloana = coloana;
                legendaColoane[l] = coloana;
                legendaTip[l] = tip;
                legendaRand[l] = rand;
                l++;
                nr++;
            }
            else k++;
            strcpy(str, str+k);
        }
        for(int i = 0; i<nr; i++)
        {
            if(structuri[i].tip == '.')
            {
                int col;
                int temp = (int)(structuri[i].coloana);
                if(temp >= 65 && temp<=90)
                    col = temp-65;
                else if(temp >= 97 && temp <= 122)
                    col = temp - 71;
                int rand = structuri[i].rand - 1;
                if(t[rand][col] == 'X')
                {
                    s[rand][col] = t[rand][col];
                    player_view(h,w,t,s);
                    printf("AI PIERDUT");
                    gameOver = 1;
                    break;
                }
                else if(t[rand][col] != 'X' && s[rand][col] != '.')
                {
                    s[rand][col] = '.';
                    player_view(h,w,t,s);
                    celuleJucator++;
                    printf("\n");
                    printf("Celule gasite: %d/%d\n", celuleJucator, celule);
                    printf("LEGENDA: ");
                    for(int d=0;d<l;d++)
                    printf("%c%c%d  ", legendaTip[d], legendaColoane[d], legendaRand[d]);
                    printf("\n");
                }
            }
            else if(structuri[i].tip=='!')
            {
                int col;
                int temp = (int)(structuri[i].coloana);
                if(temp >= 65 && temp<=90)
                    col = temp-65;
                else if(temp >= 97 && temp <= 122)
                    col = temp - 71;
                int rand = structuri[i].rand - 1;
                mark(rand,col,h,w,s);
                player_view(h,w,t,s);
                printf("\n");
                printf("Celule gasite: %d/%d\n", celuleJucator, celule);
                printf("LEGENDA: ");
                for(int d=0;d<l;d++)
                    printf("%c%c%d  ", legendaTip[d], legendaColoane[d], legendaRand[d]);
                printf("\n");
            }
        }

    }



    free(s);


    return 0;
}
