#include <iostream>
#include "SparseGraph.h"
#include "GraphReader.h"
#include "PathSearcher.h"
#include "ShortestPathSearcher.h"
#include "CycleDetection.h"

using namespace std;
int main() {
    //请使用你自己的电脑上的绝对路径
    string filename = "/Users/blentle/projects/data-structure/cpp/g2.txt";
    SparseGraph g(9, false);
    GraphReader<SparseGraph> graphReader(g, filename);
    g.render();
    cout<<endl;

//    //深度优先遍历寻找路径
//    PathSearcher<SparseGraph> path(g,13);
//    cout<<"Path from 13 to 10 : " << endl;
//    path.renderPath(10);
//
//    //广度优先遍历获取最短路径
//    ShortestPathSearcher<SparseGraph> bfs(g,4);
//    cout << "BFS-shortest path : ";
//    bfs.showPath(1);

    //深度优先遍历判断无向图是否有环
    CycleDetection<SparseGraph> cycleDetection(g);
    cout << "has cycle:"  << endl;
    cout << cycleDetection.hasCycle();
    return 0;
}
