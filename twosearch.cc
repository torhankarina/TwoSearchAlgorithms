//***************************************************************************
//
// Karina Torhan
// Z2111032
// CSCI 340 - OPE1 20268
// Assignment 01 - Two Search Algorithms
// Due Date: 9/8/26, 5:00 PM
// I certify that this is my own work and where appropriate an extension
// of the starter code provided for the assignment.
//
//***************************************************************************
#include "twosearch.h"

#include <getopt.h>
#include <cstdlib>

#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>

/**
 * see:
 * https://en.wikipedia.org/wiki/Usage_message
 * https://www.ibm.com/docs/en/aix/7.2?topic=commands-usage-statements
 *
 * @param a0 The value of argv[0] (the name of the command) so that it
 *   can be printed.
 *
 * @note This function will terminate the application via exit(1).
 ******************************************************************************/
static void usage(const char *a0)
{
    std::cerr << "Usage: " << a0 << " [-l rand_low] [-h rand_high] [-a a_size] [-b b_size] [-x a_seed] [-y b_seed] [-c print_cols] [-w col_width]" << std::endl;
    std::cerr << "    rand_low   = rand() low bound (default=1)" << std::endl;
    std::cerr << "    rand_high  = rand() high bound (default=1000)" << std::endl;
    std::cerr << "    a_size     = size of vector A (default=200)" << std::endl;
    std::cerr << "    b_size     = size of vector B (default=100)" << std::endl;
    std::cerr << "    a_seed     = random seed for vector A (default=1)" << std::endl;
    std::cerr << "    b_seed     = random seed for vector B (default=3)" << std::endl;
    std::cerr << "    print_cols = number of colums per line (default=16)" << std::endl;
    std::cerr << "    col_width  = printed column value width (default=4)" << std::endl;
    exit(1);
} // End of usage()

//Assign random values to elements of vec within the range [lo, hi].

void init_vector(std::vector<int> &vec, int seed, int lo, int hi)
{
    srand(seed);
    for (size_t i = 0; i < vec.size(); ++i)
    {
        vec[i] = rand() % (hi - lo + 1) + lo;
    }
}

//Print the contents of a vector formatted into tabular columns.

void print_vector(const std::vector<int> &v, int print_cols, int col_width)
{
    int dash_len = (col_width + 3) * print_cols + 1;
    std::string dashes(dash_len, '-');

    std::cout << dashes << "\n";

    size_t col_count = 0;
    for (size_t i = 0; i < v.size(); ++i)
    {
        if (col_count == 0)
        {
            std::cout << "|";
        }

        std::cout << std::setw(col_width) << v[i] << " |";
        col_count++;

        if (col_count == static_cast<size_t>(print_cols))
        {
            std::cout << "\n";
            col_count = 0;
        }
    }

    // If the final row has unfilled columns, pad them out
    if (col_count > 0)
    {
        while (col_count < static_cast<size_t>(print_cols))
        {
            std::cout << std::string(col_width + 1, ' ') << " |";
            col_count++;
        }
        std::cout << "\n";
    }

    std::cout << dashes << "\n";
}

//Sort the elements of vector v in ascending order using std::sort.

void sort_vector(std::vector<int> &v)
{
    std::sort(v.begin(), v.end());
}

//Linearly search for element x within vector v using std::find.

bool linear_search(const std::vector<int> &v, int x)
{
    return std::find(v.begin(), v.end(), x) != v.end();
}

//Binary search for element x within sorted vector v using std::binary_search.

bool binary_search(const std::vector<int> &v, int x)
{
    return std::binary_search(v.begin(), v.end(), x);
}

//Generic search counting how many elements of v2 appear in v1 using function pointer p.

int search_vector(const std::vector<int> &v1, const std::vector<int> &v2, bool (*p)(const std::vector<int> &, int))
{
    int successful_count = 0;
    for (size_t i = 0; i < v2.size(); ++i)
    {
        if (p(v1, v2[i]))
        {
            successful_count++;
        }
    }
    return successful_count;
}

//Print percentage of successful searches formatted to two decimal places.

void print_stat(int found, int total)
{
    double percent = (total > 0) ? (static_cast<double>(found) / total) * 100.0 : 0.0;
    std::cout << "Percent of Successful Searches = "
              << std::fixed << std::setprecision(2) << percent << "%\n";
}

/**
 * Parse the command-line args, create and sort vector A, create vector B,
 * search vector A for those elements appearing in vector B using both
 * a linear and binary search, and print the hit-rate (the percentage of
 * items in B that have been located in A.)
 *
 * If an invalid command-line arg is encountered, print a Usage statement
 * and terminate with an exit-status of 1.
 *
 * @return zero
 ******************************************************************************/
int main(int argc, char **argv)
{
    // Demonstrate the use of getopt() to override default config parameters
    int rand_low = 1;
    int rand_high = 1000;
    int a_size = 200;
    int b_size = 100;
    int a_seed = 1;
    int b_seed = 3;
    int print_cols = 16;
    int col_width = 4;

    int opt;
    while ((opt = getopt(argc, argv, "a:b:c:h:l:w:x:y:")) != -1)
    {
        switch(opt)
        {
        case 'a':
            a_size = std::stoi(optarg);
            break;
        case 'b':
            b_size = std::stoi(optarg);
            break;
        case 'c':
            print_cols = std::stoi(optarg);
            break;
        case 'h':
            rand_high = std::stoi(optarg);
            break;
        case 'l':
            rand_low = std::stoi(optarg);
            break;
        case 'w':
            col_width = std::stoi(optarg);
            break;
        case 'x':
            a_seed = std::stoi(optarg);
            break;
        case 'y':
            b_seed = std::stoi(optarg);
            break;
        default:
            usage(argv[0]);
        }
    }

    // Make sure there are not any more arguments (after the optional ones)
    if (optind < argc)
        usage(argv[0]);

    // 1. Define two vectors (A and B) with sizes a_size and b_size
    std::vector<int> A(a_size);
    std::vector<int> B(b_size);

    // 2. Pass A to init_vector
    init_vector(A, a_seed, rand_low, rand_high);

    // 3. Pass B to init_vector
    init_vector(B, b_seed, rand_low, rand_high);

    // 4. Print elements of A
    std::cout << "A vector:\n";
    print_vector(A, print_cols, col_width);

    // 5. Sort elements of A
    sort_vector(A);

    // 6. Print elements of A after sorting
    std::cout << "A vector sorted:\n";
    print_vector(A, print_cols, col_width);

    // 7. Print elements of B
    std::cout << "B vector:\n";
    print_vector(B, print_cols, col_width);

    // 8. Search for each value in B in A using linear search
    int linear_found = search_vector(A, B, linear_search);

    // 9. Print statistical values for linear search
    std::cout << "Linear Search: ";
    print_stat(linear_found, b_size);

    // 10. Search for each value in B in A using binary search
    int binary_found = search_vector(A, B, binary_search);

    // 11. Print statistical values for binary search
    std::cout << "Binary Search: ";
    print_stat(binary_found, b_size);

    return 0;
} // End of main()