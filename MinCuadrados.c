/*
Autor: josec
Compilador: gcc (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0
Compilado: gcc MC.c -o MC
Fecha: Wed Apr 22 07:14:53 CST 2020
Librerias: stdio, stdlib, math
Resumen: Este programa calcula una recta por medio del método de mínimos cuardados
Entrada: 
Salida: m, b, dm, db
*/

//Incluimos las respectivas bibliotecas
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


//Declaramos Variables
float Vol[6] = {54.3, 61.8, 72.4, 88.7, 118.6, 194.0}; //Correspondiente a la columna de volúmenes
float Pre[6] = {61.2, 49.2, 37.6, 28.4, 19.2, 10.2}; //Correspondiente a la columna de Presiones
int i; //Variable de loop
float m, b, dm, db; //Variables de salida
float sum1, sum2, sum3, sum4; //Variables que almacenarán los valores de distintas sumatorias.


//Declaramos las funciones que vamos a utilizar.
float M (float n1, float n2, float n3, float n4);
float B (float n2, float n3, float n);
float DM (float n4, float n3);


//Iniciamos nuestra función principal
void main(void)
{
	
	//Usamos un loop for para calcular todas las sumatorias que el método de mínimos cuadrados requiere.  
	for(i = 0; i < 6; i++)
	{
		sum1 = sum1 + Vol[i]*Pre[i]; //Sumatoria de Xk*Yk

		sum2 = sum2 + Vol[i]; //Sumatoria de Xk
		
		sum3 = sum3 + Pre[i]; //Sumatoria de Yk

		sum4 = sum4 + Vol[i]*Vol[i]; //Sumatoria de Xk al cuadrado
	}


	//Procedemos a imprimir la tabla, para que el usuario la vea.
	printf("Volumen\t\t\tPresión\n"); //Imprimimos 2 columnas
	
	//Creamos un loop para imprimir los datos
	for(i = 0; i < 6; i++)
	{
		printf("%.1f +- 0.1\t\t%.1f +- 0.2\n", Vol[i], Pre[i]); //Imprimimos los datos de ambos arrays, tabulados, y con sus respectivas incertezas.
	}

	//Imprimios la pendiente m, cuyo valor se obtiene con la función M.
	m = M(sum1, sum2, sum3, sum4);
	printf("\nPendiente m:\t");
	printf("%.4f\n", m); //Por conveniencia, solo imprimimos hasta el cuarto decimal.

	//Imprimimos el intersecto b, cuyo valor se obtiene con la función B.
	b = B(sum2, sum3, m); 
	printf("\nIntersecto b:\t");
	printf("%.2f\n", b); //Por conveniencia, imprimimos hasta el segundo decimal.

	//Imprimimos la incerteza en la pendiente, cuyo valor se obtiene con la función DM.
	dm = DM(sum2, sum4);
	printf("\nIncerteza en m:\t%.4f\n", dm); //Por conveniencia, imprimimos hasta el segundo decimal.


	//Imprimimos el valor de la incerteza en b.
	db = 0.1/sqrt(6); //El valor de la incerteza en b se calcula de forma directa.
	printf("\nIncerteza en b:\t%.2f\n", db); //Por conveniencia, imprimimos hasta el segundo decimal.

	//Procedemos a imprimir las solución completa.
	printf("\nEcuación de Recta:\t");
	
	//Imprimimos solo hasta el cuarto y segundo decimal respectivamente, para que los datos concuerden con la incerteza. 
	printf("y = (%.4f +- %.4f)x + (%.2f +- %.2f)\n\n", m, dm, b, db); 

	//Imprimimos el valor de la presión si V = 100, como nos pedía el enunciado, usando la aproximación de la recta.
	printf("Valor estimado de Presión con V = 100:\t");
	printf("%.1f\n", 100*m + b);



	//IMPRESIÓN DE LA GRÁFICA
	
//Para imprimir la gráfica, vamos a crear 2 archivos con C, uno .txt y uno .gp
//El archivo .txt almacenará los datos tabulados de volumen y presión.
//El archivo .gp será ejecutado por gnuplot, e imprimirá tanto los datos tabulados del archivo .txt, como la aproximación lineal.
	
	
	//Declaramos los 2 punteros que nos va a servir para poder dirigirnos a los archivos que vamos a crear.
	FILE * pun1; //Correspondiente a los datos tabulados
	FILE * pun2; //Correspondiente al archivo .gp y a la recta aproximada.
	
	//Con el primer puntero, abrimos el archivo de texto plot1.
	pun1 = fopen("plot1.txt", "w");
	
	//Usamos un loop for para ingresar los datos de ambas tablas en el archivo, de una forma más ordenada.
	for(i = 0; i < 6; i++)
	{
		fprintf(pun1, "%.1f\t%.1f\n",Vol[i], Pre[i]); //Primero van los datos de volumen, y luego de presión, como coordenadas en X y Y.
	}

	//Cerramos el archivo de texto, después de modificarlo.
	fclose(pun1);

	//Con el segundo puntero, abrimos el archivo .gp
	pun2 = fopen("squares.gp", "w");
	
	//En el archivo .gp, imprimimos las instrucciones que deseamos que siga gnuplot.
	//Le ordenamos que imprima la ecuación de recta (aproximada hasta el segundo decimal), y los puntos que almacenamos en el archivo .txt
	fprintf(pun2, "plot %.4f*x + %.2f lw 3, 'plot1.txt' lw 3;", m, b);
	
	//Cerramos el archivo .gp
	fclose(pun2);

	//Con este comando hacemos que gnuplot ejecute y siga las instrucciones del archivo .gp
	system("gnuplot -p squares.gp");

	//Procedemos a borrar ambos archivos para dejar intacto el directorio.
	remove("plot1.txt");
	remove("squares.gp");



}

	//MÉTODO DE MÍNIMOS CUADRADOS

//Comenzamos calculando la pendiente
float M (float n1, float n2, float n3, float n4)
{
	float res, num, den; //Para que todo salga más limpio, calcularemos primero numerador y denominador, y luego haremos la fracción.

	num = 6*n1 - n2*n3; //Calculamos numerador
	den = 6*n4 - n2*n2; //Calculamos denominador
	
	res = num/den; //Dividimos.

	return res; //El resultado lo retornamos a la función main.
}



float B (float n2, float n3, float n)
{
	//Declaramos variable local
	float res, num, den; //De nuevo, dividimos el procedimiento en otros más sencillos para que resulte más limpio.
	
	num = n3 -n*n2;
        
	res = num/6;

	return res; //Una vez obtenemos el resultado, lo retornamos a la función main.
}


//Calculamos la incerteza de la pendiente
float DM (float n2, float n4)
{
	//Declaramos variable local.
	float res;

	res = sqrt(6)*0.1/pow(6*n4 -n2*n2, 0.5); //Esta vez la fórmula es un poco más directa, requiriendo solo una línea para completarse.

	return res; //Retornamos el resultado a la función main.
}

