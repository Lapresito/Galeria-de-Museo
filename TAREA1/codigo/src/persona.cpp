#include "../include/persona.h"

// Define la estructura Persona
struct rep_persona {
    /************ Parte 4.1 ************/
    /*Escriba el código a continuación */
    int cedula;
    char nombre[MAX_NOMBRE];
    char apellido[MAX_APELLIDO];
    TFecha fechaNacimiento;
    /****** Fin de parte Parte 4.1 *****/
};

// Función que crea un elemento de tipo TPersona con los valores dados
TPersona crearTPersona(int cedula, const char nombre[MAX_NOMBRE], char apellido[MAX_APELLIDO], TFecha fecha){
    TPersona nuevaPersona = NULL;
    /************ Parte 4.2 ************/
    /*Escriba el código a continuación */
    nuevaPersona = new rep_persona;
    nuevaPersona -> cedula = cedula;
    strcpy(nuevaPersona->nombre, nombre);
    strcpy(nuevaPersona->apellido, apellido);
    nuevaPersona -> fechaNacimiento = fecha;
    /****** Fin de parte Parte 4.2 *****/
    return nuevaPersona;
}

// Función que retorna el nombre de la persona
void nombrePersona(TPersona persona, char nombre[MAX_NOMBRE]){
    /************ Parte 4.3 ************/
    /*Escriba el código a continuación */
    strcpy(nombre, persona->nombre);
    /****** Fin de parte Parte 4.3 *****/
}

// Funcion que retorna el apellido de la persona
void apellidoPersona(TPersona persona, char apellido[MAX_APELLIDO]){
    /************ Parte 4.3 ************/
    /*Escriba el código a continuación */
    strcpy(apellido, persona->apellido);
    /****** Fin de parte Parte 4.3 *****/
}

// Función que libera la memoria asignada para una persona
// Debe liberar también la memoria de la fecha asociada
void liberarTPersona(TPersona &persona){
    /************ Parte 4.3 ************/
    /*Escriba el código a continuación */
    liberarTFecha(persona->fechaNacimiento);
    delete persona;
    persona = NULL;
    /****** Fin de parte Parte 4.3 *****/
}

// Función que retorna la cédula de la persona
int cedulaTPersona(TPersona persona){
    int cedula = 0;
	/************ Parte 4.4 ************/
    /*Escriba el código a continuación */
    cedula = persona -> cedula;
    /****** Fin de parte Parte 4.4 *****/
	return cedula;
}

// Función que retorna la fecha de nacimiento de la persona
TFecha fechaNacimientoTPersona(TPersona persona){
    TFecha fecha = NULL;
	/************ Parte 4.4 ************/
    /*Escriba el código a continuación */
    fecha = persona->fechaNacimiento;
    /****** Fin de parte Parte 4.4 *****/
	return fecha;
}

// Función que imprime la información de la persona en el siguiente formato:
// Persona <nombre> <apellido>
// Cédula: <cedula>
// Fecha de nacimiento: <fecha>
void imprimirTPersona(TPersona persona){
    /************ Parte 4.5 ************/
    /*Escriba el código a continuación */
    // Declaracion de variables dentro de scope
    char n[MAX_NOMBRE];
    char a[MAX_APELLIDO];
    //Asignacion
    nombrePersona(persona, n);
    apellidoPersona(persona, a);

    printf("Persona %s %s\n", n, a);
    printf("Cedula: %d\n", cedulaTPersona(persona));
    printf("Fecha de nacimiento: ");
    imprimirTFecha(persona->fechaNacimiento);
    /****** Fin de parte Parte 4.5 *****/
}

// Función que retorna true si persona1 es mas joven que persona2 y false en caso contrario
bool esMasJoven(TPersona persona1, TPersona persona2){
    bool masJoven = false;
	/************ Parte 4.6 ************/
    /*Escriba el código a continuación */
    if(compararTFechas(fechaNacimientoTPersona(persona1), fechaNacimientoTPersona(persona2)) == 1){
        masJoven = true;
    }
    /****** Fin de parte Parte 4.6 *****/
	return masJoven;
}
