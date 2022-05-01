
#include "Helper.hpp"

//
//
//
void classify() {
    
    vector<pair<string, double>> list;
    for (auto& e: MEMO.StockList)
        list.push_back({e.first, e.second.surprise_pct_});
    sort(list.begin(), list.end(), [](const auto& p1, const auto& p2){ return p1.second > p2.second; } );
    
    int N = (int)MEMO.StockList.size();
    int length = round(N / 3.0);
    
    MEMO.Beat.resize(length);
    for (int i = 0; i < length; i++) {
        MEMO.Beat[i] = list[i].first;
        MEMO.StockList[MEMO.Beat[i]].group_ = BEAT;
    }
    
    MEMO.Meet.resize(length);
    for (int i = 0; i < length; i++) {
        MEMO.Meet[i] = list[length + i].first;
        MEMO.StockList[MEMO.Meet[i]].group_ = MEET;
    }
    
    MEMO.Miss.resize(N - 2*length);
    for (int i = 0; i < N - 2*length; i++) {
        MEMO.Miss[i] = list[2*length + i].first;
        MEMO.StockList[MEMO.Miss[i]].group_ = MISS;
    }
}


//
//    Take AAPL for example, its earning announcement date is July 27th, 2021
//
//              2021-01-01    2021-01-02    ...    ...    2021-07-27   ...   ...   2022-03-30    2022-03-31
//       index       0           1                            170                      300           301
//
//
//    The largest valid N for AAPL is min( 170-0, 301-170 )
//    The whole map is looped through to find the maximal N that fits all stocks
//
void calculate_max_N() {
    int N = 999;
    for (const auto& e: MEMO.StockList) {
        if (e.second.valid_) {
            int rec = e.second.earn_ann_date_index_;
            int comp = min(rec, static_cast<int>(e.second.daily_price_.size() - rec - 1));
            N = min(N, comp);
            if (comp < 60)
                cout << e.first << " " << rec << " " << e.second.daily_price_.size() - rec - 1 << endl;
        }
    }
    MEMO.N_MAX = N;
}


VectorS random_select(const VectorS& vt, int n) {
    std::set<string> set_;
    int m = (int)vt.size();
    while (set_.size() < n) {
        string tmp = vt[rand() % m];
        if (set_.find(tmp) == set_.end() && MEMO.StockList[tmp].valid_)
            set_.insert(tmp);
    }
    return VectorS(set_.begin(), set_.end());
}


void bootstrap(int N) {
    
    Matrix3D result(3, Matrix2D(4, VectorD(2*N, 0))), tmp_result(3, Matrix2D(4, VectorD(2*N, 0)));
    
    map<Group, VectorS*> group;
    group[MISS] = &MEMO.Miss;
    group[MEET] = &MEMO.Meet;
    group[BEAT] = &MEMO.Beat;

    for (int i=0; i<40; i++) {
        
        for (const auto& g: group) {
            
            VectorS selected_stocks = random_select(*g.second);
            VectorD AAR(2*N, 0), CAAR(2*N, 0);
            
            for (const auto& ticker: selected_stocks) {
                MEMO.StockList[ticker].calculate_returns(N);
                int start = MEMO.StockList[ticker].earn_ann_date_index_ - N;
            
                for (int j=0; j<2*N; j++) {
                    AAR[j] += MEMO.StockList[ticker].daily_ret_[j] - MEMO.StockList["IWV"].daily_ret_[start + j];
                    CAAR[j] += MEMO.StockList[ticker].cumulative_ret_[j] - MEMO.StockList["IWV"].cumulative_ret_[start + j];
                }
                if (start > 0)
                    CAAR += MEMO.StockList["IWV"].cumulative_ret_[start-1];
            }
        
            tmp_result[g.first][0] += AAR / 80;
            tmp_result[g.first][1] += (AAR / 80) ^ 2 ;
            tmp_result[g.first][2] += CAAR / 80;
            tmp_result[g.first][3] += (CAAR / 80) ^ 2 ;
        }
    }
    
    tmp_result = tmp_result / 40;
    
    for (int i=0; i<3; i++) {
        for (int j=0; j<4; j+=2)
            result[i][j] = tmp_result[i][j];
        for (int j=1; j<4; j+=2)
            result[i][j] = sqrt( tmp_result[i][j] - (tmp_result[i][j-1] ^ 2) ) / sqrt(40-1);
    }
    
    MEMO.Result = result;
    
}


bool is_number(const string& s) {
    return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}
