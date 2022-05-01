
#ifndef Stock_hpp
#define Stock_hpp

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include "Container.hpp"
using std::cout, std::setw, std::fixed, std::setprecision;


enum Group { MISS, MEET, BEAT, NA };
const std::string GROUP[4] {  "MISS", "MEET", "BEAT", "NA" };

class Stock {
public:
    
    // member variables
    std::string earn_ann_date_, period_ending_;
    double estimated_earn_, reported_earn_, surprise_, surprise_pct_;
    int earn_ann_date_index_;        // the index of the position where the stock price on the earning announcement date is stored in daily_price_
                                                                       
    bool valid_;                     // an indicator of whether this stock can be randomly selected
    Group group_;                    // earning group
    VectorD daily_price_, daily_ret_, cumulative_ret_;
    inline static VectorS date_;
    
    // member functions
    Stock() = default;
    Stock(std::string, std::string, double, double, double, double);
    void calculate_returns();
    void calculate_returns(int N);
    
    friend std::ostream& operator<<(std::ostream& out, Stock& stock);
};


#endif /* Stock_hpp */
