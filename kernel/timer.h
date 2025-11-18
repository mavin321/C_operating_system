/* kernel/timer.h */
#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void timer_install(uint32_t frequency);
uint32_t timer_ticks(void);

#endif /* TIMER_H */
