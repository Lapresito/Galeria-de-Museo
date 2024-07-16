#include "../include/visitante.h"


struct rep_visitante {
    int id;
    char nombre[MAX_NOMBRE];
    char apellido[MAX_APELLIDO];
    int edad;
};

TVisitante crearTVisitante(int id, const char nombre[MAX_NOMBRE], const char apellido[MAX_APELLIDO], int edad){
    TVisitante nuevoVisitante = NULL;
    nuevoVisitante = new rep_visitante;
    nuevoVisitante -> id = id;
	strcpy(nuevoVisitante->nombre, nombre);
	strcpy(nuevoVisitante->apellido, apellido);
	nuevoVisitante -> edad = edad;
    return nuevoVisitante;
}

void nombreTVisitante(TVisitante visitante, char nombre[MAX_NOMBRE]){
    strcpy(nombre, visitante->nombre);
}

void apellidoTVisitante(TVisitante visitante, char apellido[MAX_APELLIDO]){
    strcpy(apellido, visitante->apellido);
}

int idTVisitante(TVisitante visitante){
    return visitante->id;
}

int edadTVisitante(TVisitante visitante){
    return visitante->edad;
}

void liberarTVisitante(TVisitante &visitante){
    delete visitante;
    visitante = NULL;
}

TVisitante copiarTVisitante(TVisitante visitante){
    TVisitante copia = new rep_visitante;
    copia->id = visitante->id;
    strcpy(copia->nombre, visitante->nombre);
    strcpy(copia->apellido, visitante->apellido);
    copia->edad = visitante->edad;
    return copia; 

}

void imprimirTVisitante(TVisitante visitante){
    // Declaracion de variables dentro de scope para asignar e imprimir
    char n[MAX_NOMBRE];
    char a[MAX_APELLIDO];
    //Asignacion
    nombreTVisitante(visitante, n);
    apellidoTVisitante(visitante, a);

    printf("Visitante %s %s\n", n , a);
    printf("Id: %d\n", idTVisitante(visitante));
    printf("Edad: %d\n", edadTVisitante(visitante));

}


