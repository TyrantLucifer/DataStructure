import java.util.ArrayList;
import java.util.List;

/**
 * 稀疏图(使用邻接表实现)
 * 这里使用泛型标识节点的类型(节点上的值不一定是上面图中字符串A,B,C..., 可能是数字或者其他对象,就像之前的树节点)
 */
public class SparseGraph {

    /*
    节点的数量
    */
    private int nodes;

    /*
    边的数量
     */
    private int edges;

    /*
    是否有向图
     */
    private boolean directed;

    /*
    假定给图的所有节点铺开成一条直线, 按从头到尾编成序号从0到(nodes-1),这里外部List存储每个节点序号,内部List存储对应与之相连的节点下标.
     */
    private List<List<Integer>> g;

    /**
     * 构造一个图
     * @param nodes 节点的数量
     * @param directed 是否有向图
     */
    public SparseGraph(int nodes, boolean directed) {
        this.nodes = nodes;
        this.directed = directed;
        //默认边的数量是0,会提供一个方法为节点添加边
        this.edges = 0;
        this.g = new ArrayList<>();
        //根据节点的数量,初始化g,每个节点都是孤立的,不与任何节点相连,所以内层的邻接表是空表
        for (int i = 0; i < nodes ; i ++) {
            List<Integer> innerList = new ArrayList<>();
            g.add(i, innerList);
        }
    }

    /**
     * 获取节点的数量
     * @return
     */
    public int getNodes() {
        return nodes;
    }

    /**
     * 获取边的数量
     * @return
     */
    public int getEdges() {
        return edges;
    }

    /**
     * 是否是有向图
     * @return
     */
    public boolean isDirected() {
        return directed;
    }

    /**
     * 添加一条边
     * @param fromIndex  节点from的序号
     * @param toIndex   节点to的序号
     */
    public void addEdge(int fromIndex, int toIndex) {
        //越界检查
        sanityCheck(fromIndex, toIndex);

        //自己跟自己不相连
        if (fromIndex == toIndex)
            return;

        //给对应位置的节点序号添加相连的节点序号
        List<Integer> adjList = g.get(fromIndex);
        //如果有,说明本来就相连,直接返回
        if (adjList.contains(toIndex))
            return;
        //修改边的数量,这里不能简单的 edges++, 没有考虑原来添加过这条边,需要预先检查
        if (!hasEdge(fromIndex, toIndex))
            edges ++;
        //没有才添加
        adjList.add(toIndex);
        //这里只是单向的设置了fromIndex和toIndex对应的元素相连,下面这行代码根据图的有向性设置反向toIndex到fromIndex是否相连.

        //无向图,两边都得相连
        if (!directed) {
            List<Integer> inverseList = g.get(toIndex);
            if (!inverseList.contains(fromIndex))
                g.get(toIndex).add(fromIndex);
        }
    }

    /**
     * 展示这个图
     * 这里打印
     */
    public void render() {
        for (int i = 0 ; i < g.size() ; i++) {
            System.out.print(i + " -> ");
            for (int k = 0 ; k < g.get(i).size() ; k ++)
                System.out.print(g.get(i).get(k) + " ");
            System.out.println("\n");
        }
    }

    /**
     * 对外提供一个迭代器遍历某个节点(下标)的相邻节点
     * @param nodeIndex
     * @return
     */
    public Iterator iterator(int nodeIndex) {
        return new Iterator(this, nodeIndex);
    }

    /**
     * 检查 fromIndex和toIndex下标对应的元素是否相连
     * @param fromIndex
     * @param toIndex
     * @return
     */
    private boolean hasEdge(int fromIndex, int toIndex) {
        sanityCheck(fromIndex, toIndex);
        return g.get(fromIndex).contains(toIndex);
    }

    /**
     * @param fromIndex
     * @param toIndex
     */
    private void sanityCheck(int fromIndex, int toIndex) {
        if (fromIndex < 0 || fromIndex >= nodes) throw new ArrayIndexOutOfBoundsException("from index out of bound");
        if (toIndex < 0 || toIndex >= nodes) throw new ArrayIndexOutOfBoundsException("to index out of bound");
    }

    /**
     * 获取一个节点的所有相连的节点
     */
    class Iterator {

        /*
        要遍历的图的实例
         */
        private SparseGraph graph;

        /*
        对哪一个节点(节点对应的序号值)
         */
        private int nodeIndex;

        /*
        遍历到节点对应的邻接表第几个元素了.初始值0
         */
        private int index;

        /**
         *
         * @param graph 要遍历的图
         * @param nodeIndex 指定的节点的序号[图的外层List的index值]
         */
        public Iterator(SparseGraph graph, int nodeIndex) {
            this.graph = graph;
            this.nodeIndex = nodeIndex;
        }

        /**
         * 返回第一个邻接表元素对应的序号(前面List<List<Integer>这里存储的本来就不是节点本身,而是节点的下标序号)
         * @return
         */
        public int start() {
            //这里防止这个方法被多次调用,重新把该节点对应的index初始化成0
            index = 0;
            //说明该节点对应的邻接表不是空
            if (graph.g.get(nodeIndex).size() > 0)
                return graph.g.get(nodeIndex).get(index);
            //如果对应的邻接表是空表,返回-1
            return -1;
        }

        /**
         * 获取下一个相连节点的下标序号
         * @return
         */
        public int next() {
            index ++;
            // ++ 了要判断是否越界
            if (index < graph.g.get(nodeIndex).size())
                return graph.g.get(nodeIndex).get(index);
            //不存在,返回-1
            return -1;
        }

        /**
         * 是否还有相邻的节点
         * @return
         */
        public boolean hasNext() {
            return index < graph.g.get(nodeIndex).size();
        }
    }
}
