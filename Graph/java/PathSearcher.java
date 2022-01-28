import java.util.Stack;

/**
 * 寻找指定节点到某一个节点的路径
 */
public class PathSearcher {

    /*
    寻路
     */
    private SparseGraph graph;

    /*
    下标对应得节点是否被访问过
     */
    private boolean[] visited;

    /*
    寻路的起始节点的序号
     */
    private int startIndex;

    /*
    数组下标是节点的序号.下标对应的值是当前节点从哪个节点过来
     */
    private int[] from;


    public PathSearcher(SparseGraph graph, int startIndex) {
        assert startIndex >= 0 && startIndex < graph.getNodes();
        this.graph = graph;
        this.startIndex = startIndex;
        this.visited = new boolean[graph.getNodes()];
        this.from = new int[graph.getNodes()];

        //初始化from
        for (int i = 0 ; i < graph.getNodes() ; i++) {
            //初始化成 -1
            from[i] = -1;
            visited[i] = false;
        }
        //进行一次深度优先遍历,从startIndex开始
        dfs(startIndex);
    }

    public int getStartIndex() {
        return this.startIndex;
    }


    public Stack<Integer> path(int tIndex) {
        //从tIndex往前推,所以把路径放在栈里,输出时就是从最开始的节点到tIndex的路径
        Stack<Integer> path = new Stack<>();
        if (hasPath(tIndex)) {
            //上一个节点:
            int p = tIndex;
            while (p != -1) {
                path.push(p);
                p = from[p];
            }
        }
        return path;
    }

    /**
     * 从 startIndex 到tIndex是否有路径
     * 因为从某一个节点开始遍历寻找路径,所以只要这个节点被访问过,就说明有路径
     * @param tIndex
     * @return
     */
    private boolean hasPath(int tIndex) {
        assert tIndex >= 0 && tIndex < graph.getNodes();
        return visited[tIndex];
    }

    /**
     * 进行一次深度优先遍历
     * @param i
     */
    private void dfs(int i) {
        visited[i] = true;
        SparseGraph.Iterator itor = graph.iterator(i);
        for (int adj = itor.start(); itor.hasNext() ; adj = itor.next()) {
            if ( !visited[adj]) {
                //i的相邻节点来源当然是i
                from[adj] = i;
                dfs(adj);
            }
        }
    }
}
