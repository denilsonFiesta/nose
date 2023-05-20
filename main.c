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

typedef struct{
  char tareaA[50];
  char tareaB[50];
}Conexion;


void mostrarMenu(){
  printf("\n      Organizacion de Tareas     \n");
  printf("[1] Agregar Tarea \n");
  printf("[2] Establecer precedencia entre tareas \n");
  printf("[3] Mostrar Tareas por hacer \n");
  printf("[4] Marcar tarea completada \n");
  printf("[5] Deshacer ultima accion \n");
  printf("[6] Importar Datos \n");
  printf("[7] Salir \n");
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

void establecerPrecedencia(Map* mapTareas, HashMap* hashTareas, char tareaA[50], char* tareaB[50], int wwout){
  
  char key1[50], key2[50];
  if(!wwout){
    printf("Ingrese la tarea1 : ");
    scanf("%s", key1);
  }else strcpy(key1, tareaA);
  
  Par* par1 = searchMap(hashTareas, key1);
  
  if(par1 == NULL){
    printf("--- NO se encontro la tarea --- \n");
    return;
  }

  if(!wwout){
    printf("Ingrese la tarea2 : ");
    scanf("%s", key2);
  }else strcpy(key2, tareaB);
  
  
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
  
  if(!wwout) printf("\nPrecedencia ingresada correctamente\n");
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
  int cont = 0 ;
  
  while(it!=NULL){
    Tarea* tarea = getTarea(it);

    printf("%s - %d\n", tarea->nombre, tarea->prioridad);
    
    Pair* it2 = rFirst(tarea->mapPrecedentes);
    while(it2 != NULL){
      TareaE* tareaP = getTareaEP(it2);
      printf("  %s\n",tareaP->nombre);
      it2 = rNext(tarea->mapPrecedentes);
    }
    cont++;
    it = rNext(mapTareas);
  }
  printf("Se encontraron %d tarea[s]. \n", cont);
}

//opcion 4

void marcarCompletada(Map* mapTareas, HashMap* hashTareas){
  char nombTarea[50];
  char resp;
  
  printf("Que tarea sera completada: ");
  scanf("%s", nombTarea);
  Par* parTarea = searchMap(hashTareas, nombTarea);

  if(parTarea == NULL){
    printf("--- NO se encontro la tarea --- \n");
    return;
  }
  

  Pair* tareita = Search(mapTareas, getTareaE(parTarea)->key );
  Tarea* tarea = getTarea(tareita);

  if(First(tarea->mapPrecedentes) != NULL){
    printf("Está seguro que desea eliminar la tarea? s/n: ");
    scanf("%s", &resp);
    if(resp != 's'){
      printf(" --- No se realizo ninguna accion ---");
      return;
    }
  }

  Pair* it = First(mapTareas);

  while(it != NULL){

    Tarea* check = getTarea(it);
    Pair* buscado = Search(check->mapPrecedentes, tarea->key);
    if(buscado != NULL){
      Remove(check->mapPrecedentes,tarea->key);
    }
    it =  Next(mapTareas);
  }

  Remove(mapTareas, getTareaE(parTarea)->key);
  eraseMap(hashTareas, nombTarea);
  printf("--- Tarea fue marcada como completada ---\n");    
}

//opcion 5

void deshacerAccion(Map* mapTareas, HashMap* hashTareas){
  Pair* primerTarea = First(mapTareas);
  if (primerTarea == NULL){
    printf("No hay acciones que deshacer\n");
    return;
  }
}

//opcion 6

void importarDatos(Map* mapTareas, HashMap* hashTareas){

  FILE* archivo;
  char getLine[1024];
  char nombreArchivo[50];

  Conexion* cn;

  List *listaConexiones = createList();
  
  printf("Ingrese el nombre del archivo a importar: ");
  scanf("%s", nombreArchivo);
  archivo = fopen(nombreArchivo, "r");

  if(archivo == NULL){
    printf("Error al abrir el archivo. \n");
    return;
  }

  fgets(getLine, 1024, archivo);

  while(fgets(getLine, 1024, archivo)){
    char* token;
    char* cualEs;
    int contCampos = 0;

    Tarea* tareaAdd = (Tarea*) calloc(1, sizeof(Tarea));
    
    tareaAdd->mapPrecedentes = createMap();

    token = strtok(getLine, ",");

    while(token != NULL){
      cualEs = token;

      switch(contCampos){
        case 0:
          strcpy(tareaAdd->nombre, cualEs);
          tareaAdd->nombre[strcspn(tareaAdd->nombre, "\n")] ='\0';
          break;
        case 1:
          tareaAdd->prioridad = atoi(cualEs);
          break;
        default:
          if(cualEs == NULL) break;
          cn = (Conexion*) calloc(1, sizeof(Conexion));
          strcpy(cn->tareaB, tareaAdd->nombre);
          strcpy(cn->tareaA, cualEs);
          cn->tareaA[strcspn(cn->tareaA, "\n")] ='\0';
          pushBack(listaConexiones, cn);
          break;
      }
      contCampos++;
      token = strtok(NULL, ",");
    }

    tareaAdd->key = getKey(tareaAdd->nombre, tareaAdd->prioridad);    
    Insert(mapTareas, tareaAdd->key, tareaAdd);
    TareaE* auxTarea = obtenerTareaAux(tareaAdd->nombre, tareaAdd->prioridad);
    insertMap(hashTareas, auxTarea->nombre, auxTarea);
  }

  //aqui mando la lista de coso a -> b
  
  Conexion* it = firstList(listaConexiones);
  
  while(it != NULL){
    //printf("%s - %s \n", it->tareaA, it->tareaB);
    establecerPrecedencia(mapTareas, hashTareas, it->tareaA, it->tareaB, 1);
    it = nextList(listaConexiones);
  }


  
  //aun en construcciones
  
  printf("Archivo importado correctamente\n");
  fclose(archivo);
}
  
int main(void) {
  int opcion = 8;

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
        establecerPrecedencia(mapTareas, hashTareas, "", "", 0);
        break;
      case 3:
        mostrarTareas(mapTareas, hashTareas);
        break;
      case 4:
        marcarCompletada(mapTareas, hashTareas);
        break;
      case 5:
        //deshacerAccion(mapTareas, hashTareas);
        break;
      case 6:
        importarDatos(mapTareas, hashTareas);
        break;
      case 7:
        printf("----Fin del Programa----\n");
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
