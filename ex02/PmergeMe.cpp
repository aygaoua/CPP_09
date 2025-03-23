#include "PmergeMe.hpp"

bool is_number(std::string str) {
	if (str[0] == '+' || str == "-0")
		str.erase(0, 1);
	if (!std::isdigit(str[0]))
		return false;
	for (unsigned long i = 0; i < str.length(); i++) {
		if (!std::isdigit(str[i]))
			return false;
	}
	return true;
}

void printo(int n) {
    std::cout << n << " ";
}



std::vector<int> generateJacobSequence(size_t size)
{
	std::vector<int> jacob;
	jacob.push_back(0);
	if (size == 0)
		return jacob;
	jacob.push_back(1);
	for (size_t i = 2; i <= size; ++i)
	{
		jacob.push_back(jacob[i - 1] + 2 * jacob[i - 2]);
	}
	return jacob;
}

void insertSortVector(std::vector<int> &sorted, int element)
{
	std::vector<int>::iterator pos = std::lower_bound(sorted.begin(), sorted.end(), element);
	sorted.insert(pos, element);
}

void mergeSortV(std::vector<int> &arr, std::vector<int> &sorted)
{
	if (!arr.size())
		return;
	int unpaired = arr.back();

	if (arr.size() == 1)
	{
		insertSortVector(sorted, arr[0]);
		return;
	}
	std::vector<int> larger;
	std::vector<int> smaller;
	std::vector<int> tmpSorted;

	for (size_t i = 0; i + 1 < arr.size(); i += 2)
	{
		if (arr[i] > arr[i + 1])
		{
			larger.push_back(arr[i]);
			smaller.push_back(arr[i + 1]);
		}
		else
		{
			larger.push_back(arr[i + 1]);
			smaller.push_back(arr[i]);
		}
	}
	if (smaller.size() > 2)
	{
		larger.insert(larger.begin(), smaller.front());
		smaller.erase(smaller.begin());
	}
	if (!larger.empty())
		mergeSortV(larger, tmpSorted);
	if (arr.size() % 2 != 0)
		insertSortVector(tmpSorted, unpaired);
	if (!smaller.empty())
		mergeSortV(smaller, tmpSorted);
	std::vector<int> jacob = generateJacobSequence(tmpSorted.size());
    std::cout << "jacob : ";
	for (size_t i = 0; i < jacob.size(); i++)
	{
		if (static_cast<size_t>(jacob[i]) < tmpSorted.size())
		{
            std::cout << i << " ";
			insertSortVector(sorted, tmpSorted[jacob[i]]);
			tmpSorted.erase(tmpSorted.begin() + jacob[i]);
			jacob = generateJacobSequence(tmpSorted.size());
		}
	}
    std::cout << std::endl;
	for (size_t i = 0; i < tmpSorted.size(); i++)
		insertSortVector(sorted, tmpSorted[i]);
}


void merge_insert(int ac, char **av) {
    std::vector<int> vectorContainer;
    std::deque<int> dequeContainer;
    for (int i = 1; i < ac; i++) {
        std::string str(av[i]);
        if (is_number(str)) {
                char *end_ptr;
                double value = strtod(str.c_str(), &end_ptr);
                if (value > std::numeric_limits<int>::max() || value < std::numeric_limits<int>::min())
                {
                    std::cerr << "Error: not an positive integer" << std::endl;
                    exit(1);
                }
                dequeContainer.push_back(value);
                vectorContainer.push_back(value);
        } else {
            std::cerr << "Invalid value: `" << str << "`" <<  std::endl;
            exit (1);
        }

    }
    std::cout << "Before:" << std::endl;
    std::for_each(vectorContainer.begin(), vectorContainer.end(), printo);
    std::cout << std::endl;
    // std::for_each(dequeContainer.begin(), dequeContainer.end(), printo);
    // std::cout << std::endl;

    std::vector<int> sorted;
    mergeSortV(vectorContainer, sorted);
    vectorContainer = sorted;
    // mergeInsertionSort(dequeContainer);

    std::cout << "After:" << std::endl;
    std::for_each(vectorContainer.begin(), vectorContainer.end(), printo);
    std::cout << std::endl;

    // std::for_each(dequeContainer.begin(), dequeContainer.end(), printo);
    // std::cout << std::endl;
}

