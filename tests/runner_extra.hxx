#include <csignal>
#include <iostream>
#include <signal.h>

#ifdef SIPLUS_HAS_CPPTRACE
#include <cpptrace/from_current.hpp>
#endif

//static void segv_handler(int sig, siginfo_t *info, void *ucontext) {
//    auto addr = info->si_addr;
//    std::cerr << "Received SIGSEGV/SIGABRT. Faulting address:" << addr << std::endl;
//
//#ifdef SIPLUS_HAS_CPPTRACE
//    cpptrace::stacktrace::current().print();
//#endif
//
//    std::abort();
//}

static void std_segv_handler(int code) {
    std::cerr << "Received SIGSEGV/SIGABRT." << std::endl;

#ifdef SIPLUS_HAS_CPPTRACE
    cpptrace::stacktrace::current().print();
#endif

    std::cout << std::flush; //flush stdout to make sure its all written

    std::abort();
}

static void initialize(int* pargc, char*** pargv) {
    std::signal(SIGSEGV, std_segv_handler);

    //struct sigaction act = {0};
    //act.sa_sigaction = segv_handler;
    //act.sa_flags = SA_SIGINFO;
    //sigaction(SIGSEGV, &act, NULL);
    //sigaction(SIGABRT, &act, NULL);
}
