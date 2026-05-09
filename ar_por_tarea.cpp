#include <iostream>
#include <vector>

using namespace std;

void resolver() {
    int nw, nt; // nw: número de trabajadores, nt: número de tareas
    if (!(cin >> nw >> nt)) return;

    // Lectura de la matriz de beneficios: matriz[trabajador][tarea]
    vector<vector<int>> matriz(nw, vector<int>(nt));
    for (int i = 0; i < nw; ++i)
        for (int j = 0; j < nt; ++j) cin >> matriz[i][j];

    // Capacidad de cada trabajador (cuántas tareas puede realizar en total)
    vector<int> cap(nw);
    for (int i = 0; i < nw; ++i) cin >> cap[i];

    vector<int> sol(nt, -1);      // sol[j] guardará qué trabajador hace la tarea j
    long long beneficioTotal = 0; // Suma acumulada de beneficios
    int asignadas = 0;            // Contador de tareas completadas

    // ESTRATEGIA VORAZ: "Candidatos por nivel"
    // Iteramos sobre cada tarea (j) y decidimos en el momento quién es el mejor para ella.
    for (int j = 0; j < nt; ++j) {
        int mejorW = -1; // Índice del mejor trabajador encontrado para la tarea j
        int maxB = -1;   // Beneficio máximo encontrado para la tarea j

        // Buscamos entre todos los trabajadores (i) para la tarea actual (j)
        for (int i = 0; i < nw; ++i) {
            // Condición: que el trabajador tenga capacidad, que el beneficio sea mejor 
            // que el encontrado antes y que sea un beneficio positivo.
            if (cap[i] > 0 && matriz[i][j] > maxB && matriz[i][j] > 0) {
                maxB = matriz[i][j];
                mejorW = i;
            }
        }

        // Si encontramos un trabajador válido para esta tarea
        if (mejorW != -1) {
            sol[j] = mejorW;        // Se le asigna la tarea
            cap[mejorW]--;          // Se consume una unidad de su capacidad
            beneficioTotal += maxB; // Sumamos el beneficio
            asignadas++;
        }
    }

    // Si no se han podido asignar todas las tareas, el beneficio se invalida (según lógica del problema)
    if (asignadas < nt) beneficioTotal = 0;

    // Impresión de resultados
    cout << beneficioTotal << endl;
    for (int i = 0; i < nt; ++i) {
        cout << sol[i] << (i == nt - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
    int t; // Número de casos de prueba
    cin >> t;
    while (t--) {
        resolver();
    }
    return 0;
}