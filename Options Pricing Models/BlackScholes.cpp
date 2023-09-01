#include <bits/stdc++.h>
using namespace std;

// Cumulative distribution function of the standard normal distribution
double cdf_normal(double x)
{
    return 0.5 * (1.0 + erf(x / sqrt(2.0)));
}

// Calculate call option price using the Black-Scholes formula
double black_scholes_call(double S, double K, double r, double sigma, double T)
{
    double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * sqrt(T);
    return S * cdf_normal(d1) - K * exp(-r * T) * cdf_normal(d2);
}

// Calculate put option price using the Black-Scholes formula
double black_scholes_put(double S, double K, double r, double sigma, double T)
{
    double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * sqrt(T));
    double d2 = d1 - sigma * sqrt(T);
    return K * exp(-r * T) * cdf_normal(-d2) - S * cdf_normal(-d1);
}

int main()
{
    // Define parameters
    double S = 100.0;   // Current stock price
    double K = 100.0;   // Strike price
    double r = 0.05;    // Risk-free interest rate
    double sigma = 0.2; // Volatility
    double T = 1.0;     // Time to expiration

    // Calculate option prices
    double call_price = black_scholes_call(S, K, r, sigma, T);
    double put_price = black_scholes_put(S, K, r, sigma, T);

    // Display results
    cout << "Black-Scholes Option Pricing:" << endl;
    cout << "Current Stock Price: " << S << endl;
    cout << "Strike Price: " << K << endl;
    cout << "Risk-Free Rate: " << r << endl;
    cout << "Volatility: " << sigma << endl;
    cout << "Time to Expiration: " << T << endl;
    cout << "Call Option Price: " << call_price << endl;
    cout << "Put Option Price: " << put_price << endl;

    return 0;
}
