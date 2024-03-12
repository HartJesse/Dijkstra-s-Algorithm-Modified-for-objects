/*
* Jesse Hart
* Shortest Route ALgorithm//Dijkstra's Algorith modified 
* 11/24/23
* Programming Environment Used: Windows 10 Home, Version Number: 22H2, Microsoft C/C++ compiler
*/
#pragma once
#ifndef DIJKSTRA_H
#define DIJKSTRA_H

//Libraries
#include <iostream>
#include <limits.h>
#include <set>
#include <vector>
#include "MyClass.h"

using namespace std;

/*Dijkstra class holds all algorithm functions for finding the shortest path in a graph
very few modifications are made to a standard 'findShortestPaths' functions for Dijkstra's
shortest path algorithm. 

Function is passed a graph of objects for reference rather than a graph of ints
  -It is also passed a string value to use as a reference for the graph to locate vertices
set data structure of 'MyClass' objects passed is used to help return a string value
back to the calling function

-print function is leftover from original implementation of algorithm but is not used*/
class Dijkstra 
{
  public:
     std::string findShortestPaths(std::vector<std::vector<MyClass>>& graph, std::string source, set<MyClass>& createdSet);

  private:
    int minDistance(const std::vector<int>& dist, const std::vector<bool>& visited);
    void print(const std::vector<int>& dist, int numVertices, int source, std::string sourceNew, std::vector<std::vector<MyClass>>& graphNew);
};

#endif // DIJKSTRA_H
