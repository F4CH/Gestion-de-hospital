## Descripción del Programa

Este programa permite a los usuarios gestionar la atención de pacientes en un hospital. Los usuarios pueden registrar nuevos pacientes, asignar prioridades, ver la lista de espera, actualizar al siguiente paciente y mostrar los pacientes por prioridad. Esta herramienta está diseñada para mejorar la eficiencia en la atención de los pacientes, asegurando que aquellos en situaciones críticas reciban atención lo más pronto posible.

## Cómo compilar y ejecutar

Dado que el sistema está diseñado para ser accesible y fácil de probar, recomendamos usar [Repl.it](http://repl.it/) para una rápida configuración y ejecución. 

Sigue estos pasos para comenzar:

1. Visita [Repl.it](https://repl.it/).
2. Crea una nueva cuenta o inicia sesión si ya tienes una.
3. Una vez en tu dashboard, selecciona "New Repl" y elige "Import from GitHub".
4. Pega la URL del repositorio: `https://github.com/F4CH/Gestion-de-hospital`.
5. [Repl.it](http://repl.it/) clonará el repositorio y preparará un entorno de ejecución.
6. En la pestaña "Configurate Repl", sección "Configure the Compile Command", pegar el siguiente comando "gcc tdas/*.c main.c -Wno-unused-result -o main" y presionar "done".
7. Presiona el botón "Run" para compilar y ejecutar la aplicación.

## Funcionalidades

### Funcionando correctamente:

- Registrar pacientes con sus datos básicos y una prioridad inicial.
- Asignar o modificar la prioridad de los pacientes.
- Ver la lista de espera de pacientes, ordenada por prioridad y hora de registro.
- Atender al siguiente paciente, respetando el orden de prioridad.
- Ver la lista de los pacientes segun su prioridad.

### Problemas Conocidos

- Los datos deben ser ingresados por el usuarios siempre en minusculas o en mayusculas, ya que sino el programa sufrira errores.
- El usuario debe ingresar los datos correctamente tal y como le pide el programa, un ejemplo de esto sería ingresar el nombre Rya (imaginando que el usuario se saltó una letra), esto haría que al buscar al paciente como Ryan, este no sea detectado.

### A mejorar:
- Hacer que el interfaz sea mas completo para el usuario
- Mejorar la lectura de datos para aceptar errores del usuario
- Permitir la edicion de los datos en los pacientes en casos de errores
- No permite modificar la prioridad una vez asignada.

## Ejemplo de uso

### EL USUARIO NO SE EQUIVOCA AL INGRESAR LOS PACIENTES DURANTE LA EJECUCION DE TODO EL PROGRAMA

**Paso 1: Registrar un Nuevo Paciente**

Se comienza registrando los nuevos pacientes que acaban de llegar al hospital.
````
Opcion seleccionada: 1) Registrar Paciente
Ingrese el nombre del paciente: Ryan
Ingrese el apellido del paciente: Gosling
Ingrese la edad del paciente : 43
Ingrese el sintoma del paciente : Dolor de cabeza
````
````
Opcion seleccionada: 1) Registrar Paciente
Ingrese el nombre del paciente: Scarlett
Ingrese el apellido del paciente: Johnanson
Ingrese la edad del paciente : 39
Ingrese el sintoma del paciente : Colicos
````

El sistema registra a Ryan Gosling y  con una prioridad inicial "Bajo" y guarda la hora actual de registro. La prioridad inicial puede ser ajustada más tarde basada en una evaluación médica más detallada.


Paso 2: Asignar Prioridad a un Paciente
Tras una evaluación inicial, el médico determina que el estado de Ana requiere atención prioritaria.

````
Opción seleccionada: 2) Asignar prioridad a paciente
Ingrese el nombre del paciente para asignar prioridad : Ryan 
Ingrese el apellido del paciente para asignar prioridad : Gosling
Ingrese la nueva prioridad del paciente (1 = BAJA , 2 = MEDIA , 3 = ALTA) = 3
````


El sistema actualiza la prioridad de Ryan Gosling a "Alto", asegurando que será uno de las próximos pacientes en ser atendido.


Paso 3: Ver la Lista de Espera


El usuario revisa la lista de espera para ver todos los pacientes y sus prioridades.

````
Opción seleccionada: 3) Mostrar lista de espera
````


La lista muestra a Ryan Gosling en la parte superior y a Scarlett Johnanson en la parte inferior, indicando su prioridad alta y baja respectivamente , siendo Ryan Gosling al tener la prioridad alta el siguiente en línea para recibir atención.


Paso 4: Atender al Siguiente Paciente


Ryan Gosling es llamado para ser atendido basándose en su prioridad.

````
Opción seleccionada: 4) Atender al siguiente paciente
````

El sistema muestra que Ryan Gosling está siendo atendido y la elimina de la lista de espera.


Paso 5: Mostrar pacientes por prioridad


El usuario revisa la lista para poder ver sus pacientes segun su orden de prioridad y llegada.
````
Opción seleccionada: 5) Mostrar pacientes por prioridad
Ingrese la prioridad del paciente (1 = BAJA , 2 = MEDIA , 3 = ALTA): 1
````

El sistema muestra a Scarlett Johnanson como la siguiente en ser antendida con prioridad Baja

Paso 6: Salir del sistema de gestion hospitaliaria

Al terminar el turno de trabajo o simplemente no querer usar el programa, el usuario selecciona la opcion de salir de la aplicacion
````
Opción seleccionada: 6) Salir de la aplicacion
````
