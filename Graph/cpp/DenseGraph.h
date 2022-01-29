#ifndef CPP_DENSEGRAPH_H
#define CPP_DENSEGRAPH_H
//指定使用标准库里的vector
#include <iostream>
#include <vector>

using namespace std;

/**
 * 邻接矩阵实现稠密图
 */

class DenseGraph {
private:

    //节点的数量
    int nodes;

    //边的数量
    int edges;

    //是否有向图
    bool directed;

    //因为是矩阵,这里内层vector值选用bool类型,标识外层vector下标与内层vector下标对应的节点是否相连.
    vector<vector<bool>> g;

    /**
     * 检查节点序号是否越界
     * @param startIndex
     * @param endIndex
     */
    void sanityCheck(int startIndex, int endIndex) {
        assert(startIndex >= 0 && startIndex < nodes);
        assert(endIndex >= 0 && endIndex < nodes);
    }

public:
    // 构造函数
    DenseGraph(int nodes, bool directed) {
        assert(nodes >= 0);
        this->nodes = nodes;
        this->edges = 0;    // 初始化没有任何边
        this->directed = directed;
        // g初始化为n*n的布尔矩阵, 每一个g[i][j]均为false, 表示没有任和边
        g = vector<vector<bool>>(nodes, vector<bool>(nodes, false));
    }

    //没有开辟空间,什么都不用做
    ~DenseGraph() {

    }

    /**
     * 给图添加一条边
     * @param v
     * @param w
     */
    void addEdge(int start, int end) {

        sanityCheck(start, end);

        //这里防止边的数量多次+1,已经相连的两条边就不要再设置了
        if (hasEdge(start, end))
            return;

        g[start][end] = true;
        if (!directed)
            g[end][start] = true;

        this->edges++;
    }

    /**
     * start节点和end节点是否有边
     * @param start
     * @param end
     */
    bool hasEdge(int start, int end) {
        sanityCheck(start, end);
        return g[start][end];
    }

    /**
    * 返回节点的个数
    * @return
    */
    int getNodes() const {
        return nodes;
    }

    /**
     * 返回边的个数
     * @return
     */
    int getEdges() const {
        return edges;
    }

    /**
     * 展示这个图
     */
    void render() {
        for (int i = 0; i < nodes; i++) {
            for (int j = 0; j < nodes; j++)
                cout << g[i][j] << "\t";
            cout << endl;
        }
    }


    //同稀疏图一样也实现一个迭代器
    class Iterator {
    private:

        // 迭代哪个图
        DenseGraph &gr;

        //指定的节点
        int v;

        //遍历时的序号(小于这个节点的相邻接点的个数)
        int index;

    public:
        // 构造函数
        Iterator(DenseGraph &graph, int v) : gr(graph) {
            assert(v >= 0 && v < gr.getNodes());
            this->v = v;

            //这里 区别于邻接表, 索引从-1开始, 因为每次遍历都需要调用一次next()
            this->index = -1;
        }

        ~Iterator() {
            //啥也不干
        }

        // 返回图gr中与节点v相连接的第一个节点
        int start() {
            // 索引从-1开始, 因为每次遍历都需要调用一次next()
            index = -1;
            return next();
        }

        // 返回图gr中与节点v相连接的下一个节点
        int next() {
            // 从当前index开始向后搜索, 直到找到一个g[v][index]为true
            for (index += 1; index < gr.getNodes(); index++)
                if (gr.g[v][index])
                    return index;
            // 若没有节点和v相连接, 则返回-1
            return -1;
        }

        // 查看是否已经迭代完了图gr中与节点v相连接的所有节点
        bool end() {
            return index >= gr.getNodes();
        }
    };
};

#endif //CPP_DENSEGRAPH_H