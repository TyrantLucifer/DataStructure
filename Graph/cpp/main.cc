#include <iostream>
#include "SparseGraph.h"
#include "GraphReader.h"
#include "PathSearcher.h"

using namespace std;
int main() {
    //请使用你自己的电脑上的绝对路径
    string filename = "/Users/blentle/projects/data-structure/cpp/g1.txt";
    SparseGraph g(18, false);
    GraphReader<SparseGraph> graphReader(g, filename);
    g.render();
    cout<<endl;

    PathSearcher<SparseGraph> path(g,13);
    cout<<"Path from 13 to 10 : " << endl;
    path.renderPath(10);

    return 0;
}
