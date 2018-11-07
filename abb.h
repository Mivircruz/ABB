#ifndef ABB_H
#define ABB_H

typedef struct abb abb_t;

//Compara dos cadenas.
//Pre: recibe 2 cadenas. No se modifican las cadenas recibidas.
//Post: devuelve
//*)Entero MENOR a 0 si la primer cadena es menor a la segunda
//*)Entero MAYOR a 0 si la primer cadena es mayor a la segunda
//*)Entero IGUAL a 0 si ambas cadenas son iguales
typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);

//Crea un abb.
//Pre: se pasa por parámetro dos funciones: una para comparar cadenas y otra, para destruir datos.
//Post: el abb fue creado. En caso de error, devuelve NULL.
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

//Inserta un elemento a la izquierda o derecha según corresponda.
//Pre: el abb fue creado.
//Post: se insertó un elemento al árbol.
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);
void *abb_borrar(abb_t *arbol, const char *clave);

//Devuelve el elemento en caso de estar en el abb, NULL en caso contrario.
//Pre: el abb fue creado.
void *abb_obtener(const abb_t *arbol, const char *clave);

//Devuelve true si el la clave se encuentra en el árbol. False en caso contrario.
//Pre: el abb fue creado.
bool abb_pertenece(const abb_t *arbol, const char *clave);

//Muestra la cantidad de elementos del árbol.
//Pre: el árbol fue creado.
size_t abb_cantidad(abb_t *arbol);

//Destruye el abb y libera la memoria pedida.
//Pre: el abb fue creado.
//Post: el abb fue destruido.
void abb_destruir(abb_t *arbol);

#endif
