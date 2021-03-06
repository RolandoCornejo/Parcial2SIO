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

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <unistd.h>
#include <pthread.h>
  

//Definiendo la estructura cliente
typedef struct clienteStr {
    char nombre[256];
    int prioridad;
    int llegada;
    int tiempo;

}clienteStr;
//Definiendo estructura que contiene los datos para pasarlos a thread
typedef struct lista {
            clienteStr actual;
   	    }lista;
//el thread
void *func(void *var)
{
    lista *datos=(lista *)var;
    printf("------------------------\n");
    printf("ATENCIÓN A CLIENTE: %s \n", datos->actual.nombre);
    printf("PRIORIDAD: %d \n",datos ->actual.prioridad);
    printf("TIEMPO DE LLEGADA: %d \n",datos->actual.llegada);
    printf("TIEMPO DE DURACIÓN: %d \n", datos->actual.tiempo);
}
// 
typedef struct cliente { 
    int correlativo; 
    int prioridad; // A menor valor de prioridad, más alta la prioridad
    int tiempoLlegada;
    int tiempoTransaccion;
    struct cliente* siguiente; 
  } Cliente; 
  
// Función que crea un nuevo cliente
Cliente* newCliente(int c, int p, int tL, int tT) 
{ 
    Cliente* temp = (Cliente*)malloc(sizeof(Cliente)); 
    temp->correlativo = c; 
    temp->prioridad = p; 
    temp->tiempoLlegada = tL;
    temp->tiempoTransaccion = tT;
    temp->siguiente = NULL; 
  
    return temp; 
} 
  
// Regresa el valor en la cabeza de la queue
int peek(Cliente** cabeza) 
{ 
    return (*cabeza)->correlativo; 
} 
int peekP(Cliente** cabezaP) 
{ 
    return (*cabezaP)->prioridad; 
} 
int peektT(Cliente** cabezatT) 
{ 
    return (*cabezatT)->tiempoTransaccion; 
} 
int peektL(Cliente** cabezatL) 
{ 
    return (*cabezatL)->tiempoLlegada; 
} 
  
// Quita el elemento con la mayor prioridad 
void pop(Cliente** cabeza) 
{ 
    Cliente* temp = *cabeza; 
    (*cabeza) = (*cabeza)->siguiente; 
    free(temp); 
} 
  
// Función que añade conforme a valor de prioridad
void push(Cliente** cabeza, int c, int p, int tL, int tT) 
{ 
    Cliente* comienzo = (*cabeza); 
  
    // Crea un nuevo cliente
    Cliente* temp = newCliente(c, p, tL, tT); 
  
    // Caso especial cuando se ingresa otra cliente con prioridad más alta
    if ((*cabeza)->prioridad > p) { 
  
        // Ingresa el nuevo cliente antes de la cabeza anterior
        temp->siguiente = *cabeza; 
        (*cabeza) = temp; 
    } 
    else { 
  
        // Encuentra una nueva posición para el nodo
        while (comienzo->siguiente != NULL && 
               comienzo->siguiente->prioridad < p) { 
            comienzo = comienzo->siguiente; 
        } 
  
        // O encuentra posición o le toca al final
        temp->siguiente = comienzo->siguiente; 
        comienzo->siguiente = temp; 
    } 
} 
  
// Verifica si la lista está vacía
int isEmpty(Cliente** cabeza) 
{ 
    return (*cabeza) == NULL; 
} 

//Thread de proceso en el banco
void *proceso()
{
        // Creando la queue con prioridad
  Cliente* pq = newCliente(1, 1, 0, 6);
  push(&pq, 2, 3, 1, 3);
  push(&pq, 3, 2, 1, 5);
  push(&pq, 4, 4, 2, 6);
  push(&pq, 5, 4, 3, 9);
  push(&pq, 6, 4, 4, 1);
  push(&pq, 7, 2, 4, 3);
  push(&pq, 8, 1, 5, 8);
  
  
  
  float promP1=0, promP2=0, promP3=0, promP4=0;
  int c1=0, c2=0, c3=0, c4=0;
  
  printf("\n");
  printf("-------------------ORDEN DE ATENCIÓN DE LOS CLIENTES--------------------\n");
  printf("-----------------LUEGO DE SER ORDENADOS POR PRIORIDAD-------------------\n");
  printf("\n");
    while (!isEmpty(&pq)) { 
        printf(" Cliente #%d | Prioridad: %d | Tiempo de llegada: %d | Tiempo de duración: %d \n", peek(&pq), peekP(&pq), peektL(&pq), peektT(&pq));
        if(peekP(&pq)==1 && peektL(&pq)==0)
        {
            promP1=peektT(&pq);
        }
        
        if(peekP(&pq)==1)
        {
            c2=c2+1;
            promP2=promP2+peektT(&pq);
        }
        else if(peekP(&pq)==2)
        {
            c3=c3+1;
            promP3=promP3+peektT(&pq);
        }
        else if(peekP(&pq)==3)
        {
            c4=c4+1;
            promP4=promP4+peektT(&pq);
        }
        pop(&pq); 
    } 
    printf("\n");
    printf("-------------------ESTADÍSTICAS DEL BANCO--------------------\n");
    printf("\n");
    printf("Promedio de espera de clientes de alta prioridad: %f \n",(promP1));
    printf("Promedio de espera de clientes de media prioridad: %f \n",(promP2/c2));
    printf("Promedio de espera de clientes de baja prioridad: %f \n",(promP3/c3));
    printf("Promedio de espera de clientes de prioridad cero: %f \n",(promP4/c4));
}

int main() 
{ 
  printf("\n");
  printf("-------------------ORDEN DE LLEGADA DE CLIENTES--------------------\n");
  printf("\n");
    
    pthread_t th_id;
    clienteStr lista_clientes[]={
            {"Maria",1,0,6},
            {"Berta",3,1,3},
            {"Juana",2,1,5},
            {"Carol",4,2,6},
            {"Julio",4,3,9},
            {"Carla",4,4,1},
            {"Josef",2,4,3},
            {"Anton",1,5,8}
        };
    //variable que contiene el length de la lista de clientes
    size_t n = sizeof(lista_clientes) / sizeof(lista_clientes[0]);
    //el for loop para recorrer la lista de clientes
    for(int i=0; i<n; i++)
    {
        //inicializando la lista de los datos
        lista datos={lista_clientes[i]};
        //creando el thread de cada cliente
        pthread_create(&th_id, NULL, func, (void*)&datos);
        //Que el programa espere a que termine de ejecutarse el thread para continuar
        pthread_join(th_id,NULL);
    }
    pthread_create(&th_id, NULL, proceso, NULL);
     
    
    
       pthread_exit(NULL);
    return 0; 
}
