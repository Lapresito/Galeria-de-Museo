/*
  Módulo de definición de 'TFecha'.

  Los elementos de tipo TFecha son elementos que almacenan una fecha.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */
#ifndef _FECHA_H_
#define _FECHA_H_

#include "utils.h"

// Definición de tipo TFecha como puntero a una estructura rep_fecha
typedef struct rep_fecha *TFecha;

// Función para crear un nuevo elemento de tipo TFecha con una fecha dada
TFecha crearTFecha(nat dia, nat mes, nat anio);

// Función para liberar un elemento de tipo TFecha previamente creado
void liberarTFecha(TFecha &fecha);

// Función para imprimir una fecha representada por un elemento de tipo TFecha
// en el formato "dd/mm/aaaa"
void imprimirTFecha(TFecha fecha);

// Función para aumentar una fecha en una cantidad dada de días
void aumentarTFecha(TFecha &fecha, nat dias);

// Función para comparar dos fechas representadas por elementos de tipo TFecha
// Si fecha1 es mayor que fecha2 retorna 1, si es menor retorna -1,
// si son iguales retorna 0
int compararTFechas(TFecha fecha1, TFecha fecha2);

#endif  // _FECHA_H_