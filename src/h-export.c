#include <mdwf.h>

int
QX(export_half_fermion)(void (*writer)(const int pos[5],
				       int color,
				       int dirac,
				       int re_im,
				       double value,
				       void *env),
			void *env,
			const struct QX(HalfFermion) *half_fermion)
{
  struct Q(State) *state;
  double *m;
  int size;

  if (half_fermion == 0)
    return 1;

  state = half_fermion->state;
  size = state->Ls * Q(FERMION_DIM) * Q(COLORS) * 2 * sizeof (double);
  m = q(malloc)(state, size);
  if (m == 0) {
    return q(set_error)(state, 0, "export_half_fermion(): not enough space");
  }
  q(x_export)(&state->even, m, half_fermion->even, writer, env);
  q(free)(state, m, size);
  return 0;
}
