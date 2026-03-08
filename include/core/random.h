// Copyright (c) 2014-2017 Melissa O'Neill and PCG Project contributors

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef TINYMLL_RANDOM_H
#define TINYMLL_RANDOM_H

#include "core/types.h"

struct pcg_state_setseq_64 {
    u64 state;
    u64 inc;
};

typedef struct pcg_state_setseq_64      tinymll_rng_state;
#define rng_state                       tinymll_rng_state 


extern u64 
pcg_advance_lcg_64(u64 state, u64 delta, u64 cur_mult, u64 cur_plus);

#define PCG_DEFAULT_MULTIPLIER_64  6364136223846793005ULL
#define PCG_DEFAULT_INCREMENT_64   1442695040888963407ULL

inline u32 pcg_rotr_32(u32 value, unsigned int rot)
{
#if __clang__ && (__x86_64__  || __i386__)
    asm ("rorl   %%cl, %0" : "=r" (value) : "0" (value), "c" (rot));
    return value;
#else
    return (value >> rot) | (value << ((- rot) & 31));
#endif
}

inline u32 
pcg_output_xsh_rr_64_32(u64 state)
{
    return pcg_rotr_32(((state >> 18u) ^ state) >> 27u, state >> 59u);
}

inline void 
pcg_setseq_64_step_r(rng_state* rng)
{
    rng->state = rng->state * PCG_DEFAULT_MULTIPLIER_64 + rng->inc;
}

inline u32
pcg_setseq_64_xsh_rr_32_random_r(rng_state* rng)
{
    u64 oldstate = rng->state;
    pcg_setseq_64_step_r(rng);
    return pcg_output_xsh_rr_64_32(oldstate);
}

inline u32
pcg_setseq_64_xsh_rr_32_boundedrand_r(rng_state* rng, u32 bound)
{
    u32 threshold = -bound % bound;
    for (;;) {
        u32 r = pcg_setseq_64_xsh_rr_32_random_r(rng);
        if (r >= threshold)
            return r % bound;
    }
}

inline void 
pcg_setseq_64_srandom_r(rng_state* rng, u64 initstate, u64 initseq)
{
    rng->state = 0U;
    rng->inc = (initseq << 1u) | 1u;
    pcg_setseq_64_step_r(rng);
    rng->state += initstate;
    pcg_setseq_64_step_r(rng);
}

inline void 
pcg_setseq_64_advance_r(rng_state* rng, u64 delta)
{
    rng->state = pcg_advance_lcg_64(rng->state, delta, PCG_DEFAULT_MULTIPLIER_64, rng->inc);
}

// Seed random nunber generator
#define tinymll_seed_rng                pcg_setseq_64_srandom_r
// Advance random namber generator
#define tinymll_advance_rng             pcg_setseq_64_advance_r
// Get a random number 0 <= x < 2^(32)
#define tinymll_random                  pcg_setseq_64_xsh_rr_32_random_r
// Get a random number 0 <= x < bound
#define tinymll_bounded_random          pcg_setseq_64_xsh_rr_32_boundedrand_r

#include <math.h>

// Get a random number 0.0 <= x < 1.0
inline f32
tinymll_unit_random(rng_state* rng)
{
    return ldexpf(tinymll_random(rng), -32);
}

// Get a random number min_f <= x < max_f
inline f32
tinymll_real_bounded_random(rng_state* rng, f32 min, f32 max)
{
    return min + (max - min) * tinymll_unit_random(rng);
}

#define seed_rng            tinymll_seed_rng 
#define advance_rng         tinymll_advance_rng
#define random_             tinymll_random
#define bounded_random      tinymll_bounded_random
#define unit_random         tinymll_unit_random
#define real_bounded_random tinymll_real_bounded_random

#endif // TINYMLL_RANDOM_H