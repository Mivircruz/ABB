#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"

/* ******************************************************************
 *                   DEFINICIÓN DEL STRUCT ABB 
 * *****************************************************************/

typedef struct nodo{

    char* clave;
    void* dato;
    struct nodo* izq;
    struct nodo* der;
}nodo_t;

struct abb{

  nodo_t* raiz;
  abb_comparar_clave_t comparar_clave;
  abb_destruir_dato_t destruir_dato;
  size_t cantidad;
};

/* ******************************************************************
 *                   FUNCIONES AUXILIARES
 * *****************************************************************/
nodo_t* nodo_crear(const char* clave, void* dato){
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if(!nodo)
		return NULL;
	nodo->izq = NULL;
	nodo->der = NULL;
	nodo->clave = clave;
	nodo->dato = dato;
	return nodo;
}

/* ******************************************************************
 *                   	WRAPPERS
 * *****************************************************************/

bool _abb_guardar(nodo_t* nodo, const char* clave, void* dato, abb_comparar_clave_t cmp, abb_destruir_dato_t destructor){

	if(!nodo){
		char* clave_abb = strdup(clave);
		nodo_t* nodo = nodo_crear(clave_abb,dato);
		return true;
	}
	
	int comparacion_clave = cmp(clave);
	if(!comparacion_clave){
		destructor(nodo->dato);
		nodo->dato = dato;
		return true;
	}
	if(comparacion_clave < 0)
		return _abb_guardar(nodo->izq);
	else(comparacion_clave > 0)
		return _abb_guardar(nodo->der);
}

/* ******************************************************************
 *                    PRIMITIVAS DEL ABB
 * *****************************************************************/

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){

	abb_t* abb = malloc(sizeof(abb_t));
	if(!abb)
		return NULL;
	abb->destruir_dato = destruir_dato;
	abb->comparar_clave = cmp;
	abb->cantidad = 0;

}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	abb->cantidad++;
	return _abb_guardar(abb->raiz, clave, dato,abb->destruir_dato,abb->comparar_clave);

}
void *abb_borrar(abb_t *arbol, const char *clave){

}

void *abb_obtener(const abb_t *arbol, const char *clave){

}

bool abb_pertenece(const abb_t *arbol, const char *clave){

}

//
size_t abb_cantidad(abb_t *arbol){

}

void abb_destruir(abb_t *arbol){

}
