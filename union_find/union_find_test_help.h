#ifndef UNION_FIND_TEST_HELP_H
#define UNION_FIND_TEST_HELP_H

#include <iostream>
#include <ctime>
#include "union_find.h"
#include "quick_union.h"
#include "quick_union_optim.h"
#include "quick_union_optim2.h"

namespace UnionFindTestHelper {

    void testUnionFind(int n)
    {
        std::srand(time(NULL));
        UNION_FIND::UnionFind unionFind(n);

        time_t start = clock();
        for (int i = 0; i < n; ++i) {
            //unionFind.print();
            int x = rand() % n;
            int y = rand() % n;
            unionFind.unionElements(x, y);
        }

        for (int i = 0; i < n; ++i) {
            int x = rand() % n;
            int y = rand() % n;
            unionFind.isConnected(x, y);
        }

        time_t end = clock();
        double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;

        std::cout << "Union-Find Test with " << n << " elements: " << duration << " seconds." << std::endl;
    }

    void testQuickUinon(int n)
    {
        std::srand(time(NULL));
        UNION_FIND::QuickUnion unionFind(n);

        time_t start = clock();
        for (int i = 0; i < n; ++i) {
            //unionFind.print();
            int x = rand() % n;
            int y = rand() % n;
            unionFind.unionElements(x, y);
        }

        for (int i = 0; i < n; ++i) {
            int x = rand() % n;
            int y = rand() % n;
            unionFind.isConnected(x, y);
        }

        time_t end = clock();
        double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;

        std::cout << "Quick-Union Test with " << n << " elements: " << duration << " seconds." << std::endl;
    }

    void testQuickUinonOptimBySize(int n)
    {
        std::srand(time(NULL));
        UNION_FIND::QuickUnionOptimBySize unionFind(n);

        time_t start = clock();
        for (int i = 0; i < n; ++i) {
            //unionFind.print();
            int x = rand() % n;
            int y = rand() % n;
            unionFind.unionElements(x, y);
        }

        for (int i = 0; i < n; ++i) {
            int x = rand() % n;
            int y = rand() % n;
            unionFind.isConnected(x, y);
        }

        time_t end = clock();
        double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;

        std::cout << "Quick-Union-Size Test with " << n << " elements: " << duration << " seconds." << std::endl;
    }

    void testQuickUinonOptimByRank(int n)
    {
        std::srand(time(NULL));
        UNION_FIND::QuickUnionOptimByRank unionFind(n);

        time_t start = clock();
        for (int i = 0; i < n; ++i) {
            //unionFind.print();
            int x = rand() % n;
            int y = rand() % n;
            unionFind.unionElements(x, y);
        }

        for (int i = 0; i < n; ++i) {
            int x = rand() % n;
            int y = rand() % n;
            unionFind.isConnected(x, y);
        }

        time_t end = clock();
        double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;

        std::cout << "Quick-Union-Rank Test with " << n << " elements: " << duration << " seconds." << std::endl;
    }

}

#endif