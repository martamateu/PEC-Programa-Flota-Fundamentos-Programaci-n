#include <stdio.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>
#include "operarBuque.h"
#include "funcionesExtra.h"
#include "utilidades.h"
#include "estadoBuque.h"

void operarBuque(buques& Bq, puertos Cl){
int dia, mes, ano;
char id;
int indice = -1;
int i;
char quiereCargar;
char producto;
int duracionCarga;
int duracionTraslado;
int duracionDescarga;
char quiereTraslado;
char confirmarOperacion;
int idPuertoDestino;
char quiereDescargar;
char confirmacionCarga;
char productoDisponible;
char volverAlMenu;
int descargaValida = 0;
char tipoPuertoInicio;
int sumaDuracionesCarga;


// Pide al usuario la fecha de comienzo de la operación

printf("Fecha comienzo operaci%cn: D%ca? \n",162,161);
scanf("%d", &dia);
printf("Fecha comienzo operaci%cn: Mes?\n",162);
scanf("%d", &mes);
printf("Fecha comienzo operaci%cn: A%co?\n",162,164);
scanf("%d", &ano);

 // Asegúrate de que la fecha de comienzo sea válida
  if (!esFechaValida(dia, mes, ano)) {
    printf("Fecha inv%clida\n",160);
    return;
  }

 // Pide al usuario el identificador del buque

 printf("    Identificador (letra entre A y E)?\n");
  scanf(" %c", &id);
  // Convierte el identificador a mayúsculas
  id = toupper(id);
  // Asegúrate de que el identificador sea válido
  if (id < 'A' || id > 'E') {
    printf("Identificador inv%clido\n",160);
    return;
  }

  // Encuentra el índice del buque con el identificador especificado

  for (int i = 0; i < MAX_BUQUES; i++) {
    if (Bq[i].id == id) {
      indice = i;
   }
  }

  // Si el buque no existe, muestra un mensaje de error y termina la función
  if (indice == -1) {
    printf("El buque con identificador %c no existe\n", id);
    return;
  }
// Muestra la última fecha de operación del buque
printf("La %cltima operaci%cn del buque %s finaliz%c el %d/%d/%d\n",163,162, Bq[indice].nombre,162, Bq[indice].dia_fin_ultima_operacion, Bq[indice].mes_fin_ultima_operacion, Bq[indice].ano_fin_ultima_operacion);

// Verifica que la fecha de inicio de la operación sea posterior a la última operación del buque
if (ano < Bq[indice].ano_fin_ultima_operacion || (ano == Bq[indice].ano_fin_ultima_operacion && mes < Bq[indice].mes_fin_ultima_operacion) || (ano == Bq[indice].ano_fin_ultima_operacion && mes == Bq[indice].mes_fin_ultima_operacion && dia <= Bq[indice].dia_fin_ultima_operacion)) {
printf("La fecha de comienzo de la operación no es compatible con la última operación del buque. La fecha debe ser posterior a la fecha de finalización de la última operación: %d/%d/%d\n", Bq[indice].dia_fin_ultima_operacion, Bq[indice].mes_fin_ultima_operacion, Bq[indice].ano_fin_ultima_operacion);
return;
}

 // Verifica si el buque está cargado o no
 // Si el buque está vacío, todos los puertos son válidos

if (strcmp(Bq[indice].carga, "Vacio") == 0) {
printf("\n");
printf("El buque %s est%c vac%co en el puerto %s\n", Bq[indice].nombre,160,161, Bq[indice].puertoInicio);

  printf("Quiere realizar la carga (S/N)?\n");
  scanf(" %c", &quiereCargar);
  if (toupper(quiereCargar) == 'N') {


//OPCION NO QUIERE CARGAR
    printf("Quiere realizar el traslado (S/N)?\n");
    scanf(" %c", &quiereTraslado);
    if (toupper(quiereTraslado) == 'S') {
    //OPCION NO QUIERE CARGAR PERO SI QUIERE TRASLADO
    printf("Posibles puertos de inicio:\n");
    for (int i = 0; i < MAX_PUERTOS; i++) {
    if (strcmp(Bq[indice].puertoInicio, Cl[i].nombre) != 0 && strcmp(Cl[i].nombre, "") != 0) {
    printf("%d. %s ", i + 1, Cl[i].nombre);
    switch (Cl[i].tipo) {
    case 'Y':
    printf("Tipo: Yacimiento");
    break;
    case 'R':
    printf("Tipo: Refineria",161);
    break;
    case 'D':
    printf("Tipo: Dep%csito",162);
    break;
    }
    printf("\n");
    }
    }
    printf("Ingrese el n%cmero del puerto de destino:\n",163);
    scanf("%d", &idPuertoDestino);
    idPuertoDestino = idPuertoDestino - 1;//restamos 1 ya que los índices de la tabla empiezan en 0
    printf("Ingrese la duraci%cn del traslado en d%cas: ",162,161);
    scanf("%d", &duracionTraslado);


    // No Pregunta al usuario si quiere realizar una descarga porque no procede en este caso
    printf("No procede descarga porque el buque está vacío.\n");
    printf("Traslado desde %s hasta %s\n", Bq[indice].puertoInicio,Cl[idPuertoDestino].nombre );

    printf("Resumen de la operaci%cn:\n",162);
    printf("================\n");
    printf("Fecha comienzo: %d/%d/%d\n", dia, mes, ano);
    printf("Puerto origen: %s\n", Bq[indice].puertoInicio);
    printf("Puerto destino: %s\n", Cl[idPuertoDestino].nombre);
    printf("Duraci%cn del traslado en d%cas: %d\n",162,161, duracionTraslado);
    printf("Es correcta la operaci%cn (S/N)?\n",162);
     scanf(" %c", &confirmarOperacion);


   // Pide al usuario si la información del resumen es correcta
   if (toupper(confirmarOperacion) == 'S') {
       Bq[indice].dia = dia;
       Bq[indice].mes = mes;
       Bq[indice].ano = ano;
   // Actualiza la fecha de fin de la última operación del buque
  // Calcula la nueva fecha sumando los días de duración de la carga a la fecha de inicio de la operación
     dia = dia + duracionTraslado;
     printf("dia: %d\n", dia);
    while (dia > 31) { // Mientras el día sea mayor a 31
      mes = mes + 1;// Aumentamos el mes
      if (mes > 12) { // Si el mes es mayor a 12
        mes = 1; // Volvemos al mes 1
        ano = ano + 1; // Aumentamos el año
      }
      if (mes == 2) { // Si el mes es febrero
        if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)) { // Si es bisiesto
          dia = dia - 29; // Restamos 29 días
        } else { // Si no es bisiesto
          dia = dia - 28; // Restamos 28 días
        }
      } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) { // Si el mes tiene 30 días
        dia = dia - 30; // Restamos 30 días
      } else { // Si el mes tiene 31 días
        dia = dia - 31; // Restamos 31 días
      }
      printf("dia: %d, mes: %d, ano: %d\n", dia, mes, ano);
    }

  Bq[indice].dia_fin_ultima_operacion = dia; // restamos 1 ya que se sumó 1 al inicio
  Bq[indice].mes_fin_ultima_operacion = mes;
  Bq[indice].ano_fin_ultima_operacion = ano;

  strcpy(Bq[indice].puertoInicio, Cl[idPuertoDestino].nombre);
  printf("Se ha guardado su selecci%cn. Traslado desde %s hasta %s \n",162, Bq[indice].puertoInicio,Cl[idPuertoDestino].nombre);
  return;
} else if (toupper(confirmarOperacion) == 'N') {
  printf("No se ha guardado esta operaci%cn.\n",162);
  return;
} else {
  printf("Opción inv%clida.\n",161);
  return;
}


    return;
  }
  if (toupper(quiereTraslado) == 'N') {
printf("¿Quiere volver al menú principal (S/N)?\n");
scanf(" %c", &volverAlMenu);
if (toupper(volverAlMenu) == 'S') {
principal(); // Regresa al menú principal
} else {
return;// Sale del programa
}

}

return;

}
else {

// El buque esta vacio y quiere cargar

 // Verificar el puerto de inicio del buque elegido y el tipo de producto que se puede cargar
for (int i = 0; i < MAX_PUERTOS; i++) {
  if (strcmp(Cl[i].nombre, Bq[indice].puertoInicio) == 0) {
  switch (Cl[i].tipo) {
   case 'Y':
    printf("Se puede cargar: FUEL \n%cDesea realizar la carga? (S/N) ",168);
    productoDisponible = 'Y';
    scanf("%s", &confirmacionCarga);
    confirmacionCarga = toupper(confirmacionCarga);
    break;
  case 'R':
    printf("Se puede cargar: Gasolina \n%cDesea realizar la carga? (S/N) ",168);
    productoDisponible = 'R';
    scanf("%s", &confirmacionCarga);
    confirmacionCarga = toupper(confirmacionCarga);
    break;
  case 'D':
    printf("Se puede cargar: Gasoil \n%cDesea realizar la carga? (S/N) ",168);
    productoDisponible = 'D';
    scanf("%s", &confirmacionCarga);
    confirmacionCarga = toupper(confirmacionCarga);
    break;
}
  }
}

if (confirmacionCarga == 'S') {
    if (productoDisponible == 'Y') {
    strcpy(Bq[indice].carga, "Crudo");
  } else if (productoDisponible == 'R' || productoDisponible == 'D') {
    strcpy(Bq[indice].carga, "Fuel");
  }
  printf("Se ha guardado su selecci%cn.\n",162);
} else if (confirmacionCarga == 'N') {
  printf("Se ha anulado el proceso de carga.\n");
} else {
  printf("Opción inválida.\n");
}

  // Pide al usuario la duración de la carga en días

  printf("Duraci%cn de la carga en d%cas?\n",162,161);
  scanf("%d", &duracionCarga);
  //Sumamos la duración de carga a la variable tiempoCargas
  sumaDuracionesCarga = Bq[indice].tiempoCargas + duracionCarga;
  Bq[indice].tiempoCargas = sumaDuracionesCarga;
   printf("Tiempo de cargas (C): %d días\n", Bq[indice].tiempoCargas);

// Pide al usuario si quiere realizar el traslado
    printf("Quiere realizar el traslado (S/N)?\n");
    scanf(" %c", &quiereTraslado);
    if (toupper(quiereTraslado) == 'S') {
    // OPCION QUIERE CARGAR Y SI QUIERE TRASLADO
    printf("Posibles puertos de inicio:\n");
    for (int i = 0; i < MAX_PUERTOS; i++) {
    if (strcmp(Bq[indice].puertoInicio, Cl[i].nombre) != 0 && strcmp(Cl[i].nombre, "") != 0) {
    printf("%d. %s ", i + 1, Cl[i].nombre);
    switch (Cl[i].tipo) {
    case 'Y':
    printf("Tipo: Yacimiento");
    break;
    case 'R':
    printf("Tipo: Refineria",161);
    break;
    case 'D':
    printf("Tipo: Dep%csito",162);
    break;
    }
    printf("\n");
    }
    }
    printf("Ingrese el n%cmero del puerto de destino:\n",163);
    scanf("%d", &idPuertoDestino);
    idPuertoDestino = idPuertoDestino - 1;//restamos 1 ya que los índices de la tabla empiezan en 0
    printf("Ingrese la duraci%cn del traslado en d%cas: ",162,161);
    scanf("%d", &duracionTraslado);

  printf("Se ha guardado su selecci%cn. Traslado desde %s hasta %s \n",162, Bq[indice].puertoInicio,Cl[idPuertoDestino].nombre);
// verificamos si el puerto de inicio puede descargar el producto
  if (Cl[idPuertoDestino].tipo == 'Y') {
    printf("No es posible realizar una descarga en un puerto de tipo Yacimiento.\n");
}
else if (Cl[idPuertoDestino].tipo == 'R') {
    if (strcmp(Bq[indice].carga, "Fuel") == 0) {
        printf("Descarga en puerto de tipo Refineria posible.\n");
    }
    else {
        printf("No es posible realizar una descarga en un puerto de tipo Refineria con una carga distinta a Fuel.\n");
    }
}
else if (Cl[idPuertoDestino].tipo == 'D') {
    if (strcmp(Bq[indice].carga, "Crudo") == 0) {
        printf("Descarga en puerto de tipo Dep%csito posible.\n",162);
    }
    else {
        printf("No es posible realizar una descarga en un puerto de tipo Depósito con una carga distinta a Crudo.\n");
    }
}

    // Pregunta al usuario si quiere realizar una descarga porque no procede en este caso

while (!descargaValida) {
    printf("Quiere realizar una descarga (S/N)?\n");
    scanf(" %c", &quiereDescargar);


    if (toupper(quiereDescargar) == 'S') {

       if (Cl[idPuertoDestino].tipo == 'Y') {
    printf("No es posible realizar una descarga en un puerto de tipo Yacimiento.\n");
}
else if (Cl[idPuertoDestino].tipo == 'R') {
    if (strcmp(Bq[indice].carga, "Fuel") == 0) {
        printf("Descarga en puerto de tipo Refineria posible.\n");
        descargaValida = 1;
        printf("Se ha descargado la carga de tipo %s en el puerto %s\n", Bq[indice].carga, Cl[idPuertoDestino].nombre);
        strcpy(Bq[indice].carga, "Vacio");

    }
    else {
        printf("No es posible realizar una descarga en un puerto de tipo Refineria con una carga distinta a crudo.\n");
    }
}
else if (Cl[idPuertoDestino].tipo == 'D') {
    if (strcmp(Bq[indice].carga, "Crudo") == 0 ) {
        printf("Descarga en puerto de tipo Depósito posible.\n");
        descargaValida = 1;
        printf("Se ha descargado la carga de tipo %s en el puerto %s\n", Bq[indice].carga, Cl[idPuertoDestino].nombre);
         strcpy(Bq[indice].carga, "Vacio");

    }
    else {
        printf("No es posible realizar una descarga en un puerto de tipo Depósito con una carga distinta a Fuel.\n");
    }
}

if (descargaValida) {
   // Pide al usuario la duración de la descarga en días
  printf("Duraci%cn de la descarga en d%cas?\n",162,161);
  scanf("%d", &duracionDescarga);

    printf("Resumen de la operaci%cn:\n",162);
    printf("================\n");
    printf("Fecha comienzo: %d/%d/%d\n", dia, mes, ano);
    printf("Puerto origen: %s\n", Bq[indice].puertoInicio);
    printf("Puerto destino: %s\n", Cl[idPuertoDestino].nombre);
    printf("Duraci%cn  carga: %d d%cas\n",162, duracionCarga,161);
    printf("Duraci%cn del traslado en d%cas: %d\n",162,161, duracionTraslado);
    printf("Duraci%cn Descarga: %d d%cas\n",162, duracionDescarga,161);
     printf("Carga del puerto: %s\n",Bq[indice].carga);
       Bq[indice].tiempoCargas = sumaDuracionesCarga;
   printf("Tiempo de cargas (C): %d días\n", Bq[indice].tiempoCargas);
    printf("Es correcta la operaci%cn (S/N)?\n",162);
     scanf(" %c", &confirmarOperacion);



   // Pide al usuario si la información del resumen es correcta
   if (toupper(confirmarOperacion) == 'S') {

      Bq[indice].dia = dia;
       Bq[indice].mes = mes;
       Bq[indice].ano = ano;
   // Actualiza la fecha de fin de la última operación del buque
  // Calcula la nueva fecha sumando los días de duración de la carga a la fecha de inicio de la operación
     dia = dia + duracionTraslado + duracionCarga + duracionDescarga;
    while (dia > 31) { // Mientras el día sea mayor a 31
      mes = mes + 1;// Aumentamos el mes
      if (mes > 12) { // Si el mes es mayor a 12
        mes = 1; // Volvemos al mes 1
        ano = ano + 1; // Aumentamos el año
      }
      if (mes == 2) { // Si el mes es febrero
        if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)) { // Si es bisiesto
          dia = dia - 29; // Restamos 29 días
        } else { // Si no es bisiesto
          dia = dia - 28; // Restamos 28 días
        }
      } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) { // Si el mes tiene 30 días
        dia = dia - 30; // Restamos 30 días
      } else { // Si el mes tiene 31 días
        dia = dia - 31; // Restamos 31 días
      }
      printf("dia: %d, mes: %d, ano: %d\n", dia, mes, ano);
    }

  Bq[indice].dia_fin_ultima_operacion = dia; // restamos 1 ya que se sumó 1 al inicio
  Bq[indice].mes_fin_ultima_operacion = mes;
  Bq[indice].ano_fin_ultima_operacion = ano;
  printf("Se ha guardado su selecci%cn. Traslado desde %s hasta %s \n",162, Bq[indice].puertoInicio,Cl[idPuertoDestino].nombre);
  strcpy(Bq[indice].puertoInicio, Cl[idPuertoDestino].nombre);
      Bq[indice].tiempoCargas = sumaDuracionesCarga;
   printf("Tiempo de cargas (C): %d días\n", Bq[indice].tiempoCargas);

  return;

}
}
    else if (toupper(quiereDescargar) == 'N') {
        descargaValida = 1; // la descarga no se realiza, pero el usuario ha ingresado una opción válida, así que cambiamos la variable de control

    printf("Traslado desde %s hasta %s\n", Bq[indice].puertoInicio,Cl[idPuertoDestino].nombre );

    printf("Resumen de la operaci%cn:\n",162);
    printf("================\n");
    printf("Fecha comienzo: %d/%d/%d\n", dia, mes, ano);
    printf("Puerto origen: %s\n", Bq[indice].puertoInicio);
    printf("Puerto destino: %s\n", Cl[idPuertoDestino].nombre);
    printf("Duraci%cn del traslado en d%cas: %d\n",162,161, duracionTraslado);
    printf("Duraci%cn  carga: %d d%cas\n",162, duracionCarga,161);
    printf("Es correcta la operaci%cn (S/N)?\n",162);
     scanf(" %c", &confirmarOperacion);


   // Pide al usuario si la información del resumen es correcta
   if (toupper(confirmarOperacion) == 'S') {
      Bq[indice].dia = dia;
       Bq[indice].mes = mes;
       Bq[indice].ano = ano;
   // Actualiza la fecha de fin de la última operación del buque
  // Calcula la nueva fecha sumando los días de duración de la carga a la fecha de inicio de la operación
     dia = dia + duracionTraslado + duracionCarga;
     printf("dia: %d\n", dia);
    while (dia > 31) { // Mientras el día sea mayor a 31
      mes = mes + 1;// Aumentamos el mes
      if (mes > 12) { // Si el mes es mayor a 12
        mes = 1; // Volvemos al mes 1
        ano = ano + 1; // Aumentamos el año
      }
      if (mes == 2) { // Si el mes es febrero
        if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)) { // Si es bisiesto
          dia = dia - 29; // Restamos 29 días
        } else { // Si no es bisiesto
          dia = dia - 28; // Restamos 28 días
        }
      } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) { // Si el mes tiene 30 días
        dia = dia - 30; // Restamos 30 días
      } else { // Si el mes tiene 31 días
        dia = dia - 31; // Restamos 31 días
      }
      printf("dia: %d, mes: %d, ano: %d\n", dia, mes, ano);
    }

  Bq[indice].dia_fin_ultima_operacion = dia; // restamos 1 ya que se sumó 1 al inicio
  Bq[indice].mes_fin_ultima_operacion = mes;
  Bq[indice].ano_fin_ultima_operacion = ano;
  printf("Se ha guardado su selecci%cn. Traslado desde %s hasta %s \n",162, Bq[indice].puertoInicio,Cl[idPuertoDestino].nombre);
  strcpy(Bq[indice].puertoInicio, Cl[idPuertoDestino].nombre);
  printf("Tiempo de cargas (C): %d días\n", Bq[indice].tiempoCargas);

  return;


}
}
 else if (toupper(confirmarOperacion) == 'N') {
  printf("No se ha guardado esta operaci%cn.\n",162);
  return;
} else {
  printf("Opción inv%clida.\n",161);
  return;
}
    }
    else {
        printf("Opción inválida. Por favor, ingrese S o N.\n");
    }
}

    }

if (toupper(quiereTraslado) == 'N') {

// Muestra el resumen de la operación al usuario
printf("Resumen de la operaci%cn:\n",162);
printf("Fecha comienzo: %d/%d/%d\n", dia, mes, ano);
printf("Puerto origen: %s\n", Bq[indice].puertoInicio);
printf("Tipo de carga: ");
switch (productoDisponible) {
  case 'Y':
    printf("FUEL");
    break;
  case 'R':
    printf("Gasolina");
    break;
  case 'D':
    printf("Gasoil");
    break;
}
printf("\n");
printf("Duraci%cn carga: %d d%cas\n",162, duracionCarga,161 );
      Bq[indice].tiempoCargas = sumaDuracionesCarga;
   printf("Tiempo de cargas (C): %d días\n", Bq[indice].tiempoCargas);
printf("Quiere confirmar la operaci%cn (S/N)?\n",162);
scanf(" %c", &confirmarOperacion);


// Pide al usuario si la información del resumen es correcta
if (toupper(confirmarOperacion) == 'S') {
   Bq[indice].dia = dia;
       Bq[indice].mes = mes;
       Bq[indice].ano = ano;
   // Actualiza la fecha de fin de la última operación del buque
  // Calcula la nueva fecha sumando los días de duración de la carga a la fecha de inicio de la operación
     dia = dia + duracionCarga;
     printf("dia: %d\n", dia);
    while (dia > 31) { // Mientras el día sea mayor a 31
      mes = mes + 1;// Aumentamos el mes
      if (mes > 12) { // Si el mes es mayor a 12
        mes = 1; // Volvemos al mes 1
        ano = ano + 1; // Aumentamos el año
      }
      if (mes == 2) { // Si el mes es febrero
        if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)) { // Si es bisiesto
          dia = dia - 29; // Restamos 29 días
        } else { // Si no es bisiesto
          dia = dia - 28; // Restamos 28 días
        }
      } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) { // Si el mes tiene 30 días
        dia = dia - 30; // Restamos 30 días
      } else { // Si el mes tiene 31 días
        dia = dia - 31; // Restamos 31 días
      }
      printf("dia: %d, mes: %d, ano: %d\n", dia, mes, ano);
    }

  Bq[indice].dia_fin_ultima_operacion = dia; // restamos 1 ya que se sumó 1 al inicio
  Bq[indice].mes_fin_ultima_operacion = mes;
  Bq[indice].ano_fin_ultima_operacion = ano;


  printf("Se ha guardado su selección.\n");
  return;
} else if (toupper(confirmarOperacion) == 'N') {
  printf("No se ha guardado esta operacion.\n");
  return;
} else {
  printf("Opción inválida.\n");
  return;
}


}

}


} else {


  // El buque ya tiene carga

printf("El buque %s est%c cargado con %s en el puerto %s\n", Bq[indice].nombre,160, Bq[indice].carga, Bq[indice].puertoInicio);

// Pide al usuario si quiere realizar el traslado
    printf("Quiere realizar el traslado (S/N)?\n");
    scanf(" %c", &quiereTraslado);
    if (toupper(quiereTraslado) == 'S') {
    printf("Posibles puertos de inicio:\n");
    for (int i = 0; i < MAX_PUERTOS; i++) {
    if (strcmp(Bq[indice].puertoInicio, Cl[i].nombre) != 0 && strcmp(Cl[i].nombre, "") != 0) {
    printf("%d. %s ", i + 1, Cl[i].nombre);
    switch (Cl[i].tipo) {
    case 'Y':
    printf("Tipo: Yacimiento");
    break;
    case 'R':
    printf("Tipo: Refineria",161);
    break;
    case 'D':
    printf("Tipo: Dep%csito",162);
    break;
    }
    printf("\n");
    }
    }
    printf("Ingrese el n%cmero del puerto de destino:\n",163);
    scanf("%d", &idPuertoDestino);
    idPuertoDestino = idPuertoDestino - 1;//restamos 1 ya que los índices de la tabla empiezan en 0
    printf("Ingrese la duraci%cn del traslado en d%cas: ",162,161);
    scanf("%d", &duracionTraslado);

  printf("Se ha guardado su selecci%cn. Traslado desde %s hasta %s \n",162, Bq[indice].puertoInicio,Cl[idPuertoDestino].nombre);
  printf("El buque tiene una carga de %s.\n", Bq[indice].carga);
  if (Cl[idPuertoDestino].tipo == 'Y') {
   printf("%s es un puerto Yacimiento",Cl[idPuertoDestino].nombre);
} else if (Cl[idPuertoDestino].tipo == 'R') {
   printf("%s es un puerto Refineria",Cl[idPuertoDestino].nombre);
} else if (Cl[idPuertoDestino].tipo == 'D') {
   printf(" %s es un puerto Deposito",Cl[idPuertoDestino].nombre);
}



  while (!descargaValida) {
          printf("Quiere realizar una descarga (S/N)?\n");
          scanf(" %c", &quiereDescargar);
        // Pide al usuario la duración de la descarga en días

         if (toupper(quiereDescargar) == 'S') {
    if (Cl[idPuertoDestino].tipo == 'Y') {
        printf("No es posible realizar una descarga en un puerto de tipo Yacimiento.\n");

    } else if (Cl[idPuertoDestino].tipo == 'R') {
        if (strcmp(Bq[indice].carga, "Crudo") == 0) {
            printf("Descarga en puerto de tipo Refineria posible.\n");
            descargaValida = 1;
            strcpy(Bq[indice].carga, "Vacio");
            printf("Se ha descargado la carga de tipo %s en el puerto %s\n", Bq[indice].carga, Cl[idPuertoDestino].nombre);
        } else {
            printf("No es posible realizar una descarga en un puerto de tipo Refineria con una carga distinta a Crudo.\n");
        }
    } else if (Cl[idPuertoDestino].tipo == 'D') {
        if (strcmp(Bq[indice].carga, "Fuel") == 0) {
            printf("Descarga en puerto de tipo Depósito posible.\n");
            descargaValida = 1;
            printf("Se ha descargado la carga de tipo %s en el puerto %s\n", Bq[indice].carga, Cl[idPuertoDestino].nombre);
            strcpy(Bq[indice].carga, "Vacio");

        } else {
            printf("No es posible realizar una descarga en un puerto de tipo Depósito con una carga distinta a Fuel.\n");
        }
    }
    if (descargaValida) {
    printf("Duraci%cn de la descarga en d%cas?\n",162,161);
        scanf("%d", &duracionDescarga);


          printf("Resumen de la operaci%cn:\n",162);
          printf("================\n");
          printf("Fecha comienzo: %d/%d/%d\n", dia, mes, ano);
          printf("Puerto origen: %s\n", Bq[indice].puertoInicio);
          printf("Puerto destino: %s\n", Cl[idPuertoDestino].nombre);
          printf("Duraci%cn del traslado en d%cas: %d\n",162,161, duracionTraslado);
          printf("Duraci%cn Descarga: %d d%cas\n",162, duracionDescarga,161);
           printf("Carga del puerto: %s\n",Bq[indice].carga);
          printf("Es correcta la operaci%cn (S/N)?\n",162);
           scanf(" %c", &confirmarOperacion);



   // Pide al usuario si la información del resumen es correcta
   if (toupper(confirmarOperacion) == 'S') {
   // Actualiza la fecha de fin de la última operación del buque
  // Calcula la nueva fecha sumando los días de duración de la carga a la fecha de inicio de la operación
     dia = dia + duracionTraslado + duracionDescarga;
     printf("dia: %d\n", dia);
    while (dia > 31) { // Mientras el día sea mayor a 31
      mes = mes + 1;// Aumentamos el mes
      if (mes > 12) { // Si el mes es mayor a 12
        mes = 1; // Volvemos al mes 1
        ano = ano + 1; // Aumentamos el año
      }
      if (mes == 2) { // Si el mes es febrero
        if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)) { // Si es bisiesto
          dia = dia - 29; // Restamos 29 días
        } else { // Si no es bisiesto
          dia = dia - 28; // Restamos 28 días
        }
      } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) { // Si el mes tiene 30 días
        dia = dia - 30; // Restamos 30 días
      } else { // Si el mes tiene 31 días
        dia = dia - 31; // Restamos 31 días
      }
      printf("dia: %d, mes: %d, ano: %d\n", dia, mes, ano);
    }

  Bq[indice].dia_fin_ultima_operacion = dia; // restamos 1 ya que se sumó 1 al inicio
  Bq[indice].mes_fin_ultima_operacion = mes;
  Bq[indice].ano_fin_ultima_operacion = ano;
  printf("Se ha guardado su selecci%cn. Traslado desde %s hasta %s \n",162, Bq[indice].puertoInicio,Cl[idPuertoDestino].nombre);
  strcpy(Bq[indice].puertoInicio, Cl[idPuertoDestino].nombre);
  return;

}
    }


         if (toupper(quiereDescargar) == 'N') {

              // la descarga no se realiza, pero el usuario ha ingresado una opción válida, así que cambiamos la variable de control
          descargaValida = 1;
          printf("Traslado desde %s hasta %s\n", Bq[indice].puertoInicio,Cl[idPuertoDestino].nombre );

          printf("Resumen de la operaci%cn:\n",162);
          printf("================\n");
          printf("Fecha comienzo: %d/%d/%d\n", dia, mes, ano);
          printf("Puerto origen: %s\n", Bq[indice].puertoInicio);
          printf("Puerto destino: %s\n", Cl[idPuertoDestino].nombre);
          printf("Duraci%cn del traslado en d%cas: %d\n",162,161, duracionTraslado);
          printf("Es correcta la operaci%cn (S/N)?\n",162);
           scanf(" %c", &confirmarOperacion);


         // Pide al usuario si la información del resumen es correcta
         if (toupper(confirmarOperacion) == 'S') {
           Bq[indice].dia = dia;
       Bq[indice].mes = mes;
       Bq[indice].ano = ano;

         // Actualiza la fecha de fin de la última operación del buque
        // Calcula la nueva fecha sumando los días de duración de la carga a la fecha de inicio de la operación
           dia = dia + duracionTraslado;
           printf("dia: %d\n", dia);
          while (dia > 31) { // Mientras el día sea mayor a 31
            mes = mes + 1;// Aumentamos el mes
            if (mes > 12) { // Si el mes es mayor a 12
              mes = 1; // Volvemos al mes 1
              ano = ano + 1; // Aumentamos el año
            }
            if (mes == 2) { // Si el mes es febrero
              if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)) { // Si es bisiesto
                dia = dia - 29; // Restamos 29 días
              } else { // Si no es bisiesto
                dia = dia - 28; // Restamos 28 días
              }
            } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) { // Si el mes tiene 30 días
              dia = dia - 30; // Restamos 30 días
            } else { // Si el mes tiene 31 días
              dia = dia - 31; // Restamos 31 días
            }
            printf("dia: %d, mes: %d, ano: %d\n", dia, mes, ano);
          }

        Bq[indice].dia_fin_ultima_operacion = dia; // restamos 1 ya que se sumó 1 al inicio
        Bq[indice].mes_fin_ultima_operacion = mes;
        Bq[indice].ano_fin_ultima_operacion = ano;
        printf("Se ha guardado su selecci%cn. Traslado desde %s hasta %s \n",162, Bq[indice].puertoInicio,Cl[idPuertoDestino].nombre);
        strcpy(Bq[indice].puertoInicio, Cl[idPuertoDestino].nombre);

        return;


      }
      }

   else if (toupper(confirmarOperacion) == 'N') {
    printf("No se ha guardado esta operaci%cn.\n",162);
    return;
  } else {
    printf("Opción inv%clida.\n",161);
    return;
  }
      }
      else {
          printf("Opción inválida. Por favor, ingrese S o N.\n");
      }




  }



      }

if (toupper(quiereTraslado) == 'N') {

   printf("El buque tiene una carga de %s.\n", Bq[indice].carga);
// Recorre el arreglo de puertos
for (int i = 0; i < MAX_PUERTOS; i++) {
  // Compara el nombre del puerto de inicio del buque con cada nombre de puerto
  if (strcmp(Bq[indice].puertoInicio, Cl[i].nombre) == 0) {
    // Si encuentra una coincidencia, obtiene el tipo de puerto
    tipoPuertoInicio = Cl[i].tipo;
    printf("El tipo de puerto de inicio es: %c\n", tipoPuertoInicio);
  }
}

 while (!descargaValida) {
          printf("Quiere realizar una descarga (S/N)?\n");
          scanf(" %c", &quiereDescargar);
        // Pide al usuario la duración de la descarga en días

          if (toupper(quiereDescargar) == 'S') {

             if (tipoPuertoInicio == 'Y') {
          printf("No es posible realizar una descarga en un puerto de tipo Yacimiento.\n");
      }
      else if (tipoPuertoInicio == 'R') {
          if (strcmp(Bq[indice].carga, "Crudo") == 0) {
              printf("Descarga en puerto de tipo Refineria posible.\n");
              printf("Se ha descargado la carga de tipo %s en el puerto %s\n", Bq[indice].carga, Bq[indice].puertoInicio);
              strcpy(Bq[indice].carga, "Vacio");
              descargaValida = 1;

          }
          else {
              printf("No es posible realizar una descarga en un puerto de tipo Refineria con una carga distinta a Crudo.\n");
          }
      }
      else if (tipoPuertoInicio == 'D') {
          if (strcmp(Bq[indice].carga, "Fuel") == 0) {
              printf("Descarga en puerto de tipo Depósito posible.\n");
              descargaValida = 1;
              printf("Se ha descargado la carga de tipo %s en el puerto %s\n", Bq[indice].carga, Bq[indice].puertoInicio);
              strcpy(Bq[indice].carga, "Vacio");

          }
          else {
              printf("No es posible realizar una descarga en un puerto de tipo Depósito con una carga distinta a Fuel.\n");
          }

      }

  // Pide al usuario la duración de la descarga en días


  printf("Duraci%cn de la descarga en d%cas?\n",162,161);
  scanf("%d", &duracionDescarga);

    printf("Resumen de la operaci%cn:\n",162);
    printf("================\n");
    printf("Fecha comienzo: %d/%d/%d\n", dia, mes, ano);
    printf("Puerto origen: %s\n", Bq[indice].puertoInicio);
    printf("Duraci%cn Descarga: %d d%cas\n",162, duracionDescarga,161);
    printf("Es correcta la operaci%cn (S/N)?\n",162);
     scanf(" %c", &confirmarOperacion);


   // Pide al usuario si la información del resumen es correcta
   if (toupper(confirmarOperacion) == 'S') {
     Bq[indice].dia = dia;
       Bq[indice].mes = mes;
       Bq[indice].ano = ano;
   // Actualiza la fecha de fin de la última operación del buque
  // Calcula la nueva fecha sumando los días de duración de la carga a la fecha de inicio de la operación
     dia = dia + duracionDescarga;
    while (dia > 31) { // Mientras el día sea mayor a 31
      mes = mes + 1;// Aumentamos el mes
      if (mes > 12) { // Si el mes es mayor a 12
        mes = 1; // Volvemos al mes 1
        ano = ano + 1; // Aumentamos el año
      }
      if (mes == 2) { // Si el mes es febrero
        if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)) { // Si es bisiesto
          dia = dia - 29; // Restamos 29 días
        } else { // Si no es bisiesto
          dia = dia - 28; // Restamos 28 días
        }
      } else if (mes == 4 || mes == 6 || mes == 9 || mes == 11) { // Si el mes tiene 30 días
        dia = dia - 30; // Restamos 30 días
      } else { // Si el mes tiene 31 días
        dia = dia - 31; // Restamos 31 días
      }
      printf("dia: %d, mes: %d, ano: %d\n", dia, mes, ano);
    }

  Bq[indice].dia_fin_ultima_operacion = dia; // restamos 1 ya que se sumó 1 al inicio
  Bq[indice].mes_fin_ultima_operacion = mes;
  Bq[indice].ano_fin_ultima_operacion = ano;

return;
}

}


else if (toupper(quiereDescargar) == 'N') {
printf("No se realizará ninguna descarga.\n");
descargaValida = 1;
}
else {
printf("Opción no válida.\n");
}
}

}








}


}
