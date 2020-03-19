class SumSegmentTree 
{
public:
	SumSegmentTree(const std::vector<int>& v) : tree(4 * v.size())
	{
		Build(v, 0, 0, v.size() - 1);
	}

	// Query the sum between index l and r
	int SumQuery(int l, int r) 
	{
		const int size = tree.size() / 4;
		return SumQueryHelper(l, r, 0, 0, size - 1);
	}

	// increment the value at index i by val
	void PointUpdate(int i, int val)
	{
		const int size = tree.size() / 4;
		PointUpdateHelper(i, val, 0, 0, size - 1);
	}

	// increment the value b/w indices l and r by val
	void RangeUpdate(int l, int r, int val)
	{
		// TODO
	}

private:
	static int LeftChild(int i) { return 2 * i + 1; } 
	static int RightChild(int i) { return 2 * 2 + 1; }

	void Build(const std::vector<int>& v, int treeIndex, int l, int r) 
	{
		// base case, single element
		if (l == r)
		{
			tree[treeIndex] = v[l];
		}
		else 
		{
			const int mid = (l + r) / 2;
			const auto leftChild = LeftChild(treeIndex);
			const auto rightChild = RightChild(treeIndex);
			// left
			Build(v, leftChild, l, mid);
			//right
			Build(v, rightChild, mid + 1, r);
			// root
			tree[treeIndex] = tree[leftChild] + tree[rightChild];
		}
	}

	int SumQueryHelper(int l, int r, int treeIndex, int responsiblityL, int responsiblityR) 
	{
		if (r < responsiblityL || l > responsiblityR)
		{
			return 0;
		}
		if (l <= responsiblityL && r >= responsiblityR)
		{
			return tree[treeIndex];
		}

		const int mid = (responsiblityL + responsiblityR) / 2;
		const int leftSumQuery = SumQueryHelper(l, r, LeftChild(treeIndex), responsiblityL, mid);
		const int RightSumQuery = SumQueryHelper(l, r, RightChild(treeIndex), mid + 1, responsiblityR);
		return leftSumQuery + RightSumQuery;
	} 

	int RangeUpdateHelper(int l, int r, int val, int treeIndex, int responsiblityL, int responsiblityR) 
	{
		if (responsiblityL == responsiblityR && responsiblityL >= l && responsiblityL <= r)
		{
			tree[treeIndex] += val;
		}
		else
		{
			const int mid = (responsiblityL + responsiblityR) / 2;
			RangeUpdateHelper(l, r, val, LeftChild(treeIndex), responsiblityL, mid);
			RangeUpdateHelper(l, r, val, RightChild(treeIndex), mid + 1, responsiblityR);

			tree[treeIndex] += tree[LeftChild(treeIndex)] + tree[RightChild(treeIndex)];
		}
	}

	void PointUpdateHelper(int i, int val, int treeIndex, int responsiblityL, int responsiblityR)
	{
		if (responsiblityL == responsiblityR)
		{
			tree[treeIndex] += val;
		}
		else
		{
			const int mid = (responsiblityL + responsiblityR) / 2;
			if (i <= mid)
			{
				PointUpdateHelper(i, val, LeftChild(treeIndex), responsiblityL, mid);
			}
			else
			{
				PointUpdateHelper(i, val, RightChild(treeIndex), mid + 1, responsiblityR);
			}

			tree[treeIndex] += val;
		}
	}

private:
	std::vector<int> tree;
};