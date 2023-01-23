#include <stdio.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>
#include "operarBuque.h"
#include "funcionesExtra.h"
#include "utilidades.h"
#include "estadoBuque.h"
#include "resumenMensualCalendario.h"

void resumenMensual(buques& Bq, puertos Cl){
char id;
int mes, ano;
int indice = -1;
int bisiestos;
int incrementoDias;
int incrementoAnnos;
TipoDia diaSemana;
int diasEnBlanco = diaSemana;
int dia = 1;
int numDias;
int diasEnBlancoFinal = (14 - (numDias + diasEnBlanco) % 14) % 7;
int anos;
int dias;
char otroMes;


// Pide al usuario que ingrese el identificador del buque
printf("Identificador del buque: ");
scanf(" %c", &id);
 id = toupper(id);

// Pide al usuario que ingrese el mes y el año para el resumen
LeerFecha(mes,ano);
  if (((mes>=1)&&(mes<=12))&&((ano>=1601)&&(ano<=3000))){	//Solo si la
    bisiestos = CalcularBisiestos(mes,ano);	//fecha es correcta
    anos = CalcularAnnos(ano);			//el programa realiza accion alguna
    dias = CalcularDias(mes);
    incrementoDias = bisiestos+anos+dias;
    diaSemana = DiaDeLaSemana(incrementoDias);
    // Genera el resumen mensual
    printf("\n\n");
    printf("Resumen mensual Buque:\n");
    printf("Identificador Buque: %c\n", id);
    printf("Selecci%cn Mes: %d\n",162, mes);
    printf("Selecci%cn A%co: %d\n",162,164, ano);
    ImprimirCalendario(mes,ano,diaSemana);






  }
// Encuentra el índice del buque con el identificador especificado
for (int i = 0; i < MAX_BUQUES; i++) {
if (Bq[i].id == id) {
indice = i;
printf("\n\n");
printf("Tiempo de cargas (C): %d d%Cas\n", Bq[indice].tiempoCargas,161);
printf("Tiempo de traslados (T#):\n");
printf("Traslado T1: \n");
printf("Traslado T2: \n");
printf("Tiempo de descargas (D):\n");
printf("Tiempo de parada:\n");


}
printf("\n\n");
  printf("¿Desea ver otro mes? (S/N) ");

  scanf(" %c", &otroMes);
  otroMes = toupper(otroMes);
    if (otroMes == 'S'){
      resumenMensual(Bq, Cl);
     }
  if (otroMes == 'N') {
   return;
  }


}

// Si el buque no existe, muestra un mensaje de error y termina la función
if (indice == -1) {
printf("El buque con identificador %c no existe\n", id);
return;
}



}
