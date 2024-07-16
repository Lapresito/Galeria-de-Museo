/*
  Módulo de definición de 'TPersona'.

  Los elementos de tipo TPersona son elementos que almacenan un id, una descripción y una fecha.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */
#ifndef PERSONA_H
#define PERSONA_H

#include <string.h>

#include "fecha.h"

// Constante para definir el largo máximo de la nombre y apellido de una persona
const int MAX_NOMBRE = 100;
const int MAX_APELLIDO = 100;

// Define el tipo TPersona como un puntero a rep_persona
typedef struct rep_persona *TPersona;

// Función que crea un elemento de tipo TPersona con los valores dados
TPersona crearTPersona(int cedula, const char nombre[MAX_NOMBRE], char apellido[MAX_APELLIDO], TFecha fecha);

//Función que retorna el nombre de la persona
void nombrePersona(TPersona persona, char nombre[MAX_NOMBRE]);

//Funcion que retorna el apellido de la persona
void apellidoPersona(TPersona persona, char apellido[MAX_APELLIDO]);

// Función que libera la memoria asignada para una persona
// Debe liberar también la memoria de la fecha asociada
void liberarTPersona(TPersona &persona);

// Función que retorna la cédula de la persona
int cedulaTPersona(TPersona persona);

//Función que retorna la fecha de nacimiento de la persona
TFecha fechaNacimientoTPersona(TPersona persona);

// Función que imprime la información de la persona en el siguiente formato:
// Persona <nombre> <apellido>
// Cédula: <cedula>
// Fecha de nacimiento: <fecha>
void imprimirTPersona(TPersona persona);

// Función que retorna true si persona1 es mas joven que persona2 y false en caso contrario
bool esMasJoven(TPersona persona1, TPersona persona2);




#endif  // PERSONA_H