/*
  Módulo de definición de 'TVisitaDia'.

  Los elementos de tipo TVisitaDia almacenan una coleccion de elementos de tipo TVisitante y una fecha.
  Representan los diferentes grupos que van llegando en un mismo día.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */
#ifndef VISITADIA_H
#define VISITADIA_H
#include "grupoABB.h"
#include "pieza.h"

// Define el tipo TVisitaDia como un puntero a rep_visitadia
typedef struct rep_visitadia *TVisitaDia;

// Función para crear un elemento de tipo TVisitaDia.
// La función es O(1) peor caso.
TVisitaDia crearTVisitaDia(TFecha fecha);

// Agrega un grupo al inicio de la visita dia.
// La función es O(1) peor caso.
void encolarGrupoTVisitaDia(TVisitaDia &visitaDia, TGrupoABB grupo);

// Devuelve la cantidad de grupos en la visita dia.
// La función es O(1) peor caso.
int cantidadGruposTVisitaDia(TVisitaDia visitaDia);

// Imprime la visita dia con el siguiente formato: 
//   Visita para dia: <fecha>
//   <imprimir secuencialmente con imprimirTGrupoABB en cada grupo>
// La función es O(n * m), donde n es el número de grupos en la visita dia
// y m es la máxima cantidad de visitantes entre los grupos.
void imprimirVisitaDia(TVisitaDia visitaDia);

// Retira el último grupo de la visita dia y lo regresa.
// La función es O(1) peor caso.
// PRE: cantidadVisitantesTVisitaDia > 0
TGrupoABB desencolarGrupoTVisitaDia(TVisitaDia &visitaDia);

// Función que libera la memoria asignada para la visita dia.
// Deja el puntero visitaDia apuntando a NULL.
// Ejecuta en O(n) peor caso, donde n es la cantidad de grupos 
// en la visitaDia.
void liberarTVisitaDia(TVisitaDia &visitaDia);

#endif // VISITADIA_H  
