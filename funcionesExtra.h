#pragma once
#include "estructuras.h"
#include "utilidades.h"

bool esFechaValida(int dia, int mes, int ano);
void LeerFecha(int & mes, int & anno);
int CalcularBisiestos(int & mes, int & anno);
int CalcularAnnos(int & anno);
int CalcularDias(int & mes);
TipoDia DiaDeLaSemana(int & incrementoDias);
void ImprimirCalendario(int & mes, int & anno, TipoDia diaSemana);
void salir();
