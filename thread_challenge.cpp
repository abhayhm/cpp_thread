/* 
 * Question:
 * Given number of threads, string and number of characters to print.
 * Challenge is to print given number of characters from string in each thread in a circular way.
 * 
 * Input: ./<executable> 3 4 2 abcdefghijklm
 * 
 * Output:
 * Input: Thread count 3 | Char count 4 | Iterations 2 | String abcdefghijklm
 * Created Thread 1 with ID: 140351054304832
 * Created Thread 2 with ID: 140351045912128
 * Created Thread 3 with ID: 140351037519424
 * Thread 0 :abcd
 * Thread 1 :efgh
 * Thread 2 :ijkl
 * Thread 0 :mabc
 * Thread 1 :defg
 * Thread 2 :hijk
 * 
 */

#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <mutex>
#include <chrono>
#include <condition_variable>

using namespace std;

class print_job{
private:
    // Input parameters
    int thread_count;
    int char_count;
    int iterations;
    string str;

    // Required data structures
    vector<thread> threads;
    vector<std::thread::id> thread_ids;

    // Required counters
    int current_index;
    int allowed_thread;

    // Conditional variable and mutex for thread syncronization
    condition_variable condition;
    mutex mutex_lock;


public:
    print_job(int thread_count, int char_count, int iterations, string str){
        this->str = str;
        this->char_count = char_count;
        this->thread_count = thread_count;
        this->iterations = iterations;
        this->current_index = 0;
        this->allowed_thread = 0;
    }

    void print_chars(){
        cout<<"Thread "<<allowed_thread<<" :";
        for(int i = 0; i < char_count; i++){
            cout<<str[current_index];
            current_index = (current_index + 1) % str.length();
        }
        cout<<endl;
    }

    void print_thread(){
        while((thread_count) != (thread_ids.size()));
        std::this_thread::sleep_for(std::chrono::seconds(1));

        for(int iter = 0; iter < iterations; iter++){
            unique_lock<mutex> print_lock(mutex_lock);
            condition.wait(print_lock, [this]{ return thread_ids.at(allowed_thread) == std::this_thread::get_id();});
            
            print_chars();
            allowed_thread = (allowed_thread + 1) % thread_count;
            print_lock.unlock();
            condition.notify_all();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    }

    void run_threads(){
        for (int i = 0; i < thread_count; i++){
            thread t(&print_job::print_thread, this);
            cout<<"Created Thread "<<i+1<<" with ID: "<<t.get_id()<<endl;
            threads.push_back(std::move(t));
            thread_ids.push_back((threads.at(i)).get_id());
        }

        for(int i = 0; i < this->thread_count; i++){
            (threads.at(i)).join();
        }
    }
};

int main(int argc, char *argv[]){
    if(argc < 5){
        cout<<"Invalid input"<<endl;
        return EXIT_FAILURE;
    }
    
    int thread_count = std::atoi(argv[1]);
    int char_count = std::atoi(argv[2]);
    int iterations = std::atoi(argv[3]);
    string str = argv[4];

    cout<<"Input: "<<"Thread count "<<thread_count<<" | "<<"Char count "<<char_count <<" | "<<"Iterations "<<iterations<<" | "<<"String "<<str<<endl;
    print_job print_job1(thread_count, char_count, iterations, str);
    print_job1.run_threads();

    return EXIT_SUCCESS;
}