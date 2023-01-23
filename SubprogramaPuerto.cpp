#include <stdio.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>
#include "SubprogramaPuerto.h"


void editarPuerto(buques& bq, puertos& Cl, int index) {
  char confirmar;
  printf("\n\n");
  printf(" Editar Puerto:\n");
  printf("\n\n");
  printf("          Ingresa el identificador del puerto (n%cmero entre 1 y %d): \n",163, MAX_PUERTOS);
  scanf("%d", &Cl[index].num);

  // Asegúrate de que el identificador sea válido
  if (Cl[index].num < 1 || Cl[index].num > MAX_PUERTOS) {
    printf("Identificador inv%clido\n",160);
    return;
  }

  // Borra los datos del puerto con el identificador especificado
  printf(" IMPORTANTE, Se borrar%cn los datos del puerto con identificador %d. %cDeseas continuar (S/N)? \n",160, Cl[index].num,168);

  scanf(" %c", &confirmar);

  if (toupper(confirmar) == 'S') {
    strcpy(Cl[index].nombre, "");
    Cl[index].tipo = '\0';

    printf(" Ingresa los nuevos datos para el puerto con identificador %d:\n", Cl[index].num);
    printf("\n\n");
    printf("          Nombre (entre 1 y %d caracteres, sin espacios)? \n", MAX_NOMBRE);
    scanf("%s", Cl[index].nombre);
    printf("         Tipo (Y-Yacimiento, R-Refiner%ca, D-Dep%csito)? \n",161,162);
    scanf(" %c", &Cl[index].tipo);
    if (toupper(Cl[index].tipo) == 'Y' || toupper(Cl[index].tipo) == 'R' || toupper(Cl[index].tipo) == 'D') {
       printf("Los datos del tipo puerto con identificador %d han sido actualizados\n", Cl[index].num);
     } else {
     printf("Los datos del tipo puerto con identificador %d no han sido actualizados\n", Cl[index].num);
     }

    // Pregunta al usuario si los datos ingresados son correctos
    printf("Son correctos los nuevos datos (S/N)? \n");
    scanf(" %c", &confirmar);
    if (toupper(confirmar) == 'S') {
      printf("Los datos del puerto con identificador %d han sido actualizados\n", Cl[index].num);
      strcpy(bq[index].puertoInicio, Cl[index].nombre);

    } else {
      printf("Los datos del puerto con identificador %d no han sido actualizados\n", Cl[index].num);
    }
  } else {
    printf("Los datos del puerto con identificador %d no han sido modificados\n", Cl[index].num);
  }
}

