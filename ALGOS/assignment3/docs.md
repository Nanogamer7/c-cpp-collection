# Docs

### Aufwand

- 3h für ein funktionierendes Programm (Nicole, Beni)
- 10h für Optimierungen die überhaupt nicht notwendig gewesen währen (Beni)
- 1.5h fürs Einlesen und hinzufügen eines weiteren Algorithmus (Markus)

### Laufzeitanalyse

V für Anzahl Vertices, i.e. Stationen
E für Anzahl Edges, i.e. Verbindungen
Graph erstellen `O(V,E) = V + E`
Dijkstra `O(V,E) = E + V * log(V)` *für eine Implementierung mittels Fibonacci heap min-priority queue, hängt von implementierung der STL priority queue ab*
Dijkstra `O(V,E) = E * log(V) + V * log(V)` *mit binomial heap min-priority queue*
BFS `O(V,E)= V + E`
Für beide Algorithmen gilt außerdem eine konstante Runtime um die erste Node zu finden, da STL unordered map verwendet wird.