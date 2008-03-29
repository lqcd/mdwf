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
int op_Ax_even(struct Fermion *result,
	       const struct Q(Parameters) *params,
	       const struct Fermion *fermion);
int op_Ax_odd(struct Fermion *result,
	      const struct Q(Parameters) *params,
	      const struct Fermion *fermion);
int op_Ax(struct QX(Fermion) *result,
	  const struct Q(Parameters) *params,
	  const struct QX(Fermion) *fermion);
int op_A1_even(struct Fermion *result,
	       const struct Q(Parameters) *params,
	       const struct Fermion *fermion);
int op_A1_odd(struct Fermion *result,
	      const struct Q(Parameters) *params,
	      const struct Fermion *fermion);
int op_A1(struct QX(Fermion) *result,
	  const struct Q(Parameters) *params,
	  const struct QX(Fermion) *fermion);
int op_Ax1_even(struct Fermion *result,
		const struct Q(Parameters) *params,
		const struct Fermion *fermion);
int op_Ax1_odd(struct Fermion *result,
	       const struct Q(Parameters) *params,
	       const struct Fermion *fermion);
int op_Ax1(struct QX(Fermion) *result,
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
int op_Bx_even(struct Fermion *result,
	       const struct Q(Parameters) *params,
	       const struct Fermion *fermion);
int op_Bx_odd(struct Fermion *result,
	      const struct Q(Parameters) *params,
	      const struct Fermion *fermion);
int op_Bx(struct QX(Fermion) *result,
	  const struct Q(Parameters) *params,
	  const struct QX(Fermion) *fermion);
int op_B1_even(struct Fermion *result,
	       const struct Q(Parameters) *params,
	       const struct Fermion *fermion);
int op_B1_odd(struct Fermion *result,
	      const struct Q(Parameters) *params,
	      const struct Fermion *fermion);
int op_B1(struct QX(Fermion) *result,
	  const struct Q(Parameters) *params,
	  const struct QX(Fermion) *fermion);
int op_Bx1_even(struct Fermion *result,
		const struct Q(Parameters) *params,
		const struct Fermion *fermion);
int op_Bx1_odd(struct Fermion *result,
	       const struct Q(Parameters) *params,
	       const struct Fermion *fermion);
int op_Bx1(struct QX(Fermion) *result,
	   const struct Q(Parameters) *params,
	   const struct QX(Fermion) *fermion);
int op_F_even(struct Fermion *result_even,
	      struct Q(State) *state,
	      const struct SUn *U,
	      const struct Fermion *src_odd);
int op_F_odd(struct Fermion *result_odd,
	     struct Q(State) *state,
	     const struct SUn *U,
	     const struct Fermion *src_even);
int op_F(struct Q(Fermion) *result,
	 struct Q(State) *state,
	 const struct Q(Gauge) *gauge,
	 const struct Q(Fermion) *source);
int op_Fx_even(struct Fermion *result_even,
	       struct Q(State) *state,
	       const struct SUn *U,
	       const struct Fermion *src_odd);
int op_Fx_odd(struct Fermion *result_odd,
	      struct Q(State) *state,
	      const struct SUn *U,
	      const struct Fermion *src_even);
int op_Fx(struct Q(Fermion) *result,
	  struct Q(State) *state,
	  const struct Q(Gauge) *gauge,
	  const struct Q(Fermion) *source);

#endif /* !defined(MARK_0DAB983B_E5FA_4BCE_AE68_915CE2ABD086) */
