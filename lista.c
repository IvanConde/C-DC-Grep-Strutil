#include "lista.h"
#include <stdlib.h>

typedef struct nodo{
    void* dato;
    struct nodo* siguiente;
}nodo_t;

struct lista{
    nodo_t* primero;
    nodo_t* ultimo;
    size_t largo;
};

struct lista_iter{
    lista_t* lista;
    nodo_t* cursor;
    nodo_t* anterior;
};

// Primitivas PRIVADAS.

nodo_t* crear_nodo(void* valor, nodo_t* siguiente){

    nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
    if(!nodo_nuevo) return NULL;

    nodo_nuevo->siguiente = siguiente;
    nodo_nuevo->dato = valor;

    return nodo_nuevo;

}

// Primitivas de la LISTA.

lista_t* lista_crear(void){

    lista_t* lista = malloc(sizeof(lista_t));
    if(!lista) return NULL;

    lista->primero = NULL;
    lista->ultimo = NULL;
    lista->largo = 0;

    return lista;

}

bool lista_esta_vacia(const lista_t* lista){

    return (lista->largo == 0);

}

bool lista_insertar_primero(lista_t* lista, void* dato){

    nodo_t* nodo = crear_nodo(dato, lista->primero);
    if(!nodo) return false;

    if(lista_esta_vacia(lista)){
        lista->ultimo = nodo;
    }

    lista->primero = nodo;
    lista->largo++;

    return true;

}

bool lista_insertar_ultimo(lista_t* lista, void* dato){

    nodo_t* nodo = crear_nodo(dato, NULL);
    if(!nodo) return false;

    if(lista_esta_vacia(lista)){
        lista->primero = nodo;
    }
    else{
        lista->ultimo->siguiente = nodo;
    }

    lista->ultimo = nodo;
    lista->largo++;

    return true;

}

void* lista_borrar_primero(lista_t* lista){

    if(lista_esta_vacia(lista)) return NULL;

    void* dato = lista->primero->dato;
    nodo_t* aux = lista->primero;

    if(lista->primero == lista->ultimo){
        lista->ultimo = NULL;
    }
    
    lista->primero = lista->primero->siguiente;
    lista->largo--;

    free(aux);

    return dato;

}

void* lista_ver_primero(const lista_t* lista){

    if(lista_esta_vacia(lista)) return NULL;
    return lista->primero->dato;

}

void* lista_ver_ultimo(const lista_t* lista){

    if(lista_esta_vacia(lista)) return NULL;
    return lista->ultimo->dato;

}

size_t lista_largo(const lista_t* lista){

    return lista->largo;

}

void lista_destruir(lista_t* lista, void destruir_dato(void*)){

    while(!lista_esta_vacia(lista)){
        void* dato = lista_borrar_primero(lista);
        if(destruir_dato != NULL) destruir_dato(dato);
    }
    free(lista);

}

// Primitivas del ITERADOR INTERNO.

void lista_iterar(lista_t* lista, bool visitar(void* dato, void* extra), void* extra){

    nodo_t* nodo = lista->primero;
    while(nodo){
        if(!visitar(nodo->dato,extra)) break;
        nodo = nodo->siguiente;
    }

}

// Primitivas del ITERADOR EXTERNO.

lista_iter_t* lista_iter_crear(lista_t* lista){

    lista_iter_t* iterador = malloc(sizeof(lista_iter_t));
    if(!iterador) return NULL;

    iterador->lista = lista;
    iterador->cursor = lista->primero;
    iterador->anterior = NULL;

    return iterador;

}

bool lista_iter_avanzar(lista_iter_t* iter){

    if(iter->cursor == NULL) return false;
    iter->anterior = iter->cursor;
    iter->cursor = iter->cursor->siguiente;
    return true;

}

void* lista_iter_ver_actual(const lista_iter_t* iter){

    if(iter->cursor == NULL) return NULL;
    return iter->cursor->dato;

}

bool lista_iter_al_final(const lista_iter_t* iter){

    return (iter->cursor == NULL);

}

void lista_iter_destruir(lista_iter_t* iter){

    free(iter);

}

bool lista_iter_insertar(lista_iter_t* iter, void* dato){ //codigo repetido

    nodo_t* nodo = crear_nodo(dato, iter->cursor);
    if(!nodo) return false;

    if(iter->cursor == iter->lista->primero){
        iter->lista->primero = nodo;
    }
    else{
        iter->anterior->siguiente = nodo;
    }
    if(iter->lista->ultimo == iter->anterior){
        iter->lista->ultimo = nodo;
    }

    iter->cursor = nodo;
    iter->lista->largo++;

    return true;

}

void* lista_iter_borrar(lista_iter_t* iter){

    if(iter->cursor == NULL) return NULL;

    void* dato = iter->cursor->dato;
    nodo_t* aux = iter->cursor;

    if(iter->cursor == iter->lista->primero){
        iter->lista->primero = iter->cursor->siguiente; 
    }
    else{
        iter->anterior->siguiente = iter->cursor->siguiente;
    }
    if(iter->cursor == iter->lista->ultimo){
        iter->lista->ultimo = iter->anterior;
    }

    iter->cursor = iter->cursor->siguiente;
    iter->lista->largo--;
    free(aux);
    return dato;

}