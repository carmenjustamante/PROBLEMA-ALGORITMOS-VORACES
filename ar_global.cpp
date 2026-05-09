#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Estructura para representar una posible asignación de una tarea a un trabajador
struct Candidato {
    int trabajador, tarea, beneficio;

    // Sobrecarga del operador '>' para ordenar los candidatos
    // Criterio principal: mayor beneficio 
    // Criterios secundarios (para desempate): menor índice de trabajador y luego menor índice de tarea
    bool operator>(const Candidato& otro) const {
        if (beneficio != otro.beneficio) return beneficio > otro.beneficio;
        if (trabajador != otro.trabajador) return trabajador < otro.trabajador;
        return tarea < otro.tarea;
    }
};

void resolver() {
    int nw, nt; // nw: número de trabajadores, nt: número de tareas
    if (!(cin >> nw >> nt)) return;

    vector<Candidato> C;
    // Lectura de la matriz de beneficios
    for (int i = 0; i < nw; ++i) {
        for (int j = 0; j < nt; ++j) {
            int b; cin >> b;
            // Solo consideramos asignaciones con beneficio positivo
            if (b > 0) C.push_back({i, j, b});
        }
    }

    // Lectura de la capacidad de cada trabajador (cuántas tareas puede realizar)
    vector<int> cap(nw);
    for (int i = 0; i < nw; ++i) cin >> cap[i];

    // Ordenamos todos los posibles candidatos de mayor a menor beneficio
    // Esto es el corazón del algoritmo voraz
    sort(C.begin(), C.end(), greater<Candidato>());

    vector<int> sol(nt, -1);      // Almacena qué trabajador tiene asignada cada tarea (-1 = ninguna)
    long long beneficioTotal = 0; // Acumulador del beneficio total
    int asignadas = 0;            // Contador de tareas ya asignadas

    // Recorremos los candidatos ya ordenados por beneficio
    for (const auto& c : C) {
        // Si la tarea no ha sido asignada Y el trabajador aún tiene capacidad disponible
        if (sol[c.tarea] == -1 && cap[c.trabajador] > 0) {
            sol[c.tarea] = c.trabajador; // Asignamos la tarea
            cap[c.trabajador]--;         // Reducimos la capacidad del trabajador
            beneficioTotal += c.beneficio;
            asignadas++;
            
            // Si ya hemos asignado todas las tareas, podemos dejar de buscar
            if (asignadas == nt) break;
        }
    }

    // Si no se pudieron asignar todas las tareas, el beneficio total suele marcarse como 0 (o según requiera el problema)
    if (asignadas < nt) beneficioTotal = 0;

    // Salida de resultados
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