#include <iostream>
#include "digraph.h"
#include <queue>	// wg. Bfs
using namespace std;

// Hilfsroutinen

template <class TV, int maxNodes>
void setAllColor(Digraph<TV, maxNodes> &g, color_node color) { // Alle Knoten als besucht bzw unbesucht markieren
    int v = g.firstVertex();
    while (v != -1) {
        g.setColor(v, color);
        v = g.nextVertex(v);
    }
}

template <class TV, int maxNodes>
void visit(Digraph<TV, maxNodes> &g, int n) { // Knoten n besuchen
    g.printVertex(n);
}

// Tiefensuche
template <class TV, int maxNodes>
int Dfs(Digraph<TV, maxNodes> &g, int v, int time) {// Tiefensuche ab Knoten v
    if (!g.isVisited(v)) {
        g.setColor(v, GREY); // als besucht markieren
        g.setStart(v, time); // Startzeitpunkt für Knoten setzen
        visit(g, v); // v besuchen
        int w = g.firstArc(v);
        while (w != -1) { // alle Nachfolger von v bearbeiten
            if (!g.isVisited(w)) { // w noch nicht besucht
                time += 1;
                time = Dfs(g, w, time); // Tiefensuche für w starten
            } else { //Kantenmarkierungen setzen
                if (g.getColor(w) == GREY)
                    g.setArcWeight(v, w, weightBackEdge); //Rückwärtskante
                else if (g.getColor(w) == BLACK) {
                    if (g.getStart(v) < g.getEnd(w))
                        g.setArcWeight(v, w, weightForwardEdge); // Forwardkante
                    else
                        g.setArcWeight(v, w, weightCrossEdge); //Crosskante
                }
            }
            w = g.nextArc(v, w);
        }
        time += 1;
        g.setColor(v, BLACK);
        g.setEnd(v, time);
        visit(g, v);
    }
    return time;
}

template <class TV, int maxNodes>
void DepthFirstSearch(Digraph<TV, maxNodes> &g) { // Tiefensuche
    int time = 1;
    setAllColor(g, WHITE); // Alle Knoten als unbesucht markieren
    int v = g.firstVertex();
    while (v != -1) {
        if (!g.isVisited(v)) { // v noch nicht besucht
            time = Dfs(g, v, time); // Tiefensuche fuer v starten
            time += 1;
        }
        v = g.nextVertex(v);
    }
}

//// Breitensuche
//template <class TV, int maxNodes>
//void Bfs(Digraph<TV, maxNodes> &g, int v) { // Breitensuche ab Knoten v
//    queue<int> q; // Schlange zum Merken der besuchten Knoten
//    if (!g.isVisited(v)) {
//        g.setColor(v, GREY); // als besucht markieren
//        visit(g, v); // v besuchen
//        q.push(v); // Startknoten in Schlange einfuegen
//        while (!q.empty()) { // Solange bis Schlange leer
//            v = q.front(); // naechsten besuchten Knoten aus Schlange lesen
//            q.pop(); // und aus Schlange entfernen
//            int w = g.firstArc(v); // erste von v ausgehende Kante
//            while (w != -1) { // für alle Nachfolger von v
//                if (!g.isVisited(w)) { // w noch nicht besucht
//                    g.setColor(w, GREY); // als besucht markieren
//                    g.setPredecessor(w, v);
//                    visit(g, w); // w besuchen
//                    q.push(w); // w in Schlange ablegen
//                }
//                w = g.nextArc(v, w); // naechste Kante (v,w)
//            }
//            g.setColor(v, BLACK);
//            visit(g, v);
//        }
//    }
//}

//template <class TV, int maxNodes>
//void BreadthFirstSearch(Digraph<TV, maxNodes> &g) { // Breitensuche
//    setAllColor(g, WHITE); // Alle Knoten als unbesucht markieren
//    int v = g.firstVertex();
//    while (v != -1) {
//        if (!g.isVisited(v)) // v noch nicht besucht
//            Bfs(g, v); // Breitensuche fuer v starten
//        break;//meins
//    }
//}
