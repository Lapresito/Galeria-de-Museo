#include "../include/galeria.h"


struct rep_galeria{
    TColeccionPiezas piezas;
    TFecha fechaActual;
    TListaExposiciones finalizadas;
    TListaExposiciones activas;
    TListaExposiciones futuras;
    TVisitaDia visita;
    THashVisitaDia hashVisitas;
    TConjuntoPiezas reserva;
};


TGaleria crearTGaleria(TFecha fecha){
    TGaleria galeria = new rep_galeria;
    galeria->piezas = crearColeccionPiezasVacia();
    galeria->fechaActual = fecha;
    galeria->finalizadas = NULL;
    galeria->activas = NULL;
    galeria->futuras = NULL;
    TFecha fechaTVisitaDia = copiarTFecha(fecha);
    galeria->visita = crearTVisitaDia(fechaTVisitaDia, MAX_GRUPOS_VISITA_DIA);
    galeria->hashVisitas = crearTHashVisitaDia(CANT_ESTIMADA_VISITA_DIA_PASADAS);
    galeria->reserva = crearTConjuntoPiezas(MAX_PIEZAS);
    return galeria; 
}

void agregarPiezaTGaleria(TGaleria galeria, TPieza pieza){
    insertarPiezaColeccionPiezas(galeria->piezas, pieza);
    insertarTConjuntoPiezas(galeria->reserva, idTPieza(pieza));
}


void agregarExposicionTGaleria(TGaleria galeria, TExposicion expo){
    // agrego la expiscion en la lista correspondiente
    if(compararTFechas(fechaFinTExposicion(expo), galeria->fechaActual) == -1){
        agregarExposicionTListaExposiciones(galeria->finalizadas, expo);
    }else if(compararTFechas(fechaInicioTExposicion(expo), galeria->fechaActual) == 1){
        agregarExposicionTListaExposiciones(galeria->futuras, expo);
    }else{
        agregarExposicionTListaExposiciones(galeria->activas, expo);
    }
}

void agregarPiezaAExposicionTGaleria(TGaleria galeria, int idPieza, int idExpo){
    // agrego la pieza en la exposicion correspondiente
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
    // primero libero la fecha anterior y asigno la nueva.
    liberarTFecha(galeria->fechaActual);
    galeria->fechaActual = fecha;
    //agrego la visitaDia al historico
    agregarVisitaDiaTHashVisitaDia(galeria->hashVisitas, galeria->visita);
    //creo nuevamente visitaDia
    TFecha fechaTVisitaDia = copiarTFecha(fecha);
    galeria->visita = crearTVisitaDia(fechaTVisitaDia, MAX_GRUPOS_VISITA_DIA);
    // unifico las listas para volver a separarlas con la nueva fecha
    TListaExposiciones finYAct = unirListaExposiciones(galeria->finalizadas, galeria->activas);
    TListaExposiciones listaGral = unirListaExposiciones(finYAct, galeria->futuras);
    // luego de unificada libero memoria de unificaciones sin perder las exposiciones con -false-
    liberarTListaExposiciones(galeria->activas, false);
    liberarTListaExposiciones(galeria->finalizadas, false);
    liberarTListaExposiciones(galeria->futuras, false);
    liberarTListaExposiciones(finYAct, false);
    // vuelvo a separar y asignar las listas.
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
    // si es compatible en las 3 listas retorno true.
    return (esCompatibleTListaExposiciones(galeria->finalizadas,expo)  && esCompatibleTListaExposiciones(galeria->activas,expo) && esCompatibleTListaExposiciones(galeria->futuras,expo));
}

void liberarTGaleria(TGaleria &galeria){
    liberarColeccionPiezas(galeria->piezas);
    liberarTFecha(galeria->fechaActual);
    liberarTVisitaDia(galeria->visita);
    liberarTHashVisitaDia(galeria->hashVisitas);
    liberarTConjuntoPiezas(galeria->reserva);
    liberarTListaExposiciones(galeria->finalizadas, true);
    liberarTListaExposiciones(galeria->activas, true);
    liberarTListaExposiciones(galeria->futuras, true);
    delete galeria;
}

// Funciones tarea 4
//obtenerPiezasTExposicion(expo)
//TExposicion obtenerNesimaExposicionTListaExposiciones(TListaExposiciones listaExpo, int n){

TConjuntoPiezas piezasEnExposicionTGaleria(TGaleria galeria){

    if(galeria !=NULL && galeria->activas != NULL){
        // creo conjunto a devolver
        TConjuntoPiezas piezasEnExpo = crearTConjuntoPiezas(MAX_PIEZAS);
        // auxiliar para recorrer lista de activas
        TListaExposiciones aux = galeria->activas;
        // encuentro tope de iteracion
        int n = cantidadExposicionesTListaExposiciones(aux);
        int i = 1;
        while(i <= n){
            // itero realizando la union
            TExposicion exposicionActual = obtenerNesimaExposicionTListaExposiciones(aux, i);
            TConjuntoPiezas aBorrar = piezasEnExpo;
            piezasEnExpo = unionTConjuntoPiezas(obtenerPiezasTExposicion(exposicionActual), piezasEnExpo);
            liberarTConjuntoPiezas(aBorrar);
            i++;       
        }
        return piezasEnExpo;
    }else{
        // si no hay exposiciones activas, se genera un conjunto vacio para retornar.
        return crearTConjuntoPiezas(MAX_PIEZAS);
    }
}
//cardinalTConjuntoPiezas
float indiceFelicidadVisitanteTGaleria(TGaleria galeria, TVisitante visitante){
    //obtengo las favoritas y su cardinal
    TConjuntoPiezas favoritas = obtenerPiezasFavoritasTVisitante(visitante);
    float cantidadFavoritas = cardinalTConjuntoPiezas(favoritas);
    // si es mayor que 0 obtengo las piezas en exposicion para comparar
    if(cantidadFavoritas > 0){
        TConjuntoPiezas enExpo = piezasEnExposicionTGaleria(galeria);
        //comparo y obtengo cardinal
        TConjuntoPiezas interseccion = interseccionTConjuntoPiezas(enExpo, favoritas);
        float cantidadInter = cardinalTConjuntoPiezas(interseccion);
        // libero memoria solicitada
        liberarTConjuntoPiezas(interseccion);
        liberarTConjuntoPiezas(enExpo);
        //retorno indice
        return cantidadInter/cantidadFavoritas;
    }else{
        return 1.0;
    }
}

void llegaGrupoTGaleria(TGaleria galeria, TGrupoABB grupoABB){
    if( galeria !=NULL){
        // agregar grupo a la visita del dia
        encolarGrupoTVisitaDia(galeria->visita, grupoABB);
    }
}

TConjuntoPiezas piezasEnReservaTGaleria(TGaleria galeria){   
    if(galeria != NULL){
        TConjuntoPiezas activas = piezasEnExposicionTGaleria(galeria);
        TConjuntoPiezas enReserva = diferenciaTConjuntoPiezas(galeria->reserva, activas);
        liberarTConjuntoPiezas(activas);
        return enReserva;
    }else{
        return NULL;
    }
}

TVisitaDia obtenerVisitaDiaTGaleria(TGaleria galeria, TFecha fecha){
    if(galeria != NULL){
        if(compararTFechas(fecha, galeria->fechaActual) ==0 ){
            return galeria->visita;
        }else{
           return obtenerVisitaDiaTHashVisitaDia(galeria->hashVisitas, fecha);
        }
    }else{
        return NULL;
    }
}
