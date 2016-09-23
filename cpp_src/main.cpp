/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: byrdie
 *
 * Created on September 19, 2016, 10:37 AM
 */

#include "main.h"


using namespace std;

int main(int argc, char** argv) {
    
   const int pop_size = 1000;
    const int mut_rate = 30;
    const int N = 100;
    init_rand();

    Cairo * cairo = new Cairo("test.pdf");

    Map * map = problem_gen(N, WIDTH);

 
    map->clean_map();
    
    
    
    auto t1 = chrono::high_resolution_clock::now();
    
    printf("Steps = %d\n",min_conflicts(map, 4, 1000000) );
    auto t2 = chrono::high_resolution_clock::now();
    
    printf("\n\n");
    cout << "Number of reads: " << (float) map->num_reads << endl;
    cout << "Reads/s: " << (float) map->num_reads / chrono::duration_cast<chrono::microseconds>(t2-t1).count() * 1e6 << endl;
    cout << "Number of writes: " << (float) map->num_writes << endl;
    cout << "Writes/s: " << (float) map->num_writes / chrono::duration_cast<chrono::microseconds>(t2-t1).count() * 1e6 << endl;
    //cout << "Number of generations: " << (int) num_runs << endl;
    
    map->draw_map(cairo);


    cairo->finish();  

//    // 1474440327
//    init_rand();
//
//
//
//
//
//    vector<vector < Map *>> dataset;
//
//    int num_steps = 10;
//    int num_exp_per_step = 10;
//    int num_vert_per_step = 10;
//
//    for (int i = 0; i < num_steps; i++) {
//        vector<Map *> next_row;
//        for (int j = 0; j < num_exp_per_step; j++) {
//            int N = (i + 1) * num_vert_per_step;
//            Map * map = map = problem_gen(N, WIDTH);
//            next_row.push_back(map);
//        }
//        dataset.push_back(next_row);
//        int N = (i + 1) * 5;
//    }
//
//    vector<vector<float>> btmac_reads;
//    vector<vector<float>> btmac_writes;
//    backtrack_mac_experiment(dataset, btmac_reads, btmac_writes);
//
//    vector<vector<float>> btfor_reads;
//    vector<vector<float>> btfor_writes;
//    backtrack_forward_experiment(dataset, btfor_reads, btfor_writes);
//
//    vector<vector<float>> btsim_reads;
//    vector<vector<float>> btsim_writes;
//    backtrack_simple_experiment(dataset, btsim_reads, btsim_writes);
//
//    Gnuplot gp;
//
//    gp << "set terminal pdfcairo font 'Times,10'\n";
//    gp << "set output '../results/comparing_read_performance.pdf'\n";
//    gp << "set logscale y 10 \n";
//    gp << "set key left top \n";
//    gp << "set title 'Number of Vertex Reads per Algorithm'\n";
//    gp << "set ylabel 'Vertex Reads'\n";
//    gp << "set xlabel 'Number of vertices (N)'\n";
//    gp << "set grid\n";
//    gp << "set style fill transparent solid 0.2 noborder \n";
//    gp << "plot "
//            "'-' using 1:2 lt 2 lc 3 with lines title  'Simple Backtracking',"
//            "'-' using 1:3:4 lc 3 with filledcurves notitle,"
//            "'-' using 1:2 lt 2 lc 2 with lines title 'Backtracking with Forward Checking',"
//            "'-' using 1:3:4 lc 2 with filledcurves notitle,"
//            "'-' using 1:2 lt 2 lc 1 with lines title 'Backtracking with MAC',"
//            "'-' using 1:3:4 lc 1 with filledcurves notitle \n";
//    gp.send1d(btsim_reads);
//    gp.send1d(btsim_reads);
//    gp.send1d(btfor_reads);
//    gp.send1d(btfor_reads);
//    gp.send1d(btmac_reads);
//    gp.send1d(btmac_reads);
//
//
//
    return 0;
}

void backtrack_simple_experiment(vector<vector<Map *>> dataset, vector<vector<float>> &reads, vector<vector<float>> &writes) {
    for (int i = 0; i < dataset.size(); i++) {

        int N = dataset[i][0]->N;
        vector<float> reads_for_N;
        vector<float> writes_for_N;

        for (int j = 0; j < dataset[i].size(); j++) {
            Map * map = dataset[i][j];
            map->clean_map();
            auto t1 = chrono::high_resolution_clock::now();
            backtrack(map, 4, 0);
            auto t2 = std::chrono::high_resolution_clock::now();

            char * filename = new char[100];
            sprintf(filename, "../results/backtracking_simple/maps/bt_simple_N%d_I%d.pdf", N, j);
            Cairo * cairo = new Cairo(filename);
            map->draw_map(cairo);
            cairo->finish();

            cout << "Simple Backtracking N = " << N << ", j = " << j << endl;
            cout << "Number of reads: " << (float) map->num_reads << endl;
            cout << "Reads/s: " << (float) map->num_reads / chrono::duration_cast<chrono::microseconds>(t2 - t1).count() * 1e6 << endl;
            cout << "Number of writes: " << (float) map->num_writes << endl;
            cout << "Writes/s: " << (float) map->num_writes / chrono::duration_cast<chrono::microseconds>(t2 - t1).count() * 1e6 << endl;
            cout << endl;
            reads_for_N.push_back(map->num_reads);
            writes_for_N.push_back(map->num_writes);

        }

        vector<float> read_std_mean = standard_deviation(reads_for_N);
        vector<float> write_std_mean = standard_deviation(writes_for_N);

        vector<float> next_data_read;
        next_data_read.push_back((float) N);
        next_data_read.push_back(read_std_mean[0]);
        next_data_read.push_back(read_std_mean[0] + 1.96 * (read_std_mean[1] / sqrt(N)));
        next_data_read.push_back(read_std_mean[0] - 1.96 * (read_std_mean[1] / sqrt(N)));
        reads.push_back(next_data_read);

        vector<float> next_data_write;
        next_data_write.push_back((float) N);
        next_data_write.push_back(write_std_mean[0]);
        next_data_write.push_back(write_std_mean[0] + 1.96 * (write_std_mean[1] / sqrt(N)));
        next_data_write.push_back(write_std_mean[0] - 1.96 * (write_std_mean[1] / sqrt(N)));
        writes.push_back(next_data_write);
    }

    Gnuplot gp;

    gp << "set terminal pdfcairo font 'Times,10'\n";
    gp << "set output '../results/backtracking_simple/bt_simple_performance.pdf'\n";
    gp << "set logscale y 10 \n";
    gp << "set key left top \n";
    gp << "set title 'Performance of Simple Backtracking'\n";
    gp << "set ylabel 'Read/Write Count'\n";
    gp << "set xlabel 'Number of vertices (N)'\n";
    gp << "set style fill transparent solid 0.2 noborder \n";
    gp << "plot '-'  using 1:3:4 lc 1 with filledcurves notitle, "
            "'-' using 1:2 lt 2 lc 1 with lines title 'mean vertex writes',"
            "'-'  using 1:3:4 lc 2 with filledcurves notitle, "
            "'-' using 1:2 lt 2 lc 2 with lines title 'mean vertex reads'\n";
    gp.send1d(reads);
    gp.send1d(reads);
    gp.send1d(writes);
    gp.send1d(writes);
}

void backtrack_forward_experiment(vector<vector<Map *>> dataset, vector<vector<float>> &reads, vector<vector<float>> &writes) {
    for (int i = 0; i < dataset.size(); i++) {

        int N = dataset[i][0]->N;
        vector<float> reads_for_N;
        vector<float> writes_for_N;

        for (int j = 0; j < dataset[i].size(); j++) {
            Map * map = dataset[i][j];
            map->clean_map_bitwise();
            auto t1 = chrono::high_resolution_clock::now();
            backtrack_forward(map, 0);
            auto t2 = std::chrono::high_resolution_clock::now();

            char * filename = new char[100];
            sprintf(filename, "../results/backtracking_forward/maps/bt_forward_N%d_I%d.pdf", N, j);
            Cairo * cairo = new Cairo(filename);
            map->draw_map_bitwise(cairo);
            cairo->finish();

            cout << "Backtracking with Forward Checking, N = " << N << ", j = " << j << endl;
            cout << "Number of reads: " << (float) map->num_reads << endl;
            cout << "Reads/s: " << (float) map->num_reads / chrono::duration_cast<chrono::microseconds>(t2 - t1).count() * 1e6 << endl;
            cout << "Number of writes: " << (float) map->num_writes << endl;
            cout << "Writes/s: " << (float) map->num_writes / chrono::duration_cast<chrono::microseconds>(t2 - t1).count() * 1e6 << endl;
            cout << endl;
            reads_for_N.push_back(map->num_reads);
            writes_for_N.push_back(map->num_writes);

        }

        vector<float> read_std_mean = standard_deviation(reads_for_N);
        vector<float> write_std_mean = standard_deviation(writes_for_N);

        vector<float> next_data_read;
        next_data_read.push_back((float) N);
        next_data_read.push_back(read_std_mean[0]);
        next_data_read.push_back(read_std_mean[0] + 1.96 * (read_std_mean[1] / sqrt(N)));
        next_data_read.push_back(read_std_mean[0] - 1.96 * (read_std_mean[1] / sqrt(N)));
        reads.push_back(next_data_read);

        vector<float> next_data_write;
        next_data_write.push_back((float) N);
        next_data_write.push_back(write_std_mean[0]);
        next_data_write.push_back(write_std_mean[0] + 1.96 * (write_std_mean[1] / sqrt(N)));
        next_data_write.push_back(write_std_mean[0] - 1.96 * (write_std_mean[1] / sqrt(N)));
        writes.push_back(next_data_write);
    }

    Gnuplot gp;

    gp << "set terminal pdfcairo font 'Times,10'\n";
    gp << "set output '../results/backtracking_forward/bt_forward_performance.pdf'\n";
    gp << "set logscale y 10 \n";
    gp << "set key left top \n";
    gp << "set title 'Performance of Backtracking with Forward Checking'\n";
    gp << "set ylabel 'Read/Write Count'\n";
    gp << "set xlabel 'Number of vertices (N)'\n";
    gp << "set style fill transparent solid 0.2 noborder \n";
    gp << "plot '-'  using 1:3:4 lc 1 with filledcurves notitle, "
            "'-' using 1:2 lt 2 lc 1 with lines title 'mean vertex writes',"
            "'-'  using 1:3:4 lc 2 with filledcurves notitle, "
            "'-' using 1:2 lt 2 lc 2 with lines title 'mean vertex reads'\n";
    gp.send1d(reads);
    gp.send1d(reads);
    gp.send1d(writes);
    gp.send1d(writes);
}

void backtrack_mac_experiment(vector<vector<Map *>> dataset, vector<vector<float>> &reads, vector<vector<float>> &writes) {
    for (int i = 0; i < dataset.size(); i++) {

        int N = dataset[i][0]->N;
        vector<float> reads_for_N;
        vector<float> writes_for_N;

        for (int j = 0; j < dataset[i].size(); j++) {
            Map * map = dataset[i][j];
            map->clean_map_bitwise();
            auto t1 = chrono::high_resolution_clock::now();
            backtrack_mac(map, 0);
            auto t2 = std::chrono::high_resolution_clock::now();

            char * filename = new char[100];
            sprintf(filename, "../results/backtracking_mac/maps/bt_mac_N%d_I%d.pdf", N, j);
            Cairo * cairo = new Cairo(filename);
            map->draw_map_bitwise(cairo);
            cairo->finish();

            cout << "Backtracking with MAC, N = " << N << ", j = " << j << endl;
            cout << "Number of reads: " << (float) map->num_reads << endl;
            cout << "Reads/s: " << (float) map->num_reads / chrono::duration_cast<chrono::microseconds>(t2 - t1).count() * 1e6 << endl;
            cout << "Number of writes: " << (float) map->num_writes << endl;
            cout << "Writes/s: " << (float) map->num_writes / chrono::duration_cast<chrono::microseconds>(t2 - t1).count() * 1e6 << endl;
            cout << endl;
            reads_for_N.push_back(map->num_reads);
            writes_for_N.push_back(map->num_writes);

        }

        vector<float> read_std_mean = standard_deviation(reads_for_N);
        vector<float> write_std_mean = standard_deviation(writes_for_N);

        vector<float> next_data_read;
        next_data_read.push_back((float) N);
        next_data_read.push_back(read_std_mean[0]);
        next_data_read.push_back(read_std_mean[0] + 1.96 * (read_std_mean[1] / sqrt(N)));
        next_data_read.push_back(read_std_mean[0] - 1.96 * (read_std_mean[1] / sqrt(N)));
        reads.push_back(next_data_read);

        vector<float> next_data_write;
        next_data_write.push_back((float) N);
        next_data_write.push_back(write_std_mean[0]);
        next_data_write.push_back(write_std_mean[0] + 1.96 * (write_std_mean[1] / sqrt(N)));
        next_data_write.push_back(write_std_mean[0] - 1.96 * (write_std_mean[1] / sqrt(N)));
        writes.push_back(next_data_write);
    }

    Gnuplot gp;

    gp << "set terminal pdfcairo font 'Times,10'\n";
    gp << "set output '../results/backtracking_mac/bt_mac_performance.pdf'\n";
    gp << "set logscale y 10 \n";
    gp << "set key left top \n";
    gp << "set title 'Performance of Backtracking with MAC'\n";
    gp << "set ylabel 'Read/Write Count'\n";
    gp << "set xlabel 'Number of vertices (N)'\n";
    gp << "set style fill transparent solid 0.2 noborder \n";
    gp << "plot '-'  using 1:3:4 lc 1 with filledcurves notitle, "
            "'-' using 1:2 lt 2 lc 1 with lines title 'mean vertex writes',"
            "'-'  using 1:3:4 lc 2 with filledcurves notitle, "
            "'-' using 1:2 lt 2 lc 2 with lines title 'mean vertex reads'\n";
    gp.send1d(reads);
    gp.send1d(reads);
    gp.send1d(writes);
    gp.send1d(writes);
}

vector<float> standard_deviation(vector<float> data) {
    int n = data.size();
    float mean = 0.0, sum_deviation = 0.0;
    int i;
    for (i = 0; i < n; ++i) {
        mean += data[i];
    }
    mean = mean / n;
    for (i = 0; i < n; ++i)
        sum_deviation += (data[i] - mean)*(data[i] - mean);
    float std = sqrt(sum_deviation / n);

    //    cout << "Mean: " << mean << endl;
    //    cout << "Std. dev:" << std << endl;

    vector<float> result;
    result.push_back(mean);
    result.push_back(std);
    return result;
}



