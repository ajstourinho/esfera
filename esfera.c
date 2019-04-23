#include <stdio.h>
#include <math.h>

int main()
{
    int linhas=50, colunas=50, i, j;

    const float pi=3.1415, teta_esp=0.02, fi_esp=0.02;

    float raio=8, d_esf=12, d_tela=5;

    float teta, fi;

    float sin_teta, cos_teta, sin_fi, cos_fi;

    float x, y, z;

    int xp, yp;

    float luz_x=0, luz_y=1, luz_z=-1, modluz;

    float N_x, N_y, N_z;

    float L;
    int L_index;

    float ooz;

    char output[linhas][colunas];
    float zbuffer[linhas][colunas];

    char move;

    // inicializando output e zbuffer
    LOOP: for (i=0; i<linhas; i++)
    {
        for (j=0; j<colunas; j++)
        {
            output[i][j] = ' ';
            zbuffer[i][j] = 0;
        }
    }


    // construindo esfera e definindo output
    for (teta=0; teta<2*pi; teta=teta+teta_esp)
    {
        sin_teta = sin(teta);
        cos_teta = cos(teta);

        for (fi=0; fi<2*pi; fi=fi+fi_esp)
        {

            sin_fi = sin(fi);
            cos_fi = cos(fi);

            x = raio*cos_teta*cos_fi;
            y = raio*sin_teta;
            z = d_esf - raio*cos_teta*sin_fi;

            ooz = 1/z;

            xp = (int)(colunas/2 + d_tela*x/z);
            yp = (int)(linhas/2 - d_tela*y/z);

            N_x = cos_teta*cos_fi;
            N_y = sin_teta;
            N_z = -cos_teta*sin_fi;

            modluz = sqrt(luz_x*luz_x + luz_y*luz_y + luz_z*luz_z);

            L = N_x*luz_x/modluz + N_y*luz_y/modluz + N_z*luz_z/modluz;

            if (L > 0)
            {
                if (ooz > zbuffer[xp][yp])
                {
                    zbuffer[xp][yp] = ooz;

                    L_index = L*11;

                    output[xp][yp] = ".,-~:;=!*#$@"[L_index];
                }
            }

        }
    }

    //imprimindo
    for (i=0; i<linhas; i++)
    {
        for (j=0; j<colunas; j++)
        {
            printf("%c", output[i][j]);
        }

        printf("\n");
    }
    printf("luz (%f, %f, %f)", luz_x, luz_y, luz_z);


    while ((move = getch()) != 'q')
    {
        if (move == 'w')
        {
            if (raio != d_esf-1)
            {
                raio = raio + 1;
                system("cls");
                goto LOOP;
            }
        }
        else if (move == 's')
        {
            if (raio != 0)
            {
                raio = raio - 1;
                system("cls");
                goto LOOP;
            }
        }
        else if (move == 'i')
        {
            luz_z = luz_z + 1;
            system("cls");
            goto LOOP;
        }
        else if (move == 'k')
        {
            luz_z = luz_z - 1;
            system("cls");
            goto LOOP;
        }
        else if (move == 'j')
        {
            luz_x = luz_x - 1;
            system("cls");
            goto LOOP;
        }
        else if (move == 'l')
        {
            luz_x = luz_x + 1;
            system("cls");
            goto LOOP;
        }
    }
    return 0;
}
