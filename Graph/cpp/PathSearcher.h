
#ifndef CPP_PATHSEARCHER_H
#define CPP_PATHSEARCHER_H

#include <vector>
#include <stack>
#include <iostream>
#include <cassert>

using namespace std;

//不管传的是稀疏图还是稠密图,这里统一成一个图接口
template<typename Graph>

class PathSearcher {
private:

    // 图的引用
    Graph &g;

    // 起始点,从哪个节点开始寻路
    int s;

    // dfs的过程中节点是否被访问
    bool *visited;

    // 记录路径, from[i]表示查找的路径的上一个节点
    int *from;

    // 图的深度优先遍历
    void dfs(int v) {

        visited[v] = true;

        typename Graph::Iterator iterator(g, v);
        for (int i = iterator.start(); !iterator.end(); i = iterator.next()) {
            if (!visited[i]) {
                from[i] = v;
                dfs(i);
            }
        }
    }

public:
    // 构造函数, 寻路算法, 寻找图graph从s点到其他点的路径
    PathSearcher(Graph &graph, int s) : g(graph) {

        assert(s >= 0 && s < g.getNodes());
        visited = new bool[g.getNodes()];
        from = new int[g.getNodes()];
        for (int i = 0; i < g.getNodes(); i++) {
            visited[i] = false;
            from[i] = -1;
        }
        this->s = s;
        //进行一次深度优先遍历
        dfs(s);
    }

    // 析构函数
    ~PathSearcher() {
        //申请了记录节点访问情况和来源的空间,这里释放
        delete[] visited;
        delete[] from;
    }

    // 查询从s点到w点是否有路径
    bool hasPath(int w) {
        assert(w >= 0 && w < g.getNodes());
        return visited[w];
    }

    // 查询从s点到w点的路径, 存放在vec中
    void path(int w, vector<int> &vec) {

        assert(hasPath(w));

        stack<int> s;
        // 通过from数组逆向查找到从s到w的路径, 存放到栈中
        int p = w;
        while (p != -1) {
            s.push(p);
            p = from[p];
        }

        // 从栈中依次取出元素, 获得顺序的从s到w的路径
        vec.clear();
        while (!s.empty()) {
            vec.push_back(s.top());
            s.pop();
        }
    }

    // 打印出从s点到w点的路径
    void renderPath(int w) {

        assert(hasPath(w));

        vector<int> vec;
        path(w, vec);
        for (int i = 0; i < vec.size(); i++) {
            cout << vec[i];
            if (i == vec.size() - 1)
                cout << endl;
            else
                cout << " -> ";
        }
    }
};


#endif //CPP_PATHSEARCHER_H
