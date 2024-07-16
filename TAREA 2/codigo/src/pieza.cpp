#include "../include/pieza.h"


struct rep_pieza {
    int id;
    char nombre[MAX_NOMBRE_PIEZA];
    char autorN[MAX_NOMBRE_AUTOR];
    char autorA[MAX_APELLIDO_AUTOR];
    TFecha fechaCreacion;
};

TPieza crearTPieza(int identificador, const char nombrePieza[MAX_NOMBRE_PIEZA], const char nombreAutor[MAX_NOMBRE_AUTOR], const char apellidoAutor[MAX_APELLIDO_AUTOR], TFecha fechaCreacion){
    
    TPieza nuevaPieza = NULL;
    nuevaPieza = new rep_pieza;
    nuevaPieza -> id = identificador;
	strcpy(nuevaPieza->nombre, nombrePieza);
	strcpy(nuevaPieza->autorN, nombreAutor);
	strcpy(nuevaPieza->autorA, apellidoAutor);
	nuevaPieza -> fechaCreacion = fechaCreacion;

    return nuevaPieza;
}

int idTPieza(TPieza pieza){ 
    int idP = 0;
    idP = pieza->id;
    return idP;
}

void imprimirTPieza(TPieza pieza){
    // Declaracion de auxiliares para utilizar strcpy
    char n[MAX_NOMBRE_PIEZA];
    char aN[MAX_NOMBRE_AUTOR];
    char aA[MAX_APELLIDO_AUTOR];
    strcpy(n, pieza->nombre);
    strcpy(aN, pieza->autorN);
    strcpy(aA, pieza->autorA);

    //Impresion
    printf("Pieza: %d\n", idTPieza(pieza));
    printf("%s-%s %s\n", n, aN, aA);
    printf("Creada en: ");
    imprimirTFecha(pieza->fechaCreacion);

}

void liberarTPieza(TPieza &pieza){
    liberarTFecha(pieza -> fechaCreacion);
    delete pieza;
    pieza = NULL;
}
