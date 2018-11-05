

typedef struct nodo{
    char* clave;
    void* dato;
    struct nodo* izq;
    struct nodo* der;
}nodo_t;

typedef struct abb{
  nodo_t* raiz;
  abb_comp cmp;
  abb_destruir destruir;
  size_t cant;
} abb_t;

/*Recibe 2 cadenas y devuelve:
Entero MENOR a 0 si la primer cadena es menor a la segunda
Entero MAYOR a 0 si la primer cadena es mayor a la segunda
0(CERO) si ambas cadenas son iguales
*/
typedef int (*abb_comparar_clave_t) (const char *, const char *){

}

typedef void (*abb_destruir_dato_t) (void *){

}

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){

}
bool abb_guardar(abb_t *arbol, const char *clave, void *dato){

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

//destruye el arbol
void abb_destruir(abb_t *arbol){

}
