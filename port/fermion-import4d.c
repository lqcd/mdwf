#include <mdwf.h>

int
QX(import_4d_fermion)(struct QX(Fermion) **fermion_ptr,
                      struct Q(State) *state,
                      void (*reader)(double *val_re,
                                     double *val_im,
                                     const int pos[4],
                                     int color,
                                     int dirac,
                                     void *env),
                      void *env)
{
  if (QX(allocate_fermion)(fermion_ptr, state) != 0)
    return 1;

  int size = state->Ls * Q(FERMION_DIM) * Q(COLORS) * 2;
  double m[size];

  for (int i = 0; i < size; i++)
      m[i] = 0;

  BEGIN_TIMING(state);
  qx(x4_import)(&state->even, m, (*fermion_ptr)->even, reader, env);
  qx(x4_import)(&state->odd, m, (*fermion_ptr)->odd, reader, env);
  END_TIMING(state, 0, 0, 0);

  return 0;
}
