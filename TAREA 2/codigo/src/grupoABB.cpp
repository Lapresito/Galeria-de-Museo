#include "../include/grupoABB.h"

struct rep_grupoABB {
    TVisitante visitante;
    TGrupoABB izq;
    TGrupoABB der;
};

TGrupoABB crearTGrupoABBVacio(){
    TGrupoABB nuevoGrupo;
    nuevoGrupo = NULL;
    return nuevoGrupo;
}

void insertarTVisitanteTGrupoABB(TGrupoABB &grupoABB, TVisitante visitante){
    // key de inserscion = idVisitante
    if(grupoABB == NULL){
        // Si llego a destino, genero la hoja (agrego el visitante al grupo ABB)
        grupoABB = new rep_grupoABB;
        grupoABB->visitante = visitante;
        grupoABB->izq=NULL;
        grupoABB->der=NULL;
    }else if(idTVisitante(grupoABB->visitante) < idTVisitante(visitante)){
        // si es mayor el id, va hacia la derecha
        insertarTVisitanteTGrupoABB(grupoABB->der, visitante);
    }else if(idTVisitante(grupoABB->visitante) > idTVisitante(visitante)){
        // si es menor el id, va hacia la izq
        insertarTVisitanteTGrupoABB(grupoABB->izq, visitante);
    }
}

void imprimirTGrupoABB(TGrupoABB grupoABB){
    if(grupoABB != NULL){
        // imprimo InOrder
        imprimirTGrupoABB(grupoABB->izq);
        imprimirTVisitante(grupoABB->visitante);
        imprimirTGrupoABB(grupoABB->der);
    }
}

bool existeTVisitanteTGrupoABB(TGrupoABB grupoABB, int idVisitante){
    while((grupoABB != NULL) && (idTVisitante(grupoABB->visitante) != idVisitante)){
        if(idTVisitante(grupoABB->visitante) > idVisitante){
            grupoABB=grupoABB->izq;
        }else{
            grupoABB=grupoABB->der;
        }
    }
    return (grupoABB!=NULL);
}
//precondicion el id existe, no chequeo null
TVisitante obtenerTVisitanteTGrupoABB(TGrupoABB grupoABB, int idVisitante){
    while((grupoABB != NULL) && (idTVisitante(grupoABB->visitante) != idVisitante)){
        if(idTVisitante(grupoABB->visitante) > idVisitante){
            grupoABB=grupoABB->izq;
        }else{
            grupoABB=grupoABB->der;
        }
    }
    return (grupoABB->visitante);
}

// Defino funcion auxiliar para buscar el maximo de un arbol y devolver el puntero a el nodo con ese valor.
// se podria reutilizar la maxIdVisitante pero devuelve un visitante, preciso puntero, por lo que solo cambio el return
TGrupoABB max(TGrupoABB grupoABB){
    if(grupoABB==NULL){
        return NULL;
    }else{
        //me muevo solo a la derecha ya que para ese lado estan los mayores
        while (grupoABB->der != NULL){
            grupoABB = grupoABB->der;
        }
        return grupoABB;
    }
    
}
void removerTVisitanteTGrupoABB(TGrupoABB &grupoABB, int idVisitante){
    if( grupoABB != NULL ){
        if(idVisitante < idTVisitante(grupoABB->visitante)){
            //avanzo a la izq si es menor
            removerTVisitanteTGrupoABB(grupoABB->izq, idVisitante);
        }else if(idVisitante > idTVisitante(grupoABB->visitante)){
            //avanzo a la der si es mayor
            removerTVisitanteTGrupoABB(grupoABB->der, idVisitante);
        }else{
            // encontre el id
            //caso nodo sin subarbol a la derecha
            if(grupoABB->der == NULL){
                TGrupoABB aux = grupoABB;
                //borrado logico
                grupoABB = grupoABB->izq;
                //borrado fisico
                liberarTVisitante(aux->visitante);
                delete aux;
            //caso nodo sin subarbol a la izq
            }else if(grupoABB->izq == NULL){
                TGrupoABB aux = grupoABB;
                //borrado logico
                grupoABB = grupoABB->der;
                //borrado fisico
                liberarTVisitante(aux->visitante);
                delete aux;
            //caso con dos subarboles
            }else{
                TGrupoABB aux = grupoABB;
                aux = max(grupoABB->izq);
                liberarTVisitante(grupoABB->visitante);
                grupoABB->visitante = copiarTVisitante(aux->visitante);
                //eliminamos el elemento en la posicion del maximo de la rama izquierda
                removerTVisitanteTGrupoABB(grupoABB->izq, idTVisitante(aux->visitante));
            }
        }
    }
}

nat alturaTGrupoABB(TGrupoABB grupoABB) {
    //caso base de recursion
    if(grupoABB == NULL){
        return 0;
         // por def inductiva altura es 1 (raiz) + max(arbol izq, arbol der) / me quedo con la altura mayor usando if
    }else if( alturaTGrupoABB(grupoABB->izq) > alturaTGrupoABB(grupoABB->der) ) {
        return 1 + alturaTGrupoABB(grupoABB->izq);
    } else {
        return 1 + alturaTGrupoABB(grupoABB->der);
    }
}

int cantidadVisitantesTGrupoABB(TGrupoABB grupoABB){
    if(grupoABB ==NULL){
        return 0;
    }else{
        // sumo 1 por cada  visitante en el arbol y luego le sumo lo que hay en los arboles hijos
        return 1 + cantidadVisitantesTGrupoABB(grupoABB->izq) + cantidadVisitantesTGrupoABB(grupoABB->der);
    }
}


// funcion para sumar edades de todos los participantes
int sumaEdades(TGrupoABB grupoABB){
    if (grupoABB != NULL){
        return  edadTVisitante(grupoABB->visitante) + sumaEdades(grupoABB->izq) + sumaEdades(grupoABB->der);
    }else{
        return 0;
    }
}
float edadPromedioTGrupoABB(TGrupoABB grupoABB) {
    if(grupoABB == NULL){
        return 0;
    }else{
        float n=cantidadVisitantesTGrupoABB(grupoABB);
        float edades=sumaEdades(grupoABB);
        // retorno acumulacion dividida entre la cantidad de nodos para obtener la edad promedio.
        return edades/n;
    }
    
}

void liberarTGrupoABB(TGrupoABB &grupoABB){
    if(grupoABB!=NULL){
        liberarTVisitante(grupoABB->visitante);
        liberarTGrupoABB(grupoABB->izq);
        liberarTGrupoABB(grupoABB->der);
        delete grupoABB;
        grupoABB = NULL;
    }
}

TVisitante maxIdTVisitanteTGrupoABB(TGrupoABB grupoABB){
    //No tomo en cuenta arbol vacio ya que es precondicion no vacio
    //me muevo solo a la derecha ya que para ese lado estan los mayores
    while (grupoABB->der != NULL){
        grupoABB = grupoABB->der;
    }
    return grupoABB->visitante;
}
//Definicion de lista auxiliar
typedef struct rep_listaABBaplanado *TListaABBaplanado;
struct rep_listaABBaplanado{
    TVisitante visitante;
    TListaABBaplanado sig;
};
//Funcion auxiliar para insertar al principio de lsita utilizando copia de visitante
TListaABBaplanado insertarPrincipio(TListaABBaplanado &lista, TVisitante visitante){
    //creo nodo
    TListaABBaplanado nuevo = new rep_listaABBaplanado;
    //nuevo->visitante = copiarTVisitante(visitante);
    nuevo->visitante = visitante;
    nuevo->sig=NULL;
    // si la lista esta vacia
    if(lista == NULL){
        lista=nuevo;
    }else{
        //asigno siguiente incialmente a null
        nuevo->sig = lista;
        lista=nuevo;
    }
    return lista;
}

//Funcion auxiliar para aplanar arbolBB a lista
TListaABBaplanado aplanadorABB(TGrupoABB grupoABB, TListaABBaplanado &lista){
    if(grupoABB != NULL){
        //recorro inorder(invertido) insertando al principio de la lista para que quede de - a +
        aplanadorABB(grupoABB->der, lista);
        insertarPrincipio(lista, grupoABB->visitante);
        aplanadorABB(grupoABB->izq, lista);
    }
    return lista;
}

TVisitante obtenerNesimoVisitanteTGrupoABB(TGrupoABB grupoABB, int n){
    TVisitante retorno = NULL;
    TListaABBaplanado arbolAplanado = NULL;
    TListaABBaplanado aux1 = NULL;
    //lleno el arbolAplanado con los nodos del arbol en orden inversivo
    arbolAplanado = aplanadorABB(grupoABB, arbolAplanado);
    //recorro el arbol hasta n
    int i = 1;
    aux1 = arbolAplanado;
    while( aux1 != NULL && i < n ){
        aux1 = aux1->sig;
        i++;
    }
    //retorno el n-esimo Visitante
    retorno = aux1->visitante;
    //libero lista
    TListaABBaplanado aux;
    aux = arbolAplanado;
    while(aux !=NULL){
        arbolAplanado = aux->sig;
        //liberarTVisitante(aux->visitante);
        delete aux;
        aux = arbolAplanado;
    }
    return retorno;
}