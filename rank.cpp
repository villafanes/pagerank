#include "rank.h"


// pages - sets all edge double values to 1/|V| to begin with at r(1)
void AdjacencyList::setRates(){
    double r = 1.0 / pages.size();
    for (auto& page: pages){
        if (!page.second.empty()) {
            for (auto& pair: page.second) {
                pair.second = r;
            }
        }
    }
}

// web_ranks - sets all edge double values to 1/(corresponding) out-degree
// remains untouched - constant values for power iterations
void AdjacencyList::setDegrees(){
    double out_degree;
    for (auto& entry: web_ranks){
        vector<pair<string, double> >& to_pages = entry.second;
        if (!to_pages.empty()){
            out_degree = 1.0 / to_pages.size();
            for (auto& pair: entry.second){
                pair.second = out_degree;
            }
        }
    }
}

//  adds edges to pages map
void AdjacencyList::pushPage(string from, string to){
    pages[from].push_back(make_pair(to, 1));
    if (pages.find(to) == pages.end()){
        // empty vector in case a url is pointed to, but points to nothing
        pages[to] = {};
        // if this raises issues, try pages[to] = {}
    }
}

// adds edges to web ranks map
void AdjacencyList::pushRanks(string from, string to) {
    // constant map of web ranks for power iterations
    web_ranks[from].push_back(make_pair(to, 1));
    if (web_ranks.find(to) == web_ranks.end()){
        // empty pair in case a url is pointed to, but points to nothing
        web_ranks[to] = {};
    }
}

void AdjacencyList::noIterations(){
    for (auto& page : pages){
        cout << page.first << " " << fixed << setprecision(2) << 1.0/pages.size() << endl;
    }
}

void AdjacencyList::setPageRanks() {
    string pagename;
    double rate;
    double factor;
    double product;

    for (auto& page: pages) { // each entry in map
        for (auto &pair: page.second) { // each pair in each vector
            pagename = pair.first; // "to" page name
            rate = pair.second; // "to" page web rank
            for (auto &rank: web_ranks) {
                for (auto &num: rank.second) {
                    factor = num.second;
                    product = rate * factor;
                    if (pagename == num.first && page.first == rank.first){
                        page_ranks.insert(make_pair(pagename, product));
                    }
                }
            }
        }
    }
}

void AdjacencyList::setOutputs(){
    string pagename;
    // pushes "to" pages into output value map
    for (auto& page: pages){
        pagename = page.first;
        if (outputs.find(pagename) == outputs.end()){
            outputs[pagename] = 0;
        }
    }
    // calculates sum of pagerank for each page
    for (auto& page: page_ranks){
        for (auto& sum : outputs){
            if (page.first == sum.first){
                sum.second += page.second;
            }
        }
    }

}

void AdjacencyList::clearPageRanks() {
    page_ranks.clear();
}

void AdjacencyList::clearOutputs() {
    outputs.clear();
}

void AdjacencyList::updateRates() {
    for (auto& ranking : outputs) { // final ranking sums of power iteration
        string output_page = ranking.first; // page in 'outputs'
        double output_rank = ranking.second; // page's rank

        for (auto& page : pages) { // from and to pages in 'pages'
            string from_page = page.first; // from page name
            vector<pair<string, double>>& to_pages = page.second; // pages the from page is linked to

            for (auto& to_page : to_pages) { // each "to" page pair
                string pagename = to_page.first; // "to" page name
                double& pagename_rank = to_page.second; // "to" page rate

                if (output_page == from_page) {
                    pagename_rank = output_rank; // update the rate in 'pages' to the page's new page rank value
                }
            }
        }
    }
}

void AdjacencyList::getOutputs(){
    for (auto& sum: outputs){
        cout << sum.first << " " << fixed << setprecision(2) << sum.second << endl;
    }
}

//////////////////////////////////////////////////////////////////////////////////////

void AdjacencyList::tester(){
    cout << endl;
    cout << "PAGES" << endl;
//    cout << pages.size() << endl;
    for (auto& page : pages){
        cout << page.first << endl;
        for (auto& pair : page.second){
            cout << "     " << pair.first << " " << pair.second << endl;
        }
    }

    cout << endl;
    cout << "WEB RANKS" << endl;
//    cout << web_ranks.size() << endl;
    for (auto& web : web_ranks){
        cout << web.first << endl;
        for (auto& link : web.second){
            cout << "     " << link.first << " " << link.second << endl;
        }
    }

    cout << endl;
    cout << "PAGE RANKS" << endl;
    for (auto& rank : page_ranks){
        cout << rank.first << " " << rank.second << endl;
    }

    cout << endl;
    cout << "OUTPUT" << endl;
    for (auto& entry : outputs){
        cout << entry.first << " " << entry.second << endl;
    }

}