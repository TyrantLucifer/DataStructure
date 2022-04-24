/**
 * 深度优先遍历
 */
public class DeepSearch {

    /*
    遍历当然需要一个图了.
     */
    private SparseGraph graph;

    /*
    节点是否被遍历过,数组下标对应图中节点的下标
     */
    private boolean[] visited;

    /*
    连通分量的数量
     */
    private int connCount;

    /*
    标注节点对应的连通分量
     */
    private int[] connIds;

    public DeepSearch(SparseGraph graph) {
        this.graph = graph;
        this.visited = new boolean[graph.getNodes()];
        this.connIds = new int[graph.getNodes()];
        this.connCount = 0;
        //初始化节点访问数组
        initVisitedNodes();
        //开始遍历
        search();
    }

    /**
     * 返回连通分量的数量
     *
     * @return
     */
    public int getConnCount() {
        return connCount;
    }

    /**
     * 判断节点i 和节点k是否相连
     *
     * @param i
     * @param k
     * @return
     */
    public boolean connected(int i, int k) {
        //别忘了检查下标
        assert i < graph.getNodes();
        assert k < graph.getNodes();
        return connIds[i] == connIds[k];
    }

    private void initVisitedNodes() {
        for (int i = 0; i < graph.getNodes(); i++) {
            visited[i] = false;
            connIds[i] = -1;
        }
    }

    /**
     * 遍历图
     */
    private void search() {
        //这里从下标为0的节点开始遍历
        for (int i = 0; i < graph.getNodes(); i++) {
            //如果当前节点没有被遍历过,就执行深度优先遍历
            if (!visited[i]) {
                dfs(i);
                //这一次深度优先遍历完成,说明有一个连通分量.连通分量数量 + 1,为什么呢,因为每个连通分量的节点都不与其他的连通分量节点相连.遍历完了,说明这个图就是一个连通分量.
                this.connCount++;
            }
        }
    }

    /**
     * 深度优先遍历核心方法
     *
     * @param i
     */
    private void dfs(int i) {
        //标识当前节点所属的连通分量.
        connIds[i] = connCount;
        //当前节点没有被遍历过,现在遍历到了,把对应的状态变成已遍历
        visited[i] = true;
        //设置完成后,检查当前节点的相邻节点是否被遍历过,如果没有则继续dfs
        SparseGraph.Iterator itor = graph.iterator(i);
        for (int adj = itor.start(); itor.hasNext(); adj = itor.next()) {
            if (!visited[adj])
                dfs(adj);
        }
    }

}
