#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <16image.h>
#include <mouse.h>
#include <time.h>
#include <string.h>

void InicioGraph(); /* Funcion para iniciar el modo grafico directamente */

int ClickEnCirculo(int x, int y, int rad); /* Funcion para dar click en un avion (En un circulo dado) en corresponcencia a los colores*/
                                           /* Se pasan los mismos parametros del circulo en X y Y junto con el radio, los mismos que representa el avion*/

void CoCirculo(int x, int y, int rad); /* Funcion solamente para ejecutar codigo que se reutilizara una y otra vez*/

void main(void)
{
    int SalBucle = 1;
    srand(time(NULL));
    InicioGraph(); /*Iniciar modo grafico*/

    /*Se dibuja un circulo para simular que es el avion en el radar*/

    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    circle(100, 100, 10); /*Avion 1*/
    floodfill(100, 100, YELLOW);
    circle(200, 200, 10); /*Avion 2*/
    floodfill(200, 200, YELLOW);

    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    circle(300, 300, 10); /*Avion 3*/
    floodfill(300, 300, RED);

    mver(); /*Mostrar mouse en pantalla*/

    /* Se inicia el bucle para encadenar los eventos a traves de dar click */

    while (SalBucle)
    {
        CoCirculo(100, 100, 10); /*Se le pasa los parametros de los circulos preestablecidos (Aviones)*/
        CoCirculo(200, 200, 10); /*Como se crearon 3 aviones se usa esta funcion 3 veces*/
        CoCirculo(300, 300, 10);

        /*Si se preciona alguna tecla se sale del bucle*/
        while (kbhit())
        {
            if (getch())
                SalBucle = 0;
        }
    }

    getch();
}

/*Iniciar modo grafico*/

void InicioGraph()
{
    int gd = 0, gm = 0;
    initgraph(&gd, &gm, "");
}

/* Codigo del funcionamiento de los protocolos (lo que sucede cuando le vas a dar click pues)*/

int ClickEnCirculo(int x, int y, int rad)
{
    /* Sucede lo siguinte: */

    /* Aclaraciones: se sabe que al usar minlimit se crea un cuadro imaginario en el que retorna 1 si el mouse se ubica ahi*/
    /* y se usa getpixel para obtener cierto color,*/
    /* En este caso si esta en el recuadro y se obtiene el color del circulo a la vez que se le da click retornara el valor indicado*/

    /*Si se le da click al circulo que este en amarillo */

    if (minlimit(1, x - rad, y - rad, x + rad, y + rad) && mclick())
    {
        mocultar();
        if ((getpixel(mxpos(1), mypos(1)) == YELLOW))
        {
            mver();
            return 1;
        }

        mver();
    }

    /*Si se le da click al circulo que este en rojo */
    if (minlimit(1, x - rad, y - rad, x + rad, y + rad) && mclick())
    {
        mocultar();
        if ((getpixel(mxpos(1), mypos(1)) == RED))
        {
            mver();
            return 2;
        }

        mver();
    }
    /*Si no sucede nada pues se retorna eso*/

    return 0;
}

void CoCirculo(int x, int y, int rad)
{
    /*En esta funcion solamente es ejecucion de codigo*/
    int Event;
    char Emergencia[50];
    int Advertencia[]={410 , 390 , 550 , 390, 480 ,330};


    srand(time(NULL));  /*Para el uso de del random posteriormente*/
    Event = rand() % 3; /*Esta variable es unicamente para mostrar la emergencia que occurrio en pantalla y la que se mostrara*/

    if (Event == 0)
        strcpy(Emergencia, "Se detecto una tormenta electrica.");
    else if (Event == 1)
        strcpy(Emergencia, "Se encontraron fallas mecanicas.");
    else if (Event == 2)
        strcpy(Emergencia, "Se detecto altas turbulencias.");

    if (ClickEnCirculo(x, y, rad) == 1) /*Se usa esta funcion para verificar si se dio click en el momento correcto*/
    {
        /*Si es asi*/

        /*Se muestra un recuadro para, en este caso, aterrizar*/
        /*Este es en el caso en que solamente se activa el protocolo de aterrizaje*/

        setfillstyle(SOLID_FILL, GREEN);
        setcolor(GREEN);
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        settextstyle(0, 0, 1);
        mocultar();
        bar(getmaxx() / 2, getmaxy() / 2, getmaxx(), getmaxy());
        setfillstyle(SOLID_FILL, BLACK);
        bar((getmaxx() / 2) + 10, (getmaxy() / 2) + 10, getmaxx() - 10, getmaxy() - 10);

        setcolor(WHITE);
        outtextxy(((getmaxx() / 2) + 10 + getmaxx() - 10) / 2, (getmaxy() / 2) + 30, "Protocolo de Aterrizaje.");
        outtextxy(((getmaxx() / 2) + 10 + getmaxx() - 10) / 2, (getmaxy() / 2) + 45, "Pulse el boton para aterrizar.");
        mver();

        /*Se dibuja el boton para activar el protocolo de aterrizaje*/
        setfillstyle(SOLID_FILL, GREEN);
        setcolor(GREEN);

        bar((getmaxx() / 2) + 25, getmaxy() - 70, getmaxx() - 25, getmaxy() - 40);

        setfillstyle(SOLID_FILL, BLACK);

        bar((getmaxx() / 2) + 30, getmaxy() - 65, getmaxx() - 30, getmaxy() - 45);
        setcolor(WHITE);
        outtextxy(((getmaxx() / 2) + 30 + getmaxx() - 30) / 2, getmaxy() - 55, "Activar protocolo de aterrizaje");


	    setfillstyle(SOLID_FILL, YELLOW);
        fillpoly(3,Advertencia);
        settextstyle(0, 0, 5);
        setcolor(BLACK);
        outtextxy(485,370,"!");
        settextstyle(0, 0, 1);


        /*Y se detiene el programa hasta que se le de click al boton*/
        while ((!minlimit(1, (getmaxx() / 2) + 35, getmaxy() - 65, getmaxx() - 35, getmaxy() - 45)) || !mclick())
            if (kbhit())
                getch();

        /*Se hace el efecto de que se preeciono el boton*/

        mocultar();
        setcolor(DARKGRAY);
        setfillstyle(SOLID_FILL, DARKGRAY);
        bar((getmaxx() / 2) + 25, getmaxy() - 70, getmaxx() - 25, getmaxy() - 40);
        setfillstyle(SOLID_FILL, BLACK);
        bar((getmaxx() / 2) + 30, getmaxy() - 65, getmaxx() - 30, getmaxy() - 45);
        outtextxy(((getmaxx() / 2) + 30 + getmaxx() - 30) / 2, getmaxy() - 55, "Activar protocolo de aterrizaje");
        mver();
        delay(250);

        mocultar();
        setcolor(GREEN);
        setfillstyle(SOLID_FILL, GREEN);
        bar((getmaxx() / 2) + 25, getmaxy() - 70, getmaxx() - 25, getmaxy() - 40);
        setfillstyle(SOLID_FILL, BLACK);
        bar((getmaxx() / 2) + 30, getmaxy() - 65, getmaxx() - 30, getmaxy() - 45);
        setcolor(WHITE);
        outtextxy(((getmaxx() / 2) + 30 + getmaxx() - 30) / 2, getmaxy() - 55, "Activar protocolo de aterrizaje");
        mver();

        delay(50);
        
        mocultar();
        setfillstyle(SOLID_FILL, BLACK);
        bar(getmaxx() / 2, getmaxy() / 2, getmaxx(), getmaxy());
        mver();

        /*Y se termina de ejecutar este codigo*/
    }
    else if (ClickEnCirculo(x, y, rad) == 2)
    {
        /*Este es en el caso que ocurra una emergencia y tenga que cambiar de direccion a una ruta cercana*/

        setfillstyle(SOLID_FILL, GREEN);
        setcolor(GREEN);
        settextstyle(0, 0, 1);
        mocultar();
        bar(getmaxx() / 2, getmaxy() / 2, getmaxx(), getmaxy());
        setfillstyle(SOLID_FILL, BLACK);
        bar((getmaxx() / 2) + 10, (getmaxy() / 2) + 10, getmaxx() - 10, getmaxy() - 10);
        setcolor(WHITE);
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        outtextxy(((getmaxx() / 2) + 10 + getmaxx() - 10) / 2, (getmaxy() / 2) + 30, Emergencia); /*El mensaje de emergencia se determino dese antes*/
        outtextxy(((getmaxx() / 2) + 10 + getmaxx() - 10) / 2, (getmaxy() / 2) + 45, "Pulse el boton para cambiar la");
        outtextxy(((getmaxx() / 2) + 10 + getmaxx() - 10) / 2, (getmaxy() / 2) + 60, "trayecctoria a una zona cercana.");

        mver();

        /*Se dibuja el boton para activar el protocolo de aterrizaje*/
        setfillstyle(SOLID_FILL, GREEN);
        setcolor(GREEN);

        bar((getmaxx() / 2) + 30, getmaxy() - 70, getmaxx() - 30, getmaxy() - 40);

        setfillstyle(SOLID_FILL, BLACK);

        bar((getmaxx() / 2) + 35, getmaxy() - 65, getmaxx() - 35, getmaxy() - 45);
        setcolor(WHITE);
        outtextxy(((getmaxx() / 2) + 35 + getmaxx() - 35) / 2, getmaxy() - 55, "Cambiar ruta de aterrizaje");

        setfillstyle(SOLID_FILL, RED);
        fillpoly(3,Advertencia);
        settextstyle(0, 0, 5);
        setcolor(BLACK);
        outtextxy(485,370,"!");
        settextstyle(0, 0, 1);
        
        /*Y se detiene el programa hasta que se le de click al boton*/
        while ((!minlimit(1, (getmaxx() / 2) + 35, getmaxy() - 65, getmaxx() - 35, getmaxy() - 45)) || !mclick())
            if (kbhit())
                getch();

        /*Se hace el efecto de que se preeciono el boton*/
        mocultar();
        setcolor(DARKGRAY);
        setfillstyle(SOLID_FILL, DARKGRAY);
        bar((getmaxx() / 2) + 30, getmaxy() - 70, getmaxx() - 30, getmaxy() - 40);
        setfillstyle(SOLID_FILL, BLACK);
        bar((getmaxx() / 2) + 35, getmaxy() - 65, getmaxx() - 35, getmaxy() - 45);
        outtextxy(((getmaxx() / 2) + 35 + getmaxx() - 35) / 2, getmaxy() - 55, "Cambiar ruta de aterrizaje");
        mver();
        delay(250);

        mocultar();
        setcolor(GREEN);
        setfillstyle(SOLID_FILL, GREEN);
        bar((getmaxx() / 2) + 30, getmaxy() - 70, getmaxx() - 30, getmaxy() - 40);
        setfillstyle(SOLID_FILL, BLACK);
        bar((getmaxx() / 2) + 35, getmaxy() - 65, getmaxx() - 35, getmaxy() - 45);
        setcolor(WHITE);
        outtextxy(((getmaxx() / 2) + 35 + getmaxx() - 35) / 2, getmaxy() - 55, "Cambiar ruta de aterrizaje");
        mver();

        delay(50);

        mocultar();
        setfillstyle(SOLID_FILL, BLACK);
        bar(getmaxx() / 2, getmaxy() / 2, getmaxx(), getmaxy());
        mver();
    }
}