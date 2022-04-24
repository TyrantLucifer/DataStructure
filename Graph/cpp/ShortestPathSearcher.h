#ifndef CPP_SHORTESTPATHSEARCHER_H
#define CPP_SHORTESTPATHSEARCHER_H

#include <vector>
#include <queue>
#include <stack>
#include <iostream>

using namespace std;

template<typename Graph>
/**
 *  使用广度优先遍历寻找最短路径
 */
class ShortestPathSearcher {
private:
    // 图的引用
    Graph &g;

    // 起始点,从哪个节点开始寻路
    int s;

    // bfs的过程中节点是否被访问
    bool *visited;

    // 记录路径, from[i]表示查找的路径的上一个节点
    int *from;

public:
    // 构造函数, 寻路算法, 寻找图graph从startIndex点到其他点的路径
    ShortestPathSearcher(Graph &graph, int startIndex) : g(graph) {

        assert(startIndex >= 0 && startIndex < g.getNodes());
        this->visited = new bool[g.getNodes()];
        this->from = new int[g.getNodes()];
        this->s = startIndex;

        //初始化from 和visited
        for (int i = 0; i < g.getNodes(); i++) {
            visited[i] = false;
            from[i] = -1;
        }

        //进行一次广度优先遍历,从startIndex开始
        //广度优先遍历类似于层序遍历,需要一个队列
        queue<int> q;
        q.push(startIndex);
        visited[startIndex] = true;
        //只要队列不是空,就继续寻找遍历
        while(!q.empty()) {
            //取出队头元素
            int n = q.front();
            //即将要处理队头,所以从队列中剔除队头
            q.pop();
            //找到当前startIndex节点的所有相邻节点
            typename Graph::Iterator adj(g, n);
            for( int i = adj.start() ; !adj.end() ; i = adj.next() ) {
                if (!visited[i]) {
                    //没有被遍历过,推入队列
                    q.push(i);
                    visited[i] = true;
                    from[i] = n;
                }
            }
        }

    }

    ~ShortestPathSearcher() {
        //申请了记录节点访问情况和来源的空间,这里释放
        delete[] visited;
        delete[] from;
    }

    /**
     * 因为构造方法中已经遍历过一次,如果这个节点被遍历过,说明有路
     * @param node
     * @return
     */
    bool hasPath(int node){
        assert( node >= 0 && node < g.getNodes() );
        return visited[node];
    }

    void path(int w, vector<int> &vec){

        assert( w >= 0 && w < g.getNodes() );

        stack<int> s;
        // 通过from数组逆向查找到从s到w的路径, 存放到栈中
        int p = w;
        while( p != -1 ){
            s.push(p);
            p = from[p];
        }

        // 从栈中依次取出元素, 获得顺序的从s到w的路径
        vec.clear();
        while( !s.empty() ){
            vec.push_back( s.top() );
            s.pop();
        }
    }

    // 打印出从startIndex点到w点的路径
    void showPath(int w){

        assert( w >= 0 && w < g.getNodes() );

        vector<int> vec;
        path(w, vec);
        for( int i = 0 ; i < vec.size() ; i ++ ){
            cout<<vec[i];
            if( i == vec.size()-1 )
                cout<<endl;
            else
                cout<<" -> ";
        }
    }
};


#endif //CPP_SHORTESTPATHSEARCHER_H
