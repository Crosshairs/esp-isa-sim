if(sreg_t(RS1) < sreg_t(RS2)) {
  WRITE_RD(RS2);
} else {
  WRITE_RD(RS1);
}