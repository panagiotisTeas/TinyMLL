#include "core/random.h"

u64 
pcg_advance_lcg_64(u64 state, u64 delta, u64 cur_mult, u64 cur_plus)
{
    u64 acc_mult = 1u;
    u64 acc_plus = 0u;
    while (delta > 0) {
        if (delta & 1) {
            acc_mult *= cur_mult;
            acc_plus = acc_plus * cur_mult + cur_plus;
        }
        cur_plus = (cur_mult + 1) * cur_plus;
        cur_mult *= cur_mult;
        delta /= 2;
    }
    return acc_mult * state + acc_plus;
}