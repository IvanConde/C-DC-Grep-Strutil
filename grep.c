#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "lista.h"
#define d 256

#define EXITO 0
#define ERROR 1
#define NUMERO_PRIMO 101
#define ENTRADA_ARCHIVO 4
#define ENTRADA_STDIN 3

bool buscar_patron(char patron[], char string[], int n_primo){ 

    int M = (int)strlen(patron);
    int N = (int)strlen(string);
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;

    for(i = 0; i < M-1; i++)
        h = (h*d)%n_primo;

    for(i = 0; i < M; i++){
        p = (d*p + patron[i])%n_primo;
        t = (d*t + string[i])%n_primo;
    }

    for(i = 0; i <= N - M; i++){

        if(p == t){
            for(j = 0; j < M; j++){
                if(string[i+j] != patron[j])
                    break;
            }
            if(j == M)
                return true;
        }

        if(i < N-M){
            t = (d*(t - string[i]*h) + string[i+M])%n_primo;
            if(t < 0)
                t = (t + n_primo);
        }

    }

    return false;

}

char *strdup(const char *clave){
    char* copia = malloc(strlen(clave)+1);
    if(!copia) return NULL;
    strcpy(copia, clave);
    return copia;
}

bool archivo_no_vacio(FILE* archivo){
    fseek(archivo, 0, SEEK_END); 
	return ftell(archivo);
}

bool contexto_valido(char* contexto){

    int i = 0;
    while(contexto[i] != '\0'){
        if(isdigit(contexto[i]) == 0) return false;
        i++;
    }
    return true;

}

bool parametros_validos(int argc, char *argv[]){

    if(argc < 3 || argc > 4){
        fprintf(stderr,"Cantidad de parametros erronea\n");
        return false;
    }
    if(!contexto_valido(argv[2])){
        fprintf(stderr,"Tipo de parametro incorrecto\n");
        return false;
    }

    return true;

}

void imprimir_contexto(lista_t* lista, int num_contexto){

    if(num_contexto == 0) return;
    for(int i = 0; i < num_contexto; i++){
        if(!lista_esta_vacia(lista)){
            char* dato = lista_borrar_primero(lista);
            if(dato){
                fprintf(stdout, "%s", dato);
                free(dato);
            }
        }
    }

}

void aniadir_contexto(lista_t* lista, char* leido){
    lista_insertar_ultimo(lista, strdup(leido));
}

void actualizar_contexto(lista_t* lista, int cap_contexto){

    if(lista_largo(lista) == cap_contexto){
        void* dato = lista_borrar_primero(lista);
        free(dato);
    }

}

bool funcion_grep(lista_t* lista, int contexto, char* patron, FILE* archivo){

    char* match = NULL;
    size_t len = 0;

    ssize_t leer = getline(&match, &len, archivo);
    while(leer != -1){
        if(buscar_patron(patron, match, NUMERO_PRIMO)){
            imprimir_contexto(lista, contexto);
            fprintf(stdout, "%s", match);
        }
        else{
            actualizar_contexto(lista, contexto);
            aniadir_contexto(lista, match);
        }
        leer = getline(&match, &len, archivo);
    }

    free(match);

    return true;

}

int main(int argc, char *argv[]){

    if(!parametros_validos(argc, argv)) return ERROR;

    int contexto = atoi(argv[2]);
    lista_t* lista = lista_crear();
    if(!lista) return ERROR;
    bool estado = false;

    if(argc == ENTRADA_ARCHIVO){
        FILE *archivo = fopen(argv[3], "r");
        if(!archivo){
            fprintf(stderr, "No se pudo leer el archivo indicado");
            return false;
        }
        if(!archivo_no_vacio(archivo)){
            return true;
        }
        else{
            rewind(archivo);
        }
        estado = funcion_grep(lista, contexto, argv[1], archivo);
        fclose(archivo);
    }
    else if(argc == ENTRADA_STDIN){
        estado = funcion_grep(lista, contexto, argv[1], stdin);
    }

    lista_destruir(lista, free);
    if(!estado) return ERROR;
    return EXITO;

}