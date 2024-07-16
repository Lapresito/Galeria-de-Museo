#include "../include/galeria.h"


struct rep_galeria{
    TColeccionPiezas piezas;
    TFecha fechaActual;
    TListaExposiciones finalizadas;
    TListaExposiciones activas;
    TListaExposiciones futuras;
};


TGaleria crearTGaleria(TFecha fecha){
    TGaleria galeria = new rep_galeria;
    galeria->piezas = crearColeccionPiezasVacia();
    galeria->fechaActual = fecha;
    galeria->finalizadas = NULL;
    galeria->activas = NULL;
    galeria->futuras = NULL;
    return galeria; 
}

void agregarPiezaTGaleria(TGaleria galeria, TPieza pieza){
    insertarPiezaColeccionPiezas(galeria->piezas, pieza);
}


void agregarExposicionTGaleria(TGaleria galeria, TExposicion expo){
    if(compararTFechas(fechaFinTExposicion(expo), galeria->fechaActual) == -1){
        agregarExposicionTListaExposiciones(galeria->finalizadas, expo);
    }else if(compararTFechas(fechaInicioTExposicion(expo), galeria->fechaActual) == 1){
        agregarExposicionTListaExposiciones(galeria->futuras, expo);
    }else{
        agregarExposicionTListaExposiciones(galeria->activas, expo);
    }
}

void agregarPiezaAExposicionTGaleria(TGaleria galeria, int idPieza, int idExpo){
    TExposicion aAgregar = obtenerExposicionTListaExposiciones(galeria->finalizadas, idExpo);
    if(aAgregar == NULL){
        aAgregar = obtenerExposicionTListaExposiciones(galeria->activas, idExpo);
    }
    if(aAgregar == NULL){
        aAgregar = obtenerExposicionTListaExposiciones(galeria->futuras, idExpo);
    }
    if(aAgregar != NULL){
        TPieza pieza = obtenerPiezaColeccionPiezas(galeria->piezas, idPieza);
        agregarATExposicion(aAgregar, pieza);
    }
}

void avanzarAFechaTGaleria(TGaleria galeria, TFecha fecha){
    liberarTFecha(galeria->fechaActual);
    galeria->fechaActual = fecha;
    TListaExposiciones finYAct = unirListaExposiciones(galeria->finalizadas, galeria->activas);
    TListaExposiciones listaGral = unirListaExposiciones(finYAct, galeria->futuras);
    liberarTListaExposiciones(galeria->activas, false);
    liberarTListaExposiciones(galeria->finalizadas, false);
    liberarTListaExposiciones(galeria->futuras, false);
    liberarTListaExposiciones(finYAct, false);
    galeria->finalizadas = obtenerExposicionesFinalizadas(listaGral, fecha);
    galeria->activas = obtenerExposicionesActivas(listaGral, fecha);
    galeria->futuras = listaGral;

}

void imprimirExposicionesFinalizadasTGaleria(TGaleria galeria){
    imprimirTListaExposiciones(galeria->finalizadas);
}

void imprimirExposicionesActivasTGaleria(TGaleria galeria){
    imprimirTListaExposiciones(galeria->activas);
}

void imprimirExposicionesFuturasTGaleria(TGaleria galeria){
    imprimirTListaExposiciones(galeria->futuras);
}

bool esCompatibleExposicionTGaleria(TGaleria galeria, TExposicion expo){ 
    if(esCompatibleTListaExposiciones(galeria->finalizadas,expo)  && esCompatibleTListaExposiciones(galeria->activas,expo) && esCompatibleTListaExposiciones(galeria->futuras,expo)){
        return true;
    }else{
        return false;
    }
}

void liberarTGaleria(TGaleria &galeria){
    liberarColeccionPiezas(galeria->piezas);
    liberarTFecha(galeria->fechaActual);
    liberarTListaExposiciones(galeria->finalizadas, true);
    liberarTListaExposiciones(galeria->activas, true);
    liberarTListaExposiciones(galeria->futuras, true);
    delete galeria;
}
