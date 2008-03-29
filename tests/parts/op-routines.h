#ifndef MARK_0DAB983B_E5FA_4BCE_AE68_915CE2ABD086
#define MARK_0DAB983B_E5FA_4BCE_AE68_915CE2ABD086

int op_A_even(struct Fermion *result,
	      const struct Q(Parameters) *params,
	      const struct Fermion *fermion);
int op_A_odd(struct Fermion *result,
	     const struct Q(Parameters) *params,
	     const struct Fermion *fermion);
int op_A(struct QX(Fermion) *result,
	 const struct Q(Parameters) *params,
	 const struct QX(Fermion) *fermion);
int op_B_even(struct Fermion *result,
	      const struct Q(Parameters) *params,
	      const struct Fermion *fermion);
int op_B_odd(struct Fermion *result,
	     const struct Q(Parameters) *params,
	     const struct Fermion *fermion);
int op_B(struct QX(Fermion) *result,
	 const struct Q(Parameters) *params,
	 const struct QX(Fermion) *fermion);

#endif /* !defined(MARK_0DAB983B_E5FA_4BCE_AE68_915CE2ABD086) */
