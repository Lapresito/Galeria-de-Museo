#include "../include/visitaDia.h"

typedef struct rep_nodoVisitaDia * TNodoDoble;

struct rep_nodoVisitaDia{
    TGrupoABB grupo;
    TNodoDoble sig;
    TNodoDoble ant;
};

//struct cabezal
struct rep_visitadia{
    TFecha diaDeVisita;
    int cantidadGrupos;
    TNodoDoble ini;
    TNodoDoble fin;
};


TVisitaDia crearTVisitaDia(TFecha fecha){ 
    TVisitaDia visitaDia = new rep_visitadia;
    visitaDia->diaDeVisita = fecha;
    visitaDia->cantidadGrupos = 0;
    visitaDia->ini = NULL;
    visitaDia->fin = NULL;
    return visitaDia;
}

void encolarGrupoTVisitaDia(TVisitaDia &visitaDia, TGrupoABB grupo){
    if(visitaDia != NULL){
        //creo nodo
        TNodoDoble nuevo = new rep_nodoVisitaDia;
        nuevo->grupo = grupo;
        nuevo->sig = NULL;
        nuevo->ant = NULL;
        if(visitaDia->cantidadGrupos == 0){
            visitaDia->fin = nuevo;
            visitaDia->ini = nuevo;
            visitaDia->cantidadGrupos++;
        }else{
            nuevo->sig = visitaDia->ini;
            visitaDia->ini->ant = nuevo;
            visitaDia->ini = nuevo;
            visitaDia->cantidadGrupos++;
        }
    }
}

int cantidadGruposTVisitaDia(TVisitaDia visitaDia){
    if( visitaDia != NULL ){
        return visitaDia->cantidadGrupos;
    }else{
        return 0;
    }
}

void imprimirVisitaDia(TVisitaDia visitaDia){
    if(visitaDia != NULL){
        printf("Visita para dia: ");
        imprimirTFecha(visitaDia->diaDeVisita);
        printf("\n");
        TNodoDoble aux = visitaDia->ini;
        while(aux != NULL){
            imprimirTGrupoABB(aux->grupo);
            aux = aux->sig;
        }
        
    }
}

TGrupoABB desencolarGrupoTVisitaDia(TVisitaDia &visitaDia){ 
    if(visitaDia->fin != NULL){
        TNodoDoble aBorrar = visitaDia->fin;
        TGrupoABB retorno = aBorrar->grupo;
        if( visitaDia->cantidadGrupos > 1){
            visitaDia->fin = aBorrar->ant;
            visitaDia->fin->sig = NULL;
        }else{
            visitaDia->fin = NULL;
            visitaDia->ini = NULL;
        }
        visitaDia->cantidadGrupos--;
        delete aBorrar;
        return retorno;
    }else{
        return NULL;
    }

}

void liberarTVisitaDia(TVisitaDia &visitaDia){
    if(visitaDia != NULL){
        while (visitaDia->ini != NULL){
            TNodoDoble aBorrar = visitaDia->ini;
            visitaDia->ini = aBorrar->sig;
            liberarTGrupoABB(aBorrar->grupo);
            delete aBorrar;
        }
        liberarTFecha(visitaDia->diaDeVisita);
        delete visitaDia;
        visitaDia = NULL;
    }
}

