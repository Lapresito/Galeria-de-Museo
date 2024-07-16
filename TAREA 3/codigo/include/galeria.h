/*
  Módulo de definición de 'TGaleria'.

  Los elementos de tipo TGaleria contiene las estructuras necesarias para manejar la galeria.
  Un tipo Galeria tiene:
    - Una ColeccionPiezas con las piezas de la galeria
    - Una Fecha que representa la fecha actual.
    - Una lista de exposiciones finalizadas.
    - Una lista de exposiciones activas.
    - Una lista de exposiciones futuras.
  
  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */
#ifndef GALERIA_H
#define GALERIA_H
#include "coleccionPiezas.h"
#include "listaExposiciones.h"

typedef struct rep_galeria* TGaleria;

// Crea una galeria sin piezas ni exposiciones, con la fecha marcada por parámetro.
TGaleria crearTGaleria(TFecha fecha);

// Agrega la pieza a la galeria. La pieza hasta el momento no 
// Ejecuta en O(n) peor caso, donde ne es la cantidad de piezas de la galeria.
// PRE: no existe una pieza con mismo id en la galeria.
void agregarPiezaTGaleria(TGaleria galeria, TPieza pieza);

// Agrega la exposición a la galería.
// PRE: esCompatibleExposicionGaleria
void agregarExposicionTGaleria(TGaleria galeria, TExposicion expo);

// Agrega la pieza de id 'idPieza' a la exposición con id 'idExpo'
// PRE: existen una pieza en la galeria con id 'idPieza'
// PRE: existe una exposición en la galeria con id 'idExpo'
void agregarPiezaAExposicionTGaleria(TGaleria galeria, int idPieza, int idExpo);

// Realiza la modificación lógica de la fecha. Modifica la fecha
// de la galería y las listas de exposiciones para reflejar cuáles están finalizadas, 
// cuáles activas y cuáles siguen siendo futuras.
// PRE: la fecha parámetro es posterior a la fecha actual de la galeria
void avanzarAFechaTGaleria(TGaleria galeria, TFecha fecha);

// Imprime las exposiciones finalizadas.
// La función es O(n) donde n es el número de exposiciones finalizadas.
void imprimirExposicionesFinalizadasTGaleria(TGaleria galeria);

// Imprime las exposiciones activas.
// La función es O(n) donde n es el número de exposiciones activas.
void imprimirExposicionesActivasTGaleria(TGaleria galeria);

// Imprime las exposiciones futuras.
// La función es O(n) donde n es el número de exposiciones futuras.
void imprimirExposicionesFuturasTGaleria(TGaleria galeria);

// Devuelve true si la exposicion 'expo' es compatible con el resto de las exposiciones de la galeria
bool esCompatibleExposicionTGaleria(TGaleria galeria, TExposicion expo);

// Libera la memoria utilizada por la galeria
// También libera la memoria de todas las piezas y exposiciones en la galeria.
void liberarTGaleria(TGaleria &galeria);

#endif  // EXPOSICION_H