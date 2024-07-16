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

#include "include/coleccionTGrupos.h"
#include "include/coleccionPiezas.h"

#define MAX_PALABRA 32
#define MAX_LINEA 256

///////////////////////////////
// Funciones main para Fecha //
///////////////////////////////

void leerFecha(TFecha &fecha); // Lee una fecha de la entrada en formato "dd/mm/aaaa" y la escribe la variable fecha
void main_crearFecha(TFecha &fecha); // Crea una fecha y la almacena en la variable fecha
void main_liberarFecha(TFecha &fecha); // Libera la memoria de la variable fecha
void main_imprimirFecha(TFecha fecha); // Imprime la fecha almacenada en la variable fecha
void main_aumentarDias(TFecha &fecha); // Aumenta la fecha almacenada en la variable fecha en la cantidad de días indicada
void main_compararFechas(); // Compara dos fechas leidas de la entrada

////////////////////////////////////
// Funciones main para Visitantes //
////////////////////////////////////
void main_crearVisitante(TVisitante &visitante); // Crea un visitante y lo almacena en la variable 'visitante'
void main_imprimirEdadVisitante(TVisitante visitante); // Imprime la edad del visitante almacenado en la variable 'visitante'
void main_imprimirIdVisitante(TVisitante visitante); // Imprime la id del visitante almacenado en la variable 'visitante'
void main_imprimirNombreYApellidoVisitante(TVisitante visitante); // Imprime el nombre y apelldio del visitante almacenado en la variable 'visitante'
void main_imprimirVisitante(TVisitante visitante); // Imprime el visitante almacenado en la variable 'visitante'
void main_copiarVisitante(TVisitante visitante); // Copia al visitante en visitante
void main_liberarVisitante(TVisitante &visitante); // Libera la memoria asociada al visitante guardado en la variable 'visitante'

////////////////////////////////////
//   Funciones main para Piezas   //
////////////////////////////////////
void main_crearTPieza(TPieza &pieza, TFecha &fecha);
void main_imprimirTPieza(TPieza pieza);
void main_liberarTPieza(TPieza &pieza);
void main_idTPieza(TPieza pieza);

//////////////////////////////////////////////
//   Funciones main para Colección Piezas   //
//////////////////////////////////////////////
void main_crearColeccionPiezas(TColeccionPiezas &coleccionPiezas);
void main_agregarColeccionPiezas(TColeccionPiezas &coleccionPiezas, TPieza &pieza);
void main_imprimirColeccionPiezas(TColeccionPiezas coleccionPiezas);
void main_liberarColeccionPiezas(TColeccionPiezas &coleccionPiezas);
void main_esVaciaColeccionPiezas(TColeccionPiezas coleccionPiezas);
void main_existePiezaColeccionPiezas(TColeccionPiezas coleccionPiezas);
void main_obtenerPiezaColeccionPiezas(TColeccionPiezas coleccionPiezas);
void main_removerDeColeccionPiezas(TColeccionPiezas &coleccionPiezas);

//////////////////////////////////
// Funciones main para GrupoABB //
//////////////////////////////////
void main_crearGrupoABB(TGrupoABB &grupo); // Crea un grupoABB y la almacena en la variable grupo
void main_agregarVisitanteAGrupoABB(TGrupoABB &grupo, TVisitante &visitante); // Agrega el visitante almacenada en la variable 'visitante' al grupo almacenado en la variable grupo
void main_imprimirGrupoABB(TGrupoABB grupo); // Imprime toda la información del grupoABB almacenado en la variable grupo
void main_liberarGrupoABB(TGrupoABB &grupo);
void main_existeEnGrupoABB(TGrupoABB grupo);
void main_obtenerVisitanteGrupoABB(TGrupoABB grupo);
void main_alturaGrupoABB(TGrupoABB grupo);
void main_maxIdGrupoABB(TGrupoABB grupo);
void main_cantidadVisitantesGrupoABB(TGrupoABB grupo);
void main_edadPromedioGrupoABB(TGrupoABB grupo);
void main_removerDeGrupoABB(TGrupoABB &grupo);
void main_obtenerNesimoVisitanteTGrupoABB(TGrupoABB grupo);
void main_alturaGrupoABBTiempo();
void main_obtenerExisteVisitanteGrupoABBTiempo();

//////////////////////////////////////////
// Funciones main para ColeccionTGrupos //
//////////////////////////////////////////
void main_crearColeccionGrupos(TColeccionTGrupos &coleccion);
void main_agregarGrupoAColeccion(TColeccionTGrupos &coleccion, TGrupoABB &grupo);
void main_imprimirColeccionTGrupos(TColeccionTGrupos coleccion);
void main_imprimirColeccionInvertidaTGrupos(TColeccionTGrupos coleccion);
void main_obtenerNesimoColeccionTGrupos(TColeccionTGrupos coleccion);
void main_cantidadTGruposColeccionTGrupos(TColeccionTGrupos coleccion);
void main_obtenerPrimeroColeccionTGrupos(TColeccionTGrupos coleccion);
void main_removerUltimoColeccionTGrupos(TColeccionTGrupos coleccion);
void main_removerNesimoColeccionTGrupos(TColeccionTGrupos coleccion);
void main_liberarColeccionTGrupos(TColeccionTGrupos &coleccion);
void main_obtenerVisitantesRepetidos(TColeccionTGrupos coleccion);
void main_visitanteMasRepetido(TColeccionTGrupos coleccion);


// programa principal que lee comandos de la entrada estándar e invoca a la función de test correspondiente
int main() {
    TFecha fecha = NULL;
    TVisitante visitante = NULL;
    TGrupoABB grupo = NULL;
    TPieza pieza = NULL;
    TColeccionPiezas coleccionPiezas = NULL;
    TColeccionTGrupos coleccionGrupos = NULL;

    char restoLinea[MAX_LINEA + 1];
    char cmd[MAX_PALABRA];

    int cont_comandos = 0;
    bool seguir = true;
    printf("Bienvenido al programa principal de ArteProg. Por favor ingrese su comando:\n");
    while (seguir) {
        // mostrar el prompt
        cont_comandos++;
        printf("%u> ", cont_comandos);

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

        } else if (cmd_es("crearFecha", cmd)) {  
            main_crearFecha(fecha);
        } else if (cmd_es("imprimirFecha", cmd)) {  
            main_imprimirFecha(fecha);
        } else if (cmd_es("liberarFecha", cmd)) {  
            main_liberarFecha(fecha);
        } else if (cmd_es("aumentarDias", cmd)) {  
            main_aumentarDias(fecha);
        } else if (cmd_es("compararFechas", cmd)) {  
            main_compararFechas();

            //////////////////////////////////////
            /* Funciones para testear visitante */
            //////////////////////////////////////

        } else if (cmd_es("crearVisitante", cmd)) {  
            main_crearVisitante(visitante);
        } else if (cmd_es("imprimirEdadVisitante", cmd)) {  
            main_imprimirEdadVisitante(visitante);
        } else if (cmd_es("imprimirIdVisitante",cmd)){
            main_imprimirIdVisitante(visitante);
        } else if (cmd_es("imprimirNombreYApellidoVisitante", cmd)){     
            main_imprimirNombreYApellidoVisitante(visitante);
        } else if (cmd_es("imprimirVisitante", cmd)) { 
            main_imprimirVisitante(visitante);
        } else if (cmd_es("copiarVisitante",cmd)){
            main_copiarVisitante(visitante);
        } else if (cmd_es("liberarVisitante", cmd)) {  
            main_liberarVisitante(visitante);        
          
            ////////////////////////////////////
            //   Funciones main para Piezas   //
            ////////////////////////////////////
        } else if (cmd_es("crearPieza", cmd)) {  
            main_crearTPieza(pieza, fecha);
        } else if (cmd_es("imprimirPieza", cmd)) {  
            main_imprimirTPieza(pieza);
        } else if (cmd_es("liberarPieza", cmd)) {  
            main_liberarTPieza(pieza);
        } else if (cmd_es("idPieza", cmd)) {  
            main_idTPieza(pieza);
        
            //////////////////////////////////////////////
            //   Funciones main para Colección Piezas   //
            //////////////////////////////////////////////
        } else if (cmd_es("crearColeccionPiezas", cmd)) {  
            main_crearColeccionPiezas(coleccionPiezas);
        } else if (cmd_es("agregarColeccionPiezas", cmd)) {  
            main_agregarColeccionPiezas(coleccionPiezas, pieza);
        } else if (cmd_es("imprimirColeccionPiezas", cmd)) {  
            main_imprimirColeccionPiezas(coleccionPiezas);
        } else if (cmd_es("liberarColeccionPiezas", cmd)) {  
            main_liberarColeccionPiezas(coleccionPiezas);
        } else if (cmd_es("esVaciaColeccionPiezas", cmd)) {  
            main_esVaciaColeccionPiezas(coleccionPiezas);
        } else if (cmd_es("existePiezaColeccionPiezas", cmd)){ 
            main_existePiezaColeccionPiezas(coleccionPiezas);
        } else if (cmd_es("obtenerPiezaColeccionPiezas", cmd)) {  
            main_obtenerPiezaColeccionPiezas(coleccionPiezas);
        } else if (cmd_es("removerDeColeccionPiezas", cmd)) {  
            main_removerDeColeccionPiezas(coleccionPiezas);


            ///////////////////////////////////
            /* Funciones para testear grupo */
            ///////////////////////////////////
        } else if (cmd_es("crearGrupoABB", cmd)) {  // Crea un grupo y la almacena en la variable grupo
            main_crearGrupoABB(grupo);
        } else if (cmd_es("agregarAGrupoABB", cmd)) { 
            main_agregarVisitanteAGrupoABB(grupo, visitante);
        } else if (cmd_es("imprimirGrupoABB", cmd)) { 
            main_imprimirGrupoABB(grupo);
        } else if (cmd_es("existeEnGrupoABB", cmd)) { 
            main_existeEnGrupoABB(grupo);
        } else if (cmd_es("obtenerVisitanteGrupoABB", cmd)) { 
            main_obtenerVisitanteGrupoABB(grupo);
        } else if (cmd_es("alturaGrupoABB", cmd)) { 
            main_alturaGrupoABB(grupo);
        } else if (cmd_es("maxIdGrupoABB", cmd)) { 
            main_maxIdGrupoABB(grupo);
        } else if (cmd_es("cantidadVisitantesGrupoABB", cmd)) { 
            main_cantidadVisitantesGrupoABB(grupo);
        } else if (cmd_es("edadPromedioGrupoABB", cmd)) { 
            main_edadPromedioGrupoABB(grupo);
        } else if (cmd_es("removerDeGrupoABB", cmd)) { 
            main_removerDeGrupoABB(grupo);
        } else if (cmd_es("liberarGrupoABB", cmd)) { 
            main_liberarGrupoABB(grupo);
        } else if (cmd_es("obtenerNesimoVisitanteGrupoABB", cmd)) { 
            main_obtenerNesimoVisitanteTGrupoABB(grupo);
        } else if (cmd_es("alturaGrupoABBTiempo", cmd)) { 
            main_alturaGrupoABBTiempo();
        } else if (cmd_es("obtenerExisteVisitanteGrupoABBTiempo", cmd)) { 
            main_obtenerExisteVisitanteGrupoABBTiempo();

            //////////////////////////////////////////////
            // Funciones para testear ColeccionTGrupos  //
            //////////////////////////////////////////////
        } else if (cmd_es("crearColeccionGrupos", cmd)) { 
            main_crearColeccionGrupos(coleccionGrupos);
        } else if (cmd_es("agregarAColeccionGrupos", cmd)) { 
            main_agregarGrupoAColeccion(coleccionGrupos, grupo);
        } else if (cmd_es("imprimirColeccionGrupos", cmd)) { 
            main_imprimirColeccionTGrupos(coleccionGrupos);
        } else if (cmd_es("imprimirInvertidaColeccionGrupos", cmd)) { 
            main_imprimirColeccionInvertidaTGrupos(coleccionGrupos);
        } else if (cmd_es("obtenerNesimoColeccionGrupos", cmd)) { 
            main_obtenerNesimoColeccionTGrupos(coleccionGrupos);
        } else if (cmd_es("cantidadColeccionGrupos", cmd)) { 
            main_cantidadTGruposColeccionTGrupos(coleccionGrupos);
        } else if (cmd_es("obtenerPrimeroColeccionGrupos", cmd)) { 
            main_obtenerPrimeroColeccionTGrupos(coleccionGrupos);
        } else if (cmd_es("removerUltimoColeccionGrupos", cmd)) { 
            main_removerUltimoColeccionTGrupos(coleccionGrupos);
        } else if (cmd_es("removerNesimoColeccionGrupos", cmd)) { 
            main_removerNesimoColeccionTGrupos(coleccionGrupos);
        } else if (cmd_es("liberarColeccionGrupos", cmd)) { 
            main_liberarColeccionTGrupos(coleccionGrupos);
        } else if (cmd_es("obtenerVisitantesRepetidos", cmd)) { 
            main_obtenerVisitantesRepetidos(coleccionGrupos);
        } else if (cmd_es("visitanteMasRepetido", cmd)) { 
            main_visitanteMasRepetido(coleccionGrupos);
    

        } else {
            printf("Comando no reconocido.\n");  // Comando no reconocido
        }  
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
    printf("Fecha creada en forma exitosa.\n");
}

void main_liberarFecha(TFecha &fecha) {
    assert(fecha != NULL);
    liberarTFecha(fecha);
    printf("Fecha liberada en forma exitosa.\n");
}

void main_imprimirFecha(TFecha fecha) {
    assert(fecha != NULL);
    imprimirTFecha(fecha);
}

void main_aumentarDias(TFecha &fecha) {
    assert(fecha != NULL);
    nat cantDias = leerNat();
    aumentarTFecha(fecha, cantDias);
    printf("La nueva fecha aplazada %d dias es: \n", cantDias);
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

///////////////////////////////////
/* Funciones main para Visitante */
///////////////////////////////////

void main_crearVisitante(TVisitante &visitante){
    assert(visitante == NULL);
    int id = leerInt();
    char nombre[MAX_NOMBRE];
    leerChars(nombre);
    char apellido[MAX_APELLIDO];
    leerChars(apellido);
    int edad = leerInt();
    visitante = crearTVisitante(id, nombre, apellido, edad);
    printf("Visitante creadox de forma exitosa.\n");
}

void main_imprimirEdadVisitante(TVisitante visitante) {
    assert(visitante != NULL);
    printf("La edad del visitante es: %d\n", edadTVisitante(visitante));
}

void main_imprimirIdVisitante(TVisitante visitante) {
    assert(visitante != NULL);
    printf("La id del visitante es: %d\n", idTVisitante(visitante));
}

void main_imprimirNombreYApellidoVisitante(TVisitante visitante){
    assert(visitante != NULL);
    char nombre[MAX_NOMBRE];
    char apellido[MAX_APELLIDO];
    nombreTVisitante(visitante, nombre);
    apellidoTVisitante(visitante, apellido);
    printf("El nombre del visitante es: %s\n", nombre);
    printf("El apellido del visitante es: %s\n", apellido);
}

void main_imprimirVisitante(TVisitante visitante) {
    assert(visitante != NULL);
    imprimirTVisitante(visitante);
}

void main_copiarVisitante(TVisitante visitante){
    TVisitante visitanteCopia = copiarTVisitante(visitante);
    printf("Visitante copiado. Datos de la copia:\n");
    imprimirTVisitante(visitanteCopia);

    liberarTVisitante(visitanteCopia);
}

void main_liberarVisitante(TVisitante &visitante) {
    assert(visitante != NULL);
    liberarTVisitante(visitante);
    printf("Visitante liberado con exito.\n");
}

////////////////////////////////////
//   Funciones main para Piezas   //
////////////////////////////////////
void main_crearTPieza(TPieza &pieza, TFecha &fecha){
    assert(pieza == NULL);
    int id = leerInt();
    char nombrePieza[MAX_NOMBRE_PIEZA];
    leerChars(nombrePieza);
    char nombreAutor[MAX_NOMBRE_AUTOR];
    leerChars(nombreAutor);
    char apellidoAutor[MAX_APELLIDO_AUTOR];
    leerChars(apellidoAutor);
    pieza = crearTPieza(id, nombrePieza, nombreAutor, apellidoAutor, fecha);
    fecha = NULL;
    printf("Pieza creada en forma exitosa.\n");
}

void main_imprimirTPieza(TPieza pieza){
    assert(pieza != NULL);
    imprimirTPieza(pieza);
}

void main_liberarTPieza(TPieza &pieza){
    assert(pieza != NULL);
    liberarTPieza(pieza);
    pieza = NULL;
    printf("Pieza liberada en forma exitosa.\n");
}

void main_idTPieza(TPieza pieza){
    assert(pieza != NULL);
    int id = idTPieza(pieza);
    printf("ID: %d\n", id);
}


//////////////////////////////////////////////
//   Funciones main para Colección Piezas   //
//////////////////////////////////////////////
void main_crearColeccionPiezas(TColeccionPiezas &coleccionPiezas){
    assert(coleccionPiezas == NULL);
    coleccionPiezas = crearColeccionPiezasVacia();
    printf("Coleccion de piezas creada de forma exitosa.\n");
}

void main_agregarColeccionPiezas(TColeccionPiezas &coleccionPiezas, TPieza &pieza){
    insertarPiezaColeccionPiezas(coleccionPiezas, pieza);
    printf("Pieza agregada de forma exitosa.\n");
    pieza = NULL;
}

void main_imprimirColeccionPiezas(TColeccionPiezas coleccionPiezas){
    imprimirColeccionPiezas(coleccionPiezas);
}

void main_liberarColeccionPiezas(TColeccionPiezas &coleccionPiezas){
    liberarColeccionPiezas(coleccionPiezas);
    printf("Coleccion liberada con exito.\n");
}

void main_esVaciaColeccionPiezas(TColeccionPiezas coleccionPiezas){
    bool esVacia = esVaciaColeccionPiezas(coleccionPiezas);
    if (esVacia){
        printf("La coleccion de piezas es vacia.\n");
    } else {
        printf("La coleccion de piezas NO es vacia.\n");
    }
}

void main_existePiezaColeccionPiezas(TColeccionPiezas coleccionPiezas){
    int id = leerInt();
    bool existe = existePiezaColeccionPiezas(coleccionPiezas, id);
    if (existe){
        printf("La pieza con id %d pertenece a la coleccion.\n", id);
    } else {
        printf("La pieza con id %d NO pertenece a la coleccion.\n", id);
    }
}

void main_obtenerPiezaColeccionPiezas(TColeccionPiezas coleccionPiezas){
    int id = leerInt();
    assert(existePiezaColeccionPiezas(coleccionPiezas, id));
    TPieza pieza = obtenerPiezaColeccionPiezas(coleccionPiezas, id);
    imprimirTPieza(pieza);
}

void main_removerDeColeccionPiezas(TColeccionPiezas &coleccionPiezas){
    int id = leerInt();
    assert(existePiezaColeccionPiezas(coleccionPiezas, id));
    removerPiezaColeccionPiezas(coleccionPiezas, id);
    printf("Pieza con id %d removida con exito.\n", id);
}


////////////////////////////////
/* Funciones main para Grupo */
////////////////////////////////

void main_crearGrupoABB(TGrupoABB &grupo){
    assert(grupo == NULL);
    grupo = crearTGrupoABBVacio();
    printf("El grupoABB ha sido creado de forma exitosa.\n");
}

void main_agregarVisitanteAGrupoABB(TGrupoABB &grupo, TVisitante &visitante){
    assert(visitante != NULL);
    insertarTVisitanteTGrupoABB(grupo, visitante);
    visitante = NULL;
    printf("Se ha agregado el visitante al grupo de forma exitosa.\n");
}

void main_imprimirGrupoABB(TGrupoABB grupo){
    imprimirTGrupoABB(grupo);
}

void main_liberarGrupoABB(TGrupoABB &grupo){
    liberarTGrupoABB(grupo);
    printf("Grupo liberado con exito.\n");
}

void main_existeEnGrupoABB(TGrupoABB grupo){
    int id = leerInt();
    if (existeTVisitanteTGrupoABB(grupo, id)){
        printf("El visitante con id %d pertenece al grupo.\n", id);
    }else{
        printf("El visitante con id %d NO pertenece al grupo.\n", id);
    }
}

void main_obtenerVisitanteGrupoABB(TGrupoABB grupo){
    int id = leerInt();
    TVisitante visitante = obtenerTVisitanteTGrupoABB(grupo, id);
    if (visitante == NULL){
        printf("El visitante con id %d no se puede imprimir pues NO pertenece al grupo.\n", id);
    }else{  
        imprimirTVisitante(visitante);
    }
}

void main_alturaGrupoABB(TGrupoABB grupo){
    nat altura = alturaTGrupoABB(grupo);
    printf("La altura del grupo es %d.\n", altura);
}

void main_maxIdGrupoABB(TGrupoABB grupo){
    TVisitante maxId = maxIdTVisitanteTGrupoABB(grupo);
    printf("El mayor id en el grupo es %d.\n", idTVisitante(maxId));
}

void main_cantidadVisitantesGrupoABB(TGrupoABB grupo){
    int cantidad = cantidadVisitantesTGrupoABB(grupo);
    printf("La cantidad de visitantes en el grupo es %d.\n", cantidad);
}

void main_edadPromedioGrupoABB(TGrupoABB grupo){
    float edadPromedio = edadPromedioTGrupoABB(grupo);
    printf("La edad promedio del grupo es %.2f.\n", edadPromedio);
}

void main_removerDeGrupoABB(TGrupoABB &grupo){
    int id = leerInt();
    if (existeTVisitanteTGrupoABB(grupo, id)) {
        removerTVisitanteTGrupoABB(grupo, id);
        printf("El visitante con id %d se removio del grupo.\n", id);
    } else {
        printf("El visitante con id %d no se puede remover porque NO pertenece al grupo.\n", id);
    }
}

void main_obtenerNesimoVisitanteTGrupoABB(TGrupoABB grupo){
    int n = leerInt();
    int cantEnGrupo = cantidadVisitantesTGrupoABB(grupo); 
    if (cantEnGrupo >= n) {
        TVisitante visitante = obtenerNesimoVisitanteTGrupoABB(grupo, n);
        printf("Visitante nro %d del grupoABB:\n", n);
        imprimirTVisitante(visitante);
    } else {
        printf("No se puede imprimir vistante %d del grupoABB porque tiene solo %d visitantes.\n", n, cantEnGrupo);
    }
}

void insertarEnArbolDesdeArreglo(TGrupoABB &grupoABB, TVisitante *arreglo, int inicio, int final){
    if (inicio <= final){
        int mid = (inicio + final) / 2;
        insertarTVisitanteTGrupoABB(grupoABB, arreglo[mid]);
        insertarEnArbolDesdeArreglo(grupoABB, arreglo, inicio, mid - 1);
        insertarEnArbolDesdeArreglo(grupoABB, arreglo, mid + 1, final);
    }
}

void main_alturaGrupoABBTiempo(){
    TGrupoABB grupoABB = crearTGrupoABBVacio();

    nat tamanio = leerNat();
    nat timeout = leerNat();

    TVisitante *arreglo = new TVisitante[tamanio];
    for (nat i = 0; i < tamanio; i++) {
        arreglo[i] = crearTVisitante(i, "Alberto", "Pardo", 52);
    }

    nat inicio = 0;
    nat final = tamanio - 1;
    insertarEnArbolDesdeArreglo(grupoABB, arreglo, inicio, final);
    clock_t tm = clock();
    nat altura = alturaTGrupoABB(grupoABB);
    tm = clock() - tm;


    float tiempo = ((float)tm) / CLOCKS_PER_SEC;
    if (tiempo > timeout){
        printf("ERROR, tiempo excedido; %.1f > %d \n", tiempo, timeout);
    }else{
        printf("La altura del grupo es %d. Calculado correctamente en menos de %ds.\n", altura, timeout);    
    }
    
    liberarTGrupoABB(grupoABB);
    delete[] arreglo;
}

void main_obtenerExisteVisitanteGrupoABBTiempo(){
    TGrupoABB grupoABB = crearTGrupoABBVacio();

    nat tamanio = leerNat();
    double timeout = leerDouble();

    TVisitante *arreglo = new TVisitante[tamanio];
    for (nat i = 0; i < tamanio; i++) {
        arreglo[i] = crearTVisitante(i, "Carlos", "Luna", 45);
    }

    nat inicio = 0;
    nat final = tamanio - 1;
    insertarEnArbolDesdeArreglo(grupoABB, arreglo, inicio, final);
    clock_t tm = clock();
    bool existeVisitante1 = existeTVisitanteTGrupoABB(grupoABB, 0);
    bool existeVisitante2 = existeTVisitanteTGrupoABB(grupoABB, tamanio - 1);
    bool existeVisitante3 = existeTVisitanteTGrupoABB(grupoABB, tamanio / 3);
    bool existeVisitante4 = existeTVisitanteTGrupoABB(grupoABB, (2 * tamanio) / 3);
    TVisitante visitante1 = obtenerTVisitanteTGrupoABB(grupoABB, 0);
    TVisitante visitante2 = obtenerTVisitanteTGrupoABB(grupoABB, tamanio - 1);
    TVisitante visitante3 = obtenerTVisitanteTGrupoABB(grupoABB, tamanio / 3);
    TVisitante visitante4 = obtenerTVisitanteTGrupoABB(grupoABB, (2 * tamanio) / 3);
    tm = clock() - tm;

    float tiempo = ((float)tm) / CLOCKS_PER_SEC;
    printf("%f \n", tiempo);
    if (tiempo > timeout){
        printf("ERROR, tiempo excedido: %.3f > %.3f \n", tiempo, timeout);
    }else{
        printf("Se obtuvieron los visitantes? %d %d %d %d con ids respectivos %d %d %d %d\n", existeVisitante1, existeVisitante2, existeVisitante3, existeVisitante4, idTVisitante(visitante1), idTVisitante(visitante2), idTVisitante(visitante3), idTVisitante(visitante4));
        printf("Calculado correctamente en menos de %.3fs.\n", timeout);    
    }
    
    liberarTGrupoABB(grupoABB);
    delete[] arreglo;
}

//////////////////////////////////////////
// Funciones main para ColeccionTGrupos //
//////////////////////////////////////////
void main_crearColeccionGrupos(TColeccionTGrupos &coleccion){
    assert(coleccion == NULL);
    coleccion = crearTColeccionTGruposVacia();
    printf("La coleccion de grupos ha sido creado de forma exitosa.\n");
}

void main_agregarGrupoAColeccion(TColeccionTGrupos &coleccion, TGrupoABB &grupo){
    assert(grupo != NULL);
    insertarGrupoTColeccionTGrupos(coleccion, grupo);
    grupo = NULL;
    printf("Se ha agregado el grupo a la coleccion de forma exitosa.\n");
}

void main_imprimirColeccionTGrupos(TColeccionTGrupos coleccion){
    imprimirTColeccionTGrupos(coleccion);
}

void main_imprimirColeccionInvertidaTGrupos(TColeccionTGrupos coleccion){
    imprimirInvertidoTColeccionTGrupos(coleccion);
}

void main_obtenerNesimoColeccionTGrupos(TColeccionTGrupos coleccion){
    int n = leerInt();
    TGrupoABB grupo = obtenerNesimoColeccionTGrupos(coleccion, n);
    if (grupo){
        printf("Grupo en la posicion %d:\n", n);
        imprimirTGrupoABB(grupo);
    }else{
        printf("NO existe un grupo en la posicion %d\n", n);
    }
}

void main_cantidadTGruposColeccionTGrupos(TColeccionTGrupos coleccion){
    nat cant = cantidadTGruposColeccionTGrupos(coleccion);
    printf("La cantidad de grupos en la coleccion es %d\n", cant);
}

void main_obtenerPrimeroColeccionTGrupos(TColeccionTGrupos coleccion){
    nat cant = cantidadTGruposColeccionTGrupos(coleccion);
    if (cant > 0){
        TGrupoABB grupo = obtenerPrimeroColeccionTGrupos(coleccion);
        assert(grupo != NULL);
        printf("Primer grupo:\n");
        imprimirTGrupoABB(grupo);
    }else{
        printf("No se puede obtener el primero de la coleccion de grupos porque es vacia\n");
    }
}

void main_removerUltimoColeccionTGrupos(TColeccionTGrupos coleccion){
    nat cant = cantidadTGruposColeccionTGrupos(coleccion);
    if (cant > 0){
        TGrupoABB grupo = removerUltimoColeccionTGrupos(coleccion);
        assert(grupo != NULL);
        printf("Ultimo grupo (removido):\n");
        imprimirTGrupoABB(grupo);
        liberarTGrupoABB(grupo);
    }else{
        printf("No se puede remover el ultimo de la coleccion de grupos porque es vacia\n");
    }
}

void main_removerNesimoColeccionTGrupos(TColeccionTGrupos coleccion){
    nat n = leerNat();
    nat cant = cantidadTGruposColeccionTGrupos(coleccion);
    if (cant >= n){
        TGrupoABB grupo = removerNesimoColeccionTGrupos(coleccion, n);
        assert(grupo != NULL);
        printf("Grupo en la posicion %d (removido):\n", n);
        imprimirTGrupoABB(grupo);
        liberarTGrupoABB(grupo);
    }else{
        printf("No se puede remover el elemento %d de la coleccion de grupos porque solo contiene %d\n", n, cant);
    }
}

void main_liberarColeccionTGrupos(TColeccionTGrupos &coleccion){
    assert(coleccion != NULL);
    liberarTColeccionTGrupos(coleccion);
    printf("Coleccion de grupos liberada\n");
    coleccion = NULL;
}

void main_obtenerVisitantesRepetidos(TColeccionTGrupos coleccion){
    assert(coleccion != NULL);
    TGrupoABB grupo = obtenerVisitantesRepetidos(coleccion);
    if (cantidadVisitantesTGrupoABB(grupo) == 0){
        printf("No hay visitantes repetidos entre los grupos.\n");
    }else{
        printf("Los visitantes repetidos son:\n");
        imprimirTGrupoABB(grupo);
    }
    liberarTGrupoABB(grupo);
}

void main_visitanteMasRepetido(TColeccionTGrupos coleccion){
    assert(coleccion != NULL);
    TVisitante visitante = visitanteMasRepetido(coleccion);
    if (visitante == NULL){
        printf("No hay visitante repetido porque no hay visitantes en los grupos de la coleccion.\n");
    }else{
        printf("El visitante que aparece en la mayor cantidad de grupos es:\n");
        imprimirTVisitante(visitante);
    }
}


