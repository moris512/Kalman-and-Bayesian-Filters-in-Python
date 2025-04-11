//CPP Version of Chapter 1 G-H Filter
#include <iostream>    // Standard I/O streams
#include <vector>      // For std::vector
#include <string>      // For std::string
#include <map>         // For std::map
#include <set>         // For std::set
#include <tuple>       // For std::tuple and structured bindings (C++17)
#include <fstream>     // For file I/O
#include <stdexcept>   // For exceptions
#include <algorithm>   // For standard algorithms
#include <ranges>      // For C++20 ranges (optional)
#include <utility>     // To use std::pair
#include <sciplot/sciplot.hpp>
#include <windows.h>
#include <random>
using namespace sciplot;

//Generate Noisy Data
std::pair<std::vector<double>, std::vector<double>> Gen_Noisy_Data(double x0, double dx, double dt, int steps, double noise_factor){
    std::vector<double> real_data;
    real_data.push_back(x0);
    
    for (int i=1; i<= steps; i++){
        double x = x0 + dx * dt * i;
        real_data.push_back(x);
    }

    //Random number generator for noise
    std::default_random_engine generator(std::random_device{}());
    std::normal_distribution<double> distribution(0.0, noise_factor);

    std::vector<double> noisy_data;
    for(int i=1; i < real_data.size(); i++){
        double noisy_value = real_data[i] + distribution(generator);
        noisy_data.push_back(noisy_value);
    }

    return {noisy_data, real_data};
}

//GH_Filter
std::pair<std::vector<double>, std::vector<double>> GH_Filter(std::vector<double> noisy_data, double x0, double dx0, double dt, double g, double h){
    double x_est = x0;
    double dx = dx0;
    double x_pred;
    double residual;

    std::vector<double> estimates;
    estimates.push_back(x_est);
    std::vector<double> predictions;

    for(double z : noisy_data){
        //Prediction Step
        x_pred = x_est + (dx * dt);
        predictions.push_back(x_pred);
        dx = dx;
        //Update Step
        residual = z - x_pred;
        x_est = x_pred + g * residual;
        estimates.push_back(x_est);
        dx = dx + h * (residual/dt);
    }
    return {estimates, predictions};
}

int main(){
    auto [noisy_data, real_data] = Gen_Noisy_Data(160, 1., 1., 10, 1);
    auto [estimates, predictions] = GH_Filter(noisy_data, 160, 0., 1., 0.3, 0.1);
    for(double x : estimates){
        std::cout<< "Estimate: " << x << std::endl;
    }
    for(double x : predictions){
        std::cout<< "Prediction: " << x << std::endl;
    }
    // Time steps
    std::vector<int> n(estimates.size());
    std::vector<int> p(predictions.size());

    for (int i = 0; i < n.size(); ++i) n[i] = i;
    for (int i = 0; i < p.size(); ++i) p[i] = i + 1; // Predictions are 1-based in time

    // Create the plot
    Plot2D plot;

    // Add curves
    plot.drawCurve(n, estimates).label("Estimates").lineWidth(2).pointType(7);       // Circles
    plot.drawCurve(p, predictions).label("Predictions").lineWidth(1).pointType(13);  // Diamonds
    plot.drawCurve(n, real_data).label("Actual").lineWidth(1);
    plot.drawBrokenCurve(p, noisy_data).label("Measurements").lineWidth(1).pointType(10);  // Stars

    // Axis labels and legend
    plot.xlabel("Time step");
    plot.ylabel("Weight");

    // Create figure and canvas
    Figure fig = {{plot}};
    Canvas canvas = {{fig}};
    canvas.size(1000, 600);
    canvas.show();
}