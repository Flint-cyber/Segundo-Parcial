/*
Autor: josec
Compilador: gcc (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0
Compilado: gcc bis.c -o bis
Fecha: Wed Apr 22 09:47:03 CST 2020
Librerias: stdio, math, stdlib
Resumen: Este programa calcula la raíz de una función matemática a través del método iterativo de bisección, y genera una gráfica de la función
Entrada:  
Salida: raíz
*/

//Incluimos todas las librerías
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//Declaramos las variables que vamos a utilizar
float a, b, root; //Variables matemáticas
int i; //Variable de iteración

//Definimos la función de bisección, para colocarla más adelante.
float bis (float na, float nb); 


//Iniciamos nuestra función principal
float main()
{
	//Imprimimos la función a utilizar, junto con el intervalo previamente seleccionado.
	printf("La Función es: y = (sin(x)/x)\n");
	printf("\nEl intervalo seleccionado es: [1,5]\n");
	
	//Asignamos un valor a las variables de la cota superior e inferior.
	a = 1;
	b = 5;

	//La raíz de nuestra función es igual a lo que retorna la función bis, al tener a y b como valores iniciales.
	root = bis(a, b);

	//Imprimimos la respuesta para que la vea el usuario.
	printf("\nLa raíz de esta función es:\t");
	printf("%.5f\n", root); //Dejamos solo hasta 5 decimales para que aproximar el valor.



	//IMPRESIÓN DE LA GRÁFICA
	
//Para imprimir la gráfica, vamos a crear un archivo .gp, en el cual vamos a ingresar las instrucciones de plotear la función deseada.
//El archivo .gp será ejecutado por gnuplot, e imprimirá las instrucciones que le daremos.
	
	//Declaramos el puntero que nos va a servir para poder dirigirnos al archivo que vamos a crear
	FILE * pun;

	//El puntero va a crear un archivo .gp (de gnuplot), y lo va a abrir con fopen
	pun = fopen("plot2.gp", "w"); //Escribimos "w" porque, como el archivo no existía antes, hay que crearlo.

	//Proseguimos a imprimir dentro del archivo .gp, las instrucciones para que crear la gráfica en gnuplot. 
	//Creamos la gráfica de la función asignada, y tamibén la de x = 0, para que sea más fácil ver el intersecto.
	fprintf(pun, "plot [-10:10][-0.5:1.2] sin(x)/x lw 4, 0 lw 4;");

	//Cerramos el archivo una vez ya lo llenamos con el script deseado.
	fclose(pun);

	//Con este comando hacemos que gnuplot ejecute el archivo .gp y siga sus instrucciones.
	system("gnuplot -p plot2.gp"); //El término -p sirve para que la gráfica permanezca en pantalla, aún si el Biseccion.c termina de correr.

	//Por último, borramos el archivo .gp para dejar intacto el directorio.
	remove ("plot2.gp");

	return 0;

}


	//MÉTODO DE BISECCIÓN

//Iniciamos nuestra función matemática donde realizaremos el método de bisección. 
float bis (float na, float nb) //Declaramos las 2 variables que tomarán el valor de a y b cuando el main llame a esta función.
{
	//Declaración de variables locales.
	float np, xp, xa, res;

	//Realizamos el método de bisección a través de un loop for.
	for(i = 0; i < 20; i++) //Usamos un for y no while porque la raíz es irracional, y solo podemos aproximarnos a ella. 
				//Un while mantendría el programa en loop por demasiado tiempo.
	{
		np = (na + nb)/2; //Definimos np usando la fórmula vista en clase.
		
		//Definimos estas 2 variables valuando la función original con np y na, como indica el método
		xp = (sin(np)/np);
		xa = (sin(na)/na);
		
		//Multiplicamos xp y xa, asignando ese valor a la variable de resultado, para su posterior comparación.
		res = xp*xa;

		if(res > 0)
		{
			na = np; //Si el producto de xp y xa resulta positivo, na toma el valor de np.
				//Y recalculamos un nuevo np para repetir el proceso.
		}

		else if(res < 0)
		{
			nb = np; //Si el producto de xp y xa resulta negativo, nb toma el valor de np.
				//Y recalculamos un nuevo np para repetir el proceso.
		}


	}

	//Luego de 20 iteraciones, ya hay una buena estimación del valor de la raíz.
	//Así que retornaremos el valor que np tomó en la vigésima iteración (el valor más cercano a la raíz verdadera)
	return np; 


}




