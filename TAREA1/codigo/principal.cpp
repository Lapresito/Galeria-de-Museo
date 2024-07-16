/*
  Módulo principal de la Tarea 1.

Intérprete de comandos para probar los módulos implementados.

Cada comando tiene un nombre y una secuencia (posiblemente vacía) de parámetros.
Se asume que los comandos están bien formados. Esto implica que:
- el nombre es uno de los descritos más abajo;
- la cantidad y tipo de los parámetros cumplen con lo requerido.

El comando 'Fin' termina el programa

El comando '# comentario' imprime comentario.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
*/

#define cmd_es(nom_comando, cmd) (0 == strcmp(nom_comando, cmd))

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "include/grupo.h"

#define MAX_PALABRA 32
#define MAX_LINEA 256



///////////////////////////////
/* Funciones main para Fecha */
///////////////////////////////

// Lee una fecha de la entrada en formato "dd/mm/aaaa" y la escribe la variable fecha
void leerFecha(TFecha &fecha);
void main_crearFecha(TFecha &fecha);
void main_liberarFecha(TFecha &fecha);
void main_imprimirFecha(TFecha fecha);
void main_aumentarDias(TFecha &fecha);
void main_compararFechas();

/////////////////////////////////
/* Funciones main para Personas */
/////////////////////////////////
void main_crearPersona(TPersona &persona, TFecha & nacimiento);
void main_imprimirCiPersona(TPersona persona);
void main_imprimirFechaPersona(TPersona persona);
void main_imprimirNombreYApellidoPersona(TPersona persona);
void main_imprimirPersona(TPersona persona);
void main_esMasJovenPersona(TPersona persona1);
void main_liberarPersona(TPersona &persona);


////////////////////////////////
/* Funciones main para Grupo */
////////////////////////////////
void main_crearGrupo(TGrupo &grupo);
void main_agregarAGrupo(TGrupo &grupo, TPersona &persona);
void main_imprimirGrupo(TGrupo grupo);
void main_liberarGrupo(TGrupo &grupo);
void main_estaEnGrupo(TGrupo grupo);
void main_imprimirPersonasFecha(TGrupo grupo);
void main_hayPersonasFecha(TGrupo grupo);
void main_removerDeGrupo(TGrupo &grupo);

// programa principal que lee comandos de la entrada estándar e invoca a la función de test correspondiente
int main() {
    TFecha fecha = NULL;
    TPersona persona = NULL;
    TGrupo grupo = NULL;

    char restoLinea[MAX_LINEA + 1];
    char cmd[MAX_PALABRA];

    int cont_comandos = 0;
    bool seguir = true;
    while (seguir) {
        // mostrar el prompt
        cont_comandos++;
        printf("%u>", cont_comandos);

        // leer el comando en la variable cmd
        leerChars(cmd);

        // procesar el comando
        if (cmd_es("Fin", cmd)) {  // Termina el programa
            seguir = false;
            printf("Fin.\n");

        } else if (cmd_es("#", cmd)) {  // Imprime el comentario luego del #
            leerRestoLinea(restoLinea);
            printf("# %s.\n", restoLinea);

            ///////////////////////////////////
            /* Funciones para testear fecha */
            ///////////////////////////////////

        } else if (cmd_es("crearFecha", cmd)) {  // Crea una fecha y la almacena en la variable fecha
            main_crearFecha(fecha);

        } else if (cmd_es("imprimirFecha", cmd)) {  // Imprime la fecha almacenada en la variable fecha
            main_imprimirFecha(fecha);

        } else if (cmd_es("liberarFecha", cmd)) {  // Libera la memoria de la variable fecha
            main_liberarFecha(fecha);

        } else if (cmd_es("aumentarDias", cmd)) {  // Aumenta la fecha almacenada en la variable fecha en la cantidad de días indicada
            main_aumentarDias(fecha);

        } else if (cmd_es("compararFechas", cmd)) {  // Compara dos fechas leidas de la entrada
            main_compararFechas();

            ///////////////////////////////////
            /* Funciones para testear persona */
            ///////////////////////////////////

        } else if (cmd_es("crearPersona", cmd)) {  // Crea una persona y la almacena en la variable persona
            main_crearPersona(persona, fecha);
			fecha = NULL;
        } else if (cmd_es("imprimirCiPersona", cmd)) {  // Imprime la ci de la persona almacenada en la variable persona
            main_imprimirCiPersona(persona);

        } else if (cmd_es("imprimirFechaPersona", cmd)) {  // Imprime la fecha de nacimiento de la persona almacenada en la variable persona
            main_imprimirFechaPersona(persona);

        } else if (cmd_es("imprimirNombreYApellidoPersona",cmd)){ // Imprime nombre y apellido de la persona almacenada en la variable persona    
            main_imprimirNombreYApellidoPersona(persona);

        } else if (cmd_es("imprimirPersona", cmd)) {  // Imprime toda la infromación de la persona almacenada en la variable persona
            main_imprimirPersona(persona);

        } else if (cmd_es("liberarPersona", cmd)) {  // Libera la memoria de la persona almacenada en la variable persona
            main_liberarPersona(persona);

        } else if (cmd_es("esMasJovenPersona", cmd)) {  // Evalúa si la persona almacenada en persona es más joven que la ingresada
            main_esMasJovenPersona(persona);

            ///////////////////////////////////
            /* Funciones para testear grupo */
            ///////////////////////////////////

        } else if (cmd_es("crearGrupo", cmd)) {  // Crea un grupo y la almacena en la variable grupo
            main_crearGrupo(grupo);

        } else if (cmd_es("agregarAGrupo", cmd)) {  // Agrega la persona almacenada en la variable persona al grupo almacenado en la variable grupo
            main_agregarAGrupo(grupo, persona);
			persona = NULL;
        } else if (cmd_es("imprimirGrupo", cmd)) {  // Imprime toda la información del grupo almacenado en la variable grupo
            main_imprimirGrupo(grupo);

        } else if (cmd_es("liberarGrupo", cmd)) {  // Libera la memoria del grupo almacenado en la variable grupo
            main_liberarGrupo(grupo);

        } else if (cmd_es("estaEnGrupo", cmd)) {  // Indica si el grupo almacenado en la variable grupo tiene a la persona con ci ingresada
            main_estaEnGrupo(grupo);

        } else if(cmd_es("imprimirPersonasFecha", cmd)){ //Imprime las personas pertenecientes al grupo que tengan la fecha de nacimiento ingresada
            main_imprimirPersonasFecha(grupo);

        } else if (cmd_es("hayPersonasFecha", cmd)) {  // Indica si hay personas en el  grupo en una fecha indicada
            main_hayPersonasFecha(grupo);

        } else if (cmd_es("removerDeGrupo", cmd)) {  // Remueve la persona con la cédula ingresada de la variable grupo
            main_removerDeGrupo(grupo);

        } else {
            printf("Comando no reconocido.\n");  // Comando no reconocido

        }  // if
        fgets(restoLinea, MAX_LINEA + 1, stdin);
    }  // while

    return 0;
}  // main

///////////////////////////////
/* Funciones main para Fecha */
///////////////////////////////

void leerFecha(TFecha &fecha) {
    nat *componentes = new nat[3];
    scanf("%u/%u/%u", &componentes[0], &componentes[1], &componentes[2]);
    fecha = crearTFecha(componentes[0], componentes[1], componentes[2]);
    delete[] componentes;
}

void main_crearFecha(TFecha &fecha) {
    assert(fecha == NULL);
    leerFecha(fecha);
    // printf("La fecha fue definida en forma exitosa.\n");
}

void main_liberarFecha(TFecha &fecha) {
    if (fecha != NULL){
		liberarTFecha(fecha);
	}
}

void main_imprimirFecha(TFecha fecha) {
    assert(fecha != NULL);
    imprimirTFecha(fecha);
}

void main_aumentarDias(TFecha &fecha) {
    assert(fecha != NULL);
    nat cantDias = leerNat();
    aumentarTFecha(fecha, cantDias);
    printf("La nueva fecha aplazada %d dias es: ", cantDias);
    imprimirTFecha(fecha);
}

void main_compararFechas() {
    TFecha fecha1 = NULL, fecha2 = NULL;
    leerFecha(fecha1);
    leerFecha(fecha2);
    int comp = compararTFechas(fecha1, fecha2);
    if (comp == 0) {
        printf("Las fechas son iguales. \n");
    } else if (comp == 1) {
        printf("La primera fecha es posterior a la segunda. \n");
    } else
        printf("La primera fecha es anterior a la segunda. \n");
    liberarTFecha(fecha1);
    liberarTFecha(fecha2);
}

/////////////////////////////////
/* Funciones main para Personas */
/////////////////////////////////


void main_crearPersona(TPersona &persona, TFecha & nacimiento){
    assert(persona == NULL && nacimiento != NULL);
    int cedula = leerNat();
    char nombre[MAX_NOMBRE];
    leerChars(nombre);
    char apellido[MAX_APELLIDO];
    leerChars(apellido);
    persona = crearTPersona(cedula, nombre, apellido, nacimiento);
    printf("Persona creada de forma exitosa.\n");
}



void main_imprimirCiPersona(TPersona persona) {
    assert(persona != NULL);
    printf("La ci de la persona es: %d\n", cedulaTPersona(persona));
}

void main_imprimirFechaPersona(TPersona persona) {
    assert(persona != NULL);
    TFecha fecha = fechaNacimientoTPersona(persona);
    assert(fecha != NULL);
    printf("La fecha de nacimiento de la persona es: ");
    imprimirTFecha(fecha);
}

void main_imprimirNombreYApellidoPersona(TPersona persona){
    assert(persona != NULL);
    char nombre[MAX_NOMBRE];
    char apellido[MAX_APELLIDO];
    nombrePersona(persona,nombre);
    apellidoPersona(persona,apellido);
    printf("El nombre de la persona es: %s\n",nombre);
    printf("El apellido de la persona es: %s\n",apellido);
}

void main_imprimirPersona(TPersona persona) {
    assert(persona != NULL);
    imprimirTPersona(persona);
}

void main_esMasJovenPersona(TPersona persona1) {
    assert(persona1 != NULL);
    TFecha fecha = NULL;
    leerFecha(fecha);
    TPersona persona2 = NULL;
    main_crearPersona(persona2,fecha);

    char nombre[MAX_NOMBRE];
    char nombre2[MAX_NOMBRE];
    nombrePersona(persona1,nombre);
    nombrePersona(persona2,nombre2);
    
    if(esMasJoven(persona1, persona2))
        printf("%s tiene menor edad que %s\n",nombre,nombre2);
    else
        printf("%s tiene mayor edad que %s\n",nombre,nombre2);    

    main_liberarPersona(persona2);
}

void main_liberarPersona(TPersona &persona) {
    if (persona != NULL){
		liberarTPersona(persona);
	}
}

////////////////////////////////
/* Funciones main para Grupo */
////////////////////////////////

void main_crearGrupo(TGrupo &grupo) {
    assert(grupo == NULL);
    grupo = crearTGrupo();
    printf("El grupo ha sido creado de forma exitosa.\n");
}

void main_agregarAGrupo(TGrupo &grupo, TPersona &persona) {
    assert(grupo != NULL && persona != NULL);
    agregarAGrupo(grupo, persona);
    persona = NULL;
    printf("Se ha agregado la persona al grupo de forma exitosa.\n");
}

void main_imprimirGrupo(TGrupo grupo) {
    assert(grupo != NULL);
    imprimirTGrupo(grupo);
}

void main_liberarGrupo(TGrupo &grupo) {
    if (grupo != NULL){
		liberarTGrupo(grupo);
		printf("Se ha borrado el grupo en forma exitosa.\n");
	}
}

void main_estaEnGrupo(TGrupo grupo) {
    assert(grupo != NULL);
    nat ci = leerNat();
    if (estaEnGrupo(grupo, ci))
        printf("La persona con ci %i está en el grupo.\n", ci);
    else
        printf("La persona con ci %i NO está en el grupo.\n", ci);
}

void main_imprimirPersonasFecha(TGrupo grupo) {
    assert(grupo != NULL);
    TFecha fecha = NULL;
    leerFecha(fecha);

    imprimirPersonasFecha(grupo, fecha);

    liberarTFecha(fecha);
}

void main_hayPersonasFecha(TGrupo grupo) {
    assert(grupo != NULL);
    TFecha fecha = NULL;
    leerFecha(fecha);

    if (hayPersonasFecha(grupo, fecha))
        printf("Se encontraron personas en la fecha determinada.\n");
    else
        printf("No se encontraron personas en la fecha determinada.\n");

    liberarTFecha(fecha);
}



void main_removerDeGrupo(TGrupo &grupo) {
    assert(grupo != NULL);
    nat ci = leerNat();
    if (estaEnGrupo(grupo, ci)) {
        removerDeGrupo(grupo, ci);
        printf("La persona con ci %i se removió del grupo.\n", ci);
    } else
        printf("La persona con ci %i NO está en el grupo.\n", ci);
}
