require_fp;
softfloat_roundingMode = VFRM;
WRITE_FRD(f64_mulAdd(f32_to_f64(f32(HFRS1)), f32_to_f64(f32(HFRS2)), f32_to_f64(f32(f32(HFRS3).v ^ F32_SIGN))));
set_fp_exceptions;
