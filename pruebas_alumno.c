#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "testing.h"
#include "abb.h"

/* ******************************************************************
 *                 FUNCIONES VISITAR ITERADOR INTERNO
 * *****************************************************************/

bool visitar_primero(const char* clave, void* dato, void* extra){

    if(*(int*)dato == 2)
        return false;

    *(int*)extra += *(int*)dato;
        return true;
}

bool visitar_dos_primeros(const char* clave, void* dato, void* extra){

    if(*(int*)dato == 3)
        return false;

    *(int*)extra += *(int*)dato;
        return true;
}

bool visitar_tres_primeros(const char* clave, void* dato, void* extra){

    if(*(int*)dato == 4)
        return false;

    *(int*)extra += *(int*)dato;
        return true;
}

bool visitar_cuatro_primeros(const char* clave, void* dato, void* extra){

    if(*(int*)dato == 5)
        return false;

    *(int*)extra += *(int*)dato;
        return true;
}

bool visitar_todos(const char* clave, void* dato, void* extra){

    *(int*)extra += *(int*)dato;
        return true;
}

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_abb_vacio(void){

	printf("\nINICIO PRUEBAS ABB VACÍO\n");

	//Declaración de variables auxiliares

	abb_t* abb = abb_crear(strcmp, NULL);

	//Comienzo de pruebas

	print_test("Crear abb vacío", abb);
	print_test("El abb tiene 0 elementos", !abb_cantidad(abb));
	print_test("Borrar elemento A en abb vacío es NULL\n", !abb_borrar(abb, "A"));
	print_test("Obtener elemento A en abb vacío es NULL", !abb_obtener(abb, "A"));
	print_test("Elemento A pertenece a abb es falso", !abb_pertenece(abb, "A"));
	print_test("Borrar elemento A es NULL", !abb_borrar(abb, "A"));

	abb_destruir(abb);
}

static void pruebas_abb_insertar(){

	printf("\nINICIO PRUEBAS ABB INSERTAR\n");

	//Declaración de variables auxiliares

    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb pertenece clave1 (raíz sin hijos), es true", abb_pertenece(abb, clave1));
   	print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
   	print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    /* Inserta otros 2 valores y no los borra (se destruyen con el abb) */
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
  	print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));

    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
  	print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));
    print_test("Prueba abb borrar clave2 (raíz con un hijo), es true", abb_borrar(abb, clave2) == valor2);
    print_test("Cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Volver a insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Volver a insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Borrar clave3 (raíz con dos hijos)", abb_borrar(abb, clave3) == valor3);


    abb_destruir(abb);
}

static void prueba_abb_reemplazar(){

	printf("\nINICIO PRUEBAS ABB REEMPLAZAR\n");

	//Declaración de variables auxiliares.

    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave1 = "perro", *valor1a = "guau", *valor1b = "warf";
    char *clave2 = "gato", *valor2a = "miau", *valor2b = "meaow";

    /* Inserta 2 valores y luego los reemplaza */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}

static void prueba_abb_reemplazar_con_destruir(){

	printf("\nINICIO PRUEBAS ABB REEMPLAZAR CON FUNCIÓN DESTRUIR\n");

	//Declaración de variables auxiliares.

    abb_t* abb = abb_crear(strcmp,free);

    char *clave1 = "perro", *valor1a, *valor1b;
    char *clave2 = "gato", *valor2a, *valor2b;

    /* Pide memoria para 4 valores */
    valor1a = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2a = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));

    /* Inserta 2 valores y luego los reemplaza (debe liberar lo que reemplaza) */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1a));
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb obtener clave1 es valor1a", abb_obtener(abb, clave1) == valor1a);
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2a));
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb obtener clave2 es valor2a", abb_obtener(abb, clave2) == valor2a);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb insertar clave1 con otro valor", abb_guardar(abb, clave1, valor1b));
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb obtener clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Prueba abb insertar clave2 con otro valor", abb_guardar(abb, clave2, valor2b));
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb obtener clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    /* Se destruye el abb (se debe liberar lo que quedó dentro) */
    abb_destruir(abb);
}

static void prueba_abb_borrar(){

	printf("\nINICIO PRUEBAS ABB BORRAR\n");

    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave1 = "a", 		*valor1 = "guau";
    char *clave2 = "ab",		*valor2 = "miau";
    char *clave3 = "abc", 		*valor3 = "mu";
    char *clave4 = "abcd", 		*valor4 = "pio";
    char *clave5 = "abcde",		*valor5 = "me";
    char *clave6 = "abcdef", 	*valor6 = "mamadera";
    char *clave7 = "abcdefg", 	*valor7 = "mesa";
    char *clave8 = "abcdefgh", 	*valor8 = "fideos";
    char *clave9 = "abcdefghi", *valor9 = "milanesa";

    /* Inserta 3 valores y luego los borra */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));

    /* Al borrar cada elemento comprueba que ya no está pero los otros sí. */
    print_test("Prueba abb pertenece clave3, es verdadero", abb_pertenece(abb, clave3));
    print_test("Prueba abb borrar clave3, es valor3", abb_borrar(abb, clave3) == valor3);
    print_test("Prueba abb borrar clave3, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba abb pertenece clave3, es falso", !abb_pertenece(abb, clave3));
    print_test("Prueba abb obtener clave3, es NULL", !abb_obtener(abb, clave3));
    print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Prueba abb pertenece clave1, es verdadero", abb_pertenece(abb, clave1));
    print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Prueba abb borrar clave1, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba abb pertenece clave1, es falso", !abb_pertenece(abb, clave1));
    print_test("Prueba abb obtener clave1, es NULL", !abb_obtener(abb, clave1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);

    print_test("Prueba abb pertenece clave2, es verdadero", abb_pertenece(abb, clave2));
    print_test("Prueba abb borrar clave2, es valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Prueba abb borrar clave2, es NULL", !abb_borrar(abb, clave3));
    print_test("Prueba abb pertenece clave2, es falso", !abb_pertenece(abb, clave2));
    print_test("Prueba abb obtener clave2, es NULL", !abb_obtener(abb, clave2));
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    /*Inserta los valores en desorden*/
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb insertar clave9", abb_guardar(abb, clave9, valor9));
    print_test("Prueba abb insertar clave5", abb_guardar(abb, clave5, valor5));
    print_test("Prueba abb insertar clave7", abb_guardar(abb, clave7, valor7));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb insertar clave4", abb_guardar(abb, clave4, valor4));
    print_test("Prueba abb insertar clave6", abb_guardar(abb, clave6, valor6));
    print_test("Prueba abb insertar clave8", abb_guardar(abb, clave8, valor8));

    /*Borra nodos*/

    print_test("Prueba borrar clave5, es verdadero", abb_borrar(abb,clave5) == valor5);
    print_test("Prueba borrar clave6, es verdadero", abb_borrar(abb,clave6) == valor6);
    print_test("Prueba borrar clave2, es verdadero", abb_borrar(abb,clave2) == valor2);
    print_test("Prueba borrar clave9, es verdadero", abb_borrar(abb,clave9) == valor9);
    print_test("Prueba borrar clave4, es verdadero", abb_borrar(abb,clave4) == valor4);
    print_test("Prueba borrar clave3, es verdadero", abb_borrar(abb,clave3) == valor3);

    abb_destruir(abb);
}

void pruebas_iter_abb_vacio(){

    printf("\nINICIO PRUEBAS ITERADOR CON ABB VACÍO\n");

    //Declaración de variables auxiliares

    abb_t* abb = abb_crear(strcmp, NULL);
    abb_iter_t* iter = abb_iter_in_crear(abb);

    //Comienzo de pruebas

    print_test("Ver actual es NULL", !abb_iter_in_ver_actual(iter));
    print_test("Avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Iterador está al final es true", abb_iter_in_al_final(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

void pruebas_iter_abb(){

    printf("\nINICIO PRUEBAS ITERADOR CON ABB NO VACÍO\n");

    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave1 = "a",         *valor1 = "guau";
    char *clave2 = "ab",        *valor2 = "miau";
    char *clave3 = "abc",       *valor3 = "mu";
    char *clave4 = "abcd",      *valor4 = "pio";
    char *clave5 = "abcde",     *valor5 = "me";
    char *clave6 = "abcdef",    *valor6 = "mamadera";
    char *clave7 = "abcdefg",   *valor7 = "mesa";
    char *clave8 = "abcdefgh",  *valor8 = "fideos";
    char *clave9 = "abcdefghi", *valor9 = "milanesa";

    /*Inserta los valores en desorden*/
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb insertar clave9", abb_guardar(abb, clave9, valor9));
    print_test("Prueba abb insertar clave5", abb_guardar(abb, clave5, valor5));
    print_test("Prueba abb insertar clave7", abb_guardar(abb, clave7, valor7));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb insertar clave4", abb_guardar(abb, clave4, valor4));
    print_test("Prueba abb insertar clave6", abb_guardar(abb, clave6, valor6));
    print_test("Prueba abb insertar clave8", abb_guardar(abb, clave8, valor8));

    abb_iter_t* iter = abb_iter_in_crear(abb);

    print_test("Iterador esta al final es false", !abb_iter_in_al_final(iter));
    print_test("Actual es clave1", !strcmp(abb_iter_in_ver_actual(iter), clave1));
    print_test("Avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Iterador esta al final es false", !abb_iter_in_al_final(iter));
    print_test("Actual es clave2", !strcmp(abb_iter_in_ver_actual(iter), clave2));
    print_test("Avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Iterador esta al final es false", !abb_iter_in_al_final(iter));
    print_test("Actual es clave3", !strcmp(abb_iter_in_ver_actual(iter), clave3));
    print_test("Avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Iterador esta al final es false", !abb_iter_in_al_final(iter));
    print_test("Actual es clave4", !strcmp(abb_iter_in_ver_actual(iter), clave4));
    print_test("Avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Actual es clave5", !strcmp(abb_iter_in_ver_actual(iter), clave5));
    print_test("Iterador esta al final es false", !abb_iter_in_al_final(iter));
    print_test("Avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Actual es clave6", !strcmp(abb_iter_in_ver_actual(iter), clave6));
    print_test("Avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Iterador esta al final es false", !abb_iter_in_al_final(iter));
    print_test("Actual es clave7", !strcmp(abb_iter_in_ver_actual(iter), clave7));
    print_test("Avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Iterador esta al final es false", !abb_iter_in_al_final(iter));
    print_test("Actual es clave8", !strcmp(abb_iter_in_ver_actual(iter), clave8));
    print_test("Avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Iterador esta al final es false", !abb_iter_in_al_final(iter));
    print_test("Actual es clave9", !strcmp(abb_iter_in_ver_actual(iter), clave9));
    print_test("Avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Iterador esta al final es true", abb_iter_in_al_final(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

void pruebas_iter_corte_derecho(){

    printf("\nINICIO PRUEBAS ITERAR CORTE DERECHO\n");

    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave1 = "a",         *valor1 = "guau";
    char *clave2 = "ab",        *valor2 = "miau";
    char *clave3 = "abc",       *valor3 = "mu";
    char *clave4 = "abcd",      *valor4 = "pio";
    char *clave5 = "abcde",     *valor5 = "me";
    char *clave6 = "abcdef",    *valor6 = "mamadera";
    char *clave7 = "abcdefg",   *valor7 = "mesa";
    char *clave8 = "abcdefgh",  *valor8 = "fideos";
    char *clave9 = "abcdefghi", *valor9 = "milanesa";

/*Inserta elementos de tal manera que no haya ninguno a la derecha*/

    print_test("Prueba abb insertar clave9", abb_guardar(abb, clave9, valor9));
    print_test("Prueba abb insertar clave8", abb_guardar(abb, clave8, valor8));
    print_test("Prueba abb insertar clave7", abb_guardar(abb, clave7, valor7));
    print_test("Prueba abb insertar clave6", abb_guardar(abb, clave6, valor6));
    print_test("Prueba abb insertar clave5", abb_guardar(abb, clave5, valor5));
    print_test("Prueba abb insertar clave4", abb_guardar(abb, clave4, valor4));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));

    abb_iter_t* iter = abb_iter_in_crear(abb);

    print_test("Iterador esta al final es false", !abb_iter_in_al_final(iter));
    print_test("Actual es clave1", !strcmp(abb_iter_in_ver_actual(iter), clave1));
    print_test("Avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Iterador esta al final es false", !abb_iter_in_al_final(iter));
    print_test("Actual es clave2", !strcmp(abb_iter_in_ver_actual(iter), clave2));
    print_test("Avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Iterador esta al final es false", !abb_iter_in_al_final(iter));
    print_test("Actual es clave3", !strcmp(abb_iter_in_ver_actual(iter), clave3));
    print_test("Avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Iterador esta al final es false", !abb_iter_in_al_final(iter));
    print_test("Actual es clave4", !strcmp(abb_iter_in_ver_actual(iter), clave4));
    print_test("Avanzar es true", abb_iter_in_avanzar(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

void pruebas_iter_corte_izquierdo(){

	printf("\nINICIO PRUEBAS ITERAR CORTE IZQUIERDO\n");

    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave1 = "a", 		*valor1 = "guau";
    char *clave2 = "ab",		*valor2 = "miau";
    char *clave3 = "abc", 		*valor3 = "mu";
    char *clave4 = "abcd", 		*valor4 = "pio";
    char *clave5 = "abcde",		*valor5 = "me";
    char *clave6 = "abcdef", 	*valor6 = "mamadera";
    char *clave7 = "abcdefg", 	*valor7 = "mesa";
    char *clave8 = "abcdefgh", 	*valor8 = "fideos";
    char *clave9 = "abcdefghi", *valor9 = "milanesa";

/*Inserta elementos de tal manera que no haya ninguno a la izquierda*/

    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Prueba abb insertar clave4", abb_guardar(abb, clave4, valor4));
    print_test("Prueba abb insertar clave5", abb_guardar(abb, clave5, valor5));
    print_test("Prueba abb insertar clave6", abb_guardar(abb, clave6, valor6));
    print_test("Prueba abb insertar clave7", abb_guardar(abb, clave7, valor7));
    print_test("Prueba abb insertar clave8", abb_guardar(abb, clave8, valor8));
    print_test("Prueba abb insertar clave9", abb_guardar(abb, clave9, valor9));

    abb_iter_t* iter = abb_iter_in_crear(abb);

    print_test("Iterador esta al final es false", !abb_iter_in_al_final(iter));
    print_test("Actual es clave1", !strcmp(abb_iter_in_ver_actual(iter), clave1));
    print_test("Avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Iterador esta al final es false", !abb_iter_in_al_final(iter));
    print_test("Actual es clave2", !strcmp(abb_iter_in_ver_actual(iter), clave2));
    print_test("Avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Iterador esta al final es false", !abb_iter_in_al_final(iter));
    print_test("Actual es clave3", !strcmp(abb_iter_in_ver_actual(iter), clave3));
    print_test("Avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Iterador esta al final es false", !abb_iter_in_al_final(iter));
    print_test("Actual es clave4", !strcmp(abb_iter_in_ver_actual(iter), clave4));
    print_test("Avanzar es true", abb_iter_in_avanzar(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);

}

static void prueba_iter_interno(){

	printf("\nINICIO PRUEBAS ITERARADOR INTERNO\n");

    //Declaración de variables auxiliares

    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave1 = "a";
    int valor1 = 1;
    char *clave2 = "ab";
    int valor2 = 2;
    char *clave3 = "abc";
    int valor3 = 3;
    char *clave4 = "abcd"; 		
    int valor4 = 4;
    char *clave5 = "abcde";
   	int valor5 = 5;
    int extra = 0;

    //Inserta elementos 

    print_test("Prueba abb insertar clave4", abb_guardar(abb, clave4, &valor4));
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, &valor2));
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, &valor1));
    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, &valor3));
    print_test("Prueba abb insertar clave5", abb_guardar(abb, clave5, &valor5));

    //Inicio de pruebas

    abb_in_order(abb, visitar_primero, &extra);
    print_test("Prueba abb iter interno visitar un elemento\n", extra == 1);

    extra = 0;
    abb_in_order(abb, visitar_dos_primeros, &extra);
    print_test("Prueba abb iter interno visitar dos elementos\n", extra == 3);

    extra = 0;
    abb_in_order(abb, visitar_tres_primeros, &extra);
    print_test("Prueba abb iter interno visitar dos elementos\n", extra == 6);

    extra = 0;
    abb_in_order(abb, visitar_cuatro_primeros, &extra);
    print_test("Prueba abb iter interno visitar dos elementos\n", extra == 10);

    extra = 0;
    abb_in_order(abb, visitar_todos, &extra);
    print_test("Prueba abb iter interno visitar dos elementos\n", extra == 15);

    abb_destruir(abb);
}

static void prueba_abb_clave_vacia(){

	printf("\nINICIO PRUEBAS ABB CLAVE VACÍA\n");

    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave = "", *valor = "";

    print_test("Prueba abb insertar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

static void prueba_abb_valor_null(){

	printf("\nINICIO PRUEBAS ABB VALOR NULL\n");

    abb_t* abb = abb_crear(strcmp,NULL);

    char *clave = "", *valor = NULL;

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave vacia valor NULL", abb_guardar(abb, clave, valor));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
    print_test("Prueba abb pertenece clave vacia, es true", abb_pertenece(abb, clave));
    print_test("Prueba abb borrar clave vacia, es valor NULL", abb_borrar(abb, clave) == valor);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}



static void prueba_abb_volumen(size_t largo, bool debug){

    printf("\nINICIO PRUEBAS ABB VOLUMEN\n");

    abb_t* abb = abb_crear(strcmp,NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    unsigned* valores[largo];

    /* Inserta 'largo' parejas en el abb */
    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int));
        sprintf(claves[i], "%08d", i);
        *valores[i] = i;
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb almacenar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    /* Verifica que devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        ok = abb_pertenece(abb, claves[i]);
        if (!ok) break;
        ok = abb_obtener(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb pertenece y obtener muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    /* Verifica que borre y devuelva los valores correctos */
   for (size_t i = 0; i < largo; i++) {
        ok = abb_borrar(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Prueba abb borrar muchos elementos", ok);
    if (debug) print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    /* Destruye el abb y crea uno nuevo que sí libera */
   abb_destruir(abb);
    abb = abb_crear(strcmp,free);

    /* Inserta 'largo' parejas en el abb */
    ok = true;
    for (size_t i = 0; i < largo; i++) {
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    free(claves);

    /* Destruye el abb - debería liberar los enteros */
    abb_destruir(abb);

}

/*-----------------------------------
          Funcion Principal
--------------------------------------*/
void pruebas_abb_alumno(){
	pruebas_abb_vacio();
	pruebas_abb_insertar();
	prueba_abb_reemplazar();
	prueba_abb_reemplazar_con_destruir();
	prueba_abb_borrar();
	prueba_abb_clave_vacia();
	prueba_abb_valor_null();
	prueba_abb_volumen(1000, true);
    pruebas_iter_abb_vacio();
    pruebas_iter_abb();
    pruebas_iter_corte_derecho();
	pruebas_iter_corte_izquierdo();
	prueba_iter_interno();
}
