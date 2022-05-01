
#### !!! Please change FILEPATH and API_TOKEN in the LoadData.hpp to run !!!

<br>

### The program do the following things 

(1) Load the earning data ( < 0.1s )

(2) Split all the stocks into 3 groups  ( < 0.1s )

(3) Use multi-thread to download price data for all stocks upfront ( ~ 100s )

     * 12/31/2021 prices are missing for some stocks and forward fill is used
     
     * Some stocks are excluded from the pool so that they cannot be randomly selected in the bootstrapping step
         
          a. Stocks with the earning announcement date on weekend 
          b. Stocks with incomplete price series ( eg. AGL, its price data is only available from 2021-04-15 ) 
     
(4) Calculate the largest valid N ( < 0.1s )

(5) Bootstrap each time a new N is entered ( 6 ~ 10s )

<br>


### Details of Bootstrapping

(1) Randomly select 80 stocks for each group

(2) Calculate the daily returns and cumulative returns for each stock, O(2 * 2N)   * O(1) for stocks that have been selected before

(3) Compute AAR, CAAR for each t and group

(4) Repeat (1) ~ (3) for 40 times to compute Avg.AAR, AAR-STD, Avg.CAAR, CAAR STD

    Total time Complexity is ~ O(40 x 3 x 80 x 2N x (2/3 + 2))

