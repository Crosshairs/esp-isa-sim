require_fp;
WRITE_SFRD(isNaNF32UI(FRS2) || f32_le_quiet(FRS2,FRS1) /* && FRS1 not NaN */
      ? FRS1 : FRS2);
set_fp_exceptions;
