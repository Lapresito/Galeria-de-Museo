#include "../include/listaExposiciones.h"

struct rep_listaexposiciones{
    TExposicion exposicion;
    TListaExposiciones sig;
};

TListaExposiciones crearTListaExposicionesVacia(){ 
    return NULL; 
}

void agregarExposicionTListaExposiciones(TListaExposiciones &listaExposiciones, TExposicion expo){
    TListaExposiciones nuevaExposicion = new rep_listaexposiciones;
    nuevaExposicion->exposicion = expo;
    nuevaExposicion->sig = NULL;

    if( esVaciaTListaExposiciones(listaExposiciones) || compararTFechas(fechaInicioTExposicion(listaExposiciones->exposicion), fechaInicioTExposicion(expo)) == 1){
        nuevaExposicion->sig = listaExposiciones;
        listaExposiciones = nuevaExposicion;
    }else{
        TListaExposiciones aux = listaExposiciones;
        while( aux->sig != NULL && (compararTFechas(fechaInicioTExposicion(aux->exposicion), fechaInicioTExposicion(expo)) == -1 || compararTFechas(fechaInicioTExposicion(aux->exposicion), fechaInicioTExposicion(expo)) == 0)){
            aux = aux->sig;
        }
        nuevaExposicion->sig = aux->sig;
        aux->sig = nuevaExposicion;
    }

}

bool perteneceExposicionTListaExposiciones(TListaExposiciones listaExposiciones, int idExpo){
    if(listaExposiciones !=NULL){
        TListaExposiciones aux = listaExposiciones;
        while (aux != NULL && idTExposicion(aux->exposicion) != idExpo) {
            aux = aux->sig;
        }
        return aux != NULL;
    }else{
        return false;
    }
}

TExposicion obtenerExposicionTListaExposiciones(TListaExposiciones listaExposiciones, int idExpo){ 
    if(listaExposiciones !=NULL){
        TListaExposiciones aux = listaExposiciones;
        while (aux != NULL && idTExposicion(aux->exposicion) != idExpo) {
            aux = aux->sig;
        }
        if(aux != NULL){
            return aux->exposicion;
        }else{
            return NULL;
        }
    }else{
        return NULL;
    }
}

bool esVaciaTListaExposiciones(TListaExposiciones listaExposiciones){ 
    return listaExposiciones == NULL; 
}

void imprimirTListaExposiciones(TListaExposiciones listaExposiciones){
    TListaExposiciones aux = listaExposiciones;
    while (aux != NULL){
        imprimirTExposicion(aux->exposicion);
        aux = aux->sig;
    }
}

void liberarTListaExposiciones(TListaExposiciones &listaExposiciones, bool liberarExposiciones){
    while (listaExposiciones != NULL){
        TListaExposiciones aux = listaExposiciones;
        listaExposiciones = listaExposiciones->sig;
        if(liberarExposiciones){
            liberarTExposicion(aux->exposicion);
        }
        delete aux;
    }
}

TListaExposiciones obtenerExposicionesFinalizadas(TListaExposiciones &listaExposiciones, TFecha fecha){ 
    TListaExposiciones exposicionesFinalizadas = NULL;
    TListaExposiciones finFinalizadas = NULL;
    TListaExposiciones aux = listaExposiciones;
    //caso 1er elemento finalizo
    while (aux != NULL && compararTFechas(fechaFinTExposicion(aux->exposicion), fecha) == - 1){
        //caso borde finalizadas es vacia
        if(exposicionesFinalizadas == NULL){
            exposicionesFinalizadas = aux;
            finFinalizadas = exposicionesFinalizadas;
            listaExposiciones = aux->sig;
            finFinalizadas->sig = NULL;
            aux = listaExposiciones;
        // caso en que finalizadas no es vacia
        }else{
            finFinalizadas->sig = aux;
            finFinalizadas = finFinalizadas->sig;
            listaExposiciones = aux->sig;
            finFinalizadas->sig = NULL;
            aux = listaExposiciones;
        }
        
    }
    // descartamos que el 1er elemento finalizo y aux apunta a listaExposiciones
    // caso intermedio, avanzo agregando a finalizadas y removiendo de lista original
    if(aux != NULL){
        while(aux->sig != NULL){
            if(compararTFechas(fechaFinTExposicion(aux->sig->exposicion), fecha) == -1){
                // caso en que finalizadas no es null
                if( exposicionesFinalizadas != NULL){
                    finFinalizadas->sig = aux->sig;
                    finFinalizadas = finFinalizadas->sig;
                    aux->sig = finFinalizadas->sig;
                    finFinalizadas->sig = NULL;
                    aux = aux->sig;
                }else{
                    exposicionesFinalizadas = aux->sig;
                    finFinalizadas = exposicionesFinalizadas;
                    aux->sig = finFinalizadas->sig;
                    finFinalizadas->sig = NULL;
                }
            }else{
                if(aux != NULL){
                    aux = aux->sig;
                }
            }
        }
    }
    return exposicionesFinalizadas;  
}              

TListaExposiciones obtenerExposicionesActivas(TListaExposiciones &listaExposiciones, TFecha fecha){ 
    // logica igual a finalizadas con comparacion diferente.
    TListaExposiciones exposicionesActivas = NULL;
    TListaExposiciones finActivas = NULL;
    TListaExposiciones aux = listaExposiciones;
    //caso 1er elemento activo
    while (aux != NULL && (compararTFechas(fechaInicioTExposicion(aux->exposicion), fecha) == 0 || compararTFechas(fechaInicioTExposicion(aux->exposicion), fecha) == -1) && (compararTFechas(fechaFinTExposicion(aux->exposicion), fecha) == 0 || compararTFechas(fechaFinTExposicion(aux->exposicion), fecha) == 1)){
        //caso borde activas es vacia
        if(exposicionesActivas == NULL){
            exposicionesActivas = aux;
            finActivas = exposicionesActivas;
            listaExposiciones = aux->sig;
            finActivas->sig = NULL;
            aux = listaExposiciones;
        // caso en que activas no es vacia
        }else{
            finActivas->sig = aux;
            finActivas = finActivas->sig;
            listaExposiciones = aux->sig;
            finActivas->sig = NULL;
            aux = listaExposiciones;
        }
    }
    // descartamos que el 1er elemento es activo y aux apunta a listaExposiciones
    // caso intermedio, avanzo agregando a activas y removiendo de lista original
    if(aux !=NULL){
        while(aux->sig != NULL){
            if((compararTFechas(fechaInicioTExposicion(aux->sig->exposicion), fecha) == 0 || compararTFechas(fechaInicioTExposicion(aux->sig->exposicion), fecha) == -1) && (compararTFechas(fechaFinTExposicion(aux->sig->exposicion), fecha) == 1 || compararTFechas(fechaFinTExposicion(aux->sig->exposicion), fecha) == 0)){
                // caso en que activas no es null
                if( exposicionesActivas != NULL){
                    finActivas->sig = aux->sig;
                    finActivas = finActivas->sig;
                    aux->sig = finActivas->sig;
                    finActivas->sig = NULL;
                    aux = aux->sig;
                }else{
                    exposicionesActivas = aux->sig;
                    finActivas = exposicionesActivas;
                    aux->sig = finActivas->sig;
                    finActivas->sig = NULL;
                }
            }else{
                if(aux != NULL){
                    aux = aux->sig;
                }
            }
        }
    }
    return exposicionesActivas;  
}

bool esCompatibleTListaExposiciones(TListaExposiciones listaExposiciones, TExposicion expo){

    if(listaExposiciones != NULL){
        while (listaExposiciones != NULL && sonExposicionesCompatibles(listaExposiciones->exposicion,expo)){
            listaExposiciones = listaExposiciones->sig;
        }
        return listaExposiciones == NULL;
    }else{
        return false;
    }
}

TListaExposiciones unirListaExposiciones(TListaExposiciones listaExpo1, TListaExposiciones listaExpo2){
    TListaExposiciones unionListas = NULL;
    TListaExposiciones finUnion = NULL;
    TListaExposiciones aux1 = listaExpo1;
    TListaExposiciones aux2 = listaExpo2;
    // while principal
    while(aux1 !=NULL && aux2 != NULL){
        // genero nodo a agregar.
        TListaExposiciones nodo = new rep_listaexposiciones;
        nodo->sig = NULL;
        // si fecha de l1 es menor igual que fecha l2
        if((compararTFechas(fechaInicioTExposicion(aux1->exposicion), fechaInicioTExposicion(aux2->exposicion)) == - 1 ) || (compararTFechas(fechaInicioTExposicion(aux1->exposicion), fechaInicioTExposicion(aux2->exposicion)) == 0)){
            //agrego en union.
            //caso borde union vacia
            if(unionListas == NULL){
                unionListas = nodo;
                finUnion = unionListas;
                nodo->exposicion = aux1->exposicion;
                aux1 = aux1->sig;
            }else{
                finUnion->sig = nodo;
                nodo->exposicion = aux1->exposicion;
                finUnion = nodo;
                aux1 = aux1->sig;
            }
        }else{
            if(unionListas == NULL){
                unionListas = nodo;
                finUnion = unionListas;
                nodo->exposicion = aux2->exposicion;
                aux2 = aux2->sig;
            }else{
                finUnion->sig = nodo;
                nodo->exposicion = aux2->exposicion;
                finUnion = nodo;
                aux2 = aux2->sig;
            }
        }
    }
    // caso borde l1 vacia o luego del while
    while(aux1 != NULL){
        // genero nodo a agregar.
        TListaExposiciones nodo = new rep_listaexposiciones;
        nodo->sig = NULL;
        //agrego en union.
        //caso borde union vacia
        if(unionListas == NULL){
                unionListas = nodo;
                finUnion = unionListas;
                nodo->exposicion = aux1->exposicion;
                aux1 = aux1->sig;
        }else{
                finUnion->sig = nodo;
                nodo->exposicion = aux1->exposicion;
                finUnion = nodo;
                aux1 = aux1->sig;
        }
    }
    // caso borde l2 vacia o luego del while
    while(aux2 != NULL){
        // genero nodo a agregar.
        TListaExposiciones nodo = new rep_listaexposiciones;
        nodo->sig = NULL;
        //agrego en union.
        //caso borde union vacia
        if(unionListas == NULL){
                unionListas = nodo;
                finUnion = unionListas;
                nodo->exposicion = aux2->exposicion;
                aux2 = aux2->sig;
        }else{
                finUnion->sig = nodo;
                nodo->exposicion = aux2->exposicion;
                finUnion = nodo;
                aux2 = aux2->sig;
        }
    }
    return unionListas; 
}



