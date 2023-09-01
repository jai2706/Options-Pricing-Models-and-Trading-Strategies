#include <bits/stdc++.h>
using namespace std;

struct StockData
{
    string date;
    double price;
};

vector<StockData> generateRandomPrices(int numDays, double initialPrice, double volatility)
{
    vector<StockData> prices;
    double price = initialPrice;
    for (int day = 1; day <= numDays; day++)
    {
        price *= (1 + (static_cast<double>(rand() % 21 - 10) / 100.0) * volatility);
        prices.push_back({"2023-08-" + to_string(day), price});
    }
    return prices;
}

double calculateSMA(const vector<StockData> &prices, int window)
{
    double sum = 0.0;
    for (int i = prices.size() - window; i < prices.size(); i++)
    {
        sum += prices[i].price;
    }
    return sum / window;
}

double calculateATR(const vector<StockData> &prices, int window)
{
    double sumTrueRanges = 0.0;
    for (int i = prices.size() - window + 1; i < prices.size(); i++)
    {
        double trueRange = max(prices[i].price - prices[i - 1].price,
                               max(abs(prices[i].price - prices[i - 1].price), abs(prices[i - 1].price - prices[i].price)));
        sumTrueRanges += trueRange;
    }
    return sumTrueRanges / window;
}

double calculateRSI(const vector<StockData> &prices, int window)
{
    double gains = 0.0, losses = 0.0;
    for (int i = prices.size() - window; i < prices.size(); i++)
    {
        double priceChange = prices[i].price - prices[i - 1].price;
        if (priceChange > 0)
            gains += priceChange;
        else
            losses -= priceChange;
    }
    double avgGain = gains / window;
    double avgLoss = losses / window;

    if (avgLoss == 0)
        return 100.0;

    double rs = avgGain / avgLoss;
    double rsi = 100.0 - (100.0 / (1 + rs));
    return rsi;
}

void advancedTradingStrategy(const string &symbol, const vector<StockData> &historicalPrices)
{
    int window = 20;                  // Moving average and ATR window
    double initialCapital = 100000.0; // Initial capital for trading

    vector<double> upperBands, lowerBands;

    for (int i = window - 1; i < historicalPrices.size(); i++)
    {
        double sma = calculateSMA(historicalPrices, window);
        double atr = calculateATR(historicalPrices, window);
        double rsi = calculateRSI(historicalPrices, window);

        double upperBand = sma + atr * 1.5; // Adjusted using ATR
        double lowerBand = sma - atr * 1.5; // Adjusted using ATR

        upperBands.push_back(upperBand);
        lowerBands.push_back(lowerBand);
    }

    double capital = initialCapital;
    double shares = 0.0;

    for (int i = window - 1; i < historicalPrices.size(); i++)
    {
        double price = historicalPrices[i].price;
        double upperBand = upperBands[i - (window - 1)];
        double lowerBand = lowerBands[i - (window - 1)];

        double rsi = calculateRSI(historicalPrices, window);

        if (price > upperBand && rsi < 30)
        {
            if (shares == 0.0)
            {
                shares = capital / price;
                capital = 0.0;
            }
        }
        else if (price < lowerBand && shares > 0.0)
        {
            capital = shares * price;
            shares = 0.0;
        }
    }

    double finalCapital = capital + (shares * historicalPrices.back().price);
    double totalProfit = finalCapital - initialCapital;
    double percentageReturn = (totalProfit / initialCapital) * 100.0;

    // Print final results
    cout << "Initial Capital: " << initialCapital << endl;
    cout << "Final Capital: " << finalCapital << endl;
    cout << "Total Profit/Loss: " << totalProfit << endl;
    cout << "Percentage Return/Loss: " << percentageReturn << "%" << endl;
}

int main()
{
    srand(time(NULL));

    string stockSymbol = "AAPL";
    int numDays = 30;
    double initialPrice = 100.0;
    double volatility = 0.2;
    int numSimulations = 1000; // Number of simulations

    double totalPercentageReturns = 0.0;
    double totalPercentageLosses = 0.0;
    int profitableSimulations = 0;
    int lossSimulations = 0;

    for (int sim = 1; sim <= numSimulations; sim++)
    {
        vector<StockData> historicalPrices = generateRandomPrices(numDays, initialPrice, volatility);

        advancedTradingStrategy(stockSymbol, historicalPrices);

        double initialCapital = 100000.0;
        double finalCapital = initialCapital + (historicalPrices.back().price - initialPrice) * (initialCapital / initialPrice);
        double percentageReturn = ((finalCapital - initialCapital) / initialCapital) * 100.0;

        if (percentageReturn > 0)
        {
            totalPercentageReturns += percentageReturn;
            profitableSimulations++;
        }
        else if (percentageReturn < 0)
        {
            totalPercentageLosses += percentageReturn;
            lossSimulations++;
        }
    }

    double averagePercentageReturn = totalPercentageReturns / profitableSimulations;
    double averagePercentageLoss = totalPercentageLosses / lossSimulations;

    cout << "Average Percentage Return from " << profitableSimulations << " Profitable Simulations: " << averagePercentageReturn << "%" << endl;
    cout << "Average Percentage Loss from " << lossSimulations << " Losing Simulations: " << averagePercentageLoss << "%" << endl;

    return 0;
}
