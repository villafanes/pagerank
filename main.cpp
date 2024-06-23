#include <iostream>
#include <vector>
#include <algorithm>
#include "rank.h"

int main() {
    /// if a webpage points to, it should still print with a pagerank of 0
    AdjacencyList list;
    int num_lines, pow_iter;
    string from, to;
    cin >> num_lines;
    cin >> pow_iter;

    // reads in input values
    for (int i = 0; i < num_lines; i++){
        cin >> from >> to;
        // creates from->(to, r(t)) graph
        list.pushPage(from, to);
        // creates from -> (to, 1/out-degree) graph
        list.pushRanks(from, to);

    }

    // sets initial r(t) value, r(1) to 1/|V| for all edges to be updated for each power iteration
    list.setRates();
    list.setDegrees();

    // returns the pages and r(1) - no power iterations necessary
    if (pow_iter == 1){
        list.noIterations();
    }

    // while there are still iterations to be done
    while (pow_iter > 1){
        list.setPageRanks();
        list.setOutputs();
        // no need to transfer the new ranks into pages if there's just 1 iteration
        if (pow_iter > 2){
            list.updateRates();
            list.clearPageRanks();
            list.clearOutputs();
        }
        pow_iter--;
    }
    list.getOutputs();
}

