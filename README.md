Contexto
Nuestro amigo Victor participa como un instructor en un programa de voluntariado. El jefe de Victor
le ha pedido que distribuya N camisetas entre M voluntarios, una camiseta para cada voluntario, donde N
es múltiplo de seis, y N ≥ M . Hay el mismo número de camisetas de cada una de las 6 tallas disponibles:
XXL, XL, L, M, S, y XS. Victor tiene un pequeño problema porque a cada voluntario sólo le vienen dos
tallas de camiseta y no sabe si tendrá las tallas adecuadas para todos.
Problema
El problema consiste en escribir un programa que decida si Victor puede distribuir las camisetas de
tal modo que todos los voluntarios tengan una camiseta que les venga bien. Téngase en cuenta que si
N > M pueden sobrar algunas camisetas.
En este trabajo hemos implementado tres versiones de algoritmos de avance rápido (voraces) para resolver el problema de asignación de tareas, con el objetivo de encontrar un equilibrio entre la eficiencia computacional y la calidad del beneficio total obtenido. Por un lado, hemos desarrollado un enfoque de Voraz Global (tanto en versión iterativa como recursiva) que prioriza las mejores asignaciones de toda la matriz mediante una ordenación previa de candidatos, buscando maximizar el beneficio a costa de un mayor tiempo de proceso. Por otro lado, hemos implementado un algoritmo de Voraz por Tarea, que toma decisiones locales inmediatas analizando cada tarea de forma independiente, lo que optimiza drásticamente el tiempo de ejecución y el uso de memoria al evitar estructuras de datos auxiliares y procesos de ordenación complejos. Esta dualidad nos permite contrastar cómo una estrategia más 'miope' pero rápida se comporta frente a una visión global más costosa asintóticamente.
Cómo utilizar el proyecto
Para facilitar la gestión del código, la compilación y la generación de los resultados experimentales, se
ha elaborado un fichero Makefile que describe cómo se compila el proyecto y automatiza la construcción
de los ejecutables.
Compilación y Validación
Para compilar todas las variantes del algoritmo de Avance Rápido aplicando banderas de máxima
optimización (-O3), se debe abrir una terminal en el directorio del proyecto y ejecutar:
mingw32-make -f Makefile_ar
Este comando generará tres ejecutables: test_unitarios_ar.exe, test_oraculo_ar.exe y tiempos_ar.exe.
Para comprobar que el criterio voraz diseñado es correcto y supera los casos de prueba base, se debe eje-
cutar:
.\test_unitarios_ar.exe
Generación del estudio de tiempos
Para analizar la eficiencia de la técnica voraz implementada, el flujo de trabajo es el siguiente:
1. Ejecución del medidor: Se lanza el programa cronometrador. Para tener una mejor cobertura del
dominio y cubrir varios órdenes de magnitud, este medidor evalúa tamaños de entrada utilizando
un espaciado multiplicativo. Los resultados se volcarán en el archivo datos_tiempos.csv.
.\tiempos_ar.exe
2. Generación de las gráficas (requiere Python): Se ejecuta el script encargado de procesar los
datos empíricos. Este código no solo genera los archivos de imagen (PNG) mostrando el compor-
tamiento de las distintas variantes, sino que aplica una regresión lineal para contrastar los órdenes
obtenidos en el análisis teórico con las medidas experimentales.
python regresion_AR.py
