#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>


#define IS_PRIME  0b00
#define NOT_PRIME 0b11
#define UNKNOWN   0b10

#define INDEX(num)  (((num)-1) / 4)
#define OFFSET(num) ((((num) + 3) % 4) * 2)

struct prime_list_t {
	size_t max_size;
	size_t max_num;
	char* bit_list;
};

int _isnotprime(const char* bit_list, size_t num) {
	return (bit_list[INDEX(num)] & (0b11 << OFFSET(num)))
	    >> OFFSET(num);
}

void _setisprime(char* bit_list, size_t num) {
	// 0b00 表示为质数
	bit_list[INDEX(num)] &= ~(0b11 << OFFSET(num));
}

void _setnotprime(char* bit_list, size_t num) {
	// 0b11 表示非质数
	bit_list[INDEX(num)] |= (0b11 << OFFSET(num));
}

int prime_list_init(struct prime_list_t* prime_list,
                    size_t max_num) {
	prime_list->max_num = max_num;
	prime_list->max_size = (max_num + 3) / 4;
	prime_list->bit_list =
	    (char*)malloc(prime_list->max_size * sizeof(char));
	// 0b10 表示未判断
	memset(prime_list->bit_list, 0b10101010,
	       prime_list->max_size);

	_setisprime(prime_list->bit_list, 2);
	for(size_t i = 3; i <= max_num; i++) {
		if(_isnotprime(prime_list->bit_list, i) != UNKNOWN)
			continue;

		int isprime = 1;
		for(size_t j = 2; j <= (size_t)sqrt((double)i) + 1;
		    j++) {
			if(_isnotprime(prime_list->bit_list, j))
				continue;
			if(!(i % j)) {
				isprime = 0;
				break;
			}
		}

		if(isprime) {
			_setisprime(prime_list->bit_list, i);
			continue;
		}

		for(size_t k = 1; k * i < prime_list->max_num;
		    k++) {
			_setnotprime(prime_list->bit_list, k * i);
		}
	}

	return 0;
}

void prime_list_free(struct prime_list_t* prime_list) {
	prime_list->max_size = prime_list->max_num = 0;
	free(prime_list->bit_list);
}

size_t prime_list_print(struct prime_list_t* prime_list,
                        int cnt) {
	if(cnt == -1)
		cnt = INT_MAX;

	size_t _cnt = 0;
	size_t num = 1;
	while(_cnt < cnt) {
		while(1) {
			if(!_isnotprime(prime_list->bit_list, ++num))
				break;
		}
		if(num > prime_list->max_num)
			break;
		printf(",%lu" + !_cnt, num);
		_cnt++;
	}
	fputc('\n', stdout);

	return _cnt;
}


int main(int argc, char* argv[]) {
	size_t max = atoll(argv[1]);

	struct prime_list_t prime_list;
	prime_list_init(&prime_list, max);

	printf("\ncount: %lu\n",
	       prime_list_print(&prime_list, -1));

	prime_list_free(&prime_list);
	return 0;
}
