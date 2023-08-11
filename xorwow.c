struct xwrand_state {
    u32 a, b, c, d, e;
    u32 counter;
};

typedef struct xwrand_state xwrand_t;

/* The state array must be initialized to not be all zero in the first four words */
u32 xwrand(xwrand_t *state)
{
    /* Algorithm "xorwow" from p. 5 of Marsaglia, "Xorshift RNGs" */
    u32 t  = state->e;

    u32 s  = state->a;  /* Perform a contrived 32-bit shift. */
    state->e = state->d;
    state->d = state->c;
    state->c = state->b;
    state->b = s;

    t ^= t >> 2;
    t ^= t << 1;
    t ^= s ^ (s << 4);
    state->a = t;
    state->counter += 362437;
    return t + state->counter;
}

void xwrand_seed(xwrand_t *state, u32 seedval){
        state->a ^= seedval;
        xwrand(state);
}

xwrand_t xwrand_init(u32 initval){
        xwrand_t ret = {2559557ul, 7695157ul, 2456536ul, 8939310ul, 4246576ul, 2070602ul};
        xwrand_seed(&ret, initval);
        return ret;
}

