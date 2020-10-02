/******************************************************************************

                        SISTEMAS OPERATIVOS SIO104 03l
                     Rolando José Cornejo Torres 
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
    int tiempo;
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
    printf("Tiempo: %d minutos\n", datos->actual.tiempo);
    printf("Prioridad: %d\n", datos->actual.prioridad);
}

int main()
{
    pthread_t th_id;
    cliente lista_clientes[]={
            {.nombre="Maria",.tiempo=3,.prioridad=1},
            {.nombre="Juan",.tiempo=10,.prioridad=2},
            {.nombre="Josefa",.tiempo=3,.prioridad=4},
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
