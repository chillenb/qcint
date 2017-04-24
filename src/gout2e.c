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

#include "simd.h"
#include "g2e.h"

/*
 * <ki|jl> = (ij|kl); i,j\in electron 1; k,l\in electron 2
 */
void CINTgout2e(double *gout, double *g, int *idx, CINTEnvVars *envs)
{
        int nf = envs->nf;
        if (nf == 1) {
                double *gz = g + envs->g_size * 2 * SIMDD;
                MM_STORE(gout, MM_LOAD(gz));
        } else {
                int nrys_roots = envs->nrys_roots;
                int i, n;
                double *gx, *gy, *gz;
                __MD r0, r1;
                switch(nrys_roots) {
                case 1:
                        for (n = 0; n < nf; n++) {
                                gx = g + idx[0+n*3] * SIMDD;
                                gy = g + idx[1+n*3] * SIMDD;
                                gz = g + idx[2+n*3] * SIMDD;
                                r0 = MM_LOAD(gx    );
                                r1 = MM_LOAD(gy    );
                                r0 = MM_MUL (r0, r1);
                                r1 = MM_LOAD(gz    );
                                r0 = MM_MUL (r0, r1);
                                MM_STORE(gout+n*SIMDD, r0);
                        }
                        break;
                case 2:
                        for (n = 0; n < nf; n++) {
                                gx = g + idx[0+n*3] * SIMDD;
                                gy = g + idx[1+n*3] * SIMDD;
                                gz = g + idx[2+n*3] * SIMDD;
                                r0 = MM_MUL(MM_MUL(MM_LOAD(gx      ), MM_LOAD(gy      )), MM_LOAD(gz      ));
                                r0 = MM_FMA(MM_MUL(MM_LOAD(gx+SIMDD), MM_LOAD(gy+SIMDD)), MM_LOAD(gz+SIMDD), r0);
                                MM_STORE(gout+n*SIMDD, r0);
                        }
                        break;
                case 3:
                        for (n = 0; n < nf; n++) {
                                gx = g + idx[0+n*3] * SIMDD;
                                gy = g + idx[1+n*3] * SIMDD;
                                gz = g + idx[2+n*3] * SIMDD;
                                r0 = MM_MUL(MM_MUL(MM_LOAD(gx        ), MM_LOAD(gy        )), MM_LOAD(gz        ));
                                r0 = MM_FMA(MM_MUL(MM_LOAD(gx+  SIMDD), MM_LOAD(gy+  SIMDD)), MM_LOAD(gz+  SIMDD), r0);
                                r0 = MM_FMA(MM_MUL(MM_LOAD(gx+2*SIMDD), MM_LOAD(gy+2*SIMDD)), MM_LOAD(gz+2*SIMDD), r0);
                                MM_STORE(gout+n*SIMDD, r0);
                        }
                        break;
                case 4:
                        for (n = 0; n < nf; n++) {
                                gx = g + idx[0+n*3] * SIMDD;
                                gy = g + idx[1+n*3] * SIMDD;
                                gz = g + idx[2+n*3] * SIMDD;
                                r0 = MM_MUL(MM_MUL(MM_LOAD(gx        ), MM_LOAD(gy        )), MM_LOAD(gz        ));
                                r0 = MM_FMA(MM_MUL(MM_LOAD(gx+  SIMDD), MM_LOAD(gy+  SIMDD)), MM_LOAD(gz+  SIMDD), r0);
                                r0 = MM_FMA(MM_MUL(MM_LOAD(gx+2*SIMDD), MM_LOAD(gy+2*SIMDD)), MM_LOAD(gz+2*SIMDD), r0);
                                r0 = MM_FMA(MM_MUL(MM_LOAD(gx+3*SIMDD), MM_LOAD(gy+3*SIMDD)), MM_LOAD(gz+3*SIMDD), r0);
                                MM_STORE(gout+n*SIMDD, r0);
                        }
                        break;
                case 5:
                        for (n = 0; n < nf; n++) {
                                gx = g + idx[0+n*3] * SIMDD;
                                gy = g + idx[1+n*3] * SIMDD;
                                gz = g + idx[2+n*3] * SIMDD;
                                r0 = MM_MUL(MM_MUL(MM_LOAD(gx        ), MM_LOAD(gy        )), MM_LOAD(gz        ));
                                r0 = MM_FMA(MM_MUL(MM_LOAD(gx+  SIMDD), MM_LOAD(gy+  SIMDD)), MM_LOAD(gz+  SIMDD), r0);
                                r0 = MM_FMA(MM_MUL(MM_LOAD(gx+2*SIMDD), MM_LOAD(gy+2*SIMDD)), MM_LOAD(gz+2*SIMDD), r0);
                                r0 = MM_FMA(MM_MUL(MM_LOAD(gx+3*SIMDD), MM_LOAD(gy+3*SIMDD)), MM_LOAD(gz+3*SIMDD), r0);
                                r0 = MM_FMA(MM_MUL(MM_LOAD(gx+4*SIMDD), MM_LOAD(gy+4*SIMDD)), MM_LOAD(gz+4*SIMDD), r0);
                                MM_STORE(gout+n*SIMDD, r0);
                        }
                        break;
                case 6:
                        for (n = 0; n < nf; n++) {
                                gx = g + idx[0+n*3] * SIMDD;
                                gy = g + idx[1+n*3] * SIMDD;
                                gz = g + idx[2+n*3] * SIMDD;
                                r0 = MM_MUL(MM_MUL(MM_LOAD(gx        ), MM_LOAD(gy        )), MM_LOAD(gz        ));
                                r0 = MM_FMA(MM_MUL(MM_LOAD(gx+  SIMDD), MM_LOAD(gy+  SIMDD)), MM_LOAD(gz+  SIMDD), r0);
                                r0 = MM_FMA(MM_MUL(MM_LOAD(gx+2*SIMDD), MM_LOAD(gy+2*SIMDD)), MM_LOAD(gz+2*SIMDD), r0);
                                r0 = MM_FMA(MM_MUL(MM_LOAD(gx+3*SIMDD), MM_LOAD(gy+3*SIMDD)), MM_LOAD(gz+3*SIMDD), r0);
                                r0 = MM_FMA(MM_MUL(MM_LOAD(gx+4*SIMDD), MM_LOAD(gy+4*SIMDD)), MM_LOAD(gz+4*SIMDD), r0);
                                r0 = MM_FMA(MM_MUL(MM_LOAD(gx+5*SIMDD), MM_LOAD(gy+5*SIMDD)), MM_LOAD(gz+5*SIMDD), r0);
                                MM_STORE(gout+n*SIMDD, r0);
                        }
                        break;
                case 7:
                        for (n = 0; n < nf; n++) {
                                gx = g + idx[0+n*3] * SIMDD;
                                gy = g + idx[1+n*3] * SIMDD;
                                gz = g + idx[2+n*3] * SIMDD;
                                r0 = MM_MUL(MM_MUL(MM_LOAD(gx        ), MM_LOAD(gy        )), MM_LOAD(gz        ));
                                r0 = MM_FMA(MM_MUL(MM_LOAD(gx+  SIMDD), MM_LOAD(gy+  SIMDD)), MM_LOAD(gz+  SIMDD), r0);
                                r0 = MM_FMA(MM_MUL(MM_LOAD(gx+2*SIMDD), MM_LOAD(gy+2*SIMDD)), MM_LOAD(gz+2*SIMDD), r0);
                                r0 = MM_FMA(MM_MUL(MM_LOAD(gx+3*SIMDD), MM_LOAD(gy+3*SIMDD)), MM_LOAD(gz+3*SIMDD), r0);
                                r0 = MM_FMA(MM_MUL(MM_LOAD(gx+4*SIMDD), MM_LOAD(gy+4*SIMDD)), MM_LOAD(gz+4*SIMDD), r0);
                                r0 = MM_FMA(MM_MUL(MM_LOAD(gx+5*SIMDD), MM_LOAD(gy+5*SIMDD)), MM_LOAD(gz+5*SIMDD), r0);
                                r0 = MM_FMA(MM_MUL(MM_LOAD(gx+6*SIMDD), MM_LOAD(gy+6*SIMDD)), MM_LOAD(gz+6*SIMDD), r0);
                                MM_STORE(gout+n*SIMDD, r0);
                        }
                        break;
                default:
                        for (n = 0; n < nf; n++) {
                                gx = g + idx[0+n*3] * SIMDD;
                                gy = g + idx[1+n*3] * SIMDD;
                                gz = g + idx[2+n*3] * SIMDD;
                                //for (k = 0; k < SIMDD; k++) {
                                //        gc[k] = gx[k] * gy[k] * gz[k];
                                //}
                                r0 = MM_MUL(MM_MUL(MM_LOAD(gx), MM_LOAD(gy)), MM_LOAD(gz));

                                for (i = 1; i < nrys_roots-1; i+=2) {
                                        //for (k = 0; k < SIMDD; k++) {
                                        //        gc[k]+= gx[i*SIMDD+k] * gy[i*SIMDD+k] * gz[i*SIMDD+k];
                                        //}
        r0 = MM_FMA(MM_MUL(MM_LOAD(gx+ i   *SIMDD), MM_LOAD(gy+ i   *SIMDD)), MM_LOAD(gz+ i   *SIMDD), r0);
        r0 = MM_FMA(MM_MUL(MM_LOAD(gx+(i+1)*SIMDD), MM_LOAD(gy+(i+1)*SIMDD)), MM_LOAD(gz+(i+1)*SIMDD), r0);
                                }
                                if (i < nrys_roots) {
        r0 = MM_FMA(MM_MUL(MM_LOAD(gx+ i   *SIMDD), MM_LOAD(gy+ i   *SIMDD)), MM_LOAD(gz+ i   *SIMDD), r0);
                                }
                                MM_STORE(gout+n*SIMDD, r0);
                        }
                }
        }
}

void CINTgout2e_simd1(double *gout, double *g, int *idx, CINTEnvVars *envs)
{
        int nf = envs->nf;
        int nrys_roots = envs->nrys_roots;
        int i, ix, iy, iz, n;
        int jx, jy, jz;
        __m128d r0, r1, r2, r3;

        //_mm256_zeroupper();
        switch (nrys_roots) {
                case 1:
                        for (n = 0; n < nf; n++) {
                                ix = idx[0+n*3];
                                iy = idx[1+n*3];
                                iz = idx[2+n*3];
                                gout[n] = g[ix] * g[iy] * g[iz];
                        }
                        break;
                case 2:
                        for (n = 0; n < nf-1; n+=2) {
                                ix = idx[0+n*3];
                                iy = idx[1+n*3];
                                iz = idx[2+n*3];
                                jx = idx[3+n*3];
                                jy = idx[4+n*3];
                                jz = idx[5+n*3];
                                r0 = _mm_load_pd(g+ix  );
                                r1 = _mm_load_pd(g+iy  );
                                r0 = _mm_mul_pd (r0, r1);
                                r1 = _mm_load_pd(g+iz  );
                                r3 = _mm_mul_pd (r0, r1);
                                r0 = _mm_load_pd(g+jx  );
                                r1 = _mm_load_pd(g+jy  );
                                r0 = _mm_mul_pd (r0, r1);
                                r1 = _mm_load_pd(g+jz  );
                                r0 = _mm_mul_pd (r0, r1);

                                r3 = _mm_hadd_pd(r3, r0);
                                _mm_storeu_pd(gout+n, r3);
                        }
                        if (n < nf) {
                                ix = idx[0+n*3];
                                iy = idx[1+n*3];
                                iz = idx[2+n*3];
                                r0 = _mm_load_pd(g+ix  );
                                r1 = _mm_load_pd(g+iy  );
                                r0 = _mm_mul_pd (r0, r1);
                                r1 = _mm_load_pd(g+iz  );
                                r0 = _mm_mul_pd (r0, r1);
                                r0 = _mm_hadd_pd(r0, r0);
                                _mm_store_sd(gout+n, r0);
                        }
                        break;
                case 3:
                        for (n = 0; n < nf-1; n+=2) {
                                ix = idx[0+n*3];
                                iy = idx[1+n*3];
                                iz = idx[2+n*3];
                                jx = idx[3+n*3];
                                jy = idx[4+n*3];
                                jz = idx[5+n*3];
                                r0 = _mm_loadu_pd(g+ix  );
                                r1 = _mm_loadu_pd(g+iy  );
                                r0 = _mm_mul_pd (r0, r1);
                                r1 = _mm_loadu_pd(g+iz  );
                                r3 = _mm_mul_pd (r0, r1);

                                r0 = _mm_loadu_pd(g+jx  );
                                r1 = _mm_loadu_pd(g+jy  );
                                r0 = _mm_mul_pd (r0, r1);
                                r1 = _mm_loadu_pd(g+jz  );
                                r0 = _mm_mul_pd (r0, r1);
                                r3 = _mm_hadd_pd(r3, r0);

                                r0 = _mm_loadl_pd(r0, g+ix+2);
                                r0 = _mm_loadh_pd(r0, g+jx+2);
                                r1 = _mm_loadl_pd(r1, g+iy+2);
                                r1 = _mm_loadh_pd(r1, g+jy+2);
                                r0 = _mm_mul_pd (r0, r1);
                                r1 = _mm_loadl_pd(r1, g+iz+2);
                                r1 = _mm_loadh_pd(r1, g+jz+2);
                                r0 = _mm_mul_pd (r0, r1);
                                r3 = _mm_add_pd (r0, r3);
                                _mm_storeu_pd(gout+n, r3);
                        }
                        if (n < nf) {
                                ix = idx[0+n*3];
                                iy = idx[1+n*3];
                                iz = idx[2+n*3];
                                r0 = _mm_loadu_pd(g+ix  );
                                r1 = _mm_loadu_pd(g+iy  );
                                r0 = _mm_mul_pd (r0, r1);
                                r1 = _mm_loadu_pd(g+iz  );
                                r0 = _mm_mul_pd (r0, r1);
                                r0 = _mm_hadd_pd(r0, r0);
                                _mm_store_sd(gout+n, r0);
                                gout[n] += g[ix+2] * g[iy+2] * g[iz+2];
                        }
                        break;
                case 4:
                        for (n = 0; n < nf-1; n+=2) {
                                ix = idx[0+n*3];
                                iy = idx[1+n*3];
                                iz = idx[2+n*3];
                                jx = idx[3+n*3];
                                jy = idx[4+n*3];
                                jz = idx[5+n*3];
                                r0 = _mm_load_pd(g+ix  );
                                r1 = _mm_load_pd(g+iy  );
                                r0 = _mm_mul_pd (r0, r1);
                                r1 = _mm_load_pd(g+iz  );
                                r0 = _mm_mul_pd (r0, r1);
                                r2 = _mm_load_pd(g+ix+2);
                                r1 = _mm_load_pd(g+iy+2);
                                r2 = _mm_mul_pd (r2, r1);
                                r1 = _mm_load_pd(g+iz+2);
                                r2 = _mm_mul_pd (r2, r1);
                                r3 = _mm_add_pd (r0, r2);

                                r0 = _mm_load_pd(g+jx  );
                                r1 = _mm_load_pd(g+jy  );
                                r0 = _mm_mul_pd (r0, r1);
                                r1 = _mm_load_pd(g+jz  );
                                r0 = _mm_mul_pd (r0, r1);
                                r2 = _mm_load_pd(g+jx+2);
                                r1 = _mm_load_pd(g+jy+2);
                                r2 = _mm_mul_pd (r2, r1);
                                r1 = _mm_load_pd(g+jz+2);
                                r2 = _mm_mul_pd (r2, r1);
                                r0 = _mm_add_pd (r0, r2);

                                r3 = _mm_hadd_pd(r3, r0);
                                _mm_storeu_pd(gout+n, r3);
                        }
                        if (n < nf) {
                                ix = idx[0+n*3];
                                iy = idx[1+n*3];
                                iz = idx[2+n*3];
                                r0 = _mm_load_pd(g+ix  );
                                r1 = _mm_load_pd(g+iy  );
                                r0 = _mm_mul_pd (r0, r1);
                                r1 = _mm_load_pd(g+iz  );
                                r0 = _mm_mul_pd (r0, r1);
                                r2 = _mm_load_pd(g+ix+2);
                                r1 = _mm_load_pd(g+iy+2);
                                r2 = _mm_mul_pd (r2, r1);
                                r1 = _mm_load_pd(g+iz+2);
                                r2 = _mm_mul_pd (r2, r1);
                                r0 = _mm_add_pd (r0, r2);
                                r0 = _mm_hadd_pd(r0, r0);
                                _mm_store_sd(gout+n, r0);
                        }
                        break;
                case 5:
                        for (n = 0; n < nf-1; n+=2) {
                                ix = idx[0+n*3];
                                iy = idx[1+n*3];
                                iz = idx[2+n*3];
                                jx = idx[3+n*3];
                                jy = idx[4+n*3];
                                jz = idx[5+n*3];
                                r0 = _mm_loadu_pd(g+ix  );
                                r1 = _mm_loadu_pd(g+iy  );
                                r0 = _mm_mul_pd (r0, r1);
                                r1 = _mm_loadu_pd(g+iz  );
                                r0 = _mm_mul_pd (r0, r1);
                                r2 = _mm_loadu_pd(g+ix+2);
                                r1 = _mm_loadu_pd(g+iy+2);
                                r2 = _mm_mul_pd (r2, r1);
                                r1 = _mm_loadu_pd(g+iz+2);
                                r2 = _mm_mul_pd (r2, r1);
                                r3 = _mm_add_pd (r0, r2);

                                r0 = _mm_loadu_pd(g+jx  );
                                r1 = _mm_loadu_pd(g+jy  );
                                r0 = _mm_mul_pd (r0, r1);
                                r1 = _mm_loadu_pd(g+jz  );
                                r0 = _mm_mul_pd (r0, r1);
                                r2 = _mm_loadu_pd(g+jx+2);
                                r1 = _mm_loadu_pd(g+jy+2);
                                r2 = _mm_mul_pd (r2, r1);
                                r1 = _mm_loadu_pd(g+jz+2);
                                r2 = _mm_mul_pd (r2, r1);
                                r0 = _mm_add_pd (r0, r2);
                                r3 = _mm_hadd_pd(r3, r0);

                                r0 = _mm_loadl_pd(r0, g+ix+4);
                                r0 = _mm_loadh_pd(r0, g+jx+4);
                                r1 = _mm_loadl_pd(r1, g+iy+4);
                                r1 = _mm_loadh_pd(r1, g+jy+4);
                                r0 = _mm_mul_pd (r0, r1);
                                r1 = _mm_loadl_pd(r1, g+iz+4);
                                r1 = _mm_loadh_pd(r1, g+jz+4);
                                r0 = _mm_mul_pd (r0, r1);
                                r3 = _mm_add_pd (r0, r3);
                                _mm_storeu_pd(gout+n, r3);
                        }
                        if (n < nf) {
                                ix = idx[0+n*3];
                                iy = idx[1+n*3];
                                iz = idx[2+n*3];
                                r0 = _mm_loadu_pd(g+ix  );
                                r1 = _mm_loadu_pd(g+iy  );
                                r0 = _mm_mul_pd (r0, r1);
                                r1 = _mm_loadu_pd(g+iz  );
                                r0 = _mm_mul_pd (r0, r1);
                                r2 = _mm_loadu_pd(g+ix+2);
                                r1 = _mm_loadu_pd(g+iy+2);
                                r2 = _mm_mul_pd (r2, r1);
                                r1 = _mm_loadu_pd(g+iz+2);
                                r2 = _mm_mul_pd (r2, r1);
                                r0 = _mm_add_pd (r0, r2);
                                r0 = _mm_hadd_pd(r0, r0);
                                _mm_store_sd(gout+n, r0);
                                gout[n] += g[ix+4] * g[iy+4] * g[iz+4];
                        }
                        break;
                case 6:
                        for (n = 0; n < nf-1; n+=2) {
                                ix = idx[0+n*3];
                                iy = idx[1+n*3];
                                iz = idx[2+n*3];
                                jx = idx[3+n*3];
                                jy = idx[4+n*3];
                                jz = idx[5+n*3];
                                r0 = _mm_load_pd(g+ix  );
                                r1 = _mm_load_pd(g+iy  );
                                r0 = _mm_mul_pd (r0, r1);
                                r1 = _mm_load_pd(g+iz  );
                                r0 = _mm_mul_pd (r0, r1);
                                r2 = _mm_load_pd(g+ix+2);
                                r1 = _mm_load_pd(g+iy+2);
                                r2 = _mm_mul_pd (r2, r1);
                                r1 = _mm_load_pd(g+iz+2);
                                r2 = _mm_mul_pd (r2, r1);
                                r0 = _mm_add_pd (r0, r2);
                                r2 = _mm_load_pd(g+ix+4);
                                r1 = _mm_load_pd(g+iy+4);
                                r2 = _mm_mul_pd (r2, r1);
                                r1 = _mm_load_pd(g+iz+4);
                                r2 = _mm_mul_pd (r2, r1);
                                r3 = _mm_add_pd (r0, r2);

                                r0 = _mm_load_pd(g+jx  );
                                r1 = _mm_load_pd(g+jy  );
                                r0 = _mm_mul_pd (r0, r1);
                                r1 = _mm_load_pd(g+jz  );
                                r0 = _mm_mul_pd (r0, r1);
                                r2 = _mm_load_pd(g+jx+2);
                                r1 = _mm_load_pd(g+jy+2);
                                r2 = _mm_mul_pd (r2, r1);
                                r1 = _mm_load_pd(g+jz+2);
                                r2 = _mm_mul_pd (r2, r1);
                                r0 = _mm_add_pd (r0, r2);
                                r2 = _mm_load_pd(g+jx+4);
                                r1 = _mm_load_pd(g+jy+4);
                                r2 = _mm_mul_pd (r2, r1);
                                r1 = _mm_load_pd(g+jz+4);
                                r2 = _mm_mul_pd (r2, r1);
                                r0 = _mm_add_pd (r0, r2);

                                r3 = _mm_hadd_pd(r3, r0);
                                _mm_storeu_pd(gout+n, r3);
                        }
                        if (n < nf) {
                                ix = idx[0+n*3];
                                iy = idx[1+n*3];
                                iz = idx[2+n*3];
                                r0 = _mm_load_pd(g+ix  );
                                r1 = _mm_load_pd(g+iy  );
                                r0 = _mm_mul_pd (r0, r1);
                                r1 = _mm_load_pd(g+iz  );
                                r0 = _mm_mul_pd (r0, r1);
                                r2 = _mm_load_pd(g+ix+2);
                                r1 = _mm_load_pd(g+iy+2);
                                r2 = _mm_mul_pd (r2, r1);
                                r1 = _mm_load_pd(g+iz+2);
                                r2 = _mm_mul_pd (r2, r1);
                                r0 = _mm_add_pd (r0, r2);
                                r2 = _mm_load_pd(g+ix+4);
                                r1 = _mm_load_pd(g+iy+4);
                                r2 = _mm_mul_pd (r2, r1);
                                r1 = _mm_load_pd(g+iz+4);
                                r2 = _mm_mul_pd (r2, r1);
                                r0 = _mm_add_pd (r0, r2);
                                r0 = _mm_hadd_pd(r0, r0);
                                _mm_store_sd(gout+n, r0);
                        }
                        break;
                case 7:
                        for (n = 0; n < nf-1; n+=2) {
                                ix = idx[0+n*3];
                                iy = idx[1+n*3];
                                iz = idx[2+n*3];
                                jx = idx[3+n*3];
                                jy = idx[4+n*3];
                                jz = idx[5+n*3];
                                r0 = _mm_loadu_pd(g+ix  );
                                r1 = _mm_loadu_pd(g+iy  );
                                r0 = _mm_mul_pd (r0, r1);
                                r1 = _mm_loadu_pd(g+iz  );
                                r0 = _mm_mul_pd (r0, r1);
                                r2 = _mm_loadu_pd(g+ix+2);
                                r1 = _mm_loadu_pd(g+iy+2);
                                r2 = _mm_mul_pd (r2, r1);
                                r1 = _mm_loadu_pd(g+iz+2);
                                r2 = _mm_mul_pd (r2, r1);
                                r0 = _mm_add_pd (r0, r2);
                                r2 = _mm_loadu_pd(g+ix+4);
                                r1 = _mm_loadu_pd(g+iy+4);
                                r2 = _mm_mul_pd (r2, r1);
                                r1 = _mm_loadu_pd(g+iz+4);
                                r2 = _mm_mul_pd (r2, r1);
                                r3 = _mm_add_pd (r0, r2);

                                r0 = _mm_loadu_pd(g+jx  );
                                r1 = _mm_loadu_pd(g+jy  );
                                r0 = _mm_mul_pd (r0, r1);
                                r1 = _mm_loadu_pd(g+jz  );
                                r0 = _mm_mul_pd (r0, r1);
                                r2 = _mm_loadu_pd(g+jx+2);
                                r1 = _mm_loadu_pd(g+jy+2);
                                r2 = _mm_mul_pd (r2, r1);
                                r1 = _mm_loadu_pd(g+jz+2);
                                r2 = _mm_mul_pd (r2, r1);
                                r0 = _mm_add_pd (r0, r2);
                                r2 = _mm_loadu_pd(g+jx+4);
                                r1 = _mm_loadu_pd(g+jy+4);
                                r2 = _mm_mul_pd (r2, r1);
                                r1 = _mm_loadu_pd(g+jz+4);
                                r2 = _mm_mul_pd (r2, r1);
                                r0 = _mm_add_pd (r0, r2);
                                r3 = _mm_hadd_pd(r3, r0);

                                r0 = _mm_loadl_pd(r0, g+ix+6);
                                r0 = _mm_loadh_pd(r0, g+jx+6);
                                r1 = _mm_loadl_pd(r1, g+iy+6);
                                r1 = _mm_loadh_pd(r1, g+jy+6);
                                r0 = _mm_mul_pd (r0, r1);
                                r1 = _mm_loadl_pd(r1, g+iz+6);
                                r1 = _mm_loadh_pd(r1, g+jz+6);
                                r0 = _mm_mul_pd (r0, r1);
                                r3 = _mm_add_pd (r0, r3);
                                _mm_storeu_pd(gout+n, r3);
                        }
                        if (n < nf) {
                                ix = idx[0+n*3];
                                iy = idx[1+n*3];
                                iz = idx[2+n*3];
                                r0 = _mm_loadu_pd(g+ix  );
                                r1 = _mm_loadu_pd(g+iy  );
                                r0 = _mm_mul_pd (r0, r1);
                                r1 = _mm_loadu_pd(g+iz  );
                                r0 = _mm_mul_pd (r0, r1);
                                r2 = _mm_loadu_pd(g+ix+2);
                                r1 = _mm_loadu_pd(g+iy+2);
                                r2 = _mm_mul_pd (r2, r1);
                                r1 = _mm_loadu_pd(g+iz+2);
                                r2 = _mm_mul_pd (r2, r1);
                                r0 = _mm_add_pd (r0, r2);
                                r2 = _mm_loadu_pd(g+ix+4);
                                r1 = _mm_loadu_pd(g+iy+4);
                                r2 = _mm_mul_pd (r2, r1);
                                r1 = _mm_loadu_pd(g+iz+4);
                                r2 = _mm_mul_pd (r2, r1);
                                r0 = _mm_add_pd (r0, r2);
                                r0 = _mm_hadd_pd(r0, r0);
                                _mm_store_sd(gout+n, r0);
                                gout[n] += g[ix+6] * g[iy+6] * g[iz+6];
                        }
                        break;
                default:
                        for (n = 0; n < nf; n++) {
                                ix = idx[0+n*3];
                                iy = idx[1+n*3];
                                iz = idx[2+n*3];
                                r0 = _mm_loadu_pd(g+ix  );
                                r1 = _mm_loadu_pd(g+iy  );
                                r0 = _mm_mul_pd(r0, r1);
                                r1 = _mm_loadu_pd(g+iz  );
                                r0 = _mm_mul_pd(r0, r1);
                                r2 = _mm_loadu_pd(g+ix+2);
                                r1 = _mm_loadu_pd(g+iy+2);
                                r2 = _mm_mul_pd(r2, r1);
                                r1 = _mm_loadu_pd(g+iz+2);
                                r2 = _mm_mul_pd(r2, r1);
                                r0 = _mm_add_pd(r0, r2);
                                r2 = _mm_loadu_pd(g+ix+4);
                                r1 = _mm_loadu_pd(g+iy+4);
                                r2 = _mm_mul_pd(r2, r1);
                                r1 = _mm_loadu_pd(g+iz+4);
                                r2 = _mm_mul_pd(r2, r1);
                                r0 = _mm_add_pd(r0, r2);
                                r2 = _mm_loadu_pd(g+ix+6);
                                r1 = _mm_loadu_pd(g+iy+6);
                                r2 = _mm_mul_pd(r2, r1);
                                r1 = _mm_loadu_pd(g+iz+6);
                                r2 = _mm_mul_pd(r2, r1);
                                r3 = _mm_add_pd(r0, r2);
                                for (i = 8; i < nrys_roots-1; i+=2) {
                                        r0 = _mm_loadu_pd(g+ix+i);
                                        r1 = _mm_loadu_pd(g+iy+i);
                                        r0 = _mm_mul_pd(r0, r1);
                                        r1 = _mm_loadu_pd(g+iz+i);
                                        r0 = _mm_mul_pd(r0, r1);
                                        r3 = _mm_add_pd(r3, r0);
                                }
                                r3 = _mm_hadd_pd(r3, r3);
                                _mm_store_sd(gout+n, r3);
                                if (i < nrys_roots) {
                                        gout[n] += g[ix+i] * g[iy+i] * g[iz+i];
                                }
                        }
                        break;
        } // end switch nroots
}
