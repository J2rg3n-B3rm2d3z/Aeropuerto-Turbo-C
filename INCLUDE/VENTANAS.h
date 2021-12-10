#include  <fAuxi.h>

/*-----------------------------------------PROTOTIPADO DE FUNCIONES------------------------------*/
void iniciarModoGrafico(void);
int entradaAeropuerto(void);
int panelDeControl(void);
int ingresoVuelo(void);
int despeje(int registro, int despejado);
int radar(int xo, int yo, int xf, int yf, int Pais); /*Funcion para mover el circulo por medio de una tryectoria*/
int registro(int i, int destino);
/*--------------------------------------------------------------------------------------------*/

int entradaAeropuerto()
{
    fondoPantallaIncio();
    edificioAeropuerto();
    avionPantallaInicio();
    return 0;
}

void iniciarModoGrafico()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
}

int panelDeControl()
{
    setbkcolor(0);
    fondoPanelDeControl();
    ventanasPanelDeControl();
    controles();
    return 1;
}

int ingresoVuelo() 
{
    char tempNombre[TAMNOMBRES]; /* Variable temporal donde se guardara el nombre de la aereolinea ingresada */
    char tempNumVuelo[NUMVUELO]; /* Var temporal donde se guardara el numero de vuelo ingresado */
    char tempHora[TAMHORA];      /* Var temporal donde se guardara la hora ingresada */
    char *tempPais;              /* Var temporal donde se guardara el nombre del lugar destino */

    unsigned int xpos = 0, ypos = 0, guardar = 1, aereo = 1, vuelo = 1, hora = 1, pais = 1, correctAereo;
    int nombre = -1;

    Interfaz();

    do
    {
        /* Se obliga a presionar click izquierdo */
        while (mclick() != 1)
            ;

        /* Se obtienen las coordenadas del raton donde se ecuentre actualmente */
        xpos = mxpos(1);
        ypos = mypos(1);

        /* Si se encuentra dentro de la caja de datos del nombre aereoline */
        if (limit(xpos, ypos, entradaAereo.x1, entradaAereo.y1, entradaAereo.x2, entradaAereo.y2))
        {
            /* Simulacion de presionado */
            entradaAereo.effect = PRESS;
            mocultar();

            /* Se dibuja una nueva caja de entrada en la aereolinea y numero de vuelo
            *  para validar que si ya ingreso una aereolinea y un numero de vuelo (correspondiente a esa aereolinea)
            *  y luego vuelver a dar click en la aereolinea (para cambiarla) se borre automaticamente el numero de vuelo pasado */
            drawInputBox(&entradaAereo);
            drawInputBox(&entradaVuelo);

            mver();

            /* Se obliga a dar click dentro de la caja para escribir los datos */
            while (mclick() != 0 && minlimit(1, entradaAereo.x1, entradaAereo.y1, entradaAereo.x2, entradaAereo.y2))
            {
                if (kbhit())
                {
                    getch();
                }
            }

            /* Si presiono dentro de la caja realizara la accion */
            if (minlimit(1, entradaAereo.x1, entradaAereo.y1, entradaAereo.x2, entradaAereo.y2))
            {
                /* Se piden los datos de la aereoline */
                aereolinea(tempNombre, entradaAereo.x1, entradaAereo.y1);

                /* Si no se escribio nada, la variable bool "save" (guardar) sera igual a 1 (falso) */
                if (strlen(tempNombre) <= 1)
                {
                    entradaAereo.effect = UNPRESS;
                    mocultar();
                    drawInputBox(&entradaAereo);
                    mver();

                    guardar = 1;

                    /* Sino se ingreso una aereolinea, es falso (para validar que se ingresen todos los datos antes de guardar) */
                    aereo = 1;
                }
                else
                {
                    /* Se valida si la aereolinea ingresada no es correcta */
                    if (!((strcmp(tempNombre, aereolinea1) == 0) || (strcmp(tempNombre, aereolinea2) == 0)))
                    {
                        /* Efecto de no presionado */
                        entradaAereo.effect = UNPRESS;

                        mocultar();

                        drawInputBox(&entradaAereo);

                        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                        setcolor(RED);
                        outtextxy(entradaAereo.x1 + 3, entradaAereo.y1 + 10, "No encontrado");

                        mver();

                        correctAereo = 1;
                    }
                    else
                    {
                        entradaAereo.effect = UNPRESS;

                        mocultar();

                        drawInputBox(&entradaAereo);

                        /* Se muestra lo que se digito */
                        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                        setcolor(8);
                        outtextxy(entradaAereo.x1 + 15, entradaAereo.y1 + 13, tempNombre);

                        mver();

                        /* Si la aereolinea ingresada es correcta entonces la variable bool es verdadera */
                        correctAereo = 0;

                        /* Si se escribio algo, variable bool es 0 (verdadero)*/
                        guardar = 0;

                        /* Si se ingreso una aereolinea es verdadero (para validar que se hayan ingresado todos los datos) */
                        aereo = 0;
                    }

                    /* Si se escribio algo, variable bool es 0 (verdadero)*/
                    /*save = 0 ;*/
                }
            }
        }
        /* Si se encuentra dentro de la caja de datos de numero de vuelo */
        else if (limit(xpos, ypos, entradaVuelo.x1, entradaVuelo.y1, entradaVuelo.x2, entradaVuelo.y2))
        {
            entradaVuelo.effect = PRESS;
            mocultar();
            drawInputBox(&entradaVuelo);
            mver();

            while (mclick() != 0 && minlimit(1, entradaVuelo.x1, entradaVuelo.y1, entradaVuelo.x2, entradaVuelo.y2))
                ;

            if (minlimit(1, entradaVuelo.x1, entradaVuelo.y1, entradaVuelo.x2, entradaVuelo.y2))
            {
                /* Si la aereolinea ingresada es correcta se pueden ingresar el num de vuelo */
                if (correctAereo == 0)
                {
                    numVuelo(tempNombre, tempNumVuelo, entradaVuelo.x1, entradaVuelo.y1);

                    if (strlen(tempNumVuelo) <= 1)
                    {
                        entradaVuelo.effect = UNPRESS;
                        mocultar();
                        drawInputBox(&entradaVuelo);
                        mver();

                        guardar = 1;

                        /* Sino se ingreso un numero de vuelo es falso (para validar que se ingresen todos los datos antes de guardar) */
                        vuelo = 1;
                    }
                    else
                    {
                        entradaVuelo.effect = UNPRESS;

                        mocultar();

                        drawInputBox(&entradaVuelo);

                        /* Se muestra lo que se digito */
                        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                        setcolor(8);
                        outtextxy(entradaVuelo.x1 + 25, entradaVuelo.y1 + 13, tempNumVuelo);

                        mver();

                        correctAereo = 0;

                        /* Si se escribio algo, variable bool es 0 (verdadero)*/
                        guardar = 0;

                        /* Si se ingreso un numero de vuelo es verdadero (para validar que se ingresen todos los datos antes de guardar) */
                        vuelo = 0;
                    }
                }
                else
                {
                    entradaVuelo.effect = UNPRESS;
                    mocultar();
                    drawInputBox(&entradaVuelo);
                    mver();
                }
            }
        }
        /* Si se encuentra dentro de la caja Hora de salida */
        else if (limit(xpos, ypos, entradaHora.x1, entradaHora.y1, entradaHora.x2, entradaHora.y2))
        {
            entradaHora.effect = PRESS;
            mocultar();
            drawInputBox(&entradaHora);
            mver();

            while (mclick() != 0 && minlimit(1, entradaHora.x1, entradaHora.y1, entradaHora.x2, entradaHora.y2))
                ;

            if (minlimit(1, entradaHora.x1, entradaHora.y1, entradaHora.x2, entradaHora.y2))
            {
                /* Si la aereolinea ingresada es correcta se puede ingresar la hora de salida */
                if (correctAereo == 0)
                {
                    Hora(tempHora, entradaHora.x1, entradaHora.y1);

                    if (strlen(tempHora) <= 1)
                    {
                        entradaHora.effect = UNPRESS;
                        mocultar();
                        drawInputBox(&entradaHora);
                        mver();

                        guardar = 1;

                        /* Sino se ingreso una hora es falso (para validar que se ingresen todos los datos antes de guardar) */
                        hora = 1;
                    }
                    else
                    {
                        entradaHora.effect = UNPRESS;
                        mocultar();
                        drawInputBox(&entradaHora);

                        /* Se muestra lo que se digito */
                        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                        setcolor(8);
                        outtextxy(entradaHora.x1 + 19, entradaHora.y1 + 12, tempHora);

                        mver();

                        correctAereo = 0;

                        /* Si se escribio algo, variable bool es 0 (verdadero)*/
                        guardar = 0;

                        /* Si se ingreso una hora es verdadero (para validar que se ingresen todos los datos antes de guardar) */
                        hora = 0;
                    }
                }
                else
                {
                    entradaHora.effect = UNPRESS;
                    mocultar();
                    drawInputBox(&entradaHora);
                    mver();
                }
            }
        }

        /* Si se presiona dentro de EEUU en el croquis */
        else if (limit(xpos, ypos, 164, 94, 186, 110) || limit(xpos, ypos, 155, 108, 162, 119))
        {
            while ((mclick() != 0) && (minlimit(1, 164, 94, 186, 110) || minlimit(1, 155, 108, 162, 119)))
                ;

            if (minlimit(1, 164, 94, 186, 110) || minlimit(1, 155, 108, 162, 119))
            {
                /* Si escribio la aereolinea correcta y se han escrito los demas datos
                *  entonces si puede seleccionar un pais */
                if (correctAereo == 0 && guardar == 0 && aereo == 0 && vuelo == 0 && hora == 0)
                {
                    /* Si presiono en cualquiera de las coordenadas dentro del pais (EEUU) */
                    tempPais = "EEUU";

                    mocultar();
                    drawInputBox(&entradaPais);
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                    setcolor(8);
                    outtextxy(entradaPais.x1 + 19, entradaPais.y1 + 12, tempPais);
                    mver();

                    /* Variable bool guardar es Verdadero */
                    guardar = 0;

                    /* Si se ingreso un pais, es verdadero */
                    pais = 0;

                    /* Se asigna 0 para indicarle el numero del pais seleccionado */
                    nombre = 0;
                }
                else
                {
                    /* Si la condicion no se cumple, variable bool Falso */
                    guardar = 1;

                    /* Sino se ingreso ningun pais, es falso */
                    pais = 1;
                }
            }
        }

        /* Si se presiona dentro de EEUU en el croquis */
        else if (limit(xpos, ypos, 183, 138, 222, 148) || limit(xpos, ypos, 179, 149, 230, 176) || limit(xpos, ypos, 231, 153, 239, 170) || limit(xpos, ypos, 174, 151, 178, 174))
        {
            while ((mclick() != 0) && (minlimit(1, 183, 138, 222, 148) || minlimit(1, 179, 149, 230, 176) || minlimit(1, 231, 153, 239, 170) || minlimit(1, 174, 151, 178, 174)))
                ;

            if (minlimit(1, 183, 138, 222, 148) || minlimit(1, 179, 149, 230, 176) || minlimit(1, 231, 153, 239, 170) || minlimit(1, 174, 151, 178, 174))
            {
                /* Si escribio la aereolinea correcta y se han escrito los demas datos
                *  entonces si puede seleccionar un pais */
                if (correctAereo == 0 && guardar == 0 && aereo == 0 && vuelo == 0 && hora == 0)
                {
                    /* Si presiono en cualquiera de las coordenadas dentro del pais (EEUU) */
                    tempPais = "EEUU";

                    mocultar();
                    drawInputBox(&entradaPais);
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                    setcolor(8);
                    outtextxy(entradaPais.x1 + 19, entradaPais.y1 + 12, tempPais);
                    mver();

                    /* Variable bool guardar es Verdadero */
                    guardar = 0;

                    /* Si se ingreso un pais, es vedadero*/
                    pais = 0;

                    /* Se asigna 0 para indicarle el numero del pais seleccionado */
                    nombre = 0;
                }
                else
                {
                    /* Si la condicion no se cumple, variable bool Falso */
                    guardar = 1;

                    /* Sino se ingreso un pais, es falso */
                    pais = 1;
                }
            }
        }

        /* Si presiono en Mexico */
        else if (limit(xpos, ypos, 176, 180, 184, 195) || limit(xpos, ypos, 185, 180, 194, 188) || limit(xpos, ypos, 188, 189, 201, 208) || limit(xpos, ypos, 201, 209, 211, 218))
        {
            while ((mclick() != 0) && (minlimit(1, 176, 180, 184, 195) || minlimit(1, 185, 180, 194, 188) || minlimit(1, 188, 189, 201, 208) || minlimit(1, 201, 209, 211, 218)))
                ;

            if (minlimit(1, 176, 180, 184, 195) || minlimit(1, 185, 180, 194, 188) || minlimit(1, 188, 189, 201, 208) || minlimit(1, 201, 209, 211, 218))
            {
                /* Si escribio la aereolinea correcta y se han escrito los demas datos
                *  entonces si puede seleccionar un pais */
                if (correctAereo == 0 && guardar == 0 && aereo == 0 && vuelo == 0 && hora == 0)
                {
                    /* Si presiono en cualquiera de las coordenadas dentro del pais (EEUU) */
                    tempPais = "Mexico";

                    mocultar();
                    drawInputBox(&entradaPais);
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                    setcolor(8);
                    outtextxy(entradaPais.x1 + 19, entradaPais.y1 + 12, tempPais);
                    mver();

                    /* Variable bool guardar es Verdadero */
                    guardar = 0;

                    /* Si se ingreso un pais, es vedadero*/
                    pais = 0;

                    /* Se asigna 2 para indicarle el numero del pais seleccionado */
                    nombre = 2;
                }
                else
                {
                    /* Si la condicion no se cumple, variable bool Falso */
                    guardar = 1;

                    /* Sino se ingreso un pais, es falso */
                    pais = 1;
                }
            }
        }

        /* Si presiono en Argentina */
        else if (limit(xpos, ypos, 245, 305, 257, 339) || limit(xpos, ypos, 247, 340, 255, 370))
        {
            while ((mclick() != 0) && (minlimit(1, 245, 305, 257, 339) || minlimit(1, 247, 340, 255, 370)))
                ;

            if (minlimit(1, 245, 305, 257, 339) || minlimit(1, 247, 340, 255, 370))
            {
                /* Si escribio la aereolinea correcta y se han escrito los demas datos
                *  entonces si puede seleccionar un pais */
                if (correctAereo == 0 && guardar == 0 && aereo == 0 && vuelo == 0 && hora == 0)
                {
                    /* Si presiono en cualquiera de las coordenadas dentro del pais (Argentina) */
                    tempPais = "Argentina";

                    mocultar();
                    drawInputBox(&entradaPais);
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                    setcolor(8);
                    outtextxy(entradaPais.x1 + 19, entradaPais.y1 + 12, tempPais);
                    mver();

                    /* Variable bool guardar es Verdadero */
                    guardar = 0;

                    /* Si se ingreso un pais, es vedadero*/
                    pais = 0;

                    /* Se asigna 1 para indicarle el numero del pais seleccionado */
                    nombre = 1;
                }
                else
                {
                    /* Si la condicion no se cumple, variable bool Falso */
                    guardar = 1;

                    /* Sino se ingreso un pais, es falso*/
                    pais = 1;
                }
            }
        }

        /* Si presiono en Inglaterra */
        else if (limit(xpos, ypos, 334, 118, 342, 135))
        {
            while ((mclick() != 0) && (minlimit(1, 334, 118, 342, 135)))
                ;

            if (minlimit(1, 334, 118, 342, 135))
            {
                /* Si escribio la aereolinea correcta y se han escrito los demas datos
                *  entonces si puede seleccionar un pais */
                if (correctAereo == 0 && guardar == 0 && aereo == 0 && vuelo == 0 && hora == 0)
                {
                    /* Si presiono en cualquiera de las coordenadas dentro del pais (Argentina) */
                    tempPais = "Inglaterra";

                    mocultar();
                    drawInputBox(&entradaPais);
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                    setcolor(8);
                    outtextxy(entradaPais.x1 + 19, entradaPais.y1 + 12, tempPais);
                    mver();

                    /* Variable bool guardar es Verdadero */
                    guardar = 0;

                    /* Si se ingreso un pais, es vedadero*/
                    pais = 0;

                    /* Se asigna 5 para indicarle el numero del pais seleccionado */
                    nombre = 5;
                }
                else
                {
                    /* Si la condicion no se cumple, variable bool Falso */
                    guardar = 1;

                    /* Sino se ingreso un pais, es falso*/
                    pais = 1;
                }
            }
        }

        /* Si presiono en Alemania */
        else if (limit(xpos, ypos, 350, 126, 362, 144))
        {
            while ((mclick() != 0) && (minlimit(1, 350, 126, 362, 144)))
                ;

            if (minlimit(1, 350, 126, 362, 144))
            {
                /* Si escribio la aereolinea correcta y se han escrito los demas datos
                *  entonces si puede seleccionar un pais */
                if (correctAereo == 0 && guardar == 0 && aereo == 0 && vuelo == 0 && hora == 0)
                {
                    /* Si presiono en cualquiera de las coordenadas dentro del pais (Argentina) */
                    tempPais = "Alemania";

                    mocultar();
                    drawInputBox(&entradaPais);
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                    setcolor(8);
                    outtextxy(entradaPais.x1 + 19, entradaPais.y1 + 12, tempPais);
                    mver();

                    /* Variable bool guardar es Verdadero */
                    guardar = 0;

                    /* Si se ingreso un pais, es vedadero*/
                    pais = 0;

                    /* Se asigna 4 para indicarle el numero del pais seleccionado */
                    nombre = 4;
                }
                else
                {
                    /* Si la condicion no se cumple, variable bool Falso */
                    guardar = 1;

                    /* Sino se ingreso un pais, es falso */
                    pais = 1;
                }
            }
        }

        /* Si presiono en Japon */
        else if (limit(xpos, ypos, 523, 149, 531, 172))
        {
            while ((mclick() != 0) && (minlimit(1, 523, 149, 531, 172)))
                ;

            if (minlimit(1, 523, 149, 531, 172))
            {
                /* Si escribio la aereolinea correcta y se han escrito los demas datos
                *  entonces si puede seleccionar un pais */
                if (correctAereo == 0 && guardar == 0 && aereo == 0 && vuelo == 0 && hora == 0)
                {
                    /* Si presiono en cualquiera de las coordenadas dentro del pais (Argentina) */
                    tempPais = "Japon";

                    mocultar();
                    drawInputBox(&entradaPais);
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
                    setcolor(8);
                    outtextxy(entradaPais.x1 + 19, entradaPais.y1 + 12, tempPais);
                    mver();

                    /* Variable bool guardar es Verdadero */
                    guardar = 0;

                    /* Si se ingreso un pais, es vedadero*/
                    pais = 0;

                    /* Se asigna 3 para indicarle el numero del pais seleccionado */
                    nombre = 3;
                }
                else
                {
                    /* Si la condicion no se cumple, variable bool Falso */
                    guardar = 1;

                    /* Sino se ingreso un pais, es falso */
                    pais = 1;
                }
            }
        }

        /* Si se encuentra en el boton Guardar */
        else if (limit(xpos, ypos, btnGuardar.x1, btnGuardar.y1, btnGuardar.x2, btnGuardar.y2))
        {
            btnGuardar.effect = PRESS;
            mocultar();
            drawButton2(&btnGuardar);
            mver();

            while (mclick() != 0 && minlimit(1, btnGuardar.x1, btnGuardar.y1, btnGuardar.x2, btnGuardar.y2))
                ;

            if (minlimit(1, btnGuardar.x1, btnGuardar.y1, btnGuardar.x2, btnGuardar.y2))
            {
                /* Si se escribieron los datos entonces se guardara */
                if (guardar == 0 && aereo == 0 && vuelo == 0 && hora == 0 && pais == 0)
                {
                    /*contador_regis < TAM*/
                    if (contador_regis < TAM)
                    {
                        /* Si se desean guardar cambios se guardaran los datos en la estructura de datos y en el fichero */
                        strcpy(Datos[contador_regis].aereolinea, tempNombre);

                        strcpy(Datos[contador_regis].numVuelo, tempNumVuelo);

                        strcpy(Datos[contador_regis].horaSalida, tempHora);

                        strcpy(Datos[contador_regis].Pais, tempPais);

                        /* Se llama la funcion donde se guardaran los datos en el fichero */
                        guardarDatos();

                        /* Se retorna el numero del pais ingresado  */
                        return nombre;
                    }

                    /* El contador de registros aumenta */
                    contador_regis++;

                    /*contador_regis == TAM*/
                    if (contador_regis == TAM)
                    {
                        ErrorMessage(10, 438, 117, 467, "REGISTRO LLENO!");
                    }
                }
                else
                {
                    /*Text3D(10, 450, 2, 15, 4, "> Ingrese los datos para guardar");*/
                    drawInputBox(&entradaAereo);
                    drawInputBox(&entradaVuelo);
                    drawInputBox(&entradaHora);
                    drawInputBox(&entradaPais);

                    settextstyle(SMALL_FONT, HORIZ_DIR, 4);
                    /* Se manda mensaje donde se ingresa la aereolinea */
                    setcolor(4);
                    outtextxy(40, 96, "Ingrese");
                    outtextxy(50, 104, "los");
                    outtextxy(45, 112, "datos");

                    /* Se manda mensaje donde se ingresa el num vuelo */
                    setcolor(4);
                    outtextxy(40, 166, "Ingrese");
                    outtextxy(50, 174, "los");
                    outtextxy(45, 182, "datos");

                    /* Se manda mensaje donde se ingresa la hora */
                    setcolor(4);
                    outtextxy(40, 236, "Ingrese");
                    outtextxy(50, 244, "los");
                    outtextxy(45, 252, "datos");

                    /* Se manda mensaje donde se imprime el lugar */
                    setcolor(4);
                    outtextxy(40, 306, "Ingrese");
                    outtextxy(50, 314, "los");
                    outtextxy(45, 322, "datos");
                }
            }

            btnGuardar.effect = UNPRESS;
            mocultar();
            drawButton2(&btnGuardar);
            mver();
        }

        /* Si se encuentra dentro del boton Cancelar */
        else if (limit(xpos, ypos, btnCancelar.x1, btnCancelar.y1, btnCancelar.x2, btnCancelar.y2))
        {
            btnCancelar.effect = PRESS;
            mocultar();
            drawButton2(&btnCancelar);
            mver();

            while (mclick() != 0 && minlimit(1, btnCancelar.x1, btnCancelar.y1, btnCancelar.x2, btnCancelar.y2))
                ;

            if (minlimit(1, btnCancelar.x1, btnCancelar.y1, btnCancelar.x2, btnCancelar.y2))
            {
                /* Si se realiza la accion se cierra el modo grafico y termina el programa */

                /* Retorna -1 sino se ingreso ningun pais */

                return -1;

                break;
            }

            btnCancelar.effect = UNPRESS;
            mocultar();
            drawButton2(&btnCancelar);
            mver();
        }

        while (mclick() == 1)
            ;

    } while (true);
}

int despeje(int registro, int despejado)
{
    button btnAvion1, btnAvion2, btnAvion3, btnAvion4, btnAvion5, btnRegresar;
    int xpos = mxpos(1); /*Capturamos su posicion evitando su desplazamiento*/
    int ypos = mypos(1);
    /*aviones*/
    int avion_1[] = {20, 320, 48, 314, 62, 311, 63, 341, 45, 351, 66, 349, 86, 350, 70, 341, 71, 312, 84, 312, 119, 318, 85, 304, 84, 294, 79, 294, 79, 299, 72, 298, 70, 270, 64, 270, 61, 297, 57, 300, 56, 293, 52, 293, 52, 304, 20, 320};
    int avion_2[] = {143, 320, 172, 313, 185, 311, 185, 340, 170, 351, 189, 348, 208, 351, 194, 341, 195, 310, 207, 312, 237, 320, 205, 303, 205, 295, 201, 294, 200, 300, 196, 298, 194, 278, 189, 265, 184, 278, 183, 297, 178, 300, 178, 295, 174, 295, 173, 303, 143, 320};
    int avion_3[] = {294, 322, 324, 313, 335, 313, 337, 341, 321, 353, 341, 350, 363, 353, 346, 341, 348, 313, 363, 314, 395, 321, 359, 303, 359, 295, 352, 295, 352, 300, 348, 299, 348, 283, 341, 270, 335, 281, 335, 298, 331, 302, 331, 296, 326, 296, 326, 304, 294, 322};
    int avion_4[] = {454, 315, 456, 341, 438, 354, 460, 349, 480, 354, 464, 343, 466, 316, 474, 316, 481, 316, 510, 321, 475, 303, 475, 296, 470, 296, 470, 301, 466, 301, 466, 281, 460, 269, 454, 280, 454, 301, 449, 303, 449, 298, 442, 298, 442, 305, 411, 322, 442, 315, 452, 315};
    int avion_5[] = {538, 322, 569, 314, 580, 314, 582, 342, 564, 353, 587, 349, 607, 353, 590, 343, 593, 314, 603, 315, 634, 322, 602, 306, 602, 298, 596, 298, 596, 304, 591, 300, 591, 281, 585, 270, 580, 281, 580, 298, 576, 302, 576, 297, 569, 297, 569, 305, 538, 322};
    /*pavimento poligonos */
    int poli_1[] = {16, 337, 51, 372, 91, 372, 126, 337, 126, 286, 92, 252, 51, 252, 16, 287, 16, 337};
    int poli_2[] = {136, 337, 171, 372, 209, 372, 243, 333, 243, 286, 209, 252, 170, 252, 136, 285, 136, 337};
    int poli_3[] = {288, 332, 326, 370, 363, 370, 395, 331, 395, 286, 361, 252, 321, 252, 287, 286, 288, 332};
    int poli_4[] = {406, 288, 441, 253, 475, 253, 513, 289, 513, 339, 482, 375, 442, 375, 405, 338, 406, 288};
    int poli_5[] = {532, 287, 566, 253, 604, 253, 637, 290, 637, 344, 606, 375, 569, 375, 533, 342, 532, 287};
    /*acion de despegue*/
    int avion_despegue[] = {28, 112, 53, 112, 53, 95, 46, 66, 54, 66, 60, 82, 66, 82, 66, 87, 62, 87, 65, 95, 72, 95, 72, 100, 68, 100, 74, 111, 92, 111, 101, 116, 94, 119, 74,
                            119, 70, 131, 73, 131, 73, 136, 67, 136, 64, 142, 67, 144, 67, 149, 61, 149, 53, 165, 47, 165, 53, 134, 54, 121, 40, 121, 31, 118, 22, 131, 17, 131, 21, 117, 16, 101, 21, 101, 28, 112};

    /**/
    void *buffer2;
    int i;
    /**/
    setbkcolor(8);
    /*-------------------------------------------------------------pavimento------------------------------------------------*/
    setfillstyle(SOLID_FILL, 7);
    bar(0, 0, 640, 480);
    setfillstyle(SOLID_FILL, 8); /*pista*/
    bar(0, 6, 640, 226);
    setfillstyle(SOLID_FILL, LIGHTBLUE); /*torre*/
    bar(0, 410, 640, 480);
    setbkcolor(8);
    setcolor(15);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH); /*lineas de la pista*/
    line(1, 52, 290, 52);
    line(290, 52, 290, 6);
    line(344, 52, 640, 52);
    line(344, 52, 344, 6);
    line(300, 6, 300, 37);
    line(312, 6, 312, 37);
    line(323, 6, 323, 37);
    line(335, 6, 335, 37);
    line(1, 180, 290, 180);
    line(290, 180, 290, 226);
    line(344, 180, 640, 180);
    line(344, 180, 344, 226);
    line(300, 197, 300, 226);
    line(312, 197, 312, 226);
    line(323, 197, 323, 226);
    line(335, 197, 335, 226);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH); /*lineas de la pista*/
    line(82, 36, 290, 36);
    line(82, 36, 82, 6);
    line(344, 36, 526, 36);
    line(526, 36, 526, 6);
    line(46, 204, 290, 204);
    line(46, 204, 46, 226);
    line(344, 204, 590, 204);
    line(590, 204, 590, 226);
    setfillstyle(SOLID_FILL, YELLOW); /*luces de pista*/
    bar(121, 58, 124, 62);
    bar(176, 58, 179, 62);
    bar(232, 58, 235, 62);
    bar(287, 58, 290, 62);
    bar(342, 58, 345, 62);
    bar(398, 58, 401, 62);
    bar(454, 58, 457, 62);
    bar(510, 58, 512, 62);
    bar(121, 170, 124, 174);
    bar(176, 170, 179, 174);
    bar(232, 170, 235, 174);
    bar(287, 170, 290, 174);
    bar(342, 170, 345, 174);
    bar(398, 170, 401, 174);
    bar(454, 170, 457, 174);
    bar(510, 170, 512, 174);
    /*los poligonos del pavimento*/
    setcolor(YELLOW);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    setfillstyle(SOLID_FILL, 8);
    fillpoly(9, poli_1);
    fillpoly(9, poli_2);
    fillpoly(9, poli_3);
    fillpoly(9, poli_4);
    fillpoly(9, poli_5);
    /*----------------------------------------------------pasarelas----------------------------------------------------*/
    setcolor(10);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    setfillstyle(SOLID_FILL, 9);
    bar(72, 288, 180, 298);
    bar(137, 298, 120, 450);
    bar(349, 289, 454, 300);
    bar(394, 296, 410, 454);
    bar(590, 283, 640, 294);
    bar(625, 284, 640, 450);
    /*-----------------------------------------------borde del aeropuerto-----------------------------*/
    setcolor(15);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    setfillstyle(SOLID_FILL, 15);
    line(10, 468, 285, 468);
    line(10, 425, 285, 425);
    line(343, 468, 630, 468);
    line(343, 425, 630, 425);

    /*torre*/
    setfillstyle(SOLID_FILL, 8);
    bar(275, 410, 360, 480);

    setcolor(15);
    circle(318, 445, 30);
    setcolor(14);
    circle(318, 445, 2);
    setcolor(BLUE);

    circle(285, 473, 2);
    circle(352, 473, 2);
    circle(285, 418, 2);
    circle(352, 418, 2);

    /*colorea aviones en pasarela*/
    setcolor(15);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    setfillstyle(SOLID_FILL, 15);
    fillpoly(24, avion_1);
    fillpoly(25, avion_2);
    fillpoly(25, avion_3);
    fillpoly(26, avion_4);
    fillpoly(25, avion_5);
    /*botones___________________________________________________________________________________________________*/

    newButton(&btnAvion1, 36, 384, " Avion 1 ");
    newButton(&btnAvion2, 156, 384, " Avion 2 ");
    newButton(&btnAvion3, 305, 384, "  Avion 3 ");
    newButton(&btnAvion4, 430, 384, " Avion 4 ");
    newButton(&btnAvion5, 548, 384, "  Avion 5  ");
    mver();
    switch (registro)
    {
    case 1:
        if (despejado == 1)
        {
            desaparecerAvion1(poli_1);
        }
        break;
    case 2:
        if (despejado == 1)
        {
            desaparecerAvion1(poli_1);
            desaparecerAvion2(poli_2);
        }
        else
        {
            desaparecerAvion1(poli_1);
        }
        break;
    case 3:
        if (despejado == 1)
        {
            desaparecerAvion1(poli_1);
            desaparecerAvion2(poli_2);
            desaparecerAvion3(poli_3);
        }
        else
        {
            desaparecerAvion1(poli_1);
            desaparecerAvion2(poli_2);
        }
        break;
    case 4:
        if (despejado == 1)
        {
            desaparecerAvion1(poli_1);
            desaparecerAvion2(poli_2);
            desaparecerAvion3(poli_3);
            desaparecerAvion4(poli_4);
        }
        else
        {
            desaparecerAvion1(poli_1);
            desaparecerAvion2(poli_2);
            desaparecerAvion3(poli_3);
        }
        break;
    case 5:
        if (despejado == 0)
        {
            desaparecerAvion1(poli_1);
            desaparecerAvion2(poli_2);
            desaparecerAvion3(poli_3);
            desaparecerAvion4(poli_4);
        }
        break;
    default:
        break;
    }
    if (registro > 5 || registro == 5 && despejado == 1)
    {
        desaparecerAvion1(poli_1);
        desaparecerAvion2(poli_2);
        desaparecerAvion3(poli_3);
        desaparecerAvion4(poli_4);
        desaparecerAvion5(poli_5);
        setcolor(15);
        outtextxy(150, 150, "Ya despejaron todos los aviones");
        delay(10000);
    }
    else if (despejado == 1)
    {
        setcolor(15);
        outtextxy(150, 150, "Ya despejo el avion registrado");
        delay(300000);
    }
    else if (registro == 0)
    {
        setcolor(15);
        outtextxy(150, 150, "NO SE HA REGISTRADO NINGUN AVION");
        delay(10000);
    }
    else
    {
        do
        {
            while (mclick() != 1)
                ;            /*Esperamos que haga un click*/
            xpos = mxpos(1); /*Capturamos su posicion evitando su desplazamiento*/
            ypos = mypos(1);
            if (limit(xpos, ypos, btnAvion1.x1, btnAvion1.y1, btnAvion1.x2, btnAvion1.y2))
            {
                /*Hacemos el efecto que esta presionado*/
                btnAvion1.effect = PRESS;
                mocultar();
                drawButton(&btnAvion1);
                mver();

                /*Validar que el click se suelte o salga del boton para asi saber si se ejecuta o no la accion*/
                while (mclick() != 0 && minlimit(1, btnAvion1.x1, btnAvion1.y1, btnAvion1.x2, btnAvion1.y2))
                    ;
                mocultar();
                btnAvion1.effect = UNPRESS;
                /*Si la region en que lo solto es en las cordenadas del boton que ejecute la accion*/
                if (minlimit(1, btnAvion1.x1, btnAvion1.y1, btnAvion1.x2, btnAvion1.y2) && registro == 1)
                {
                    /*-----------------------------------------------------funcionalidad-----------------------------------------*/
                    setcolor(15);
                    settextstyle(2, 0, 2);
                    /*outtextxy(250,280,"Ingrese la hora de despegue");  -------------------bloque para pedir el despegue*/

                    desaparecerAvion1(poli_1);

                    /*SIMULACION DEL DESPEGUE-------------------------------------------*/
                    setcolor(WHITE);
                    setfillstyle(SOLID_FILL, 15);
                    buffer2 = malloc(imagesize(0, 0, 88, 103));
                    fillpoly(38, avion_despegue);
                    getimage(14, 65, 102, 168, buffer2);
                    delay(5);
                    putimage(14, 65, buffer2, 1);

                    for (i = 0; i < 854; i += 2)
                    {

                        putimage(14 + i, 65, buffer2, 0);
                        delay(100);

                        putimage(14 + i, 65, buffer2, 1);
                    }
                    free(buffer2);
                    break;
                }
                /*Se pinta el boton desprecionado*/
                drawButton(&btnAvion1);
                mver();
            }

            else if (limit(xpos, ypos, btnAvion2.x1, btnAvion2.y1, btnAvion2.x2, btnAvion2.y2))
            {
                /*Hacemos el efecto que esta presionado*/
                btnAvion2.effect = PRESS;
                mocultar();
                drawButton(&btnAvion2);
                mver();

                /*Validar que el click se suelte o salga del boton para asi saber si se ejecuta o no la accion*/
                while (mclick() != 0 && minlimit(1, btnAvion2.x1, btnAvion2.y1, btnAvion2.x2, btnAvion2.y2))
                    ;
                mocultar();
                btnAvion2.effect = UNPRESS;
                /*Si la region en que lo solto es en las cordenadas del boton que ejecute la accion*/
                if (minlimit(1, btnAvion2.x1, btnAvion2.y1, btnAvion2.x2, btnAvion2.y2) && registro == 2)
                {

                    /*-----------------------------------------------------funcionalidad-----------------------------------------*/
                    /* BOTON 2------------------------------------------------------*/

                    desaparecerAvion2(poli_2);

                    /*SIMULACION DEL DESPEGUE-------------------------------------------*/
                    setcolor(WHITE);
                    setfillstyle(SOLID_FILL, 15);
                    buffer2 = malloc(imagesize(0, 0, 88, 103));
                    fillpoly(38, avion_despegue);
                    getimage(14, 65, 102, 168, buffer2);
                    delay(5);
                    putimage(14, 65, buffer2, 1);

                    for (i = 0; i < 854; i += 2)
                    {
                        putimage(14 + i, 65, buffer2, 0);
                        delay(100);
                        putimage(14 + i, 65, buffer2, 1);
                    }
                    free(buffer2);
                    break;
                }
                /*Se pinta el boton desprecionado*/
                drawButton(&btnAvion2);
                mver();
            }

            /*--------------------------------------------------------------------------------------......................................*/

            else if (limit(xpos, ypos, btnAvion3.x1, btnAvion3.y1, btnAvion3.x2, btnAvion3.y2))
            {
                /*Hacemos el efecto que esta presionado*/
                btnAvion3.effect = PRESS;
                mocultar();
                drawButton(&btnAvion3);
                mver();

                /*Validar que el click se suelte o salga del boton para asi saber si se ejecuta o no la accion*/
                while (mclick() != 0 && minlimit(1, btnAvion3.x1, btnAvion3.y1, btnAvion3.x2, btnAvion3.y2))
                    ;
                mocultar();
                btnAvion3.effect = UNPRESS;
                /*Si la region en que lo solto es en las cordenadas del boton que ejecute la accion*/
                if (minlimit(1, btnAvion3.x1, btnAvion3.y1, btnAvion3.x2, btnAvion3.y2) && registro == 3)
                {
                    /*-----------------------------------------------------funcionalidad-----------------------------------------*/
                    desaparecerAvion3(poli_3);
                    /*SIMULACION DEL DESPEGUE-------------------------------------------*/
                    setcolor(WHITE);
                    setfillstyle(SOLID_FILL, 15);
                    buffer2 = malloc(imagesize(0, 0, 88, 103));
                    fillpoly(38, avion_despegue);
                    getimage(14, 65, 102, 168, buffer2);
                    delay(5);
                    putimage(14, 65, buffer2, 1);

                    for (i = 0; i < 854; i += 2)
                    {
                        putimage(14 + i, 65, buffer2, 0);
                        delay(100);
                        putimage(14 + i, 65, buffer2, 1);
                    }
                    free(buffer2);
                    break;
                }
                /*Se pinta el boton desprecionado*/
                drawButton(&btnAvion3);
                mver();
            }

            else if (limit(xpos, ypos, btnAvion4.x1, btnAvion4.y1, btnAvion4.x2, btnAvion4.y2))
            {
                /*Hacemos el efecto que esta presionado*/
                btnAvion4.effect = PRESS;
                mocultar();
                drawButton(&btnAvion4);
                mver();

                /*Validar que el click se suelte o salga del boton para asi saber si se ejecuta o no la accion*/
                while (mclick() != 0 && minlimit(1, btnAvion4.x1, btnAvion4.y1, btnAvion4.x2, btnAvion4.y2))
                    ;
                mocultar();
                btnAvion4.effect = UNPRESS;
                /*Si la region en que lo solto es en las cordenadas del boton que ejecute la accion*/
                if (minlimit(1, btnAvion4.x1, btnAvion4.y1, btnAvion4.x2, btnAvion4.y2) && registro == 4)
                {
                    /*-----------------------------------------------------funcionalidad-----------------------------------------*/
                    /* BOTON 4------------------------------------------------------*/
                    desaparecerAvion4(poli_4);

                    /*SIMULACION DEL DESPEGUE-------------------------------------------*/
                    setcolor(WHITE);
                    setfillstyle(SOLID_FILL, 15);
                    buffer2 = malloc(imagesize(0, 0, 88, 103));
                    fillpoly(38, avion_despegue);
                    getimage(14, 65, 102, 168, buffer2);
                    delay(5);
                    putimage(14, 65, buffer2, 1);

                    for (i = 0; i < 854; i += 2)
                    {

                        putimage(14 + i, 65, buffer2, 0);
                        delay(100);

                        putimage(14 + i, 65, buffer2, 1);
                    }
                    free(buffer2);
                    break;
                }
                /*Se pinta el boton desprecionado*/
                drawButton(&btnAvion4);
                mver();
            }
            else if (limit(xpos, ypos, btnAvion5.x1, btnAvion5.y1, btnAvion5.x2, btnAvion5.y2))
            {
                /*Hacemos el efecto que esta presionado*/
                btnAvion5.effect = PRESS;
                mocultar();
                drawButton(&btnAvion5);
                mver();

                /*Validar que el click se suelte o salga del boton para asi saber si se ejecuta o no la accion*/
                while (mclick() != 0 && minlimit(1, btnAvion5.x1, btnAvion5.y1, btnAvion5.x2, btnAvion5.y2))
                    ;
                mocultar();
                btnAvion5.effect = UNPRESS;
                /*Si la region en que lo solto es en las cordenadas del boton que ejecute la accion*/
                if (minlimit(1, btnAvion5.x1, btnAvion5.y1, btnAvion5.x2, btnAvion5.y2) && registro == 5)
                {
                    /*-----------------------------------------------------funcionalidad-----------------------------------------*/
                    /* BOTON 5------------------------------------------------------*/
                    desaparecerAvion5(poli_5);

                    /*SIMULACION DEL DESPEGUE-------------------------------------------*/
                    setcolor(WHITE);
                    setfillstyle(SOLID_FILL, 15);
                    buffer2 = malloc(imagesize(0, 0, 88, 103));
                    fillpoly(38, avion_despegue);
                    getimage(14, 65, 102, 168, buffer2);
                    delay(5);
                    putimage(14, 65, buffer2, 1);

                    for (i = 0; i < 854; i += 2)
                    {

                        putimage(14 + i, 65, buffer2, 0);
                        delay(100);

                        putimage(14 + i, 65, buffer2, 1);
                    }
                    free(buffer2);
                    break;
                }
                /*Se pinta el boton desprecionado*/
                drawButton(&btnAvion5);
                mver();
            }
        } while (true);
    }
    return 0;
}

int radar(int xo, int yo, int xf, int yf, int Pais)
{
    /*Se usan los puntos de inicios y los puntos finales*/
    int x, y, rad = 5, ox, oy, dif, xoCambio = 0, yoCambio = 0, xfCambio = 0, yfCambio = 0, Evento = 0, boolllegar = 1;
    float DistMenor = 0;

    /*Explicacion de ambas variables*/
    /*
	x => va a ser la variable la cual se ira sumando o restando para que de esta manera el circulo siga la trayectoria (Este seria la variable independiente)
	y => esta variable sera dependiente de x la cual se obtendra a traves de una ecuacion y de esta manera se obtendira las coordenadas en y de la trayectoria del circulo
	rad => Radio del circulo
	ox => el origen de x, para ubicar el origen en el centro de la pantalla
	oy => lo mismo pero en y
	dif=> esta variable es para calibrar la ubicacion en y del circulo

	variables 'nombre'Cambio
	Estas variables solamente se utilizan para calcular el cambio de trayectoria

	Evento => Variable la cual se usara paraobtener un numero random y que de esa manera ocurra una emergencia de manera aleatoria
	DistMenor => Variable para calcular la trayectoria mas cercana
	boolllegar => variable para indicar que no se siga moviendo una vez que se llego al destino
	*/
    int seg, dd, di = 0; /*Variables de tiempo*/
    int Salir = 1, i;    /*Variables de bucle*/

    void far *buffer1; /*Buffer para guardar la imagen a traves del Rasterop*/

    ox = getmaxx() / 2;
    oy = getmaxy() / 2;

    cleardevice();
    mocultar();
    setfillstyle(SOLID_FILL, 9);
    bar(0, 0, 640, 480);

    muestraBMP(0, 0, "C:\\BMP\\map.bmp"); /*Se carga la imagen*/

    setfillstyle(SOLID_FILL, BLUE);
    setcolor(15);

    setcolor(GREEN);
    line(0, oy, 640, oy);
    line(ox, 0, ox, 480);

    /*Para dibujar los circulos donde se encuentra los punto final*/

    for (i = 0; i < PAISES; i++)
    {
        setcolor(0);
        circle(dato[i][0] + ox, dato[i][1] + oy, 5);
    }
    mver();
    /*Puntos de origen de la pantalla*/

    buffer1 = malloc(imagesize(0, 0, 10, 10)); /*Reserva de memoria*/

    x = xo;                       /*Al momento de iniciar la interaccion x siempre tendra el valor del punto inicial por que directamente se lo asignamos*/
    y = Recta(xo, yo, xf, yf, x); /*y va a tener el valor de la ecuacion de la Recta*/
    dif = (y - yo);               /*Habia un problema que normalmente la funcion retornaba valores que no eran exactos y el avion iniciaba en un lugar que no era
									al momento de obtener la diferencia entre el valor de y que te da la funcion recta y el valor de y inicial se logra calibrar*/

    y = y - dif; /*Al restarle el valor de dif es que se logra calibrar le ubicacion del avion o circulo*/
    outtextxy(10, 480 - 20, "Pulsa Esc para salir");

    /*Se obtiene la imagen de fondo y se guarda en el buffer*/

    getimage(x - rad + ox, y - rad + oy, x + rad + ox, y + rad + oy, buffer1);
    rectangle(x - rad + ox, y - rad + oy, x + rad + ox, y + rad + oy);
    delay(500);

    srand(time(NULL)); /*Para el uso de del random posteriormente*/
    Evento = rand() % 2;

    mver();

    /*Si ocurre un evento para cambiar la trayectoria*/

    if (Evento == 1)
    {
        /*Se obtiene de manera aleatoria el punto especifico donde va a ocurrir el cambio de trayectoria*/
        if (xo < xf)
            xoCambio = (xo + 2) + (rand() % (xf - xo - 3));
        else
            xoCambio = (xf + 2) + (rand() % (xo - xf - 3));

        yoCambio = Recta(xo, yo, xf, yf, xoCambio) - dif;

        /*Se calcula la distancia de cada punto(Paises) y se guarda el mas cercano*/
        for (i = 0; i < PAISES; i++)
        {
            if (i == 0)
            {
                DistMenor = sqrt(pow((xoCambio - dato[i][0]), 2) + pow((yoCambio - dato[i][1]), 2));
                xfCambio = dato[i][0];
                yfCambio = dato[i][1];
                Pais = i;
            }
            else if (DistMenor > sqrt(pow((xoCambio - dato[i][0]), 2) + pow((yoCambio - dato[i][1]), 2)))
            {
                DistMenor = sqrt(pow((xoCambio - dato[i][0]), 2) + pow((yoCambio - dato[i][1]), 2));
                xfCambio = dato[i][0];
                yfCambio = dato[i][1];
                Pais = i;
            }
        }
    }

    while (Salir != 27)
    {

        gettime(&tiempo);
        dd = tiempo.ti_sec;

        if (dd == seg + 30)
        {
            if (seg + 30 == 60) /*Cuando ya es un minuto*/
                seg = 0;
            else /*Cuando ya es medio minuto*/
                seg = 30;
        }

        if ((di != dd) && boolllegar == 1)
        {
            mocultar();

            di = tiempo.ti_sec;

            /*Esto es para borrar el mensaje*/
            setcolor(0);

            /*Para borrar el circulo*/
            putimage(x - rad + ox, y - rad + oy, buffer1, 0);
            free(buffer1);

            /*Esta condicion indica que si x final (xf) es menor a x inicial, (xo) pues x se restara hasta ser igua a xf 
			si no es asi se sumara hasta ser igual xf*/

            if (x != xf)
            {
                if (xf < xo)
                    x--;
                else if (xf > xo)
                    x++;
            }

            y = Recta(xo, yo, xf, yf, x); /*La ecuacion de la recta para obteber y*/
            y = y - dif;                  /*Aqui se vuelve a utilizar esta variable para calibrarlo*/

            buffer1 = malloc(imagesize(0, 0, 10, 10));
            getimage(x - rad + ox, y - rad + oy, x + rad + ox, y + rad + oy, buffer1); /*Se guarda el fondo*/

            /*Se pinta el avion*/
            setcolor(BLUE);
            setfillstyle(SOLID_FILL, BLUE);
            circle(x + ox, y + oy, rad);
            floodfill(x + ox, y + oy, BLUE);

            /*Si aleatoria mente ocurre un evento, (Que el random haya asignado a Evento un valor de 1) y x sea igual al valor de xcambio
			(Que se obtuvo al inicio del bucle)*/

            if (x == xoCambio && Evento == 1)
            {
                /*Se pinta el avion en rojo*/
                mocultar();
                setcolor(RED);
                setfillstyle(SOLID_FILL, RED);
                circle(x + ox, y + oy, rad);
                floodfill(x + ox, y + oy, RED);
                mver();
                /*Se muestra el mensaje de advertencia y se cambian las variables para redireccionar el trayecto*/
                Advertencias(2);
                xo = x;
                yo = y;
                xf = xfCambio;
                yf = yfCambio;
                dif = (Recta(xo, yo, xf, yf, x) - yo);
                xfCambio = yfCambio = xoCambio = yoCambio = 0;
                Evento = 0;
            }

            if (x == xf)
            {
                /*Se pinta el avion en amarillo*/
                mocultar();
                setcolor(YELLOW);
                setfillstyle(SOLID_FILL, YELLOW);
                circle(x + ox, y + oy, rad);
                floodfill(x + ox, y + oy, YELLOW);
                mver();
                /*Se muestra el mensaje de advertencia para activar el protocolo de aterrizaje
				una vez activado se boora el circulo y se tendra que salir del bucle presionando ESC
				*/
                Advertencias(1);
                putimage(x - rad + ox, y - rad + oy, buffer1, 0);
                free(buffer1);
                boolllegar = 0;
                Salir = 27; /*Esto es para que al momento de llegar el avion termine el bucle y se salga*/
            }

            mver();
        }
        /*Codigo para el desarrollo: Eso es mas que nada para salirse del programa a medio proceso*/
        mver();
    }

    /*Esto es para cuando ya termine el bucle y se libere el espacio en memoria*/
    return Pais;
}

int registro(int i, int destino)
{
    char numero[3];
    char mensage[20];
    int total1;
    /**/
    
    setbkcolor(0);
    setfillstyle(SOLID_FILL, 14);
    bar(0, 0, 637, 50);
    Letras();
    /*-----------------------------------------------*/
    setfillstyle(SOLID_FILL, 15); /*barra de indicación*/
    bar(0, 50, 639, 86);
    settextstyle(0, 0, 2);         /*diseño de la letra*/
    outtextxy(5, 60, "AEROLINEA"); /*mensaje*/

    /*-----------------------------------------------*/
    settextstyle(0, 0, 2);           /*diseño de la letra*/
    outtextxy(145, 60, "  N.VUELO"); /*mensaje*/

    /*-----------------------------------------------*/
    settextstyle(0, 0, 2);       /*diseño de la letra*/
    outtextxy(290, 60, " HORA"); /*mensaje*/

    /*-----------------------------------------------*/
    settextstyle(0, 0, 2);         /*diseño de la letra*/
    outtextxy(390, 60, "DESTINO"); /*mensaje*/

    /*-------------------4ta linea division----------------------------*/

    /*-----------------------------------------------*/
    settextstyle(0, 0, 2);         /*diseño de la letra*/
    outtextxy(520, 60, "LLEGADA"); /*mensaje*/

    /*-----------------------------------------------*/
    settextstyle(0, 0, 1); /*diseño de la letra*/
    setcolor(14);
    outtextxy(25, 155 + (40 * i), datos[i].Areolinea);
    setcolor(5);
    outtextxy(165, 155 + (40 * i), datos[i].Numero_de_vuelo);
    setcolor(7);
    outtextxy(305, 155 + (40 * i), datos[i].Hora_de_salida);
    setcolor(10);
    outtextxy(410, 155 + (40 * i), datos[i].Destino);
    setcolor(11);
    numero[0] = datos[i].Hora_de_salida[0];
    numero[1] = datos[i].Hora_de_salida[1];
    numero[2] = '/0';
    total1 = atoi(numero);
    if (destino == 0)
    {
        total1 += 1;
    }
    else if (destino == 1)
    {
        total1 += 2;
    }
    else if (destino == 2)
    {
        total1 += 1;
    }
    else if (destino == 4)
    {
        total1 += 12;
    }
    else if (destino == 5)
    {
        total1 += 5;
    }
    else if (destino == 0)
    {
        total1 += 5;
    }
    if (total1 > 24)
    {
        total1 = total1 - 24;
    }
    sprintf(mensage, "%d : 45", total1);
    outtextxy(520, 155 + (40 * i), mensage);
    return 0;
}
