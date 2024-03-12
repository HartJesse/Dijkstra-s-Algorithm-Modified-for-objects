/*
* Jesse Hart
* Shortest Route ALgorithm//Dijkstra's Algorithm modified
* 11/24/23
* Programming Environment Used: Windows 10 Home, Version Number: 22H2, Microsoft C/C++ compiler
*/

//Libraries
#include <set>
#include <algorithm> 
#include "dijkstra.h"
#include <limits.h> // include for INT_MAX

using namespace std;


#define INF INT_MAX
/*initialize all vertices' distances to infinity (∞),
initializes all vertices' predecessors to null, and 
enqueue all vertices into a queue of unvisited vertices.*/
std::string Dijkstra::findShortestPaths(std::vector<std::vector<MyClass>>& graph, std::string source, set<MyClass>& createdSet)
{
  //data
  int numVertices = graph[0].size();
  int sourceIndex = -1;
  std::string nearestStreet;
  std::vector<int> dist(numVertices, INF);
  std::vector<bool> visited(numVertices, false);

  /*find index value for source index to use later in graph traversal*/
  bool foundSource = false;
 
  /*use for loop to traverse each row of graph
  compare string value in traversed vertex with 
  desired starting vertex string, point at specified
  vertex when string is found*/
  for (int i = 0; i < graph.size(); ++i) {
    auto it = std::find_if(graph[i].begin(), graph[i].end(),
      [&source](const MyClass& element)
      {
        return element.strData == source;
      });

    if (it != graph[i].end()) {
      sourceIndex = std::distance(graph[i].begin(), it);
      foundSource = true;
      break;
    }
  }

  /*throw up a weird error in case something happens 
  and the program attempts to access elements outside
  the vector's range*/
  if (!foundSource) 
  {
    std::cout << "Woah I got here!" << endl; // Handle the case where the source is not found.
    nearestStreet = "StreetExample1";
    return nearestStreet;
  }
  
  /*assign the start vertex's distance with 0*/
  for (int a = 0; a < static_cast<int>(graph.size()); a++)
  {
    for (int b = 0; b < static_cast<int>(graph[a].size()); b++)
    {
      if (source == graph[a][b].strData)
      {
        dist[sourceIndex] = 0;
        sourceIndex = a;
        break;
      }
    }
  }

  /*For each adjacent vertex, compute the distance of 
  the path from the start vertex to the current vertex. 
  If path's distance is shorter than adjacent vertex's 
  current distance the adjacent vertex's current distance 
  is updated to new path, vertex's predecessor pointer is 
  pointed to the current vertex.*/


  // Dijkstra's algorithm
  for (int count = 0; count < numVertices - 1; ++count)
  {
    int u = minDistance(dist, visited);
    visited[u] = true;

    for (int v = 0; v < numVertices; ++v)
    {
      if (!visited[v] && graph[u][v].data1 && dist[u] != INT_MAX && dist[u] + graph[u][v].data1 < dist[v])
      {
        dist[v] = dist[u] + graph[u][v].data1;
      }
    }
  }


  /*use found vertex distances and look for the closest vertex to
  the source vertex to determine the next stop in the route*/
  int nearestStop = INF;
  /*iterator traverses route manifest to compare edgeweights of all vertices listed
  vertex with the smallest edge weight is saved and returned to calling function*/
  for (set<MyClass>::iterator setIt = createdSet.begin(); setIt != createdSet.end(); ++setIt) {
    int vertexIndex = -1;

    // Iterate over all rows in the graph
    for (int i = 0; i < graph.size(); ++i) 
    {
      /*Search for the vertex in the current row by comparing 
      string values held in object.*/ 
      auto vertexIt = std::find_if(graph[i].begin(), graph[i].end(),
        [setIt](const MyClass& element)
        {
          return element.strData == setIt->strData;
        });

      /*when vertex desired from createdSet is found
      check if it has the smallest edgeweight
      currently from all points in the set
      save separately if so*/
      if (vertexIt != graph[i].end()) {
        // Calculate the vertex index
        vertexIndex = std::distance(graph[i].begin(), vertexIt);

        if (vertexIndex != -1 && dist[vertexIndex] < nearestStop) {
          nearestStop = dist[vertexIndex];
          nearestStreet = setIt->strData;
        }

        // Break out of the loop since we found the vertex
        break;
      }
    }
  }
 
  return nearestStreet;
}

/*find the index of the vertex with the minimum distance value among the
vertices that have not been visited yet.*/
int Dijkstra::minDistance(const std::vector<int>& dist, const std::vector<bool>& visited) 
{
  //data
  int minDist = INF;
  int minIndex = -1;
  int v = 0;

  /*iterate over each vertex 'v' in the graph represented by the dist vector.
  Check for two conditions: 1.Ensures that the vertex has not been visited yet.
  2.Checks if the distance to the current vertex is less than or equal to the 
  current minimum distance.
  If yes to both update minDist to current distance,
  update minIndex to save vertex through to reach minDist for shortest path route*/
  for (v = 0; v < dist.size(); ++v) 
  {
    if (!visited[v] && dist[v] <= minDist) 
    {
      minDist = dist[v];
      minIndex = v;
    }
  }

  return minIndex;
}

/*print **Not used in this variation of the algorithm*/
void Dijkstra::print(const std::vector<int>& dist, int numVertices, int source, std::string sourceNew, std::vector<std::vector<MyClass>>& graphNew)
{
  //data
  int i = 0;


  std::cout << "Shortest paths from vertex " << source << " to all other vertices:\n";
  /*for (int a = 0; a < static_cast<int>(graphNew.size()) - 1; a++)
  {
    for (int b = 0; b < static_cast<int>(graphNew[a].size()) - 1; b++)
    {
      if (sourceNew != graphNew[a][b].strData)
      {
        std::cout << "Vertex " << i << ": ";

          /*print either the shortest path from the source vertex
          to the current vertex 'dist[i]' or 'No path' if
          distance is INF.
          if (dist[i] == INF)
          {
            std::cout << "No path";
          }
          else
          {
            std::cout << dist[i];
          }
        std::cout << std::endl;
      }
    }
  }*/
  for (int i = 0; i < numVertices; ++i)
  {
    //avoid showing distances for source vertex
    if (i != source) 
    {
      std::cout << "Vertex " << i << ": ";

      /*print either the shortest path from the source vertex
      to the current vertex 'dist[i]' or 'No path' if 
      distance is INF.*/
      if (dist[i] == INF) 
      {
        std::cout << "No path";
      }
      else 
      {
        std::cout << dist[i];
      }
      std::cout << std::endl;
    }
  }

  return;
}
