EL ANEXO:
(1) Cómo compilar y ejecutar la tarea:
[1] Esta función de agregar tareas es crear la tarea de tipo Tarea a partir de la funcion obtener, dónde se ingresó el nombre y su respectiva prioridad y luego, esa tarea la inserta en el mapa. Después se crear otra variable de tipo tarea obteniendolo con el obtener tarea auxiliar para agregarlo a la tabla hash.
[2] Se pide al usuario que ingrese 2 tareas para realizar alguna precedencia entre ellas. Puede ser que uno se haga primero que la otra. Y despúes se buscan ambas en el mapa. Se asigna la segunda tarea con el auxiliar de la tabla hash para insertarlo en el mapa de los precedentes.
[3] Se comienza a mostrar las tareas por hacer desde el primero del mapa en órden descendente, y esta ejecuta el algoritmo de topological sort solo si no ha sido visitado antes, y de esa manera mostrar las tareas con mayor prioridad.
[4] Se pide al usuario que ingrese el nombre de la tarea a marcar como completada, una vez ingresada se procede a buscar si es que esta tarea es precedente de otras, y si es que lo fuera entonces se elimina de la lista de precedentes de las tareas encontradas. Luego se elimina la tarea del map y el hash.
[5] En la función del deshacer acción, se ve las posibilidades de que se quiera deshacer el agregado, el completado o el eliminado de alguna tarea y de sus precedentes. Para realizar esto de manera correcta se reutilizaron las mismas funciones para revertir una accion.
[6] Esta funcion importara datos de las Tareas desde un archivo .csv , para ello solicitara el nombre de un archivo (el cual idealmente deberia ser tareas.csv o alguno de similares caracteristicas que sea de su preferencia) y en caso de que el archivo exista, el programa guardar todos los datos de la tareas provenientes del archivo.
[7] Esta funcion es un extra del programa. Esta funcion muestra todas la tareas almacenadas, los atributos mostrados en la consola son el nombre de la tarea, su prioridad y su lista de precedentes. 

(2) Indique las opciones que funcionan correctamente y las que no lo hacen indicando posibles causas:

[-]Todas las opciones funcionan correctamente, no se encontro ningun error durante las pruebas realizadas. Notar que lo mostrado por la opcion 3 es una de la posibilidad valida para la resolucion de una tarea.

(3) Coevaluación del trabajo en parejas (usando rúbrica):

Nombre Equipo: Estructura-2
Participación activa y equitativa: 20
Resolución de conflictos: 20
Colaboración: 20
Responsabilidad: 20
Comunicación: 18

Puntaje Total: 98

Aspectos a mejorar: mejorar la coordinacion y la puntualizadad a la hora de reunirse.

(4) coevaluación del aporte individual de cada integrante (usando rúbrica).
-----------------------------------------------------------------
Nombre: Denilson Fiesta
Participación: 20
Responsabilidad: 20
Comunicación: 18
Calidad del Trabajo: 20
Trabajo en Equipo: 18

Aspectos a mejorar: Mejorar la seriedad

Puntaje Total: 96
------------------------------------------------------------------------
Nombre: Kavon Kermani
Participación: 19
Responsabilidad: 19
Comunicación: 19
Calidad del Trabajo: 20
Trabajo en Equipo: 20

Aspectos a mejorar: Mejorar la puntualidad a la hora de reunirse y una mejor comunicación para realizar la tarea.

Puntaje Total: 97
---------------------------------------------------------------


































































































































































































































































































































# atte: joselito
