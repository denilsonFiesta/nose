#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"
#include "heap.h"

typedef struct {
  int prioridad;
  char nombre[50];
  Heap* heapPrecedentes;
}Tarea;


void mostrarMenu(){
  printf("\n      Organizacion de Tareas     \n");
  printf("[1] Agregar Tarea \n");
  printf("[2] Establecer precedencia entre tareas \n");
  printf("[3] Mostrar Tareas por hacer \n");
  printf("[4] Marcar tarea completada \n");
  printf("[5] Deshacer ultima accion \n");
  printf("[6] Exportar Datos \n");
  printf("[7] Cargar las tareas del archivo \n");
  printf("Seleccione una opción: ");
}

Tarea* obtenerTarea(){

  Tarea* new = calloc(1, sizeof(Tarea));
  printf("Nombre : ");
  scanf("%s", new->nombre);
  printf("Prioridad : ");
  scanf("%d", new->prioridad);
  new->heapPrecedentes =CreateHeap();
  return new;
  
}

//opcion 1

void agregarTarea (Heap* heapTareas){
  Tarea* nuevaTarea = obtenerTarea();
  
}

//opcion 2

void establecerPrecedencia(Heap* heapTareas, )



int main(void) {
  int opcion = 7;

  Heap* heapTareas = CreateHeap();
  

  while (true){
    mostrarMenu();

    scanf("%d", &opcion);
    printf("\n");

    switch(opcion){
      case 1:
        agregarTarea(heapTareas);
        break;
      default:
        printf("Opcion Invalida, ingrese nueva opcion\n");
    }
    if(opcion == 7)
      break;
  }
  return 0;
}
