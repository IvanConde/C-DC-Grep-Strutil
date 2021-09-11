#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "pila.h"
#include "strutil.h"

#define EXITO 0
#define LONGITUD_MINIMA 2
#define VALOR_SUMA 0
#define VALOR_RESTA 1
#define VALOR_MULTIPLICACION 2
#define VALOR_DIVISION 3

bool funcion_operador_ternario(pila_t* pila){

    if(!pila_esta_vacia(pila)){
        int* ultimo = (int*)pila_desapilar(pila);
        if(!pila_esta_vacia(pila)){
            int* penultimo = (int*)pila_desapilar(pila);
            if(!pila_esta_vacia(pila)){
                int* antepenultimo = (int*)pila_desapilar(pila);
                int* resultado = malloc(sizeof(int));
                if(!resultado){
                    free(ultimo);
                    free(penultimo);
                    return false;
                }
                *resultado = (*ultimo != 0) ? *penultimo : *antepenultimo;
                free(ultimo);
                free(penultimo);
                free(antepenultimo);
                if(!pila_apilar(pila, resultado)){
                    free(resultado);
                    return false;
                }
                return true;
            }
            else{
                free(ultimo);
                free(penultimo);
                return false;
            }
        }
        else{
            free(ultimo);
            return false;
        }
    }
    else return false;

}

int _funcion_logaritmo(int valor, int base){
    return (valor > base - 1) ? 1 + _funcion_logaritmo(valor/base, base) : 0;
}

bool funcion_logaritmo(pila_t* pila){

    if(!pila_esta_vacia(pila)){
        int* ultimo = (int*)pila_desapilar(pila);
        if(!pila_esta_vacia(pila)){
            int* penultimo = (int*)pila_desapilar(pila);
            if(*penultimo <= 1){
                free(ultimo);
                free(penultimo);
                return false;
            }
            int* resultado = malloc(sizeof(int));
            if(!resultado){
                free(ultimo);
                free(penultimo);
                return false;
            }
            *resultado = _funcion_logaritmo(*ultimo, *penultimo);
            free(ultimo);
            free(penultimo);
            if(!pila_apilar(pila, resultado)){
                free(resultado);
                return false;
            }
            return true;
        }
        else{
            free(ultimo);
            return false;
        }
    }
    else return false;

}

int _funcion_potencia(int base, int exponente){

    int aux;
    if(exponente == 0)
        return 1;
    aux = _funcion_potencia(base, exponente/2);
    if(exponente%2 == 0)
        return aux*aux;
    else
        return base*aux*aux;

}

bool funcion_potencia(pila_t* pila){

    if(!pila_esta_vacia(pila)){
        int* ultimo = (int*)pila_desapilar(pila);
        if(!pila_esta_vacia(pila)){
            int* penultimo = (int*)pila_desapilar(pila);
            if(*penultimo < 0){
                free(ultimo);
                free(penultimo);
                return false;
            }
            int* resultado = malloc(sizeof(int));
            if(!resultado){
                free(ultimo);
                free(penultimo);
                return false;
            }
            *resultado = _funcion_potencia(*ultimo, *penultimo);
            free(ultimo);
            free(penultimo);
            if(!pila_apilar(pila, resultado)){
                free(resultado);
                return false;
            }
            return true;
        }
        else{
            free(ultimo);
            return false;
        }
    }
    else return false;

}

int _funcion_raiz(int operando){

    if(operando == 1 || operando == 0) return operando;
    int inicio = 1;
    int fin = operando;
    int aux = 0;

    while(inicio <= fin){
        int medio = (inicio+fin)/2;
        if(medio*medio == operando) return medio;
        else if(medio*medio < operando){
            inicio = medio+1;
            aux = medio;
        }
        else{
            fin = medio-1;
        }
    }

    return aux;

}

bool funcion_raiz(pila_t* pila){

    if(!pila_esta_vacia(pila)){
        int* ultimo = (int*)pila_desapilar(pila);
        if(*ultimo < 0){
            free(ultimo);
            return false;
        }
        int* resultado = malloc(sizeof(int));
        if(!resultado){
            free(ultimo);
            return false;
        }
        *resultado = _funcion_raiz(*ultimo);
        free(ultimo);
        if(!pila_apilar(pila, resultado)){
            free(resultado);
            return false;
        }
        return true;
    }
    else return false;

}

void _operacion_simple(int* resultado, int* ultimo, int* penultimo, int valor_operador){

    switch(valor_operador){
        case VALOR_SUMA:
            *resultado = (*ultimo) + (*penultimo);
            break;
        case VALOR_RESTA:
            *resultado = (*ultimo) - (*penultimo);
            break;
        case VALOR_MULTIPLICACION:
            *resultado = (*ultimo) * (*penultimo);
            break;
        case VALOR_DIVISION:
            *resultado = (*ultimo) / (*penultimo);
            break;
    }

}

bool operacion_simple(pila_t* pila, int valor_operador){

    if(!pila_esta_vacia(pila)){
        int* ultimo = (int*)pila_desapilar(pila);
        if(!pila_esta_vacia(pila)){
            int* penultimo = (int*)pila_desapilar(pila);
            if(valor_operador == VALOR_DIVISION && (*penultimo) == 0){
                free(ultimo);
                free(penultimo);
                return false;
            }
            int* resultado = malloc(sizeof(int));
            if(!resultado){
                free(ultimo);
                free(penultimo);
                return false;
            }
            _operacion_simple(resultado, ultimo, penultimo, valor_operador);
            free(ultimo);
            free(penultimo);
            if(!pila_apilar(pila, resultado)){
                free(resultado);
                return false;
            }
            return true;
        }
        else{
            free(ultimo);
            return false;
        }
    }
    else return false;

}

bool realizar_operacion(char* operador, pila_t* pila){

    bool resultado = true;

    if(strcmp(operador, "+") == 0) return resultado = operacion_simple(pila, VALOR_SUMA);
    else if(strcmp(operador, "-") == 0) return resultado = operacion_simple(pila, VALOR_RESTA);
    else if(strcmp(operador, "*") == 0) return resultado = operacion_simple(pila, VALOR_MULTIPLICACION);
    else if(strcmp(operador, "/") == 0) return resultado = operacion_simple(pila, VALOR_DIVISION);
    else if(strcmp(operador, "sqrt") == 0) return resultado = funcion_raiz(pila);
    else if(strcmp(operador, "^") == 0) return resultado = funcion_potencia(pila);
    else if(strcmp(operador, "log") == 0) return resultado = funcion_logaritmo(pila);
    else if(strcmp(operador, "?") == 0) return resultado = funcion_operador_ternario(pila);

    return resultado;

}

void limpiar_pila(pila_t* pila){

    while(!pila_esta_vacia(pila)){
        void* elemento = pila_desapilar(pila);
        if(elemento){
            free(elemento);
        }
    }

}

bool es_numero(char* str){

    size_t tam = strlen(str);
    if(tam == 0) return false;
    
    size_t contador = 0;

    for(size_t i = 0; i < tam; i++){
        if(isdigit(str[i]) != 0) contador++;
    }

    if((str[0] == '-') && (contador == tam-1) && (contador >= 1)) return true;
    else if(contador == tam) return true;

    return false;

}

void eliminar_fin_de_linea(char** strv, size_t longitud){
    char* pos;
    if((pos = strchr(strv[longitud-1], '\n')) != NULL) *pos = '\0';
}

bool _procesar_linea(pila_t* pila, char** strv, int** valores_enteros){

    for(int i = 0; strv[i] != NULL; i++){
        if(es_numero(strv[i])){
            valores_enteros[i] = malloc(sizeof(int));
            if(!valores_enteros[i]) return false;
            *valores_enteros[i] = atoi(strv[i]);
            if(!pila_apilar(pila, valores_enteros[i])) return false;
        }
        else{
            if(!realizar_operacion(strv[i], pila)) return false;
        }
    }

    void* resultado = pila_desapilar(pila);
    if(!pila_esta_vacia(pila)){
        free(resultado);
        return false;
    }
    else{
        fprintf(stdout, "%d\n", *(int*)resultado);
        free(resultado);
    }

    return true;

}

bool procesar_linea(char* linea){

    pila_t* pila = pila_crear();
    if(!pila) return false;

    char** strv = split(linea, ' ');
    if(!strv) return false;

    size_t longitud = 0;
    for(int i = 0; strv[i] != NULL; i++) longitud++;
    if(longitud < LONGITUD_MINIMA){
        pila_destruir(pila);
        free_strv(strv);
        return false;
    }
    eliminar_fin_de_linea(strv, longitud);

    int** valores_enteros = malloc(sizeof(int*) * longitud);
    if(!valores_enteros) return false;

    bool estado = _procesar_linea(pila, strv, valores_enteros);

    limpiar_pila(pila);
    pila_destruir(pila);
    free_strv(strv);
    free(valores_enteros);

    return estado;

}

int main(int argc, char *argv[]){

    char* linea = NULL;
    size_t len = 0;

    ssize_t leer = getline(&linea, &len, stdin);
    while(leer != -1){
        if(!procesar_linea(linea)) fprintf(stdout, "ERROR\n");
        leer = getline(&linea, &len, stdin);
    }

    free(linea);

    return EXITO;

}