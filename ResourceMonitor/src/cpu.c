#include "../include/cpu.h"

struct timespec t;

double get_overall_cpu_usage() {
    struct sysinfo sysinf;
    memset(&sysinf, 0, sizeof sysinf);
    if (!sysinfo(&sysinf)) {
        float f_load = 1.f / (1 << SI_LOAD_SHIFT);
        return sysinf.loads[0] * f_load * 100/get_nprocs();
    }
}

int getNumberOfProcessors() {

    return get_nprocs();
}

static inline uint64_t getCycles() {     

    unsigned a, d;

    asm volatile("rdtsc" : "=a" (a), "=d" (d));

    return ((uint64_t)a) | (((uint64_t)d) << 32);
}

static inline uint32_t getMillisecondCounter() {

    uint32_t millisecondCounter;
    
    clock_gettime (CLOCK_PROCESS_CPUTIME_ID, &t);
    millisecondCounter = (uint32_t) (t.tv_sec * 1000 + t.tv_nsec / 1000000);

    return millisecondCounter;
}

int getClockSpeed() {

    const uint64_t cycles = getCycles();
    const uint32_t millis = getMillisecondCounter();
    int lastResult = 0;

    for (;;) {

        int n = 1000000;
        while (--n > 0) {}

        const uint32_t milliSecondsElapsed = getMillisecondCounter() - millis;
        const uint64_t cyclesNow = getCycles();

        if (milliSecondsElapsed  > 80) {

            const int newResult = (int) (((cyclesNow - cycles) / milliSecondsElapsed ) / 1000);

            if (milliSecondsElapsed  > 500 || (lastResult == newResult && newResult > 100))
                return newResult;

            lastResult = newResult;
        }
    }
    return lastResult;
}
