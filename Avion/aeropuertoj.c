#include <graphics.h>
#include <stdio.h>
#include <dos.h>
#include <math.h>
#include <conio.h>
#include <stdio.h>
#include <16image.h>

#define izquierda 75
#define derecha 77
#define enter 13

/*En este arreglo se muestran los puntos que representan a cada pais*/

int dato[13][2]={	99,153,/*EEUU 0*/
					262,151,/*Espana 1*/
					272,131,/*Francia 2*/
					437,163,/*China 3*/
					401,89,/*Rusia 4*/
					107,97,/*Canada 5*/
					159,368,/*Argentina 6*/
					178,291,/*Brazil 7*/
					499,337,/*Australia 8*/
					90,201,/*Mexico 9*/
					500,158,/*Japon 10*/
					403,202,/*India 11*/
					117,227};/*Nicaragua 12*/
					
/*Para facilitar a el dato de los paises*/

enum paises{

	Estados_unidos=0,
	Espana=1,
	Francia=2,
	China=3,
	Rusia=4,
	Canada=5,
	Argentina=6,
	Brazil=7,
	Australia=8,
	Mexico=9,
	Japon=10,
	India=11,
	Nicaragua=12

};


struct time tiempo;/*estructura timpo*/

/*funciones utilizadas*/

int Recta(int p1,int p2,int x);

void movi(int p12[5][2],int av[],int tiemp);

void main()
{

	int adap=DETECT, modo;

	/*el primer parametro representa el pais de origen y el segundo el pais de llegada*/

	int p12[5][2]={Nicaragua,Rusia,Nicaragua,Japon,Nicaragua,Canada,Nicaragua,Francia,Nicaragua,Espana};

	/*marca que avion puede salir o no*/
	/*si se desea evitar que un avion salga solo pon 0 en el indice que corresponde*/

	int p[]={1,1,1,1,1};

	initgraph(&adap,&modo,"c:\\tc20\\bin");
	setfillstyle(SOLID_FILL, 9);
	bar(0,0,640,480);
	muestraBMP(0,0, "C:\\TC20\\BIN\\map.bmp");
	setfillstyle(SOLID_FILL, BLUE);
	movi(p12,p,0);
	getch();

}

/*El parametro p12 muestra el punto de de salida y de llegada*/
/*El parametro av muestra que avion puede volar. 1= puede volar , 0 = no puede volar*/
/*El parametro tiemp aun no tiene utilidad*/

void movi(int p12[5][2],int av[5],int tiemp){

	/*controlar de los aviones*/
	int ox,x[5],y[5],rad=5,s[5]={0,0,0,0,0};

	/*variables tiempo*/
	int seg,dd,hora=0,di;

	/*iteradores*/
	int i=0,ii;

	/*variables para control de teclas*/
	char mensaje[50],c;                /*Si el punto medio de la pantalla es el origen (es decir igual a 0) -320 seria el inicio de la pantalla*/

	/*para guardar imagen*/
	void far *buffer1;

	ox=getmaxx()/2;         /*Con esta ecuacion se obtiene el valor del origen en x*/

	/*reservamos memoria*/

	buffer1=malloc(imagesize(0,0,10,10));

	/*asignamos los puntos x de inicio*/
	
	for(ii=0;ii<5;ii++)
	{
		/*le asigamos un punto simbolico donde el origen se encuentra 
		en el punto 320x240*/

		x[ii]=dato[p12[ii][0]][0]-ox;

		/*Se obtiene el valor de y por medio de la funcion recta*/
		y[ii]=Recta(p12[ii][0],p12[ii][1],x[ii]);

		/*S[] sirve para calcular la diferencia que hay entre y[] y el punto y original*/
		if(y[ii]+240<dato[p12[ii][0]][1])
		{
			s[ii]=dato[p12[ii][0]][1]-(y[ii]);
		}else
		{
			s[ii]=(y[ii])-dato[p12[ii][0]][1];
		}
	}
	
	/*se pone la zona inicial a recoger*/

	getimage(x[i]+ox-rad,y[i]-rad-s[i],x[i]+ox+rad,y[i]+rad-s[i],buffer1);
	rectangle(x[i]+ox-rad,y[i]-rad-s[i],x[i]+ox+rad,y[i]+rad-s[i]);

	while(1)
	{/*siempre se iniciara en 0 o 30 para mayor facilidad */
		gettime(&tiempo);/*fecha del sistema*/
		dd=tiempo.ti_sec;
		if(dd==0 || dd==30)
		{	/*rompera ciclo cuando sea 0 o 30*/
			break;
		}
	}/*para ir recogiendo el tiempo*/

	gettime(&tiempo);
	dd=tiempo.ti_sec;
	di=tiempo.ti_sec;
	seg=dd;
	i=0;
	while(1)
	{
		gettime(&tiempo);
		dd=tiempo.ti_sec;
		if(dd==seg+30)
		{
			if(seg+30==60)/*cuando ya es un minuto*/
				seg=0;
			else/*cuando ya es medio minuto*/
				seg=30;
			
			if(hora==24)
				hora=0;
		hora++;/*incremento de hora*/
		}
		/*cada segundo hara una iteracion*/
		if(di!=dd)
		{
			setcolor(15);
			sprintf(mensaje,"%d",i);    /*Se guarda el valor como caracter en la cadena mensaje*/
			outtextxy(10,10,mensaje);   /*Se imprime el mensaje*/
			di=tiempo.ti_sec;/*se le asigna el nuevo segundo al valor di*/
				if(av[i]==1)
				{
					/*pone el trozo de pantalla*/
						putimage(x[i]+ox-rad,y[i]-rad-s[i],buffer1,0);
						free(buffer1);/*libera memoria*/
						
						/*se valida si el punto de origen es menor que el punto destino o viceversa*/
						if(x[i]+ox<=dato[p12[i][1]][0])
						{
							x[i]++;    /*Se le suma 1 a las coordenada en x*/
							y[i]=Recta(p12[i][0],p12[i][1],x[i]);       /*Se obtiene el valor de y por medio de la funcion recta*/
						}
						if(x[i]+ox>=dato[p12[i][1]][0]){
								x[i]--;    /*Se le resta 1 a las coordenada en x*/
								y[i]=Recta(p12[i][0],p12[i][1],x[i]);       /*Se obtiene el valor de y por medio de la funcion recta*/
						}
						/*recogemos la nueva coordeada*/
						getimage(x[i]+ox-rad,y[i]-rad-s[i],x[i]+ox+rad,y[i]+rad-s[i],buffer1);
					
						/*se valida que x no sea mayor o menor que el punto de origen*/
						if(x[i]+ox<=dato[p12[i][1]][0])
						{
							setcolor(BLUE);               /*Se manda a pintar en blanco*/
							circle(x[i]+ox, y[i]-s[i],rad);      /*Se dibuja el circulo como anteriormente mencionamos*/
							floodfill(x[i]+ox,y[i]-s[i],BLUE); /*se rellena el circulo*/
						}
						else if(x[i]+ox>=dato[p12[i][1]][0])
						{
							setcolor(BLUE);               /*Se manda a pintar en blanco*/
							circle(x[i]+ox, y[i]-s[i],rad);      /*Se dibuja el circulo como anteriormente mencionamos*/
							floodfill(x[i]+ox,y[i]-s[i],BLUE);/*se rellena el circulo*/
						}

						if(x[i]+ox==dato[p12[i][1]][0])
						{
							break;

						}
				}
		}/*se valida si se preciono una tecla
		dependiendo de que direccional se toque se sumara o se restara a i pra ver los diferentes aviones*/
		if(kbhit()!=0){
			c=getch();
			if(c==izquierda){
				if(i==0){
					for(ii=4;i>=0;i--){
						if(av[i]==1){
							i=ii;
						}
					}
				}else{
					i--;
				}
			}else if(c==derecha){
				if(i==4){
					for(ii=0;i<5;i++){
						if(av[i]==1){
							i=ii;
						}
					}
				}else{
					i++;
				}
			}else if(c==enter){
				break;
			}
		}
	}
	
}

int Recta(int p1,int p2,int x)
{
	
	int x1= dato[p1][0]-320;
	int y1= dato[p1][1]-240;
	int x2= dato[p2][0]-320;
	int y2= dato[p2][1]-240;
    /*x1 y y1 son los valores de la ubicacion del primer punto, x2 y y2 son los valores de la ubicacion del segundo puntos, y x es la variable que varia alrededor de la ejecucion*/

    int y;
    y= ((x*(y2-y1))-(x2*(y2+y1))+(x1*y1))/(x2-x1);  /*La ecuacion que se resuelve*/
    return y;                                       /*Si x vale un numero (variable independiente), se retorna el valor de y, (variable dependiente)*/


}

/*se que no es e*l codigo mas optimo pero fue lo que se me ocurrio :c*/