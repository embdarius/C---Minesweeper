#ifndef MINESWEEPER_H_INCLUDED
#define MINESWEEPER_H_INCLUDED

void mark(int i, int j,int h, int w, char** s)
{
    if(s[i][j] == '?')
        s[i][j] = '!';
    else if(s[i][j] == '!')
        s[i][j] = '?';
    return;
}

void player_view(int h, int w, char t[h][w], char** s)
{
    int w1 = w + 64;
    printf("    ");
    for(int i = 65; i<=w1; i++)     //afisare coloanele de sus
    {
        if(i == 91) break;
        printf("%c", i);
    }
    w1 = w1+6;
    for(int i = 97; i<=w1; i++)      //afisare coloanele de sus(litere mici)
        printf("%c", i);
    printf("\n");




    for(int i = 0;i<h;i++)
    {
        if(i+1 >= 1 && i+1<= 9)
        {
            printf("  ");
            printf("%d",i+1);
        }
        else if(i+1 >=10 && i+1 < 100)
            printf(" %d", i+1);
        else if(i+1 == 100)
            printf("%d", i+1);
        printf(" ");
        for(int j = 0;j<w;j++)
        {
            if(s[i][j] == '.')
                printf("%c", t[i][j]);
            if(s[i][j] == '!')
                printf("!");
            if(s[i][j] == '?')
                printf("?");
            if(s[i][j] == 'X')
                printf("X");
        }
        printf(" %d", i+1);
        printf("\n");
    }
    printf("    ");
    w1 = w  + 64;
    for(int i = 65; i<=w1; i++)     //afisare coloanele de jos
    {
        if(i == 91) break;
        printf("%c", i);
    }
    w1 = w1+6;
    for(int i = 97; i<=w1; i++)     //afisare coloane de jos(Litere mici)
        printf("%c", i);
    printf("\n");

    return;
}



char** init_state(int h, int w)
{
    char** s = (char**)malloc(h*sizeof(char*));
    for(int i = 0; i<h; i++)
    {
        s[i] = (char*)calloc(w, sizeof(char));
        for(int j = 0;j<w;j++)
            s[i][j] = '?';
    }
    return s;
}

int discover(int i, int j, int h, int w, char t[h][w], char** s)
{
    int lin[] = {-1,-1,-1,0,0,1,1,1};
    int col[] = {-1,0,1,-1,1,-1,0,1};
    int sizel = sizeof(lin)/sizeof(lin[0]);
    if(i > h || i<0 || j>w || j<0)
    {
        return -2;
    }
    if(t[i][j] == 'X')
    {
        return -1;
    }
    if(s[i][j] == '.')
    {
        return 0;
    }

    if(t[i][j] != '.' && t[i][j] != 'X')
    {

        s[i][j] = '.';
        return 1;
    }
    int k = 0;
    if(t[i][j] == '.')
    {
        s[i][j] = '.';
        while(k<=sizel)
        {
            if(i+lin[k] >= 0 && i +lin[k] < h && j+col[k] >= 0 && j+col[k] < w)
                discover(i+lin[k],j+col[k],h,w,t,s);
            k++;
        }
    }
    return 2;
}



void print(int h, int w, char t[h][w])
{
    int w1 = w + 64;
    printf("   ");
    for(int i = 65; i<=w1; i++)     //afisare coloanele de sus
    {
        if(i == 91) break;
        printf("%c", i);
    }
    w1 = w1+6;
    for(int i = 97; i<=w1; i++)      //afisare coloanele de sus(litere mici)
        printf("%c", i);
    printf("\n");
    for(int i = 0; i < h; i++)
    {
        if(i+1 <= 9)                    //afisare randuri stanga <=9
        {
            printf(" ");
            printf("%d", i+1);
            printf(" ");
        }
        else if(i+1 >= 10)              //afisare randuri stanga >= 10
        {
            printf("%d", i+1);
            printf(" ");
        }
        for(int j = 0; j<w; j++)
            printf("%c", t[i][j]);
        printf(" %d", i+1);         //afisare randuri dreapta
        printf("\n");
    }
    printf("   ");
    w1 = w  + 64;
    for(int i = 65; i<=w1; i++)     //afisare coloanele de jos
    {
        if(i == 91) break;
        printf("%c", i);
    }
    w1 = w1+6;
    for(int i = 97; i<=w1; i++)     //afisare coloane de jos(Litere mici)
        printf("%c", i);

}


void create(int nr_bombs, char cols[], int rows[], int h, int w, char t[h][w])
{
    for(int i = 0; i<h; i++)
        for(int j = 0; j<w; j++)
            t[i][j] = '*';
    int linie, coloana;
    for(int i = 0; i<nr_bombs; i++)
    {
        linie = rows[i] - 1;
        if((int)(cols[i])<=90)
            coloana = (int)(cols[i]) - 65;
        else if((int)(cols[i]>90))
            coloana = (int)(cols[i]-71);

        printf("%d %c\n", linie+1, cols[i]);      //debug (arata pe ce pozitie se plaseaza o bomba)
        t[linie][coloana] = 'X';
    }
    for(int i = 0; i<h; i++)
    {
        for(int j = 0; j<w; j++)
            if(t[i][j] != 'X')
                t[i][j] = '.';
    }

    char nr = 0;
    for(int i = 0 ; i<h; i++)               //VERIFICA CATE BOMBE VECINE EXISTA PENTRU FIECARE t[i][j]
        for(int j = 0; j<w; j++)
            if(t[i][j] == '.')
            {
                nr = 0;
                if(i+1 <h && t[i+1][j] == 'X')
                    nr++;
                if(i-1 >= 0 && t[i-1][j] == 'X')
                    nr++;
                if(j + 1 < w && t[i][j+1] == 'X')
                    nr++;
                if(j - 1 >= 0 && t[i][j-1] == 'X')
                    nr++;
                if(i+1 < h && j - 1 >= 0 && t[i+1][j-1] == 'X')
                    nr++;
                if(i + 1 < h && j+1 <w && t[i+1][j+1] == 'X')
                    nr++;
                if(i - 1 >= 0 && j - 1 >= 0 && t[i-1][j-1] == 'X')
                    nr++;
                if(i - 1 >= 0 && j+1 < w && t[i-1][j+1] == 'X')
                    nr++;
                char rez = nr + '0';
                if(nr == 0)
                    t[i][j] == '.';
                else
                    t[i][j] = rez;
            }

}




#endif // MINESWEEPER_H_INCLUDED
