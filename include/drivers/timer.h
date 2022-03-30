#pragma once

#include <ports.h>
#include <types.h>
#include <cpu/isr.h>

void timer_callback();

void init_timer(uint32_t freq);

void uptime();

uint32_t getTime();

void sleep(uint32_t time);