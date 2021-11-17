#ifndef GB_THREAD_HPP
#define GB_THREAD_HPP

#include <thread>
#include <memory>

class GBThread {
private:
    bool is_stop_ = true;
    std::unique_ptr<std::thread> t_ = nullptr;

public:
    GBThread() = default;
    ~GBThread() {
        StopInterval();
    }

    template <typename T>
    void SetTimeout(T function, int delay) {
        StopInterval();

        is_stop_ = false;
        t_ = std::make_unique<std::thread>(
                [=]() {
                    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
                    if(is_stop_) return;
                    function();
                }
        );
    }

    template <typename T>
    void SetInterval(T function, int interval) {
        StopInterval();

        is_stop_ = false;
        t_ = std::make_unique<std::thread>(
                [=]() {
                    while(true) {
                        std::chrono::system_clock::time_point next_time =
                                std::chrono::system_clock::now() + std::chrono::milliseconds(interval);

                        if(is_stop_) return;
                        function();

                        std::this_thread::sleep_until(next_time);
                    }
                }
        );
    }

    void StopInterval() {
        is_stop_ = true;
        Join();
        t_.reset();
    }

    void Join() {
        if (t_ && t_->joinable()) {
            t_->join();
        }
    }

    bool isStopped() const {
        return is_stop_;
    }
};
#endif

