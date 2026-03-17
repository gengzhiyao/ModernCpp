#include <iostream>
#include <condition_variable>
#include <queue>
#include <vector>
#include <functional>
#include <thread>
#include <string>
#include <chrono>

class ThreadPool
{
public:
    ThreadPool ( int numThreads )
        :stop ( false )
    {
        for ( int i = 0; i < numThreads; i++ )
        {
            threads.emplace_back ( [this]() {
                for ( ;;)
                {
                    std::unique_lock<std::mutex> lock ( mtx );
                    condition.wait ( lock, [this]() {
                        return !tasks.empty () || stop;
                        } );
                    if ( stop && tasks.empty () ) return;

                    std::function<void ()> task ( std::move ( tasks.front () ) );
                    tasks.pop ();
                    lock.unlock ();
                    task ();
                }

                }
            );
        }

    }

    ~ThreadPool ()
    {
        {
            std::unique_lock<std::mutex> lock ( mtx );
            stop = true;
        }
        condition.notify_all ();

        for ( auto& i : threads )
        {
            i.join ();
        }

    }

    template<class F, class ...Args>
    void enqueue ( F&& f, Args&&... args )
    {
        std::function<void ()> task =
            std::bind ( std::forward<F> ( f ), std::forward<Args> ( args )... );

        {
            std::unique_lock<std::mutex> lock ( mtx );

            if ( stop )
                throw std::runtime_error ( "enqueue on stopped ThreadPool" );

            tasks.emplace ( std::move ( task ) );
        }

        condition.notify_one ();    // 放在锁外面，先解锁，再通知
    }
private:
    std::vector<std::thread> threads;
    std::queue<std::function<void ()>> tasks;
    std::mutex mtx;
    std::condition_variable condition;
    bool stop;
};

std::mutex printMutex;

int main ()
{
    ThreadPool pool ( 4 );
    for ( int i = 0; i < 10; i++ )
    {
        pool.enqueue ( [i]() {
            {
                std::unique_lock<std::mutex> guard ( printMutex );
                std::cout << "tasks : " << i << "start!" << std::endl;
            }
            // 线程等待期间不要锁
            std::this_thread::sleep_for ( std::chrono::seconds ( 1 ) );

            {
                std::unique_lock<std::mutex> guard ( printMutex );
                std::cout << "tasks : " << i << "finished..." << std::endl;
            }
            } );
    }

    return 0;
}