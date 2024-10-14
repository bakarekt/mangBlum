#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// Hàm kiểm tra xem một số có phải là số nguyên tố hay không
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return false;
    }
    return true;
}

// Hàm tạo ra các số Blum (tích của 2 số nguyên tố khác nhau)
vector<int> generateBlumNumbers(int N) {
    vector<int> primes;
    
    for (int i = 2; i <= sqrt(N); i++) {
        if (isPrime(i)) {
            primes.push_back(i);
        }
    }
    
    vector<int> blumNumbers;
    
    for (size_t i = 0; i < primes.size(); i++) {
        for (size_t j = i; j < primes.size(); j++) {
            int blumNumber = primes[i] * primes[j];
            if (blumNumber < N) {
                // Kiểm tra xem số Blum này đã có trong vector chưa
                if (find(blumNumbers.begin(), blumNumbers.end(), blumNumber) == blumNumbers.end()) {
                    blumNumbers.push_back(blumNumber);
                }
            }
        }
    }
    
    sort(blumNumbers.begin(), blumNumbers.end());  // Sắp xếp để tìm kiếm dễ hơn
    return blumNumbers;
}

// Hàm tìm tất cả các cặp số Blum có tổng cũng là số Blum
vector<pair<int, int>> findBlumPairsWithBlumSum(const vector<int>& blumNumbers, int N) {
    vector<pair<int, int>> result;
    
    for (size_t i = 0; i < blumNumbers.size(); i++) {
        for (size_t j = i + 1; j < blumNumbers.size(); j++) {
            int sum = blumNumbers[i] + blumNumbers[j];
            if (sum < N && find(blumNumbers.begin(), blumNumbers.end(), sum) != blumNumbers.end()) {
                result.emplace_back(blumNumbers[i], blumNumbers[j]);
            }
        }
    }
    
    return result;
}

// Hàm kiểm tra xem số Blum M có trong dãy số Blum hay không
bool isBlumNumberExist(const vector<int>& blumNumbers, int M) {
    return binary_search(blumNumbers.begin(), blumNumbers.end(), M);
}

int main() {
    int N, M;
    cout << "Nhập giá trị N: ";
    cin >> N;
    
    // Tạo dãy số Blum nhỏ hơn N
    vector<int> blumNumbers = generateBlumNumbers(N);
    
    cout << "Dãy số Blum nhỏ hơn " << N << " là:\n";
    for (int num : blumNumbers) {
        cout << num << " ";
    }
    cout << endl;
    
    // Tìm các cặp số Blum có tổng cũng là số Blum
    vector<pair<int, int>> blumPairs = findBlumPairsWithBlumSum(blumNumbers, N);
    cout << "Các cặp số Blum có tổng cũng là số Blum:\n";
    for (auto& pair : blumPairs) {
        cout << pair.first << " + " << pair.second << endl;
    }
    
    // Kiểm tra xem một số Blum M có trong dãy không
    cout << "Nhập số Blum M để kiểm tra: ";
    cin >> M;
    
    if (isBlumNumberExist(blumNumbers, M)) {
        cout << M << " là số Blum có trong dãy.\n";
    } else {
        cout << M << " không có trong dãy số Blum.\n";
    }
    
    return 0;
}