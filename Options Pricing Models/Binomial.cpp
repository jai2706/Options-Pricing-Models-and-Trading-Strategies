#include <bits/stdc++.h>
using namespace std;

double binomial_option_pricing(double S, double K, double r, double sigma, double T, int steps, char type)
{
    double dt = T / steps;
    double u = exp(sigma * sqrt(dt));
    double d = 1.0 / u;
    double p = (exp(r * dt) - d) / (u - d);

    vector<vector<double>> prices(steps + 1, vector<double>(steps + 1));

    for (int j = 0; j <= steps; j++)
    {
        prices[steps][j] = max(0.0, (type == 'C' ? 1 : -1) * (S * pow(u, j) * pow(d, steps - j) - K));
    }

    for (int i = steps - 1; i >= 0; i--)
    {
        for (int j = 0; j <= i; j++)
        {
            prices[i][j] = exp(-r * dt) * (p * prices[i + 1][j + 1] + (1 - p) * prices[i + 1][j]);
        }
    }

    return prices[0][0];
}

int main()
{
    double S = 100.0;   // Current stock price
    double K = 100.0;   // Strike price
    double r = 0.05;    // Risk-free interest rate
    double sigma = 0.2; // Volatility
    double T = 1.0;     // Time to expiration
    int steps = 100;    // Number of steps
    char type = 'C';    // 'C' for call option, 'P' for put option

    double option_price = binomial_option_pricing(S, K, r, sigma, T, steps, type);

    cout << "Binomial Option Pricing:" << endl;
    cout << "Option Type: " << (type == 'C' ? "Call" : "Put") << endl;
    cout << "Current Stock Price: " << S << endl;
    cout << "Strike Price: " << K << endl;
    cout << "Risk-Free Rate: " << r << endl;
    cout << "Volatility: " << sigma << endl;
    cout << "Time to Expiration: " << T << endl;
    cout << "Number of Steps: " << steps << endl;
    cout << "Option Price: " << option_price << endl;

    return 0;
}
