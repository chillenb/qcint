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
 * Description: code generated by  gen-code.cl
 */
#include <stdlib.h>
#include "cint_bas.h"
#include "simd.h"
#include "cart2sph.h"
#include "g1e.h"
#include "g2e.h"
#include "optimizer.h"
#include "cint1e.h"
#include "cint2e.h"
#include "misc.h"
#include "c2f.h"
/* <NABLA i|OVLP |j> */
static void CINTgout1e_int1e_ipovlp(double *gout, double *g, int *idx, CINTEnvVars *envs, int count) {
CINTg1e_ovlp(g, envs, count);
int nf = envs->nf;
int nfc = nf * 3;
int ix, iy, iz, n;
DECLARE_GOUT;
double *RESTRICT g0 = g;
double *RESTRICT g1 = g0  + envs->g_size * 3 * SIMDD;
__MD r1;
__MD rs[3];
G1E_D_I(g1, g0, envs->i_l+0, envs->j_l, 0);
for (n = 0; n < nf; n++) {
ix = idx[0+n*3];
iy = idx[1+n*3];
iz = idx[2+n*3];
rs[0] = MM_LOAD(g1+ix*SIMDD) * MM_LOAD(g0+iy*SIMDD) * MM_LOAD(g0+iz*SIMDD);
rs[1] = MM_LOAD(g0+ix*SIMDD) * MM_LOAD(g1+iy*SIMDD) * MM_LOAD(g0+iz*SIMDD);
rs[2] = MM_LOAD(g0+ix*SIMDD) * MM_LOAD(g0+iy*SIMDD) * MM_LOAD(g1+iz*SIMDD);
r1 = + rs[0]; GOUT_SCATTER(gout, n*3+0, r1);
r1 = + rs[1]; GOUT_SCATTER(gout, n*3+1, r1);
r1 = + rs[2]; GOUT_SCATTER(gout, n*3+2, r1);
}}
void int1e_ipovlp_optimizer(CINTOpt **opt, int *atm, int natm, int *bas, int nbas, double *env) {
int ng[] = {1, 0, 0, 0, 1, 1, 1, 3};
CINTall_1e_optimizer(opt, ng, atm, natm, bas, nbas, env);
}
int int1e_ipovlp_cart(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 0, 0, 0, 1, 1, 1, 3};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_ipovlp;
return CINT1e_drv(out, dims, &envs, opt, cache, &c2s_cart_1e);
} // int1e_ipovlp_cart
int int1e_ipovlp_sph(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 0, 0, 0, 1, 1, 1, 3};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_ipovlp;
return CINT1e_drv(out, dims, &envs, opt, cache, &c2s_sph_1e);
} // int1e_ipovlp_sph
int int1e_ipovlp_spinor(double complex *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 0, 0, 0, 1, 1, 1, 3};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_ipovlp;
return CINT1e_spinor_drv(out, dims, &envs, opt, cache, &c2s_sf_1e);
} // int1e_ipovlp_spinor
ALL_CINT1E(int1e_ipovlp)
//ALL_CINT1E_FORTRAN_(cint1e_ipovlp)
/* <NABLA i|OVLP |P DOT P j> */
static void CINTgout1e_int1e_ipkin(double *gout, double *g, int *idx, CINTEnvVars *envs, int count) {
CINTg1e_ovlp(g, envs, count);
int nf = envs->nf;
int nfc = nf * 3;
int ix, iy, iz, n;
DECLARE_GOUT;
double *RESTRICT g0 = g;
double *RESTRICT g1 = g0  + envs->g_size * 3 * SIMDD;
double *RESTRICT g2 = g1  + envs->g_size * 3 * SIMDD;
double *RESTRICT g3 = g2  + envs->g_size * 3 * SIMDD;
double *RESTRICT g4 = g3  + envs->g_size * 3 * SIMDD;
double *RESTRICT g5 = g4  + envs->g_size * 3 * SIMDD;
double *RESTRICT g6 = g5  + envs->g_size * 3 * SIMDD;
double *RESTRICT g7 = g6  + envs->g_size * 3 * SIMDD;
__MD r1;
__MD rs[27];
G1E_D_J(g1, g0, envs->i_l+1, envs->j_l+0, 0);
G1E_D_J(g2, g0, envs->i_l+1, envs->j_l+1, 0);
G1E_D_J(g3, g2, envs->i_l+1, envs->j_l+0, 0);
G1E_D_I(g4, g0, envs->i_l+0, envs->j_l, 0);
G1E_D_I(g5, g1, envs->i_l+0, envs->j_l, 0);
G1E_D_I(g6, g2, envs->i_l+0, envs->j_l, 0);
G1E_D_I(g7, g3, envs->i_l+0, envs->j_l, 0);
for (n = 0; n < nf; n++) {
ix = idx[0+n*3];
iy = idx[1+n*3];
iz = idx[2+n*3];
rs[0] = MM_LOAD(g7+ix*SIMDD) * MM_LOAD(g0+iy*SIMDD) * MM_LOAD(g0+iz*SIMDD);
rs[1] = MM_LOAD(g6+ix*SIMDD) * MM_LOAD(g1+iy*SIMDD) * MM_LOAD(g0+iz*SIMDD);
rs[2] = MM_LOAD(g6+ix*SIMDD) * MM_LOAD(g0+iy*SIMDD) * MM_LOAD(g1+iz*SIMDD);
rs[3] = MM_LOAD(g5+ix*SIMDD) * MM_LOAD(g2+iy*SIMDD) * MM_LOAD(g0+iz*SIMDD);
rs[4] = MM_LOAD(g4+ix*SIMDD) * MM_LOAD(g3+iy*SIMDD) * MM_LOAD(g0+iz*SIMDD);
rs[5] = MM_LOAD(g4+ix*SIMDD) * MM_LOAD(g2+iy*SIMDD) * MM_LOAD(g1+iz*SIMDD);
rs[6] = MM_LOAD(g5+ix*SIMDD) * MM_LOAD(g0+iy*SIMDD) * MM_LOAD(g2+iz*SIMDD);
rs[7] = MM_LOAD(g4+ix*SIMDD) * MM_LOAD(g1+iy*SIMDD) * MM_LOAD(g2+iz*SIMDD);
rs[8] = MM_LOAD(g4+ix*SIMDD) * MM_LOAD(g0+iy*SIMDD) * MM_LOAD(g3+iz*SIMDD);
rs[9] = MM_LOAD(g3+ix*SIMDD) * MM_LOAD(g4+iy*SIMDD) * MM_LOAD(g0+iz*SIMDD);
rs[10] = MM_LOAD(g2+ix*SIMDD) * MM_LOAD(g5+iy*SIMDD) * MM_LOAD(g0+iz*SIMDD);
rs[11] = MM_LOAD(g2+ix*SIMDD) * MM_LOAD(g4+iy*SIMDD) * MM_LOAD(g1+iz*SIMDD);
rs[12] = MM_LOAD(g1+ix*SIMDD) * MM_LOAD(g6+iy*SIMDD) * MM_LOAD(g0+iz*SIMDD);
rs[13] = MM_LOAD(g0+ix*SIMDD) * MM_LOAD(g7+iy*SIMDD) * MM_LOAD(g0+iz*SIMDD);
rs[14] = MM_LOAD(g0+ix*SIMDD) * MM_LOAD(g6+iy*SIMDD) * MM_LOAD(g1+iz*SIMDD);
rs[15] = MM_LOAD(g1+ix*SIMDD) * MM_LOAD(g4+iy*SIMDD) * MM_LOAD(g2+iz*SIMDD);
rs[16] = MM_LOAD(g0+ix*SIMDD) * MM_LOAD(g5+iy*SIMDD) * MM_LOAD(g2+iz*SIMDD);
rs[17] = MM_LOAD(g0+ix*SIMDD) * MM_LOAD(g4+iy*SIMDD) * MM_LOAD(g3+iz*SIMDD);
rs[18] = MM_LOAD(g3+ix*SIMDD) * MM_LOAD(g0+iy*SIMDD) * MM_LOAD(g4+iz*SIMDD);
rs[19] = MM_LOAD(g2+ix*SIMDD) * MM_LOAD(g1+iy*SIMDD) * MM_LOAD(g4+iz*SIMDD);
rs[20] = MM_LOAD(g2+ix*SIMDD) * MM_LOAD(g0+iy*SIMDD) * MM_LOAD(g5+iz*SIMDD);
rs[21] = MM_LOAD(g1+ix*SIMDD) * MM_LOAD(g2+iy*SIMDD) * MM_LOAD(g4+iz*SIMDD);
rs[22] = MM_LOAD(g0+ix*SIMDD) * MM_LOAD(g3+iy*SIMDD) * MM_LOAD(g4+iz*SIMDD);
rs[23] = MM_LOAD(g0+ix*SIMDD) * MM_LOAD(g2+iy*SIMDD) * MM_LOAD(g5+iz*SIMDD);
rs[24] = MM_LOAD(g1+ix*SIMDD) * MM_LOAD(g0+iy*SIMDD) * MM_LOAD(g6+iz*SIMDD);
rs[25] = MM_LOAD(g0+ix*SIMDD) * MM_LOAD(g1+iy*SIMDD) * MM_LOAD(g6+iz*SIMDD);
rs[26] = MM_LOAD(g0+ix*SIMDD) * MM_LOAD(g0+iy*SIMDD) * MM_LOAD(g7+iz*SIMDD);
r1 = - rs[0] - rs[4] - rs[8]; GOUT_SCATTER(gout, n*3+0, r1);
r1 = - rs[9] - rs[13] - rs[17]; GOUT_SCATTER(gout, n*3+1, r1);
r1 = - rs[18] - rs[22] - rs[26]; GOUT_SCATTER(gout, n*3+2, r1);
}}
void int1e_ipkin_optimizer(CINTOpt **opt, int *atm, int natm, int *bas, int nbas, double *env) {
int ng[] = {1, 2, 0, 0, 3, 1, 1, 3};
CINTall_1e_optimizer(opt, ng, atm, natm, bas, nbas, env);
}
int int1e_ipkin_cart(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 2, 0, 0, 3, 1, 1, 3};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_ipkin;
envs.common_factor *= 0.5;
return CINT1e_drv(out, dims, &envs, opt, cache, &c2s_cart_1e);
} // int1e_ipkin_cart
int int1e_ipkin_sph(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 2, 0, 0, 3, 1, 1, 3};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_ipkin;
envs.common_factor *= 0.5;
return CINT1e_drv(out, dims, &envs, opt, cache, &c2s_sph_1e);
} // int1e_ipkin_sph
int int1e_ipkin_spinor(double complex *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 2, 0, 0, 3, 1, 1, 3};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_ipkin;
envs.common_factor *= 0.5;
return CINT1e_spinor_drv(out, dims, &envs, opt, cache, &c2s_sf_1e);
} // int1e_ipkin_spinor
ALL_CINT1E(int1e_ipkin)
//ALL_CINT1E_FORTRAN_(cint1e_ipkin)
/* <NABLA i|NUC |j> */
static void CINTgout1e_int1e_ipnuc(double *gout, double *g, int *idx, CINTEnvVars *envs, int count) {
int nf = envs->nf;
int nrys_roots = envs->nrys_roots;
int nfc = nf * 3;
double *gout1 = gout + nfc*SIMDD;
int ix, iy, iz, ia, n, i;
double *RESTRICT g0 = g;
double *RESTRICT g1 = g0  + envs->g_size * 3 * SIMDD;
__MD r1;
__MD rs[3];
for (n = 0; n < nfc*SIMDD; n++) { gout1[n] = 0; }
for (ia = 0; ia < envs->natm; ia++) {
CINTg1e_nuc(g, envs, count, ia);
G2E_D_I(g1, g0, envs->i_l+0, envs->j_l, 0, 0);
for (n = 0; n < nf; n++) {
ix = idx[0+n*3];
iy = idx[1+n*3];
iz = idx[2+n*3];
for (i = 0; i < 3; i++) { rs[i] = MM_SET1(0.); }
for (i = 0; i < nrys_roots; i++) {
rs[0] += MM_LOAD(g1+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[1] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g1+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[2] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g1+(iz+i)*SIMDD);
}
r1 = MM_LOAD(gout1+(n*3+0)*SIMDD) + + rs[0]; MM_STORE(gout1+(n*3+0)*SIMDD, r1);
r1 = MM_LOAD(gout1+(n*3+1)*SIMDD) + + rs[1]; MM_STORE(gout1+(n*3+1)*SIMDD, r1);
r1 = MM_LOAD(gout1+(n*3+2)*SIMDD) + + rs[2]; MM_STORE(gout1+(n*3+2)*SIMDD, r1);
}
}
CINTsort_gout(gout, gout1, nfc, SIMDD);
}
void int1e_ipnuc_optimizer(CINTOpt **opt, int *atm, int natm, int *bas, int nbas, double *env) {
int ng[] = {1, 0, 0, 0, 1, 1, 0, 3};
CINTall_1e_optimizer(opt, ng, atm, natm, bas, nbas, env);
}
int int1e_ipnuc_cart(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 0, 0, 0, 1, 1, 0, 3};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_ipnuc;
return CINT1e_drv(out, dims, &envs, opt, cache, &c2s_cart_1e);
} // int1e_ipnuc_cart
int int1e_ipnuc_sph(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 0, 0, 0, 1, 1, 0, 3};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_ipnuc;
return CINT1e_drv(out, dims, &envs, opt, cache, &c2s_sph_1e);
} // int1e_ipnuc_sph
int int1e_ipnuc_spinor(double complex *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 0, 0, 0, 1, 1, 0, 3};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_ipnuc;
return CINT1e_spinor_drv(out, dims, &envs, opt, cache, &c2s_sf_1e);
} // int1e_ipnuc_spinor
ALL_CINT1E(int1e_ipnuc)
//ALL_CINT1E_FORTRAN_(cint1e_ipnuc)
/* <NABLA i|RINV |j> */
static void CINTgout1e_int1e_iprinv(double *gout, double *g, int *idx, CINTEnvVars *envs, int count) {
CINTg1e_nuc(g, envs, count, -1);
int nf = envs->nf;
int nfc = nf * 3;
int nrys_roots = envs->nrys_roots;
int ix, iy, iz, n, i;
DECLARE_GOUT;
double *RESTRICT g0 = g;
double *RESTRICT g1 = g0 + envs->g_size * 3 * SIMDD;
__MD r1;
__MD rs[3];
G2E_D_I(g1, g0, envs->i_l+0, envs->j_l, 0, 0);
for (n = 0; n < nf; n++) {
ix = idx[0+n*3];
iy = idx[1+n*3];
iz = idx[2+n*3];
for (i = 0; i < 3; i++) { rs[i] = MM_SET1(0.); }
for (i = 0; i < nrys_roots; i++) {
rs[0] += MM_LOAD(g1+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[1] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g1+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[2] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g1+(iz+i)*SIMDD);
}
r1 = + rs[0]; GOUT_SCATTER(gout, n*3+0, r1);
r1 = + rs[1]; GOUT_SCATTER(gout, n*3+1, r1);
r1 = + rs[2]; GOUT_SCATTER(gout, n*3+2, r1);
}}
void int1e_iprinv_optimizer(CINTOpt **opt, int *atm, int natm, int *bas, int nbas, double *env) {
int ng[] = {1, 0, 0, 0, 1, 1, 0, 3};
CINTall_1e_optimizer(opt, ng, atm, natm, bas, nbas, env);
}
int int1e_iprinv_cart(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 0, 0, 0, 1, 1, 0, 3};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_iprinv;
return CINT1e_drv(out, dims, &envs, opt, cache, &c2s_cart_1e);
} // int1e_iprinv_cart
int int1e_iprinv_sph(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 0, 0, 0, 1, 1, 0, 3};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_iprinv;
return CINT1e_drv(out, dims, &envs, opt, cache, &c2s_sph_1e);
} // int1e_iprinv_sph
int int1e_iprinv_spinor(double complex *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 0, 0, 0, 1, 1, 0, 3};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_iprinv;
return CINT1e_spinor_drv(out, dims, &envs, opt, cache, &c2s_sf_1e);
} // int1e_iprinv_spinor
ALL_CINT1E(int1e_iprinv)
//ALL_CINT1E_FORTRAN_(cint1e_iprinv)
/* <i|RINV |j> */
static void CINTgout1e_int1e_rinv(double *gout, double *g, int *idx, CINTEnvVars *envs, int count) {
CINTg1e_nuc(g, envs, count, -1);
int nf = envs->nf;
int nfc = nf * 1;
int nrys_roots = envs->nrys_roots;
int ix, iy, iz, n, i;
DECLARE_GOUT;
double *RESTRICT g0 = g;
__MD r1;
__MD rs[1];
for (n = 0; n < nf; n++) {
ix = idx[0+n*3];
iy = idx[1+n*3];
iz = idx[2+n*3];
for (i = 0; i < 1; i++) { rs[i] = MM_SET1(0.); }
for (i = 0; i < nrys_roots; i++) {
rs[0] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
}
r1 = + rs[0]; GOUT_SCATTER(gout, n*1+0, r1);
}}
void int1e_rinv_optimizer(CINTOpt **opt, int *atm, int natm, int *bas, int nbas, double *env) {
int ng[] = {0, 0, 0, 0, 0, 1, 0, 1};
CINTall_1e_optimizer(opt, ng, atm, natm, bas, nbas, env);
}
int int1e_rinv_cart(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {0, 0, 0, 0, 0, 1, 0, 1};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_rinv;
return CINT1e_drv(out, dims, &envs, opt, cache, &c2s_cart_1e);
} // int1e_rinv_cart
int int1e_rinv_sph(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {0, 0, 0, 0, 0, 1, 0, 1};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_rinv;
return CINT1e_drv(out, dims, &envs, opt, cache, &c2s_sph_1e);
} // int1e_rinv_sph
int int1e_rinv_spinor(double complex *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {0, 0, 0, 0, 0, 1, 0, 1};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_rinv;
return CINT1e_spinor_drv(out, dims, &envs, opt, cache, &c2s_sf_1e);
} // int1e_rinv_spinor
ALL_CINT1E(int1e_rinv)
//ALL_CINT1E_FORTRAN_(cint1e_rinv)
/* <NABLA SIGMA DOT P i|NUC |SIGMA DOT P j> */
static void CINTgout1e_int1e_ipspnucsp(double *gout, double *g, int *idx, CINTEnvVars *envs, int count) {
int nf = envs->nf;
int nrys_roots = envs->nrys_roots;
int nfc = nf * 12;
double *gout1 = gout + nfc*SIMDD;
int ix, iy, iz, ia, n, i;
double *RESTRICT g0 = g;
double *RESTRICT g1 = g0  + envs->g_size * 3 * SIMDD;
double *RESTRICT g2 = g1  + envs->g_size * 3 * SIMDD;
double *RESTRICT g3 = g2  + envs->g_size * 3 * SIMDD;
double *RESTRICT g4 = g3  + envs->g_size * 3 * SIMDD;
double *RESTRICT g5 = g4  + envs->g_size * 3 * SIMDD;
double *RESTRICT g6 = g5  + envs->g_size * 3 * SIMDD;
double *RESTRICT g7 = g6  + envs->g_size * 3 * SIMDD;
__MD r1;
__MD rs[27];
for (n = 0; n < nfc*SIMDD; n++) { gout1[n] = 0; }
for (ia = 0; ia < envs->natm; ia++) {
CINTg1e_nuc(g, envs, count, ia);
G2E_D_J(g1, g0, envs->i_l+2, envs->j_l+0, 0, 0);
G2E_D_I(g2, g0, envs->i_l+1, envs->j_l, 0, 0);
G2E_D_I(g3, g1, envs->i_l+1, envs->j_l, 0, 0);
G2E_D_I(g4, g0, envs->i_l+0, envs->j_l, 0, 0);
G2E_D_I(g5, g1, envs->i_l+0, envs->j_l, 0, 0);
G2E_D_I(g6, g2, envs->i_l+0, envs->j_l, 0, 0);
G2E_D_I(g7, g3, envs->i_l+0, envs->j_l, 0, 0);
for (n = 0; n < nf; n++) {
ix = idx[0+n*3];
iy = idx[1+n*3];
iz = idx[2+n*3];
for (i = 0; i < 27; i++) { rs[i] = MM_SET1(0.); }
for (i = 0; i < nrys_roots; i++) {
rs[0] += MM_LOAD(g7+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[1] += MM_LOAD(g6+(ix+i)*SIMDD) * MM_LOAD(g1+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[2] += MM_LOAD(g6+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g1+(iz+i)*SIMDD);
rs[3] += MM_LOAD(g5+(ix+i)*SIMDD) * MM_LOAD(g2+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[4] += MM_LOAD(g4+(ix+i)*SIMDD) * MM_LOAD(g3+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[5] += MM_LOAD(g4+(ix+i)*SIMDD) * MM_LOAD(g2+(iy+i)*SIMDD) * MM_LOAD(g1+(iz+i)*SIMDD);
rs[6] += MM_LOAD(g5+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g2+(iz+i)*SIMDD);
rs[7] += MM_LOAD(g4+(ix+i)*SIMDD) * MM_LOAD(g1+(iy+i)*SIMDD) * MM_LOAD(g2+(iz+i)*SIMDD);
rs[8] += MM_LOAD(g4+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g3+(iz+i)*SIMDD);
rs[9] += MM_LOAD(g3+(ix+i)*SIMDD) * MM_LOAD(g4+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[10] += MM_LOAD(g2+(ix+i)*SIMDD) * MM_LOAD(g5+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[11] += MM_LOAD(g2+(ix+i)*SIMDD) * MM_LOAD(g4+(iy+i)*SIMDD) * MM_LOAD(g1+(iz+i)*SIMDD);
rs[12] += MM_LOAD(g1+(ix+i)*SIMDD) * MM_LOAD(g6+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[13] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g7+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[14] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g6+(iy+i)*SIMDD) * MM_LOAD(g1+(iz+i)*SIMDD);
rs[15] += MM_LOAD(g1+(ix+i)*SIMDD) * MM_LOAD(g4+(iy+i)*SIMDD) * MM_LOAD(g2+(iz+i)*SIMDD);
rs[16] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g5+(iy+i)*SIMDD) * MM_LOAD(g2+(iz+i)*SIMDD);
rs[17] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g4+(iy+i)*SIMDD) * MM_LOAD(g3+(iz+i)*SIMDD);
rs[18] += MM_LOAD(g3+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g4+(iz+i)*SIMDD);
rs[19] += MM_LOAD(g2+(ix+i)*SIMDD) * MM_LOAD(g1+(iy+i)*SIMDD) * MM_LOAD(g4+(iz+i)*SIMDD);
rs[20] += MM_LOAD(g2+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g5+(iz+i)*SIMDD);
rs[21] += MM_LOAD(g1+(ix+i)*SIMDD) * MM_LOAD(g2+(iy+i)*SIMDD) * MM_LOAD(g4+(iz+i)*SIMDD);
rs[22] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g3+(iy+i)*SIMDD) * MM_LOAD(g4+(iz+i)*SIMDD);
rs[23] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g2+(iy+i)*SIMDD) * MM_LOAD(g5+(iz+i)*SIMDD);
rs[24] += MM_LOAD(g1+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g6+(iz+i)*SIMDD);
rs[25] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g1+(iy+i)*SIMDD) * MM_LOAD(g6+(iz+i)*SIMDD);
rs[26] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g7+(iz+i)*SIMDD);
}
r1 = MM_LOAD(gout1+(n*12+0)*SIMDD) + + rs[11] - rs[19]; MM_STORE(gout1+(n*12+0)*SIMDD, r1);
r1 = MM_LOAD(gout1+(n*12+1)*SIMDD) + + rs[18] - rs[2]; MM_STORE(gout1+(n*12+1)*SIMDD, r1);
r1 = MM_LOAD(gout1+(n*12+2)*SIMDD) + + rs[1] - rs[9]; MM_STORE(gout1+(n*12+2)*SIMDD, r1);
r1 = MM_LOAD(gout1+(n*12+3)*SIMDD) + + rs[0] + rs[10] + rs[20]; MM_STORE(gout1+(n*12+3)*SIMDD, r1);
r1 = MM_LOAD(gout1+(n*12+4)*SIMDD) + + rs[14] - rs[22]; MM_STORE(gout1+(n*12+4)*SIMDD, r1);
r1 = MM_LOAD(gout1+(n*12+5)*SIMDD) + + rs[21] - rs[5]; MM_STORE(gout1+(n*12+5)*SIMDD, r1);
r1 = MM_LOAD(gout1+(n*12+6)*SIMDD) + + rs[4] - rs[12]; MM_STORE(gout1+(n*12+6)*SIMDD, r1);
r1 = MM_LOAD(gout1+(n*12+7)*SIMDD) + + rs[3] + rs[13] + rs[23]; MM_STORE(gout1+(n*12+7)*SIMDD, r1);
r1 = MM_LOAD(gout1+(n*12+8)*SIMDD) + + rs[17] - rs[25]; MM_STORE(gout1+(n*12+8)*SIMDD, r1);
r1 = MM_LOAD(gout1+(n*12+9)*SIMDD) + + rs[24] - rs[8]; MM_STORE(gout1+(n*12+9)*SIMDD, r1);
r1 = MM_LOAD(gout1+(n*12+10)*SIMDD) + + rs[7] - rs[15]; MM_STORE(gout1+(n*12+10)*SIMDD, r1);
r1 = MM_LOAD(gout1+(n*12+11)*SIMDD) + + rs[6] + rs[16] + rs[26]; MM_STORE(gout1+(n*12+11)*SIMDD, r1);
}
}
CINTsort_gout(gout, gout1, nfc, SIMDD);
}
void int1e_ipspnucsp_optimizer(CINTOpt **opt, int *atm, int natm, int *bas, int nbas, double *env) {
int ng[] = {2, 1, 0, 0, 3, 4, 0, 3};
CINTall_1e_optimizer(opt, ng, atm, natm, bas, nbas, env);
}
int int1e_ipspnucsp_cart(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {2, 1, 0, 0, 3, 4, 0, 3};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_ipspnucsp;
return CINT1e_drv(out, dims, &envs, opt, cache, &c2s_cart_1e);
} // int1e_ipspnucsp_cart
int int1e_ipspnucsp_sph(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {2, 1, 0, 0, 3, 4, 0, 3};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_ipspnucsp;
return CINT1e_drv(out, dims, &envs, opt, cache, &c2s_sph_1e);
} // int1e_ipspnucsp_sph
int int1e_ipspnucsp_spinor(double complex *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {2, 1, 0, 0, 3, 4, 0, 3};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_ipspnucsp;
return CINT1e_spinor_drv(out, dims, &envs, opt, cache, &c2s_si_1e);
} // int1e_ipspnucsp_spinor
ALL_CINT1E(int1e_ipspnucsp)
//ALL_CINT1E_FORTRAN_(cint1e_ipspnucsp)
/* <NABLA SIGMA DOT P i|RINV |SIGMA DOT P j> */
static void CINTgout1e_int1e_ipsprinvsp(double *gout, double *g, int *idx, CINTEnvVars *envs, int count) {
CINTg1e_nuc(g, envs, count, -1);
int nf = envs->nf;
int nfc = nf * 12;
int nrys_roots = envs->nrys_roots;
int ix, iy, iz, n, i;
DECLARE_GOUT;
double *RESTRICT g0 = g;
double *RESTRICT g1 = g0 + envs->g_size * 3 * SIMDD;
double *RESTRICT g2 = g1 + envs->g_size * 3 * SIMDD;
double *RESTRICT g3 = g2 + envs->g_size * 3 * SIMDD;
double *RESTRICT g4 = g3 + envs->g_size * 3 * SIMDD;
double *RESTRICT g5 = g4 + envs->g_size * 3 * SIMDD;
double *RESTRICT g6 = g5 + envs->g_size * 3 * SIMDD;
double *RESTRICT g7 = g6 + envs->g_size * 3 * SIMDD;
__MD r1;
__MD rs[27];
G2E_D_J(g1, g0, envs->i_l+2, envs->j_l+0, 0, 0);
G2E_D_I(g2, g0, envs->i_l+1, envs->j_l, 0, 0);
G2E_D_I(g3, g1, envs->i_l+1, envs->j_l, 0, 0);
G2E_D_I(g4, g0, envs->i_l+0, envs->j_l, 0, 0);
G2E_D_I(g5, g1, envs->i_l+0, envs->j_l, 0, 0);
G2E_D_I(g6, g2, envs->i_l+0, envs->j_l, 0, 0);
G2E_D_I(g7, g3, envs->i_l+0, envs->j_l, 0, 0);
for (n = 0; n < nf; n++) {
ix = idx[0+n*3];
iy = idx[1+n*3];
iz = idx[2+n*3];
for (i = 0; i < 27; i++) { rs[i] = MM_SET1(0.); }
for (i = 0; i < nrys_roots; i++) {
rs[0] += MM_LOAD(g7+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[1] += MM_LOAD(g6+(ix+i)*SIMDD) * MM_LOAD(g1+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[2] += MM_LOAD(g6+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g1+(iz+i)*SIMDD);
rs[3] += MM_LOAD(g5+(ix+i)*SIMDD) * MM_LOAD(g2+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[4] += MM_LOAD(g4+(ix+i)*SIMDD) * MM_LOAD(g3+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[5] += MM_LOAD(g4+(ix+i)*SIMDD) * MM_LOAD(g2+(iy+i)*SIMDD) * MM_LOAD(g1+(iz+i)*SIMDD);
rs[6] += MM_LOAD(g5+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g2+(iz+i)*SIMDD);
rs[7] += MM_LOAD(g4+(ix+i)*SIMDD) * MM_LOAD(g1+(iy+i)*SIMDD) * MM_LOAD(g2+(iz+i)*SIMDD);
rs[8] += MM_LOAD(g4+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g3+(iz+i)*SIMDD);
rs[9] += MM_LOAD(g3+(ix+i)*SIMDD) * MM_LOAD(g4+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[10] += MM_LOAD(g2+(ix+i)*SIMDD) * MM_LOAD(g5+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[11] += MM_LOAD(g2+(ix+i)*SIMDD) * MM_LOAD(g4+(iy+i)*SIMDD) * MM_LOAD(g1+(iz+i)*SIMDD);
rs[12] += MM_LOAD(g1+(ix+i)*SIMDD) * MM_LOAD(g6+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[13] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g7+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[14] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g6+(iy+i)*SIMDD) * MM_LOAD(g1+(iz+i)*SIMDD);
rs[15] += MM_LOAD(g1+(ix+i)*SIMDD) * MM_LOAD(g4+(iy+i)*SIMDD) * MM_LOAD(g2+(iz+i)*SIMDD);
rs[16] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g5+(iy+i)*SIMDD) * MM_LOAD(g2+(iz+i)*SIMDD);
rs[17] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g4+(iy+i)*SIMDD) * MM_LOAD(g3+(iz+i)*SIMDD);
rs[18] += MM_LOAD(g3+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g4+(iz+i)*SIMDD);
rs[19] += MM_LOAD(g2+(ix+i)*SIMDD) * MM_LOAD(g1+(iy+i)*SIMDD) * MM_LOAD(g4+(iz+i)*SIMDD);
rs[20] += MM_LOAD(g2+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g5+(iz+i)*SIMDD);
rs[21] += MM_LOAD(g1+(ix+i)*SIMDD) * MM_LOAD(g2+(iy+i)*SIMDD) * MM_LOAD(g4+(iz+i)*SIMDD);
rs[22] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g3+(iy+i)*SIMDD) * MM_LOAD(g4+(iz+i)*SIMDD);
rs[23] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g2+(iy+i)*SIMDD) * MM_LOAD(g5+(iz+i)*SIMDD);
rs[24] += MM_LOAD(g1+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g6+(iz+i)*SIMDD);
rs[25] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g1+(iy+i)*SIMDD) * MM_LOAD(g6+(iz+i)*SIMDD);
rs[26] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g7+(iz+i)*SIMDD);
}
r1 = + rs[11] - rs[19]; GOUT_SCATTER(gout, n*12+0, r1);
r1 = + rs[18] - rs[2]; GOUT_SCATTER(gout, n*12+1, r1);
r1 = + rs[1] - rs[9]; GOUT_SCATTER(gout, n*12+2, r1);
r1 = + rs[0] + rs[10] + rs[20]; GOUT_SCATTER(gout, n*12+3, r1);
r1 = + rs[14] - rs[22]; GOUT_SCATTER(gout, n*12+4, r1);
r1 = + rs[21] - rs[5]; GOUT_SCATTER(gout, n*12+5, r1);
r1 = + rs[4] - rs[12]; GOUT_SCATTER(gout, n*12+6, r1);
r1 = + rs[3] + rs[13] + rs[23]; GOUT_SCATTER(gout, n*12+7, r1);
r1 = + rs[17] - rs[25]; GOUT_SCATTER(gout, n*12+8, r1);
r1 = + rs[24] - rs[8]; GOUT_SCATTER(gout, n*12+9, r1);
r1 = + rs[7] - rs[15]; GOUT_SCATTER(gout, n*12+10, r1);
r1 = + rs[6] + rs[16] + rs[26]; GOUT_SCATTER(gout, n*12+11, r1);
}}
void int1e_ipsprinvsp_optimizer(CINTOpt **opt, int *atm, int natm, int *bas, int nbas, double *env) {
int ng[] = {2, 1, 0, 0, 3, 4, 0, 3};
CINTall_1e_optimizer(opt, ng, atm, natm, bas, nbas, env);
}
int int1e_ipsprinvsp_cart(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {2, 1, 0, 0, 3, 4, 0, 3};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_ipsprinvsp;
return CINT1e_drv(out, dims, &envs, opt, cache, &c2s_cart_1e);
} // int1e_ipsprinvsp_cart
int int1e_ipsprinvsp_sph(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {2, 1, 0, 0, 3, 4, 0, 3};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_ipsprinvsp;
return CINT1e_drv(out, dims, &envs, opt, cache, &c2s_sph_1e);
} // int1e_ipsprinvsp_sph
int int1e_ipsprinvsp_spinor(double complex *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {2, 1, 0, 0, 3, 4, 0, 3};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_ipsprinvsp;
return CINT1e_spinor_drv(out, dims, &envs, opt, cache, &c2s_si_1e);
} // int1e_ipsprinvsp_spinor
ALL_CINT1E(int1e_ipsprinvsp)
//ALL_CINT1E_FORTRAN_(cint1e_ipsprinvsp)
/* <NABLA i|P* NUC DOT P |j> */
static void CINTgout1e_int1e_ippnucp(double *gout, double *g, int *idx, CINTEnvVars *envs, int count) {
int nf = envs->nf;
int nrys_roots = envs->nrys_roots;
int nfc = nf * 3;
double *gout1 = gout + nfc*SIMDD;
int ix, iy, iz, ia, n, i;
double *RESTRICT g0 = g;
double *RESTRICT g1 = g0  + envs->g_size * 3 * SIMDD;
double *RESTRICT g2 = g1  + envs->g_size * 3 * SIMDD;
double *RESTRICT g3 = g2  + envs->g_size * 3 * SIMDD;
double *RESTRICT g4 = g3  + envs->g_size * 3 * SIMDD;
double *RESTRICT g5 = g4  + envs->g_size * 3 * SIMDD;
double *RESTRICT g6 = g5  + envs->g_size * 3 * SIMDD;
double *RESTRICT g7 = g6  + envs->g_size * 3 * SIMDD;
__MD r1;
__MD rs[27];
for (n = 0; n < nfc*SIMDD; n++) { gout1[n] = 0; }
for (ia = 0; ia < envs->natm; ia++) {
CINTg1e_nuc(g, envs, count, ia);
G2E_D_J(g1, g0, envs->i_l+1, envs->j_l+0, 0, 0);
G2E_D_J(g2, g0, envs->i_l+1, envs->j_l+1, 0, 0);
G2E_D_J(g3, g2, envs->i_l+1, envs->j_l+0, 0, 0);
G2E_D_I(g4, g0, envs->i_l+0, envs->j_l, 0, 0);
G2E_D_I(g5, g1, envs->i_l+0, envs->j_l, 0, 0);
G2E_D_I(g6, g2, envs->i_l+0, envs->j_l, 0, 0);
G2E_D_I(g7, g3, envs->i_l+0, envs->j_l, 0, 0);
for (n = 0; n < nf; n++) {
ix = idx[0+n*3];
iy = idx[1+n*3];
iz = idx[2+n*3];
for (i = 0; i < 27; i++) { rs[i] = MM_SET1(0.); }
for (i = 0; i < nrys_roots; i++) {
rs[0] += MM_LOAD(g7+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[1] += MM_LOAD(g6+(ix+i)*SIMDD) * MM_LOAD(g1+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[2] += MM_LOAD(g6+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g1+(iz+i)*SIMDD);
rs[3] += MM_LOAD(g5+(ix+i)*SIMDD) * MM_LOAD(g2+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[4] += MM_LOAD(g4+(ix+i)*SIMDD) * MM_LOAD(g3+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[5] += MM_LOAD(g4+(ix+i)*SIMDD) * MM_LOAD(g2+(iy+i)*SIMDD) * MM_LOAD(g1+(iz+i)*SIMDD);
rs[6] += MM_LOAD(g5+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g2+(iz+i)*SIMDD);
rs[7] += MM_LOAD(g4+(ix+i)*SIMDD) * MM_LOAD(g1+(iy+i)*SIMDD) * MM_LOAD(g2+(iz+i)*SIMDD);
rs[8] += MM_LOAD(g4+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g3+(iz+i)*SIMDD);
rs[9] += MM_LOAD(g3+(ix+i)*SIMDD) * MM_LOAD(g4+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[10] += MM_LOAD(g2+(ix+i)*SIMDD) * MM_LOAD(g5+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[11] += MM_LOAD(g2+(ix+i)*SIMDD) * MM_LOAD(g4+(iy+i)*SIMDD) * MM_LOAD(g1+(iz+i)*SIMDD);
rs[12] += MM_LOAD(g1+(ix+i)*SIMDD) * MM_LOAD(g6+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[13] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g7+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[14] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g6+(iy+i)*SIMDD) * MM_LOAD(g1+(iz+i)*SIMDD);
rs[15] += MM_LOAD(g1+(ix+i)*SIMDD) * MM_LOAD(g4+(iy+i)*SIMDD) * MM_LOAD(g2+(iz+i)*SIMDD);
rs[16] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g5+(iy+i)*SIMDD) * MM_LOAD(g2+(iz+i)*SIMDD);
rs[17] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g4+(iy+i)*SIMDD) * MM_LOAD(g3+(iz+i)*SIMDD);
rs[18] += MM_LOAD(g3+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g4+(iz+i)*SIMDD);
rs[19] += MM_LOAD(g2+(ix+i)*SIMDD) * MM_LOAD(g1+(iy+i)*SIMDD) * MM_LOAD(g4+(iz+i)*SIMDD);
rs[20] += MM_LOAD(g2+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g5+(iz+i)*SIMDD);
rs[21] += MM_LOAD(g1+(ix+i)*SIMDD) * MM_LOAD(g2+(iy+i)*SIMDD) * MM_LOAD(g4+(iz+i)*SIMDD);
rs[22] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g3+(iy+i)*SIMDD) * MM_LOAD(g4+(iz+i)*SIMDD);
rs[23] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g2+(iy+i)*SIMDD) * MM_LOAD(g5+(iz+i)*SIMDD);
rs[24] += MM_LOAD(g1+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g6+(iz+i)*SIMDD);
rs[25] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g1+(iy+i)*SIMDD) * MM_LOAD(g6+(iz+i)*SIMDD);
rs[26] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g7+(iz+i)*SIMDD);
}
r1 = MM_LOAD(gout1+(n*3+0)*SIMDD) + - rs[0] - rs[4] - rs[8]; MM_STORE(gout1+(n*3+0)*SIMDD, r1);
r1 = MM_LOAD(gout1+(n*3+1)*SIMDD) + - rs[9] - rs[13] - rs[17]; MM_STORE(gout1+(n*3+1)*SIMDD, r1);
r1 = MM_LOAD(gout1+(n*3+2)*SIMDD) + - rs[18] - rs[22] - rs[26]; MM_STORE(gout1+(n*3+2)*SIMDD, r1);
}
}
CINTsort_gout(gout, gout1, nfc, SIMDD);
}
void int1e_ippnucp_optimizer(CINTOpt **opt, int *atm, int natm, int *bas, int nbas, double *env) {
int ng[] = {1, 2, 0, 0, 3, 1, 0, 3};
CINTall_1e_optimizer(opt, ng, atm, natm, bas, nbas, env);
}
int int1e_ippnucp_cart(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 2, 0, 0, 3, 1, 0, 3};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_ippnucp;
return CINT1e_drv(out, dims, &envs, opt, cache, &c2s_cart_1e);
} // int1e_ippnucp_cart
int int1e_ippnucp_sph(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 2, 0, 0, 3, 1, 0, 3};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_ippnucp;
return CINT1e_drv(out, dims, &envs, opt, cache, &c2s_sph_1e);
} // int1e_ippnucp_sph
int int1e_ippnucp_spinor(double complex *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 2, 0, 0, 3, 1, 0, 3};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_ippnucp;
return CINT1e_spinor_drv(out, dims, &envs, opt, cache, &c2s_sf_1e);
} // int1e_ippnucp_spinor
ALL_CINT1E(int1e_ippnucp)
//ALL_CINT1E_FORTRAN_(cint1e_ippnucp)
/* <NABLA i|P* RINV DOT P |j> */
static void CINTgout1e_int1e_ipprinvp(double *gout, double *g, int *idx, CINTEnvVars *envs, int count) {
CINTg1e_nuc(g, envs, count, -1);
int nf = envs->nf;
int nfc = nf * 3;
int nrys_roots = envs->nrys_roots;
int ix, iy, iz, n, i;
DECLARE_GOUT;
double *RESTRICT g0 = g;
double *RESTRICT g1 = g0 + envs->g_size * 3 * SIMDD;
double *RESTRICT g2 = g1 + envs->g_size * 3 * SIMDD;
double *RESTRICT g3 = g2 + envs->g_size * 3 * SIMDD;
double *RESTRICT g4 = g3 + envs->g_size * 3 * SIMDD;
double *RESTRICT g5 = g4 + envs->g_size * 3 * SIMDD;
double *RESTRICT g6 = g5 + envs->g_size * 3 * SIMDD;
double *RESTRICT g7 = g6 + envs->g_size * 3 * SIMDD;
__MD r1;
__MD rs[27];
G2E_D_J(g1, g0, envs->i_l+1, envs->j_l+0, 0, 0);
G2E_D_J(g2, g0, envs->i_l+1, envs->j_l+1, 0, 0);
G2E_D_J(g3, g2, envs->i_l+1, envs->j_l+0, 0, 0);
G2E_D_I(g4, g0, envs->i_l+0, envs->j_l, 0, 0);
G2E_D_I(g5, g1, envs->i_l+0, envs->j_l, 0, 0);
G2E_D_I(g6, g2, envs->i_l+0, envs->j_l, 0, 0);
G2E_D_I(g7, g3, envs->i_l+0, envs->j_l, 0, 0);
for (n = 0; n < nf; n++) {
ix = idx[0+n*3];
iy = idx[1+n*3];
iz = idx[2+n*3];
for (i = 0; i < 27; i++) { rs[i] = MM_SET1(0.); }
for (i = 0; i < nrys_roots; i++) {
rs[0] += MM_LOAD(g7+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[1] += MM_LOAD(g6+(ix+i)*SIMDD) * MM_LOAD(g1+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[2] += MM_LOAD(g6+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g1+(iz+i)*SIMDD);
rs[3] += MM_LOAD(g5+(ix+i)*SIMDD) * MM_LOAD(g2+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[4] += MM_LOAD(g4+(ix+i)*SIMDD) * MM_LOAD(g3+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[5] += MM_LOAD(g4+(ix+i)*SIMDD) * MM_LOAD(g2+(iy+i)*SIMDD) * MM_LOAD(g1+(iz+i)*SIMDD);
rs[6] += MM_LOAD(g5+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g2+(iz+i)*SIMDD);
rs[7] += MM_LOAD(g4+(ix+i)*SIMDD) * MM_LOAD(g1+(iy+i)*SIMDD) * MM_LOAD(g2+(iz+i)*SIMDD);
rs[8] += MM_LOAD(g4+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g3+(iz+i)*SIMDD);
rs[9] += MM_LOAD(g3+(ix+i)*SIMDD) * MM_LOAD(g4+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[10] += MM_LOAD(g2+(ix+i)*SIMDD) * MM_LOAD(g5+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[11] += MM_LOAD(g2+(ix+i)*SIMDD) * MM_LOAD(g4+(iy+i)*SIMDD) * MM_LOAD(g1+(iz+i)*SIMDD);
rs[12] += MM_LOAD(g1+(ix+i)*SIMDD) * MM_LOAD(g6+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[13] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g7+(iy+i)*SIMDD) * MM_LOAD(g0+(iz+i)*SIMDD);
rs[14] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g6+(iy+i)*SIMDD) * MM_LOAD(g1+(iz+i)*SIMDD);
rs[15] += MM_LOAD(g1+(ix+i)*SIMDD) * MM_LOAD(g4+(iy+i)*SIMDD) * MM_LOAD(g2+(iz+i)*SIMDD);
rs[16] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g5+(iy+i)*SIMDD) * MM_LOAD(g2+(iz+i)*SIMDD);
rs[17] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g4+(iy+i)*SIMDD) * MM_LOAD(g3+(iz+i)*SIMDD);
rs[18] += MM_LOAD(g3+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g4+(iz+i)*SIMDD);
rs[19] += MM_LOAD(g2+(ix+i)*SIMDD) * MM_LOAD(g1+(iy+i)*SIMDD) * MM_LOAD(g4+(iz+i)*SIMDD);
rs[20] += MM_LOAD(g2+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g5+(iz+i)*SIMDD);
rs[21] += MM_LOAD(g1+(ix+i)*SIMDD) * MM_LOAD(g2+(iy+i)*SIMDD) * MM_LOAD(g4+(iz+i)*SIMDD);
rs[22] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g3+(iy+i)*SIMDD) * MM_LOAD(g4+(iz+i)*SIMDD);
rs[23] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g2+(iy+i)*SIMDD) * MM_LOAD(g5+(iz+i)*SIMDD);
rs[24] += MM_LOAD(g1+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g6+(iz+i)*SIMDD);
rs[25] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g1+(iy+i)*SIMDD) * MM_LOAD(g6+(iz+i)*SIMDD);
rs[26] += MM_LOAD(g0+(ix+i)*SIMDD) * MM_LOAD(g0+(iy+i)*SIMDD) * MM_LOAD(g7+(iz+i)*SIMDD);
}
r1 = - rs[0] - rs[4] - rs[8]; GOUT_SCATTER(gout, n*3+0, r1);
r1 = - rs[9] - rs[13] - rs[17]; GOUT_SCATTER(gout, n*3+1, r1);
r1 = - rs[18] - rs[22] - rs[26]; GOUT_SCATTER(gout, n*3+2, r1);
}}
void int1e_ipprinvp_optimizer(CINTOpt **opt, int *atm, int natm, int *bas, int nbas, double *env) {
int ng[] = {1, 2, 0, 0, 3, 1, 0, 3};
CINTall_1e_optimizer(opt, ng, atm, natm, bas, nbas, env);
}
int int1e_ipprinvp_cart(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 2, 0, 0, 3, 1, 0, 3};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_ipprinvp;
return CINT1e_drv(out, dims, &envs, opt, cache, &c2s_cart_1e);
} // int1e_ipprinvp_cart
int int1e_ipprinvp_sph(double *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 2, 0, 0, 3, 1, 0, 3};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_ipprinvp;
return CINT1e_drv(out, dims, &envs, opt, cache, &c2s_sph_1e);
} // int1e_ipprinvp_sph
int int1e_ipprinvp_spinor(double complex *out, int *dims, int *shls,
int *atm, int natm, int *bas, int nbas, double *env, CINTOpt *opt, double *cache) {
int ng[] = {1, 2, 0, 0, 3, 1, 0, 3};
CINTEnvVars envs;
CINTinit_int1e_EnvVars(&envs, ng, shls, atm, natm, bas, nbas, env);
envs.f_gout = &CINTgout1e_int1e_ipprinvp;
return CINT1e_spinor_drv(out, dims, &envs, opt, cache, &c2s_sf_1e);
} // int1e_ipprinvp_spinor
ALL_CINT1E(int1e_ipprinvp)
//ALL_CINT1E_FORTRAN_(cint1e_ipprinvp)
