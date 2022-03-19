#include <vector>
#include <cstdio>
#include <string>
#include <iostream>
#include <cassert>

using namespace std;

/// <summary>
/// Returns the maximum value from a given vector
/// </summary>
/// <typeparam name="T">The type of elements from the vector</typeparam>
/// <param name="v">The vector vien</param>
/// <returns>The maximum value from the vector</returns>
/// throws exception if there are no elements in the given vector
template <typename T>
T fct(vector<T> v) {
    if (v.size() == 0) {
        throw exception();
    }

    T maxElem = v[0];

    for (int i = 1; i < v.size(); i++) {
        if (v[i] > maxElem) {
            maxElem = v[i];
        }
    }

    return maxElem;

}


void testFct() {
    vector<int> v1{ 4, 2, 1, 6, 3, -4 };
    assert(fct<int>(v1) == 6);
    vector<int> v2;
    try {
        fct<int>(v2);
        assert(false);
    }
    catch (std::exception&) { assert(true); }

    vector<double> v3{ 2, 10.5, 6.33, -100, 9, 1.212 };
    assert(fct<double>(v3) == 10.5);

    vector<string> v4{ "y", "q", "a", "m" };
    assert(fct<string>(v4) == "y");
}


//int main() {
//
//    testFct();
//	return 0;
//}