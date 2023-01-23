
#include <stdio.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>
#include "utilidades.h"
#include "SubprogramaPuerto.h"
#include "Buque.h"
#include "funcionesExtra.h"
#include "operarBuque.h"
#include "estadoBuque.h"
#include "resumenMensualCalendario.h"


int main(){
  char opcion;
  bool volverMenu = false;
  puertos Cl = {
  {1, "RefinosFinos", 'R'},
  {2, "AlmacenReservas", 'D'},
  {3, "PozoGrande", 'Y'},
  {4, "ReservasEstrategicas", 'D'},
  {5, "PozoReserva", 'Y'},
  };
  buques Bq = {
  {'A', "Insignia", "RefinosFinos", 12, 2, 2023, "Crudo", 12, 02, 2023},
  {'B', "MarEgeo", "AlmacenReservas", 2, 3, 2023, "Vacio", 02, 03, 2023},
  {'C', "Alondra", "PozoGrande", 15, 3, 2023, "Fuel", 15, 03, 2023},
  {'D', "Rapido", "ReservasEstrategicas", 24, 4, 2023, "Vacio", 24, 04, 2023},
  {'E', "Lento", "PozoReserva", 23, 4, 2023, "Vacio", 13, 02, 2023},
  };
  int index =0;
  printf("\n\n");
  printf("Autor: MARTA MATEU LOPEZ\n\n");

  do {
  principal();
  scanf("%c", &opcion);
  volverMenu = true;
  switch(toupper(opcion)){
            case 'P':
                editarPuerto(Bq, Cl, index);
                break;

            case 'B':
                editarBuque(Bq, Cl, index);
                break;

            case 'E':
                estadoBuques(Bq, Cl);
                break;

            case 'O':
                operarBuque(Bq, Cl);
                break;

            case 'R':
                resumenMensual(Bq, Cl);
                break;

            case 'S':
              salir();
            	break;
          default: printf("Opci%cn inv%clida\n", 162, 160);
          }
          system("pause");

         } while (opcion !='S');


}


