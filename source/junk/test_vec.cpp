//#include <stdlib.h>

// g++ -O3  test_vec.cpp -S

typedef float float32;

// Define a structure of 4 floats
struct str4f {
  float32 x, y, z, w;

  str4f(float32 a, float32 b, float32 c, float32 d) {
    x = a; y = b; z = c; w = d;
  }
};

// Define an array of 4 floats
typedef float32 vec4f __attribute__ ((vector_size (16)));


// Define add for the strucutre version
str4f add(str4f a, str4f b) {
  return str4f(
    a.x + b.x,
    a.y + b.y,
    a.z + b.z,
    a.w + b.w
  );
}
/*
_Z3add5str4fS_:
.LFB3:
	.cfi_startproc
	subq	$88, %rsp
	.cfi_def_cfa_offset 96
	movq	%xmm0, 32(%rsp)
	movq	%xmm1, 40(%rsp)
	movq	%xmm2, 16(%rsp)
	movq	%xmm3, 24(%rsp)
	movq	%fs:40, %rax
	movq	%rax, 72(%rsp)
	xorl	%eax, %eax
	movups	16(%rsp), %xmm0
	movups	32(%rsp), %xmm1
	addps	%xmm0, %xmm1
	movaps	%xmm1, (%rsp)
	movq	8(%rsp), %rax
	movaps	%xmm1, 48(%rsp)
	movq	(%rsp), %xmm0
	movq	%rax, (%rsp)
	movq	72(%rsp), %rax
	xorq	%fs:40, %rax
	movq	(%rsp), %xmm1
	jne	.L5
	addq	$88, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
*/

// Define add for the vector version
vec4f add(vec4f a, vec4f b) {
  return a + b;
}

/*
_Z3addDv4_fS_:
.LFB4:
	.cfi_startproc
	addps	%xmm1, %xmm0
	ret
*/
