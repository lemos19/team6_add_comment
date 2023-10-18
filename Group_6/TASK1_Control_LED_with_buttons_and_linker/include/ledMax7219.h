#ifndef _LED_H_
#define _LED_H_
#include <stdint.h>
typedef enum{
    _0 = 0x7E,
    _1 = 0x30,
    _2 = 0x6D,
    _3 = 0x79,
    _4 = 0x33,
    _5 = 0x5B,
    _6 = 0x5F,
    _7 = 0x70,
    _8 = 0x7F,
    _9 = 0x7B,
    _off = 0x00,
    _up = 0x40,
    _down = 0x08,
    _mid = 0x01,
    _leftUp= 0x02,
    _leftDown = 0x04,
    _rightUp = 0x20,
    _rightDown = 0x10
}Number_Print_t;
typedef enum{
    Led_1 = 0x01,
    Led_2 = 0x02,
    Led_3 = 0x03,
    Led_4 = 0x04,
    Led_5 = 0x05,
    Led_6 = 0x06,
    Led_7 = 0x07,
    Led_8 = 0x08
}Led_add;
typedef enum{
    no_dot,
    dot
}Dot_t;
uint16_t Printf_led(Number_Print_t,Led_add,Dot_t);
void ConfigledMAX7219(void);
void StartUPled(void);
#endif
