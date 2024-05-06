
#include <stdint.h>

#define DIV10(x)        ((x + x/2 + x/16 + x/32) >> 4)


//int8_t div(int8_t v)
//{
//    return DIV10(v);
//}

//uint16_t shift(uint16_t v)
//{
//    return v << 2;
//}

uint16_t udiv(uint16_t up, uint16_t divisor)
{
    union {
        uint32_t v;
        struct {
            uint16_t lower;
            uint16_t upper;
        };
    } mant = { up };
    uint8_t counter = 16;
    uint16_t res = 0;

    while (counter > 0) {
        mant.v <<= 1;
        res <<= 1;
        if (mant.upper > divisor)     {
            mant.upper -= divisor;
            res |= 1;
        }
        --counter;
    }
    return res;
}

