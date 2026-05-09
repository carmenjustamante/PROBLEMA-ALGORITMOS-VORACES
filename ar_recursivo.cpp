#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Estructura para almacenar una posible asignación
struct Candidato {
    int trabajador, tarea, beneficio;
};

// Función de comparación para el ordenamiento (Greedy)
// Ordena de mayor a menor beneficio, y en caso de empate, por índice de trabajador
bool comparar(const Candidato& a, const Candidato& b) {
    if (a.beneficio != b.beneficio) return a.beneficio > b.beneficio;
    return a.trabajador < b.trabajador;
}

/**
 * Esquema recursivo de "avance rápido" para el algoritmo voraz.
 * Sustituye al bucle for tradicional recorriendo la lista de candidatos uno a uno.
 */
void vorazRecursivo(int idx, const vector<Candidato>& C, vector<int>& sol, vector<int>& cap, int& asignadas, long long& total, int nt) {
    // CASO BASE: Si hemos recorrido todos los candidatos o ya asignamos todas las tareas
    if (idx == (int)C.size() || asignadas == nt) return;

    const Candidato& c = C[idx];
    
    // Si la tarea está libre y el trabajador tiene capacidad (lógica voraz)
    if (sol[c.tarea] == -1 && cap[c.trabajador] > 0) {
        sol[c.tarea] = c.trabajador; // Asignar
        cap[c.trabajador]--;         // Reducir capacidad
        total += c.beneficio;        // Acumular beneficio
        asignadas++;                 // Incrementar contador de éxito
    }
    
    // LLAMADA RECURSIVA: Pasa al siguiente candidato de la lista (idx + 1)
    vorazRecursivo(idx + 1, C, sol, cap, asignadas, total, nt);
}

void resolver() {
    int nw, nt;
    if (!(cin >> nw >> nt)) return;

    vector<Candidato> C;
    // Carga de la matriz de beneficios en una lista de candidatos
    for (int i = 0; i < nw; ++i) {
        for (int j = 0; j < nt; ++j) {
            int b; cin >> b;
            if (b > 0) C.push_back({i, j, b});
        }
    }

    // Capacidad de cada trabajador
    vector<int> cap(nw);
    for (int i = 0; i < nw; ++i) cin >> cap[i];

    // Ordenamos los candidatos según la estrategia voraz (mayor beneficio primero)
    sort(C.begin(), C.end(), comparar);

    vector<int> sol(nt, -1);
    long long beneficioTotal = 0;
    int asignadas = 0;

    // Llamada inicial a la función recursiva empezando por el primer candidato (índice 0)
    vorazRecursivo(0, C, sol, cap, asignadas, beneficioTotal, nt);

    // Si no se cubrieron todas las tareas, el beneficio se considera 0
    if (asignadas < nt) beneficioTotal = 0;

    // Salida por pantalla
    cout << beneficioTotal << endl;
    for (int i = 0; i < nt; ++i) {
        cout << sol[i] << (i == nt - 1 ? "" : " ");
    }
    cout << endl;
}

int main() {
    int t;
    cin >> t;
    while (t--) resolver();
    return 0;
}