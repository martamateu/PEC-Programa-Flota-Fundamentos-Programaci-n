#include "utilidades.h"
#include <stdio.h>


void principal(){
  printf(" GesFlota: Gestion de Movimientos de una Flota\n\n");
  printf("                                              \n");
  printf("                                    --------------------\n");
  printf("                                       Menu de usuario:\n");
  printf("                                    --------------------\n");
  printf("                                              \n\n");

  printf("      Editar Puerto             %16s(Pulsar P)\n", "");
  printf("      Editar Buque              %16s(Pulsar B)\n", "");
  printf("      Estado Buque              %16s(Pulsar E)\n", "");
  printf("      Operar Buque              %16s(Pulsar O)\n", "");
  printf("      Resumen Mensual Buque     %16s(Pulsar R)\n", "");
  printf("      Salir                     %16s(Pulsar S)\n\n", "");

  printf(" Teclear una opci%cn v%clida (P|B|E|O|R|S)? ",162,160);
}




