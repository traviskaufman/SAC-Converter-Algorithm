/**
 * @file SAC_DAC_Algorithm.c
 *
 * Implementation of an algorithm used by Succesive Approximation Analog-to-
 * Digital converters. Current Implementation accepts integer values only.
 *
 * @author: Travis Kaufman
 *
 * @version: 1.0.0
 */

// TODO: Make more bulletproof

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int approximate(const int vRef, const int wordLength);
int main(int argc, const char* argv[]) {
	const int vRef = (argc >= 2) ? atoi(argv[1]) : 10;
	const int wL = (argc == 3) ? atoi(argv[2]) : 4;
	printf("Attempting to approximate a vRef of %i with a wordLength of %i\n", vRef, wL);
	int result = approximate(vRef, wL);
	printf("Result is %i\n", result);
 	return 0;
} // end main()

int approximate(const int vRef, const int wordLength) {
	if (wordLength >= 32) {
		printf("Too large of a word length\n");
		return -1;
	}
	if (vRef >= pow(2, wordLength) - 1) {
		printf("vRef too large\n");
		return -1;
	}

	int appr = 0, msb = wordLength - 1;
	int count = 0;
	while (appr != wordLength) {
		// make sure the lsb has a value of 1
		/*if (appr == 0 || appr % 2 == 0)
			appr++;*/
		// shift it to the next-most significant bit
		appr += pow(2,msb);
		printf("appr = %i\n", appr);
		if (appr < vRef)
			msb--;
		else if (appr > vRef) {
			appr -= pow(2,msb);
			msb--;
		} 
		else // they are equal
			break;
		count++;
	} // end while
	printf("Performed %i approximations\n", count);
	return appr;
} // end approximate();

unsigned short int SigDig (Base b, RepNum num) {
	double n;
	if (num == 0)
		n = 1;
	else {
		n = log10((double)(abs(num)+1)) / log10((double)(b));
		if (n > n-(int)n && (n-(int)n) != 0) // If n has any remainder whatsoever,
			++n; // ...round up
	}
	return n;
} // end SigDig()
