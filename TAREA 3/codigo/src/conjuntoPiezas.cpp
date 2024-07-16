#include "../include/conjuntoPiezas.h"

struct rep_conjuntopiezas{
    int cantidadMax;
    int cantidad;
    int * piezas;
};

TConjuntoPiezas crearTConjuntoPiezas(int cantMax){
    TConjuntoPiezas conjuntoPiezas = new rep_conjuntopiezas;
    conjuntoPiezas->cantidadMax = cantMax;
    conjuntoPiezas->cantidad = 0;
    conjuntoPiezas->piezas = new int[cantMax];
    for(int i= 0; i < cantMax; i++){
        conjuntoPiezas->piezas[i] = 0;
    }
    return conjuntoPiezas;
}

bool esVacioTConjuntoPiezas(TConjuntoPiezas c){ 
    return c->cantidad == 0;
}

void insertarTConjuntoPiezas(TConjuntoPiezas &c, int id){
    if( id >= 0 && id < c->cantidadMax){
        if(c->piezas[id] != 1){
            c->piezas[id] = 1;
            c->cantidad++;
        } 
    }
}

void borrarDeTConjuntoPiezas(TConjuntoPiezas &c, int id){
     if( id >= 0 && id < c->cantidadMax){
        if(c->piezas[id] != 0){
            c->piezas[id] = 0;
            c->cantidad--;
        } 
    }
}

bool perteneceTConjuntoPiezas(TConjuntoPiezas c, int id){
    if( id >= 0 && id < c->cantidadMax){
        return c->piezas[id] == 1; 
    }else{
        return false;
    }
}

int cardinalTConjuntoPiezas(TConjuntoPiezas c){ 
    return c->cantidad;
}

int cantMaxTConjuntoPiezas(TConjuntoPiezas c){ 
    return c->cantidadMax; 
}

void imprimirTConjuntoPiezas(TConjuntoPiezas c){
    for(int i=0; i < c->cantidadMax; i++){
        if(c->piezas[i] == 1){
            printf("%d ", i);
        }
    }
    printf("\n");
}

void liberarTConjuntoPiezas(TConjuntoPiezas &c){
    delete [] c->piezas;
    delete c;
    c = NULL;
}

TConjuntoPiezas unionTConjuntoPiezas(TConjuntoPiezas c1, TConjuntoPiezas c2){ 
    TConjuntoPiezas c3 = crearTConjuntoPiezas(c1->cantidadMax);
    for(int i=0; i < c1->cantidadMax; i++){
        if(c1->piezas[i] == 1 || c2->piezas[i] == 1){
            insertarTConjuntoPiezas(c3, i);
        }
    }
    return c3; 
}

TConjuntoPiezas interseccionTConjuntoPiezas(TConjuntoPiezas c1, TConjuntoPiezas c2){ 
    TConjuntoPiezas c3 = crearTConjuntoPiezas(c1->cantidadMax);
    for(int i=0; i < c1->cantidadMax; i++){
        if(c1->piezas[i] == 1 && c2->piezas[i] == 1){
            insertarTConjuntoPiezas(c3, i);
        }
    }
    return c3; 
}

TConjuntoPiezas diferenciaTConjuntoPiezas(TConjuntoPiezas c1, TConjuntoPiezas c2){ 
    TConjuntoPiezas c3 = crearTConjuntoPiezas(c1->cantidadMax);
    for(int i=0; i < c1->cantidadMax; i++){
        if(c1->piezas[i] == 1 && !(c2->piezas[i] == 1)){
            insertarTConjuntoPiezas(c3, i);
        }
    }
    return c3;
}
