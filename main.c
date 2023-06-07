
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <assert.h>

#define SDEFL_IMPLEMENTATION
#include "sdefl.h"

#define SINFL_IMPLEMENTATION
#include "sinfl.h"

//const char* input = "main.c";
const char* input = "input.txt";

int main() {
	struct stat sb;
	int rc = stat(input, &sb);
	assert(rc == 0);

	int sizeInput = sb.st_size;
	int bound = sdefl_bound(sizeInput);

	unsigned char* bufferInput = calloc(sizeInput,1);
	assert(bufferInput);

	unsigned char* bufferDeflate = calloc(bound,1);
	assert(bufferDeflate);

	FILE *file = fopen(input, "r");
	assert(file);

	int n = fread(bufferInput, 1, sizeInput, file);
	assert(n == sizeInput);

	fclose(file);

	struct sdefl sdefl;
	memset(&sdefl, 0, sizeof(sdefl));

	int sizeDeflated = sdeflate(&sdefl, bufferDeflate, bufferInput, sizeInput, SDEFL_LVL_DEF);

	unsigned char* bufferInflate = calloc(bound,1);
	assert(bufferInflate);

	int sizeInflated = sinflate(bufferInflate, bound, bufferDeflate, sizeDeflated);

	assert(sizeInflated == sizeInput);
	assert(memcmp(bufferInput, bufferInflate, sizeInflated) == 0);

	printf("input %d bound %d deflated %d inflated %d\n", sizeInput, bound, sizeDeflated, sizeInflated);

	return EXIT_SUCCESS;
}
