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
 *                   PRIMITIVAS DEL NODO
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
 *                   FUNCIONES AUXILIARES
 * *****************************************************************/

nodo_t* abb_recorrer(nodo_t* nodo, char* clave, abb_comparar_clave_t cmp){
		if(!nodo)
			return NULL;

		int comparacion_clave = cmp(nodo->clave, clave);
		if(!comparacion_clave)
			return nodo;
		if(comparacion_clave < 0)
		return _abb_guardar(nodo->izq);
	else(comparacion_clave > 0)
		return _abb_guardar(nodo->der);
}

/* ******************************************************************
 *                   	WRAPPERS
 * *****************************************************************/

bool _abb_guardar(nodo_t* nodo, const char* clave, void* dato, abb_comparar_clave_t cmp, abb_destruir_dato_t destructor){

	nodo_t* nodo_guardar = abb_recorrer(nodo, clave, cmp);
	if(!nodo_guardar){
		char* clave_abb = strdup(clave);
		nodo_t* nodo = nodo_crear(clave_abb,dato);
		return (!nodo) ? false : true;
	}
	else{
		destructor(nodo_guardar->dato);
		nodo_guardar->dato = dato;
		return true;

}

void _abb_destruir(nodo_t* nodo, abb_destruir_dato_t destruir_dato){

	if(!nodo)
		return;

	_abb_destruir(nodo->izq, destruir_dato);
	_abb_destruir(nodo->der, destruir_dato);
	destruir_dato(nodo->dato);
	free(nodo->clave);
	free(nodo);
	return;
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
	return abb_recorrer(arbol->raiz,clave);

}

bool abb_pertenece(const abb_t *arbol, const char *clave){
	return (abb_recorrer(arbol->raiz, clave)) ? true : false;
}

size_t abb_cantidad(abb_t *arbol){
	return abb->cantidad;

}

void abb_destruir(abb_t *arbol){
	return _abb_destruir(arbol->raiz, arbol->destructor);
}
