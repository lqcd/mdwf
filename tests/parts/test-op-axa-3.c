#include <qop-mdwf3.h>
#include "../../port/mdwf.h"
#include "opxtest.h"
#include "op-routines.h"

char *op_a_name = "mlib:conj(A)";
char *op_b_name = "mlib:A";

double
read_gauge(int dir,
	   const int pos[4],
	   int a, int b,
	   int re_im,
	   void *env)
{
    int i;
    unsigned int v = sum_init(seed_u);

    v = sum_add(v, re_im);
    v = sum_add(v, a);
    v = sum_add(v, b);
    for (i = 0; i < 4; i++) {
	v = sum_add(v, pos[i]);
	v = sum_add(v, dir);
    }
    v = sum_add(v, seed_u);
    return sum_fini(v);
}

static double
read_fermion(unsigned int seed,
	     const int pos[5],
	     int c, int d,
	     int re_im)
{
    int i;
    unsigned int v = sum_init(seed);
    v = sum_add(v, c);
    v = sum_add(v, d);
    v = sum_add(v, re_im);
    for (i = 0; i < 5; i++)
	v = sum_add(v, pos[i]);
    v = sum_add(v, seed);
    return sum_fini(v);
}

double
read_fermion_a(const int pos[5],
	       int c, int d,
	       int re_im,
	       void *env)
{
    return read_fermion(seed_a, pos, c, d, re_im);
}

double
read_fermion_b(const int pos[5],
	       int c, int d,
	       int re_im,
	       void *env)
{
    return read_fermion(seed_b, pos, c, d, re_im);
}

static void
A(struct QX(Fermion) *r,
  const struct Q(Parameters) *params,
  const struct QX(Fermion) *s)
{
    struct Q(State) *state = params->state;
    long long flops = 0;

    qx(op_A)(r->even, &state->even, params, s->even, &flops);
    qx(op_A)(r->odd, &state->odd, params, s->odd, &flops);
	      
}

int
operator_a(void)
{
    double x, y;
    struct QX(Fermion) *fermion_x;

    if (QOP_MDWF_allocate_fermion(&fermion_x, gauge->state)) {
	zprint("operator_A(): alloc failed");
	return 1;
    }

    A(fermion_x, params, fermion_a);
    dot_fermion(&x, &y, fermion_b, fermion_x);

    QOP_MDWF_free_fermion(&fermion_x);
    zprint("normal: %20.10e %20.10e", x, y);
    return 0;
}

static void
Ax(struct QX(Fermion) *r,
   const struct Q(Parameters) *params,
   const struct QX(Fermion) *s)
{
    struct Q(State) *state = params->state;
    long long flops = 0;

    qx(op_Ax)(r->even, &state->even, params, s->even, &flops);
    qx(op_Ax)(r->odd, &state->odd, params, s->odd, &flops);
	      
}

int
operator_b(void)
{
    double x, y;
    struct QX(Fermion) *fermion_x;

    if (QOP_MDWF_allocate_fermion(&fermion_x, gauge->state)) {
	zprint("operator_Ax(): alloc failed");
	return 1;
    }

    Ax(fermion_x, params, fermion_b);
    dot_fermion(&x, &y, fermion_x, fermion_a);
    QOP_MDWF_free_fermion(&fermion_x);
    zprint("conj  : %20.10e %20.10e", x, y);
    return 0;
}
