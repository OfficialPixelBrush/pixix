#include <stdio.h>
#include <time.h>

struct complex {
	float r,i;
};

typedef struct complex cplx;

static inline cplx ComplexAdd(cplx x, cplx y) {
	cplx result;
	result.r = x.r + y.r;
	result.i = x.i + y.i;
	return result;
}

static inline cplx ComplexPower(cplx a) {
	cplx result;
	result.r = a.r * a.r - a.i * a.i;
	result.i = a.r * a.i + a.r * a.i;
	return result;
}

const int iterations = 100;

static inline int Mandeltest(float x, float y) {
	cplx c;
	c.r = x;
	c.i = y;

	cplx z;
	z.r = 0.0f;
	z.i = 0.0f;

	for (int i = 0; i < iterations; i++) {
		z = ComplexPower(z);
		z = ComplexAdd(z,c);
		//if (z.r > 2.0f || z.r < -2.0f || z.i > 2.0f || z.i < -2.0f) {
		//	return 0;
		//}
		// Calculate distance
		if (z.r*z.r + z.i*z.i > 2*2) {
			return 0;
		}
	}
	return 1;
}

int ComplexPrint(cplx a) {
	printf("(%f, %fi)", a.r, a.i);
	return 0;
}

const float unit = 0.2;

int main() {
	clock_t start_time = clock();
	//for (int i = 0; i < 4; i++) {
		for (float y = 2.0f; y > -2.0; y -= unit) {
			for (float x = -2.0f; x < 2.0; x += unit) {
				if (Mandeltest(x,y)) {
					printf("*");
				} else {
					printf(".");
				}
			}
			printf("\n");
		}
	//}
	double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
	printf("Done in %f seconds\n", elapsed_time);
	return 0;
}
