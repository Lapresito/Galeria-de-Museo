#include "../include/grupoABB.h"

struct rep_grupoABB {
    TVisitante visitante;
    TGrupoABB izq, der;
};

TGrupoABB crearTGrupoABBVacio(){
    return NULL;
}

void insertarTVisitanteTGrupoABB(TGrupoABB &grupoABB, TVisitante visitante){
    if (grupoABB == NULL) {
        grupoABB = new rep_grupoABB;
        grupoABB->visitante = visitante;
        grupoABB->izq = NULL;
        grupoABB->der = NULL;
    } else {
        if (idTVisitante(visitante) < idTVisitante(grupoABB->visitante)) {
            insertarTVisitanteTGrupoABB(grupoABB->izq, visitante);
        } else {
            insertarTVisitanteTGrupoABB(grupoABB->der, visitante);
        }
    }
}

void imprimirTGrupoABB(TGrupoABB grupoABB){
    if (grupoABB != NULL) {
        imprimirTGrupoABB(grupoABB->izq);
        imprimirTVisitante(grupoABB->visitante);
        imprimirTGrupoABB(grupoABB->der);
    }
}

// implementación lineal para fallar el test de tiempo
bool existeTVisitanteTGrupoABBBogus(TGrupoABB grupoABB, int idVisitante){
    if (grupoABB == NULL) {
        return false;
    } else {
        TGrupoABB temp = NULL;
        for (int i = 0; i < 1000000; i++){
            if (i % 2 == 0){
                temp = grupoABB->izq;
            }else{
                temp = grupoABB->der;
            }
        }
        if (temp == NULL){
            return true;
        }else{
            return true;
        }
        // bool existeIzq = existeTVisitanteTGrupoABB(grupoABB->izq, idVisitante);
        // bool existeDer = existeTVisitanteTGrupoABB(grupoABB->der, idVisitante);
        // return existeIzq || existeDer || idVisitante == idTVisitante(grupoABB->visitante);
    }
}

bool existeTVisitanteTGrupoABB(TGrupoABB grupoABB, int idVisitante){
    if (grupoABB == NULL) {
        return false;
    } else {
        if (idVisitante < idTVisitante(grupoABB->visitante)) {
            return existeTVisitanteTGrupoABB(grupoABB->izq, idVisitante);
        } else if (idVisitante > idTVisitante(grupoABB->visitante)) {
            return existeTVisitanteTGrupoABB(grupoABB->der, idVisitante);
        } else {
            return true;
        }
    }
}

TVisitante obtenerTVisitanteTGrupoABB(TGrupoABB grupoABB, int idVisitante){
    if (idVisitante < idTVisitante(grupoABB->visitante)) {
        return obtenerTVisitanteTGrupoABB(grupoABB->izq, idVisitante);
    } if (idVisitante > idTVisitante(grupoABB->visitante)) {
        return obtenerTVisitanteTGrupoABB(grupoABB->der, idVisitante);
    } else {
        return grupoABB->visitante;
    }
}

// función auxiliar para liberar un nodo
void liberarNodoTGrupoABB(TGrupoABB &grupoABB) {
    liberarTVisitante(grupoABB->visitante);
    delete grupoABB;
    grupoABB = NULL;
}

void removerTVisitanteTGrupoABB(TGrupoABB &grupoABB, int idVisitante){
    if (grupoABB != NULL) {
        if (idVisitante < idTVisitante(grupoABB->visitante)) {
            removerTVisitanteTGrupoABB(grupoABB->izq, idVisitante);
        } else if (idVisitante > idTVisitante(grupoABB->visitante)) {
            removerTVisitanteTGrupoABB(grupoABB->der, idVisitante);
        } else if (grupoABB->izq == NULL && grupoABB->der == NULL) {
            liberarNodoTGrupoABB(grupoABB);
        } else {
            if (grupoABB->izq == NULL) {
                TGrupoABB aux = grupoABB;
                grupoABB = grupoABB->der;
                liberarNodoTGrupoABB(aux);
            } else if (grupoABB->der == NULL) {
                TGrupoABB aux = grupoABB;
                grupoABB = grupoABB->izq;
                liberarNodoTGrupoABB(aux);
            } else {
                liberarTVisitante(grupoABB->visitante);
                grupoABB->visitante = copiarTVisitante(maxIdTVisitanteTGrupoABB(grupoABB->izq));
                removerTVisitanteTGrupoABB(grupoABB->izq, idTVisitante(grupoABB->visitante));
            }
        }
    }
}

nat alturaTGrupoABB(TGrupoABB grupoABB) {
    if (grupoABB == NULL) {
        return 0;
    } else {
        nat alturaIzq = alturaTGrupoABB(grupoABB->izq);
        nat alturaDer = alturaTGrupoABB(grupoABB->der);
        if (alturaIzq > alturaDer) {
            return 1 + alturaIzq;
        } else {
            return 1 + alturaDer;
        }
    }
}

int cantidadVisitantesTGrupoABB(TGrupoABB grupoABB){
    if (grupoABB == NULL) {
        return 0;
    } else {
        int cantVisitantesIzq = cantidadVisitantesTGrupoABB(grupoABB->izq);
        int cantVisitantesDer = cantidadVisitantesTGrupoABB(grupoABB->der);
        return 1 + cantVisitantesIzq + cantVisitantesDer;
    }
}

int edadTotalVisitantesTGrupoABB(TGrupoABB grupoABB){
    if (grupoABB == NULL) {
        return 0;
    } else {
        int edadTotalIzq = edadTotalVisitantesTGrupoABB(grupoABB->izq);
        int edadTotalDer = edadTotalVisitantesTGrupoABB(grupoABB->der);
        return edadTVisitante(grupoABB->visitante) + edadTotalIzq + edadTotalDer;
    }
}

float edadPromedioTGrupoABB(TGrupoABB grupoABB) {
    int cantidadVisitantes = cantidadVisitantesTGrupoABB(grupoABB);
    if (cantidadVisitantes == 0){
        return 0;
    }else{
        int edadTotal = edadTotalVisitantesTGrupoABB(grupoABB);
        return edadTotal / ((float) cantidadVisitantes);
    }
}

void liberarTGrupoABB(TGrupoABB &grupoABB){
    if (grupoABB != NULL) {
        liberarTGrupoABB(grupoABB->izq);
        liberarTGrupoABB(grupoABB->der);
        liberarNodoTGrupoABB(grupoABB);
    }
}

TVisitante maxIdTVisitanteTGrupoABB(TGrupoABB grupoABB){
    if (grupoABB->der == NULL) {
        return grupoABB->visitante;
    } else {
        return maxIdTVisitanteTGrupoABB(grupoABB->der);
    }
}

TVisitante obtenerNesimoVisitanteTGrupoABB(TGrupoABB grupoABB, int n){
    int cantIzq = cantidadVisitantesTGrupoABB(grupoABB->izq);
    if (cantIzq >= n) {
        return obtenerNesimoVisitanteTGrupoABB(grupoABB->izq, n);
    } else if (n == cantIzq + 1){
        return grupoABB->visitante;
    } else {
        return obtenerNesimoVisitanteTGrupoABB(grupoABB->der, n - cantIzq - 1);
    }
}

