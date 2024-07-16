#include "../include/grupo.h"

struct rep_grupo {
    /************ Parte 5.1 ************/
    /*Escriba el código a continuación */
    TPersona grupo[MAX_PERSONAS];
    int tope;
    /****** Fin de parte Parte 5.1 *****/
};


TGrupo crearTGrupo(){
    TGrupo grupo = NULL;
    /************ Parte 5.2 ************/
    /*Escriba el código a continuación */
    grupo = new rep_grupo;
    grupo->tope = 0;
    /****** Fin de parte Parte 5.2 *****/
    return grupo;
}


// Funcion auxiliar para intercambiar personas
void intercambio(TPersona& persona1,TPersona& persona2){
    TPersona aux;
    aux = persona1;
    persona1 = persona2;
    persona2 = aux;

}
// Ordenamiento por insercion

// Función para agregar una persona a un grupo
// Recibe un elemento de tipo TGrupo y un elemento de tipo TPersona y lo agrega al grupo en orden por fecha de nacimiento (de menor a mayor)
// Si dos personas tienen la misma fecha de nacimiento, deben ordenarse por orden de ingreso al grupo, de más nuevo a más antiguo
// Si la cantidad de personas en el grupo es igual a MAX_PERSONAS, la función no tiene efecto
void agregarAGrupo(TGrupo& grupo, TPersona persona){
    /************ Parte 5.2 ************/
    /*Escriba el código a continuación */
    if (grupo->tope < MAX_PERSONAS) {
        // si esta lleno no ejecuta
        if(grupo->tope == 0){
            grupo->tope++;
            grupo->grupo[0]= persona;
        }else{
            // tope mayor 0 
            grupo->grupo[grupo->tope]= persona;
            // ordeno con algoritmo
            int i = grupo->tope;
            while ( (i > 0 )  &&  (compararTFechas(fechaNacimientoTPersona(grupo->grupo[i]) , fechaNacimientoTPersona(grupo->grupo[i -1 ]) )  == - 1 || compararTFechas( fechaNacimientoTPersona(grupo->grupo[i]) , fechaNacimientoTPersona(grupo->grupo[i -1 ])  )  == 0)){
                intercambio(grupo->grupo[i],grupo->grupo[ i - 1 ]);
                i--;
            }

            grupo->tope++;
        }
    }
    /****** Fin de parte Parte 5.2 *****/
}


// Función para imprimir todas las personas de un grupo
// Recibe un elemento de tipo TGrupo e imprime sus personas en orden cronológico
// El formato en el que se debe imprimir el grupo es utilizando de forma secuencial la función imprimirTPersona
// Si el grupo está vacío no imprime nada
void imprimirTGrupo(TGrupo grupo){
    /************ Parte 5.2 ************/
    /*Escriba el código a continuación */
    for (int i=0 ; i < grupo->tope ; i++){
        imprimirTPersona(grupo->grupo[i]);
    }
    /****** Fin de parte Parte 5.2 *****/
}

// Función para liberar un grupo
// Recibe una referencia a un elemento de tipo TGrupo y libera su memoria
// Libera además la memoria de cada una de las personas en el grupo
void liberarTGrupo(TGrupo& grupo){
   /************ Parte 5.2 ************/
    /*Escriba el código a continuación */
    if(grupo != NULL) {
        for(int i=0; i < grupo->tope; i++){
        liberarTPersona(grupo->grupo[i]);
        }
    }
    delete grupo;
    grupo = NULL;
    /****** Fin de parte Parte 5.2 *****/
}

// Función para verificar si un elemento de tipo TPersona existe en un grupo
// Recibe un grupo y la cédula de la persona y regresa un booleano indicando su existencia
bool estaEnGrupo(TGrupo grupo, int cedula){
    bool esta = false;
	/************ Parte 5.3 ************/
    /*Escriba el código a continuación */
    int i = 0;
    while (i < grupo->tope && (cedulaTPersona(grupo->grupo[i]) !=  cedula)) {
        i++;
    }
    if(i < grupo->tope) {
        esta = true;
    }
    /****** Fin de parte Parte 5.3 *****/
	return esta;
}

// Esta función remueve la persona con ci "cedula" del grupo "grupo"
void removerDeGrupo(TGrupo &grupo, int cedula){
    /************ Parte 5.4 ************/
    /*Escriba el código a continuación */
    if(estaEnGrupo(grupo, cedula)){
        int i = 0;
        while ( i < grupo->tope && (cedulaTPersona(grupo->grupo[i]) !=  cedula)) {
            i++;
        }
        if(i < grupo->tope) {
            liberarTPersona(grupo->grupo[i]);
            // correr todos los elementos un lugar hacia atras
             for (int j = i; j < grupo->tope - 1; j++) {
                grupo->grupo[j] = grupo->grupo[j + 1];
            }
        }
        grupo->tope--;
    }

    /****** Fin de parte Parte 5.4 *****/   
}

// Función para verificar si hay, al menos, una persona en el grupo que tenga la fecha de nacimiento "fecha"
// Debe implementarse utilizando búsqueda binaria
bool hayPersonasFecha(TGrupo grupo, TFecha fecha){
    bool hay = false;
    /************ Parte 5.5 ************/
    /*Escriba el código a continuación */
    //Busqueda binaria
    int primero = 0;
    int ultimo = grupo->tope - 1;
    while(primero<=ultimo && !hay){
        int medio = (primero+ultimo)/2;
        if(compararTFechas(fechaNacimientoTPersona(grupo->grupo[medio]), fecha) == 0){
            hay = true;
        }else{
            if(compararTFechas(fechaNacimientoTPersona(grupo->grupo[medio]), fecha) == 1){
                ultimo = medio - 1;
            }else{
                primero = medio + 1;
            }
        }
    }
// Codigo sin binaria
    // while ((i < grupo->tope) && (compararTFechas(fechaNacimientoTPersona(grupo->grupo[i]) , fecha ) != 0)) {
    //     i++;
    // }
    // if(i < grupo->tope) {
    //     hay = true;
    // }
    /****** Fin de parte Parte 5.5 *****/ 
    return hay;
}

// Imprime en pantalla las personas del grupo que tengan la fecha de nacimiento "fecha" 
void imprimirPersonasFecha(TGrupo grupo, TFecha fecha){
    /************ Parte 5.5 ************/
    /*Escriba el código a continuación */
    for(int i = 0; i < grupo->tope; i++){
        if(compararTFechas(fechaNacimientoTPersona(grupo->grupo[i]), fecha) == 0){
            imprimirTPersona(grupo->grupo[i]);
        }
    }
    /****** Fin de parte Parte 5.5 *****/ 
}
