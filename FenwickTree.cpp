#include <iostream>
#include <vector>

class FenwickTree
{
public:
    FenwickTree(const std::vector<int>& array) : mTree(array.size() + 1)
    {
        // Copy values
        // mTree[0] is not used through out FenwickTree
        for (size_t i = 0; i < array.size(); ++i)
        {
            mTree[i + 1] = array[i];
        }
        
        // Build tree
        // Update values in immediate parent upwards
        for (size_t i = 1; i < mTree.size(); ++i)
        {
            int j = i + lsb(i);
            if (j < mTree.size())
            {
                mTree[j] += mTree[i];
            }
        }
    }
    
    // Get sum from [i, j] (1 based index)
    int SumQuery(int i, int j)
    {
        return PrefixSum(j) - PrefixSum(i - 1);
    }
    
    // 1 based index
    int PrefixSum(int i)
    {
        int sum = 0;
        while (i != 0)
        {
            sum += mTree[i];
            i -= lsb(i);
        }
        return sum;
    }

    // Add value to index i (1 based)
    void Add(int i, int value)
    {
        while (i < mTree.size())
        {
            mTree[i] += value;
            i += lsb(i);
        }
    }
    
    static int lsb(int x)
    {
        // isolate the lsb
        return x & -x; 
    }
    
private:
    std::vector<int> mTree;
};

int main()
{
    const std::vector<int> v {1, 2, 3 ,4, 5};
    FenwickTree tree(v);
    std::cout << tree.SumQuery(1, 4) << '\n';
    tree.Add(1, 4);
    std::cout << tree.SumQuery(1, 4) << '\n';

