#include "pch.h"
#include "operations.h"

#include<time.h>
#include<math.h>
#include<stdlib.h>
#include<stdio.h>

void ecc_encryption(int * arr, int Mx, int My, int Gx, int Gy, int Pu_x, int Pu_y,
	int a, int b, int p, int r);
void ecc_decryption(int * point_pair, int Pr, int a, int b, int p);


int main()
{
	int p = 29;
	int a = 4;
	int b = 20;
	int Gx = 13;
	int Gy = 23;
	int Pr = 25;
	int Pu_x, Pu_y;
	int arr[4];

	int r = get_Gs_rank(Gx, Gy, p, a);

	printf("G's rank is: %d\n", r);

	multiplier(arr, Gx, Gy, Pr, a, p);
	Pu_x = arr[0];
	Pu_y = arr[1];

	printf("Public key: (%d, %d)\n", Pu_x, Pu_y);

	int Mx = 3;
	int My = 28;

	ecc_encryption(arr, Mx, My, Gx, Gy, Pu_x, Pu_y, a, b, p, r);

	printf("C1: (%d, %d), C2: (%d, %d)\n", arr[0], arr[1], arr[2], arr[3]); 

	ecc_decryption(arr, Pr, a, b, p);

	printf("M: (%d, %d)\n", arr[0], arr[1]);

	return 0;
}


void ecc_encryption(int * arr, int Mx, int My, int Gx, int Gy, int Pu_x, int Pu_y,
	int a, int b, int p, int r) {

	srand(time(NULL));
	int random = rand() % r;

	printf("Random number is: %d\n", random);

	int C1_x, C1_y, C2_x, C2_y;
	int temp[2];

	multiplier(temp, Gx, Gy, random, a, p);
	C1_x = temp[0];
	C1_y = temp[1];

	multiplier(temp, Pu_x, Pu_y, random, a, p);

	get_sum(temp, Mx, My, temp[0], temp[1], a, p);
	C2_x = temp[0];
	C2_y = temp[1];

	arr[0] = C1_x;
	arr[1] = C1_y;
	arr[2] = C2_x;
	arr[3] = C2_y;
}

void ecc_decryption(int * point_pair, int Pr, int a, int b, int p) {

	int C1_x, C1_y, C2_x, C2_y, Minus_x, Minus_y;
	C1_x = point_pair[0];
	C1_y = point_pair[1];
	C2_x = point_pair[2];
	C2_y = point_pair[3];

	int temp[2];

	multiplier(temp, C1_x, C1_y, Pr, a, p);
	Minus_x = temp[0];
	Minus_y = p - temp[1];

	get_sum(temp, C2_x, C2_y, Minus_x, Minus_y, a, p);

	point_pair[0] = temp[0];
	point_pair[1] = temp[1];
	point_pair[2] = 0;
	point_pair[3] = 0;
}
