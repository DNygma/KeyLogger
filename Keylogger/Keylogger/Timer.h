#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <thread>

class Timer{
    std::thread Thread;
    bool Alive = false;
    long CallNumber = -1L;
    // L for long so it does not become int
    long repeat_count = -1L; // count amount of times certain functions are called
    std::chrono::milliseconds interval = std::chrono::milliseconds(0);
    std::function<void(void)> funct = nullptr;

    void SleepAndRun(){
        std::this_thread::sleep_for(interval);
        if(Alive){
            Function()();
            // second parentheses calls function that function Function returns
        }
    }

    void ThreadFunc(){
        if(CallNumber == Infinite)
            while(Alive)
                SleepAndRun();
            else
                while(repeat_count--)
                    SleepAndRun();
    }

public:
        static const long Infinite = -1L;
        Timer(){}

        Timer(const std::function<void(void)> &f) : funct (f) {}

        Timer(const std::function<void(void)> &f,
              const unsigned long &i,
              const long repeat = Timer::Infinite) : funct (f),
                                                     interval(std::chrono::milliseconds(i)),
                                                     CallNumber(repeat){}

    void Start(bool Async = true){
        if(IsAlive())
            return;
        Alive = true;
        repeat_count = CallNumber;
        if(Async)
            Thread = std::thread(ThreadFunc, this);
        else
            this->ThreadFunc();
    }

    void Stop(){
        Alive = false;
        Thread.join();
    }

    void SetFunction(const std::function<void(void)> &f){
        funct = f;
    }

    bool IsAlive() const {return Alive;};

    //Sets number of repeats
    void RepeatCount (const long r){
        if(Alive)
            return;
        CallNumber = r;
    }

    long GetLeftCount() const {return repeat_count;}

    long RepeatCount() const {return CallNumber;}

    void SetInterval(const unsigned long &i){
        if(Alive)
            return;
        interval =std::chrono::milliseconds(i);
    }

    unsigned long Interval() const {return interval.count();}

    const std::function<void(void)> &Function() const{
        return funct;
    }
};

#endif // TIMER_H
