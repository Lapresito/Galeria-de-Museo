#include "../include/exposicion.h"

struct rep_exposicion{
    int id;
    TFecha ini;
    TFecha fin;
    TConjuntoPiezas piezas;
};

TExposicion crearTExposicion(int idExp, TFecha ini, TFecha fin, int cantMax){
    TExposicion exposicion = new rep_exposicion;
    exposicion->id = idExp;
    exposicion->ini = ini;
    exposicion->fin = fin;
    exposicion->piezas = crearTConjuntoPiezas(cantMax);
    return exposicion; 
}

void agregarATExposicion(TExposicion &exp, TPieza p){
    insertarTConjuntoPiezas(exp->piezas, idTPieza(p));
}

bool perteneceATExposicion(TExposicion exp, TPieza p){ 
    return perteneceTConjuntoPiezas(exp->piezas, idTPieza(p)); 
}

int idTExposicion(TExposicion exp){
    if(exp != NULL){
        return exp->id;
    } else{
        return 0; 
    }
}

void imprimirTExposicion(TExposicion exp){
    if(exp != NULL){
        printf("Exposicion #%d del ", exp->id);
        imprimirTFecha(exp->ini);
        printf(" al ");
        imprimirTFecha(exp->fin);
        printf("\n");
        printf("Piezas: ");
        imprimirTConjuntoPiezas(exp->piezas);
    }
}

TFecha fechaInicioTExposicion(TExposicion exp){ 
    if(exp != NULL){
        return exp->ini;
    } else{
        return NULL; 
    }
}

TFecha fechaFinTExposicion(TExposicion exp){ 
     if(exp != NULL){
        return exp->fin;
    } else{
        return NULL; 
    }
}

bool sonExposicionesCompatibles(TExposicion exp1, TExposicion exp2){ 
    if(exp1 != NULL && exp2 != NULL){
        
        //1er caso exp1 ocurre despues que exp2
        if(compararTFechas(exp1->ini, exp2->fin) == 1){
            return true;
        //2do caso exp1 ocurre antes
        }else if(compararTFechas(exp2->ini, exp1->fin) == 1){
            return true;
        //3er caso, se cruzan algun dia
        }else{
            TConjuntoPiezas interseccion = interseccionTConjuntoPiezas(exp1->piezas, exp2->piezas);
            int cant = cardinalTConjuntoPiezas(interseccion);
            liberarTConjuntoPiezas(interseccion);
            if(cant == 0){
                return true;
            }else{
                return false;
            }
        }
    }else{
        return false;
    }
}

void liberarTExposicion(TExposicion &exp){
    if(exp != NULL){
        liberarTConjuntoPiezas(exp->piezas);
        liberarTFecha(exp->ini);
        liberarTFecha(exp->fin);
        delete exp;
        exp = NULL;
    }
}

