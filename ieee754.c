#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>

uint8_t *binaire(uint32_t n) {
	uint8_t *form = (uint8_t*) calloc(32, 1);
	int i=0, temp=n;
	while (temp) {
		temp>>=1;
		i++;
	}
	while (n) {
		form[i-1]='0'+(n & 1);
		n>>=1;
		i--;
	}
	return form;
}

char *rep_bin(uint32_t n, int d) {
	uint8_t *form = (uint8_t*) calloc(32, 1);
	uint8_t *b = binaire(n);
	if (d <= strlen(b)) return b;
	memset(form, '0', d-strlen(b));
	memcpy(form+d-strlen(b), b, strlen(b));
	return form;
}

int main(int argc, char *argv[]) {
	if (argc != 2) return 1;
	float f = atof(argv[1]);
	uint8_t *p = (uint8_t*) &f;
	printf("le bit de signe : %d\n", (p[3] & 128) ? 1:0);
	printf("exposant : %s\n", rep_bin((p[3]<<1) | ((p[2] & 128)>>7), 8));
	printf("mantisse : %s\n", rep_bin(*((uint32_t*)&f) & (-1 + (1<<23)), 23));
	printf("IEEE754 : %d%s%s\n", (p[3] & 128) ? 1:0, rep_bin((p[3]<<1) | ((p[2] & 128)>>7), 8), rep_bin(*((uint32_t*)&f) & (-1 + (1<<23)), 23));
	return 0;
}