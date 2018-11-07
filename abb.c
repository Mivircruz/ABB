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
//El sub procedimiento de borrar requiere del nodo donde viajar, la clave y la funcion de comparar
void* _abb_borrar(nodo_t* nodo, const char* clave, abb_comparar_clave_t cmp){
  //Si me pasan un nodo NULL
  if (!nodo)
    return NULL;
  //Hago un puntero para pasar al recorrer
  void* padre = NULL;
  //Busco el nodo a Borrar
  nodo_t* a_borrar = abb_recorrer(nodo,padre,clave,cmp);
  //Si el recorrrer falla, entonces no esta en el arbol
  if (!a_borrar)
    return NULL;
  //Si el a borrar no tiene hijos, se lo borra y listo
    if ( !(a_borrar->izq) && !(a_borrar->der) ){
      free(a_borrar->clave); // Libero la memoria del nodo
      return (a_borrar->dato); // retorno el dato al abb_borrar principal;
      }
    else { //Casos donde tiene hijos
      //Caso si tiene ambos hijos
      if (a_borrar->izq && a_borrar->der){
          /*------------------  LA LOGICA DENTRO DE ESTE IF AUN SE ESTA PENSANDO ----------------*/
        /*
        //sELECCIONO uno de los 2 hijos para que reemplaze el lugar de su padre, elijo el derecho (porque?)
        //Porque asi siempre esta el mayor arriba ("el mayor de las claves menores")
        nodo_t* hijo = a_borrar->der;
        void* devolver = a_borrar->dato;

        //logica de reemplazo para reemplazar al hijo del padre por el hijo del hijo

        if (padre->izq == a_borrar){
           //Si el que se va a borrar es el hijo izquierdo del padre obtenidop en recorrer
           hijo =
          padre->izq = hijo
          free(a_borrar) //Borro el dato
        }
        if (padre->der == a_borrar){
          //Si el que se va a borrar es el hijoderecho del padre obtenidop en recorrer
          padre->der = hijo;
          free(a_borrar)

          */
      }
      else { // Caso donde tiene un solo hijo
        //Determinar cual es el que existe y subirlo como hijo de =l padre
        //Guardar el dato para deovlverlo, y borrar la clave del a borrar
        nodo_t* hijo = NULL; //ESTA LINEA PUEDE SER TUNEADA CON TU OPERADOR ? QUE TANTO AMAS
        void* devolver = NULL;
        //Busco quien es el UNICO hijo
        if (a_borrar->izq)
          hijo = a_borrar->izq;
        if (a_borrar->der)
          hijo = a_borrar->der;
        free(a_borrar->clave); // Borro la clave
        devolver = a_borrar->dato; //Guardo el dato para devolverlo

        //logica de reemplazo para reemplazar al hijo del padre por el hijo del hijo
        if (padre->izq == a_borrar){
           //Si el que se va a borrar es el hijo izquierdo del padre obtenidop en recorrer
          padre->izq = hijo
          free(a_borrar) //Borro el dato
        }
        if (padre->der == a_borrar){
          //Si el que se va a borrar es el hijoderecho del padre obtenidop en recorrer
          padre->der = hijo;
          free(a_borrar)
        }
        return devolver;
      }
    }
}

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
  //Si recibo un arbol vacio devuelvo NULL
  if (!arbol)
    return NULL;
  //Si no tiene raiz
  if (arbol->raiz)
    return NULL;
	return _abb_borrar(arbol->raiz,clave, arbol->comparar_clave);
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
