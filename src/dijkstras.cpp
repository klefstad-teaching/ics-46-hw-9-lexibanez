#include "dijkstras.h"
#include <algorithm>

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    vector<int> distances(G.numVertices, INF);
    distances[source] = 0;
    previous.resize(G.numVertices, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        for (const auto& e : G[u])
        {
            int v = e.dst;
            int w = e.weight;
            if (distances[v] > distances[u] + w)
            {
                distances[v] = distances[u] + w;
                previous[v] = u;
                pq.push({distances[v], v});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination)
{
    vector<int> path;
    for (int v = destination; v != -1; v = previous[v])
    {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total)
{
    cout << "Shortest path: ";
    for (int i = 0; i < v.size(); ++i)
    {
        cout << v[i];
        if (i < v.size() - 1)
        {
            cout << " -> ";
        }
    }
    cout << endl;
    cout << "Total weight = " << total << endl;
}
