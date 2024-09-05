#include <algorithm>
#include <iostream>
#include "help_class/Student.h"
#include "sort/sort_test_help.h"
#include "sort/sort.h"
#include "heap/heap.h"
#include "heap/index_heap.h"

#include "binary_search_tree/binary_search_tree.h"
#include "union_find/union_find_test_help.h"
#include "graph/sparse_graph.h"
#include "graph/dense_graph.h"
#include "graph/read_graph.h"
#include "graph/component.h"
#include "graph/path.h"

#include "weighted_graph/dense_graph.h"
#include "weighted_graph/sparse_graph.h"
#include "weighted_graph/read_graph.h"
#include "weighted_graph/lazy_prim_min_tree.h"
#include "weighted_graph/kruskal_min_tree.h"
#include "weighted_graph/prim_mst_optim.h"
#include "weighted_graph/dijkstra_shortest_path.h"
#include "weighted_graph/edge.h"

using namespace std;

int main()
{
    // Student s1("John", 18), s2("Alice", 20), s3("Bob", 17);
    // Student arr_students[] = {s1, s2, s3};
    // n = sizeof(arr_students) / sizeof(arr_students[0]);
    // select_sort(arr_students, n);
    // SortTestHelper::PrintArray<Student>(arr_students, 3);

    // 堆
    // int HeapCapacity = 10;
    // HEAP::IndexHeap<int> heap(HeapCapacity);
    // srand(time(NULL));
    // for (int i = 0; i < HeapCapacity; ++i) {
    //     // int index = rand() % HeapCapacity;
    //     int num = rand() % (HeapCapacity*10);
    //     cout << "index " << i << " : "<<  num << endl;
    //     heap.push(i, num);
    // }
    // int size = heap.size();
    // cout << "heap size: " << size << endl;
    // heap.printHeap();
    // heap.change(2, 1000);
    // heap.change(8, 1);
    // heap.printHeap();
    // cout << endl;
    // for (int i = 0; i < size; ++i) {
    //     cout << heap.pop() << " ";
    // }
    // cout << endl;

    // int n = 5;
    // int swapTimes = 10;
    // int *arr = SortTestHelper::generateRandomArray(n, 0, n*4);
    // int *copyArray = SortTestHelper::copyIntArray(arr, n);
    // int *copyArray2 = SortTestHelper::copyIntArray(arr, n);
    // int *copyArray3 = SortTestHelper::copyIntArray(arr, n);
    // Sort::Sort<int> obj;
    // SortTestHelper::testSort("mergeSort", obj, Sort::Sort<int>::mergeSort, arr, n);
    // SortTestHelper::testSort("quickSort", obj, Sort::Sort<int>::quickSort, copyArray, n);
    // SortTestHelper::testSort("heapSort", obj, Sort::Sort<int>::heapSort, arr, n);
    // SortTestHelper::testSort("heapSort1", obj, Sort::Sort<int>::heapSort1, arr, n);
    // delete[] arr;
    // delete[] copyArray;
    // delete[] copyArray2;
    // delete[] copyArray3;

    // 二叉树
    // BINARY_SEARCH_TREE::BinarySearchTree<int, int> bst;
    // bst.insert(10, 10);
    // bst.insert(5, 5);
    // bst.insert(15, 15);
    // bst.insert(3, 3);
    // bst.insert(7, 7);
    // bst.insert(13, 13);
    // cout << "tree size: " << bst.size() << endl;
    // bst.preOrder();
    // bst.midOrder();
    // bst.postOrder();
    // bst.levelOrder();

    // 并查集:
    // UnionFindTestHelper::testUnionFind(n);
    // UnionFindTestHelper::testQuickUinon(n);
    // UnionFindTestHelper::testQuickUinonOptimBySize(n);
    // UnionFindTestHelper::testQuickUinonOptimByRank(n);

    int vNum = 7; // 从文件中获取
    GRAPH::DenseGraph graph(vNum, true);
    /*
     * 如果要打开的目标文件与可执行文件xx.exe不在同一目录，建议使用绝对路径；
     * 如果要打开的目标文件与可执行文件xx.exe在同一目录，可使用相对路径。
     */
    std::string filename = "/code/mooc_algorithm/test_data/testG1.txt";
    GRAPH::ReadGraph<GRAPH::DenseGraph> readGraph(filename, graph); // 无权图

    // int eNum = 5;
    // GRAPH::DenseGraph graph(vNum, true);
    // graph.addEdge(0, 1);
    // graph.addEdge(0, 2);
    // graph.addEdge(0, 3);
    // graph.addEdge(1, 3);
    // graph.addEdge(2, 3);
    // for (int i = 0; i < vNum; ++i) {
    //     GRAPH::DenseGraph::iterator it(graph, i);
    //     cout << "vertex " << i << ": ";
    //     for (int w = it.begin(); !(it.end()); w = it.next()) {
    //         cout << w << " ";
    //     }
    //     cout << endl;
    // }
    GraphAlgorithm::Component<GRAPH::DenseGraph> graphAlgorithm(graph);
    cout << "componentCount: " << graphAlgorithm.componentCount() << endl;
    GraphAlgorithm::ShortestPath<GRAPH::DenseGraph> path(graph, 0);
    path.showPathTo(3);

    // 有权图

    // WEIGHTED_GRAPH::Edge<int> e1(1, 2, 10);
    // WEIGHTED_GRAPH::Edge<int> e2(4, 2, 10); // 权值一样的边认为是相等的边，set会丢边不合理
    // set<WEIGHTED_GRAPH::Edge<int>> s{};
    // s.insert(e1);
    // s.insert(e2);
    // for (auto &edge : s) {
    //     cout << edge << endl;
    // }

    int weightVNum = 8;
    WEIGHTED_GRAPH::SparseGraph<float> weightGraph(weightVNum, false); // 最小生成树针对的是无向图
    std::string filename2 = "/code/mooc_algorithm/test_data/weighted_testG1.txt";
    WEIGHTED_GRAPH::ReadGraph<WEIGHTED_GRAPH::SparseGraph<float>, float> readWeightGraph(filename2, weightGraph);
    // weightGraph.showGraph();

    GraphAlgorithm::LazyPrimeMST<WEIGHTED_GRAPH::SparseGraph<float>, float> lazyPrim(weightGraph); ///
    lazyPrim.showMST();

    GraphAlgorithm::KruskalMST<WEIGHTED_GRAPH::SparseGraph<float>, float> kruskal(weightGraph);
    kruskal.showMST();

    GraphAlgorithm::PrimMst<WEIGHTED_GRAPH::SparseGraph<float>, float> prim(weightGraph);
    prim.showMST();

    GraphAlgorithm::DijkstraShortestPath<WEIGHTED_GRAPH::SparseGraph<float>, float> dijkstra(weightGraph, 0);
    // dijkstra.showPathTo(6);
    dijkstra.showAllPath();

    return 0;
}