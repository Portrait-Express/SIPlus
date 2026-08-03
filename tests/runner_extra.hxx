#include <csignal>
#include <iostream>
#include <signal.h>
#include <stacktrace>

static bool g_aborted = false;

#ifdef __linux__
static void posix_segv_handler(int sig, siginfo_t *info, void *ucontext) {
    if(g_aborted) {
        return;
    }
    g_aborted = true;

    auto addr = info->si_addr;
    std::cerr << "Received SIGSEGV/SIGABRT. Faulting address:" << addr << std::endl;

    std::cout << std::stacktrace::current() << '\n';

    std::abort();
}
#else
static void std_segv_handler(int code) {
    if(g_aborted) {
        return;
    }
    g_aborted = true;

    std::cerr << "Received SIGSEGV/SIGABRT." << std::endl;

    std::cout << std::stacktrace::current() << std::endl;

    std::abort();
}
#endif

static void initialize(int* pargc, char*** pargv) {
#ifdef __linux__
    struct sigaction act = {0};
    act.sa_sigaction = posix_segv_handler;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV, &act, NULL);
    sigaction(SIGABRT, &act, NULL);
#else
    std::signal(SIGSEGV, std_segv_handler);
    std::signal(SIGABRT, std_segv_handler);
#endif
}
