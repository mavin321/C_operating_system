/* kernel/irq.h */
#ifndef IRQ_H
#define IRQ_H

#include <stdint.h>

typedef void (*irq_handler_t)(void);

void irq_install(void);
void irq_install_handler(int irq, irq_handler_t handler);
void irq_uninstall_handler(int irq);
void irq_handler(uint32_t int_no, uint32_t err_code);

#endif /* IRQ_H */
