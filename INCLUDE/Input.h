#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <GRAPHICS.H>
/*#include <mouse.h>*/

#define TAMNOMBRES 18         /* Tamano max de nombres */
#define TAMHORA 7           /* Tamano max de la hora */
#define NUMVUELO 8          /* Tamano max de numero de vuelo */

/*#define SIZEAIRPORT 30*/       /* Tamano max de nombre aereopuerto */

char aereolinea1 [] = "AVIANCA";
char aereolinea2 [] = "AEREOPOSTAL";

void obtenerNombre(char tempNombre [], int x, int y)
{
    char tecla;
    int contador_caracter = 0;

    /* A la posicion 1 del arreglo temporal donde se almacenara la cadena le asignamos fin de cadena ya que esta ira cambiando luego */
    tempNombre[0] = '\0';
    
    /* Mientras se capture una tecla */
    while (1)
    {
        tecla = getch();

        /* Si se presiono enter */
        if(tecla == 13)
        {
            /* Indicar fin de cadena en la posicion que se encuentre*/
            tempNombre[contador_caracter] = '\0';
            break;
        }
        else if(tecla == 8)
        {
            /* Si presiono backspace y si el tamano de la cadena es mayor que 0*/
            if(contador_caracter > 0)
            {
                mocultar();

                settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                setcolor(15);

                /*moveto(x, y);
                outtext(tempString);*/
                /*tempString[count_char] = '\0';*/
                outtextxy(x, y, tempNombre);

                /* Se resta 1 del tamano de la cadena y se le indica fin de cadena*/
                tempNombre[contador_caracter - 1] = '\0';

                /*settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);*/
                setcolor(8);
                /*moveto(x, y);
                outtext(tempString);*/
                outtextxy(x, y, tempNombre);

                mver();

                /* Disminuye el contador de caracteres */
                contador_caracter--;   
            }
        }
        else if((tecla >= 65 && tecla <= 90) || (tecla >= 97 && tecla <= 122) && contador_caracter < TAMNOMBRES)
        {
            /* Si se presiono una letra mayus o minus, y si el contador de caracteres es menor que el tamano maximo de caracteres*/
            
            mocultar();

            settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
            setcolor(15);
            outtextxy(x, y, tempNombre);
            /*moveto(x, y);
            outtext("_");*/
            /*outtextxy(x, y, tempString);*/

            /* Se guarda el caracter que capturo key en el arreglo temporal */
            tempNombre[contador_caracter] = toupper(tecla);

            /* Se indica fin de cadena al nuevo tamano de la cadena + 1*/
            tempNombre[contador_caracter + 1] = '\0';

            /* Aqui se ira imprimiendo en pantalla lo que se vaya escribiendo */
            setcolor(8);
            outtextxy(x, y, tempNombre);
            /*moveto(x, y);
            outtext("_");*/
            /*printf("%c", tempString[count_char]);*/

            mver();

            /* Aumenta el contador de caracteres para la siguiente posicion */
            contador_caracter++;
        }
    }
}

void obtenerNumVuelo(char tempNumVuelo [], char tempNombre [], int x, int y)
{ 
    char tecla;
    int contador_caracter = 2;

    tempNumVuelo[2] = '\0';

    /* Si la aereolinea ingresada es igual a la aereolinea1 (AVIANCA) */
    if (strcmp(tempNombre, aereolinea1) == 0)
    {
        mocultar();

        /* Se indica a las dos primeras posiciones del arreglo (tempNumFlight) 'AV' correspondiente al codigo IATA */
        tempNumVuelo[0] = 'A';
        tempNumVuelo[1] = 'V';

        /* Se imprime */
        setcolor(8);
        outtextxy(x,y, tempNumVuelo);

        mver();
    }

    /* Si la aereolinea ingresada es igual a la aereolinea2 (AEREOPOSTAL) */
    else if (strcmp(tempNombre, aereolinea2) == 0)
    {
        mocultar();

        /* Se indica a las dos primeras posiciones del arreglo (tempNumFlight) 'VH' correspondiente al codigo IATA */
        tempNumVuelo[0] = 'V';
        tempNumVuelo[1] = 'H';

        setcolor(8);
        outtextxy(x,y, tempNumVuelo);

        mver();
    }
    
    while (1)
    {
        tecla = getch();

        if(tecla == 13 && contador_caracter == NUMVUELO- 2)
        {
            /* Indica fin de cadena al llegar al tamano max y si se presiona enter*/
            tempNumVuelo[contador_caracter] = '\0';
            break;
        }
        else if(tecla == 8)
        {
            /* Si presiono backspace y si el tamano de la cadena es mayor que 2*/
            if(contador_caracter > 2)
            {
                mocultar();

                settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                setcolor(15);
                outtextxy(x, y, tempNumVuelo);

                /* Se resta 1 del tamano de la cadena y se le indica fin de cadena*/
                tempNumVuelo[contador_caracter - 1] = '\0';

                setcolor(8);
                outtextxy(x, y, tempNumVuelo);

                mver();

                /* Disminuye el contador de caracteres */
                contador_caracter--;   
            }
        }
        /* Si se presiona un numero, y si el contador de caracteres es menor que el tamano maximo de caracteres*/
        else if((tecla >= 48 && tecla <= 57) && (contador_caracter < NUMVUELO- 2))
        {
            mocultar();

            settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
            setcolor(15);
            outtextxy(x, y, tempNumVuelo);

            /* Se guarda el caracter que capturo key en el arreglo temporal */
            tempNumVuelo[contador_caracter] = tecla;

            /* Se indica fin de cadena al nuevo tamano de la cadena + 1*/
            tempNumVuelo[contador_caracter + 1] = '\0';

            /* Aqui se ira imprimiendo en pantalla lo que se vaya escribiendo */
            setcolor(8);
            outtextxy(x, y, tempNumVuelo);
            /*printf("%c", tempNumFlight[count_char]);*/

            mver();

            /* Aumenta el contador de caracteres para la siguiente posicion */
            contador_caracter++;
        }
    }
}

/******************************************************************
/* La funcion getHour esta validada segun el formato de 24 horas 
******************************************************************/

void obtenerHora(char tempHora [], int x, int y)
{
   char tecla;
   int contador_caracter = 0;

   tempHora[0] = '\0';

    while (1)
    {
        tecla = getch();
        
        /* Si se presiona enter y el tamano es el correspondiente se indica fin de cadena y termina el bucle */
        if((tecla == 13) && (contador_caracter == TAMHORA- 2))
        {                                              
           /*tempHour[count_char] = '\0';*/
           break;
        }

        /* Si se presiona backspace */
        else if (tecla == 8)
        {
            if(contador_caracter > 0)
            {
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                
                /* Se imprime */ 
                setcolor(15);
                outtextxy(x, y, tempHora);

                /* Se resta 1 del tamano de la cadena y se le indica fin de cadena*/
                tempHora[contador_caracter - 1] = '\0';

                setcolor(8);
                outtextxy(x, y, tempHora);

                /* Disminuye el contador de caracteres */
                contador_caracter--;   
            }
        }
        
        /* Si presiona un numero y si el contador de caracteres (del arreglo) es menor que 5 */
        else if ((tecla >= 48 && tecla <= 57) && (contador_caracter < 5))
        {
            /* Se guarda el caracter presionado en el arreglo temporal */
            tempHora[contador_caracter] = tecla;

            /* Si el contador es 0 (es decir la posicion 1 del arreglo) */
            if (contador_caracter == 0)
            {
                /* Si lo digitado es un numero del 0 - 2*/
                if (tempHora[contador_caracter] >= '0' && tempHora[contador_caracter] <= '2')
                {
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

                    /* Se imprime */    
                    setcolor(15);
                    outtextxy(x, y, tempHora);

                    /* Se indica fin de cadena al nuevo tamano de la cadena + 1*/
                    tempHora[contador_caracter + 1] = '\0';

                    /* Aqui se ira imprimiendo en pantalla lo que se vaya escribiendo */
                    setcolor(8);
                    outtextxy(x, y, tempHora);

                    /* Aumenta el contador de caracteres para la siguiente posicion */
                    contador_caracter++;  /* Contador = 1 */
                }
            }

            /* Si el contador es 1 (es decir la posicion 2 del arreglo) */
            if (contador_caracter == 1)
            {
                /* Si el primero numero digitado (posicion 1 del arreglo) es 2 */
                if (tempHora[0] == '2')
                {
                    /* Si digita un numero en el rango de 20 - 23 */
                    if (tempHora[contador_caracter] >= '0' && tempHora[contador_caracter] <= '3')
                    {
                        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

                        /* Se imprime */    
                        setcolor(15);
                        outtextxy(x, y, tempHora);

                        tempHora[contador_caracter + 1] = '\0';

                        setcolor(8);
                        outtextxy(x, y, tempHora);

                        contador_caracter++; /* Contador = 2 */
                    }
                }

                /* Sino (si digito 0 o 1 en la primera posicion del arreglo),
                *  si digita un numero en el rango de 00 al 19 en la posicion actual (pos 2) */
                else if (tempHora[contador_caracter] >= '0' && tempHora[contador_caracter] <= '9')
                {
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                    
                    /* Se imprime */
                    setcolor(15);
                    outtextxy(x, y, tempHora);

                    tempHora[contador_caracter + 1] = '\0';

                    setcolor(8);
                    outtextxy(x, y, tempHora);

                    contador_caracter++;   /* Contador = 2 */
                }
            }

            /* Si el contador de caracteres es 2 (es decir la pos 3 del arreglo)
            *  entonces se imprimira ":" correspodiente a la hora */
            if (contador_caracter == 2)
            {
                tempHora[contador_caracter] = ':';

                settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

                /* Se imprime */
                setcolor(15);
                outtextxy(x, y, tempHora);

                tempHora[contador_caracter + 1] = '\0';

                setcolor(8);
                outtextxy(x, y, tempHora);

                contador_caracter++; /* Contador = 3 */
            }

            /* Si el contador de caracteres es 3 (es decir la pos 4 del arreglo) */
            if (contador_caracter == 3)
            {
                /* Si se digita un numero del 0 al 5 (correspondiente a los minutos) */
                if (tempHora[contador_caracter] >= '0' && tempHora[contador_caracter] <= '5')
                {
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                    
                    /* Se imprime */
                    setcolor(15);
                    outtextxy(x, y, tempHora);

                    tempHora[contador_caracter + 1] = '\0';

                    setcolor(8);
                    outtextxy(x, y, tempHora);

                    contador_caracter++; /* Contador = 4 */
                }
            }

            /* Si el contador de caracteres es 4 (es decir la pos 5 del arreglo) */
            if (contador_caracter == 4)
            {
                /* Si se digita un numero del 0 al 9 */
                if (tempHora[contador_caracter] >= '0' && tempHora[contador_caracter] <= '9')
                {
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

                    /* Se imprime */   
                    setcolor(15);
                    outtextxy(x, y, tempHora);

                    tempHora[contador_caracter + 1] = '\0';

                    setcolor(8);
                    outtextxy(x, y, tempHora);

                    contador_caracter++; /* Contador = 5 */
                }
            }
        }
    }
}