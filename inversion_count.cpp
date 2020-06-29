long long merge(vector<int>& v, int l1, int r1, int l2, int r2) {
    const int ll1 = l1;
    const int ll2 = l2;
    
    const int size = r1 - l1 + 1 + r2 - l2 + 1;
    vector<int> merged;
    merged.reserve(size);

    long long inversions = 0;
    while (true) {
        if (l1 <= r1 && l2 <= r2) {
            if (v[l2] >= v[l1]) {
                merged.push_back(v[l1++]);
            }
            else {
                inversions += (r1 - l1 + 1); // l2 forms inversion with all current elements in first range
                merged.push_back(v[l2++]);
            }
        }
        else if (l1 <= r1)
        {
            merged.push_back(v[l1++]);
        }
        else if (l2 <= r2) {
            merged.push_back(v[l2++]);
        }
        else
        {
            break;
        }
    }

    // copy back
    int j = 0;
    for (int i = ll1; i <= r1; ++i) {
        v[i] = merged[j++];
    }
    for (int i = ll2; i <= r2; ++i) {
        v[i] = merged[j++];
    }

    return inversions;
}

long long inversion_count(vector<int>& v, int l, int r) {
    long long inversions = 0;
    if (l >= r) // single element
        return inversions;
    
    const int mid  = l + (r - l) / 2;
    inversions += inversion_count(v, l, mid);
    inversions += inversion_count(v, mid + 1, r);
    inversions += merge(v, l, mid, mid + 1, r);
    return inversions;
}