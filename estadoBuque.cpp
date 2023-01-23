#include <stdio.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>
#include "funcionesExtra.h"
#include "SubprogramaPuerto.h"
#include "Buque.h"
#include "operarBuque.h"
#include "estadoBuque.h"


void estadoBuques(buques Bq, puertos Cl) {
  int contador = 0;

  // Recorre la tabla de buques y cuenta cuántos buques hay
  for (int i = 0; i < MAX_BUQUES; i++) {
    if (Bq[i].id != '\0') {
      contador++;
    }
  }

  // Si no hay buques en la tabla, muestra un mensaje de error y termina la función
  if (contador == 0) {
    printf("No hay buques en la tabla\n");
    return;
  }

  // Si hay buques en la tabla, imprime la tabla
  printf("\n\n");
  printf("%*sEstado de Buques%*s\n", 36, "", 36, "");
  printf("\n\n");
  printf(" Id     Nombre            Puerto                       Ultima Fecha               Carga\n");
  printf(" ---    --------         -----------                  ---------------          ------------\n");
  printf("\n");
  for (int i = 0; i < MAX_BUQUES; i++) {
    if (Bq[i].id != '\0') {
      // Aquí debes imprimir los datos del buque en la tabla
      printf("  %c\t%-10s\t%-30s\t%02d/%02d/%04d\t%*s%s\n",
      Bq[i].id, Bq[i].nombre, Bq[i].puertoInicio, Bq[i].dia_fin_ultima_operacion, Bq[i].mes_fin_ultima_operacion, Bq[i].ano_fin_ultima_operacion,
      16 - strlen(Bq[i].carga), "", Bq[i].carga);



    }
      printf("\n\n");
  }
}
