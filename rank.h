
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <iterator>
#include <iomanip>
using namespace std;

class AdjacencyList {
private:
    map<string, vector<pair<string, double> > > pages; // main adjacency list
    map<string, vector<pair<string, double> > > web_ranks; // adjacency list that holds each edge's out-ranks
    map<string, double> outputs; // container holding the results of the power iterations
    multiset<pair<string, double> > page_ranks; // pages and their ranks

public:
    void setRates(); // assigns r(0) : 1/|V| to each edge in the map
    void setDegrees(); // assigns 1/out-degree each edge in map
    void pushPage(string from, string to); // adds new entries to the pages map
    void pushRanks(string from, string to); // adds new entries to the web ranks map
    void setPageRanks(); // executes list multiplication between web ranks and pages, then pushes into new container
    void setOutputs(); // adds up the products to get the final page ranks
    void updateRates(); // assigns page_rank values to the pages list for next power iteration
    void clearPageRanks(); // clears page_ranks for the next iteration's sums
    void clearOutputs(); // prints pages and their ranks
    void getOutputs(); // prints pages and their ranks
    void noIterations();
    void tester();
};

