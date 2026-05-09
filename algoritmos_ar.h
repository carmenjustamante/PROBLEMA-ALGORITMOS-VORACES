#ifndef ALGORITMOS_AR_H
#define ALGORITMOS_AR_H

#include <vector>
#include <utility>

using namespace std;

// Estructura para representar a los candidatos (par trabajador-tarea)
struct Candidato {
    int trabajador, tarea, beneficio;
    
    /**
     * Sobrecarga del operador < para std::sort.
     * Para un algoritmo voraz global, queremos que los mejores beneficios
     * aparezcan al principio del contenedor tras ordenar.
     */
    bool operator<(const Candidato& otro) const {
        // Ordenamos de mayor a menor beneficio
        if (beneficio != otro.beneficio) {
            return beneficio > otro.beneficio; 
        }
        // Criterios secundarios para desempatar (estabilidad)
        if (trabajador != otro.trabajador) return trabajador < otro.trabajador;
        return tarea < otro.tarea;
    }
};

// Implementación 1: Voraz global (iterativo)
// Revisa todos los beneficios posibles de la tabla de mayor a menor.
pair<long long, vector<int>> voraz_global(int nw, int nt, const vector<vector<int>>& matriz, vector<int> cap);

// Implementación 2: Voraz global (recursivo)
// Misma lógica que el anterior pero con inmersión recursiva.
pair<long long, vector<int>> voraz_recursivo(int nw, int nt, const vector<vector<int>>& matriz, vector<int> cap);

// Implementación 3: Voraz por tarea
// Para cada tarea, elige el mejor trabajador disponible en ese momento.
pair<long long, vector<int>> voraz_por_tarea(int nw, int nt, const vector<vector<int>>& matriz, vector<int> cap);

#endif