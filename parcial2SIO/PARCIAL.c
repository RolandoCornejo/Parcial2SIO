/******************************************************************************

                    SISTEMAS OPERATIVOS SIO104 03l
                 Rolando José Cornejo Torres CT180058
                 Paola Raquel Jiménez Torrez JT180795
                 SIMULACIÓN DE VENTANILLA DE UN BANCO

                 CONSIDERACIONES:
        1. Prioridad alta: tercera edad, clientes VIP, mujeres embarazadas.
        2. Prioridad media
        3. Prioridad baja
        4. Ninguna prioridad: clientes sin cuenta.
                     

*******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

//Definiendo la estructura cliente
typedef struct cliente {
    char nombre[256];
    int tiempo_transaccion;
    int tiempo_llegada; //
    int prioridad;
}cliente;
//Definiendo estructura que contiene los datos para pasarlos a thread
typedef struct lista {
            cliente actual;
            cliente *caja1;
            cliente *caja2;
   	    }lista;
//el thread
void *func(void *var)
{
    lista *datos=(lista *)var;
    
    printf("Cliente: %s\n", datos->actual.nombre);
    printf("Tiempo de transacción: %d minutos\n", datos->actual.tiempo_transaccion);
    printf("Tiempo de llegada después de abierto: %d minutos\n", datos->actual.tiempo_transaccion);
    printf("Prioridad: %d\n", datos->actual.prioridad);
}

int main()
{
    pthread_t th_id;
    cliente lista_clientes[]={
            /******************************************************************************

                    SISTEMAS OPERATIVOS SIO104 03l
                 Rolando José Cornejo Torres CT180058
                 Paola Raquel Jiménez Torrez JT180795
                 SIMULACIÓN DE VENTANILLA DE UN BANCO

                 CONSIDERACIONES:
        1. Prioridad alta: tercera edad, clientes VIP, mujeres embarazadas.
        2. Prioridad media
        3. Prioridad baja
        4. Ninguna prioridad: clientes sin cuenta.
                     

*******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

//Definiendo la estructura cliente
typedef struct cliente {
    char nombre[256];
    int tiempo_transaccion;
    int tiempo_llegada; //
    int prioridad;
}cliente;
//Definiendo estructura que contiene los datos para pasarlos a thread
typedef struct lista {
            cliente actual;
            cliente *caja1;
            cliente *caja2;
   	    }lista;
//el thread
void *func(void *var)
{
    lista *datos=(lista *)var;
    
    printf("Cliente: %s\n", datos->actual.nombre);
    printf("Tiempo de transacción: %d minutos\n", datos->actual.tiempo_transaccion);
    printf("Tiempo de llegada después de abierto: %d minutos\n", datos->actual.tiempo_llegada);
    printf("Prioridad: %d\n", datos->actual.prioridad);
}

int main()
{
    pthread_t th_id;
    cliente lista_clientes[]={
            {"Maria",3,0,1},
            {"Berta",3,0,3},
            {"Juan Pablo",3,0,2},
            {"Juan",10,1,3},
            {"Julio",10,1,4},
            {"Carlos",10,1,4},
            {"Josefa",3,2,2},
            {"Antonieta",3,2,1},
            {"Roberto",3,2,3},
            {"Trujillo",3,2,1},
            {"Carolina",3,2,4},
        };
        cliente caja1[]={0};
        cliente caja2[]={0}; 
    //varia que contiene el length de la lista de clientes
    size_t n = sizeof(lista_clientes) / sizeof(lista_clientes[0]);
    //el for loop para recorrer la lista de clientes
    for(int i=0; i<n; i++)
    {
        //inicializando la lista de los datos
        lista datos={lista_clientes[i],caja1,caja2};
        //creando el thread de cada cliente
        pthread_create(&th_id, NULL, func, (void*)&datos);
        //Que el programa espere a que termine de ejecutarse el thread para continuar
        pthread_join(th_id,NULL);
    }
    pthread_exit(NULL);
    return 0;
}

        };
        cliente caja1[]={0};
        cliente caja2[]={0}; 
    //varia que contiene el length de la lista de clientes
    size_t n = sizeof(lista_clientes) / sizeof(lista_clientes[0]);
    //el for loop para recorrer la lista de clientes
    for(int i=0; i<n; i++)
    {
        //inicializando la lista de los datos
        lista datos={lista_clientes[i],caja1,caja2};
        //creando el thread de cada cliente
        pthread_create(&th_id, NULL, func, (void*)&datos);
        //Que el programa espere a que termine de ejecutarse el thread para continuar
        pthread_join(th_id,NULL);
    }
    pthread_exit(NULL);
    return 0;
}
