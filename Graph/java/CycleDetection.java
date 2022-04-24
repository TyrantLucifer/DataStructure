
/**
 * 检测无向图是否有环
 */
public class CycleDetection {

    /*
    当然需要一个图了,这里使用稀疏图
     */
    private SparseGraph graph;

    /*
    该图是否有环
     */
    private boolean cycled;

    /*
    被访问过的节点序号
     */
    private boolean[] visited;



    public CycleDetection(SparseGraph graph) {
        //初始化被访问的节点
        this.graph = graph;
        this.visited = new boolean[graph.getNodes()];
        for (int i = 0 ; i < graph.getNodes() ; i++) {
            if (!visited[i]) {
                if(dfs (i, i)) {
                    this.cycled = true;
                    break;
                }
            }
        }

    }

    /**
     * 如果这一次遍历发现有环,就终止遍历
     * @param nodeIndex 节点序号
     * @param fromIndex 从哪个节点遍历到当前节点
     * @return
     */
    private boolean dfs(int nodeIndex, int fromIndex) {
        visited[nodeIndex] = true;
        //获取nodeIndex的所有相邻节点
        SparseGraph.Iterator iterator = graph.iterator(nodeIndex);
        for (int j = iterator.start() ; iterator.hasNext(); j = iterator.next()) {
            if (!visited[j]) {
                visited[j] = true;
                if (dfs(j, nodeIndex))
                    return true;
            } else if (j != fromIndex)
                return true;
        }
        return false;
    }

    public boolean hasCycle() {
        return this.cycled;
    }

}
