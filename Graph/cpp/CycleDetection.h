//
// Created by blentle on 2022/2/11.
//

#ifndef CPP_CYCLEDETECTION_H
#define CPP_CYCLEDETECTION_H

#endif  // CPP_CYCLEDETECTION_H
using namespace std;

template<typename Graph>
class CycleDetection {
private:

    //当然需要一个图的引用了
    Graph &g;


    //记录被访问的节点的下标
    bool *visited;

    //是否有环
    bool cycled;

    /**
     *
     * @param nodeIndex 当前节点
     * @param from 当前节点是由哪个节点遍历过来
     * @return
     */
    bool dfs(int nodeIndex, int from) {
        //遍历到当前节点,把当前节点置为已访问
        visited[nodeIndex] = true;
        //遍历当前节点所有相邻的节点
        typename Graph::Iterator adj(g, nodeIndex);
        for(int j = adj.start() ; !adj.end() ; j = adj.next()) {
            if (!visited[j]) {
                //没被访问过就进行一次深度优先遍历
                visited[j] = true;
                if (dfs(j, nodeIndex))
                    return true;
            }
            else if (j != from)
                return true;
        }
        return false;
    }

public:

    CycleDetection(Graph &graph) : g(graph) {
        this->visited = new bool[g.getNodes()];
        //深度优先遍历每个节点
        for (int i = 0 ; i < g.getNodes() ; i++) {
            if (!visited[i]) {
                //未被访问过就进行一次深度优先遍历,如果遍历过程中发现有环,就直接跳出了,不要再浪费时间去遍历下一个节点了
                if (dfs(i, i)) {
                    this-> cycled = true;
                    break;
                }
            }
        }
    }

    ~CycleDetection() {
        delete[] visited;
    }

    bool hasCycle() {
        return this->cycled;
    }
};