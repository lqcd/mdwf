#include <mdwf.h>

/* Solve
 *   D_dw psi = eta
 *
 * with psi_0 as an initial guess
 *
 */ 

#define MAX_OPTIONS (Q(LOG_CG_RESIDUAL)     | \
                     Q(LOG_TRUE_RESIDUAL)   | \
                     Q(FINAL_CG_RESIDUAL)   | \
                     Q(FINAL_DIRAC_RESIDUAL))

int
QX(DDW_CG)(struct QX(Fermion)          *psi,
           int                         *out_iterations,
           double                      *out_epsilon,
           const struct Q(Parameters)  *params,
           const struct QX(Fermion)    *psi_0,
           const struct QX(Gauge)      *gauge,
           const struct QX(Fermion)    *eta,
           int                          max_iterations,
           double                       min_epsilon,
           unsigned int                 options)
{
    DECLARE_STATE;
    long long flops = 0;
    long long sent = 0;
    long long received = 0;
    void *ptr = 0;
    size_t ptr_size = 0;
    void *temps = 0;
    struct SUn *U = 0;
    int status = 1;
    struct Fermion *xi_e = 0;
    struct Fermion *chi_e = 0;
    struct Fermion *rho_e = 0;
    struct Fermion *pi_e = 0;
    struct Fermion *zeta_e = 0;
    struct Fermion *t0_e = 0;
    struct Fermion *t1_e = 0;
    struct Fermion *t2_e = 0;
    struct Fermion *t0_o = 0;
    double dirac_residual = 0;
    double rhs_norm = 0;

    /* check arguments */
    CHECK_ARG0(psi);
    CHECK_ARGn(params, "DDW_CG");
    CHECK_ARGn(psi_0, "DDW_CG");
    CHECK_ARGn(gauge, "DDW_CG");
    CHECK_ARGn(eta, "DDW_CG");

    /* setup communication */
    if (q(setup_comm)(state, sizeof (REAL))) {
        return q(set_error)(state, 0, "DDW_CG(): communication setup failed");
    }

    /* allocate locals */
    ptr = qx(allocate_eo)(state, &ptr_size, &temps,
                          0, /* header */
                          8, /* evens */
                          1); /* odds */
    if (ptr == 0) {
        return q(set_error)(state, 0, "DDW_CG(): not enough memory");
    }
    U = gauge->data;
    t0_e  = temps;
    t1_e  = temps = qx(step_even)(state, temps);
    t2_e  = temps = qx(step_even)(state, temps);
    xi_e  = temps = qx(step_even)(state, temps);
    chi_e = temps = qx(step_even)(state, temps);
    rho_e = temps = qx(step_even)(state, temps);
    pi_e = temps = qx(step_even)(state, temps);
    zeta_e = temps = qx(step_even)(state, temps);
    t0_o  = temps = qx(step_even)(state, temps);

    /* clear bits we do not understand */
    options = options & MAX_OPTIONS;

    BEGIN_TIMING(state);
    /* compute the norm of the RHS */
    flops += qx(op_norm2)(&rhs_norm, eta, state);
    if (options) {
        qx(zprint)(state, "DDW CG", "rhs norm %e normalized epsilon %e",
                   rhs_norm, min_epsilon * rhs_norm);
    }
    
    /* precondition */
    qx(cg_precondition)(xi_e, chi_e, state, params,
                        U, psi_0->even, eta->even, eta->odd,
                        &flops, &sent, &received,
                        t0_e, t1_e, t0_o);

    /* solve */
    status = qx(cg_solver)(xi_e, "DDW CG", out_iterations, out_epsilon,
                           state, params, U,
                           chi_e, NULL,
                           max_iterations, min_epsilon * rhs_norm, options,
                           &flops, &sent, &received,
                           rho_e, pi_e, zeta_e,
                           t0_e, t1_e, t2_e, t0_o);
    /* handle zero mode properly */
    if (status > 1) {
        END_TIMING(state, flops, sent, received);
        goto end;
    }

    /* inflate */
    qx(cg_inflate)(psi->even, psi->odd,
                   state, params, U, eta->odd, xi_e,
                   &flops, &sent, &received,
                   t0_o);
    
    if (options & Q(FINAL_DIRAC_RESIDUAL)) {
        dirac_residual = qx(cg_dirac_error)(psi->even, psi->odd,
                                            state, params, U,
                                            eta->even, eta->odd,
                                            &flops, &sent, &received,
                                            t0_e, t1_e, t0_o);
    }

    END_TIMING(state, flops, sent, received);

    /* output final residuals if desired */
    if (options) {
        qx(zprint)(state, "DDW CG", "status %d, total iterations %d",
                  status, *out_iterations);
    }
    if (options & (Q(FINAL_CG_RESIDUAL) | Q(LOG_CG_RESIDUAL))) {
        double norm = rhs_norm == 0? 1: rhs_norm;

        qx(zprint)(state, "DDW CG", "solver residual %e normalized %e",
                   *out_epsilon, *out_epsilon / norm);
    }
    if (options & Q(FINAL_DIRAC_RESIDUAL)) {
        double norm = rhs_norm == 0? 1: rhs_norm;

        qx(zprint)(state, "DDW CG", "Dirac residual %e normalized %e",
                   dirac_residual, dirac_residual / norm);
    }
    if (rhs_norm != 0.0)
        *out_epsilon = *out_epsilon / rhs_norm;

end:
    /* free memory */
    q(free)(state, ptr, ptr_size);
    if (status != 0) {
        q(set_error)(state, 0, "DDW_CG() solver failed to converge");
    }
    return status;
}
