#ifndef CPP_GRAPHREADER_H
#define CPP_GRAPHREADER_H


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

//使用标准库api, 如string, stringstream
using namespace std;

template <typename Graph>

/**
 * java版本里想实现的,先cpp版本里实现
 * 辅助图的初始化数据读取器
 */
class GraphReader {
public:
    // 从文件filename中读取图的信息, 存储进图graph中
    GraphReader(Graph &graph, const string &filename){

        ifstream file(filename);
        string line;
        int nodes;
        int edges;

        assert( file.is_open() );

        // 第一行读取图中的节点个数和边的个数
        assert( getline(file, line) );
        stringstream ss(line);
        ss>>nodes>>edges;

        assert( nodes == graph.getNodes() );

        // 读取每一条边的信息
        for( int i = 0 ; i < edges ; i ++ ){

            assert( getline(file, line) );
            stringstream ss(line);

            int a,b;
            ss>>a>>b;
            assert( a >= 0 && a < nodes );
            assert( b >= 0 && b < nodes );
            graph.addEdge( a , b );
        }
    }
};


#endif //CPP_GRAPHREADER_H
