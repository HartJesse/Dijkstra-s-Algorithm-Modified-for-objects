/*
* Jesse Hart
* Shortest Route ALgorithm//Dijkstra's Algorithm modified
* 11/24/23
* Programming Environment Used: Windows 10 Home, Version Number: 22H2, Microsoft C/C++ compiler
*/
//Libraries
#include "MyClass.h"
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std; // Add this line

#include <cstdlib>

/*routeFill is a custom class function which creates a set of 'MyClass'
objects to use for main objective of the program*/
void MyClass::routeFill(set<MyClass>& createdSet, vector<vector<MyClass>>& map) 
{

  //data
  set<MyClass> ogSet; // Create a set of MyClass objects
  string buf = "";
  int response = -1;
  bool anotherEntry = false;
  MyClass receivedObj(0, 0, "");

  /*traverse every vertex of graph and store
  vertex data in 'ogSet', ogSet will be used
  for comparisons when referencing createdSet
  later in program functioning*/
  for (int a = 0; a < static_cast<int>(map.size()); a++)
  {
    /*using a temp set to ensure ogSet is
    populated correctly helps program avoid errors*/
    set<MyClass> tempSet;

    /*save vertex data*/
    for (int b = 0; b < static_cast<int>(map[a].size()); b++)
    {
      tempSet.insert(map[a][b]);
    }

    
    ogSet.insert(tempSet.begin(), tempSet.end()); // Insert elements into ogSet

  }

  /*ask user whether they want to manually enter addresses in*/
  cout << "Please select a method to add addresses to a new route manifest\nby inputting the corresponding number.\n1.Manual Entry\n2. Import from file\nAny other input to Quit\n\nSelection:";
  cin >> buf;
  response = atoi(buf.c_str());
  cin.ignore(1000, 10);
  cin.clear();

  if (response == 1)
  {
    manualEntry(ogSet, createdSet);
  }
  else if (response == 2)
  {
    fromFile(ogSet, createdSet);
  }
}

/*manualEntry asks the user to input a string
string is compared to every vertex 'strData'
value.

If match is found vertex is copied into createdSet
else ask user to enter a valid string input

valid input is any vertex's 'strData' value*/
void MyClass::manualEntry(const set<MyClass>& masterSet, set<MyClass>& createdSet)
{
  //data
  int stopEntries = 0;
  string street = "";
  string buf = "";
  bool badInput = false;
  MyClass temp(0, 0, "");


  do
  {
    do
    {
      street = "";
      badInput = false;
      cout << "Please input the delivery address:";
      getline(cin, street);
      cin.ignore(1000, 10);

      if (!inSet(masterSet, street))
      {
        cout << "Address is invalid, please try again." << endl << endl;
        badInput = true;
      }

    } while (badInput);

    //object used for set traversal
    MyClass searchObject(0, 0, street);
    // Use std::find_if with a lambda function to find an object with matching strData
    auto is = find_if(createdSet.begin(), createdSet.end(),
      [&searchObject](const MyClass& element)
      {
        return element.strData == searchObject.strData;
      });

    /*check if vertex has been added to createdSet already
    update 'data2' attribute if so*/
    //set<MyClass>::iterator is = createdSet.find(searchObject);
    if (is != createdSet.end())
    {
      //Update set by copying old values into new object
      temp.data1 = is->data1;
      temp.data2 = is->data2 + 1;
      temp.strData = is->strData;

      // Element found, erase and replace it
      createdSet.erase(is);
      createdSet.insert(temp);
      cout << "Route manifest updated for address: " << street << endl;

    }
    else
    {
      auto it = find_if(masterSet.begin(), masterSet.end(),
        [&searchObject](const MyClass& element)
        {
          return element.strData == searchObject.strData;
        });

      //Update set by copying old values into new object
      temp.data1 = it->data1;
      temp.data2 = it->data2;
      temp.strData = it->strData;

      //new stop added
      createdSet.insert(temp);
    }

    /*ask user to continue updating set*/
    stopEntries = 0;
    cout << "Would you like to add another entry? [Yes = 1 | No = Any other input]:";
    cin >> buf;
    stopEntries = atoi(buf.c_str());
    cin.ignore(1000, 10);
    cin.clear();

  } while (stopEntries == 1);


}

/*inSet function will check if an object is in a
set by checking string value held in object. For
program to work all strings in map must be unique*/
bool MyClass::inSet(const set<MyClass>& masterSet, string address)
{
  for (set<MyClass>::iterator it = masterSet.begin(); it != masterSet.end(); ++it)
  {
    const MyClass& element = *it;
    if (address == element.strData)
      return true;
  }
  return false;
}

/*function asks user to input desired file name-file must be in same directory
only '.txt' files are accepted
because the graph's unique ID is a vertex's 'strData' the only data necessary
to find a desired vertex and add it to createdSet 
File must formatted in specific manner to allow program to read its data
and use it as intended*/
void MyClass::fromFile(const set<MyClass>& masterSet, set<MyClass>& createdSet)
{
  string lineFromFile; //store line received from file
  ifstream fin;//read file
  string userFile = "";
  string inputFile = "manifest.txt";

  /*ask user if they have their own file to import a route manifest from*/
  cout << "Please input desired file name to import route manifest [file names must end in '.txt']:";
  getline(cin, userFile);

  //check if filename is technically valid to open
  if ((userFile.length() >= 5) && ((userFile[userFile.length() - 1] == 't') && (userFile[userFile.length() - 2] == 'x') && (userFile[userFile.length() - 3] == 't') && (userFile[userFile.length() - 4] == '.')))
    inputFile = userFile;

  //attempt to open file, bad files/filenames will cause program to terminate
  fin.open(inputFile.c_str());
  if (!fin.good()) throw "I/O error";

  /*check if string from file is found in masterSet
  if yes, add/update createdSet
  else tell user a line from file did not
  hold a valid string and was skipped
  to avoid errors*/
  while (!fin.eof())
  {
    getline(fin, lineFromFile);

    if (inSet(masterSet, lineFromFile))
    {
      if (inSet(createdSet, lineFromFile))
      {
        MyClass searchObject(0, 0, lineFromFile);
        auto it = find_if(createdSet.begin(), createdSet.end(),
          [&searchObject](const MyClass& element)
          {
            return element.strData == searchObject.strData;
          });
        searchObject.data1 = it->data1;
        searchObject.data2 = it->data2 + 1;
        searchObject.strData = it->strData;

        // Element found, erase and replace it
        createdSet.erase(it);
        createdSet.insert(searchObject);
        cout << "Route manifest updated for address: " << lineFromFile << endl;
      }
      else
      {
        MyClass searchObject(0, 0, lineFromFile);
        auto it = find_if(masterSet.begin(), masterSet.end(),
          [&searchObject](const MyClass& element)
          {
            return element.strData == searchObject.strData;
          });

        //Update set by copying old values into new object
        searchObject.data1 = it->data1;
        searchObject.data2 = it->data2;
        searchObject.strData = it->strData;

        //new stop added
        createdSet.insert(searchObject);
      }

    }
    else
    {
      cout << "Address: '" << lineFromFile << "' from file is not a valid address.\nPlease review entries in file to ensure route accuracy." << endl;
    }
  }
  fin.close();
}