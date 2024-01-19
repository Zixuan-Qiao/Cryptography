#include "pch.h"
#include "operations.h"

#include<stdlib.h>
#include<stdio.h>

void extended_euclidean(int * arr, int p, int b) {
	int r0, r1, q;
	int s0, s1, t0, t1;
	int temp;

	r0 = p;
	r1 = b;
	s0 = 1;
	s1 = 0;
	t0 = 0;
	t1 = 1;

	while (r1 != 0) {
		q = r0 / r1;
		temp = r0 - q * r1;
		r0 = r1;
		r1 = temp;

		temp = s0 - q * s1;
		s0 = s1;
		s1 = temp;

		temp = t0 - q * t1;
		t0 = t1;
		t1 = temp;
	}

	arr[0] = s0;
	arr[1] = t0;

	//return arr;

}

int get_inverse(int p, int b) {
	int t;
	int arr[2];

	extended_euclidean(arr, p, b);
	t = arr[1];
	if (t < 0) {
		while (t < 0) {
			t = t + p;
		}
	}
	return t;
}

void get_sum(int * arr, int Px, int Py, int Qx, int Qy, int a, int p) {
	int k;
	int i_d;
	int numerator;
	int denominator;
	int sum[2];

	if (Px == Qx && Py == Qy) {
		numerator = 3 * Px * Px + a;
		denominator = 2 * Py;
		i_d = get_inverse(p, denominator);
		k = (numerator * i_d) % p;
	}
	else {
		numerator = Qy - Py;
		while (numerator < 0) {
			numerator = numerator + p;
		}
		denominator = Qx - Px;
		while (denominator < 0) {
			denominator = denominator + p;
		}
		i_d = get_inverse(p, denominator);
		k = (numerator * i_d) % p;
	}

	sum[0] = (k * k - Px - Qx);
	if (sum[0] < 0) {
		while (sum[0] < 0) {
			sum[0] = sum[0] + p;
		}
	}
	else {
		sum[0] = sum[0] % p;
	}

	sum[1] = (k * (Px - sum[0]) - Py);
	if (sum[1] < 0) {
		while (sum[1] < 0) {
			sum[1] = sum[1] + p;
		}
	}
	else {
		sum[1] = sum[1] % p;
	}

	arr[0] = sum[0];
	arr[1] = sum[1];
}

int get_Gs_rank(int Gx, int Gy, int p, int a) {
	int n = 1;
	int sum[2];
	int minus_Gx = Gx;
	int minus_Gy = p - Gy;

	sum[0] = Gx;
	sum[1] = Gy;

	while (true) {
		n++;
		get_sum(sum, Gx, Gy, sum[0], sum[1], a, p);
		if (sum[0] == minus_Gx && sum[1] == minus_Gy) {
			n = n + 1;
			return n;
		}
		else if (n >= 100) {
			printf("G's rank is infinite\n");
			return 0;
		}
	}
}

void multiplier(int *arr, int Px, int Py, int m, int a, int p) {

	int sum[2];
	int counter = 1;

	sum[0] = Px;
	sum[1] = Py;

	while (counter < m) {
		get_sum(sum, Px, Py, sum[0], sum[1], a, p);
		counter++;
	}

	arr[0] = sum[0];
	arr[1] = sum[1];
}
