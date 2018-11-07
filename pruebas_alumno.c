#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "testing.h"
#include "abb.h"


void pruebas_abb_vacio(void){

	printf("INICIO PRUEBAS ABB VACÍO\n");

	//Declaración de variables auxiliares

	abb_t* abb = abb_crear(strcmp, NULL);

	//Comienzo de pruebas

	print_test("Crear abb vacío", abb);
	print_test("El abb tiene 0 elementos", !abb_cantidad(abb));
	print_test("Borrar elemento A en abb vacío es NULL\n", !abb_borrar(abb, "A"));
	print_test("Obtener elemento A en abb vacío es NULL", !abb_obtener(abb, "A"));
	print_test("Elemento A pertenece a abb es falso", !abb_pertenece(abb, "A"));

	abb_destruir(abb);
}

static void pruebas_abb_insertar(){

	printf("INICIO PRUEBAS ABB INSERTAR\n");

	//Declaración de variables auxiliares

    abb_t* abb = abb_crear(strcmp, NULL);

    char *clave1 = "perro", *valor1 = "guau";
    char *clave2 = "gato", *valor2 = "miau";
    char *clave3 = "vaca", *valor3 = "mu";

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba abb insertar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Prueba abb la cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Prueba abb obtener clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Prueba abb pertenece clave1, es true", abb_pertenece(abb, clave1));
   // print_test("Prueba abb borrar clave1, es valor1", abb_borrar(abb, clave1) == valor1);
   // print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    /* Inserta otros 2 valores y no los borra (se destruyen con el abb) */
    print_test("Prueba abb insertar clave2", abb_guardar(abb, clave2, valor2));
  	print_test("Prueba abb la cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb obtener clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Prueba abb pertenece clave2, es true", abb_pertenece(abb, clave2));

    print_test("Prueba abb insertar clave3", abb_guardar(abb, clave3, valor3));
  	print_test("Prueba abb la cantidad de elementos es 3", abb_cantidad(abb) == 3);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb obtener clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Prueba abb pertenece clave3, es true", abb_pertenece(abb, clave3));

    abb_destruir(abb);
}


/*-----------------------------------
          Funcion Principal
--------------------------------------*/
void pruebas_abb_alumno(){
	pruebas_abb_vacio();
	pruebas_abb_insertar();
}
