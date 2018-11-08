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
	nodo->clave = strdup(clave);
	nodo->dato = dato;
	return nodo;
}

/* ******************************************************************
 *                   ESTRUCTURA AUXILIAR
 * *****************************************************************/

//Estructura auxiliar con lo que se necesita para agregar/borrarle un hijo al abb.
typedef struct{

	bool izq;
	nodo_t* padre;
}hijo_t;
/* ******************************************************************
 *                   FUNCIONES AUXILIARES
 * *****************************************************************/
hijo_t* hijo_crear(void){
	hijo_t* hijo = malloc(sizeof(hijo_t));
	if(!hijo)
		return NULL;
	hijo->padre = NULL;
	hijo->izq = false;
	return hijo;
}

//Recorre el árbol buscando un nodo con la clave pasada por parámetro.
//Además, se pasa un doble puntero para obtener al padre del nodo con la clave.
//Si no se encuentra al nodo, devuelve NULL.
 nodo_t* abb_recorrer(nodo_t* nodo, const char* clave, abb_comparar_clave_t cmp, hijo_t* extra){
 	if(!nodo)
 		return NULL;

 	//Si encuentra la clave en el árbol, devuelve el nodo que la contiene.
 	int comparacion_clave = cmp(nodo->clave, clave);
 	if(!comparacion_clave)
 		return nodo;

 	//Si no, busca a izquierda o derecha según la clave sea mayor o menor al nodo actual.
 	if(extra)
 		extra->padre = nodo;
 	if(comparacion_clave < 0){
 		if(extra)
 			extra->izq = false;
 		return abb_recorrer(nodo->der, clave, cmp, extra);
 	}

   else{
   		if(extra)
   			extra->izq = true;
 		return abb_recorrer(nodo->izq, clave, cmp, extra);
   }

 }


/* ******************************************************************
 *                   	WRAPPERS
 * *****************************************************************/

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

	hijo_t* extra = hijo_crear();
	if(!extra)
		return false;

 	nodo_t* nodo_misma_clave = abb_recorrer(abb->raiz, clave, abb->comparar_clave, extra);
 	if(!nodo_misma_clave){
 		nodo_t* a_guardar = nodo_crear(clave, dato);
 		if(!a_guardar)
 			return false;
	 	if(!extra->padre)
	 		abb->raiz = a_guardar;
	 	else{
	 		if(!extra->izq)
	 			extra->padre->der = a_guardar;
	 		else
	 			extra->padre->izq = a_guardar;
	 	}
	 }
	 	else{
	 		abb->destruir_dato(nodo_misma_clave->dato);
	 		nodo_misma_clave->dato = dato;
		}
	abb->cantidad++;
	free(extra);
	return true;
}

void *abb_borrar(abb_t *arbol, const char *clave){

	if(!arbol)	
		return NULL;

	hijo_t* extra = hijo_crear();
	if(!extra)
		return NULL;

	nodo_t* a_borrar = abb_recorrer(arbol->raiz, clave, arbol->comparar_clave, extra);
	if(!a_borrar){
		free(extra);
		return NULL;
	}
	
	void* a_devolver = a_borrar->dato;

//Primer caso: es una hoja (nodo sin hijos)
	if(!a_borrar->izq && !a_borrar->der){
		free(a_borrar->clave);
		free(a_borrar);
		if(!extra->padre)
			arbol->raiz = NULL;
		else if(extra->izq)
			extra->padre->izq = NULL;
		else
			extra->padre->der = NULL;
	}
//Segundo caso: es un nodo interno con un hijo.
	else if((!a_borrar->izq && a_borrar->der )|| (a_borrar->izq && !a_borrar->der)){
		nodo_t* hijo = (!a_borrar->izq && a_borrar->der) ? a_borrar->der : a_borrar->izq;
		if(extra->izq)
			extra->padre->izq = hijo;
		else
			extra->padre->der = hijo;
		free(a_borrar->clave);
		free(a_borrar);
	}

	if(a_devolver)
		arbol->cantidad--;
	free(extra);
	return a_devolver;
}

void *abb_obtener(const abb_t *abb, const char *clave){

	nodo_t* nodo = abb_recorrer(abb->raiz, clave, abb->comparar_clave, NULL);
	if(!nodo)
		return NULL;

	return nodo->dato;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){

	return (abb_recorrer(arbol->raiz, clave, arbol->comparar_clave, NULL)) ? true : false;
}

size_t abb_cantidad(abb_t *abb){
	return abb->cantidad;

}

void abb_destruir(abb_t *arbol){
	_abb_destruir(arbol->raiz, arbol->destruir_dato);
	free(arbol);
}
