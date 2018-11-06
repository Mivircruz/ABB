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

 nodo_t* abb_recorrer(nodo_t* nodo,const char* clave, abb_comparar_clave_t cmp){
 	if(!nodo)
 		return NULL;

 	int comparacion_clave = cmp(nodo->clave, clave);
 	if(!comparacion_clave)
 		return nodo;
 	if(comparacion_clave < 0)
 	 return (nodo->izq);
   else /*(comparacion_clave > 0)*/
 	  return (nodo->der);

 }


 //Guardra Realmente el dato en el Arbol (Guarda la hoja)
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
}


/* ******************************************************************
 *                   	WRAPPERS
 * *****************************************************************/

//Destruye una hoja del arbol
void _abb_destruir(nodo_t* nodo, abb_destruir_dato_t destruir_dato){

	if(!nodo)
		return;

	_abb_destruir(nodo->izq, destruir_dato);
	_abb_destruir(nodo->der, destruir_dato);
	destruir_dato(nodo->dato);
  //destruida la clave clonada
  free(nodo->clave);
	free(nodo);
	return;
}

/* ******************************************************************
 *                    PRIMITIVAS DEL ABB
 * *****************************************************************/

//Crea el arbol
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){

	abb_t* abb = malloc(sizeof(abb_t));
	if(!abb)
		return NULL;
	abb->destruir_dato = destruir_dato;
	abb->comparar_clave = cmp;
	abb->cantidad = 0;
  //retorno el abb
  return abb;
}

//Aumenta la cantidad y llama a _abb_guardar para guardar la hoja
bool abb_guardar(abb_t *abb, const char *clave, void *dato){
	abb->cantidad++;
	return _abb_guardar(abb->raiz, clave, dato,abb->comparar_clave,abb->destruir_dato);

}


void *abb_borrar(abb_t *arbol, const char *clave){
  return NULL;
}

//Obtiene el nodo
void *abb_obtener(const abb_t *abb, const char *clave){
	return abb_recorrer(abb->raiz,clave, abb->comparar_clave);

}

bool abb_pertenece(const abb_t *arbol, const char *clave){
	return (abb_recorrer(arbol->raiz, clave,arbol->comparar_clave)) ? true : false;
}

size_t abb_cantidad(abb_t *abb){
	return abb->cantidad;

}

void abb_destruir(abb_t *arbol){
	return _abb_destruir(arbol->raiz, arbol->destruir_dato);
}
