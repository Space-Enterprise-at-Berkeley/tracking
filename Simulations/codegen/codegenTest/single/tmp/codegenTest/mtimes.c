#include "mtimes.h"
#include "codegenTest_float_mex_data.h"
#include "rt_nonfinite.h"
#include "blas.h"
#include <stddef.h>

void mtimes(const real_T A[81], const real_T B[81], real_T C[81])
{
  ptrdiff_t k_t;
  ptrdiff_t lda_t;
  ptrdiff_t ldb_t;
  ptrdiff_t ldc_t;
  ptrdiff_t m_t;
  ptrdiff_t n_t;
  real_T alpha1;
  real_T beta1;
  char_T TRANSA1;
  char_T TRANSB1;
  TRANSB1 = 'N';
  TRANSA1 = 'N';
  alpha1 = 1.0;
  beta1 = 0.0;
  m_t = (ptrdiff_t)9;
  n_t = (ptrdiff_t)9;
  k_t = (ptrdiff_t)9;
  lda_t = (ptrdiff_t)9;
  ldb_t = (ptrdiff_t)9;
  ldc_t = (ptrdiff_t)9;
  dgemm(&TRANSA1, &TRANSB1, &m_t, &n_t, &k_t, &alpha1, (real_T *)&A[0], &lda_t,
        (real_T *)&B[0], &ldb_t, &beta1, &C[0], &ldc_t);
}
