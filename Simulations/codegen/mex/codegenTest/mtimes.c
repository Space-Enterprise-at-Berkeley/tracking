/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * mtimes.c
 *
 * Code generation for function 'mtimes'
 *
 */

/* Include files */
#include "mtimes.h"
#include "rt_nonfinite.h"
#include "blas.h"
#include <stddef.h>

/* Function Definitions */
void mtimes(const real32_T A[81], const real32_T B[81], real32_T C[81])
{
  ptrdiff_t k_t;
  ptrdiff_t lda_t;
  ptrdiff_t ldb_t;
  ptrdiff_t ldc_t;
  ptrdiff_t m_t;
  ptrdiff_t n_t;
  real32_T alpha1;
  real32_T beta1;
  char_T TRANSA1;
  char_T TRANSB1;
  TRANSB1 = 'N';
  TRANSA1 = 'N';
  alpha1 = 1.0F;
  beta1 = 0.0F;
  m_t = (ptrdiff_t)9;
  n_t = (ptrdiff_t)9;
  k_t = (ptrdiff_t)9;
  lda_t = (ptrdiff_t)9;
  ldb_t = (ptrdiff_t)9;
  ldc_t = (ptrdiff_t)9;
  sgemm(&TRANSA1, &TRANSB1, &m_t, &n_t, &k_t, &alpha1, (real32_T *)&A[0],
        &lda_t, (real32_T *)&B[0], &ldb_t, &beta1, &C[0], &ldc_t);
}

/* End of code generation (mtimes.c) */
