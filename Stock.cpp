
#include "Stock.hpp"


Stock::Stock(std::string earn_ann_date, std::string period_ending, double estimated_earn, double reported_earn, double surprise, double surprise_pct):
    earn_ann_date_(earn_ann_date), period_ending_(period_ending), estimated_earn_(estimated_earn), reported_earn_(reported_earn), surprise_(surprise), surprise_pct_(surprise_pct), earn_ann_date_index_(0), group_(NA)  { }


void Stock::calculate_returns() {
    
    int n = (int)daily_price_.size() - 1;
    daily_ret_.resize(n);
    cumulative_ret_.resize(n);
    
    double cum = 0.0;
    for (int i = 0; i < n; i++) {
        daily_ret_[i] = (daily_price_[i+1] - daily_price_[i]) / daily_price_[i];
        cum += daily_ret_[i];
        cumulative_ret_[i] = cum;
    }
}


void Stock::calculate_returns(int N) {
    
    if ( daily_ret_.size() != 2 * N ) {
        
        daily_ret_.resize(2 * N);
        cumulative_ret_.resize(2 * N);
        
        int start = earn_ann_date_index_ - N + 1;
        double cum = 0.0;
        for (int i = 0; i < 2*N; i++) {
            daily_ret_[i] = (daily_price_[start+i] - daily_price_[start+i-1]) / daily_price_[start+i-1];
            cum += daily_ret_[i];
            cumulative_ret_[i] = cum;
        }
    }
}


std::ostream& operator<<(std::ostream& out, Stock& stock) {
    
    stock.calculate_returns();
    int n = (int)stock.daily_price_.size();
    int start = 314 - n;
    
    out << fixed;
    out << "     Date           Price        Cum. Return   "  << endl << endl;
    
    for (int i = 0; i < n; i ++) {
        out << "  " << stock.date_[start+i] << setw(13) << setprecision(2) << stock.daily_price_[i] ;
        if (i > 0)
            out << setw(16) << setprecision(2) << 100.0 * stock.cumulative_ret_[i-1] << "%";
        out << endl;
    }
    out << endl;
    
    out << "                      Group : " << setw(12) << GROUP[stock.group_] << endl;
    out << "  Earning Announcement Date : " << setw(12) << stock.earn_ann_date_ << endl;
    out << "              Period Ending : " << setw(12) << stock.period_ending_ << endl;
    out << "         Estimated Earnings : " << setw(12) << stock.estimated_earn_ << endl;
    out << "          Reported Earnings : " << setw(12) << stock.reported_earn_ << endl;
    out << "                   Surprise : " << setw(12) << stock.surprise_ << endl;
    out << "                 Surprise % : " << setw(12) << stock.surprise_pct_ << endl;
    
    return out;
}
