
#include <iostream>
#include <thread>
#include <chrono>
#include "Stock.hpp"
#include "Helper.hpp"
#include "LoadData.hpp"
#include "Gnuplot.hpp"
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;
using std::cin;


// wrap all global variables in a struct
_MEMO_ MEMO;

int main() {
    
    srand((unsigned)time(NULL));
    
    // read earning csv file and save all information into the map ( MEMO.StockList )
    populateSymbolVector();
    
    // divide all stocks into three vector ( MEMO.Beat / MEMO.Meet / MEMO.Miss )
    classify();
    
    auto t1 = high_resolution_clock::now();
    // use multi-thread to download price data of all stocks + IWV
    cout << "  ---------  Downloading Price Data  --------- " << endl << endl;
    MEMO._cnt = 0;
    MEMO.Beat.push_back("IWV");
    std::thread thread1(download, &MEMO.Beat, &MEMO.StockList);
    std::thread thread2(download, &MEMO.Meet, &MEMO.StockList);
    std::thread thread3(download, &MEMO.Miss, &MEMO.StockList);
    thread1.join();
    thread2.join();
    thread3.join();
    MEMO.Beat.pop_back();
    MEMO.StockList["IWV"].valid_ = false;
    MEMO.StockList["IWV"].calculate_returns();
    
    auto t2 = high_resolution_clock::now();
    duration<double, std::milli> dt = t2 - t1;
    cout << endl << "  Downloading takes "  << static_cast<int>(dt.count()) / 1000 << " seconds !" << endl << endl;
    
    // calculate the largest valid N
    calculate_max_N();
    
    
    bool state = true;
    string input;
    int option;
    
    while (state) {

        cout << "  ----------------------------------------------- " << endl;
        cout << "  | 1. Set N                                    |" << endl;
        cout << "  | 2. Get information of a single stock        |" << endl;
        cout << "  | 3. Display AAR, AAR-STD, CAAR and CAAR-STD  | " << endl;
        cout << "  | 4. Plot CAAR                                |" << endl;
        cout << "  | 5. Exit the program                         |" << endl;
        cout << "  ----------------------------------------------- " << endl << endl;
        cout << "  Choose one option : ";
        cin >> input;
        
        if ( input.size() != 1 || input[0] < '1' || input[0] > '5') {
            cout << endl << "  Invalid Input !" << endl << endl;
            continue;
        }
        cout << endl;
        
        option = std::stoi(input);
        string ticker, n_;

        switch (option) {
            
            case 1: {
                cout << "  Enter N (60 <= N <= " << MEMO.N_MAX << "): ";
                cin >> n_;
                while (!is_number(n_) || std::stoi(n_) < 60 || std::stoi(n_) > MEMO.N_MAX) {
                    cout << "  Invalid N ! Please enter again : ";
                    cin >> n_;
                }
                MEMO.N = std::stoi(n_);
                cout << endl << "  -------------   Bootsctrapping   -------------- " << endl ;
                
                t1 = high_resolution_clock::now();
                bootstrap(MEMO.N);
                t2 = high_resolution_clock::now();
                duration<double, std::milli> dt = t2 - t1;
                cout << endl << "  Bootstrapping takes " << static_cast<int>(dt.count()) / 1000 << " seconds !" << endl;
                
                break;
            }
            
            case 2:
                cout << "  Enter the stock ticker or EXIT back to the menu : ";
                cin >> ticker;
                while ( MEMO.StockList.find(ticker) == MEMO.StockList.end() && ticker != "EXIT" ) {
                    cout << endl << "  \"" << ticker << "\" not found ! Please enter the ticker again : ";
                    cin >> ticker;
                }
                if (ticker != "EXIT")
                    cout << endl << endl << MEMO.StockList[ticker] << endl;
                break;

            case 3:
                if (MEMO.N < 60 || MEMO.N > MEMO.N_MAX) {
                    cout << "  Please enter a valid N first ! "<< endl;
                    break;
                }
                cout << "  Choose one group ? ( 0 : MISS, 1 : MEET, 2 : BEAT ) ";
                cin >> n_;
                while (n_.size() != 1 || n_[0] < '0' || n_[0] > '2') {
                    cout << endl << "  Invalid Input !" << endl << endl;
                    cin >> n_;
                }
                
                cout << "-----------------------------------------------------------------" << endl;
                cout << "|   t   |     AAR     |   AAR-STD   |    CAAR     |   CAAR-STD  |" << endl;
                cout << "-----------------------------------------------------------------" << endl;
                
                cout << fixed << setprecision(4);
                for (int i=0; i<2*MEMO.N; i++)
                    cout << "| " << setw(4) << i - MEMO.N + 1 << "  |   " << setw(7) << MEMO.Result[std::stoi(n_)][0][i] << "   |   " << setw(7) << MEMO.Result[std::stoi(n_)][1][i] << "   |   " << setw(7) << MEMO.Result[std::stoi(n_)][2][i] << "   |   " << setw(7) << MEMO.Result[std::stoi(n_)][3][i] << "   |" << endl;
                
                cout << "-----------------------------------------------------------------" << endl;
                break;
                
            case 4:
                if (MEMO.N < 60 || MEMO.N > MEMO.N_MAX)
                    cout << "  Please enter a valid N first ! "<< endl;
                else
                    plotResults(MEMO.Result[0][2], MEMO.Result[1][2], MEMO.Result[2][2], MEMO.N);
                break;
                
            case 5:
                state = false;
                break;
        }
        
        cout << endl;
    }
    
    return 0;
}
