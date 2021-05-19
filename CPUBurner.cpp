#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <climits>
#include <string>
using std::string;
using std::getline;
#include <pthread.h>

#if defined(__MINGW32__ ) && !defined(_GLIBCXX_HAS_GTHREADS)
#include <thread>
#else
#define MINGW_STDTHREAD_REDUNDANCY_WARNING
#include "mingw.thread.h"
#endif

#include "utils.h"
#include "CPUBurner.h"

// Remove following 3 comment line if [multiple definition of "windows_console_handle"] error thrown
// #ifdef WINDOWS_SYSTEM
// extern HANDLE windows_console_handle; // NOLINT(readability-redundant-declaration)
// #endif

#define CPU_BURN_TYPE_EMPTY_LOOP 1
#define CPU_BURN_TYPE_BOOL 2
#define CPU_BURN_TYPE_FPU 3
#define CPU_BURN_TYPE_DOUBLE_FPU 4
#define CPU_BURN_TYPE_REGISTER 5

/**
 * CPUBurner.cpp internal static functions
 * Function call only inside this CPUBurner.cpp
 **/
void burn_internal(CPUBurner *burner);
[[noreturn]]
void burn_internal_empty_loop();
[[noreturn]]
void burn_internal_bool();
[[noreturn]]
void burn_internal_register();
[[noreturn]]
void burn_internal_fpu();
[[noreturn]]
void burn_internal_double_fpu();

void *pthread_burn(void *arg);

void CPUBurner::menu() {
    cout << "=|BURN-CPU|====================" << endl
         << "= 1) Empty loop" << endl
         << "= 2) Boolean loop" << endl
         << "= 3) FPU" << endl
         << "= 4) Double FPU" << endl
         << "= 5) Register";
#ifdef WINDOWS_SYSTEM
    // HANDLE windows_console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(windows_console_handle, WIN_CONSOLE_BOLDRED);
    cout << " [BE CAUTIOUS]" << endl;
    SetConsoleTextAttribute(windows_console_handle, WIN_CONSOLE_RESET);
#else
    cout << LINUX_TERMINAL_BOLDRED << " [BE CAUTIOUS]" << LINUX_TERMINAL_RESET << endl;
#endif
    Burner::menu();
}

CPUBurner::CPUBurner() {
    _cpu_max_thread = (int) std::thread::hardware_concurrency() - 1;
    _threads = (pthread_t *) malloc(_cpu_max_thread);
}

void CPUBurner::prepare() {
    Burner::prepare();
}

void CPUBurner::burn() {
    for (int i = 0; i < _cpu_max_thread; ++i) {
        pthread_create(&_threads[i], nullptr, pthread_burn, (void *) this);
    }
    burn_internal(this);
}

/** Internal function operating content **/
void *pthread_burn(void *arg) {
    burn_internal((CPUBurner *) arg);
    return nullptr;
}

void burn_internal(CPUBurner *burner) {
    switch (burner->get_type()) {
        case CPU_BURN_TYPE_EMPTY_LOOP:
            burn_internal_empty_loop();
        case CPU_BURN_TYPE_BOOL:
            burn_internal_bool();
        case CPU_BURN_TYPE_FPU:
            burn_internal_fpu();
        case CPU_BURN_TYPE_DOUBLE_FPU:
            burn_internal_double_fpu();
        case CPU_BURN_TYPE_REGISTER:
            burn_internal_register();
        case BURNER_TYPE_INIT:
        default:
            cout << "Unknown burning method: " << burner->get_type() << endl;
            break;
    }
}

[[noreturn]]
void burn_internal_empty_loop() {
    while (true);
}

[[noreturn]]
void burn_internal_bool() {
    bool boolean = false;
    while (true) {
        boolean = !boolean;
    }
}

float get_fpu_value(int index) {
    return (float) ((index % 2) ? 1 : -1) * (1 / (2 * (float) index + 1));
}

[[noreturn]]
void burn_internal_fpu() {
    float float_point;
    while (true) {
        float_point = 0;
        for (int i = 1; i < INT_MAX; ++i) {
            float_point += get_fpu_value(i);
        }
    }
}

double get_double_fpu_value(int index) {
    return (double) ((index % 2) ? 1 : -1) * (1.0 / (2 * (double) index + 1));
}

[[noreturn]]
void burn_internal_double_fpu() {
    double double_float_point;
    while (true) {
        double_float_point = 0;
        for (int i = 1; i < INT_MAX; ++i) {
            double_float_point += get_double_fpu_value(i);
        }
    }
}

[[noreturn]]
void burn_internal_register() {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wregister"
    register int reg;
#pragma clang diagnostic pop
    while (true) {
        reg = 0;
        for (int i = 0; i < INT_MAX; ++i) {
            reg++;
        }
    }
}

#undef CPU_BURN_TYPE_EMPTY_LOOP
#undef CPU_BURN_TYPE_BOOL
#undef CPU_BURN_TYPE_FPU
#undef CPU_BURN_TYPE_DOUBLE_FPU
#undef CPU_BURN_TYPE_REGISTER