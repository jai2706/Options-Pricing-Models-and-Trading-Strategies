#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

double call_payoff(double S, double K)
{
    return std::max(S - K, 0.0);
}

double put_payoff(double S, double K)
{
    return std::max(K - S, 0.0);
}

double random_walk(double S0, double r, double sigma, double T, double Z)
{
    double ST = S0 * std::exp((r - 0.5 * sigma * sigma) * T + sigma * std::sqrt(T) * Z);
    return ST;
}

double monte_carlo_pricing_without_vr(double S0, double K, double r, double sigma, double T, int N, char type)
{
    double sum_payoff = 0.0;
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());

    for (int i = 0; i < N; i++)
    {
        double Z = std::normal_distribution<double>(0.0, 1.0)(generator);
        double ST = random_walk(S0, r, sigma, T, Z);
        double payoff = 0.0;

        if (type == 'C')
        {
            payoff = call_payoff(ST, K);
        }
        else if (type == 'P')
        {
            payoff = put_payoff(ST, K);
        }

        sum_payoff += payoff;
    }

    double price = (sum_payoff / N) * std::exp(-r * T);
    return price;
}

double monte_carlo_pricing_with_vr(double S0, double K, double r, double sigma, double T, int N, char type)
{
    double sum_payoff = 0.0;
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());

    for (int i = 0; i < N; i++)
    {
        double Z = std::normal_distribution<double>(0.0, 1.0)(generator);
        double ST = random_walk(S0, r, sigma, T, Z);
        double payoff = 0.0;

        if (type == 'C')
        {
            payoff = call_payoff(ST, K);
        }
        else if (type == 'P')
        {
            payoff = put_payoff(ST, K);
        }

        sum_payoff += payoff;

        // Implement antithetic variates
        ST = random_walk(S0, r, sigma, T, -Z);

        if (type == 'C')
        {
            payoff = call_payoff(ST, K);
        }
        else if (type == 'P')
        {
            payoff = put_payoff(ST, K);
        }

        sum_payoff += payoff;
    }

    double price = (sum_payoff / (2 * N)) * std::exp(-r * T);
    return price;
}

int main()
{
    double S0 = 100.0;  // Initial stock price
    double K = 100.0;   // Strike price
    double r = 0.05;    // Risk-free interest rate
    double sigma = 0.2; // Volatility
    double T = 1.0;     // Time to maturity
    int N = 100000;     // Number of simulations

    // Calculate option prices without variance reduction
    auto start_time_without_vr = std::chrono::high_resolution_clock::now();
    double call_price_without_vr = monte_carlo_pricing_without_vr(S0, K, r, sigma, T, N, 'C');
    double put_price_without_vr = monte_carlo_pricing_without_vr(S0, K, r, sigma, T, N, 'P');
    auto end_time_without_vr = std::chrono::high_resolution_clock::now();
    auto time_taken_without_vr = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_without_vr - start_time_without_vr).count();

    // Calculate option prices with variance reduction
    auto start_time_with_vr = std::chrono::high_resolution_clock::now();
    double call_price_with_vr = monte_carlo_pricing_with_vr(S0, K, r, sigma, T, N, 'C');
    double put_price_with_vr = monte_carlo_pricing_with_vr(S0, K, r, sigma, T, N, 'P');
    auto end_time_with_vr = std::chrono::high_resolution_clock::now();
    auto time_taken_with_vr = std::chrono::duration_cast<std::chrono::milliseconds>(end_time_with_vr - start_time_with_vr).count();

    std::cout << "Option Prices without Variance Reduction:" << std::endl;
    std::cout << "Call Price: " << call_price_without_vr << std::endl;
    std::cout << "Put Price: " << put_price_without_vr << std::endl;
    std::cout << "Time Taken (without VR): " << time_taken_without_vr << " ms" << std::endl;

    std::cout << "\nOption Prices with Variance Reduction:" << std::endl;
    std::cout << "Call Price: " << call_price_with_vr << std::endl;
    std::cout << "Put Price: " << put_price_with_vr << std::endl;
    std::cout << "Time Taken (with VR): " << time_taken_with_vr << " ms" << std::endl;

    return 0;
}
