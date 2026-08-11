#ifndef IR_H
#define IR_H

#include <stdint.h>

#define IR_MAX_PULSES 512

typedef struct
{
    uint32_t duration_us;
    uint8_t level;
} ir_pulse_t;

typedef struct
{
    ir_pulse_t pulses[IR_MAX_PULSES];
    int count;
} ir_code_t;

int ir_init(int gpio);
int ir_capture(ir_code_t *code);
void ir_print(const ir_code_t *code);
void ir_close(void);

#endif