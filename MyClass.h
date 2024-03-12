/*
* Jesse Hart
* Shortest Route ALgorithm//Dijkstra's Algorithm modified
* 11/24/23
* Programming Environment Used: Windows 10 Home, Version Number: 22H2, Microsoft C/C++ compiler
*/
// MyClass.h

//Libraries
#pragma once
#include <set>
#include <string>
#include <vector>

using namespace std;

/*MyClass handles all information relating to each vertex on graph including:
attributes of MyClass objects, constructors, overload operators, class functions*/
class MyClass 
{
  public:
    int data1; //holds edge weight value for a vertex
    int data2; //for program readability, saves number of instances a vertex is requested to be visited when building userSet in 'buildSet.cpp'
    std::string strData; //unique value to differentiate vertices to ease searching for a vertex

    //constructor
    MyClass(int value1, int value2, const std::string& str)
      : data1(value1), data2(value2), strData(str) {}

    MyClass() : data1(0), data2(0), strData("") {} // Default constructor

    //overload operator helps ensure values are properly initialized when an object is created
    bool operator<(const MyClass& other) const 
    {
      if (data1 != other.data1) 
      {
        return data1 < other.data1;
      }
      if (data2 != other.data2) 
      {
        return data2 < other.data2;
      }
      return strData < other.strData;
    }

    //function to create route manifest
    void routeFill(set<MyClass>& createdSet, vector<vector<MyClass>>& map);
  
    /*private functions are extensions of routefill function just separated for programmer readability*/
  private:
    void manualEntry(const set<MyClass>& masterSet, set<MyClass>& createdSet);
    void fromFile(const set<MyClass>& masterSet, set<MyClass>& createdSet);
    bool inSet(const set<MyClass>& masterSet, string address);


};
