#include "codegenTest_float_mex_mexutil.h"
#include "codegenTest_float_mex_data.h"
#include "rt_nonfinite.h"

void emlrtInitVarDataTables(emlrtLocationLoggingDataType dataTables[24])
{
  int32_T i;
  for (i = 0; i < 24; i++) {
    dataTables[i].SimMin = rtInf;
    dataTables[i].SimMax = rtMinusInf;
    dataTables[i].OverflowWraps = 0;
    dataTables[i].Saturations = 0;
    dataTables[i].IsAlwaysInteger = true;
    dataTables[i].HistogramTable = (emlrtLocationLoggingHistogramType *)NULL;
  }
}
