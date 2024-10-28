#include <iostream>
#include <chrono>

class SearchStats
{
public:
    int nodesExplored = 0;
    int backtracks = 0;
    int maxDepth = 0;
    int currentDepth = 0;
    std::chrono::steady_clock::time_point startTime;

    void startTimer()
    {
        startTime = std::chrono::steady_clock::now();
    }

    double elapsedTime() const
    {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = now - startTime;
        return elapsed.count();
    }

    void incrementNode()
    {
        nodesExplored++;
        if (currentDepth > maxDepth)
        {
            maxDepth = currentDepth;
        }
    }

    void incrementBacktrack()
    {
        backtracks++;
    }

    void increaseDepth()
    {
        currentDepth++;
    }

    void decreaseDepth()
    {
        currentDepth--;
    }

    void display() const
    {
        std::cout << "Search Statistics:\n";
        std::cout << "Nodes explored: " << nodesExplored << "\n";
        std::cout << "Backtracks: " << backtracks << "\n";
        std::cout << "Max depth reached: " << maxDepth << "\n";
        std::cout << "Time elapsed: " << elapsedTime() << " seconds\n";
        std::cout << "Nodes per second: " << nodesExplored / elapsedTime() << "\n";
    }
};