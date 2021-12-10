#include <stdio.h>
#include <graphics.h>
#include <POLYGON.H>
#include <dos.h>
#include <math.h>
#include <conio.h>
#include <string.h>
#include <16IMAGE.h>
/*#include <mouse.h>*/
#include <GTools.h> /* Libreria personalizada */
#include "Button.h" /* Libreria personalizada */
#include "Input.h"
/*---------------------------------------------Varables gobales,contantes, enum y estructuras-----------------------------*/
#define PAISES 7      /*Define la cantidad de paises*/
#define TAM 6         /* Tamano max de registros */
#define TAMNOMBRES 18 /* Tamano max nombres */
#define NUMVUELO 8    /* Tamano max de numero de vuelo */
#define TAMHORA 7     /* Tamano max de hora */
/*Estructura y variables para el radar*/
int dato[PAISES][2] =
    {
        99 - 320, 153 - 240,  /*EEUU 0*/
        159 - 320, 368 - 240, /*Argentina 1*/
        90 - 320, 201 - 240,  /*Mexico 2*/
        499 - 320, 157 - 240, /*Japon 3*/
        286 - 320, 117 - 240, /*Alemania 4*/
        268 - 320, 115 - 240, /*Inglaterra 5*/
        117 - 320, 227 - 240  /*Nicaragua 6*/
};

enum paises
{
    Estados_unidos = 0,
    Argentina = 1,
    Mexico = 2,
    Japon = 3,
    Alemania = 4,
    Inglaterra = 5,
    Nicaragua = 6
};

struct time tiempo; /*estructura tiempo*/

typedef struct data
{
    char aereolinea[TAMNOMBRES]; /* Arreglo para guardar el nombre de la aereolinea*/
    char numVuelo[NUMVUELO];     /* Guardar el numero de vuelo */
    char Pais[TAMNOMBRES];       /* Lugar de aterrizaje */
    char horaSalida[TAMHORA];    /* Guardar la hora de salida */
} data;

data Datos[TAM];                                          /* Variable de tipo data que manejara la estructura de datos */
button btnCancelar, btnGuardar, btnVolver;                /* Variables de tipo boton para crear botones (Button.h) */
box entradaAereo, entradaVuelo, entradaHora, entradaPais; /* Variables de tipo box para crear cajas de entrada (Button.h) */

unsigned int contador_regis = 0;
struct datos_vuelos
{
    char Areolinea[15];
    char Numero_de_vuelo[15];
    char Hora_de_salida[15];
    char Destino[15];
} datos[5];
/*--------------------------------------------------------------------------------------------------------------------*/

/*-----------------------------------------------Prototipado de funciones----------------------------------------*/
/*Funciones Auxiliares Para la pantalla de inicio*/
void avionPantallaInicio(void);
void edificioAeropuerto(void);
void fondoPantallaIncio(void);
void ventanas(int x, int y);
/*Funciones Auxiliares para el panel de control*/
void fondoPanelDeControl(void);
void ventanasPanelDeControl(void);
void controles(void);
/*Funciones auxiliares de la ventana Ingreso Vuelo*/
void Interfaz(void);
void mostrarBMP(void);
void aereolinea(char *, int, int);
void numVuelo(char *, char *, int, int);
void Hora(char *, int, int);
void guardarDatos(void);
/*Funciones auxiliares para el Despeje*/
void desaparecerAvion1(int poligono[]);
void desaparecerAvion2(int poligono[]);
void desaparecerAvion3(int poligono[]);
void desaparecerAvion4(int poligono[]);
void desaparecerAvion5(int poligono[]);
/*Funciones Auxiliares de la ventana Radar*/
int Recta(int x1, int y1, int x2, int y2, int x);
void Advertencias(int Indicacion);
/*Funciones Auxiliares de la ventana Registro*/
int informacion(void);
void Letras(void);
/*-------------------------------------------------Fin del prototipado-------------------------------------------------------*/

/*Para el inicio de pantalla*/
void avionPantallaInicio()
{
    /*-------------------------------------------------------Declaracion de las partes de los tres aviones-----------------------------------------------------*/
    int cola[] = {207, 185, 189, 152, 199, 150, 233, 173, 207, 185}; /*Cola del avion de pantalla de presentacion*/
    int cola2[] = {506, 411, 530, 382, 541, 382, 528, 413, 506, 411};
    int cola3[] = {574, 433, 598, 398, 609, 400, 600, 435, 574, 433};
    int cuerpo[] = {196, 195, 201, 187, 273, 157, 320, 139, 374, 110, 406, 118, 409, 123, 398, 137, 384, 147, 312, 177, 286, 187, 269, 192, 242, 198, 210, 197, 196, 195};
    int cuerpo2[] = {352, 425, 363, 414, 378, 407, 390, 407, 398, 407, 414, 412, 437, 412, 462, 412, 480, 412, 504, 412, 530, 412, 539, 418, 513, 431, 502, 431, 487, 431, 465, 427, 433, 427, 412, 439, 377, 439, 365, 435, 352, 425};
    int cuerpo3[] = {407, 446, 420, 433, 434, 426, 445, 426, 462, 426, 469, 429, 479, 431, 487, 432, 496, 434, 512, 434, 530, 434, 557, 434, 590, 434, 609, 434, 604, 443, 574, 459, 539, 463, 465, 463, 435, 463, 418, 457, 407, 446};
    int linea[] = {404, 118, 411, 120, 215, 194, 229, 185, 404, 118};
    int linea2[] = {360, 422, 523, 422, 495, 425, 355, 425, 360, 422};
    int linea3[] = {415, 448, 577, 448, 554, 451, 418, 451, 415, 448};
    int aleta[] = {330, 157, 187, 198, 194, 200, 329, 163, 330, 157};
    int ventana[] = {380, 111, 372, 115, 376, 119, 386, 115, 380, 111};
    int ventana2[] = {370, 410, 381, 410, 381, 413, 370, 413, 370, 410};
    int ventana3[] = {426, 435, 427, 431, 435, 431, 434, 436, 426, 435};
    int puntosLinea = 5, puntosCola = 5, puntosCuerpo = 15, puntosVentana = 5;

    /*Mandamos a pintar los tres cuerpo de los aviones*/
    setfillstyle(SOLID_FILL, 15);
    fillpoly(puntosCuerpo, cuerpo);
    fillpoly(puntosCuerpo + 6, cuerpo2);
    fillpoly(puntosCuerpo + 6, cuerpo3);
    setfillstyle(SOLID_FILL, 14);
    fillpoly(puntosCola, cola2);
    fillpoly(puntosLinea, linea2);
    setfillstyle(SOLID_FILL, 4);
    fillpoly(puntosCola, cola3);
    fillpoly(puntosLinea, linea3);
    setfillstyle(SOLID_FILL, 1);
    fillpoly(puntosCola, cola);
    fillpoly(puntosLinea, linea);
    setfillstyle(SOLID_FILL, 15);
    fillpoly(puntosLinea, aleta);
    drawpoly(puntosLinea, aleta);
    /*Se pintan las ventanas de los pilotos y las rayas horizontales del color correspondiente*/
    setfillstyle(SOLID_FILL, 0);
    setlinestyle(0, 0, THICK_WIDTH);
    line(399, 440, 399, 447);
    fillregpoly(399, 447, 4, 30);
    setlinestyle(0, 0, THICK_WIDTH);
    line(460, 464, 460, 471);
    fillregpoly(460, 471, 4, 30);
    setlinestyle(0, 0, THICK_WIDTH);
    line(546, 462, 549, 469);
    fillregpoly(549, 469, 4, 30);
    fillpoly(puntosVentana, ventana);
    fillpoly(puntosVentana, ventana2);
    fillpoly(puntosVentana, ventana3);
}

void fondoPantallaIncio()
{
    /*-----------------------------------------Declaracion de los elementos del paisaje que incluye las nubes y la ciudad de fondo-------------------*/
    int nube[] = {70, 147, 61, 139, 69, 131, 114, 131, 122, 139, 114, 147, 135, 147, 143, 156, 134, 163, 150, 163, 157, 173, 149, 183, 29, 183, 17, 173, 26, 163, 59, 163, 50, 154, 58, 147, 70, 147};
    int nube1_2[] = {14, 148, 46, 148, 48, 153, 44, 156, 15, 156, 10, 152, 14, 148};
    int nube1_3[] = {48, 188, 143, 188, 145, 194, 142, 198, 49, 198, 44, 194, 48, 188};
    int nube2[] = {562, 265, 558, 260, 563, 256, 605, 256, 609, 261, 606, 266, 591, 266, 595, 272, 589, 277, 549, 277, 544, 271, 549, 265, 562, 265};
    int nube2_2[] = {596, 277, 608, 277, 612, 281, 608, 284, 596, 284, 593, 281, 596, 277};
    int nube3[] = {236, 228, 285, 228, 288, 233, 284, 238, 302, 238, 307, 245, 301, 252, 256, 252, 252, 246, 256, 240, 237, 240, 231, 233, 236, 228};
    int nube3_2[] = {225, 249, 239, 249, 242, 253, 239, 257, 225, 257, 222, 253, 225, 249};
    int ciudad[] = {0, 364, 14, 364, 14, 375, 29, 375, 29, 343, 44, 343, 44, 314, 80, 360, 80, 323, 114, 323, 114, 281, 137, 281, 137, 318, 146, 318, 146, 255, 154, 255, 154, 298, 163, 296, 163, 267, 171, 267, 171, 240, 218, 240, 218, 303, 238, 303, 238, 277, 288, 277, 288, 310, 304, 310, 304, 248, 338, 273, 347, 273, 347, 238, 418, 238, 418, 275, 441, 275, 442, 267, 490, 267, 490, 276, 532, 276, 532, 306, 540, 306, 540, 371, 550, 371, 550, 315, 561, 313, 561, 341, 580, 341, 580, 365, 598, 365, 598, 398, 610, 398, 610, 379, 624, 379, 624, 415, 1, 415, 0, 364};
    int puntosNube = 19, puntosNubeT2 = 13, puntosNubeP = 7, puntosCiudad = 56;

    /*Se pinta el cielo en celeste y la carretera en color gris claro*/
    setfillstyle(SOLID_FILL, 11);
    bar(0, 0, 640, 413);
    setfillstyle(SOLID_FILL, 7);
    bar(0, 414, 640, 480);
    /*Se manada a pintar la ciudad de fondo*/
    setfillstyle(SOLID_FILL, 2);
    fillpoly(puntosCiudad, ciudad);
    /*Mandamos a colocar las nubes*/
    setfillstyle(SOLID_FILL, 15);
    fillpoly(puntosNube, nube);
    fillpoly(puntosNubeP, nube1_2);
    fillpoly(puntosNubeP, nube1_3);
    fillpoly(puntosNubeT2, nube2);
    fillpoly(puntosNubeP, nube2_2);
    fillpoly(puntosNubeT2, nube3);
    fillpoly(puntosNubeP, nube3_2);
}

void ventanas(int x, int y)
{
    /*Se pintan las ventanas de color celeste con bordeado en negro en la parte superior y  gris en la parte inferior*/
    setfillstyle(SOLID_FILL, 11);
    bar(x, y, x + 10, y + 10);
    setcolor(0);
    line(x, y, x + 10, y);
    line(x, y, x, y + 10);
    setcolor(8);
    line(x, y + 10, x + 10, y + 10);
    line(x + 10, y, x + 10, y + 10);
}

void edificioAeropuerto()
{
    /*--------------------------------------------------Declaracion de las partes del Aeropuerto------------------------------------------------*/
    int torre[] = {497, 415, 498, 205, 498, 202, 482, 199, 482, 199, 469, 159, 475, 156, 484, 152, 482, 141, 479, 141, 478, 138, 480, 134, 483, 132, 487, 129, 492, 129, 492, 126, 499, 123, 501, 123, 508, 121, 515, 121, 523, 121, 532, 121, 540, 123, 551, 125, 557, 129, 565, 136, 568, 143, 565, 144, 564, 144, 564, 145, 556, 173, 542, 175, 540, 177, 536, 197, 527, 202, 526, 203, 535, 415, 535, 415, 499, 415, 496, 415};
    int piso2[] = {497, 286, 336, 286, 336, 339, 497, 339, 497, 286};
    int pisoBSD[] = {497, 339, 263, 339, 273, 348, 497, 348, 497, 339};          /*Piso1 borde superior derecho - color:cafe*/
    int pisoBSD2[] = {497, 348, 274, 348, 284, 360, 497, 360, 497, 348};         /*Piso1 borde superior derecho2 - color:blanco*/
    int pisoBSD3[] = {497, 360, 286, 360, 289, 369, 497, 369, 497, 360};         /*Piso1 borde superior derecho3  - color:cafe*/
    int pisoBSI[] = {176, 339, 98, 339, 98, 348, 166, 348, 176, 339};            /*piso1 borde superior izquierdo - color: cafe*/
    int pisoBSI2[] = {166, 348, 98, 348, 98, 360, 157, 360, 166, 348};           /*piso1 borde superior izquierdo2 - color: blanco*/
    int pisoBSI3[] = {156, 360, 98, 360, 98, 369, 150, 369, 156, 360};           /*piso1 borde superior izquierdo3 - color: cafe*/
    int pisoPD[] = {497, 369, 291, 369, 304, 394, 307, 415, 497, 415, 497, 369}; /*Pate inferior derecha del piso*/
    int pisoPI[] = {150, 369, 98, 369, 98, 415, 134, 415, 137, 397, 150, 369};   /*Pate inferior izquierda del piso*/
    int base[] = {77, 415, 77, 424, 564, 424, 564, 415, 77, 415};
    int piso2BS[] = {334, 278, 498, 278, 498, 287, 334, 287, 334, 278};
    int marcoPuerta[] = {136, 416, 136, 402, 141, 387, 146, 375, 153, 365, 158, 357, 167, 346, 182, 335, 195, 329, 213, 324, 230, 324, 252, 331, 263, 339, 274, 347, 284, 359, 294, 374, 301, 389, 305, 401, 307, 416, 298, 416, 298, 403, 293, 388, 285, 375, 277, 362, 267, 351, 255, 343, 244, 336, 229, 333, 212, 333, 197, 337, 188, 341, 174, 352, 165, 361, 158, 369, 151, 379, 147, 390, 143, 402, 143, 416, 136, 416};
    int vistaTorre[] = {477, 175, 485, 171, 494, 169, 502, 169, 518, 169, 528, 172, 538, 177, 534, 189, 525, 187, 516, 185, 502, 185, 494, 185, 486, 187, 480, 190, 477, 175};
    int vistaTorre2[] = {484, 144, 496, 138, 508, 134, 522, 134, 534, 134, 546, 138, 556, 143, 560, 146, 556, 162, 550, 160, 543, 159, 534, 155, 518, 152, 503, 153, 488, 151, 484, 144};
    int techoTorre[] = {477, 139, 482, 130, 493, 125, 511, 119, 527, 119, 538, 121, 549, 124, 561, 130, 568, 137, 568, 144, 563, 144, 558, 137, 546, 131, 535, 128, 524, 127, 513, 127, 497, 132, 485, 137, 482, 143, 477, 139};
    int techoMenor[] = {465, 160, 476, 154, 485, 152, 494, 152, 501, 152, 502, 157, 494, 157, 486, 157, 477, 157, 466, 164, 465, 160};
    int sombraTorre[] = {502, 163, 528, 163, 540, 163, 549, 167, 559, 172, 546, 175, 538, 172, 530, 169, 504, 167, 502, 163};
    int sombraTorrebaja[] = {484, 202, 481, 197, 497, 193, 509, 193, 520, 193, 525, 194, 534, 198, 526, 203, 524, 199, 513, 196, 498, 198, 484, 202};
    int ventanaPrincipal[] = {142, 414, 148, 391, 156, 375, 164, 362, 176, 351, 192, 339, 210, 334, 229, 333, 251, 339, 266, 353, 278, 365, 287, 377, 292, 390, 297, 403, 299, 414, 142, 414};
    int i = 0, k = 0, l = 0, m = 0, x = 99, y = 343, x_2 = 342, y_2 = 285, x_3 = 188, y_3 = 331;
    int puntosTorre = 40, puntosPiso = 5, puntosParte = 6, puntosMarcoPuerta = 39, puntosVistaTorre = 15, puntosTechoTorre = 20, puntosTechoMenor = 11, puntosSombraTorreBaja = 12, puntosVentanaPrincipal = 16;

    /*Mandamos a pintar los bordes de los primeros dos pisos*/
    setcolor(0);
    drawpoly(puntosPiso, pisoBSD);
    setfillstyle(SOLID_FILL, 6);
    fillpoly(puntosPiso, base);
    fillpoly(puntosPiso, piso2BS);
    /*Mandamos a colocar las paredes de color blanco*/
    setfillstyle(SOLID_FILL, 15);
    fillpoly(puntosPiso, piso2);
    fillpoly(puntosParte, pisoPD);
    fillpoly(puntosParte, pisoPI);
    /*Mandamos a colocar todas las ventanas*/
    fillpoly(puntosVentanaPrincipal, ventanaPrincipal);
    for (i = 1; i <= 6; i++)
    {
        for (k = 0; k <= 30; k++) /*Para el piso1*/
        {
            ventanas(x, y);
            x = x + 13;
        }
        y = y + 12;
        x = 99;
        if (i <= 4)
        {
            for (l = 0; l < 11; l++) /*Segundo piso*/
            {
                ventanas(x_2, y_2);
                x_2 = x_2 + 14;
            }
            y_2 = y_2 + 14;
            x_2 = 342;
        }
        if (i == 1)
        {
            for (m = 0; m <= 4; m++) /*parte del arco de la ventana principal*/
            {
                ventanas(x_3, y_3);
                x_3 = x_3 + 13;
            }
            y_3 = y_3 + 12;
            x_3 = 337;
        }
    }
    /*Mandamos a colocar el borde cafe de todos los pisos junto con el marco de la puerta*/
    setfillstyle(SOLID_FILL, 15);
    setcolor(0);
    fillpoly(puntosPiso, pisoBSD2);
    fillpoly(puntosPiso, pisoBSI2);
    setfillstyle(SOLID_FILL, 6);
    fillpoly(puntosMarcoPuerta, marcoPuerta);
    fillpoly(puntosPiso, pisoBSD);
    fillpoly(puntosPiso, pisoBSD3);
    fillpoly(puntosPiso, pisoBSI);
    fillpoly(puntosPiso, pisoBSI3);
    /*Mandamos a dibujar y pintar la torre con toda sus devidas partes*/
    setfillstyle(SOLID_FILL, 15);
    fillpoly(puntosTorre, torre);
    setfillstyle(SOLID_FILL, 11);
    fillpoly(puntosVistaTorre, vistaTorre);
    fillpoly(puntosVistaTorre + 1, vistaTorre2);
    setfillstyle(SOLID_FILL, 0);
    drawpoly(puntosVistaTorre, vistaTorre);
    drawpoly(puntosVistaTorre + 1, vistaTorre2);
    drawpoly(puntosTechoTorre, techoTorre);
    drawpoly(puntosTechoMenor, techoMenor);
    line(493, 170, 496, 184);
    line(520, 170, 518, 184);
    line(508, 135, 511, 152);
    line(544, 138, 537, 155);
    setfillstyle(SOLID_FILL, 6);
    fillpoly(puntosTechoTorre, techoTorre);
    fillpoly(puntosTechoMenor, techoMenor);
    bar3d(515, 197, 521, 415, 3, 1);
    setfillstyle(SOLID_FILL, 7);
    fillpoly(puntosTechoTorre / 2, sombraTorre);
    fillpoly(puntosSombraTorreBaja, sombraTorrebaja);
}

/*Para el panel de control*/
void controles()
{
    int sombraAvionC[] = {
        142, 207, 159, 207, 159, 195, 158, 190, 158, 182, 164, 182, 164, 190, 163, 194, 163, 207, 223, 207, 230, 212, 230, 201, 228, 198, 228, 193, 234, 193, 233, 198, 231, 202, 232, 212, 252, 213, 264, 213, 264, 217, 272, 217, 283, 219, 290, 221, 330, 221, 334, 217, 341, 214, 339, 220, 343, 223, 336, 226, 329, 225, 320, 227, 286, 227, 285, 233, 300, 236, 311, 236, 314, 239, 321, 239, 322, 243, 371, 243, 386, 226, 394, 227, 386, 240, 396, 242, 376, 249, 342, 249, 337, 253, 330, 253, 328, 248, 316, 249, 313, 253, 310, 249, 302, 249, 302, 244, 237, 233, 237, 250, 231, 251, 231, 235, 184, 235, 172, 240, 162, 243, 162, 253, 170, 253, 170, 257, 186, 257, 198, 262, 206, 262, 213, 264, 223, 264, 223, 267, 232, 267, 242, 267, 242, 279, 258, 273, 314, 270, 309, 260, 316, 260, 331, 268, 362, 267, 391, 262, 432, 263, 462, 221, 470, 221, 458, 260, 467, 265, 495, 266, 495, 267, 468, 267, 416, 284, 498, 284, 498, 287, 416, 287, 384, 288, 385, 293, 391, 293, 391, 297, 387, 297, 385, 302, 382, 299, 378, 304, 360, 306, 355, 300, 358, 291, 326, 294, 259, 301, 256, 306, 256, 311, 253, 311, 252, 301, 227, 294, 235, 283, 223, 285, 216, 281, 210, 278, 204, 280, 203, 294, 200, 295, 202, 280, 192, 273, 191, 297, 188, 297, 190, 273, 180, 273, 175, 270, 168, 271, 163, 265, 163, 291, 159, 291, 159, 267, 152, 271, 156, 278, 152, 290, 142, 291, 142, 207};
    int sombraAvionI[] = {
        0, 211, 66, 211, 66, 167, 64, 163, 64, 156, 61, 149, 61, 139, 66, 135, 63, 129, 66, 128, 69, 127, 69, 123, 75, 123, 75, 126, 79, 126, 77, 131, 82, 130, 81, 135, 85, 139, 85, 147, 82, 155, 82, 164, 80, 167, 80, 210, 132, 209, 134, 270, 129, 271, 129, 286, 125, 279, 119, 291, 118, 271, 0, 271};

    int ingresoDeVuelo[] = {9, 386, 95, 359, 113, 423, 25, 452, 9, 386};
    int despeje[] = {170, 355, 268, 355, 268, 424, 171, 424, 170, 355};
    int radar[] = {344, 342, 467, 342, 467, 424, 344, 424, 344, 342};
    int registro[] = {541, 347, 613, 369, 590, 446, 516, 421, 541, 347};
    int sombraIngresoDeVuelo[] = {8, 389, 8, 419, 26, 452, 8, 389};
    int ingresoDeVueloP1[] = {20, 399, 48, 390, 61, 432, 35, 440, 20, 399};
    int ingresoDeVueloP2[] = {63, 386, 88, 377, 90, 384, 66, 393, 63, 386};
    int ingresoDeVueloP3[] = {67, 401, 72, 397, 76, 403, 71, 406, 67, 401};
    int ingresoDeVueloP4[] = {84, 394, 88, 391, 92, 397, 87, 400, 84, 394};
    int ingresoDeVueloP5[] = {72, 414, 77, 411, 80, 417, 74, 420, 72, 414};
    int ingresoDeVueloP6[] = {88, 407, 93, 405, 96, 411, 91, 414, 88, 407};
    int registroP1[] = {540, 367, 546, 364, 549, 371, 543, 373, 540, 367};
    int registroP2[] = {555, 367, 594, 377, 589, 386, 552, 375, 555, 367};
    int registroP3[] = {596, 383, 603, 380, 604, 387, 598, 390, 596, 383};
    int registroP4[] = {540, 384, 562, 391, 548, 430, 524, 420, 540, 384};
    int registroP5[] = {569, 393, 596, 402, 581, 442, 554, 430, 569, 393};
    int registroPA1[] = {447, 392, 439, 392, 448, 388, 448, 384, 451, 381, 454, 384, 454, 388, 461, 392, 454, 392, 454, 396, 457, 400, 445, 400, 449, 396, 449, 392, 447, 392};
    int sombraRegistro[] = {614, 372, 614, 419, 591, 446, 614, 372};
    int puntosSombraAviones = 134, puntosTablas = 5, puntosPiezas = 5, i = 0, puntosPiezasAvion = 15;
    /*Mandamos a poner la vista de las ventanas*/
    setcolor(0);
    setfillstyle(SOLID_FILL, 0);
    fillpoly(puntosSombraAviones, sombraAvionC);
    fillpoly(puntosSombraAviones - 102, sombraAvionI);
    /*Mandamos a poner la puertas del garaje de los sviones*/
    /*setfillstyle(SOLID_FILL, 15);
    fillregpoly(153,259,5,4);*/
    setfillstyle(SOLID_FILL, 0);
    fillpoly(puntosTablas - 1, sombraIngresoDeVuelo);
    fillpoly(puntosTablas - 1, sombraRegistro);
    setfillstyle(SOLID_FILL, 7); /*Se coloca el molde de cada tabla*/
    fillpoly(puntosTablas, ingresoDeVuelo);
    fillpoly(puntosTablas, despeje);
    fillpoly(puntosTablas, radar);
    fillpoly(puntosTablas, registro);
    setfillstyle(SOLID_FILL, 0); /*Mandamos a colocar las piezas de cada tabla*/
    fillpoly(puntosPiezas, ingresoDeVueloP1);
    fillpoly(puntosPiezas, registroP4);
    fillpoly(puntosPiezas, registroP5);
    /*Solo dibujamos las piezas del refistro e ingreso de vuelo*/
    drawpoly(puntosPiezas, ingresoDeVueloP2);
    drawpoly(puntosPiezas, ingresoDeVueloP3);
    drawpoly(puntosPiezas, ingresoDeVueloP4);
    drawpoly(puntosPiezas, ingresoDeVueloP5);
    drawpoly(puntosPiezas, ingresoDeVueloP6);
    drawpoly(puntosPiezas, registroP1);
    drawpoly(puntosPiezas, registroP2);
    drawpoly(puntosPiezas, registroP3);
    /*Ponemos las piezas de la tabla del radar*/
    setfillstyle(SOLID_FILL, 0);
    circle(406, 383, 32);
    floodfill(406, 383, BLACK);
    setfillstyle(SOLID_FILL, 15);
    fillpoly(puntosPiezasAvion, registroPA1);
    setcolor(2);
    for (i = 0; i < 30; i = i + 5)
        circle(406, 383, 30 - i);
    /*Esto es parte de la tala del despeje*/
    setfillstyle(SOLID_FILL, 0);
    bar(183, 368, 257, 386);
    setfillstyle(SOLID_FILL, 2);
    circle(192, 405, 8);
    circle(241, 405, 8);
    setcolor(0);
    setfillstyle(SOLID_FILL, 0);
    fillregpoly(192, 405, 6, 3); /*triangulos*/
    fillregpoly(241, 405, 6, 3);
    /*Comenzamos a poner etiquetas de colores en el tablero del radar para representar los colores del avion*/
    setfillstyle(SOLID_FILL, 14); /*Amarillo*/
    bar(352, 356, 359, 363);
    setfillstyle(SOLID_FILL, 1); /*Azul*/
    bar(352, 370, 359, 377);
    setfillstyle(SOLID_FILL, 4); /*rojo*/
    bar(352, 384, 359, 391);
    setfillstyle(SOLID_FILL, 11); /*celeste*/
    bar(352, 398, 359, 405);
    setfillstyle(SOLID_FILL, 10); /*verde claro*/
    bar(352, 412, 359, 419);
    /*Lineas de la pista de la tabla del despeje*/
    setcolor(15);
    for (i = 1; i <= 17; i = i + 2)
        line(211 + i, 387, 211 + i, 382);
    for (i = 1; i <= 17; i = i + 2)
        line(211 + i, 368, 211 + i, 371);
    setcolor(14); /*Amarillo*/
    line(184, 373, 210, 373);
    line(210, 373, 210, 368);
    line(183, 381, 210, 381);
    line(210, 381, 210, 387);
    line(230, 368, 230, 373);
    line(230, 373, 258, 373);
    line(230, 387, 230, 380);
    line(230, 380, 258, 380);
    /*Lineas de simulacion de texto de el ingreso de vuelos*/
    setcolor(13); /*Mangenta13 - RojoClaro12 - grisclaro7 - cian 11*/
    line(24, 403, 34, 399);
    line(32, 406, 48, 400);
    setcolor(7); /*grisclaro*/
    line(25, 414, 35, 410);
    line(33, 417, 49, 411);
    setcolor(11);
    line(30, 427, 40, 423);
    line(36, 430, 52, 424);
    /*Lineas de simulacion de texto de la parte de registro*/
    setcolor(14); /*Amarillo*/
    line(540, 390, 549, 393);
    line(542, 397, 555, 401);
    setcolor(1); /*Azul*/
    line(535, 399, 546, 403);
    line(537, 406, 552, 411);
    setcolor(5); /*Mangenta*/
    line(531, 413, 544, 417);
    line(533, 420, 547, 425);
    setcolor(7); /*Gris Claro*/
    line(571, 398, 582, 402);
    line(572, 404, 588, 410);
    setcolor(10); /*Verde Claro*/
    line(568, 412, 579, 416);
    line(567, 418, 585, 424);
    setcolor(11); /*Cian*/
    line(562, 425, 574, 429);
    line(562, 431, 579, 437);
}

void fondoPanelDeControl()
{
    /*---------------------Declaracion de los elemetos del fondo del panel---------------*/
    int luzRI[] = {84, 35, 115, 26, 120, 34, 117, 43, 87, 51, 91, 41, 84, 35};
    int luzAI[] = {46, 48, 85, 34, 90, 39, 92, 45, 88, 50, 46, 64, 50, 58, 50, 53, 46, 48};
    int luzAD[] = {563, 38, 558, 45, 561, 51, 564, 55, 604, 67, 600, 62, 598, 56, 602, 51, 563, 38};
    int luzRD[] = {535, 30, 529, 37, 531, 41, 534, 46, 561, 53, 558, 48, 558, 43, 563, 39, 535, 30};
    int luzBC[] = {295, 20, 362, 20, 366, 26, 362, 31, 296, 31, 292, 26, 295, 20};
    int luzBC2[] = {318, 25, 343, 25, 343, 36, 318, 36, 318, 25};
    int puntosLuces = 10;
    /*Pintamos el fondo de color gris claro y blanco*/
    setlinestyle(0, 0, 1);
    setfillstyle(SOLID_FILL, 7);
    bar(0, 0, 640, 451);
    setfillstyle(SOLID_FILL, 15);
    bar(0, 451, 640, 480);
    /*Mandamos a colocar las luces*/
    setfillstyle(SOLID_FILL, 4);
    setcolor(0);
    fillpoly(puntosLuces - 3, luzRI);
    fillpoly(puntosLuces - 1, luzRD);
    setfillstyle(SOLID_FILL, 14);
    fillpoly(puntosLuces - 1, luzAI);
    fillpoly(puntosLuces - 1, luzAD);
    setfillstyle(SOLID_FILL, 15);
    setcolor(8);
    fillpoly(puntosLuces - 3, luzBC);
    fillpoly(puntosLuces - 5, luzBC2);
}

void ventanasPanelDeControl()
{ /*Declaramos las partes de la ventanas y como la lampar principal*/
    int lampara[] = {235, 36, 416, 36, 416, 58, 235, 58, 235, 36};
    int ventanaSI[] = {0, 100, 132, 58, 132, 207, 0, 234, 0, 100};
    int ventanaII[] = {0, 234, 132, 207, 132, 330, 0, 370, 0, 234};
    int ventanaSD[] = {506, 57, 640, 100, 640, 247, 506, 202, 506, 57};
    int ventanaID[] = {506, 202, 640, 247, 640, 372, 506, 328, 506, 202};
    int ventanaSC[] = {140, 55, 498, 55, 498, 205, 140, 205, 140, 55};
    int ventanaIC[] = {140, 205, 498, 205, 498, 325, 140, 325, 140, 205};
    int control[] = {0, 369, 139, 326, 504, 326, 640, 371, 640, 480, 588, 480, 508, 453, 144, 453, 60, 480, 0, 480, 0, 371};
    int contornoControl[] = {60, 479, 143, 452, 507, 452, 586, 480, 576, 480, 508, 459, 144, 459, 72, 480, 60, 479};

    int puntosLampara = 5, puntosVentana = 5, puntosControl = 11;
    /*-------Mandamos a colocar las tres ventanas---------*/
    setfillstyle(SOLID_FILL, 11);
    fillpoly(puntosVentana, ventanaSI);
    fillpoly(puntosVentana, ventanaSD);
    fillpoly(puntosVentana, ventanaSC);
    setfillstyle(SOLID_FILL, 2);
    fillpoly(puntosVentana, ventanaII);
    fillpoly(puntosVentana, ventanaID);
    fillpoly(puntosVentana, ventanaIC);
    setfillstyle(SOLID_FILL, 8);
    fillpoly(puntosControl, control);
    setfillstyle(SOLID_FILL, 0);
    fillpoly(puntosControl - 2, contornoControl);
    setfillstyle(SOLID_FILL, 15);
    fillpoly(puntosLampara, lampara);
}

/*Para el ingreso del vuelo*/
void Interfaz(void)
{
    /* Barra de registro */
    effect3d(0, 0, 639, 35, 2, DEPRESSED);
    setfillstyle(SOLID_FILL, 3);
    /*back3D(6, 6, getmaxx() - 6, 41, 8, 15);*/
    bar(2, 2, 637, 33);

    /* Tipo de fuente y efecto 3D */
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(15);
    Text3D(255, 11, 2, 8, 15, "Registro");

    /*setcolor(0);
    outtextxy(25, 95, "Pulse ENTER");
    outtextxy(50, 104, "al");
    outtextxy(9, 112, "ingresar los datos");*/

    /* Se dibuja la barra donde se mostraran las cajas de entrada */
    effect3d(0, 36, 119, 425, 2, DEPRESSED);
    setfillstyle(SOLID_FILL, 7);
    bar(2, 38, 117, 423);

    /* Opcion aereolinea */
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    Text3D(3, 80, 2, 8, 15, "> Aereolinea:");
    /* Opcion vuelo */
    Text3D(3, 150, 2, 8, 15, "> Num. vuelo:");
    /* Opcion hora */
    Text3D(3, 220, 2, 8, 15, "> Hora salida:");
    /* Opcion lugar */
    Text3D(3, 290, 2, 8, 15, "> Destino:");

    settextstyle(SMALL_FONT, HORIZ_DIR, 4);
    /* Dibujo barra de entrada de aereolinea */
    inputBox(&entradaAereo, 5, 95);

    /* Barra de entrada numero de vuelo */
    inputBox(&entradaVuelo, 5, 165);

    /* Barra de entrada hora */
    inputBox(&entradaHora, 5, 235);

    /* Barra de lugar de destino */
    inputBox(&entradaPais, 5, 305);
    setcolor(0);
    outtextxy(30, 306, "Seleccione");
    outtextxy(50, 314, "en");
    outtextxy(35, 322, "croquis");

    /* Se dibuja la barra donde se mostraran los botones de Cancelar y Guardar */
    effect3d(0, 426, 639, 479, 2, DEPRESSED);
    setfillstyle(SOLID_FILL, 7);
    bar(2, 428, 637, 477);

    /* Se dibuja el boton Cancelar */
    newButton2(&btnCancelar, 400, 438, "Cancelar");

    /* Se dibuja el boton Guardar */
    newButton2(&btnGuardar, 525, 438, "Guardar");

    /* Se muestra la imagen bmp en la interfaz */
    mostrarBMP();

    /* Se muestra el raton */
    mver();
}

void mostrarBMP(void)
{
    /* Se llama la funcion para mostrar imagen bmp del mapa (16Image.h),
    * y se indican las coordenadas en donde se empezara a mostrar la imagen
    * y el nombre de la imagen localizada en el disco C */
    muestraBMP(120, 36, "C:\\BMP\\mini.bmp");

    /* Se dibuja un circulo correspondiente al color de EEUU
    * para indicarle al usuario cual es cual y se dibujan barras dentro del los paises
    * para determinar si se da click sobre esa barra el lugar destino sera el pais que corresponda */
    settextstyle(SMALL_FONT, HORIZ_DIR, 4);

    /* Dibujo EEUU */
    setfillstyle(SOLID_FILL, MAGENTA);
    /* Parte Alaska */
    bar(164 + 2, 94 + 2, 186 - 1, 110);
    bar(155, 108, 162, 119 - 3);
    /* Parte de EEUU baja */
    bar(183 + 2, 138 + 2, 222, 148);
    bar(179 + 2, 149, 230, 176);
    bar(231, 153, 239, 170);
    bar(174, 153, 178, 170);
    setcolor(MAGENTA);
    circle(140, 409, 5);
    setcolor(WHITE);
    outtextxy(155, 403, "EEUU");

    /* Dibujo Inglaterra */
    setfillstyle(SOLID_FILL, LIGHTRED);
    bar(334, 122, 342, 135);
    setcolor(LIGHTRED);
    circle(195, 409, 5);
    setcolor(WHITE);
    outtextxy(205, 403, "Inglaterra");

    /* Dibujo Mexico */
    setfillstyle(SOLID_FILL, GREEN);
    bar(176 + 2, 182, 183, 195);
    bar(185, 180, 194, 188);
    bar(188, 189, 201, 208);
    bar(201, 209, 211, 218);
    setcolor(LIGHTGREEN);
    circle(275, 409, 5);
    setcolor(WHITE);
    outtextxy(285, 403, "Mexico");

    /* Dibujo Argentina */
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(245, 308, 257 - 2, 339);
    bar(247, 340, 255, 370);
    setcolor(LIGHTGRAY);
    circle(335, 409, 5);
    setcolor(WHITE);
    outtextxy(345, 403, "Argentina");

    /* Dibujo Alemania */
    setfillstyle(SOLID_FILL, YELLOW);
    bar(350, 129, 362 - 2, 144);
    setcolor(YELLOW);
    circle(410, 409, 5);
    setcolor(WHITE);
    outtextxy(420, 403, "Alemania");

    /* Dibujo Japon */
    setfillstyle(SOLID_FILL, LIGHTCYAN);
    bar(523 + 3, 151, 531 - 2, 172);
    setcolor(CYAN);
    circle(480, 409, 5);
    setcolor(WHITE);
    outtextxy(490, 403, "Japon");
}

void aereolinea(char tempString[], int x, int y)
{
    /* Se piden los datos con la funcion getNames de la libreria Input.h */
    mocultar();
    obtenerNombre(tempString, x + 15, y + 13);
    mver();
}

void numVuelo(char tempString[], char tempNumFlight[], int x, int y)
{
    /* Se piden los datos con la funcion getFlight de la lib Input.h */
    mocultar();
    obtenerNumVuelo(tempNumFlight, tempString, x + 25, y + 13);
    mver();
}

void Hora(char tempHour[], int x, int y)
{
    /* Se piden los datos con la funcion getHour de la lib Input.h */
    mocultar();
    obtenerHora(tempHour, x + 20, y + 12);
    mver();
}

void guardarDatos(void)
{
    int i;
    /* Se abre el archivo de texto en modo a (solo para escribir)*/
    FILE *file;

    file = fopen("C:\\AIRPORT\\REGISTRO.txt", "a");

    if (file)
    {
        /*fprintf(file,"%s  %s  %s  %s\n","Aereolinea", "Numero de vuelo", "Hora de salida", "Destino");*/

        for (i = 0; i <= contador_regis; i++)
        {
            fprintf(file, "%s  %s  %s  %s\n", Datos[i].aereolinea, Datos[i].numVuelo, Datos[i].horaSalida, Datos[i].Pais);
        }

        fclose(file);
    }
}

/*Para el despeje*/
void desaparecerAvion1(int poligono[])
{
    /*Si ya es el segundo avion que va a salir pues que se oculte el primero*/
    /*esta parte pinta de nuevo el poligono de abajo del avion, para poder simular que desaparecio-------------------------------*/
    setcolor(YELLOW);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    setfillstyle(SOLID_FILL, 8);
    fillpoly(9, poligono);

    /*pasarela repintar*/
    setcolor(10);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    setfillstyle(SOLID_FILL, 9);
    bar(72, 288, 180, 298);
    bar(137, 298, 120, 400);
}

void desaparecerAvion2(int poligono[])
{

    setcolor(YELLOW); /*pinta el poligono*/
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    setfillstyle(SOLID_FILL, 8);
    fillpoly(9, poligono);

    /*pasarela repintar*/
    setcolor(10);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    setfillstyle(SOLID_FILL, 9);
    bar(72, 288, 180, 298);
    bar(137, 298, 120, 400);
}

void desaparecerAvion3(int poligono[])
{
    setcolor(YELLOW);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    setfillstyle(SOLID_FILL, 8);
    fillpoly(9, poligono);

    /*pasarela repintar*/
    setcolor(10);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    setfillstyle(SOLID_FILL, 9);
    bar(349, 289, 454, 300);
    bar(394, 296, 410, 400);
}

void desaparecerAvion4(int poligono[])
{
    setcolor(YELLOW);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    setfillstyle(SOLID_FILL, 8);
    fillpoly(9, poligono);

    /*pasarela repintar*/
    setcolor(10);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    setfillstyle(SOLID_FILL, 9);
    bar(349, 289, 454, 300);
    bar(394, 296, 410, 400);
}

void desaparecerAvion5(int poligono[])
{
    setcolor(YELLOW);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    setfillstyle(SOLID_FILL, 8);
    fillpoly(9, poligono);

    /*pasarela repintar*/
    setcolor(10);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    setfillstyle(SOLID_FILL, 9);
    bar(590, 283, 640, 294);
    bar(625, 284, 640, 450);
}

/*Funciones Auxiliares de la ventana del Radar*/
int Recta(int x1, int y1, int x2, int y2, int x)
{
    long int y;
    long int a = x * (y2 - y1);
    long int b = x2 * (y2 + y1);
    long int c = (x1 * y1);
    long int d = (x2 - x1);

    y = (a - b + c) / d;

    return y; /*Al momento de retornar y este ya tiene un valor que si puede ser contenido en una variable del tipo int*/
}

void Advertencias(int Indicacion)
{
    /*En esta funcion solamente es ejecucion de codigo para mostrar las advetencias*/

    int Event;
    char Emergencia[50];                                /*Cadena para guardar el mensaje a mostrar*/
    int Advertencia[] = {410, 390, 550, 390, 480, 330}; /*Puntos para dibujar el triangulo de advertencia*/

    void far *buffer; /*Variable para el rasterop*/

    srand(time(NULL));  /*Para el uso de del random posteriormente*/
    Event = rand() % 3; /*Esta variable es unicamente para mostrar la emergencia que ocurrio en pantalla y la que se mostrara*/

    if (Event == 0)
        strcpy(Emergencia, "Se detecto una tormenta electrica.");
    else if (Event == 1)
        strcpy(Emergencia, "Se encontraron fallas mecanicas.");
    else if (Event == 2)
        strcpy(Emergencia, "Se detecto altas turbulencias.");

    if (Indicacion == 1)
    {
        mocultar();
        buffer = malloc(imagesize(getmaxx() / 2, getmaxy() / 2, getmaxx(), getmaxy()));
        getimage(getmaxx() / 2, getmaxy() / 2, getmaxx(), getmaxy(), buffer);

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

        /*Se dibuja el boton para activar el protocolo de aterrizaje*/

        setfillstyle(SOLID_FILL, GREEN);
        setcolor(GREEN);

        bar((getmaxx() / 2) + 25, getmaxy() - 70, getmaxx() - 25, getmaxy() - 40);

        setfillstyle(SOLID_FILL, BLACK);

        bar((getmaxx() / 2) + 30, getmaxy() - 65, getmaxx() - 30, getmaxy() - 45);
        setcolor(WHITE);
        outtextxy(((getmaxx() / 2) + 30 + getmaxx() - 30) / 2, getmaxy() - 55, "Activar protocolo de aterrizaje");

        setfillstyle(SOLID_FILL, YELLOW);
        fillpoly(3, Advertencia);
        settextstyle(0, 0, 5);
        setcolor(BLACK);
        outtextxy(485, 370, "!");
        settextstyle(0, 0, 1);

        /*Y se detiene el programa hasta que se le de click al boton*/
        while ((!minlimit(1, (getmaxx() / 2) + 35, getmaxy() - 65, getmaxx() - 35, getmaxy() - 45)) || !mclick())
        {
            mver();
            if (kbhit())
                getch();
        }
        /*Se hace el efecto de que se presiono el boton*/

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
        putimage(getmaxx() / 2, getmaxy() / 2, buffer, 0);
        free(buffer);
        mver();
    }
    else if (Indicacion == 2)
    {
        mocultar();
        buffer = malloc(imagesize(getmaxx() / 2, getmaxy() / 2, getmaxx(), getmaxy()));
        getimage(getmaxx() / 2, getmaxy() / 2, getmaxx(), getmaxy(), buffer);

        /*Este es en el caso que ocurra una emergencia y tenga que cambiar de direccion a una ruta cercana*/

        setfillstyle(SOLID_FILL, GREEN);
        setcolor(GREEN);
        settextstyle(0, 0, 1);

        bar(getmaxx() / 2, getmaxy() / 2, getmaxx(), getmaxy());
        setfillstyle(SOLID_FILL, BLACK);
        bar((getmaxx() / 2) + 10, (getmaxy() / 2) + 10, getmaxx() - 10, getmaxy() - 10);
        setcolor(WHITE);
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        outtextxy(((getmaxx() / 2) + 10 + getmaxx() - 10) / 2, (getmaxy() / 2) + 30, Emergencia); /*El mensaje de emergencia se determino dese antes*/
        outtextxy(((getmaxx() / 2) + 10 + getmaxx() - 10) / 2, (getmaxy() / 2) + 45, "Pulse el boton para cambiar la");
        outtextxy(((getmaxx() / 2) + 10 + getmaxx() - 10) / 2, (getmaxy() / 2) + 60, "trayecctoria a una zona cercana.");

        /*Se dibuja el boton para activar el protocolo de aterrizaje*/
        setfillstyle(SOLID_FILL, GREEN);
        setcolor(GREEN);

        bar((getmaxx() / 2) + 30, getmaxy() - 70, getmaxx() - 30, getmaxy() - 40);

        setfillstyle(SOLID_FILL, BLACK);

        bar((getmaxx() / 2) + 35, getmaxy() - 65, getmaxx() - 35, getmaxy() - 45);
        setcolor(WHITE);
        outtextxy(((getmaxx() / 2) + 35 + getmaxx() - 35) / 2, getmaxy() - 55, "Cambiar ruta de aterrizaje");

        setfillstyle(SOLID_FILL, RED);
        fillpoly(3, Advertencia);
        settextstyle(0, 0, 5);
        setcolor(BLACK);
        outtextxy(485, 370, "!");
        settextstyle(0, 0, 1);

        /*Y se detiene el programa hasta que se le de click al boton*/
        while ((!minlimit(1, (getmaxx() / 2) + 35, getmaxy() - 65, getmaxx() - 35, getmaxy() - 45)) || !mclick())
        {
            mver();
            if (kbhit())
                getch();
        }
        /*Se hace el efecto de que se presiono el boton*/
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
        putimage(getmaxx() / 2, getmaxy() / 2, buffer, 0);
        free(buffer);
        mver();
    }
}

/*Funciones Auxiliares de la ventana de Registro*/
void Letras()
{
    settextstyle(0, 0, 3);
    Text3D(200, 10, 5, 2, 10, "REGISTRO");
}

int informacion(void)
{
    FILE *fichero;
    char caracter;
    char mensage[30];
    int contador = 0, bool1 = 0, i = 0, ii = 0;
    fichero = fopen("C:\\Airport\\REGISTRO.txt", "r");

    while (feof(fichero) == 0)
    {

        caracter = fgetc(fichero);
        if (caracter >= 65 && caracter <= 90 && caracter != '\n' || caracter >= 97 && caracter <= 122 && caracter != '\n' || caracter >= 48 && caracter <= 57 && caracter != '\n' || caracter == 58)
        {
            mensage[ii] = caracter;

            bool1 = 0;
            ii++;
        }
        if (caracter == 32 && bool1 == 0)
        {
            mensage[ii] = '\0';
            bool1++;
            if (contador == 0)
            {
                strcpy(datos[i].Areolinea, mensage);

                strcpy(mensage, " ");
                ii = 0;
            }
            else if (contador == 1)
            {
                strcpy(datos[i].Numero_de_vuelo, mensage);
                strcpy(mensage, " ");
                ii = 0;
            }
            else if (contador == 2)
            {
                strcpy(datos[i].Hora_de_salida, mensage);
                strcpy(mensage, " ");
                ii = 0;
            }
            contador++;
        }

        if (caracter == '\n')
        {
            mensage[ii] = '\0';
            strcpy(datos[i].Destino, mensage);
            strcpy(mensage, " ");
            i++;
            contador = 0;
            ii = 0;
        }
    }

    fclose(fichero);
    return i;
}
