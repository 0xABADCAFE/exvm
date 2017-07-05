; example code

export @mainProgram
import @nativeAllocBuffer
import @nativeWriteBuffer
import @nativeFreeBuffer

@renderFractal:
  ; r0 = pixel data address
  ; r1 = width in pixels
  ; r2 = height in pixels
  ; r3 = cY (float pos, starting at yMin)
  ; r4 = y (int) pixel
  ; r5 = xMin (float)
  ; r6 = cX (float pos, starting at xMin)
  ; r7 = fStep
  ; r8 = x (int) pixel
  ; r9 = iStep (1)

  ; r11-15 - temporaries

  save      r0             ; 2 : save pixel address
  loadq     #0, r4         ; 1 : y = 0
  load.s32  #255, r9       ; 2 : i = max iteration

@yloop:                    ; do {
  loadq      #0, r8          ; 1 : x = 0
  move.32    r5, r6          ; 1 : cX = xMin

@xloop:                      ; do {
  move.32    r6, r10           ; 1 : zx = cX
  move.32    r3, r11           ; 1 : zy = cY
  loadq      #0, r12           ; 1 : n  = 0

@iter:                         ; while (zx*zx + zy*zy < 4.0 && i < max) {
  move.32    r10, r13            ; 1
  mul.f32    r10, r13            ; 1 : zx2 = zx*zx
  move.32    r11, r14            ; 1
  mul.f32    r11, r14            ; 1 : zy2   = zy*zy

  move.32    r6,  r15            ; 1 : new_zx = cX
  add.f32    r13, r15            ; 1 : new_zx += zx2
  sub.f32    r14, r15            ; 1 : new_zx -= zy2

  add.f32    r14, r13            ; 1 : r14 = zx*zx + zy*zy (for loop test)

  move.32    r10, r14            ; 1 : tmp = zx
  mul.f32    r11, r14            ; 1 : tmp *= zy
  add.f32    r14, r14            ; 1 : tmp += tmp2
  add.f32    r3,  r14            ; 1 : tmp += cY (tmp = 2*zx*zy+cY)

  move.32    r14, r11            ; 1 : zy = tmp
  move.32    r15, r10            ; 1 : zx = new_zx
  add.s16    #1,  r12            ; 2 : n++

  load.f32   $4.0, r15           ; 3
  bgr.f32    r13, r15, @bail     ; 2
  bls.s32    r12, r9, @iter      ; 2 : }

@bail:
  mul.u16    r12, r12          ; 1
  store.8    r12, (r0)+        ; 1 : out = n
  add.f32    r7, r6            ; 1 : cX += fStep
  add.s16    #1, r8            ; 2 : x += iStep

  bls.s32    r8, r1, @xloop    ; 2 : } while (x < width)

  add.f32    r7, r3          ; 1 : cY += fStep
  add.s16    #1, r4          ; 2 : y += iStep
  bls.s32    r4, r2, @yloop  ; 2 : } while (y < height)

  rest       r0            ; 1 : restore pixel address
  ret


@calculateRanges:
; calculates xMin in r6, xMax in r7, step in r8
  move.32    r4, r5
  sub.f32    r3, r5         ; r5 = r4-r3 (total y range)
  f32.s32    r1, r6         ; r6 = (float) r1
  move.32    r6, r8
  mul.f32    r5, r6         ; r6 *= r5
  f32.s32    r2, r5         ; r5 = (float) r2
  div.f32    r5, r6         ; r6 /= r5
  move.32    r6, r7
  div.f32    r8, r7
  load.f32   $0.75, r5
  sub.f32    r6, r5
  add.f32    r5, r6
  ret

@mainProgram:
; entry point
  load.s16   #512, r1
  load.s16   #512, r2
  calln      @nativeAllocBuffer
  load.f32   $-1.25f, r3       ; yMin
  load.f32   $1.25f, r4        ; yMax
  call       @calculateRanges
  call       @renderFractal
  loada      @filename, r15
  calln      @nativeWriteBuffer
  calln      @nativeFreeBuffer
  ret

@filename:
  const.u8 "framebuffer.pgm"

