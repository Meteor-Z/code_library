#ifndef CODE_DEMO_EPOLL_DEMO_H
#define CODE_DEMO_EPOLL_DEMO_H

#include <ctime>
#include <sys/epoll.h>
#include <sys/time.h>
#include <sys/timerfd.h>
#include <unistd.h>
#include <iostream>

inline void handle_stdin() { std::cout << "标准输入" << std::endl; }
inline void handle_timer() { std::cout << "触发定时器" << std::endl; }

inline void add_stdin(int epoll_fd) {
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;
    event.data.ptr = reinterpret_cast<void*>(handle_stdin);

    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event);
}

inline void add_timer(int epoll_fd, int second) {
    int timer_fd = timerfd_create(CLOCK_MONOTONIC, 0);

    struct itimerspec duration {};

    duration.it_value.tv_sec = second; // 设定2s
    duration.it_value.tv_nsec = 0;
    duration.it_interval.tv_sec = duration.it_value.tv_sec;
    // 每隔2s触发一次
    duration.it_interval.tv_nsec = duration.it_value.tv_nsec;

    timerfd_settime(timer_fd, 0, &duration, nullptr);

    epoll_event event;
    event.events = EPOLLIN;

    event.data.ptr = reinterpret_cast<void*>(handle_timer);

    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, timer_fd, &event);
}
inline void epoll_demo_test() {
    int epoll_fd = epoll_create(100);

    add_stdin(epoll_fd);
    // add_timer(epoll_fd, 2);

    while (true) {
        epoll_event events[4] {};
        const int ready_number = epoll_wait(epoll_fd, events, 4, -1);
        if (ready_number < 0) {
            std::cout << "寄了" << std::endl;
            continue;
        }

        std::cout << ready_number << std::endl;

        for (int i = 0; i < ready_number; i++) {
            auto handler = reinterpret_cast<void (*)()>(events[i].data.ptr);
            handler();
        }
    }
}
#endif