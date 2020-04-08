# float dotProductImpl(const std::vector<float> &v1,
#                      const std::vector<float> &v2);

.global dotProductImpl
.text

dotProductImpl:
  movi    v0.4s, #0
  ldp     x0, x2, [x0]
  ldr     x1, [x1]
  sub     x3, x2, x0
  asr     x3, x3, #4
  cbz     x3, sum

loop:
  ld1     {v1.4s}, [x0], #16
  ld1     {v2.4s}, [x1], #16
  subs    x3, x3, #1
  fmla    v0.4s, v1.4s, v2.4s
  bne     loop

sum:
  faddp   v0.4s, v0.4s, v0.4s
  faddp   v0.4s, v0.4s, v0.4s

  cmp     x0, x2
  bhs     exit

leftover:
  ldr     s1, [x0], #4
  ldr     s2, [x1], #4
  cmp     x0, x2
  fmadd   s0, s1, s2, s0
  bne     leftover

exit:
  ret

.end
