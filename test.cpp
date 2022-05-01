
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "curl/curl.h"
#include "Gnuplot.hpp"

using namespace std;

/* test the running time
 
#include <chrono>
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;
 
*/



int main() {
    
    
    // auto t1 = high_resolution_clock::now();
    
    vector<double> v1{1,2,3,4,3,3,2,4}, v2{2,4,4,4,5,6,3,2}, v3{1,1,1,1,6,6,6,6};
    
    plotResults(v1, v2, v3);
    
    /*
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> dt = t2 - t1;
    cout << dt.count() << endl;
    */
    
    return 0;
}
