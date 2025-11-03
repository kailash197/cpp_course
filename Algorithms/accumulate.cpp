#include <iostream>
#include <numeric> // for accumulate
#include <vector>
#include <cmath>

using namespace std;

double arithmeticMean(const vector<int>& v1){
    return std::accumulate(v1.cbegin(), v1.cend(), 0) / v1.size();
}

double geometricMean(const vector<int>& v){
    int product = std::accumulate(v.cbegin(), v.cend(), 1, [](int a, int b){return a*b;});
    return std::pow(product, 1.0 / v.size());
}

int main(){
    vector<int> v1 {1, 2, 3, 4, 5};
    cout << "The average of elements: "<<arithmeticMean(v1)<<endl;
    cout << "The geometric mean of elements: "<<geometricMean(v1)<<endl;

    cout << "sum of squares: " << std::accumulate(v1.cbegin(), v1.cend(), 0, [](int a, int b){return a +  b * b;}) << endl;
    cout << "product of squares: " << std::accumulate(v1.cbegin(), v1.cend(), 1, [](int a, int b){return a * b * b;}) << endl;

    return 0;
}
/*
The average of elements: 3
The geometric mean of elements: 2.60517
sum of squares: 55
product of squares: 14400
*/