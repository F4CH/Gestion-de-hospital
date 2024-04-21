#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "tdas/list.h"

// Definición de la estructura para representar a una persona (paciente)
typedef struct{
  char nombre[50];
  char apellido[50];
  int edad;
  char sintoma[100];
  int prioridad;
  time_t fecha_hora;
  char *priochain;
} tipo_persona;

// Estructura para mantener las listas de pacientes con diferentes prioridades
typedef struct
{
  List *prioridad_baja;
  List *prioridad_media;
  List *prioridad_alta;
}tipo_prioridad;

// Función para inicializar la estructura de prioridades
tipo_prioridad *iniciar_prioridad()
{
  tipo_prioridad *prioridad = malloc(sizeof(tipo_prioridad));
  prioridad->prioridad_alta = list_create();
  prioridad->prioridad_media = list_create();
  prioridad->prioridad_baja = list_create();
  return prioridad;
}

// Función para registrar un paciente en la lista de espera
void registrar_paciente(List *lista)
{
  tipo_persona *persona = (tipo_persona*) malloc(sizeof(tipo_persona));
  printf("Ingrese el nombre del paciente: ");
  scanf("%s", persona->nombre);
  getchar();
  printf("Ingrese el apellido del paciente: ");
  scanf("%s", persona->apellido);
  getchar();
  printf("Ingrese la edad del paciente: ");
  scanf("%d", &persona->edad);
  getchar();
  printf("Ingrese el sintoma del paciente: ");
  fscanf(stdin, "%[^\n]", persona->sintoma);
  getchar();
  time(&persona->fecha_hora);

  persona->prioridad = 1;
  persona->priochain = "BAJA";
  list_pushBack(lista, persona);
}

// Función para mostrar la lista de espera
void mostrar_lista(List *lista)
{
  tipo_persona *persona = (tipo_persona*) list_first(lista);
  while(persona != NULL)
    {
      printf("Nombre del paciente: %s %s\n", persona->nombre, persona->apellido);
      printf("Edad del paciente : %d\n", persona->edad);
      printf("Sintoma del paciente: %s\n", persona->sintoma);
      printf("Hora de ingreso: %s\n", ctime(&persona->fecha_hora));
      printf("Prioridad del paciente: %s\n\n", persona->priochain);
      persona = (tipo_persona*) list_next(lista);
    }
}

// Funcion para ver si se encuentra el nombre en la lista
tipo_persona *esta_nombre(List *lista, char *nombre, char *apellido)
{
  tipo_persona *persona = (tipo_persona *) list_first(lista);
  while(persona != NULL)
    {
      if(strcmp(persona->nombre, nombre) == 0 && strcmp(persona->apellido, apellido) == 0)
        return persona;
      persona = (tipo_persona *) list_next(lista);
    }
  return NULL;
}

// Función para eliminar un paciente de la lista de espera
void eliminar_paciente(List *lista, tipo_persona *persona)
{
  tipo_persona *actual = (tipo_persona *) list_first(lista);
  while(actual != NULL)
    {
      if(actual == persona)
      {
        list_popCurrent(lista);
        return;
      }
      actual = (tipo_persona *) list_next(lista);
    }
}

// Función para comparar la fecha y hora de dos pacientes
int comparar(void *ptr, void *elemento)
{
  tipo_persona *ptr_persona = (tipo_persona *) ptr;
  tipo_persona *elemento_persona = (tipo_persona *) elemento;

  if(ptr_persona->fecha_hora < elemento_persona->fecha_hora)
    return 1;
  return 0;
}

// Función para convertir una cadena de caracteres en un número entero
int string_numero(char *cadena)
{
  int numero = 0;
  while((*cadena) != '\0')
    {
      numero = numero * 10 + (*cadena - '0');
      cadena++;
    }
  return numero;
}

// Función para asignar una nueva prioridad a un paciente
void asignar_prioridad(tipo_prioridad * lista)
{
  char nombre[50];
  char apellido[50];
  printf("Ingrese el nombre del paciente para asignar prioridad : ");
  scanf("%49s", nombre);
  getchar();
  printf("Ingrese el apellido del paciente para asignar prioridad : ");
  scanf("%49s", apellido);
  getchar();
  tipo_persona *persona_1 = esta_nombre(lista->prioridad_baja, nombre, apellido);
  if(persona_1 == NULL) 
  {
    printf("No se encontro el paciente\n");
    printf("Aprete cualquier boton para continuar");
    while((getchar() != '\n'));
    return;
  }
  char *priochain = (char *) malloc(sizeof(char) * 4);
  printf("Ingrese la nueva prioridad del paciente (1 = BAJA , 2 = MEDIA , 3 = ALTA): ");
  scanf("%3s", priochain);
  persona_1->prioridad = string_numero(priochain);

  if(persona_1->prioridad == 2)
  {
    persona_1->priochain = "MEDIA";
    eliminar_paciente(lista->prioridad_baja, persona_1);
    list_sortedInsert(lista->prioridad_media, persona_1, comparar);
  }
  else if(persona_1->prioridad == 3)
  {
    persona_1->priochain = "ALTA";
    eliminar_paciente(lista->prioridad_baja, persona_1);
    list_sortedInsert(lista->prioridad_alta, persona_1, comparar);
  }
  free(priochain);
}

// Función para mostrar la lista de espera ordenada por prioridad
void mostrar_lista_espera(tipo_prioridad *listas)
{
  mostrar_lista(listas->prioridad_alta);
  mostrar_lista(listas->prioridad_media);
  mostrar_lista(listas->prioridad_baja);
}

// Función para atender al siguiente paciente de la lista de espera
void atender_siguiente_paciente(tipo_prioridad *listas)
{
  tipo_persona *persona = (tipo_persona*) list_first(listas->prioridad_alta);
  if(persona != NULL)
  {
    list_popCurrent(listas->prioridad_alta);
    return;
  }

  persona = (tipo_persona*) list_first(listas->prioridad_media);
  if(persona != NULL)
  {
    list_popCurrent(listas->prioridad_media);
    return;
  }
  persona = (tipo_persona*) list_first(listas->prioridad_baja);
  if(persona != NULL)
  {
    list_popCurrent(listas->prioridad_baja);
    return;
  }
  printf("NO QUEDAN PACIENTES EN ESPERA\n");
  return;
}

// Función para mostrar la lista de pacientes por prioridad
void mostrar_pacientes_prioridad(tipo_prioridad *listas)
{
  char *priochain = (char *) malloc(sizeof(char) * 4);
  printf("Ingrese la prioridad del paciente (1 = BAJA , 2 = MEDIA , 3 = ALTA): ");
  scanf("%3[^\n]s", priochain);
  while((getchar() != '\n'));
  printf("\n");

  if(strcmp(priochain, "1") == 0)
    mostrar_lista(listas->prioridad_baja);
  else if(strcmp(priochain, "2") == 0)
    mostrar_lista(listas->prioridad_media);
  else
    mostrar_lista(listas->prioridad_alta);

  return;
}

// Función para limpiar la pantalla de la consola
void limpiar_pantalla()
{
  system("clear");
}

// Función para mostrar un mensaje y esperar a que el usuario presione una tecla
void presione_tecla_para_continuar() {
  puts("Presione una tecla para continuar...");
  getchar();
}

// Menú principal
void mostrar_menu_principal() {
  limpiar_pantalla();
  puts("========================================");
  puts("     Sistema de Gestión Hospitalaria");
  puts("========================================");

  puts("1) Registrar paciente");
  puts("2) Asignar prioridad a paciente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente paciente");
  puts("5) Mostrar pacientes por prioridad");
  puts("6) Salir de la aplicacion");
}

int main() {
  tipo_prioridad *listas = iniciar_prioridad();
  char opcion;
  do {
    mostrar_menu_principal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion);
    getchar();

    switch (opcion) {
    case '1':
      registrar_paciente(listas->prioridad_baja);
      break;
    case '2':
      asignar_prioridad(listas);
      break;
    case'3':
      mostrar_lista_espera(listas);
      break;
    case '4':
      atender_siguiente_paciente(listas);
      break;
    case '5':
      mostrar_pacientes_prioridad(listas);
      break;
    case '6':
      puts("Saliendo del sistema de gestión hospitalaria...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presione_tecla_para_continuar();

  } while (opcion != '6');
  
  return 0;
}