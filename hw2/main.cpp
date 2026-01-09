#include "FarmSimulator.h"
#include <iostream>
#include <ctime>
#include <cmath>
#include <random>
#include <iomanip>
#include <vector> 
#include <fstream>

using namespace std;

int main() {
    // 1. Setup CSV Output
    ofstream csvFile("farm_results.csv");
    if (!csvFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }
    
    // Header
    csvFile << "sep=;" << endl; 
    csvFile << "N;Linear K=1;Linear K=N/8;Linear K=N/4;Linear K=N/2;"
            << "Binary K=1;Binary K=N/8;Binary K=N/4;Binary K=N/2;"
            << "Jump K=1;Jump K=N/8;Jump K=N/4;Jump K=N/2" << endl;

    // 2. Sizes 2^3 to 2^15
    vector<int> sizes;
    for (int p = 10; p <= 20; p++) {
        sizes.push_back(pow(2, p));
    }
    
    // KEY POOL:
    // Since we don't know how many times we will run (M is dynamic),
    // we generate a fixed pool of random keys and cycle through them.
    int POOL_SIZE = 10000;
    
    cout << fixed << setprecision(6);
    cout << "===== FARM SIMULATOR (Adaptive Time-Based) =====" << endl;
    
    random_device rd;
    mt19937 gen(rd());

    for (int N : sizes) {
        FarmSimulator farm(N);
        farm.createSheep(N);
        
        // Generate a pool of random keys for this N
        vector<int> keyPool(POOL_SIZE);
        uniform_int_distribution<> distr(0, 10 * N); 
        for(int i = 0; i < POOL_SIZE; i++) {
            keyPool[i] = distr(gen);
        }

        // Calculate K values
        int K_values[4] = {1, N/8, N/4, N/2};
        // Safety
        if (K_values[1] == 0) K_values[1] = 1;
        if (K_values[2] == 0) K_values[2] = 1;
        if (K_values[3] == 0) K_values[3] = 1;
        
        cout << "N=" << setw(5) << N << " | ";
        csvFile << N << ";";
        
        for (int algo = 0; algo < 3; algo++) {
            for (int k_idx = 0; k_idx < 4; k_idx++) {
                int K = K_values[k_idx];
                
                // --- ADAPTIVE BENCHMARKING ---
                
                long long repetitions = 0;
                clock_t startTime = clock();
                clock_t now = startTime;
                
                // TARGET: Run for at least 100ms (0.1 seconds)
                // This ensures we always get a non-zero, accurate result.
                double minDurationSecs = 0.1; 
                
                // Note: We check 'repetitions < 5' to ensure it runs at least a few times 
                // even if the clock resolution is poor.
                while (double(now - startTime) / CLOCKS_PER_SEC < minDurationSecs || repetitions < 5) {
                    
                    // Cycle through the key pool using modulo
                    int currentKey = keyPool[repetitions % POOL_SIZE];
                    int* result = nullptr;
                    
                    if (algo == 0) result = farm.lineerSearch(currentKey, K);
                    else if (algo == 1) result = farm.binaryInfect(currentKey, K);
                    else result = farm.jumpInfect(currentKey, K);
                    
                    delete[] result;
                    
                    repetitions++;
                    now = clock();
                }
                
                // --- CALCULATION ---
                double totalDurationMs = 1000.0 * double(now - startTime) / CLOCKS_PER_SEC;
                double avgTime = totalDurationMs / repetitions;
                
                cout << avgTime << " | ";
                csvFile << avgTime << (algo==2 && k_idx==3 ? "" : ";");
            }
        }
        cout << endl;
        csvFile << endl;
    }
    
    csvFile.close();
    cout << endl << "Done. Data saved to 'farm_results.csv'." << endl;
    return 0;
}