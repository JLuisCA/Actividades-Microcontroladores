/*
 * timers.h
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_

void timer0_normalmode_noprescaler(void);
void timer0_normalmode_prescaler(void);
void timer0_overflow_interrupt(void);
void timer1_normalmode_noprescaler(void);
void timer1_CTCmode_interrupt(void);
void timer1_CTCmode_nonPWM(void);
void timer1_fastPWM_inverting(void);
void timer2_CTCmode(void);
void Timer2_PhaseCorrectPWMMode_Inverting(void);
void pwm_init(void);
void set_red_intensity(uint8_t intensity);
void set_green_intensity(uint8_t intensity);
void set_blue_intensity(uint8_t intensity);
#endif /* TIMERS_H_ */