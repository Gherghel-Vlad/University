#include <vector>
#include <cassert>
#include <string>

using namespace std;

/// <summary>
/// Adds the element from the given vector
/// </summary>
/// <typeparam name="T">The template typename</typeparam>
/// <param name="v">The vector to be worked on</param>
/// <returns>The sum of all the elements from the vector</returns>
template <typename T>
T fct(std::vector<T> v) {
    if (v.size() == 0)
        throw exception();

    T res = T();

    for (auto a : v) {
        res += a;
    }

    return res;
}


void testFct() {
    vector<int> v1{ 4, 2, 1, -4 };
    assert(fct<int>(v1) == 3);
    vector<int> v2;
    try {
        fct<int>(v2);
        assert(false);
    }
    catch (std::exception&) { assert(true); }

    vector<double> v3{ 2, 10.5, 5, -10 };
    assert(fct<double>(v3) == 7.5);

    vector<string> v4{ "y", "q", "a", "m" };
    assert(fct<string>(v4) == "yqam");
}



//int main() {
//
//    testFct();
//	return 0;
//}