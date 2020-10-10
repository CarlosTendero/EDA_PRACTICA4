/*
 * File:   TR_VictorOtero_CarlosTendero.c
 * Author: Carlos Tendero
 *         Victor Otero
 *
 * Created on 22 de abril de 2018, 16:48
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <stdlib.h>
#include <time.h>
#include <locale.h>

/* ZONA DE DECLARACIÓN DE CONSTANTES*/

/*Constantes para manejo de errores */
#define CORRECTO 0
#define ERR_PILA_VACIA 1 
#define ERR_MEMORIA 2
#define ERR_COLA_VACIA 1
#define ERR_ARBOL_VACIO 2
#define ERR_LECT_FICHERO 100
#define ERR_ELE_NO_ENCONTRADO 200

#define NOM_FICHERO "frases.txt"
/* Nombre del fichero que contiene las frases */

#define MAX_CARACTERES 100
/* Maximo de carácteres de la frase */

/* Constantes para manejo de opciones */
#define OPCION_1 1
#define OPCION_2 2
#define OPCION_3 3
#define OPCION_4 4
#define OPCION_5 5
#define OPCION_6 6
#define OPCION_7 7
#define SALIR 8

/* ZONA DE DECLARACIÓN DE TIPOS*/

typedef enum {
    FALSE, TRUE
} tBoolean;
/* Tipo Boolean*/

/* Tipo nodo. Cada nodo contiene un elemento de la pila o cola. */
typedef struct _pnodo {
    char Elem; /* Variable para almacenar un elemento de la pila o cola */
    struct _pnodo *Sig;
    /* Puntero al siguiente nodo que contiene un elemento. */
} tNodo;

/* Tipo Cola. */
typedef struct {
    tNodo *pCab, *pCol; /* Punteros a la cabeza y la cola. */
} tCola;

/*Tipo Pila */
typedef tNodo tPila;

/* Tipo para las líneas del fichero */
typedef struct {
    int Num; /* Posición entre las frases */
    char Frase[MAX_CARACTERES]; /*Frase */
} tReg;

/* Tipo tNodoArbol */
typedef struct NodoArbol {
    struct NodoArbol *pIzq;
    char Dato;
    struct NodoArbol *pDer;
} tNodoArbol;


/*ZONA DE DECLARACIÓN DE PROTOTIPOS DE FUNCIONES */

/* Función: AsignarMemoriaPila
 * Devuelve un puntero a un puntero de tipo tPila.
 * Parámetros de entrada: 
 * no tiene.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Puntero a puntero de tipo tPila. Valor devuelto por la función.
 */
tPila **AsignarMemoriaPila(int N);

/* Función: AsignarMemoriaCola
 * Devuelve un puntero a un puntero de tipo tCola.
 * Parámetros de entrada: 
 * no tiene.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Puntero a puntero de tipo tCola. Valor devuelto por la función.
 */
tCola **AsignarMemoriaCola(void);

/* Función: Encolar
 * Devuelve el resultado de la operación (correcto o error).
 * Parámetros de entrada: 
 * Elemento añadir a la cola.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Cola. Valor devuelto por referencia.
 * Resultado de la operación. Valor devuelto por la función.
 */
int Encolar(tCola **p, char E);

/* Funcion: Desencolar
 * Devuelve el resultado de la operacion (correcto o error).
 * Parï¿½metros de entrada: 
 * Elemento anyadir a la cola.
 * Precondiciones: 
 * no tiene 
 * Parametros de salida: 
 * Cola. Valor devuelto por referencia.
 * Elemento desapilado. Valor devuelto por referencia.
 * Resultado de la operacion. Valor devuelto por la funcion.
 */
int Desencolar(tCola **p, float *E);
/* Funcion: Apilar
 * Devuelve el resultado de la operacion (correcto o error).
 * Parametros de entrada: 
 * Elemento anyadir a la pila.
 * Precondiciones: 
 * no tiene 
 * Parametros de salida: 
 * Pila. Valor devuelto por referencia.
 * Resultado de la operacion. Valor devuelto por la funcion.
 */
int Apilar(tPila **p, char E);

/* Función: Desapilar
 * Devuelve el resultado de la operación (correcto o error).
 * Parámetros de entrada: 
 * Elemento añadir a la pila.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Pila. Valor devuelto por referencia.
 * Elemento desapilado. Valor devuelto por referencia.
 * Resultado de la operación. Valor devuelto por la función.
 */
int Desapilar(tPila **p, char *E);

/* Función: Palindroma
 * Devuelve el resultado de la operación (correcto o error).
 * Parámetros de entrada: 
 * Cadena a chequear si es palíndromo.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Es o no palíndromo. Valor devuelto por referencia.
 * Resultado de la operación. Valor devuelto por la función.
 */
int Palindroma(char * Cad, tBoolean *EsPal);

/* Función: LeeFichero
 * Lee un fichero con la información de los conjuntos y
 * almacena la
 * información.
 * Parámetros de entrada: 
 * Nombre de fichero. 
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Puntero a puntero a tipo tReg, almacena la información 
 * leida. Valor devuelto por referencia.
 * Número de líneas leídas. Valor devuelto por referencia.
 * Resultado de la operación. Valor devuelto por la función.
 */
int LeeFichero(char *NomFichero, tReg **pR, int *N);

/* Función: Menu
 * Devuelve la opción de menú escogida.
 * Parámetros de entrada: 
 * no tiene.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Opción de menú escogida. Valor devuelto por la función.
 */
int Menu(void);

/* Función: BusquedaBinaria
 * Busca la frase en pR que ocupa la posición Clave. 
 * Parámetros de entrada: 
 * Puntero a tipo tReg que guarda la información leída 
 * del fichero.
 * Número de líneas almacenadas.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Puntero a puntero a tipo char, almacena la frase que 
 * ocupa la posición Clave. Valor devuelto por referencia.
 * Resultado de la operación. Valor devuelto por la función.
 */

int BusquedaBinaria(tReg *pR, int N, int Clave, char **Frase);

/* Función: InsertarNodo
 * Inserta un nuevo nodo en el árbol binario.
 * Parámetros de entrada: 
 * Carácter a insertar en el árbol.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Puntero a puntero de tipo tNodoArbol. Valor devuelto por  
 * referencia.
 * 
 * Resultado de la operación. Valor devuelto por la  
 * función.
 */
int InsertarNodo(tNodoArbol **pArbol, char Car);

/* Función: Inorden
 * Recorre el árbol en modo inorden y muestra el recorrido 
 * en pantalla.
 * Parámetros de entrada: 
 * no tiene.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Puntero a puntero de tipo tNodoArbol. Valor devuelto 
 *  por referencia.
 * 
 */
void inOrden(tNodoArbol *pArbol);

/* Función: Preorden
 * Recorre el árbol en modo preorden y muestra el recorrido 
 * en pantalla.
 * Parámetros de entrada: 
 * no tiene.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Puntero a puntero de tipo tNodoArbol. Valor devuelto 
 *  por referencia.
 * 
 * 
 */
void preOrden(tNodoArbol *pArbol);

/* Función: Postorden
 * Recorre el árbol en modo preorden y muestra el recorrido 
 * en pantalla.
 * Parámetros de entrada: 
 * no tiene.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Puntero a puntero de tipo tNodoArbol. Valor devuelto 
 *  por referencia.
 */
void postOrden(tNodoArbol *pArbol);

/* Función: CrearArbol
 * Inserta un nuevo nodo en el árbol binario.
 * Parámetros de entrada: 
 * Cadena que contiene los caracteres que formaran parte 
 * del árbol.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Puntero a puntero de tipo tNodoArbol. Valor devuelto por  
 * referencia.
 * Resultado de la operación. Valor devuelto por la  
 * función.
 */

int CrearArbol(tNodoArbol **pArbol, char *Cad);

/* Función: Altura
 * Cálcula la altura del árbol.
 * Parámetros de entrada: 
 * Puntero a tNodoArbol.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Altura. Valor devuelto por la función.
 */
int Altura(tNodoArbol *pArbol);

/* Función: Max
 * Cálcula el máximo de dos elementos.
 * Parámetros de entrada: 
 * Numero 1 y Numero 2.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Maximo. Valor devuelto por la función.
 */
int Max(int x, int y);

/* Función: TratarError
 * Trata el error que se le pasa como parámetro.
 * Parámetros de entrada: 
 * Error.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * no tiene.
 */
void TratarError(int Error);

int main() /* PROGRAMA PRINCIPAL */ {
    int Resultado = 0, Opcion = 0;
    /* Resultado: permite guardar el resultado de las operaciones; Opcion:permite guardar la opción seleccionada por el 
       usuario */
    char **Cadena = NULL;
    /* Puntero a la cadena de caracteres seleccionada de las almacenadas en el fichero */
    tBoolean Pal, FlgSalir;
    /* Pal: permite guardar si la frase es o no un palíndromo; FlgSalir: permite controlar la salida del programa*/
    int Num = 0, NF = 0;
    /* Num: número de líneas leídas delfichero; NF: Posición de la frase a buscar entre las almacenadas en el fichero */
    tReg **pReg = NULL;
    /* Puntero a puntero que permite guardar los datos leidos del fichero*/
    tNodoArbol **pA = NULL;
    /* Puntero a puntero a estructura de tipo árbol */

    int i = 0, posicion = 0; /*variable auxiliar*/
     
    setlocale(LC_ALL, "spanish");
    pReg = malloc(sizeof (tReg *));
    (*pReg) = NULL;

    Resultado = LeeFichero(NOM_FICHERO, pReg, &Num);
    if (Resultado == CORRECTO) {
        FlgSalir = FALSE;
        do {
            Opcion = Menu();
            switch (Opcion) {
                case OPCION_1: /*1. Seleccionar frase.*/

                    if(Cadena != NULL)
                        if(*Cadena != NULL)
                            free(*Cadena);
                    free(Cadena);
                    
                    if(Cadena == NULL){
                    Cadena = malloc(sizeof (char *));
                    (*Cadena) = malloc(sizeof (MAX_CARACTERES));
                    }
                    printf("\nSe dispone de las siguientes frases");

                    for (i = 0; i < Num; i++)
                        printf("\n%d\t%s", (*pReg)[i].Num, (*pReg)[i].Frase);
                    printf("\nElige la frase que quiera: \n");
                    scanf("%d", &NF); /*Se escoge la frase*/
                    /*control de errores*/
                    while (Num < NF) {
                        printf("\nOpcion incorrecta, por favor eliga una frase: ");
                        scanf("%d", &NF);
                    }
                    posicion = BusquedaBinaria((*pReg), Num, NF, Cadena); /*busqueda binaria*/
                   printf("\n%s", *Cadena); 
                   
                    if (posicion != -1)/*control de errores*/
                        printf("\nLa frase seleccionada es: %s", (*pReg)[posicion].Frase);
                    else
                        printf("\nNo se ha encontrado la frase");


                    break;

                case OPCION_2: /*2. Comprobar si es palíndromo.*/
                    
                    Palindroma(*Cadena, &Pal);
                    if (Pal) {
                        printf("Es palindroma");
                    } else {
                        printf("No es palindroma");
                    }
                    break;
                case OPCION_3:          /*3. Convertir en árbol */
                   
                    if(Cadena != NULL){
                    
                    if(pA != NULL)      /*Existia un arbol antes (?)*/
                        if(*pA != NULL)
                            free(*pA);
                    free(pA);
                    
                    pA = malloc(sizeof (tNodoArbol *)); /*Reserva de memoria*/
                    (*pA) = NULL;                       /*Contenido del arbol*/
                    
                    CrearArbol(pA, *Cadena);            /*Creamos el arbol*/
                    }
                    else        /*no se escogio antes una frase*/
                        printf("\nNo se ha seleccionado la frase\n");
                    break;
                case OPCION_4: /*4. Recorrer en inorden.*/

                    if(pA != NULL)
                        inOrden(*pA);   /*InOrden*/
                    else
                        printf("\nNo se ha construido el arbol");
                    break;

                case OPCION_5: /* 5. Recorrer en preorden. */

                    if(pA != NULL)
                        preOrden(*pA);  /*PreOrden*/
                    else
                        printf("\nNo se ha construido el arbol");
                    break;
                case OPCION_6: /* 6. Recorrer en postorden. */

                    if(pA != NULL)
                        postOrden(*pA); /*PostOrden*/
                    else
                        printf("\nNo se ha construido el arbol");
                    break;                    
                case OPCION_7: /*7. Calcular la altura*/
                    if(pA!= NULL)
                        printf("\nLa altura del arbol es:\t%d\n", Altura(*pA));
                    else
                        printf("\nNo se ha construido el arbol");
                    break;
                case SALIR:
                    FlgSalir = TRUE;
                    printf(" Adios\n");

                    /*Liberamos pReg*/
              /*      if (pReg != NULL)
                        if (*pReg != NULL)
                            free((*pReg));
                    free(pReg);
*/
                    /*Liberamos cadena*/
                    if (Cadena != NULL)
                        if (*Cadena != NULL)
                            free(*Cadena);
                    free(Cadena);
                    /*Liberamos el arbol*/
                    if (pA != NULL)
                        if (*pA != NULL)
                            free(*pA);
                    free(pA);

                    break;
                default:
                    printf("Opcion no valida\n");
                    break;

            }
        } while (Opcion != SALIR);
    }
    return Resultado;

}

/* Función: BusquedaBinaria
 * Busca la frase en pR que ocupa la posición Clave. 
 * Parámetros de entrada: 
 * Puntero a tipo tReg que guarda la información leída 
 * del fichero.
 * Número de líneas almacenadas.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Puntero a puntero a tipo char, almacena la frase que 
 * ocupa la posición Clave. Valor devuelto por referencia.
 * Resultado de la operación. Valor devuelto por la función.
 */

int BusquedaBinaria(tReg *pR, int N, int Clave, char **Frase) {

    int primero = 0, ultimo = N, central = 0, valor = 0;
    while (primero <= ultimo) {
        central = (primero + ultimo) / 2;
        valor = pR[central].Num;
        if (Clave == valor){
            strcpy(*Frase, pR[central].Frase);
            return central; /*posicion encontrada*/
        }
        else if (valor > Clave)
            ultimo = central - 1; /*actualizo primero*/
        else
            primero = central + 1; /*actualizo ultimo*/
    }
    return -1; /*Elemento no encontrado*/
}

/* Función: Menu
 * Devuelve la opción de menú escogida.
 * Parámetros de entrada: 
 * no tiene.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Opción de menú escogida. Valor devuelto por la función.
 */
int Menu(void) {
    int opcion = 0;

    printf("\n1.\tSeleccionar frase");
    printf("\n2.\tComprobar si es palindromo");
    printf("\n3.\tConvertir en arbol");
    printf("\n4.\tRecorrer arbol en modo inorden");
    printf("\n5.\tRecorrer arbol en modo preorden");
    printf("\n6.\tRecorrer arbol en modo postorden");
    printf("\n7.\tCalcular la altura");
    printf("\n8.\tSalir del programa");
    printf("\nIntroduce opcion: ");
    scanf("%d", &opcion);
    return opcion;

}

/* Función: LeeFichero
 * Lee un fichero con la información de los conjuntos y
 * almacena la
 * información.
 * Parámetros de entrada: 
 * Nombre de fichero. 
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Puntero a puntero a tipo tReg, almacena la información 
 * leida. Valor devuelto por referencia.
 * Número de líneas leídas. Valor devuelto por referencia.
 * Resultado de la operación. Valor devuelto por la función.
 */
int LeeFichero(char *NomFichero, tReg **pR, int *N) {
    char cadena[MAX_CARACTERES];
    char *toks = NULL;
    int i = 0, leido = 0;
    FILE *fichero = NULL;

    if (pR == NULL)
        return -1;

    fichero = fopen(NomFichero, "r");
    if (fichero) {
        while (fgets(cadena, MAX_CARACTERES, fichero)) {
            pR[i] = (tReg*) malloc(sizeof (tReg));
            toks = strtok(cadena, ";"); /*Cojo la posicion*/
            (*pR)[i].Num = atol(toks);
            toks = strtok(NULL, "\n"); /*Cojo la frase, si no es \n entonces probar con ;*/
            strcpy((*pR)[i].Frase, toks);
            i++;
            leido = 1;
            (*N)++;
        }
        if (leido == 0) {
            printf("\nFichero vacio");
            fclose(fichero);
            return -1; /*No se ha leido correctamente*/
        } else {
            fclose(fichero);
            return CORRECTO; /*se ha leido correctamente*/
        }
    }
    return -1; /*no se ha leido correctamente*/
}

/* Función: AsignarMemoriaPila
 * Devuelve un puntero a un puntero de tipo tPila.
 * Parámetros de entrada: 
 * no tiene.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Puntero a puntero de tipo tPila. Valor devuelto por la función.
 */
tPila **AsignarMemoriaPila(int N) {
    tPila **new_pila = NULL;
    /*reserva de memoria*/
    new_pila = (tPila**) malloc(sizeof (tPila*));
    /*control de errores*/
    if (new_pila == NULL)
        return NULL;
    /*reserva de memoria para el contenido*/
    //(*new_pila) = (tPila*)malloc(N*sizeof(tPila));
    /*control de errores*/
    //if((*new_pila) == NULL)
    //    return NULL;

    (*new_pila) = NULL;

    /*se devuelve la pila creada*/
    return new_pila;

}

/* Función: AsignarMemoriaCola
 * Devuelve un puntero a un puntero de tipo tCola.
 * Parámetros de entrada: 
 * no tiene.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Puntero a puntero de tipo tCola. Valor devuelto por la función.
 */
tCola **AsignarMemoriaCola(void) {

    tCola **new_cola = NULL;
    /*reserva de memoria*/
    new_cola = (tCola**) malloc(sizeof (tCola*));
    /*control de erroes*/
    if (new_cola == NULL)
        return NULL;
    /*reserva para el contenido de memoria*/
    //(*new_cola) = (tCola*)malloc(sizeof(tCola));
    /*control de errores*/
    //if((*new_cola) == NULL)
    //    return NULL;

    (*new_cola) = NULL;

    /*se devuelve la cola creada*/
    return new_cola;

}

/* Función: Encolar
 * Devuelve el resultado de la operación (correcto o error).
 * Parámetros de entrada: 
 * Elemento añadir a la cola.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Cola. Valor devuelto por referencia.
 * Resultado de la operación. Valor devuelto por la función.
 */
int Encolar(tCola **p, char E) {
    tNodo* nodo_aux = NULL; /*variable auxiliar*/

    nodo_aux = (tNodo*) malloc(sizeof (tNodo));


    if (nodo_aux == NULL) /*control de errores*/
        return -1;
    else {
        nodo_aux->Elem = E;
        nodo_aux->Sig = NULL;
        /*esta vacia la cola (?)*/
        if ((*p)->pCab == NULL) {
            (*p)->pCab = nodo_aux;
            /*solo hay un elemento para este caso por lo que la cola 
             y la cabeza apuntan al mismo*/
            (*p)->pCol = (*p)->pCab;
        } else { /*no esta vacia*/
            (*p)->pCol->Sig = nodo_aux;
            (*p)->pCol = (*p)->pCol->Sig;
        }
    }
    return 1;

}

/* Funcion: Apilar
 * Devuelve el resultado de la operacion (correcto o error).
 * Parametros de entrada: 
 * Elemento anyadir a la pila.
 * Precondiciones: 
 * no tiene 
 * Parametros de salida: 
 * Pila. Valor devuelto por referencia.
 * Resultado de la operacion. Valor devuelto por la funcion.
 */
int Apilar(tPila **p, char E) {
    tNodo *nodo_aux = NULL;
    int resultado = 0;

    nodo_aux = (tNodo*) malloc(sizeof (tNodo));

    if (nodo_aux == NULL) /*control de errores*/
        resultado = -1;
    else {
        nodo_aux->Elem = E;
        if (*p == NULL) /*si no hay elementos*/
            nodo_aux->Sig = NULL;
        else /*si hay elementos*/
            nodo_aux->Sig = *p;
        *p = nodo_aux;
        resultado = 1; /*correcto*/
    }
    return resultado;

}

/* Función: Desapilar
 * Devuelve el resultado de la operación (correcto o error).
 * Parámetros de entrada: 
 * Elemento añadir a la pila.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Pila. Valor devuelto por referencia.
 * Elemento desapilado. Valor devuelto por referencia.
 * Resultado de la operación. Valor devuelto por la función.
 */

int Desapilar(tPila **p, char *E) {
    tNodo* nodo_aux = NULL;
    int resultado = 0;

    if (*p == NULL) /*control de errores*/
        resultado = -1;

    else {
        nodo_aux = *p;
        *E = (*p)->Elem; /*recojo elemento*/
        *p = (*p)->Sig; 
        free(nodo_aux); /*libero memoria*/
    }
    return resultado;

}

/* Función: Palindroma
 * Devuelve el resultado de la operación (correcto o error).
 * Parámetros de entrada: 
 * Cadena a chequear si es palíndromo.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Es o no palíndromo. Valor devuelto por referencia.
 * Resultado de la operación. Valor devuelto por la función.
 */

int Palindroma(char *Cad, tBoolean *EsPal) {
    char* d = Cad;
    char* s = Cad;
    tNodo *pAux; // Declaro una variable pAux de tipo tNodo
    tPila** pilaCad;
    *EsPal = TRUE;
    int cont = 0;
    char res;
    while (*(d += !isspace(*s++)) = *s); //Elimina espacios en blanco
    pilaCad = AsignarMemoriaPila(strlen(Cad));
    for (int i = 0; i < strlen(Cad); i++) {
        Apilar(pilaCad, Cad[i]);
    }

    if (pilaCad != NULL) { // Si nuestra pila esta vacia...
        pAux = *pilaCad; // Igualamos nuestra variable auxiliar a la pila, para que al recorrer la pila no perdamos los punteros
        do {
            if (pAux->Elem != Cad[cont]) {
                *EsPal = FALSE;
            }
            cont++;
            pAux = (*pAux).Sig; // Movemos el puntero a la siguiente posicion de la pila
        } while (pAux != NULL && EsPal); // hasta que pAux no sea nulo no para, es decir, si llega al final se sale

        free(pAux); // Liberamos memoria de la variable auxiliar
    }
}

/* Función: InsertarNodo
 * Inserta un nuevo nodo en el árbol binario.
 * Parámetros de entrada: 
 * Carácter a insertar en el árbol.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Puntero a puntero de tipo tNodoArbol. Valor devuelto por  
 * referencia.
 * 
 * Resultado de la operación. Valor devuelto por la  
 * función.
 */
int InsertarNodo(tNodoArbol **pArbol, char Valor) {
    if ((*pArbol) == NULL) {
        *pArbol = malloc(sizeof (tNodoArbol));  /*Reserva de memoria*/
        if ((*pArbol) != NULL) {                /*Control de errores*/
            (*pArbol)->Dato = Valor;            /*Actualizo el error*/
            (*pArbol)->pIzq = NULL;             /*Hijo izquierdo*/
            (*pArbol)->pDer = NULL;             /*Hijo derecho*/
        }
        else    /*No se ha reservado memoria*/
            printf("no se inserto %c. No hay memoria disponible.\n", Valor);

    }
    else {      /*El nodo que hemos insertado ya "existia"*/
                /*Se insertan, orden estricto*/
        if (Valor <= (*pArbol)->Dato)       /*Valor (?) raiz pequenyo (?)*/
            InsertarNodo(&((*pArbol)->pIzq), Valor);    /*Inserto por el hijo izquierdo*/
        else if (Valor > (*pArbol)->Dato)   /*Valor (?) raiz mayor (?)*/   
            InsertarNodo(&((*pArbol)->pDer), Valor);    /*Inserto por el hijo derecho*/
        else    /*No se ha podido insertar*/
            printf("No insertar\n");
    }
}

/* Función: CrearArbol
 * Inserta un nuevo nodo en el árbol binario.
 * Parámetros de entrada: 
 * Cadena que contiene los caracteres que formaran parte 
 * del árbol.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Puntero a puntero de tipo tNodoArbol. Valor devuelto por  
 * referencia.
 * Resultado de la operación. Valor devuelto por la  
 * función.
 */
int CrearArbol(tNodoArbol **pArbol, char *Cad) {
    
  int i = 0;
  
  for (i = 0; i < strlen(Cad); i++)
      InsertarNodo(pArbol, Cad[i]); /*se inserta el nodo*/
        

}

/* Función: Inorden
 * Recorre el árbol en modo inorden y muestra el recorrido 
 * en pantalla.
 * Parámetros de entrada: 
 * no tiene.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Puntero a puntero de tipo tNodoArbol. Valor devuelto 
 *  por referencia.
 * 
 */
void inOrden(tNodoArbol *pArbol) {

    /*existe izq (?)*/
    if (pArbol->pIzq != NULL)
        inOrden(pArbol->pIzq);  /*visito izquierdo*/

    /*visito nodo*/
    printf("\n%c", pArbol->Dato);

    /*existe der (?)*/
    if (pArbol->pDer != NULL)
        inOrden(pArbol->pDer);  /*visito derecho*/


}

/* Función: Preorden
 * Recorre el árbol en modo preorden y muestra el recorrido 
 * en pantalla.
 * Parámetros de entrada: 
 * no tiene.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Puntero a puntero de tipo tNodoArbol. Valor devuelto 
 *  por referencia.
 * 
 * 
 */
void preOrden(tNodoArbol *pArbol) {
    /*Visito nodo*/
    printf("\n%c", pArbol->Dato);   /*muestro el dato*/
    /*existe izq (?)*/
    if (pArbol->pIzq != NULL)
        preOrden(pArbol->pIzq); /*visito izquierdo*/
    /*existe der(?)*/
    if (pArbol->pDer != NULL)
        preOrden(pArbol->pDer); /*visito derecho*/

}

/* Función: Postorden
 * Recorre el árbol en modo preorden y muestra el recorrido 
 * en pantalla.
 * Parámetros de entrada: 
 * no tiene.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Puntero a puntero de tipo tNodoArbol. Valor devuelto 
 *  por referencia.
 */
void postOrden(tNodoArbol *pArbol) {

    /*existe izq(?)*/
    if (pArbol->pIzq != NULL)
        postOrden(pArbol->pIzq);    /*visito izquierdo*/
    /*existe der(?)*/
    if (pArbol->pDer != NULL)
        postOrden(pArbol->pDer);    /*visito derecho*/
    /*visito el nodo*/
    printf("\n%c", pArbol->Dato);   /*muestro el dato*/


}

/* Función: Altura
 * Cálcula la altura del árbol.
 * Parámetros de entrada: 
 * Puntero a tNodoArbol.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Altura. Valor devuelto por la función.
 */
int Altura(tNodoArbol *pArbol) {
  
    if(pArbol == NULL)
        return 0;
    
    if (pArbol->pIzq == NULL && pArbol->pDer == NULL)
         return 1;
    else
    {
        if(Max(Altura(pArbol->pIzq), Altura(pArbol->pDer)) == 1)
            return 1 + Altura(pArbol->pDer);
        else
            return 1 + Altura(pArbol->pIzq);
    }
}

/* Función: Max
 * Cálcula el máximo de dos elementos.
 * Parámetros de entrada: 
 * Numero 1 y Numero 2.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * Maximo. Valor devuelto por la función.
 */
int Max(int x, int y) {
    
    if(x < y)
        return 1;
    else
        return 2;
    
}

/* Función: TratarError
 * Trata el error que se le pasa como parámetro.
 * Parámetros de entrada: 
 * Error.
 * Precondiciones: 
 * no tiene 
 * Parámetros de salida: 
 * no tiene.
 */
void TratarError(int Error) {
    /* A RELLENAR POR EL ALUMNO */
}

