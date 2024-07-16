#include "../include/coleccionPiezas.h"

struct rep_coleccionpiezas{
    TPieza pieza;
    TColeccionPiezas sig;
};

TColeccionPiezas crearColeccionPiezasVacia(){ 
    TColeccionPiezas coleccion = NULL;
    return coleccion; 
}

void insertarPiezaColeccionPiezas(TColeccionPiezas &coleccionPiezas, TPieza pieza){
    // genero el nodo  a insertar
    TColeccionPiezas nuevaPieza = new rep_coleccionpiezas;
    nuevaPieza->pieza = pieza;
    nuevaPieza->sig = NULL;
    TColeccionPiezas aux = coleccionPiezas;
    if(coleccionPiezas == NULL){
        //caso borde lista vacia
        coleccionPiezas = nuevaPieza;
    }else if(idTPieza(coleccionPiezas->pieza) > idTPieza(pieza)){
        // caso es menor a toda la lista no vacia
        coleccionPiezas = nuevaPieza;
        nuevaPieza->sig=aux;  
    }else{
        //recorro con auxiliar para no alterar coleccion hasta encontrar donde insertar (desde despues de 1er elem)
        while (aux->sig != NULL && idTPieza(aux->sig->pieza) < idTPieza(pieza)){
            aux=aux->sig;
        }
        nuevaPieza->sig=aux->sig;
        aux->sig=nuevaPieza;
    }
}

void imprimirColeccionPiezas(TColeccionPiezas coleccionPiezas){
    //aprovecho pasaje por valor y recorro imprimiendo, al finalizar la coleccion vuelve a apuntar al pincipio
   while(coleccionPiezas!=NULL){
    imprimirTPieza(coleccionPiezas->pieza);
    coleccionPiezas = coleccionPiezas->sig;
   }
}

bool esVaciaColeccionPiezas(TColeccionPiezas piezas){
    // si apunta a null esta vacia
    return piezas==NULL;
}

bool existePiezaColeccionPiezas(TColeccionPiezas coleccionPiezas, int idPieza){
    while(coleccionPiezas != NULL && idTPieza(coleccionPiezas->pieza) != idPieza){
        coleccionPiezas = coleccionPiezas -> sig;
    }
    return coleccionPiezas != NULL;
}

TPieza obtenerPiezaColeccionPiezas(TColeccionPiezas coleccionPiezas, int idPieza){
     while(coleccionPiezas != NULL && idTPieza(coleccionPiezas->pieza) != idPieza){
        coleccionPiezas = coleccionPiezas -> sig;
    }
    return coleccionPiezas->pieza;
}
//precondicion el id esta en lista, no tomo en cuenta caso como lista vacia
void removerPiezaColeccionPiezas(TColeccionPiezas &coleccionPiezas, int idPieza){
    TColeccionPiezas aux;
    aux = coleccionPiezas;
        //caso borde, es el primer elemento
    if(idTPieza(coleccionPiezas->pieza) == idPieza){
        //borrado logico
        coleccionPiezas= coleccionPiezas->sig;
        //borrado fisico
        liberarTPieza(aux->pieza);
        delete aux;
    }else{
        //Busco y borro.
        //utilizo el limitante del !=NULL pero no deberia ser necesario por precondicion
        while(aux->sig != NULL && idTPieza(aux->sig->pieza) != idPieza){
            aux = aux->sig;
        }
        // declaro un aux2 para el borrado fisico.
        TColeccionPiezas aux2;
        aux2=aux->sig;
        //borrado logico
        aux->sig = aux2->sig;
        //borrado fisico
        liberarTPieza(aux2->pieza);
        delete aux2;
    }
}

void liberarColeccionPiezas(TColeccionPiezas &coleccionPiezas){
        TColeccionPiezas aux;
        aux = coleccionPiezas;
        while (aux != NULL){
            coleccionPiezas=aux->sig;
            liberarTPieza(aux->pieza);
            delete aux;
            aux=coleccionPiezas;
        }
}