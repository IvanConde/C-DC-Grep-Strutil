#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está planteada como una lista de punteros genéricos. */

struct lista;
typedef struct lista lista_t;

struct lista_iter;
typedef struct lista_iter lista_iter_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t* lista_crear(void);

// Devuelve verdadero si la lista no tiene elementos, false en caso contrario.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento al principio lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al inicio
// de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento al final lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al final
// de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Borra el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void* lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void* lista_ver_primero(const lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void* lista_ver_ultimo(const lista_t* lista);

// Devuelve el largo de la lista.
// Pre: la lista fue creada.
// Post: se devolvió el largo de la lista.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *));

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

// Crea un iterador.
// Pre: la lista fue creada.
// Post: devuelve un iterador inicializado y en la primera posicion de la lista.
lista_iter_t* lista_iter_crear(lista_t *lista);

// Avanza el iterador al siguiente elemento de la lista.
// Pre: el iterador fue creado.
// Post: el iterador avanzó de posicion.
bool lista_iter_avanzar(lista_iter_t *iter);

// Obtiene el valor del elemento que esta en la posicion del iterador.
// Si la lista tiene elementos, se devuelve el valor, si está vacía devuelve NULL.
// Pre: el iterador fue creado.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void* lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelve verdadero si el iterador esta al final de la lista.
// Pre: el iterador fue creado.
// Post: se devuelve true si el iterador esta al final de la lista, caso contrario falso.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador.
// Pre: el iterador fue creado.
// Post: se destruyo el iterador.
void lista_iter_destruir(lista_iter_t *iter);

// Agrega un nuevo elemento en la posicion del iterador. Devuelve falso en caso de error.
// Pre: el iterador fue creado.
// Post: Se agregó un nuevo elemento a la lista, valor se encuentra en la posicion del iterador.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Borra un elemento de la lista segun la posicion del iterador.
// Pre: el iterador fue creado.
// Post: se devolvió el valor del elemento en la posicion del iterador, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void* lista_iter_borrar(lista_iter_t *iter);

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

// Itera toda la lista, excepto en caso de corte, provida siguiendo las operaciones indicadas segun la funcion visitar.
// Pre: La lista fue creada, visitar es una funcion capaz de realizar lo que el usuario tenga intencionado,
// extra es opcional segun la funcion visitar.
// Post: la funcion itero por toda la lista, excepto en caso de corte, realizando las operaciones indicadas segun 
// la funcion visitar e interactuando con la variable en extra si es el caso como es debido.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación del alumno.
//
// Las pruebas deben emplazarse en el archivo ‘pruebas_alumno.c’, y
// solamente pueden emplear la interfaz pública tal y como aparece en lista.h
// (esto es, las pruebas no pueden acceder a los miembros del struct lista).
//
// Para la implementación de las pruebas se debe emplear la función
// print_test(), como se ha visto en TPs anteriores.
void pruebas_lista_alumno(void);

#endif // LISTA_H