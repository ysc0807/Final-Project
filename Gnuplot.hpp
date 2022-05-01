
#ifndef Gnuplot_hpp
#define Gnuplot_hpp

#include <vector>
using std::vector;


void plotResults(const vector<double>& miss, const vector<double>& meet, const vector<double>& beat, int N){
    
    FILE *gnuplotPipe, *tempDataFile;
    
    const char *tempDataFileMiss = "Miss";
    const char *tempDataFileMeet = "Meet";
    const char *tempDataFileBeat = "Beat";
    
    double x1, y1, x2, y2, x3, y3;
    
    //set gnuplot enviorment
    gnuplotPipe = popen("/opt/local/bin/gnuplot", "w");
    if(gnuplotPipe){
        fprintf(gnuplotPipe,"plot \"%s\" with lines, \"%s\" with lines, \"%s\" with lines\n",tempDataFileBeat, tempDataFileMeet, tempDataFileMiss);
        fflush(gnuplotPipe);
        
        // miss data
        tempDataFile = fopen(tempDataFileMiss, "w");
        for (int i=0; i<2*N; i++) {
            x3 = i - N + 1;
            y3 = miss[i];
            fprintf(tempDataFile,"%lf %lf\n",x3,y3);
        }
        fclose(tempDataFile);
        
        // meet data
        tempDataFile = fopen(tempDataFileMeet,"w");
        for (int i=0; i<2*N; i++) {
            x2 = i - N + 1;
            y2 = meet[i];
            fprintf(tempDataFile,"%lf %lf\n",x2,y2);
        }
        fclose(tempDataFile);
        
        // beat data
        tempDataFile = fopen(tempDataFileBeat,"w");
        for (int i=0; i<2*N; i++) {
            x1 = i - N + 1;
            y1 = beat[i];
            fprintf(tempDataFile,"%lf %lf\n",x1,y1);
        }
        fclose(tempDataFile);
        
        //printf("  press enter to continue...");
        //getchar();
        //fprintf(gnuplotPipe,"exit \n");
    }
    else
        printf("gnuplot not found...");
    
}

#endif /* Gnuplot_hpp */
