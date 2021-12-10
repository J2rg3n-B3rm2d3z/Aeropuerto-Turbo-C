#include <graphics.h>
#include <stdio.h>
#include <dos.h>
#include <math.h>
#include <conio.h>
#include <mouse.h>
#include <16image.h>

#define PAISES 7 /*Define la cantidad de paises*/
#define OX 320
#define OY 240
#define RAD 5
/*En este arreglo se muestran los puntos que representan a cada pais*/

/*En este caso se le resto 320 y 240 para que de esa manera estos se puedan utilizar posteriormente
en la pantalla en la cual el punto de origen se ubicara en el centro del todo siendo 0 la mitad de la pantalla, 
lo numeros negativos la parte izquierda o arriba del centro la pantalla y los numeros positivos la parte derecha o por debajo del centro de la pantalla */

int dato[PAISES][2] =
	{
		99 - 320, 153 - 240,  /*EEUU 0*/
		159 - 320, 368 - 240, /*Argentina 1*/
		90 - 320, 201 - 240,  /*Mexico 2*/
		499 - 320, 157 - 240, /*Japon 3*/
		286 - 320, 117 - 240, /*Alemania 4*/
		268 - 320, 115 - 240, /*Inglaterra 5*/
		117 - 320, 227 - 240  /*Nicaragua 6*/

		/*Paises extras*/

		/*403-320,202-240,India 7*/
		/*178-320,291-240,Brazil 8*/
		/*499-320,337-240,Australia 9*/
		/*262-320,151-240,Espana 10*/
		/*272-320,131-240,Francia 11*/
		/*437-320,163-240,China 12*/
		/*401-320,89-240,Rusia 13*/
		/*107-320,97-240,Canada 14*/

};

/*Para facilitar a el dato de los paises*/

enum paises
{

	Estados_unidos = 0,
	Argentina = 1,
	Mexico = 2,
	Japon = 3,
	Alemania = 4,
	Inglaterra = 5,
	Nicaragua = 6

	/*Paises extras*/

	/*
	India=7,
	Brazil=8,
	Australia=9,
	Espana=10,
	Francia=11,
	China=12,
	Rusia=13,
	Canada=14
	*/
};

struct time tiempo; /*estructura tiempo*/

/*funciones utilizadas*/

void movimiento(int *xo, int *yo, int *xf, int *yf, int *x, int *y, int *dif, int *xoCambio, int *yoCambio, int *xfCambio, int *yfCambio, int *Evento, int *boolllegar, float *DistMenor, int *seg, int *dd, int *hora, int *di, void **Bufer) /*Se usan los puntos de inicios y los puntos finales*/

int Recta(int x1, int y1, int x2, int y2, int x); /*Funcion para obtener y en una funcion dada y de esa manera poder graficar*/

void Advertencias(int Indicacion); /*Funcion para mostrar mensaje de Advertencia durante el vuelo al momento de tener que cambiar de trayectoria o al momento de aterrizar*/

void MovimientoConjunto(int Paises[][4], int Num);

void InicioGraph(void); /*Funcion para iniciar el modo grafico*/

void main()
{
	int i; /*Variables para indicar el centro de la pantalla, OX => origen de x OY=> origen de y*/

	InicioGraph();

	/*Se pinta el fondo*/

	setfillstyle(SOLID_FILL, 9);
	bar(0, 0, 640, 480);

	muestraBMP(0, 0, "C:\\TC20\\BIN\\map.bmp"); /*Se carga la imagen*/

	/*Para trazar la mitad de la pantalla como un plano cartesiano*/

	setcolor(GREEN);
	line(0, OY, 640, OY);
	line(OX, 0, OX, 480);

	/*Para dibujar los circulos donde se encuentra los punto final*/

	for (i = 0; i < PAISES; i++)
	{
		setcolor(0);
		circle(dato[i][0] + OX, dato[i][1] + OY, 5);
	}

	movimiento(dato[Nicaragua][0], dato[Nicaragua][1], dato[Inglaterra][0], dato[Inglaterra][1]);
}

void movimiento(int *xo, int *yo, int *xf, int *yf, int *x, int *y, int *dif, int *xoCambio, int *yoCambio, int *xfCambio, int *yfCambio, int *Evento, int *boolllegar, float *DistMenor, int *seg, int *dd, int *hora, int *di,void **Bufer) /*Se usan los puntos de inicios y los puntos finales*/
{
	int i;			   /*Variables de bucle*/

	char mensaje[100]; /*Por el momento solo se utiliza para mostrar algunos datos de desarrollo*/
					   /*Buffer para guardar la imagen a traves del Rasterop*/

	setfillstyle(SOLID_FILL, BLUE);
	setcolor(15);
	mver();

	/*Puntos de origen de la pantalla*/

	*Bufer = malloc(imagesize(0, 0, 10, 10)); /*Reserva de memoria*/

	x = xo;						  /*Al momento de iniciar la interaccion x siempre tendra el valor del punto inicial por que directamente se lo asignamos*/
	y = Recta(xo, yo, xf, yf, x); /*y va a tener el valor de la ecuacion de la Recta*/
	dif = (y - yo);				  /*Habia un problema que normalmente la funcion retornaba valores que no eran exactos y el avion iniciaba en un lugar que no era
									al momento de obtener la diferencia entre el valor de y que te da la funcion recta y el valor de y inicial se logra calibrar*/

	y = y - dif; /*Al restarle el valor de dif es que se logra calibrar le ubicacion del avion o circulo*/

	sprintf(mensaje, "%d %d %d %d %d %d %d %d %d", x, y, Recta(xo, yo, xf, yf, x), xoCambio, yoCambio, xf, yf, xfCambio, yfCambio); /*Por el momento solo se utiliza para mostrar algunos datos de desarrollo*/
	outtextxy(10, 10, mensaje);

	/*Se obtiene la imagen de fondo y se guarda en el buffer*/

	getimage(x - RAD + OX, y - RAD + OY, x + RAD + OX, y + RAD + OY, buffer1);
	rectangle(x - RAD + OX, y - RAD + OY, x + RAD + OX, y + RAD + OY);
	delay(500);

	srand(time(NULL)); /*Para el uso de del random posteriormente*/
	Evento = rand() % 2;

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
			}
			else if (DistMenor > sqrt(pow((xoCambio - dato[i][0]), 2) + pow((yoCambio - dato[i][1]), 2)))
			{
				DistMenor = sqrt(pow((xoCambio - dato[i][0]), 2) + pow((yoCambio - dato[i][1]), 2));
				xfCambio = dato[i][0];
				yfCambio = dato[i][1];
			}
		}
	}

	while (1)
	{
		/*Siempre se iniciara en 0 o 30 para mayor facilidad */

		gettime(&tiempo);	/*Fecha del sistema*/
		dd = tiempo.ti_sec; /*Se obtiene los segundos del sistema*/
		if (dd == 0 || dd == 30)
		{ /*Rompera ciclo cuando sea 0 o 30*/
			break;
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

			if (hora == 24)
				hora = 0;
			hora++; /*Incremento de hora*/
		}

		if ((di != dd) && boolllegar == 1)
		{
			mocultar();

			di = tiempo.ti_sec;

			/*Esto es para borrar el mensaje*/
			setcolor(0);
			outtextxy(10, 10, mensaje);

			/*Para borrar el circulo*/
			putimage(x - RAD + OX, y - RAD + OY, *Bufer, 0);
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
			y = y - dif;				  /*Aqui se vuelve a utilizar esta variable para calibrarlo*/

			*Bufer = malloc(imagesize(0, 0, 10, 10));
			getimage(x - RAD + OX, y - RAD + OY, x + RAD + OX, y + RAD + OY, *Bufer); /*Se guarda el fondo*/

			/*Se pinta el avion*/
			setcolor(BLUE);
			setfillstyle(SOLID_FILL, BLUE);
			circle(x + OX, y + OY, RAD);
			floodfill(x + OX, y + OY, BLUE);

			/*Por el momento solo se utiliza para mostrar algunos datos de desarrollo*/
			sprintf(mensaje, "%d %d %d %d %d %d %d %d %d", x, y, Recta(xo, yo, xf, yf, x), xoCambio, yoCambio, xf, yf, xfCambio, yfCambio);
			outtextxy(10, 10, mensaje);

			/*Si aleatoria mente ocurre un evento, (Que el random haya asignado a Evento un valor de 1) y x sea igual al valor de xcambio
			(Que se obtuvo al inicio del bucle)*/

			if (x == xoCambio && Evento == 1)
			{
				/*Se pinta el avion en rojo*/
				mocultar();
				setcolor(RED);
				setfillstyle(SOLID_FILL, RED);
				circle(x + OX, y + OY, RAD);
				floodfill(x + OX, y + OY, RED);
				mver();
				/*Se muestra el mensaje de advertencia y se cambian las variables para redireccionar el trayecto*/
				Advertencias(2);
				xo = x;
				yo = y;
				xf = xfCambio;
				yf = yfCambio;
				dif = (Recta(xo, yo, xf, yf, x) - yo);
				xfCambio = yfCambio = xoCambio = yoCambio = 0;
				mensaje[0] = '\0';
				Evento = 0;
			}

			if (x == xf)
			{
				/*Se pinta el avion en amarillo*/
				mocultar();
				setcolor(YELLOW);
				setfillstyle(SOLID_FILL, YELLOW);
				circle(x + OX, y + OY, RAD);
				floodfill(x + OX, y + OY, YELLOW);
				mver();
				/*Se muestra el mensaje de advertencia para activar el protocolo de aterrizaje
				una vez activado se boora el circulo y se tendra que salir del bucle presionando ESC
				*/
				Advertencias(1);
				putimage(x - RAD + OX, y - RAD + OY, *Bufer, 0);
				free(*Bufer);
				boolllegar = 0;
			}

			mver();
		}
		/*Codigo para el desarrollo: Eso es mas que nada para salirse del programa a medio proceso*/
		
	}

	/*Esto es para cuando ya termine el bucle y se libere el espacio en memoria*/
}

int Recta(int x1, int y1, int x2, int y2, int x)
{
	long int y;
	long int a = x * (y2 - y1);
	long int b = x2 * (y2 + y1);
	long int c = (x1 * y1);
	long int d = (x2 - x1);

	/*
	Se sabe que a traves de dos puntos en un plano se pasa una recta, a la vez que teniendo dos puntos en un plano se
	puede obtener la ecuacion que pasa por estos dos puntos.

	y= (((x*(y2-y1))-(x2*(y2+y1))+(x1*y1))/(x2-x1)); 

	Esta ecuacion es la ecuacion general de la recta de manera despejada para obtener el valor de y, ya teniendo los puntos iniciales, finales,
	y dandole valores diferentes a x cada vez que se llama para de esa manera obtener el valor de y para de esta manera ya tener las coordenadas
	
	Daba un problema que en este caso se trabajaba con valores muy altos y se desbordaba la memoria causando inconvenientes, asi que se 
	decidio asignarle una variable del tipo long int a cada termino de la ecuacion y de esa manera no se desborde memoria
	reduciendolo a la siguiente ecuacion:
	*/

	y = (a - b + c) / d;

	return y; /*Al momento de retornar y este ya tiene un valor que si puede ser contenido en una variable del tipo int*/
}

void InicioGraph(void)
{
	int gd = 0, gm = 0;
	initgraph(&gd, &gm, "");
}

void Advertencias(int Indicacion)
{
	/*En esta funcion solamente es ejecucion de codigo para mostrar las advetencias*/

	int Event;
	char Emergencia[50];								/*Cadena para guardar el mensaje a mostrar*/
	int Advertencia[] = {410, 390, 550, 390, 480, 330}; /*Puntos para dibujar el triangulo de advertencia*/

	void far *buffer; /*Variable para el rasterop*/

	srand(time(NULL));	/*Para el uso de del random posteriormente*/
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

void MovimientoConjunto(int Paises[][4], int Num)
{
	int x[Num], y[Num], dif[Num], xoCambio[Num], yoCambio[Num], xfCambio[Num], yfCambio[Num], Evento[Num], boolllegar[Num];
	float DistMenor[Num];

	/*Explicacion de ambas variables*/
	/*
	x => va a ser la variable la cual se ira sumando o restando para que de esta manera el circulo siga la trayectoria (Este seria la variable independiente)
	y => esta variable sera dependiente de x la cual se obtendra a traves de una ecuacion y de esta manera se obtendira las coordenadas en y de la trayectoria del circulo
	RAD => Radio del circulo
	OX => el origen de x, para ubicar el origen en el centro de la pantalla
	OY => lo mismo pero en y
	dif=> esta variable es para calibrar la ubicacion en y del circulo

	variables 'nombre'Cambio
	Estas variables solamente se utilizan para calcular el cambio de trayectoria

	Evento => Variable la cual se usara paraobtener un numero random y que de esa manera ocurra una emergencia de manera aleatoria
	DistMenor => Variable para calcular la trayectoria mas cercana
	boolllegar => variable para indicar que no se siga moviendo una vez que se llego al destino
	*/
	int seg[Num], dd[Num], hora[Num], di[Num]; /*Variables de tiempo*/
	int i;									   /*Variables de bucle*/

	void far *buffer1[Num]; /*Buffer para guardar la imagen a traves del Rasterop*/

	int SalirBP = 1;

	for (i = 0; i < Num, i++)
	{
		x[i] = y[i] = dif[i] = xoCambio[i] = yoCambio[i] = xfCambio[i] = yfCambio[i] = Evento[i] = DistMenor[i] = seg[i] = dd[i] = hora[i] = di[i] = 0;
		boolllegar[i] = 1;
	}

	while (SalirBP)
	{
		switch (Num)
		{
		case 1:
			movimiento(&Paises[0][0], &Paises[0][1], &Paises[0][2], &Paises[0][3], &x[0], &y[0], &dif[0], &xoCambio[0], &yoCambio[0], &xfCambio[0], &yfCambio[0], &Evento[0], &boolllegar[0], &DistMenor[0], &seg[0], &dd[0], &hora[0], &di[0],&buffer1[0]);
			break;

		case 2:
			break;

		case 3:
			break;

		case 4:
			break;

		case 5:
			break;

		default:
			break;
		}

		if (kbhit())
			Salir = getch();

	}
}