#pragma once

const int MAX_PUERTOS=10;
const int MAX_NOMBRE=200;
const int MAX_BUQUES=5;

typedef enum TipoDia{	//Creamos un nuevo tipo de dato con los dias de la semana
  Lunes,Martes,Miercoles,Jueves,Viernes,Sabado,Domingo
};


typedef struct tPuerto{
  int num;
  char nombre[MAX_NOMBRE];
  char tipo;
  int idPuertoDestino;
  bool cargable;
  char productoDisponible[40];
};

typedef struct tBuque{
  char id;
  char nombre[MAX_NOMBRE];
  char puertoInicio[MAX_NOMBRE];
  int dia;
  int mes;
  int ano;
  char carga[MAX_NOMBRE];
  int dia_fin_ultima_operacion;
  int mes_fin_ultima_operacion;
  int ano_fin_ultima_operacion;
  int duracionCarga;
  int duracionTraslado;
  int duracionDescarga;
  int tiempoCargas;





};

typedef tPuerto puertos[MAX_PUERTOS];
typedef tBuque buques[MAX_BUQUES];
