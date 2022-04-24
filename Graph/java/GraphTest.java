import org.junit.Test;

import java.util.Map;
import java.util.Random;
import java.util.Set;
import java.util.Stack;
import java.util.TreeMap;
import java.util.TreeSet;

public class GraphTest {

    /**
     * 测试稀疏图(邻接表实现)
     */
    @Test
    public void testSparseGraph() {
        //随机初始化一个稀疏图
        SparseGraph sparseGraph = new SparseGraph(20, false);
        //20个节点无向图最多 n(n-1)/2条边, 这里n =20
        //添加边, 稀疏图 这里使用随机最多添加 15条边 << 190 条边, 因为多次随机可能下标都一样,还有可能fromIndex和toIndex一样,这里使用generateNrandomSparseData避免了这两个情况
        Map<Integer, Integer> sparseData = generateSparseNrandomData(20, 15);
        sparseData.forEach(sparseGraph::addEdge);
        sparseGraph.render();
        System.err.println("edge count:" + sparseGraph.getEdges());
    }


    /**
     * 测试稠密图(邻接矩阵实现)
     */
    @Test
    public void testDenseGraph() {
        //随机初始化一个稠密图
        DenseGraph denseGraph = new DenseGraph(10, false);
        //20个节点无向图最多 n(n-1)/2条边, 这里n =10
        //添加边, 稠密图 这里使用随机最多添加 45 条边, 因为多次随机可能下标都一样,还有可能fromIndex和toIndex一样，所以可能不是个完全图,这里使用generateNrandomSparseData避免了这两个情况
        Map<Integer, Set<Integer>> denseData = generateDenseNrandomData(10, 38);
        denseData.forEach((fromRandom, toRandom) -> toRandom.forEach(to -> denseGraph.addEdge(fromRandom, to)));
        denseGraph.render();
        System.err.println("edge count:" + denseGraph.getEdges());
    }

    /**
     * 测试深度优先遍历获取一个图的连通分量的数量
     */
    @Test
    public void testDeepSearchForSparseGraph() {
        //有3个连通分量的图
        SparseGraph g1 = new SparseGraph(18, false);
        g1.addEdge(0, 1);
        g1.addEdge(0, 2);
        g1.addEdge(0, 3);
        g1.addEdge(1, 2);
        g1.addEdge(3, 4);
        g1.addEdge(3, 5);
        g1.addEdge(6, 7);
        g1.addEdge(6, 8);
        g1.addEdge(7, 9);
        g1.addEdge(8, 9);
        g1.addEdge(10, 11);
        g1.addEdge(11, 12);
        g1.addEdge(12, 13);
        g1.addEdge(13, 14);
        g1.addEdge(14, 15);
        g1.addEdge(15, 16);
        g1.addEdge(16, 17);

        SparseGraph g2 = new SparseGraph(6, false);
        g2.addEdge(0, 1);
        g2.addEdge(0, 2);
        g2.addEdge(0, 3);
        g2.addEdge(1, 2);
        g2.addEdge(3, 4);
        g2.addEdge(3, 5);

        DeepSearch search1 = new DeepSearch(g1);
        DeepSearch search2 = new DeepSearch(g2);
        System.out.println(search1.getConnCount());
        System.out.println(search2.getConnCount());

        System.err.println(search1.connected(0, 15));
        System.err.println(search1.connected(5, 2));
        System.err.println(search1.connected(9, 4));
        System.err.println(search1.connected(8, 17));
        System.err.println(search1.connected(10, 17));

    }

    @Test
    public void testPathDeepSearch() {
        //有3个连通分量的图
        SparseGraph g1 = new SparseGraph(18, false);
        g1.addEdge(0, 1);
        g1.addEdge(0, 2);
        g1.addEdge(0, 3);
        g1.addEdge(1, 2);
        g1.addEdge(3, 4);
        g1.addEdge(3, 5);
        g1.addEdge(6, 7);
        g1.addEdge(6, 8);
        g1.addEdge(7, 9);
        g1.addEdge(8, 9);
        g1.addEdge(10, 11);
        g1.addEdge(11, 12);
        g1.addEdge(12, 13);
        g1.addEdge(13, 14);
        g1.addEdge(14, 15);
        g1.addEdge(15, 16);
        g1.addEdge(16, 17);

        PathSearcher dfs = new PathSearcher(g1, 4);

        Stack<Integer> stack = dfs.path(2);

        while(!stack.empty())
            System.out.println(stack.pop());
    }

    @Test
    public void testShortestPathBroadSearch() {
        //有3个连通分量的图
        SparseGraph g1 = new SparseGraph(18, false);
        g1.addEdge(0, 1);
        g1.addEdge(0, 2);
        g1.addEdge(0, 3);
        g1.addEdge(1, 2);
        g1.addEdge(3, 4);
        g1.addEdge(3, 5);
        g1.addEdge(6, 7);
        g1.addEdge(6, 8);
        g1.addEdge(7, 9);
        g1.addEdge(8, 9);
        g1.addEdge(10, 11);
        g1.addEdge(11, 12);
        g1.addEdge(12, 13);
        g1.addEdge(13, 14);
        g1.addEdge(14, 15);
        g1.addEdge(15, 16);
        g1.addEdge(16, 17);

        ShortestPathSearcher bfs =  new ShortestPathSearcher(g1, 4);

        Stack<Integer> stack = bfs.path(16);

        while(!stack.empty())
            System.out.println(stack.pop());
    }

    @Test
    public void testCycleDetection() {
        //有3个连通分量的图
        SparseGraph g1 = new SparseGraph(18, false);
        g1.addEdge(0, 1);
        g1.addEdge(0, 2);
        g1.addEdge(0, 3);
        g1.addEdge(1, 2);
        g1.addEdge(3, 4);
        g1.addEdge(3, 5);
        g1.addEdge(6, 7);
        g1.addEdge(6, 8);
        g1.addEdge(7, 9);
        g1.addEdge(8, 9);
        g1.addEdge(10, 11);
        g1.addEdge(11, 12);
        g1.addEdge(12, 13);
        g1.addEdge(13, 14);
        g1.addEdge(14, 15);
        g1.addEdge(15, 16);
        g1.addEdge(16, 17);

        //下标是0到5的连通分量
        SparseGraph g2 = new SparseGraph(6, false);
        g2.addEdge(0, 1);
        g2.addEdge(0, 2);
        g2.addEdge(0, 3);
        g2.addEdge(1, 2);
        g2.addEdge(3, 4);
        g2.addEdge(3, 5);

        //下标是10到17的连通分量(无环)
        SparseGraph g3 = new SparseGraph(8, false);
        g3.addEdge(0, 1);
        g3.addEdge(1, 2);
        g3.addEdge(2, 3);
        g3.addEdge(3, 4);
        g3.addEdge(4, 5);
        g3.addEdge(5, 6);
        g3.addEdge(6, 7);


        CycleDetection detection1 = new CycleDetection(g1);
        CycleDetection detection2 = new CycleDetection(g2);
        CycleDetection detection3 = new CycleDetection(g3);
        System.out.println(detection1.hasCycle());
        System.out.println(detection2.hasCycle());
        System.out.println(detection3.hasCycle());
    }

    /**
     *
     * @param nodeCount 节点数量
     * @param maxEdgeCount 最多生成maxEdgeCount条边(自己对自己不算)
     * @return
     */
    private Map<Integer, Integer> generateSparseNrandomData(int nodeCount, int maxEdgeCount) {
        assert maxEdgeCount > 0;
        assert nodeCount > 0;
        Map<Integer, Integer> sparseData = new TreeMap<>();
        Random r = new Random();
        while (sparseData.size() < maxEdgeCount) {
            int fromRandom = r.nextInt(nodeCount);
            int toRandom = r.nextInt(nodeCount);
            //1.自己不连自己
            if (fromRandom != toRandom)
                sparseData.put(fromRandom, toRandom);
        }
        return sparseData;
    }

    /**
     *
     * @param nodeCount 节点数量
     * @param maxEdgeCount 最多生成maxEdgeCount条边(自己对自己不算)
     * @return
     */
    private Map<Integer, Set<Integer>> generateDenseNrandomData(int nodeCount, int maxEdgeCount) {
        assert maxEdgeCount > 0;
        assert nodeCount > 0;
        Map<Integer, Set<Integer>> denseData = new TreeMap<>();
        Random r = new Random();
        for(int i = 0 ; i < nodeCount ; i++) {
            while (denseData.get(i) == null || denseData.get(i).size() < nodeCount -1) {
                int d = r.nextInt(nodeCount);
                denseData.computeIfAbsent(i, s -> new TreeSet<>()).add(d);
            }
        }

        return denseData;
    }

}
