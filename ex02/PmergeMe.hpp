#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <deque>

static int nbr_of_comps;

bool is_number(std::string str);
void merge_insert(int ac, char **av);
void printo(int n);

// std::vector<int> generateJacobSequence(size_t size);
void mergeSortV(std::vector<int> &arr, std::vector<int> &sorted);
void insertSortVector(std::vector<int> &sorted, int element);

/*

The provided code is a C++ header file [``PmergeMe.hpp``] that defines a template-based merge-insertion sort algorithm.
The file begins with include guards to prevent multiple inclusions of the same header file.
It includes several standard libraries such as `<iostream>`, `<string>`, `<vector>`, `<algorithm>`, and `<deque>` to support various functionalities used in the code.

A static integer `nbr_of_comps` is declared to keep track of the number of comparisons made during sorting.
The file also declares several function prototypes: `is_number`, `merge_insert`, and `_jacobsthal_number`.
These functions are likely defined elsewhere in the project.

The template function `_comp` is defined to compare two elements of type `T`.
It increments the `nbr_of_comps` counter each time a comparison is made and returns whether the first element is less than the second.

The main function `_merge_insertion_sort` is a template function that performs a merge-insertion sort on a container of type `T`.
It takes two parameters: a reference to the container and an integer `pair_level`.
The function first calculates the number of pairs in the container.
If there are fewer than two pairs, the function returns early.

The function then divides the container into two vectors: `main` and `pend`.
The `main` vector stores the last elements of each pair, while the `pend` vector stores any remaining elements if the number of pairs is odd.
The `main` vector is then sorted using the `_comp` function.

The function uses Jacobsthal numbers to determine the positions at which elements from `pend` should be inserted into `main`.
It iterates through the Jacobsthal sequence, inserting elements from `pend` into `main` at the appropriate positions using `std::upper_bound` to find the correct insertion points.

Finally, the function merges the sorted `main` vector back into the original container.
It iterates through the `main` vector, copying elements back into the container in their sorted order.
This completes the merge-insertion sort process.

*/

#endif