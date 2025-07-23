#include <cpptrace/from_current.hpp>
#include <iostream>
#include <signal.h>

static void segv_handler(int sig, siginfo_t *info, void *ucontext) {
    auto addr = info->si_addr;
    std::cerr << "Received SIGSEGV. Faulting address:" << addr << std::endl;
    cpptrace::stacktrace::current().print();
    std::abort();
}


static void initialize(int* pargc, char*** pargv) {
    struct sigaction act = {0};
    act.sa_sigaction = segv_handler;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV, &act, NULL);
}
