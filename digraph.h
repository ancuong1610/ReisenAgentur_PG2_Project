//		Klasse "Digraph" Deklarationen
#ifndef DIGRAPH_H
#define DIGRAPH_H
#include <iostream>
#include <iomanip>
#include <string>
#include <cfloat>  // wg. MAXFLOAT
using namespace std;

const double noArc = FLT_MAX;
const double weightBackEdge = -1.0;
const double weightCrossEdge = -2.0;
const double weightForwardEdge = -3.0;

enum color_node {
    WHITE = 0, GREY = 1, BLACK = 2
};

template <class TV, int maxNodes>
class Digraph {
private:

    class Vertex {
    public:
        Vertex() { // Konstruktor
            indegree = outdegree = ord = 0;
            living = false;
            color = WHITE;
            start = end = 0;
            predecessor = -1;
        }
        TV value; // Daten des Knotens
        int indegree; // Eingangsgrad
        int outdegree; // Ausgangsgrad
        int ord; // Ordnungszahl des Knotens
        bool living; // Knoten existiert
        color_node color; //Farbcodierung für Bearbeitungszustand
        int start, end; //Start und Ende der Bearbeitungszeit für DFS
        int predecessor; //Für aufspannenden Baum
    };
    int numVertices; // Anzahl der Knoten eines Digraphen
    int numArcs; // Anzahl der Kanten eines Digraphen
    Vertex vertices[maxNodes]; // repraesentiert Knoten des Digraphen
    double arcs[maxNodes][maxNodes]; // repraesentiert bewertete Kanten des Graphen
public:// Operationen auf dem Graphen
    Digraph(); // Graphen generieren
    ~Digraph(); // Graphen freigeben
    void insertVertex(int n, TV m); // fuegt neuen Knoten n mit Markierung m ein
    void deleteVertex(int n); // entfernt Knoten n
    TV getVertexValue(int n); // gibt Wert des Knoten n zurueck
    void setVertexValue(int n, TV m); // Aendert Wert des Knoten n
    int firstVertex(); // Erster Knoten des Graphen
    int nextVertex(int n); // nächster Knoten nach n (-1 wenn keiner existiert)
    void insertArc(int v, int w, double weight); // fgt neue Kante (v,w) mit Gewicht weight ein
    void insertArc(int v, int w); // fgt neue Kante (v,w) mit Gewicht 0 ein
    void deleteArc(int v, int w); // loescht Kante (v,w)
    int firstArc(int v); // Erster Kante des Knoten v des Graphen
    int nextArc(int v, int n); // naechste Kante des Knotens v nach n
    // (-1 wenn keiner existiert)
    bool isVisited(int n); // true, wenn Knoten n besucht, sonst false
    void setArcWeight(int v, int w, double weight); //aendert Kantengewicht
    bool isArc(int v, int w); // existiert Kante (v,w)?
    double getArc(int v, int w); // gibt Kantenbewertung  von (v,w) zurck
    int getNumVertices(); // Anzahl der Knoten
    int getMaxNodes(); // Max. Anzahl der Knoten
    int getNumArcs(); // Anzahl der Kanten
    int getIndegree(int n); // liefert Eingangsgrad eines Knotens
    int getOutdegree(int n); // liefert Ausgangsgrad eines Knotens
    int getColor(int n); //liefert Farbe des Knotens
    void setColor(int n, color_node color); // Knoten n als nicht besucht, besucht oder abgeschlossen markieren
    int getStart(int n); //liefert Startzeitpunkt
    void setStart(int n, int time); //Startzeitpunkt der Bearbeitung für DFS setzen
    int getEnd(int n); //liefert Endzeitpunkt
    void setEnd(int n, int time); //Endzeitpunkt der Bearbeitung für DFS setzen
    int getOrd(int v); // Ordnungsnummer des Knotens v liefern
    int getPredecessor(int n); //liefert Vorgaengerknoten
    void setPredecessor(int n, int pre); //Vorgängerknoten setzen
    void printVertex(int n); // Ausgabe des Knotens n eines Graphen
    void printVertices(); // Ausgabe aller Knotens  eines Graphen
    void printAdjMatrix(); // Adjazenzmatrix ausgeben
    void deleteDigraph(); // alle Knoten und Kanten loeschen
};

template <class TV, int maxNodes>
Digraph<TV, maxNodes>::Digraph() {
    numVertices = numArcs = 0;
    for (int i = 0; i < maxNodes; i++)
        for (int j = 0; j < maxNodes; j++)
            arcs[i][j] = noArc;
}

template <class TV, int maxNodes>
Digraph<TV, maxNodes>::~Digraph() {
    ;
}

template <class TV, int maxNodes>
void Digraph<TV, maxNodes>::insertVertex(int n, TV m) {
    if (n >= 0 && n < maxNodes) {
        vertices[n].living = true;
        vertices[n].value = m;
    }
}

template <class TV, int maxNodes>
int Digraph<TV, maxNodes>::firstVertex() {
    for (int i = 0; i < maxNodes; i++)
        if (vertices[i].living == true)
            return i;
    return -1;
}

template <class TV, int maxNodes>
int Digraph<TV, maxNodes>::nextVertex(int n) { // nächster Knoten nach n (-1 wenn n der letzte ist)
    if (n < 0 || n > maxNodes - 2) return -1;
    for (int i = n + 1; i < maxNodes; i++)
        if (vertices[i].living == true)
            return i;
    return -1;
}

template <class TV, int maxNodes>
int Digraph<TV, maxNodes>::firstArc(int v) {
    if (vertices[v].living == true)
        for (int i = 0; i < maxNodes; i++)
            if (isArc(v, i))
                return i;
    return -1;
}

template <class TV, int maxNodes>
int Digraph<TV, maxNodes>::nextArc(int v, int n) {
    if (vertices[v].living == true)
        for (int i = n + 1; i < maxNodes; i++)
            if (isArc(v, i))
                return i;
    return -1;
}

template <class TV, int maxNodes>
void Digraph<TV, maxNodes>::deleteVertex(int n) {
    if (n >= 0 && n < maxNodes) {
        vertices[n].living = false;
        vertices[n].color = WHITE;
        vertices[n].value = vertices[n].ord = vertices[n].start =
                vertices[n].end = vertices[n].indegree =
                vertices[n].outdegree = vertices[n].predecessor = 0;
    }
    for (int i = 0; i < maxNodes; i++) {
        //  Vorhandene Kanten zum Knoten löschen
        arcs[i][n] = noArc;
        arcs[n][i] = noArc;
    }
}

template <class TV, int maxNodes>
TV Digraph<TV, maxNodes>::getVertexValue(int n) {
    if (n >= 0 && n < maxNodes && vertices[n].living) {
        return vertices[n].value;
    }
}

template <class TV, int maxNodes>
int Digraph<TV, maxNodes>::getOrd(int n) {
    if (n >= 0 && n < maxNodes && vertices[n].living) {
        return vertices[n].ord;
    }
    return -1;
}

template <class TV, int maxNodes>
int Digraph<TV, maxNodes>::getPredecessor(int n) {
    return vertices[n].predecessor;
}

template <class TV, int maxNodes>
void Digraph<TV, maxNodes>::setPredecessor(int n, int pre) {
    vertices[n].predecessor = pre;
}

template <class TV, int maxNodes>
void Digraph<TV, maxNodes>::setVertexValue(int n, TV m) {
    if (n >= 0 && n < maxNodes && vertices[n].living) {
        vertices[n].value = m;
    }
}

template <class TV, int maxNodes>
int Digraph<TV, maxNodes>::getMaxNodes() {
    return maxNodes;
}

template <class TV, int maxNodes>
int Digraph<TV, maxNodes>::getColor(int n) {
    return vertices[n].color;
}

template <class TV, int maxNodes>
void Digraph<TV, maxNodes>::setColor(int n, color_node color) {
    if (n >= 0 && n < maxNodes && vertices[n].living)
        vertices[n].color = color;
}

template <class TV, int maxNodes>
int Digraph<TV, maxNodes>::getStart(int n) {
    return vertices[n].start;
}

template <class TV, int maxNodes>
void Digraph<TV, maxNodes>::setStart(int n, int time) {
    if (n >= 0 && n < maxNodes && vertices[n].living)
        vertices[n].start = time;
}

template <class TV, int maxNodes>
int Digraph<TV, maxNodes>::getEnd(int n) {
    return vertices[n].end;
}

template <class TV, int maxNodes>
void Digraph<TV, maxNodes>::setEnd(int n, int time) {
    if (n >= 0 && n < maxNodes && vertices[n].living)
        vertices[n].end = time;
}

template <class TV, int maxNodes>
bool Digraph<TV, maxNodes>::isVisited(int n) {
    if (n >= 0 && n < maxNodes && vertices[n].living) {
        return vertices[n].color;
    }
    return false;
}

template <class TV, int maxNodes>
void Digraph<TV, maxNodes>::insertArc(int v, int w, double weight) {
    if (v >= 0 && v < maxNodes && w >= 0 && w < maxNodes && vertices[v].living && vertices[w].living && weight >= 0) {
        arcs[v][w] = weight;
        vertices[v].outdegree++;
        vertices[v].ord++;
        vertices[w].indegree++;
        vertices[w].ord++;
    }
}

template <class TV, int maxNodes>
void Digraph<TV, maxNodes>::insertArc(int v, int w) {
    insertArc(v, w, 0);
}

template <class TV, int maxNodes>
void Digraph<TV, maxNodes>::deleteArc(int v, int w) {
    if (v >= 0 && v < maxNodes && w >= 0 && w < maxNodes && vertices[v].living && vertices[w].living) {
        arcs[v][w] = noArc;
        vertices[v].outdegree--;
        vertices[v].ord--;
        vertices[w].indegree--;
        vertices[w].ord--;
    }
}

template <class TV, int maxNodes>
void Digraph<TV, maxNodes>::setArcWeight(int v, int w, double weight) {
    arcs[v][w] = weight;
}

template <class TV, int maxNodes>
bool Digraph<TV, maxNodes>::isArc(int v, int w) {
    if (v >= 0 && v < maxNodes && w >= 0 && w < maxNodes)
        return arcs[v][w] != noArc;
    return false;
}

template <class TV, int maxNodes>
double Digraph<TV, maxNodes>::getArc(int v, int w) {
    if (isArc(v, w))
        return arcs[v][w];
    return noArc;
}

template <class TV, int maxNodes>
int Digraph<TV, maxNodes>::getNumArcs() {
    return numArcs;
}

template <class TV, int maxNodes>
int Digraph<TV, maxNodes>::getNumVertices() {
    return numVertices;
}

template <class TV, int maxNodes>
int Digraph<TV, maxNodes>::getIndegree(int n) {
    return vertices[n].indegree;
}

template <class TV, int maxNodes>
int Digraph<TV, maxNodes>::getOutdegree(int n) {
    return vertices[n].outdegree;
}

template <class TV, int maxNodes>
void Digraph<TV, maxNodes>::printVertices() {
    cout << "Knoten:" << endl;
    for (int i = 0; i < maxNodes; i++) {
        printVertex(i);
    }
}

template <class TV, int maxNodes>
void Digraph<TV, maxNodes>::printVertex(int n) {
    string color;
    if (vertices[n].living) {
        if (getColor(n) == 0)
            color = "WHITE";
        else if (getColor(n) == 1)
            color = "GREY";
        else
            color = "BLACK";
        cout << "Nummer: " << n << " Wert: " << getVertexValue(n) << " Ordnung: " << getOrd(n)
                << " Farbe: " << setw(6) << color << " Start: " << getStart(n) << " Ende: " << getEnd(n)
                << " Vorgaenger: " << getPredecessor(n) << endl;
    }
}

template <class TV, int maxNodes>
void Digraph<TV, maxNodes>::printAdjMatrix() {
    cout << "Adjazenz Matrix:" << endl;
    cout << "    ";
    for (int i = 1; i < maxNodes; i++)
        cout << setw(5) << i << " ";
    cout << "\n  --";
    for (int i = 1; i < maxNodes; i++)
        cout << "------";
    cout << endl;
    for (int i = 1; i < maxNodes; i++) {
        cout << "  " << i << "|";
        for (int j = 1; j < maxNodes; j++) {
            if (isArc(i, j))
                cout << setw(5) << getArc(i, j) << " ";
            else
                cout << setw(5) << "-" << " ";
        }
        cout << endl;
    }
}

template <class TV, int maxNodes>
void Digraph<TV, maxNodes>::deleteDigraph() {
    for (int i = 0; i < maxNodes; i++)
        deleteVertex(i);
    for (int i = 0; i < maxNodes; i++)
        for (int j = 0; j < maxNodes; j++)
            deleteArc(i, j);
}
#endif
