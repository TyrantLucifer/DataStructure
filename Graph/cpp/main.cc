#include <iostream>
#include "SparseGraph.h"
#include "GraphReader.h"
#include "PathSearcher.h"

using namespace std;
int main() {
    string filename = "g1.txt";
    SparseGraph g = SparseGraph(7, false);
    GraphReader<SparseGraph> graphReader(g, filename);
    g.render();
    cout<<endl;

    PathSearcher<SparseGraph> path(g,0);
    cout<<"Path from 0 to 6 : " << endl;
    path.renderPath(6);

    return 0;
}
