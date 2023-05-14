#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"
#include "map.h"
#include "hashmap.h"


typedef struct {
  int prioridad;
  char nombre[50];
  char* key;
  Map* mapPrecedentes;
}Tarea;

typedef struct {
  int prioridad;
  char nombre[50];
  char* key;
  int visited;
}TareaE;


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

char* getKey(char* nombre, int prioridad){
  char a = 33+prioridad;
  char* key= (char*)malloc(strlen(nombre) + 2); 
  *(key) = a;
  *(key+1) = '\0';
  strcat(key, nombre);
  return key;
}

Tarea* obtenerTarea(){

  Tarea* new = calloc(1, sizeof(Tarea));
  printf("Nombre : ");
  scanf("%s", new->nombre);
  printf("Prioridad : ");
  scanf("%d", &new->prioridad);  
  char a = 33+new->prioridad;
  new->key = getKey(new->nombre, new->prioridad);
  new->mapPrecedentes = createMap();
  return new;
  
}

TareaE* obtenerTareaAux(char* nombre, int prioridad){
  TareaE* new = calloc(1, sizeof(TareaE));
  strcpy(new->nombre, nombre);
  new->key = getKey(nombre, prioridad);
  new->prioridad = prioridad;
  new->visited = 0;
  return new;
}


TareaE* getTareaE(Par* nose){
  return nose->value;
}
TareaE* getTareaEP(Pair* nose){
  return nose->value;
}

Tarea* getTarea(Pair* nose){
  return nose->value;
}

void resetVisited(HashMap* hashTareas){
  Par* it  = firstMap(hashTareas);
  while(it != NULL){
    TareaE* tarea = getTareaE(it);
    tarea->visited = 0;
    it = nextMap(hashTareas);
  }
  
}

//opcion 1

void agregarTarea (Map* mapTareas, HashMap* hashTareas){
  Tarea* nuevaTarea = obtenerTarea();
  Insert(mapTareas, nuevaTarea->key, nuevaTarea);
  
  TareaE* auxTarea = obtenerTareaAux(nuevaTarea->nombre, nuevaTarea->prioridad);
  insertMap(hashTareas, auxTarea->nombre, auxTarea);
  printf("\nTarea ingresada correctamente\n");
}

//opcion 2

void establecerPrecedencia(Map* mapTareas, HashMap* hashTareas){

  char key1[50], key2[50];

  printf("Ingrese la tarea1 : ");
  scanf("%s", key1);

  Par* par1 = searchMap(hashTareas, key1);

  if(par1 == NULL){
    printf("--- NO se encontro la tarea --- \n");
    return;
  }

  printf("Ingrese la tarea2 : ");
  scanf("%s", key2);

  
  Par* par2 = searchMap(hashTareas, key2);

  if(par2 == NULL){
    printf("--- NO se encontro la tarea --- \n");
    return;
  }

  TareaE* tar1 = getTareaE(par1);
  TareaE* tar2 = getTareaE(par2);

  Pair* parcito = Search(mapTareas, tar2->key);
  Tarea* tarea2 = getTarea(parcito);

  //Tarea2 -> Tarea1
  Map* mapita =  tarea2->mapPrecedentes;
  TareaE* precedencia = obtenerTareaAux(tar1->nombre, tar1->prioridad);
  Insert(mapita, precedencia->key, precedencia);
  
  printf("\nPrecedencia ingresada correctamente\n");
}

//opcion 3


void topologicalSort(Tarea* v,  Map* mapTareas, HashMap* hashTareas){
  
  if( getTareaE( searchMap(hashTareas, v->nombre) )->visited  == 1 ) return;
  
  getTareaE( searchMap(hashTareas, v->nombre) )->visited  = 1;

  Pair* u = rFirst(v->mapPrecedentes);
  while(u != NULL){
    TareaE* aux = getTareaEP(u);
    Tarea* tarea = getTarea( Search(mapTareas, aux->key) );
    topologicalSort(tarea, mapTareas, hashTareas);
    u = rNext(v->mapPrecedentes);
  }

  printf("%s \n" , v->nombre);
  
}

void mostrarTareas(Map* mapTareas, HashMap* hashTareas){

  //Marcar unvisited al hash de tareas
  resetVisited(hashTareas);
  
  Pair* it = rFirst(mapTareas);
  while(it!=NULL){
    Tarea* tarea = getTarea(it);
    if( getTareaE( searchMap(hashTareas, tarea->nombre) )->visited  == 0){
      topologicalSort(tarea,mapTareas,hashTareas);
    }
    it = rNext(mapTareas);
  }
  
}

void imprimirTareas(Map* mapTareas){
  Pair* it = rFirst(mapTareas);
  while(it!=NULL){
    Tarea* tarea = getTarea(it);

    printf("%s - %d\n", tarea->nombre, tarea->prioridad);
    
    Pair* it2 = rFirst(tarea->mapPrecedentes);
    while(it2 != NULL){
      TareaE* tareaP = getTareaEP(it2);
      printf("  %s\n",tareaP->nombre);
      it2 = rNext(tarea->mapPrecedentes);
    }
    
    it = rNext(mapTareas);
  }
}
  
int main(void) {
  int opcion = 7;

  Map* mapTareas = createMap();
  HashMap* hashTareas = createHash(10000); // <- usa Par
  
  while (true){
    mostrarMenu();

    scanf("%d", &opcion);
    printf("\n");

    switch(opcion){
      case 1:
        agregarTarea(mapTareas, hashTareas);
        break;
      case 2:
        establecerPrecedencia(mapTareas, hashTareas);
        break;
      case 3:
        mostrarTareas(mapTareas, hashTareas);
        break;
      case 8:
        imprimirTareas(mapTareas);
        break;
      default:
        printf("Opcion Invalida, ingrese nueva opcion\n");
    }
    if(opcion == 7)
      break;
  }
  return 0;
}
