require_fp;
softfloat_roundingMode = VRM;
WRITE_FRD(f64_mulAdd(FRS1, FRS2, (FRS1 ^ FRS2) & (uint64_t)INT64_MIN));
set_fp_exceptions;
