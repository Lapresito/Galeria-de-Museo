
#include "hashVisitaDia.h"

typedef struct rep_nodoHashVisita *TNodoHash;
struct rep_nodoHashVisita{
    TVisitaDia visita;
    // lista hash
    TNodoHash sig_nodoHash;
    // lista de todos los elementos para borrar en O(n)
    TNodoHash sig_listaTodosHash;
};

struct rep_hashvisitadia {
    TNodoHash*tabla;
    // para imprimir
    int tamanoTabla;
    // para liberar en O(1)
    TNodoHash listaTodos;
};

// interna funcion hash
int funcionHash(TFecha fecha, int cantEstimadas){
    return (31 * (int) mesTFecha(fecha) + (int) diaTFecha(fecha)) % cantEstimadas;
}

THashVisitaDia crearTHashVisitaDia(int cantEstimadas){
    THashVisitaDia nuevaTabla = new rep_hashvisitadia;
    nuevaTabla->tabla = new TNodoHash[cantEstimadas];
    nuevaTabla->tamanoTabla = cantEstimadas;
    nuevaTabla->listaTodos=NULL;
    for(int i=0; i< cantEstimadas; i++){
        nuevaTabla->tabla[i] = NULL;
    }
    return nuevaTabla;
}

void agregarVisitaDiaTHashVisitaDia(THashVisitaDia hash, TVisitaDia visitaDia) {
    if(hash != NULL){
        // creo nodo hash
        TNodoHash nuevoNodo = new rep_nodoHashVisita;
        nuevoNodo->visita = visitaDia;
        nuevoNodo->sig_nodoHash = NULL;
        nuevoNodo->sig_listaTodosHash = NULL;

        // obtener el índice usando la funcion hash
        int indice = funcionHash(fechaTVisitaDia(visitaDia), hash->tamanoTabla);

        // insertar el nuevo nodo en la lista de colisiones en el bucket correspondiente
        if (hash->tabla[indice] == NULL) {
            hash->tabla[indice] = nuevoNodo;
        } else {
            // insertar al principio de la lista de colisiones
            nuevoNodo->sig_nodoHash = hash->tabla[indice];
            hash->tabla[indice] = nuevoNodo;
        }
        // insertar el nuevo nodo al principio de la listaTodos para liberacion en O(1)
        nuevoNodo->sig_listaTodosHash = hash->listaTodos;
        hash->listaTodos = nuevoNodo;

    }
}

void imprimirTHashVisitaDia(THashVisitaDia hash){
    if(hash !=NULL){
        for(int i=0; i < hash->tamanoTabla; i++){
            if(hash->tabla[i] == NULL){
                printf("No hay elementos guardados la posicion %d de la tabla.\n", i);
            }else{
                TNodoHash aux = hash->tabla[i];
                printf("Elementos en la posicion %d de la tabla:\n", i);
                while( aux != NULL){
                    imprimirTVisitaDia(aux->visita);
                    aux=aux->sig_nodoHash;
                }
            }
        }
    }
}

TVisitaDia obtenerVisitaDiaTHashVisitaDia(THashVisitaDia hash, TFecha fecha){
    if(hash != NULL){
        int indice = funcionHash(fecha, hash->tamanoTabla);
        TNodoHash aux = hash->tabla[indice];
        while(aux != NULL && (compararTFechas(fechaTVisitaDia(aux->visita), fecha) != 0)){
            aux = aux->sig_nodoHash;
        }
        if(aux != NULL){
            return aux->visita;
        }else{
            return NULL;       
        }
    }else{
        return NULL;
    }
}

bool perteneceVisitaDiaTHashVisitaDia(THashVisitaDia hash, TFecha fecha){
    if(hash != NULL){
        int indice = funcionHash(fecha, hash->tamanoTabla);
        TNodoHash aux = hash->tabla[indice];
        while(aux != NULL && (compararTFechas(fechaTVisitaDia(aux->visita), fecha) != 0)){
            aux = aux->sig_nodoHash;
        }
        return aux != NULL;
    }else{
        return false;
    }
}

void liberarTHashVisitaDia(THashVisitaDia &hash){
    if(hash != NULL){
        while(hash->listaTodos !=NULL){
            TNodoHash aux = hash->listaTodos;
            // borrado logico
            hash->listaTodos = hash->listaTodos->sig_listaTodosHash;
            // borrado fisico
            liberarTVisitaDia(aux->visita);
            delete aux;
        }
        delete []hash->tabla;
        delete hash;
        hash = NULL;
    }
}
