#include <stdio.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>
#include "Buque.h"
#include "funcionesExtra.h"
#include "estadoBuque.h"

void editarBuque(buques& bq, puertos Cl, int index) {
char id;
int puertoInicioId;
char confirmar_datos;
int indice = -1;
int dia, mes, ano;

printf("\n\n");
printf("Editar Buque:\n");
printf("\n\n");
  // Pide al usuario que ingrese el identificador del buque a editar
 printf("    Identificador (letra entre A y E)?\n");
  scanf(" %c", &id);
  // Convierte el identificador a mayúsculas
  id = toupper(id);
  // Asegúrate de que el identificador sea válido
  if (id < 'A' || id > 'E') {
    printf("Identificador invalido\n");
    return;
  }

  // Encuentra el índice del buque con el identificador especificado

  for (int i = 0; i < MAX_BUQUES; i++) {
    if (bq[i].id == id) {
      indice = i;
   }
  }

  // Si el buque no existe, muestra un mensaje de error y termina la función
  if (indice == -1) {
    printf("El buque con identificador %c no existe\n", id);
    return;
  }
printf("    Nombre (entre 1 y %d caracteres, sin espacios)? \n", MAX_NOMBRE);
scanf("%s", bq[index].nombre);
printf("    Fecha inicio: D%ca? \n",161);
scanf("%d", &dia);
printf("    Fecha inicio: Mes? \n");
scanf("%d", &mes);
printf("    Fecha inicio: A%co? \n",164);
scanf("%d", &ano);

if (!esFechaValida(dia, mes, ano)) {
  printf("Fecha inv%clida\n",160);
  return;
}
if (ano < 1900 || ano > 2100) {
  printf("A%co inv%clido\n",164,160);
  return;
}


printf("    Puertos posibles para la ubicación inicial del buque: \n");
printf("\n");
printf("------------------------------------------------------------------\n");
printf("| Numero | Nombre                    | Tipo                         |\n");
printf("------------------------------------------------------------------\n");
for (int i = 0; i < MAX_PUERTOS; i++) {
  if (Cl[i].num != 0) {
    printf("| %6d | %-24s | ", Cl[i].num, Cl[i].nombre);
    switch (Cl[i].tipo) {
      case 'Y':
        printf("Yacimiento");
        break;
         case 'R':
        printf("Refineria",161);
        break;
        case 'D':
        printf("Dep%csito",162);
        break;
    }
    printf("\n");
  }
}
printf("------------------------------------------------------------------\n");
printf("\n\n");
printf("    Identificador de puerto inicio? \n");
scanf("%d", &puertoInicioId);

// Asegúrate de que el puerto de inicio exista y asigna su identificador al buque
if (puertoInicioId < 1 || puertoInicioId > MAX_PUERTOS || Cl[puertoInicioId - 1].num == 0) {
printf("Identificador de puerto de inicio invalido\n");

return;
}


// Pregunta al usuario si los datos ingresados son correctos
printf("   IMPORTANTE: Esta opci%cn borra los datos anteriores. \n",162);
printf("   Son correctos los nuevos datos (S/N)? \n");
scanf(" %c", &confirmar_datos);

if (toupper(confirmar_datos) == 'S') {
  strcpy(bq[index].puertoInicio, Cl[puertoInicioId - 1].nombre);
  // Guarda el id del buque
  bq[index].id = id;
  // Guarda el nombre del buque
  strcpy(bq[indice].nombre, bq[index].nombre);
   // Guarda la fecha de inicio del buque
  bq[index].dia = dia;
  bq[index].mes = mes;
  bq[index].ano = ano;
  // Guarda el puerto de inicio elegido
  strcpy(bq[index].puertoInicio, Cl[puertoInicioId - 1].nombre);
  // Guarda el tipo de puerto asociado al puerto de inicio elegido
  Cl[index].tipo = Cl[puertoInicioId - 1].tipo;


printf("Los datos del buque con identificador %c han sido actualizados\n", bq[index].id);
} else {
printf("Los datos del buque con identificador %c no han sido actualizados\n", bq[index].id);
}
}


