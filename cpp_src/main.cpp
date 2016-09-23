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

    vector<vector < Map *>> dataset;

    init_rand();

    int num_steps = 10;
    int num_exp_per_step = 10;
    int num_vert_per_step = 4;
    int k = 4;

    for (int i = 0; i < num_steps; i++) {
        vector<Map *> next_row;
        for (int j = 0; j < num_exp_per_step; j++) {
            int N = (i + 1) * num_vert_per_step;
            Map * map = map = problem_gen(N, WIDTH);
            next_row.push_back(map);
        }
        dataset.push_back(next_row);
        int N = (i + 1) * 5;
    }

    vector<vector<float>> mincon_reads;
    vector<vector<float>> mincon_writes;
    vector<vector<float>> mincon_timings;
    minconflicts_experiment(dataset, mincon_reads, mincon_writes, mincon_timings, k);

    vector<vector<float>> btmac_reads;
    vector<vector<float>> btmac_writes;
    vector<vector<float>> btmac_timings;
    backtrack_mac_experiment(dataset, btmac_reads, btmac_writes, btmac_timings, k);

    vector<vector<float>> btfor_reads;
    vector<vector<float>> btfor_writes;
    vector<vector<float>> btfor_timings;
    backtrack_forward_experiment(dataset, btfor_reads, btfor_writes, btfor_timings, k);

    vector<vector<float>> btsim_reads;
    vector<vector<float>> btsim_writes;
    vector<vector<float>> btsim_timings;
    backtrack_simple_experiment(dataset, btsim_reads, btsim_writes, btsim_timings, k);

    vector<vector<float>> gen_reads;
    vector<vector<float>> gen_writes;
    vector<vector<float>> gen_timings;
    genetic_experiment(dataset, gen_reads, gen_writes, gen_timings, k);

    Gnuplot gp;

    gp << "set terminal pdfcairo font 'Times,10'\n";
    gp << "set output '../results/comparing_read_performance.pdf'\n";
    gp << "set logscale y 10 \n";
    gp << "set key left top \n";
    gp << "set title 'Number of Vertex Reads per Algorithm'\n";
    gp << "set ylabel 'Vertex Read Count'\n";
    gp << "set xlabel 'Number of vertices (N)'\n";
    gp << "set grid\n";
    gp << "set style fill transparent solid 0.1 noborder \n";
    gp << "plot "
            "'-' using 1:2 lw 3 lt 2 lc 5 with lines title  'Minimum Conflicts',"
            "'-' using 1:3:4 lc 5 with filledcurves notitle,"
            "'-' using 1:2 lw 3 lt 2 lc 3 with lines title  'Simple Backtracking',"
            "'-' using 1:3:4 lc 3 with filledcurves notitle,"
            "'-' using 1:2 lw 3 lt 2 lc 2 with lines title 'Backtracking with Forward Checking',"
            "'-' using 1:3:4 lc 2 with filledcurves notitle,"
            "'-' using 1:2 lw 3 lt 2 lc 1 with lines title 'Backtracking with MAC',"
            "'-' using 1:3:4 lc 1 with filledcurves notitle,"
            "'-' using 1:2 lw 3 lt 2 lc 4 with lines title 'Genetic Algorithm',"
            "'-' using 1:3:4 lc 4 with filledcurves notitle \n";
    gp.send1d(mincon_reads);
    gp.send1d(mincon_reads);
    gp.send1d(btsim_reads);
    gp.send1d(btsim_reads);
    gp.send1d(btfor_reads);
    gp.send1d(btfor_reads);
    gp.send1d(btmac_reads);
    gp.send1d(btmac_reads);
    gp.send1d(gen_reads);
    gp.send1d(gen_reads);

    gp << "set output '../results/comparing_write_performance.pdf'\n";
    gp << "set title 'Number of Vertex Writes per Algorithm'\n";
    gp << "set ylabel 'Vertex Write Count'\n";
    gp << "plot "
            "'-' using 1:2 lw 3 lt 2 lc 5 with lines title  'Minimum Conflicts',"
            "'-' using 1:3:4 lc 5 with filledcurves notitle,"
            "'-' using 1:2 lw 3 lt 2 lc 3 with lines title  'Simple Backtracking',"
            "'-' using 1:3:4 lc 3 with filledcurves notitle,"
            "'-' using 1:2 lw 3 lt 2 lc 2 with lines title 'Backtracking with Forward Checking',"
            "'-' using 1:3:4 lc 2 with filledcurves notitle,"
            "'-' using 1:2 lw 3 lt 2 lc 1 with lines title 'Backtracking with MAC',"
            "'-' using 1:3:4 lc 1 with filledcurves notitle,"
            "'-' using 1:2 lw 3 lt 2 lc 4 with lines title 'Genetic Algorithm',"
            "'-' using 1:3:4 lc 4 with filledcurves notitle \n";

    gp.send1d(mincon_writes);
    gp.send1d(mincon_writes);
    gp.send1d(btsim_writes);
    gp.send1d(btsim_writes);
    gp.send1d(btfor_writes);
    gp.send1d(btfor_writes);
    gp.send1d(btmac_writes);
    gp.send1d(btmac_writes);
    gp.send1d(gen_writes);
    gp.send1d(gen_writes);

    gp << "set output '../results/comparing_time_performance.pdf'\n";
    gp << "set title 'Time Elapsed per Algorithm'\n";
    gp << "set ylabel 'Time Elapsed (s)'\n";
    gp << "plot "
            "'-' using 1:2 lw 3 lt 2 lc 5 with lines title  'Minimum Conflicts',"
            "'-' using 1:3:4 lc 5 with filledcurves notitle,"
            "'-' using 1:2 lw 3 lt 2 lc 3 with lines title  'Simple Backtracking',"
            "'-' using 1:3:4 lc 3 with filledcurves notitle,"
            "'-' using 1:2 lw 3 lt 2 lc 2 with lines title 'Backtracking with Forward Checking',"
            "'-' using 1:3:4 lc 2 with filledcurves notitle,"
            "'-' using 1:2 lw 3 lt 2 lc 1 with lines title 'Backtracking with MAC',"
            "'-' using 1:3:4 lc 1 with filledcurves notitle,"
            "'-' using 1:2 lw 3 lt 2 lc 4 with lines title 'Genetic Algorithm',"
            "'-' using 1:3:4 lc 4 with filledcurves notitle \n";

    gp.send1d(mincon_timings);
    gp.send1d(mincon_timings);
    gp.send1d(btsim_timings);
    gp.send1d(btsim_timings);
    gp.send1d(btfor_timings);
    gp.send1d(btfor_timings);
    gp.send1d(btmac_timings);
    gp.send1d(btmac_timings);
    gp.send1d(gen_timings);
    gp.send1d(gen_timings);



    return 0;
}

void backtrack_simple_experiment(vector<vector<Map *>> dataset, vector<vector<float>> &reads, vector<vector<float>> &writes, vector<vector<float>> &timings, int k) {
    int max_steps = 2e6;
    vector<vector<float>> step_arr;

    for (int i = 0; i < dataset.size(); i++) {

        int N = dataset[i][0]->N;
        vector<float> reads_for_N;
        vector<float> writes_for_N;
        vector<float> timings_for_N;
        vector<float> step_arr_for_N;


        for (int j = 0; j < dataset[i].size(); j++) {
            Map * map = dataset[i][j];
            map->clean_map();
            auto t1 = chrono::high_resolution_clock::now();
            int steps = 0;
            bool result = backtrack(map, k, 0, &steps, max_steps);
            auto t2 = std::chrono::high_resolution_clock::now();

            char * filename = new char[100];
            sprintf(filename, "../results/backtracking_simple/maps/bt_simple__N%d_k%d_I%d.pdf", N, k, j);
            Cairo * cairo = new Cairo(filename);
            map->draw_map(cairo);
            cairo->finish();


            //            etime = chrono::duration_cast<chrono::hours>(t2 - t1).count()

            cout << "Simple Backtracking N = " << N << ", k = " << k << ", j = " << j << endl;
            bool saturated = (steps >= max_steps);
            cout << "Experiment success: " << ((!saturated and !result) ? false : true) << endl;
            cout << "Step limit reached: " << saturated << endl;
            print_time(t1, t2);
            cout << "Number of recursive calls: " << (float) steps << endl;
            cout << "Number of reads: " << (float) map->num_reads << endl;
            cout << "Reads/s: " << (float) map->num_reads / chrono::duration_cast<chrono::microseconds>(t2 - t1).count() * 1.0e6 << endl;
            cout << "Number of writes: " << (float) map->num_writes << endl;
            cout << "Writes/s: " << (float) map->num_writes / chrono::duration_cast<chrono::microseconds>(t2 - t1).count() * 1.0e6 << endl;
            cout << "Steps: " << (float) steps << endl;
            cout << "Steps/s: " << (float) steps / chrono::duration_cast<chrono::microseconds>(t2 - t1).count() * 1.0e6 << endl;
            cout << endl;


            reads_for_N.push_back(map->num_reads);
            writes_for_N.push_back(map->num_writes);
            timings_for_N.push_back(chrono::duration_cast<chrono::microseconds>(t2 - t1).count() / 1.0e6);
            step_arr_for_N.push_back(steps);



        }

        vector<float> read_std_mean = standard_deviation(reads_for_N);
        vector<float> write_std_mean = standard_deviation(writes_for_N);


        vector<float> next_data_read;
        next_data_read.push_back((float) N);
        next_data_read.push_back(read_std_mean[0]);
        next_data_read.push_back(*max_element(begin(reads_for_N), end(reads_for_N)));
        next_data_read.push_back(*min_element(begin(reads_for_N), end(reads_for_N)));
        reads.push_back(next_data_read);

        vector<float> next_data_write;
        next_data_write.push_back((float) N);
        next_data_write.push_back(write_std_mean[0]);
        next_data_write.push_back(*max_element(begin(writes_for_N), end(writes_for_N)));
        next_data_write.push_back(*min_element(begin(writes_for_N), end(writes_for_N)));
        writes.push_back(next_data_write);

        vector<float> timings_std_mean = standard_deviation(timings_for_N);
        vector<float> next_data_timing;
        next_data_timing.push_back((float) N);
        next_data_timing.push_back(timings_std_mean[0]);
        next_data_timing.push_back(*max_element(begin(timings_for_N), end(timings_for_N)));
        next_data_timing.push_back(*min_element(begin(timings_for_N), end(timings_for_N)));
        timings.push_back(next_data_timing);

        vector<float> step_std_mean = standard_deviation(step_arr_for_N);
        vector<float> next_data_step;
        next_data_step.push_back((float) N);
        next_data_step.push_back(step_std_mean[0]);
        next_data_step.push_back(*max_element(begin(step_arr_for_N), end(step_arr_for_N)));
        next_data_step.push_back(*min_element(begin(step_arr_for_N), end(step_arr_for_N)));
        step_arr.push_back(next_data_step);


    }

    Gnuplot gp;

    gp << "set terminal pdfcairo font 'Times,10'\n";
    gp << "set output '../results/backtracking_simple/bt_simple_performance.pdf'\n";
    gp << "set logscale y 10 \n";
    gp << "set key left top \n";
    gp << "set title 'Performance of Simple Backtracking'\n";
    gp << "set ylabel 'Read/Write Count'\n";
    gp << "set xlabel 'Number of vertices (N)'\n";
    gp << "set style fill transparent solid 0.1 noborder \n";
    gp << "plot "
            "'-' using 1:2 lw 3 lt 2 lc 2 with lines title 'mean vertex reads',"
            "'-'  using 1:3:4 lc 2 with filledcurves notitle, "
            "'-' using 1:2 lw 3 lt 2 lc 1 with lines title 'mean vertex writes',"
            "'-'  using 1:3:4 lc 1 with filledcurves notitle,"
            "'-' using 1:2 lw 3 lt 2 lc 3 with lines title 'mean recursive calls',"
            "'-'  using 1:3:4 lc 3 with filledcurves notitle\n";
    gp.send1d(reads);
    gp.send1d(reads);
    gp.send1d(writes);
    gp.send1d(writes);
    gp.send1d(step_arr);
    gp.send1d(step_arr);
}

void minconflicts_experiment(vector<vector<Map *>> dataset, vector<vector<float>> &reads, vector<vector<float>> &writes, vector<vector<float>> &timings, int k) {
    int max_steps = 1e8;
    vector<vector<float>> step_arr;

    for (int i = 0; i < dataset.size(); i++) {

        int N = dataset[i][0]->N;
        vector<float> reads_for_N;
        vector<float> writes_for_N;
        vector<float> timings_for_N;
        vector<float> step_arr_for_N;


        for (int j = 0; j < dataset[i].size(); j++) {
            Map * map = dataset[i][j];
            map->clean_map();
            auto t1 = chrono::high_resolution_clock::now();
            int steps = min_conflicts(map, k, max_steps);
            auto t2 = std::chrono::high_resolution_clock::now();

            char * filename = new char[100];
            sprintf(filename, "../results/min_conflicts/maps/minconf_N%d_k%d_I%d.pdf", N, k, j);
            Cairo * cairo = new Cairo(filename);
            map->draw_map(cairo);
            cairo->finish();


            //            etime = chrono::duration_cast<chrono::hours>(t2 - t1).count()

            cout << "Minimum Conflicts N = " << N << ", k = " << k << ", j = " << j << endl;
            cout << "Step limit reached: " << ((steps != 0) ? false : true) << endl;
            print_time(t1, t2);
            cout << "Number of reads: " << (float) map->num_reads << endl;
            cout << "Reads/s: " << (float) map->num_reads / chrono::duration_cast<chrono::microseconds>(t2 - t1).count() * 1.0e6 << endl;
            cout << "Number of writes: " << (float) map->num_writes << endl;
            cout << "Writes/s: " << (float) map->num_writes / chrono::duration_cast<chrono::microseconds>(t2 - t1).count() * 1.0e6 << endl;
            cout << "Steps: " << (float) steps << endl;
            cout << "Steps/s: " << (float) steps / chrono::duration_cast<chrono::microseconds>(t2 - t1).count() * 1.0e6 << endl;
            cout << endl;


            reads_for_N.push_back(map->num_reads);
            writes_for_N.push_back(map->num_writes);
            timings_for_N.push_back(chrono::duration_cast<chrono::microseconds>(t2 - t1).count() / 1.0e6);
            step_arr_for_N.push_back(steps);



        }

        vector<float> read_std_mean = standard_deviation(reads_for_N);
        vector<float> write_std_mean = standard_deviation(writes_for_N);


        vector<float> next_data_read;
        next_data_read.push_back((float) N);
        next_data_read.push_back(read_std_mean[0]);
        next_data_read.push_back(*max_element(begin(reads_for_N), end(reads_for_N)));
        next_data_read.push_back(*min_element(begin(reads_for_N), end(reads_for_N)));
        reads.push_back(next_data_read);

        vector<float> next_data_write;
        next_data_write.push_back((float) N);
        next_data_write.push_back(write_std_mean[0]);
        next_data_write.push_back(*max_element(begin(writes_for_N), end(writes_for_N)));
        next_data_write.push_back(*min_element(begin(writes_for_N), end(writes_for_N)));
        writes.push_back(next_data_write);

        vector<float> timings_std_mean = standard_deviation(timings_for_N);
        vector<float> next_data_timing;
        next_data_timing.push_back((float) N);
        next_data_timing.push_back(timings_std_mean[0]);
        next_data_timing.push_back(*max_element(begin(timings_for_N), end(timings_for_N)));
        next_data_timing.push_back(*min_element(begin(timings_for_N), end(timings_for_N)));
        timings.push_back(next_data_timing);

        vector<float> step_std_mean = standard_deviation(step_arr_for_N);
        vector<float> next_data_step;
        next_data_step.push_back((float) N);
        next_data_step.push_back(step_std_mean[0]);
        next_data_step.push_back(*max_element(begin(step_arr_for_N), end(step_arr_for_N)));
        next_data_step.push_back(*min_element(begin(step_arr_for_N), end(step_arr_for_N)));
        step_arr.push_back(next_data_step);


    }

    Gnuplot gp;

    gp << "set terminal pdfcairo font 'Times,10'\n";
    gp << "set output '../results/min_conflicts/min_conflicts_performance.pdf'\n";
    gp << "set logscale y 10 \n";
    gp << "set key left top \n";
    gp << "set title 'Performance of Minimum Conflicts'\n";
    gp << "set ylabel 'Count'\n";
    gp << "set xlabel 'Number of vertices (N)'\n";
    gp << "set style fill transparent solid 0.1 noborder \n";
    gp << "plot "
            "'-' using 1:2 lw 3 lt 2 lc 2 with lines title 'mean vertex reads',"
            "'-'  using 1:3:4 lc 2 with filledcurves notitle, "
            "'-' using 1:2 lw 3 lt 2 lc 1 with lines title 'mean vertex writes',"
            "'-'  using 1:3:4 lc 1 with filledcurves notitle,"
            "'-' using 1:2 lw 3 lt 2 lc 3 with lines title 'mean steps',"
            "'-'  using 1:3:4 lc 3 with filledcurves notitle\n";
    gp.send1d(reads);
    gp.send1d(reads);
    gp.send1d(writes);
    gp.send1d(writes);
    gp.send1d(step_arr);
    gp.send1d(step_arr);
}

void backtrack_forward_experiment(vector<vector<Map *>> dataset, vector<vector<float>> &reads, vector<vector<float>> &writes, vector<vector<float>> &timings, int k) {
    int max_steps = 2e9;
    vector<vector<float>> step_arr;

    for (int i = 0; i < dataset.size(); i++) {

        int N = dataset[i][0]->N;
        vector<float> reads_for_N;
        vector<float> writes_for_N;
        vector<float> timings_for_N;
        vector<float> step_arr_for_N;

        for (int j = 0; j < dataset[i].size(); j++) {
            Map * map = dataset[i][j];
            if (k == 4) {
                map->clean_map_bitwise();
            } else if (k == 3) {
                map->three_clean_map_bitwise();
            }
            auto t1 = chrono::high_resolution_clock::now();
            int steps = 0;
            bool result = backtrack_forward(map, 0, &steps, max_steps);
            auto t2 = std::chrono::high_resolution_clock::now();

            char * filename = new char[100];
            sprintf(filename, "../results/backtracking_forward/maps/bt_forward_N%d_k%d_I%d.pdf", N, k, j);
            Cairo * cairo = new Cairo(filename);
            map->draw_map_bitwise(cairo);
            cairo->finish();

            if (steps > max_steps) {
                result = false;
            }

            cout << "Backtracking with Forward Checking, N = " << N << ", k = " << k << ", j = " << j << endl;
            bool saturated = (steps >= max_steps);
            cout << "Experiment success: " << ((!saturated and !result) ? false : true) << endl;
            cout << "Step limit reached: " << saturated << endl;
            print_time(t1, t2);
            cout << "Number of reads: " << (float) map->num_reads << endl;
            cout << "Reads/s: " << (float) map->num_reads / chrono::duration_cast<chrono::microseconds>(t2 - t1).count() * 1.0e6 << endl;
            cout << "Number of writes: " << (float) map->num_writes << endl;
            cout << "Writes/s: " << (float) map->num_writes / chrono::duration_cast<chrono::microseconds>(t2 - t1).count() * 1.0e6 << endl;
            cout << "Steps: " << (float) steps << endl;
            cout << "Steps/s :" << (float) steps / chrono::duration_cast<chrono::microseconds>(t2 - t1).count() * 1.0e6 << endl;
            cout << endl;
            reads_for_N.push_back(map->num_reads);
            writes_for_N.push_back(map->num_writes);
            timings_for_N.push_back(chrono::duration_cast<chrono::microseconds>(t2 - t1).count() / 1.0e6);
            step_arr_for_N.push_back(steps);


        }

        vector<float> read_std_mean = standard_deviation(reads_for_N);
        vector<float> write_std_mean = standard_deviation(writes_for_N);

        vector<float> next_data_read;
        next_data_read.push_back((float) N);
        next_data_read.push_back(read_std_mean[0]);
        next_data_read.push_back(*max_element(begin(reads_for_N), end(reads_for_N)));
        next_data_read.push_back(*min_element(begin(reads_for_N), end(reads_for_N)));
        reads.push_back(next_data_read);

        vector<float> next_data_write;
        next_data_write.push_back((float) N);
        next_data_write.push_back(write_std_mean[0]);
        next_data_write.push_back(*max_element(begin(writes_for_N), end(writes_for_N)));
        next_data_write.push_back(*min_element(begin(writes_for_N), end(writes_for_N)));
        writes.push_back(next_data_write);

        vector<float> timings_std_mean = standard_deviation(timings_for_N);
        vector<float> next_data_timing;
        next_data_timing.push_back((float) N);
        next_data_timing.push_back(timings_std_mean[0]);
        next_data_timing.push_back(*max_element(begin(timings_for_N), end(timings_for_N)));
        next_data_timing.push_back(*min_element(begin(timings_for_N), end(timings_for_N)));
        timings.push_back(next_data_timing);

        vector<float> step_std_mean = standard_deviation(step_arr_for_N);
        vector<float> next_data_step;
        next_data_step.push_back((float) N);
        next_data_step.push_back(step_std_mean[0]);
        next_data_step.push_back(*max_element(begin(step_arr_for_N), end(step_arr_for_N)));
        next_data_step.push_back(*min_element(begin(step_arr_for_N), end(step_arr_for_N)));
        step_arr.push_back(next_data_step);
    }

    Gnuplot gp;

    gp << "set terminal pdfcairo font 'Times,10'\n";
    gp << "set output '../results/backtracking_forward/bt_forward_performance.pdf'\n";
    gp << "set logscale y 10 \n";
    gp << "set key left top \n";
    gp << "set title 'Performance of Backtracking with Forward Checking'\n";
    gp << "set ylabel 'Read/Write Count'\n";
    gp << "set xlabel 'Number of vertices (N)'\n";
    gp << "set style fill transparent solid 0.1 noborder \n";
    gp << "plot "
            "'-' using 1:2 lw 3 lt 2 lc 2 with lines title 'mean vertex reads',"
            "'-'  using 1:3:4 lc 2 with filledcurves notitle, "
            "'-' using 1:2 lw 3 lt 2 lc 1 with lines title 'mean vertex writes',"
            "'-'  using 1:3:4 lc 1 with filledcurves notitle,"
            "'-' using 1:2 lw 3 lt 2 lc 3 with lines title 'mean recursive calls',"
            "'-'  using 1:3:4 lc 3 with filledcurves notitle\n";
    gp.send1d(reads);
    gp.send1d(reads);
    gp.send1d(writes);
    gp.send1d(writes);
    gp.send1d(step_arr);
    gp.send1d(step_arr);


}

void backtrack_mac_experiment(vector<vector<Map *>> dataset, vector<vector<float>> &reads, vector<vector<float>> &writes, vector<vector<float>> &timings, int k) {

    int max_steps = 2e6;
    vector<vector<float>> step_arr;

    for (int i = 0; i < dataset.size(); i++) {

        int N = dataset[i][0]->N;
        vector<float> reads_for_N;
        vector<float> writes_for_N;
        vector<float> timings_for_N;
        vector<float> step_arr_for_N;

        for (int j = 0; j < dataset[i].size(); j++) {
            Map * map = dataset[i][j];
            if (k == 4) {
                map->clean_map_bitwise();
            } else if (k == 3) {
                map->three_clean_map_bitwise();
            }
            auto t1 = chrono::high_resolution_clock::now();
            int steps = 0;
            bool result = backtrack_mac(map, 0, &steps, max_steps);
            auto t2 = std::chrono::high_resolution_clock::now();

            char * filename = new char[100];
            sprintf(filename, "../results/backtracking_mac/maps/bt_mac_N%d_k%d_I%d.pdf", N, k, j);
            Cairo * cairo = new Cairo(filename);
            map->draw_map_bitwise(cairo);
            cairo->finish();

            if (steps > max_steps) {
                result = false;
            }

            cout << "Backtracking with MAC, N = " << N << ", k = " << k << ", j = " << j << endl;
            bool saturated = (steps >= max_steps);
            cout << "Experiment success: " << ((!saturated and !result) ? false : true) << endl;
            cout << "Step limit reached: " << saturated << endl;
            print_time(t1, t2);
            cout << "Number of reads: " << (float) map->num_reads << endl;
            cout << "Reads/s: " << (float) map->num_reads / chrono::duration_cast<chrono::microseconds>(t2 - t1).count() * 1.0e6 << endl;
            cout << "Number of writes: " << (float) map->num_writes << endl;
            cout << "Writes/s: " << (float) map->num_writes / chrono::duration_cast<chrono::microseconds>(t2 - t1).count() * 1.0e6 << endl;
            cout << "Steps: " << (float) steps << endl;
            cout << "Steps/s " << (float) steps / chrono::duration_cast<chrono::microseconds>(t2 - t1).count() * 1.0e6 << endl;
            cout << endl;
            reads_for_N.push_back(map->num_reads);
            writes_for_N.push_back(map->num_writes);
            timings_for_N.push_back(chrono::duration_cast<chrono::microseconds>(t2 - t1).count() / 1.0e6);
            step_arr_for_N.push_back(steps);

        }

        vector<float> read_std_mean = standard_deviation(reads_for_N);
        vector<float> write_std_mean = standard_deviation(writes_for_N);

        vector<float> next_data_read;
        next_data_read.push_back((float) N);
        next_data_read.push_back(read_std_mean[0]);
        next_data_read.push_back(*max_element(begin(reads_for_N), end(reads_for_N)));
        next_data_read.push_back(*min_element(begin(reads_for_N), end(reads_for_N)));
        reads.push_back(next_data_read);

        vector<float> next_data_write;
        next_data_write.push_back((float) N);
        next_data_write.push_back(write_std_mean[0]);
        next_data_write.push_back(*max_element(begin(writes_for_N), end(writes_for_N)));
        next_data_write.push_back(*min_element(begin(writes_for_N), end(writes_for_N)));
        writes.push_back(next_data_write);

        vector<float> timings_std_mean = standard_deviation(timings_for_N);
        vector<float> next_data_timing;
        next_data_timing.push_back((float) N);
        next_data_timing.push_back(timings_std_mean[0]);
        next_data_timing.push_back(*max_element(begin(timings_for_N), end(timings_for_N)));
        next_data_timing.push_back(*min_element(begin(timings_for_N), end(timings_for_N)));
        timings.push_back(next_data_timing);

        vector<float> step_std_mean = standard_deviation(step_arr_for_N);
        vector<float> next_data_step;
        next_data_step.push_back((float) N);
        next_data_step.push_back(step_std_mean[0]);
        next_data_step.push_back(*max_element(begin(step_arr_for_N), end(step_arr_for_N)));
        next_data_step.push_back(*min_element(begin(step_arr_for_N), end(step_arr_for_N)));
        step_arr.push_back(next_data_step);
    }

    Gnuplot gp;

    gp << "set terminal pdfcairo font 'Times,10'\n";
    gp << "set output '../results/backtracking_mac/bt_mac_performance.pdf'\n";
    gp << "set logscale y 10 \n";
    gp << "set key left top \n";
    gp << "set title 'Performance of Backtracking with MAC'\n";
    gp << "set ylabel 'Read/Write Count'\n";
    gp << "set xlabel 'Number of vertices (N)'\n";
    gp << "set style fill transparent solid 0.1 noborder \n";
    gp << "plot "
            "'-' using 1:2 lw 3 lt 2 lc 2 with lines title 'mean vertex reads',"
            "'-'  using 1:3:4 lc 2 with filledcurves notitle, "
            "'-' using 1:2 lw 3 lt 2 lc 1 with lines title 'mean vertex writes',"
            "'-'  using 1:3:4 lc 1 with filledcurves notitle,"
            "'-' using 1:2 lw 3 lt 2 lc 3 with lines title 'mean recursive calls',"
            "'-'  using 1:3:4 lc 3 with filledcurves notitle\n";
    gp.send1d(reads);
    gp.send1d(reads);
    gp.send1d(writes);
    gp.send1d(writes);
    gp.send1d(step_arr);
    gp.send1d(step_arr);
}

void genetic_experiment(vector<vector<Map *>> dataset, vector<vector<float>> &reads, vector<vector<float>> &writes, vector<vector<float>> &timings, int k) {
    int max_generations = 1e6;
    vector<vector<float>> num_runs;

    for (int i = 0; i < dataset.size(); i++) {

        int N = dataset[i][0]->N;
        vector<float> reads_for_N;
        vector<float> writes_for_N;
        vector<float> num_runs_for_N;
        vector<float> timings_for_N;

        for (int j = 0; j < dataset[i].size(); j++) {
            Map * map = dataset[i][j];
            map->clean_map();
            const int pop_size = (int) N;
            const int mut_rate = 100;
            GeneticAlgorithm * ga = new GeneticAlgorithm(map, pop_size, mut_rate, N, k, max_generations);
            auto t1 = chrono::high_resolution_clock::now();
            int gens = ga->run();
            auto t2 = std::chrono::high_resolution_clock::now();

            char * filename = new char[100];
            sprintf(filename, "../results/genetic/maps/genetic_N%d_k%d_I%d.pdf", N, k, j);
            Cairo * cairo = new Cairo(filename);
            map->draw_map(cairo);
            cairo->finish();

            cout << "Genetic Algorithm, N = " << N << ", k = " << k << ", j = " << j << endl;
            cout << "Generation limit reached: " << ((gens == 0) ? true : false) << endl;
            print_time(t1, t2);
            cout << "Number of reads: " << (float) map->num_reads << endl;
            cout << "Reads/s: " << (float) map->num_reads / chrono::duration_cast<chrono::microseconds>(t2 - t1).count() * 1.0e6 << endl;
            cout << "Number of writes: " << (float) map->num_writes << endl;
            cout << "Writes/s: " << (float) map->num_writes / chrono::duration_cast<chrono::microseconds>(t2 - t1).count() * 1.0e6 << endl;
            cout << "Generations: " << gens << endl;
            cout << "Generations/s : " << (float) gens / chrono::duration_cast<chrono::microseconds>(t2 - t1).count() * 1.0e6 << endl;
            cout << endl;
            reads_for_N.push_back(map->num_reads);
            writes_for_N.push_back(map->num_writes);
            num_runs_for_N.push_back(gens);
            timings_for_N.push_back(chrono::duration_cast<chrono::microseconds>(t2 - t1).count() / 1.0e6);

        }

        vector<float> read_std_mean = standard_deviation(reads_for_N);
        vector<float> write_std_mean = standard_deviation(writes_for_N);
        vector<float> gens_std_mean = standard_deviation(num_runs_for_N);

        vector<float> next_data_read;
        next_data_read.push_back((float) N);
        next_data_read.push_back(read_std_mean[0]);
        next_data_read.push_back(*max_element(begin(reads_for_N), end(reads_for_N)));
        next_data_read.push_back(*min_element(begin(reads_for_N), end(reads_for_N)));
        reads.push_back(next_data_read);

        vector<float> next_data_write;
        next_data_write.push_back((float) N);
        next_data_write.push_back(write_std_mean[0]);
        next_data_write.push_back(*max_element(begin(writes_for_N), end(writes_for_N)));
        next_data_write.push_back(*min_element(begin(writes_for_N), end(writes_for_N)));
        writes.push_back(next_data_write);

        vector<float> next_data_gens;
        next_data_gens.push_back((float) N);
        next_data_gens.push_back(gens_std_mean[0]);
        next_data_gens.push_back(*max_element(begin(num_runs_for_N), end(num_runs_for_N)));
        next_data_gens.push_back(*min_element(begin(num_runs_for_N), end(num_runs_for_N)));
        ;
        num_runs.push_back(next_data_gens);

        vector<float> timings_std_mean = standard_deviation(timings_for_N);
        vector<float> next_data_timing;
        next_data_timing.push_back((float) N);
        next_data_timing.push_back(timings_std_mean[0]);
        next_data_timing.push_back(*max_element(begin(timings_for_N), end(timings_for_N)));
        next_data_timing.push_back(*min_element(begin(timings_for_N), end(timings_for_N)));
        timings.push_back(next_data_timing);
    }

    Gnuplot gp;

    gp << "set terminal pdfcairo font 'Times,10'\n";
    gp << "set output '../results/genetic/genetic_performance.pdf'\n";
    gp << "set logscale y 10 \n";
    gp << "set key left top \n";
    gp << "set title 'Genetic Algorithm Performance'\n";
    gp << "set ylabel 'Counts'\n";
    gp << "set xlabel 'Number of vertices (N)'\n";
    gp << "set style fill transparent solid 0.1 noborder \n";
    gp << "plot "
            "'-' using 1:2 lw 3 lt 2 lc 2 with lines title 'mean vertex reads',"
            "'-'  using 1:3:4 lc 2 with filledcurves notitle, "
            "'-' using 1:2 lw 3 lt 2 lc 1 with lines title 'mean vertex writes',"
            "'-'  using 1:3:4 lc 1 with filledcurves notitle, "
            "'-' using 1:2 lw 3 lt 2 lc 3 with lines title 'mean number of generations',"
            "'-'  using 1:3:4 lc 3 with filledcurves notitle, \n";
    gp.send1d(reads);
    gp.send1d(reads);
    gp.send1d(writes);
    gp.send1d(writes);
    gp.send1d(num_runs);
    gp.send1d(num_runs);
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

void print_time(std::chrono::time_point<std::chrono::system_clock> t1, std::chrono::time_point<std::chrono::system_clock> t2) {

    int hours = chrono::duration_cast<chrono::hours>(t2 - t1).count();
    int minutes = chrono::duration_cast<chrono::minutes>(t2 - t1).count() - chrono::duration_cast<chrono::hours>(t2 - t1).count() * 60;
    int seconds = chrono::duration_cast<chrono::seconds>(t2 - t1).count() - chrono::duration_cast<chrono::minutes>(t2 - t1).count()* 60;
    int millis = chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() - chrono::duration_cast<chrono::seconds>(t2 - t1).count() * 1000;
    printf("Time Elapsed: %02d:%02d:%02d.%03d\n", hours, minutes, seconds, millis);
}


