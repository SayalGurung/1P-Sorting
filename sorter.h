/*
 * sorter.h
 *
 * Declares a template function:
 *    
 *   sorter() : k-way merge sort.
 * 
 * 
 * You may add other functions if you wish, but this template function
 * is the only one that need to be exposed for the testing code.
 * 
 * Authors: C. Painter-Wakefield & Tolga Can
 */

#ifndef _SORTER_H
#define _SORTER_H

#include <string>
#include <cstddef>
#include <vector>

/***
 * DO NOT put unscoped 'using namespace std;' in header files!
 * Instead put them at the beginning of class or function definitions
 * (as demonstrated below).
 *
 * For more details, see the commentary at the top of
 *   tests/header-sans-using-namespace.h
 * in this project repo.
 */

template <class T>
void sorter(std::vector<T> &items, std::size_t k) {
    if (k < 2) {
        throw std::invalid_argument("k must be at least 2");
    }

    if (items.size() < 2) {
        return;
    }

    // Efficiency: Cap k at the size of the vector
    if (k > items.size()) {
        k = items.size();
    }

    std::size_t n = items.size();
    std::vector<std::vector<T>> partitions(k);

    // Split logic (Round-robin)
    for (std::size_t i = 0; i < n; i++) {
        partitions[i % k].push_back(items[i]);
    }

    // Recursion
    for (std::size_t i = 0; i < k; i++) {
        sorter(partitions[i], k);
    }

    // Merge logic (Max-elements approach)
    for (int i = static_cast<int>(n) - 1; i >= 0; i--) {
        int max_idx = -1;
        for (std::size_t j = 0; j < k; j++) {
            if (!partitions[j].empty()) {
                if (max_idx == -1 || partitions[j].back() > partitions[max_idx].back()) {
                    max_idx = static_cast<int>(j);
                }
            }
        }
        items[i] = partitions[max_idx].back();
        partitions[max_idx].pop_back();
    }
}
#endif

