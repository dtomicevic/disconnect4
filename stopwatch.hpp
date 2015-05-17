#ifndef PARPRO_CONNECT4_STOPWATCH_HPP
#define PARPRO_CONNECT4_STOPWATCH_HPP

#include <chrono>

template <typename T = std::chrono::microseconds, 
          typename C = std::chrono::high_resolution_clock,
          typename D = double>
class Stopwatch
{
public:
    Stopwatch() { start(); }
    
    void start();
    D stop();
    D elapsed();

private:
    std::chrono::time_point<C> started, ended;
};

template <typename T, typename C, typename D>
void Stopwatch<T, C, D>::start()
{
    started = ended = C::now();
}

template <typename T, typename C, typename D>
D Stopwatch<T, C, D>::stop()
{
    ended = C::now();
    return elapsed();
}

template <typename T, typename C, typename D>
D Stopwatch<T, C, D>::elapsed()
{
    return std::chrono::duration_cast<T>(ended - started).count();
}

#endif
