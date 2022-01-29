#ifndef CPP_SPARSEGRAPH_H
#define CPP_SPARSEGRAPH_H

#include <vector>

//指定使用标准库里的vector
using namespace std;

/**
 * 邻接表实现稀疏图
 */
class SparseGraph {
private:
    //节点的数量
    int nodes;

    //边的数量
    int edges;

    //是否有向图
    bool directed;

    //外层表示节点序号,内层是节点(序号)对应的邻接表
    vector<vector<int>> g;

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

    //构造方法
    SparseGraph(int nodes, bool directed) {
        //边界检查
        assert(nodes > 0);
        this->nodes = nodes;
        this->directed = directed;
        //初始化时没有边
        this->edges = 0;
        //初始化邻接表也是空表
        this->g = vector<vector<int>>(nodes, vector<int>());

    }

    //析构函数:因为构造函数中没有开辟任何堆空间,这里啥都不用干.
    ~SparseGraph() {

    }

    /**
     * 初始化一条边 表示哪两个节点相连
     * @param start
     * @param end
     */
    void addEdge(int start, int end) {

        sanityCheck(start, end);

        g[start].push_back(end);

        //如果是无向的,这里对应的反向数据也连上
        if (start != end && !directed)
            g[end].push_back(start);
        //边的个数 + 1
        this->edges++;
    }

    /**
     * start节点和end节点是否有边
     * @param start
     * @param end
     */
    bool hasEdge(int start, int end) {

        sanityCheck(start, end);

        for (int i = 0; i < g[start].size(); i++)
            if (g[start][i] == end)
                return true;
        return false;
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
     * 显示图的信息
     */
    void render(){

        for( int i = 0 ; i < nodes ; i ++ ){
            cout<<"adj "<<i<<":\t";
            for( int j = 0 ; j < g[i].size() ; j ++ )
                cout<<g[i][j]<<"\t";
            cout<<endl;
        }
    }

    //构造一个迭代器,用于获取指定节点的相邻节点
    class Iterator {

    private:

        // 迭代哪个图
        SparseGraph &gr;

        //指定的节点
        int v;

        //遍历时的序号(小于这个节点的相邻接点的个数)
        int index;

    public:

        Iterator(SparseGraph &graph, int v) : gr(graph) {
            assert( v >= 0 && v < gr.nodes );
            this->v = v;
            this->index = 0;
        }

        ~Iterator() {

        }

        /**
         * 返回图gr中与节点v相连接的第一个节点
         * @return
         */
        int start() {
            index = 0;
            if (gr.g[v].size())
                return gr.g[v][index];
            // 若没有节点和v相连接, 则返回-1 ,好像永远也走不到这里.
            return -1;
        }

        /**
         * 与节点v相连接的下一个节点
         * @return
         */
        int next() {
            index++;
            if (index < gr.g[v].size())
                return gr.g[v][index];
            // 若没有节点和v相连接, 则返回-1
            return -1;
        }

        /**
         * 是否已经迭代完了图gr中与节点v相连接的所有节点
         * @return
         */
        bool end() {
            return index >= gr.g[v].size();
        }
    };

};


#endif //CPP_SPARSEGRAPH_H
