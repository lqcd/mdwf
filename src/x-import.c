#include <mdwf.h>

void
q(x_import)(struct eo_lattice *eo,
	    double r[],
	    struct Fermion *data,
	    double (*reader)(const int pos[Q(DIM)+1],
			     int color,
			     int dirac,
			     int re_im,
			     void *env),
	    void *env)
{
  int size = eo->full_size;
  int *layout2linear = eo->layout2vector;
  int Ls = eo->Ls;
  int i, p, c, d;
  int x[Q(DIM)+1];
  double *v;

  for (p = 0; p < size; p++, layout2linear++) {
    int q = *layout2linear;
    for (i = 0; i < Q(DIM); i++) {
      x[i] = q % eo->dx[i];
      q = q / eo->dx[i];
    }
    for (v = r, x[Q(DIM)] = 0; x[Q(DIM)] < Ls; x[Q(DIM)]++) {
      for (c = 0; c < Q(COLORS); c++) {
	for (d = 0; d < Q(FERMION_DIM); d++) {
	  *v++ = reader(x, c, d, 0, env);
	  *v++ = reader(x, c, d, 1, env);
	}
      }
    }
    qx(put_fermion)(data, p, Ls, r);
  }
}
