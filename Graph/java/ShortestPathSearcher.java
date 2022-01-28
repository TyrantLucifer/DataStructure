import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

/**
 * 广度优先遍历求最短路径
 */
public class ShortestPathSearcher {

    /*
    遍历当然需要一个图了.
     */
    private SparseGraph graph;

    /*
    节点是否被遍历过,数组下标对应图中节点的下标
     */
    private boolean[] visited;

    /*
     记录每一个节点的上一个节点
     下标是节点的序号,值对应的是上一个节点的序号.
     */
    private int[] from;

    /*
    从哪个节点(序号)开始遍历
     */
    private int startIndex;

    public ShortestPathSearcher(SparseGraph graph, int startIndex) {
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
        //进行一次广度优先遍历,从startIndex开始
        //需要先初始化一个队列
        Queue<Integer> queue = new LinkedList();
        //先把选定的起始节点塞入队列,也即先访问起始节点
        queue.add(startIndex);
        visited[startIndex] = true;
        //从下开始遍历队列
        while (!queue.isEmpty()) {
            //弹出队头元素
            int p = queue.poll();
            //获取这个节点的相邻节点
            SparseGraph.Iterator itor = graph.iterator(p);
            for (int i = itor.start() ; itor.hasNext(); i = itor.next()) {
                //相邻节点是否被访问过
                if ( !visited[i] ) {
                    //如果没有被访问过,就加入队列
                    queue.add(i);
                    visited[i] = true;
                    //更新当前节点的上一个节点
                    from[i] = p;
                }
            }
        }

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

}
