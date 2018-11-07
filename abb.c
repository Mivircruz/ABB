#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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
  //Clono la clave, Debe ser liberada al destruir
	nodo->clave = strdup(clave);
	nodo->dato = dato;
	return nodo;
}
/* ******************************************************************
 *                   FUNCIONES AUXILIARES
 * *****************************************************************/

//Recorre el árbol buscando un nodo con la clave pasada por parámetro. 
//Además, se pasa un doble puntero para obtener al padre del nodo con la clave.
//Si no se encuentra al nodo, devuelve NULL.
 nodo_t* abb_recorrer(nodo_t* nodo, nodo_t** padre, const char* clave, abb_comparar_clave_t cmp){
 	if(!nodo)
 		return NULL;

 	//Si encuentra la clave en el árbol, devuelve el nodo que la contiene.
 	int comparacion_clave = cmp(nodo->clave, clave);
 	if(!comparacion_clave)
 		return nodo;

 	//Si no, busca a izquierda o derecha según la clave sea mayor o menor al nodo actual.
 	*padre = nodo;
 	if(comparacion_clave < 0)
 		return abb_recorrer(nodo->der, padre, clave, cmp);

   else 
 	  return abb_recorrer(nodo->izq, padre, clave, cmp);

 }


/* ******************************************************************
 *                   	WRAPPERS
 * *****************************************************************/

 /*void* _abb_borrar(nodo_t* nodo, const char* clave, void* dato, abb_comparar_clave_t cmp){
	if(!nodo)
		return NULL;

	nodo_t* a_borrar = abb_recorrer(nodo, clave, cmp);
	if(!a_borrar)
		return NULL;

	void* a_devolver = a_borrar->dato;

	if(!a_borrar->izq && !a_borrar->der){
		free(a_borrar->clave);
		free(a_borrar);
	}

	else if(!a_borrar->izq && a_borrar->der || a_borrar->izq && !a_borrar->der){
		nodo_t* aux = (!a_borrar->izq && a_borrar->der) ? a_borrar->der : a_borrar->izq;
	}
}
*/

void _abb_destruir(nodo_t* nodo, abb_destruir_dato_t destruir_dato){

	if(!nodo)
		return;

	_abb_destruir(nodo->izq, destruir_dato);
	_abb_destruir(nodo->der, destruir_dato);
	if(destruir_dato)
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
	abb->raiz = NULL;
  return abb;
}

bool abb_guardar(abb_t *abb, const char *clave, void *dato){

	nodo_t* padre = NULL;
 	nodo_t* nodo_misma_clave = abb_recorrer(abb->raiz, &padre, clave, abb->comparar_clave);
 	if(!nodo_misma_clave){
 		nodo_t* a_guardar = nodo_crear(clave, dato);
 		if(!a_guardar)
 			return false;
	 	if(!abb->raiz)
	 		abb->raiz = a_guardar;
	 	else{
	 		if(abb->comparar_clave(padre->clave, clave) < 0)
	 			padre->der = a_guardar;
	 		else 
	 			padre->izq = a_guardar;
	 	}
	 }
	 	else{
	 		abb->destruir_dato(nodo_misma_clave->dato);
	 		nodo_misma_clave->dato = dato;
		}
	abb->cantidad++;
	return true;
}

void *abb_borrar(abb_t *arbol, const char *clave){
	return NULL;
	//return _abb_borrar(arbol->raiz, arbol->comparar_clave);
}

//Obtiene el nodo
void *abb_obtener(const abb_t *abb, const char *clave){
	nodo_t* nodo = NULL;
	nodo = abb_recorrer(abb->raiz, &nodo, clave, abb->comparar_clave);
	if(!nodo)
		return NULL;
	return nodo->dato;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
	nodo_t* padre = NULL;
	return (abb_recorrer(arbol->raiz, &padre, clave,arbol->comparar_clave)) ? true : false;
}

size_t abb_cantidad(abb_t *abb){
	return abb->cantidad;

}

void abb_destruir(abb_t *arbol){
	_abb_destruir(arbol->raiz, arbol->destruir_dato);
	free(arbol);
}
