#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

void InicioGraph(); /* Funcion para iniciar el modo grafico directamente */

int Recta(int x1,int y1,int x2,int y2,int x); /*Esta funcion es la ecuacion despejada de la recta, la cual se sabe que al tener dos puntos de una recta*/
											  /*Se puede obtener la ecuacion de la propia recta a traves del despeje, aqui directamente se despejo esta ecuacion*/
                                              /*Para que te retorne la posicion del punto en las coordenadas en Y*/
                                              /*Sus parametros son, el punto de inicio, el punto final (Estos dos se mantinen constantes), y la posicion en x, que va a ir variando*/
void main(void)
{
    int x,y,Salir=1,ox,oy,i;  /*X y Y van a ser las coordenadas de nuestro circulo, salir es para el bucle, y ox y oy, para ubicarse en el centro*/
    int rad =10;            /*Es el radio del circulo*/
    char mensaje[50];       /*Para guardar el mensaje a mostrar en pantalla del valor de Y posteriormente*/
    InicioGraph();           /*Iniciar modo grafico*/
    x=-320;                 /*Si el punto medio de la pantalla es el origen (es decir igual a 0) -320 seria el inicio de la pantalla*/
    y=Recta(10,10,0,0,x);  /*Y va a tener el valor de retorno de la funcion*/

            /*Si queres cambiar la trayectoria solo tenes que cambiar los puntos x1 y1, y x2,y2*/

    ox=getmaxx()/2;         /*Con esta ecuacion se obtiene el valor del origen en x y y*/
    oy=getmaxy()/2;
    setcolor(DARKGRAY);
    for(i=0;i<64;i++)
    {
        line((10*i)-1,0,(10*i)-1,480);
    }

    for(i=0;i<48;i++)
    {
        line(0,(10*i)-1,640,(10*i)-1);
    }

    setcolor(RED);
    line(ox,0,ox,480);
    line(0,oy,640,oy);
    setcolor(WHITE);
    circle(x+ox+(rad/2),y+oy+(rad/2),rad); /*Se dibuja el circulo, en la coordenada x, ya dado, mas el valor del origen, (EL cual estaria ubicado en el centro de la pantalla)
                            y en la coordenada y el obtuvimos a traves de la funcion de la recta, mas el origen, para que este en el centro de la pantalla, y el radio*/

    while(Salir)
    {
        setcolor(15);               /*Se manda a pintar en blanco*/
        circle(x+ox+(rad/2),y+oy+(rad/2),rad);      /*Se dibuja el circulo como anteriormente mencionamos*/
        sprintf(mensaje,"%d",y);    /*Se guarda el valor como caracter en la cadena mensaje*/
        outtextxy(10,10,mensaje);   /*Se imprime el mensaje*/
        delay(50);                 /*Se detiene por 100 milisegundos*/


        setcolor(0);                /*Se pinta en negro (color de fondo)*/
        circle(x+ox+(rad/2),y+oy+(rad/2),rad);      /*Se dibuja el circulo en negro para desaparecerlo*/
        outtextxy(10,10,mensaje);   /*Se pinta el mensaje en negro para desaparecer el mensaje anterior*/
       

        

        if(kbhit())                 /*Se preciona alguna tecla para salir del bucle*/
        Salir=0;

        x++;                        /*Se le suma 1 a las coordenada en x*/
        y=Recta(10,10,0,0,x);   /*Se obtiene el valor de y por medio de la funcion recta*/
    }

   
}

/*Iniciar modo grafico*/

void InicioGraph()
{
    int gd = 0, gm = 0;
    initgraph(&gd, &gm, "");
}

/* Codigo de la recta*/

int Recta(int x1,int y1,int x2,int y2,int x)
{
    /*x1 y y1 son los valores de la ubicacion del primer punto, x2 y y2 son los valores de la ubicacion del segundo puntos, y x es la variable que varia alrededor de la ejecucion*/

    int y;
    y= ((x*(y2-y1))-(x2*(y2+y1))+(x1*y1))/(x2-x1);  /*La ecuacion que se resuelve*/
    return y;                                       /*Si x vale un numero (variable independiente), se retorna el valor de y, (variable dependiente)*/


}
