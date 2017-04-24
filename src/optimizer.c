/*
 * Qcint is a general GTO integral library for computational chemistry
 * Copyright (C) 2014- Qiming Sun <osirpt.sun@gmail.com>
 *
 * This file is part of Qcint.
 *
 * Qcint is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * optimizer for 2e integrals.  Note if CINT2e_drv is only called a few
 * hundred times, this optimizer cannot really speed up the integration. 
 */

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "cint_const.h"
#include "cint_bas.h"
#include "g1e.h"
#include "g2e.h"
#include "optimizer.h"
#include "misc.h"

// generate caller to CINTinit_2e_optimizer for each type of function
void CINTinit_2e_optimizer(CINTOpt **opt, int *atm, int natm,
                           int *bas, int nbas, double *env)
{
        CINTOpt *opt0 = (CINTOpt *)malloc(sizeof(CINTOpt));
        opt0->index_xyz_array = NULL;
        opt0->non0ctr = NULL;
        opt0->sortedidx = NULL;
        opt0->nbas = 0;

        opt0->data_ptr = NULL;
        opt0->data = NULL;
        *opt = opt0;
}
void CINTinit_optimizer(CINTOpt **opt, int *atm, int natm,
                        int *bas, int nbas, double *env)
{
        CINTinit_2e_optimizer(opt, atm, natm, bas, nbas, env);
}

void CINTdel_2e_optimizer(CINTOpt **opt)
{
        CINTOpt *opt0 = *opt;
        if (opt0 == NULL) { // when opt is created by CINTno_optimizer
                return;
        }

        int i;

        if (opt0->index_xyz_array != NULL) {
                for (i = 0; i < ANG_MAX*ANG_MAX*ANG_MAX*ANG_MAX; i++) {
                        if (opt0->index_xyz_array[i] != NULL) {
                                free(opt0->index_xyz_array[i]);
                        };
                }
                free(opt0->index_xyz_array);
        }

        if (opt0->non0ctr != NULL) {
                for (i = 0; i < opt0->nbas; i++) {
                        free(opt0->sortedidx[i]);
                        free(opt0->non0ctr[i]);
                }
                free(opt0->sortedidx);
                free(opt0->non0ctr);
        }

        if (opt0->data_ptr != NULL) {
                free(opt0->data);
                free(opt0->data_ptr);
        }

        free(opt0);
        *opt = NULL;
}
void CINTdel_optimizer(CINTOpt **opt)
{
        CINTdel_2e_optimizer(opt);
}

void CINTno_optimizer(CINTOpt **opt, int *atm, int natm,
                      int *bas, int nbas, double *env)
{
        *opt = NULL;
}

void CINTall_1e_optimizer(CINTOpt **opt, int *ng,
                          int *atm, int natm, int *bas, int nbas, double *env)
{
        CINTinit_2e_optimizer(opt, atm, natm, bas, nbas, env);
        CINTOpt_set_non0coeff(*opt, atm, natm, bas, nbas, env);
        CINTOpt_2cindex_xyz(*opt, ng, atm, natm, bas, nbas, env);
}

void CINTall_2e_optimizer(CINTOpt **opt, int *ng,
                          int *atm, int natm, int *bas, int nbas, double *env)
{
        CINTinit_2e_optimizer(opt, atm, natm, bas, nbas, env);
        CINTOpt_setij(*opt, ng, atm, natm, bas, nbas, env);
        CINTOpt_set_non0coeff(*opt, atm, natm, bas, nbas, env);
        CINTOpt_4cindex_xyz(*opt, ng, atm, natm, bas, nbas, env);
}

void CINTall_3c2e_optimizer(CINTOpt **opt, int *ng,
                            int *atm, int natm, int *bas, int nbas, double *env)
{
        CINTinit_2e_optimizer(opt, atm, natm, bas, nbas, env);
        CINTOpt_setij(*opt, ng, atm, natm, bas, nbas, env);
        CINTOpt_set_non0coeff(*opt, atm, natm, bas, nbas, env);
        CINTOpt_3cindex_xyz(*opt, ng, atm, natm, bas, nbas, env);
}

void CINTall_2c2e_optimizer(CINTOpt **opt, int *ng,
                            int *atm, int natm, int *bas, int nbas, double *env)
{
        CINTinit_2e_optimizer(opt, atm, natm, bas, nbas, env);
        CINTOpt_set_non0coeff(*opt, atm, natm, bas, nbas, env);
        CINTOpt_2cindex_xyz(*opt, ng, atm, natm, bas, nbas, env);
}

void CINTOpt_3c1eindex_xyz(CINTOpt *opt, int *ng, int *atm, int natm,
                         int *bas, int nbas, double *env);
void CINTall_3c1e_optimizer(CINTOpt **opt, int *ng,
                            int *atm, int natm, int *bas, int nbas, double *env)
{
        CINTinit_2e_optimizer(opt, atm, natm, bas, nbas, env);
        CINTOpt_setij(*opt, ng, atm, natm, bas, nbas, env);
        CINTOpt_set_non0coeff(*opt, atm, natm, bas, nbas, env);
        CINTOpt_3c1eindex_xyz(*opt, ng, atm, natm, bas, nbas, env);
}

static int _make_fakebas(int *fakebas, int *bas, int nbas, double *env)
{
        int i;
        int max_l = 0;
        for (i = 0; i < nbas; i++) {
                max_l = MAX(max_l, bas(ANG_OF,i));
        }

        int fakenbas = max_l + 1;
        for (i = 0; i < BAS_SLOTS*fakenbas; i++) {
                fakebas[i] = 0;
        }
        // fakebas only initializes ANG_OF, since the others does not
        // affect index_xyz
        for (i = 0; i <= max_l; i++) {
                fakebas[BAS_SLOTS*i+ANG_OF] = i;
        }
        return max_l;
}

/* len(ng) = 8. The first 4 items are the increment adding to envs.li_ceil
 * ... envs.ll_ceil for shell i, j, k, l */
void CINTOpt_4cindex_xyz(CINTOpt *opt, int *ng, int *atm, int natm,
                         int *bas, int nbas, double *env)
{
        int i, j, k, l, ptr;
        int n = ANG_MAX*ANG_MAX*ANG_MAX*ANG_MAX;
        opt->index_xyz_array = (int **)malloc(sizeof(int *) * n);
        for (i = 0; i < n; i++) {
                opt->index_xyz_array[i] = NULL;
        }

        int fakebas[BAS_SLOTS*ANG_MAX];
        int max_l = _make_fakebas(fakebas, bas, nbas, env);
        int fakenbas = max_l+1;
        CINTEnvVars envs;
        int shls[4];
        for (i = 0; i <= max_l; i++) {
        for (j = 0; j <= max_l; j++) {
        for (k = 0; k <= max_l; k++) {
        for (l = 0; l <= max_l; l++) {
                shls[0] = i; shls[1] = j; shls[2] = k; shls[3] = l;
                CINTinit_int2e_EnvVars(&envs, ng, shls,
                                       atm, natm, fakebas, fakenbas, env);
                ptr = i*ANG_MAX*ANG_MAX*ANG_MAX
                    + j*ANG_MAX*ANG_MAX
                    + k*ANG_MAX
                    + l;
                opt->index_xyz_array[ptr] =
                        (int *)malloc(sizeof(int)*envs.nf*3);
                CINTg4c_index_xyz(opt->index_xyz_array[ptr], &envs);
        } } } }
}

void CINTOpt_3cindex_xyz(CINTOpt *opt, int *ng, int *atm, int natm,
                         int *bas, int nbas, double *env)
{
        int i, j, k, ptr;
        int n = ANG_MAX*ANG_MAX*ANG_MAX;
        opt->index_xyz_array = (int **)malloc(sizeof(int *) * n);
        for (i = 0; i < n; i++) {
                opt->index_xyz_array[i] = NULL;
        }

        int fakebas[BAS_SLOTS*ANG_MAX];
        int max_l = _make_fakebas(fakebas, bas, nbas, env);
        int fakenbas = max_l+1;
        CINTEnvVars envs;
        int shls[3];
        for (i = 0; i <= max_l; i++) {
        for (j = 0; j <= max_l; j++) {
        for (k = 0; k <= max_l; k++) {
                shls[0] = i; shls[1] = j; shls[2] = k;
                CINTinit_int3c2e_EnvVars(&envs, ng, shls,
                                         atm, natm, fakebas, fakenbas, env);
                ptr = i*ANG_MAX*ANG_MAX + j*ANG_MAX + k;
                opt->index_xyz_array[ptr] =
                        (int *)malloc(sizeof(int)*envs.nf*3);
                CINTg3c_index_xyz(opt->index_xyz_array[ptr], &envs);
        } } }
}

void CINTOpt_2cindex_xyz(CINTOpt *opt, int *ng, int *atm, int natm,
                         int *bas, int nbas, double *env)
{
        int i, j, ptr;
        int n = ANG_MAX*ANG_MAX;
        opt->index_xyz_array = (int **)malloc(sizeof(int *) * n);
        for (i = 0; i < n; i++) {
                opt->index_xyz_array[i] = NULL;
        }

        int fakebas[BAS_SLOTS*ANG_MAX];
        int max_l = _make_fakebas(fakebas, bas, nbas, env);
        int fakenbas = max_l+1;
        CINTEnvVars envs;
        int shls[2];
        for (i = 0; i <= max_l; i++) {
        for (j = 0; j <= max_l; j++) {
                shls[0] = i; shls[1] = j;
                CINTinit_int1e_EnvVars(&envs, ng, shls,
                                       atm, natm, fakebas, fakenbas, env);
                ptr = i*ANG_MAX + j;
                opt->index_xyz_array[ptr] =
                        (int *)malloc(sizeof(int)*envs.nf*3);
                CINTg2c_index_xyz(opt->index_xyz_array[ptr], &envs);
        } }
}

void CINTOpt_3c1eindex_xyz(CINTOpt *opt, int *ng, int *atm, int natm,
                         int *bas, int nbas, double *env)
{
        int i, j, k, ptr;
        int n = ANG_MAX*ANG_MAX*ANG_MAX;
        opt->index_xyz_array = (int **)malloc(sizeof(int *) * n);
        for (i = 0; i < n; i++) {
                opt->index_xyz_array[i] = NULL;
        }

        int fakebas[BAS_SLOTS*ANG_MAX];
        int max_l = _make_fakebas(fakebas, bas, nbas, env);
        int fakenbas = max_l+1;
        CINTEnvVars envs;
        int shls[3];
        for (i = 0; i <= max_l; i++) {
        for (j = 0; j <= max_l; j++) {
        for (k = 0; k <= max_l; k++) {
                shls[0] = i; shls[1] = j; shls[2] = k;
                CINTinit_int3c1e_EnvVars(&envs, ng, shls,
                                         atm, natm, fakebas, fakenbas, env);
                ptr = i*ANG_MAX*ANG_MAX + j*ANG_MAX + k;
                opt->index_xyz_array[ptr] =
                        (int *)malloc(sizeof(int)*envs.nf*3);
                CINTg3c_index_xyz(opt->index_xyz_array[ptr], &envs);
        } } }
}


// for the coeffs of the pGTO, find the maximum abs(coeff)
static double max_pgto_coeff(const double *coeff, int nprim, int nctr,
                             int prim_id)
{
        int i;
        double maxc = 0;
        for (i = 0; i < nctr; i++) {
                maxc = MAX(maxc, fabs(coeff[i*nprim+prim_id]));
        }
        return maxc;
}

void CINTOpt_setij(CINTOpt *opt, int *ng,
                   int *atm, int natm, int *bas, int nbas, double *env)
{
        int i, j, ip, jp;
        int iprim, ictr, jprim, jctr, li, lj;
        const double *ai, *aj, *ri, *rj, *ci, *cj;

        if (opt->data_ptr == NULL) {
                size_t tot_prim = 0;
                for (i = 0; i < nbas; i++) {
                        tot_prim += bas(NPRIM_OF, i);
                }
                opt->data_ptr = malloc(sizeof(int) * nbas*nbas);
                opt->data = malloc(sizeof(PairData) * tot_prim*tot_prim);
        }

        int ijkl_inc;
        if ((ng[IINC]+ng[JINC]) > (ng[KINC]+ng[LINC])) {
                ijkl_inc = ng[IINC] + ng[JINC];
        } else {
                ijkl_inc = ng[KINC] + ng[LINC];
        }

        size_t stack_size = 0;
        double eij, aij, rr, maxci, maxcj, rirj_g4d, min_cceij;
        PairData *pdata;
        for (i = 0; i < nbas; i++) {
                ri = env + atm(PTR_COORD,bas(ATOM_OF,i));
                ai = env + bas(PTR_EXP,i);
                iprim = bas(NPRIM_OF,i);
                ictr = bas(NCTR_OF,i);
                ci = env + bas(PTR_COEFF,i);
                li = bas(ANG_OF,i);
// For derivative/dipole operator, the l-value in g2e is virtually increased

                for (j = 0; j < nbas; j++) {
                        rj = env + atm(PTR_COORD,bas(ATOM_OF,j));
                        aj = env + bas(PTR_EXP,j);
                        jprim = bas(NPRIM_OF,j);
                        jctr = bas(NCTR_OF,j);
                        cj = env + bas(PTR_COEFF,j);
                        lj = bas(ANG_OF,j);
                        rr = (ri[0]-rj[0])*(ri[0]-rj[0])
                           + (ri[1]-rj[1])*(ri[1]-rj[1])
                           + (ri[2]-rj[2])*(ri[2]-rj[2]);

                        pdata = opt->data + stack_size;
                        min_cceij = 1e9;
                        for (jp = 0; jp < jprim; jp++) {
                                maxcj = max_pgto_coeff(cj, jprim, jctr, jp);
                                maxcj = maxcj / CINTgto_norm(lj,aj[jp]);

                                for (ip = 0; ip < iprim; ip++, pdata++) {
                                        maxci = max_pgto_coeff(ci, iprim, ictr, ip);
                                        maxci = maxci / CINTgto_norm(li,ai[ip]);

                                        aij = ai[ip] + aj[jp];
                                        eij = rr * ai[ip] * aj[jp] / aij;
                                        pdata->rij[0] = (ai[ip]*ri[0] + aj[jp]*rj[0]) / aij;
                                        pdata->rij[1] = (ai[ip]*ri[1] + aj[jp]*rj[1]) / aij;
                                        pdata->rij[2] = (ai[ip]*ri[2] + aj[jp]*rj[2]) / aij;
                                        pdata->eij = exp(-eij);

        if (maxci*maxcj == 0) {
                pdata->cceij = 750;
        } else if (rr > 1e-12) {
/* value estimation based on g0_2e_2d and g0_xx2d_4d,
 * value/exp(-eij) ~< (il+jl+2)!*(aij/2)^(il+jl)*(ri_or_rj-rij)^(ij+jl)*rirj^max(il,jl)
 *                 ~< (il+jl+2)!*(aij/2)^(il+jl)*|rirj|^((il+jl)+max(il,jl))
 * But in practice, |rirj|^((il+jl)/2) is large enough to cover all other factors
 * +0.5 to avoid very close gaussian pairs */
                rirj_g4d = pow(rr+0.5, (li+lj+ijkl_inc+1)/2);
                pdata->cceij = eij - log(maxci*maxcj*rirj_g4d);
        } else {
/* If basis on the same center, include the (ss|ss)^{1/2} contribution
 * (ss|ss) = 2\sqrt{aij/pi} */
                pdata->cceij = -log(maxci*maxcj) - log(aij)/4;
        }
        min_cceij = MIN(min_cceij, pdata->cceij);

                                }
                        }
                        if (min_cceij > CUTOFF15) { // very small pair-density
                                opt->data_ptr[i*nbas+j] = NOVALUE;
                        } else {
                                opt->data_ptr[i*nbas+j] = stack_size;
                                stack_size += iprim * jprim;
                        }
                }
        }
        opt->data = realloc(opt->data, sizeof(PairData) * stack_size);
}

void CINTOpt_non0coeff_byshell(int *sortedidx, int *non0ctr, double *ci,
                               int iprim, int ictr)
{
        int ip, j, k, kp;
        int zeroidx[ictr];
        for (ip = 0; ip < iprim; ip++) {
                for (j = 0, k = 0, kp = 0; j < ictr; j++) {
                        if (ci[iprim*j+ip] != 0) {
                                sortedidx[k] = j;
                                k++;
                        } else {
                                zeroidx[kp] = j;
                                kp++;
                        }
                }
// Append the index of zero-coeff to sortedidx for function CINTprim_to_ctr_0
                for (j = 0; j < kp; j++) {
                        sortedidx[k+j] = zeroidx[j];
                }
                non0ctr[ip] = k;
                sortedidx += ictr;
        }
}

void CINTOpt_set_non0coeff(CINTOpt *opt, int *atm, int natm,
                           int *bas, int nbas, double *env)
{
        int i, iprim, ictr;
        double *ci;
        opt->non0ctr = malloc(sizeof(int *) * nbas);
        opt->sortedidx = malloc(sizeof(int *) * nbas);
        for (i = 0; i < nbas; i++) {
                iprim = bas(NPRIM_OF,i);
                ictr = bas(NCTR_OF,i);
                ci = env + bas(PTR_COEFF,i);
                opt->sortedidx[i] = malloc(sizeof(int) * iprim*ictr);
                opt->non0ctr[i] = malloc(sizeof(int) * iprim);
                CINTOpt_non0coeff_byshell(opt->sortedidx[i], opt->non0ctr[i],
                                          ci, iprim, ictr);
        }
}

