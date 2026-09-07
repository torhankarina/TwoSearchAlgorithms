#ifndef twosearch_H
#define twosearch_H

// Only include those headers that are required by the rest of contents 
// of this header file.

#include <vector>

// No using statements here.

void init_vector(std::vector<int> &vec, int seed, int lo, int hi);
void print_vector(const std::vector<int> &v, int print_cols, int col_width);
void sort_vector(std::vector<int> &v);
int search_vector(const std::vector<int> &v1, const std::vector<int> &v2, bool (*p)(const std::vector<int> &, int));
void print_stat(int found, int total);
bool linear_search(const std::vector<int> &v, int x);
bool binary_search(const std::vector<int> &v, int x);

#endif
