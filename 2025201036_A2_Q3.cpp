#include <iostream>
#include <algorithm> 
using namespace std;

// fun to get the sum of frequencies from index i to j using prefix sums
long long getFreqSum(long long* prefixSum, int i, int j) {
    if (i > j) {
        return 0LL;
    }
    return prefixSum[j] - prefixSum[i - 1];
}

// for calculating the ideal search plan without robot cst
void theIdealSearchPlan() {
    int n;
    cin >> n;
    long long* freq = new long long[n + 1];
    long long* freqPrefixSum = new long long[n + 1];
    freqPrefixSum[0] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> freq[i];
        freqPrefixSum[i] = freqPrefixSum[i - 1] + freq[i];
    }

    long long** dpp = new long long*[n + 2];
    for (int i = 0; i <= n + 1; ++i) {
        dpp[i] = new long long[n + 2]();
    }

    for (int len = 1; len <= n; ++len) {
        for (int i = 1; i <= n - len + 1; ++i) {
            int j = i + len - 1;
            dpp[i][j] = -1;
            for (int k = i; k <= j; ++k) {
                long long current_cost = dpp[i][k - 1] + dpp[k + 1][j];
                if (dpp[i][j] == -1 || current_cost < dpp[i][j]) {
                    dpp[i][j] = current_cost;
                }
            }
            dpp[i][j] += getFreqSum(freqPrefixSum, i, j);
        }
    }

    cout << dpp[1][n] << endl;

    for (int i = 0; i <= n + 1; ++i) delete[] dpp[i];
    delete[] dpp;
    delete[] freq;
    delete[] freqPrefixSum;
}

// for calculating the ideal search plan including robot cost
long long part2Rec(int i, int j, int parentPos, int n, long long* freqPrefixSum, long long*** m) {
    if (i > j) {
        return 0;
    }

    if (m[i][j][parentPos] != -1) {
        return m[i][j][parentPos];
    }

    long long min_cost = -1;

    for (int k = i; k <= j; ++k) {

        long long costFromParent = getFreqSum(freqPrefixSum, i, j) * abs(k - parentPos);

        long long leftCost = part2Rec(i, k - 1, k, n, freqPrefixSum, m);
        long long rightCost = part2Rec(k + 1, j, k, n, freqPrefixSum, m);
        
        long long current_total_cost = costFromParent + leftCost + rightCost;

        if (min_cost == -1 || current_total_cost < min_cost) {
            min_cost = current_total_cost;
        }
    }
    
    return m[i][j][parentPos] = min_cost;
}

void IncludingRobotCost() {
    int n;
    cin >> n;
    long long* freq = new long long[n + 1];
    long long* freqPrefixSum = new long long[n + 1];
    freqPrefixSum[0] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> freq[i];
        freqPrefixSum[i] = freqPrefixSum[i - 1] + freq[i];
    }
    
    long long*** m = new long long**[n + 2];
    for(int i = 0; i < n + 2; ++i) {
        m[i] = new long long*[n + 2];
        for (int j = 0; j < n + 2; ++j) {
            m[i][j] = new long long[n + 2];
            for (int k = 0; k < n + 2; ++k) {
                m[i][j][k] = -1;
            }
        }
    }
    
    cout << part2Rec(1, n, 0, n, freqPrefixSum, m) << endl;

    for (int i = 0; i < n + 2; ++i) {
        for (int j = 0; j < n + 2; ++j) {
            delete[] m[i][j];
        }
        delete[] m[i];
    }
    delete[] m;
    delete[] freq;
    delete[] freqPrefixSum;
}

void fullRealisticModel() {
    int n;
    cin >> n;
    long long* freq = new long long[n + 1];
    long long* freqPrefixSum = new long long[n + 1];
    freqPrefixSum[0] = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> freq[i];
        freqPrefixSum[i] = freqPrefixSum[i - 1] + freq[i];
    }
    long long alpha, beta, gamma;
    cin >> alpha >> beta >> gamma;

    long long*** dppCost = new long long**[n + 2];
    int*** root = new int**[n + 2];
    for (int i = 0; i <= n + 1; ++i) {
        dppCost[i] = new long long*[n + 2];
        root[i] = new int*[n + 2];
        for (int j = 0; j <= n + 1; ++j) {
            dppCost[i][j] = new long long[2]();
            root[i][j] = new int[2]();
        }
    }

    for (int len = 1; len <= n; ++len) {
        for (int i = 1; i <= n - len + 1; ++i) {
            int j = i + len - 1;
            for (int dir = 0; dir < 2; ++dir) {
                dppCost[i][j][dir] = -1;
                for (int k = i; k <= j; ++k) {
                    long long leftCost = (k > i) ? dppCost[i][k - 1][1] : 0;
                    long long rightCost = (k < j) ? dppCost[k + 1][j][0] : 0;
                    long long scanCost = beta * getFreqSum(freqPrefixSum, i, j);
                    long long edgeCost = 0;
                    if (k > i) {
                        int left_root = root[i][k - 1][1];
                        long long sum_f = getFreqSum(freqPrefixSum, i, k - 1);
                        edgeCost += sum_f * alpha * abs(k - left_root);
                        if (dir == 0) edgeCost += sum_f * gamma;
                    }
                    if (k < j) {
                        int right_root = root[k + 1][j][0];
                        long long sum_f = getFreqSum(freqPrefixSum, k + 1, j);
                        edgeCost += sum_f * alpha * abs(k - right_root);
                        if (dir == 1) edgeCost += sum_f * gamma;
                    }
                    long long currTotal = leftCost + rightCost + scanCost + edgeCost;
                    if (dppCost[i][j][dir] == -1 || currTotal < dppCost[i][j][dir]) {
                        dppCost[i][j][dir] = currTotal;
                        root[i][j][dir] = k;
                    }
                }
            }
        }
    }

    long long return_cost = 0;
    for (int i = 1; i <= n; ++i) {
        return_cost += freq[i] * alpha * i;
    }
    long long minTreeCost = dppCost[1][n][0];
    long long firstMoveCost = getFreqSum(freqPrefixSum, 1, n) * alpha * abs(root[1][n][0] - 0);
    long long finalCost = minTreeCost + firstMoveCost + return_cost;
    cout << finalCost << endl;
    
    for (int i = 0; i <= n + 1; ++i) {
        for (int j = 0; j <= n + 1; ++j) { delete[] dppCost[i][j]; delete[] root[i][j]; }
        delete[] dppCost[i];
        delete[] root[i];
    }
    delete[] dppCost;
    delete[] root;
    delete[] freq;
    delete[] freqPrefixSum;
}


int main() {
    int query_type;
    while(cin >> query_type) {
        if (query_type == 1) {
            theIdealSearchPlan();
        } else if (query_type == 2) {
            IncludingRobotCost(); 
        } 
        // else if (query_type == 3) {
        //      fullRealisticModel();
        // }
    }
    return 0;
}
