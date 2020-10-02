#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

//Definiendo el estructura cliente
typedef struct cliente {
    char nombre[256];
    int tiempo;
    int prioridad;
}cliente;

typedef struct lista {
            cliente actual;
            cliente *caja1;
            cliente *caja2;
   	    }lista;



void *func(void *var)
{
    lista *id=(lista *)var;
    
    printf("Cliente: %s\n", id->actual.nombre);
    printf("Tiempo: %d minutos\n", id->actual.tiempo);
    printf("Prioridad: %d\n", id->actual.prioridad);
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

    
    
    size_t n = sizeof(lista_clientes) / sizeof(lista_clientes[0]);
    for(int i=0; i<n; i++)
    {
        lista datos={lista_clientes[i],caja1,caja2};
 
        pthread_create(&th_id, NULL, func, (void*)&datos);
        pthread_join(th_id,NULL);
    }
    pthread_exit(NULL);
    return 0;
}
