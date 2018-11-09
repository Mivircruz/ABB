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
	print_test("Borrar elemento A es NULL", !abb_borrar(abb, "A"));

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

bool insertar_preposiciones(abb_t* abb){

	char* preposiciones_desordenadas[] = {"segun","en","so","con","por","bajo","cabe","entre","sin","a","hacia","contra","versus","ante","para","via","tras","durante","hasta","desde","sobre","mediante","de"};
	bool ok = false;
	size_t cant_proposiciones = 23;
	for (size_t i = 0; i < cant_proposiciones; i++){
		ok = abb_guardar(abb,preposiciones_desordenadas[i],preposiciones_desordenadas[i]);
	}
	return ok;
}

bool verificar_insertados(abb_t* abb){
	bool ok = false;
	size_t cant_proposiciones = 23;
	char* proposiciones[] = {"a", "ante", "bajo", "cabe", "con", "contra", "de", "desde", "durante", "en", "entre", "hacia", "hasta", "mediante", "para", "por", "segun", "sin", "so", "sobre", "tras", "versus", "via"};
	for (size_t i = 0; i < cant_proposiciones; i++){
		if (! (proposiciones[i] == abb_obtener(abb, proposiciones[i]) ) ){
			ok = false;
			break;
		}
		ok = true;
	}
	return ok;
}

bool imprimir(const char* nada, void* cadena, void* extra){
  printf("%s;", (char*)cadena);
	return true;
}

bool borrar_pronombres(abb_t* abb){
	char* proposiciones[] = {"a", "ante", "bajo", "cabe", "con", "contra", "de", "desde", "durante", "en", "entre", "hacia", "hasta", "mediante", "para", "por", "segun", "sin", "so", "sobre", "tras", "versus", "via"};
	//bool ok = false;
	size_t cant_proposiciones = 23;
	for (size_t i = 0; i < cant_proposiciones; i++){
	if (!(proposiciones[i] == abb_borrar(abb,proposiciones[i]) ))
		return false;
	}
	return true;
}

void pruebas_abb_varios_elementos(){

	abb_t* abb = abb_crear(strcmp,NULL);

	bool ok = false;
	ok = insertar_preposiciones(abb);
	print_test("colocado varios elementos", ok);
	print_test("la cantidad de pronombres colocados es 23", (abb_cantidad(abb) == 23));
	ok = verificar_insertados(abb);
	//verificar de alguna forma que estan ordenados
	print_test("los elementos insertados estan presentes en el arbol", ok);
	printf("Resultado de usar el iterador interno con imprimir;\n");
	abb_in_order(abb,imprimir,NULL);
	printf("\n");
	ok = borrar_pronombres(abb);
	print_test("Todos los pronombres fueron borrados", ok);
	print_test("La cantidad de nodos es 0", (abb_cantidad(abb) == 0));
	abb_destruir(abb);
}

void pruebas_abb_iter_simples(){
	printf("\nPruebas de iterador con abb vacio\n");
	abb_t* abb = abb_crear(NULL,NULL);

	abb_iter_t* iter = abb_iter_in_crear(abb);
	print_test("Iterador NO creado porque el abb no tiene raiz", !iter);
	//abb_iter_in_destruir(iter);

	char *clave1 = "perro", *valor1 = "guau";
	//char *clave2 = "gato", *valor2 = "miau";
	//char *clave3 = "vaca", *valor3 = "mu";

	printf("\nPruebas de iterador con abb de un solo elemento\n");

	abb_guardar(abb, clave1, valor1);
	iter = abb_iter_in_crear(abb);
	print_test("El iterador creado no esta en NULL", iter);
	print_test("El valor actual al que apunta es el guardado", (abb_iter_in_ver_actual(iter) == clave1) );
	print_test("El iterador NO esta al final", (abb_iter_in_al_final(iter) == false));
	print_test("El iterador puede avanzar", (abb_iter_in_avanzar(iter) == true));
	print_test("El iterador esta al final", (abb_iter_in_al_final(iter) == true));
	print_test("El iterador NO puede avanzar", (abb_iter_in_avanzar(iter) == false));

	abb_iter_in_destruir(iter);
}

/*-----------------------------------
          Funcion Principal
--------------------------------------*/
void pruebas_abb_alumno(){
	pruebas_abb_vacio();
	pruebas_abb_insertar();
	pruebas_abb_varios_elementos();
	pruebas_abb_iter_simples();
}
