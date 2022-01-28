import java.util.ArrayList;
import java.util.List;

/**
 * 稠密图(使用邻接矩阵实现)
 */
public class DenseGraph {

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
    外层的的节点是否与内层的每个节点是否相连,相连即为true,不相连则false.
     */
    private List<List<Boolean>> g;

    /**
     * 构造一个图
     * @param nodes 节点的数量
     * @param directed 是否有向图
     */
    public DenseGraph(int nodes, boolean directed) {
        this.nodes = nodes;
        this.directed = directed;
        //默认边的数量是0,会提供一个方法为节点添加边
        this.edges = 0;
        this.g = new ArrayList<>();
        //根据节点的数量,初始化g(方阵)对应每个元素都是false.表示每个节点都不与其他节点相连
        for (int i = 0; i < nodes ; i ++) {
            List<Boolean> innerList = new ArrayList<>();
            for (int j = 0; j < nodes ; j ++)
                innerList.add(false);
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
     * @param fromIndex  节点from 到 节点to时, from在矩阵中元素的位置,即List<List<T>>外层List的下标位置
     * @param toIndex   节点from 到 节点to时, from在矩阵中元素的位置,即List<List<T>>内层List的下标位置
     */
    public void addEdge(int fromIndex, int toIndex) {
        //越界检查
        sanityCheck(fromIndex, toIndex);
        //自己跟自己不相连
        if (fromIndex == toIndex)
            return;
        //修改边的数量,这里不能简单的 edges++, 没有考虑原来添加过这条边,对应的矩阵元素已经是true了.需要预先检查
        if (!hasEdge(fromIndex, toIndex))
            edges ++;
        //对应位置的元素值为true
        g.get(fromIndex).set(toIndex, true);
        //这里只是单向的设置了fromIndex和toIndex对应的元素相连,下面这行代码根据图的有向性设置反向toIndex到fromIndex是否相连.

        //无向图,两边都得相连
        if (!directed)
            g.get(toIndex).set(fromIndex, true);
    }

    /**
     * 展示这个图
     * 这里打印
     */
    public void render() {
        for (int i = 0 ; i < g.size() ; i++) {
            for (int k = 0 ; k < g.size() ; k ++)
                System.out.print((g.get(i).get(k) ? 1 : 0) + " ");
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
        return g.get(fromIndex).get(toIndex);
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
     * 获取一个节点(下标)的所有相连的节点(下标)
     */
    class Iterator {

        /*
        要遍历的图的实例
         */
        private DenseGraph graph;

        /*
        需要哪一个节点(节点对应的序号值)的相邻节点
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
        public Iterator(DenseGraph graph, int nodeIndex) {
            this.graph = graph;
            this.nodeIndex = nodeIndex;
        }

        /**
         * 返回第一个邻接矩阵元素对应的序号(前面List<List<Boolean>这里存储的本来就不是节点本身,而是节点的下标序号)
         * @return
         */
        public int start() {
            index = -1;
            return next();
        }

        /**
         * 获取下一个相连节点的下标序号
         * @return
         */
        public int next() {
            index ++;
            // ++ 了要判断是否越界
            for (int i = index; i < graph.g.size(); i ++) {
                //这里是true,说明这个矩阵对应的这个元素两个维度相连.
                if (graph.g.get(nodeIndex).get(i))
                    return i;
            }
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
