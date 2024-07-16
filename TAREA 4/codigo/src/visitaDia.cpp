#include "../include/visitaDia.h"

// struct auxiliar para visita dia
typedef struct rep_visitaDiaUnidad *TVisitaDiaNodo;
struct rep_visitaDiaUnidad{
    float edadPromedio;
    int idGrupo;
    TGrupoABB grupo;
};

struct rep_visitadia{
    TFecha fecha;
    int cantidadMax;
    // tope y array heap para cola de prioridad.
    int tope;
    TVisitaDiaNodo * heap;
    // bitmap que guarda nodo por id correspondinte a posicion de array.
    TVisitaDiaNodo * gruposMap;
    // si el bool es true, prioritario es la menor edad promedio, si es false esta invertido
    bool orden;
};

// Funcionex auxiliares para realizar los filtrados.
void filtradoAscendente(int pos, TVisitaDia &visita){
  // renombro la posicion
  int i = pos;
  if(visita->orden){
    // avanzo sin llegar al tope y evaluando si es necesario
    while(i > 1 && visita->heap[i]->edadPromedio < visita->heap[i / 2]->edadPromedio){
      // busco padre para para evaluar si debe subir
      int padre = i/2;
      if(visita->heap[padre]->edadPromedio > visita->heap[i]->edadPromedio){
        TVisitaDiaNodo aux = visita->heap[padre];
        visita->heap[padre] = visita->heap[i];
        visita->heap[i] = aux;
      }
      //avanzo al padre
      i = padre;
    }
  }else{// ORDEN INVERTIDO
    // avanzo sin llegar al tope y evaluando si es necesario
    while(i > 1 && visita->heap[i]->edadPromedio > visita->heap[i / 2]->edadPromedio){
      // busco padre para para evaluar si debe subir
      int padre = i/2;
      if(visita->heap[padre]->edadPromedio < visita->heap[i]->edadPromedio){
        TVisitaDiaNodo aux = visita->heap[padre];
        visita->heap[padre] = visita->heap[i];
        visita->heap[i] = aux;
      }
      //avanzo al padre
      i = padre;
    }
  }
}
void filtradoDescendente(int pos, TVisitaDia &visita) {
    int i = pos;
    // bandera para seguir filtrando
    bool filtrar = true;
    if(visita->orden){
      while (filtrar) {
          int hijoIzq = 2 * i;
          int hijoDer = 2 * i + 1;
          int menor = i;
          // comparo con el hijo izquierdo si existe y es menor
          if (hijoIzq <= visita->tope && visita->heap[hijoIzq]->edadPromedio < visita->heap[menor]->edadPromedio) {
              menor = hijoIzq;
          }
          // comparo con el hijo derecho si existe y es menor
          if (hijoDer <= visita->tope && visita->heap[hijoDer]->edadPromedio < visita->heap[menor]->edadPromedio) {
              menor = hijoDer;
          }
          // si el elemento actual no es el menor, intercambiar con el hijo correspondiente
          if (menor != i) {
              TVisitaDiaNodo aux = visita->heap[i];
              visita->heap[i] = visita->heap[menor];
              visita->heap[menor] = aux;
              
              // avanzo hacia abajo en el árbol
              i = menor;
          } else {
              // si ya esta en su posicion correcta, terminar el filtrado
              filtrar = false;
          }
      }
    }else{// ORDEN INVERTIDO
      while (filtrar) {
          int hijoIzq = 2 * i;
          int hijoDer = 2 * i + 1;
          int mayor = i;
          // comparo con el hijo izquierdo si existe y es menor
          if (hijoIzq <= visita->tope && visita->heap[hijoIzq]->edadPromedio > visita->heap[mayor]->edadPromedio) {
              mayor = hijoIzq;
          }
          // comparo con el hijo derecho si existe y es menor
          if (hijoDer <= visita->tope && visita->heap[hijoDer]->edadPromedio > visita->heap[mayor]->edadPromedio) {
              mayor = hijoDer;
          }
          // si el elemento actual no es el menor, intercambiar con el hijo correspondiente
          if (mayor != i) {
              TVisitaDiaNodo aux = visita->heap[i];
              visita->heap[i] = visita->heap[mayor];
              visita->heap[mayor] = aux;
              
              // avanzo hacia abajo en el árbol
              i = mayor;
          }else {
              // si ya esta en su posicion correcta, terminar el filtrado
              filtrar = false;
          }
      }
  }
}


TVisitaDia crearTVisitaDia(TFecha fecha, int N){
    TVisitaDia nuevo = new rep_visitadia;
    nuevo->fecha = fecha;
    nuevo->cantidadMax = N;
    nuevo->tope = 0;
    nuevo->heap = new TVisitaDiaNodo[N + 1];
    nuevo->gruposMap = new TVisitaDiaNodo[N + 1];
    nuevo->orden = true;
    for(int i= 0; i < N + 1; i++){
        nuevo->heap[i] = NULL;
        nuevo->gruposMap[i]= NULL;
    }
    return nuevo;
}

void encolarGrupoTVisitaDia(TVisitaDia &visita, TGrupoABB grupo){
  if(idGrupo(grupo) <= maxGruposTVisitaDia(visita) && idGrupo(grupo) > 0 && visita->tope <= maxGruposTVisitaDia(visita)){ 
    //creo el nodo si el grupo pertenece al rango y si el tope es menor que N
    TVisitaDiaNodo nuevo = new rep_visitaDiaUnidad;
    nuevo->edadPromedio = edadPromedioTGrupoABB(grupo);
    nuevo->idGrupo = idGrupo(grupo);
    nuevo->grupo = grupo;
    //lo agrego en el bitmap
    visita->gruposMap[idGrupo(grupo)] = nuevo;
    //aumento tope
    visita->tope++;
    //lo agrego en heap
    visita->heap[visita->tope] = nuevo;
    //filtro y ordeno
    filtradoAscendente(visita->tope, visita);
  }
}

int cantidadGruposTVisitaDia(TVisitaDia visitaDia){
    if(visitaDia != NULL){
        return visitaDia->tope;
    }else{
        return 0;
    }
}

void imprimirTVisitaDia(TVisitaDia visitaDia) {
    if (visitaDia != NULL) {
        printf("Visita para dia: ");
        imprimirTFecha(visitaDia->fecha);
        printf("\n");
        int i = 1;
        int nivel = 1;
        while (i <= visitaDia->tope) {
            printf("\n");
            printf("Nivel %d\n", nivel);
            
            // calculo la cantidad de nodos en el nivel actual (2^(nivel-1))
            int cantidadNodosNivel = 1;
            for (int k = 1; k < nivel; k++) {
                cantidadNodosNivel *= 2;
            }
            // imprimo todos los nodos en el nivel actual
            // utilizando j como contador de nodos e i para acceder al grupo correcto.
            for (int j = 0; j < cantidadNodosNivel && i <= visitaDia->tope; j++, i++) {
                printf("%d) Grupo %d con edad promedio %.2f\n", i, visitaDia->heap[i]->idGrupo, visitaDia->heap[i]->edadPromedio);
                imprimirTGrupoABB(visitaDia->heap[i]->grupo);
            }
            // avanzo de nivel
            nivel++;
        }
    }
}

TGrupoABB desencolarGrupoTVisitaDia(TVisitaDia &visitaDia){
  if(visitaDia != NULL && visitaDia->tope > 0){
    TGrupoABB aRetornar = visitaDia->heap[1]->grupo;
    if(visitaDia->tope >1){
      //reemplazo el primer elemento con el ultimo y luego hago filtrado
      TVisitaDiaNodo aux = visitaDia->heap[1];
      visitaDia->heap[1] = visitaDia->heap[visitaDia->tope];
      // libero memoria de nodo.
      delete aux;
      visitaDia->heap[visitaDia->tope] = NULL;
      visitaDia->gruposMap[idGrupo(aRetornar)] = NULL;
    }else{
      delete visitaDia->heap[1];
      visitaDia->heap[1]= NULL;
      visitaDia->gruposMap[idGrupo(aRetornar)] = NULL;
    }
    // dismunyo el tope.
    visitaDia->tope--;
    // filtro para ordenar heap
    if(visitaDia->tope >1){
      filtradoDescendente(1, visitaDia);
    }
    // retorno
    return aRetornar;
  }else{
    return NULL;  
  }

}

void liberarTVisitaDia(TVisitaDia &visitaDia){
  if(visitaDia != NULL){
    for(int i=1; i<=cantidadGruposTVisitaDia(visitaDia); i++){
      if(visitaDia->heap[i] != NULL){
        liberarTGrupoABB(visitaDia->heap[i]->grupo);
        delete visitaDia->heap[i];
      }
    }
    liberarTFecha(visitaDia->fecha);
    delete [] visitaDia->gruposMap;
    delete [] visitaDia->heap;
    delete visitaDia;
    visitaDia = NULL;
  }
}

void invertirPrioridadTVisitaDia(TVisitaDia &visita) {
    if (visita != NULL) {
        // Invertir el orden
        visita->orden = !visita->orden;

        // Reconstruir el heap desde el medio hacia el principio
        for (int i = visita->tope / 2; i >= 1; i--) {
            filtradoDescendente(i, visita);
        }
    }
}

bool estaEnTVisitaDia(TVisitaDia visita, int id) {
  if(id < maxGruposTVisitaDia(visita) && id > 0){
    return visita->gruposMap[id] != NULL;
  }else{
    return false;
  }
} 

float prioridadTVisitaDia(TVisitaDia visita, int id){
  if(visita != NULL && id < maxGruposTVisitaDia(visita) && id > 0){
    if(estaEnTVisitaDia(visita, id)){
      return visita->gruposMap[id]->edadPromedio;
    }else{
      return 0.0;
    }
  }else{
    return 0.0;
  }
}

TGrupoABB masPrioritarioTVisitaDia(TVisitaDia visita){
	  if(visita != NULL){
        return visita->heap[1]->grupo;
    }else{
        return NULL;
    }
}


int maxGruposTVisitaDia(TVisitaDia visita){
    if(visita != NULL){
        return visita->cantidadMax;
    }else{
        return 0;
    }
}

TFecha fechaTVisitaDia(TVisitaDia visitaDia){
  	if(visitaDia != NULL){
        return visitaDia->fecha;
    }else{
        return NULL;
    }
}


