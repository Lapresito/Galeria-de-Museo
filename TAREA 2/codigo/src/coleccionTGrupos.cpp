#include "../include/coleccionTGrupos.h"

// defino struct auxiliar para nodos doblemente enlazados
typedef struct rep_nodoColeccionTGrupos * TNodoDoble;

struct rep_nodoColeccionTGrupos {
	TGrupoABB grupoABB;
	TNodoDoble sig;
	TNodoDoble ant;
};

//struct de cabezal
struct rep_coleccionTGrupos {
	TNodoDoble ini;
	TNodoDoble fin;
};

TColeccionTGrupos crearTColeccionTGruposVacia(){
	// genero cabezal con null null
	TColeccionTGrupos coleccion = new rep_coleccionTGrupos;
	coleccion->ini=NULL;
	coleccion->fin=NULL;
	return coleccion;
}

void insertarGrupoTColeccionTGrupos(TColeccionTGrupos coleccion, TGrupoABB grupo){
	//genero nodo a insertar
	TNodoDoble nuevo = new rep_nodoColeccionTGrupos;
	nuevo->grupoABB = grupo;
	nuevo->sig = NULL;
	nuevo->ant = NULL;
	if (coleccion->ini == NULL){ // si es la primera insercion
		coleccion->ini = nuevo;
		coleccion->fin = nuevo;
	} else if(coleccion->ini != NULL && edadPromedioTGrupoABB(coleccion->ini->grupoABB) > edadPromedioTGrupoABB(grupo)){
		 //el que inserto es menor al primero, lo inserto al principio
		coleccion->ini->ant = nuevo;
		nuevo->sig = coleccion->ini; 
		coleccion->ini=nuevo;
	}else{
		//inserto del segundo en adelante, no modifico ini de cabezal.
		// utilizo auxiliar para recorrer
		TNodoDoble aux = coleccion->ini;
		while(aux != NULL && edadPromedioTGrupoABB(aux->grupoABB) <= edadPromedioTGrupoABB(grupo)){
			aux = aux->sig;
		}
		//estoy en el medio
		if(aux !=NULL){
			aux->ant->sig = nuevo;
			nuevo->ant = aux->ant;
			nuevo->sig = aux;
			aux->ant=nuevo;
		}else if(aux == NULL){ //estoy al final, agrego y modifico cabezal
			coleccion->fin->sig = nuevo;
			nuevo->ant = coleccion->fin;
			coleccion->fin = nuevo;
		}
	}

}

void imprimirTColeccionTGrupos(TColeccionTGrupos coleccion){
	if( coleccion != NULL){
		TNodoDoble aux = coleccion->ini;
		printf("Coleccion de grupos:\n");
		while (aux !=NULL){
			float edadProm = edadPromedioTGrupoABB(aux->grupoABB);
			printf("Grupo con edad promedio %.2f:\n", edadProm);
			imprimirTGrupoABB(aux->grupoABB);
			aux=aux->sig;
		}
	}

}

void imprimirInvertidoTColeccionTGrupos(TColeccionTGrupos coleccion){
	if( coleccion != NULL){
		TNodoDoble aux = coleccion->fin;
		printf("Coleccion de grupos:\n");
		while (aux !=NULL){
			float edadProm = edadPromedioTGrupoABB(aux->grupoABB);
			printf("Grupo con edad promedio %.2f:\n", edadProm);
			imprimirTGrupoABB(aux->grupoABB);
			aux = aux->ant;
		}
	}
}

nat cantidadTGruposColeccionTGrupos(TColeccionTGrupos coleccion){
	if(coleccion->ini == NULL || coleccion == NULL){
		return 0;
	}else{
		TNodoDoble aux = coleccion->ini;
		nat contador = 0;
		while(aux != NULL) {
			contador++;
			aux=aux->sig;
		}
		return contador;
	}
}

TGrupoABB obtenerNesimoColeccionTGrupos(TColeccionTGrupos coleccion, int n){
	//obtengo canidad en O(n)
	int cantidad = cantidadTGruposColeccionTGrupos(coleccion);
	if( n > cantidad || n < 1){
		return NULL; //Error: El numero no esta entre los posibles.
	}else{
		TNodoDoble aux = coleccion->ini;
		int contador = 1;
		while ((aux != NULL) && contador < n ){
			contador++;
			aux = aux->sig;
		}
		return aux->grupoABB;
	}
}

TGrupoABB obtenerPrimeroColeccionTGrupos(TColeccionTGrupos coleccion){
	return coleccion->ini->grupoABB;
}

TGrupoABB removerUltimoColeccionTGrupos(TColeccionTGrupos coleccion){
	// defino cantidad
	nat cantidad = cantidadTGruposColeccionTGrupos(coleccion);
	// defino retorno
	TGrupoABB grupoRetornar = NULL;
	//descarto que no tenga un solo elemento
	if(cantidad == 1){
		//asignacion a retorno
		grupoRetornar = coleccion->ini->grupoABB;
		//borrado fisico
		delete coleccion->ini;
		//borrado logico
		coleccion->ini=NULL;
		coleccion->fin=NULL;
	}else{
		// defino auxiliar para borrado fisico
		TNodoDoble aux = coleccion->fin;
		//borrado logico
		coleccion->fin = aux->ant;
		coleccion->fin->sig = NULL;
		//asignacion a retorno
		grupoRetornar = aux->grupoABB;
		//borrado  fisico
		delete aux;
	}
	return grupoRetornar;
}

//funcion auxiliar apra remover primer elemento
TGrupoABB removerPrimerColeccionTGrupos(TColeccionTGrupos coleccion){
	// defino retorno
	TGrupoABB grupoRetornar = NULL;
	//descarto que no tenga un solo elemento
	if(coleccion->fin == coleccion->ini){
		//asignacion a retorno
		grupoRetornar = coleccion->ini->grupoABB;
		//borrado fisico
		delete coleccion->ini;
		//borrado logico
		coleccion->ini=NULL;
		coleccion->fin=NULL;
	}else{
		// defino auxiliar para borrado fisico
		TNodoDoble aux = coleccion->ini;
		//borrado logico
		coleccion->ini = aux->sig;
		aux->sig->ant = NULL;
		//asignacion a retorno
		grupoRetornar = aux->grupoABB;
		//borrado  fisico
		delete aux;
	}
	return grupoRetornar;
}

TGrupoABB removerNesimoColeccionTGrupos(TColeccionTGrupos coleccion, int n){
	// utilizo cantidad para caso borde
	int cantidad = cantidadTGruposColeccionTGrupos(coleccion);
	//printf("cantidadddddd %d", cantidad);
	// defino retorno
	TGrupoABB grupoRetornar = NULL;
	// precondicion n <= cantidad elems en lista;
	//casos borde
	if(n==1){
		return removerPrimerColeccionTGrupos(coleccion);
	}else if(n==cantidad){
		return removerUltimoColeccionTGrupos(coleccion);
	}else{
		TNodoDoble aux = coleccion->ini;
		int cont = 1;
		while ((aux != NULL) && cont < n ){
			cont++;
			aux = aux->sig;
		}
		//asigno retorno
		grupoRetornar = aux->grupoABB;
		//borrado logico
		aux->ant->sig = aux->sig;
		aux->sig->ant = aux->ant;
		//borrado fisico
		delete aux;
		return grupoRetornar;
	}
}

void liberarTColeccionTGrupos(TColeccionTGrupos &coleccion){
	if(coleccion != NULL){
		//defino auxiliar para recorrer coleccion y lo asigno al 1er elemento
		TNodoDoble aux = coleccion->ini;
		while(aux != NULL){
			//borrado logico
			coleccion->ini = aux->sig;
			//borrado fisico
			liberarTGrupoABB(aux->grupoABB);
			delete aux;
			//asignacion de nuevo valor a aux
			aux = coleccion->ini;
		}
		// borrado  del puntero a la cabezal
		delete coleccion;
		//Asignacion de NULL
		coleccion = NULL;
	}

}

// defino nueva struct con repeticiones
typedef struct rep_arbolConRepetidos * TGrupoABBRepetidos;
struct rep_arbolConRepetidos {
	int repeticiones;
	TVisitante visitante;
	TGrupoABBRepetidos izq;
	TGrupoABBRepetidos der;
};
// se define nuevamente grupoABB para poder moverme por el arbol
typedef struct rep_grupoABB * TGrupoABB;
struct rep_grupoABB {
    TVisitante visitante;
    TGrupoABB izq;
    TGrupoABB der;
};
// funcion auxiliar para insertar ordenadamente en arbol con repeticion *casi misma funcion que en grupoABB*
void insertarTVisitanteTGrupoABBRepetidos(TGrupoABBRepetidos &grupoABB, TVisitante visitante){
    // key de inserscion = idVisitante
    if(grupoABB == NULL){
        // Si no existe, genero la hoja (agrego el visitante al grupo ABB)
        grupoABB = new rep_arbolConRepetidos;
		grupoABB->repeticiones = 0;
        grupoABB->visitante = copiarTVisitante(visitante);
        grupoABB->izq=NULL;
        grupoABB->der=NULL;
    }else if(idTVisitante(grupoABB->visitante) < idTVisitante(visitante)){
        // si es mayor el id, va hacia la derecha
        insertarTVisitanteTGrupoABBRepetidos(grupoABB->der, visitante);
    }else if(idTVisitante(grupoABB->visitante) > idTVisitante(visitante)){
        // si es menor el id, va hacia la izq
        insertarTVisitanteTGrupoABBRepetidos(grupoABB->izq, visitante);
    }else if(idTVisitante(grupoABB->visitante) == idTVisitante(visitante)){
		//si son iguales sumo una repeticion
    	(grupoABB->repeticiones)++;
	}
}

void insertarTVisitanteTGrupoABBconCopia(TGrupoABB &grupoABB, TVisitante visitante){
    // key de inserscion = idVisitante
    if(grupoABB == NULL){
        // Si llego a destino, genero la hoja (agrego el visitante al grupo ABB)
        grupoABB = new rep_grupoABB;
        grupoABB->visitante = copiarTVisitante(visitante);
        grupoABB->izq=NULL;
        grupoABB->der=NULL;
    }else if(idTVisitante(grupoABB->visitante) < idTVisitante(visitante)){
        // si es mayor el id, va hacia la derecha
        insertarTVisitanteTGrupoABBconCopia(grupoABB->der, visitante);
    }else if(idTVisitante(grupoABB->visitante) > idTVisitante(visitante)){
        // si es menor el id, va hacia la izq
        insertarTVisitanteTGrupoABBconCopia(grupoABB->izq, visitante);
    }
}

// funcion para recorrer un arbol agregandolos a la copia
void recorridoCopiarArbol(TGrupoABBRepetidos &grupoABBTodos, TGrupoABB grupoABB){
	if(grupoABB != NULL){
			//recorro inOrder insertando
			recorridoCopiarArbol(grupoABBTodos, grupoABB->izq);
			insertarTVisitanteTGrupoABBRepetidos(grupoABBTodos, grupoABB->visitante);
			recorridoCopiarArbol(grupoABBTodos, grupoABB->der);
		}
}
void liberarTGrupoABBRepetidos(TGrupoABBRepetidos &grupoABB){
	if(grupoABB != NULL){
		liberarTVisitante(grupoABB->visitante);
        liberarTGrupoABBRepetidos(grupoABB->izq);
        liberarTGrupoABBRepetidos(grupoABB->der);
        delete grupoABB;
        grupoABB = NULL;
    }
}

// funcion de filtro de arbol para nuevo arbol con repetidos
void filtrarRepetidos(TGrupoABBRepetidos grupoABB, TGrupoABB &grupoRetorno){
	if(grupoABB != NULL){
		// recorro inOrder insertando los elementos con repeticiones
		filtrarRepetidos(grupoABB->izq, grupoRetorno);
		if(grupoABB->repeticiones > 0){
			insertarTVisitanteTGrupoABBconCopia(grupoRetorno, grupoABB->visitante);
		}
		filtrarRepetidos(grupoABB->der,grupoRetorno);
	}
}


TGrupoABB obtenerVisitantesRepetidos(TColeccionTGrupos coleccion){
	if(coleccion != NULL){
		// arbol a retornar
		TGrupoABB retorno = NULL;
		// defino el arbol que voy a filtrar
		TGrupoABBRepetidos aFiltrar = NULL;
		//defino auxiliar para recorrer coleccion y lo asigno al 1er elemento
		TNodoDoble aux = coleccion->ini;
		while(aux != NULL){
			recorridoCopiarArbol(aFiltrar, aux->grupoABB);
			aux = aux->sig;
		}
		//llamo a la funcion de filtrado
		filtrarRepetidos(aFiltrar,retorno);
		liberarTGrupoABBRepetidos(aFiltrar);
		return retorno;
	}else{
		return NULL;
	}
}

//funcion auxiliar para el mas repetido
// void filtrarMasRepetido(TGrupoABBRepetidos grupoABB, TGrupoABBRepetidos &ptr_Visitante ){
// 	if( grupoABB!=NULL ){
// 		filtrarMasRepetido(grupoABB->izq, ptr_Visitante);
// 		if((ptr_Visitante->repeticiones) < (grupoABB->repeticiones)){
// 			ptr_Visitante=grupoABB;
// 		}else if( ((ptr_Visitante->repeticiones) == (grupoABB->repeticiones) )&& (idTVisitante(ptr_Visitante->visitante) < idTVisitante(grupoABB->visitante))){
// 			ptr_Visitante=grupoABB;
// 		}
// 		filtrarMasRepetido(grupoABB->der, ptr_Visitante);
// 	}
// }
TGrupoABBRepetidos filtrarMasRepetido(TGrupoABBRepetidos grupoABB, TGrupoABBRepetidos ptr_Visitante) {
    if (grupoABB != NULL) {
        ptr_Visitante = filtrarMasRepetido(grupoABB->izq, ptr_Visitante);
        if (ptr_Visitante == NULL || grupoABB->repeticiones > ptr_Visitante->repeticiones ||
            (grupoABB->repeticiones == ptr_Visitante->repeticiones && idTVisitante(grupoABB->visitante) < idTVisitante(ptr_Visitante->visitante))) {
            ptr_Visitante = grupoABB;
        }
        ptr_Visitante = filtrarMasRepetido(grupoABB->der, ptr_Visitante);
    }
    return ptr_Visitante;
}




// busqueda de visitante sin precondicion
TVisitante obtenerTVisitante(TGrupoABB grupoABB, int idVisitante){
	if(grupoABB != NULL){
		while((grupoABB != NULL) && (idTVisitante(grupoABB->visitante) != idVisitante)){
			if(idTVisitante(grupoABB->visitante) > idVisitante){
				grupoABB=grupoABB->izq;
			}else{
				grupoABB=grupoABB->der;
			}
		}
		if(grupoABB == NULL){
			return NULL;
		}
		return grupoABB->visitante;
	}else{
		return NULL;
	}
}

//function aux para debug
void imprimirTGrupoABBrepetidos(TGrupoABBRepetidos grupoABB){
    if(grupoABB != NULL){
        // imprimo InOrder
        imprimirTGrupoABBrepetidos(grupoABB->izq);
        imprimirTVisitante(grupoABB->visitante);
        imprimirTGrupoABBrepetidos(grupoABB->der);
    }
}


// consigo el visitante en mis copias y despues lo busco por id
TVisitante visitanteMasRepetido(TColeccionTGrupos coleccion){
	if(coleccion == NULL || coleccion->ini == NULL){
		return NULL;
	}else{
		/* Primer etapa - generar arbol con repeticiones */
		//////////////////////////////////////////////////
		// Genero arbol con repeticiones
		TGrupoABBRepetidos repetidos = NULL;
		// defino auxiliar para recorrer coleccion mientras voy generando el arbol
		// Se que no es NULL por precondicion, almenos 1 grupo (puede ser NULL) existe
		TNodoDoble aux = coleccion->ini;
		while(aux != NULL){
			//copio el arbol
			recorridoCopiarArbol(repetidos, aux->grupoABB);
			//avanzo
			aux = aux->sig;
		}
		////////////////////////////////////////////
		/* Segunda etapa - conseguir mas repetido */
		////////////////////////////////////////////
		// defino el primer puntero
		TGrupoABBRepetidos primero = repetidos;
		// asigno a buscador el mas repetido
		primero = filtrarMasRepetido(repetidos, primero );
		// consigo ID de mas repetido
		int idABuscar = idTVisitante(primero->visitante);

		////////////////////////////////////////////
		/* Tercer etapa - buscar mas repetido */
		////////////////////////////////////////////
		// defino visitante NULL a devolver
		TVisitante aBuscar = NULL;
		// defino auxiliar para buscar en coleccion
		TNodoDoble auxiliar = coleccion->ini;
		//busqueda
		while(auxiliar !=NULL && aBuscar == NULL){
			aBuscar=obtenerTVisitante(auxiliar->grupoABB,idABuscar);
			auxiliar=auxiliar->sig;
		}

		//libero memoria
		liberarTGrupoABBRepetidos(repetidos);
		primero=NULL;
		repetidos=NULL;


		return  aBuscar;
	}
}
 