#include <stddef.h>
#include <stdlib.h>
#include <math.h>


struct prime_list_t {
	size_t max_size;
	size_t max_num;
	char* bit_list;
};

int _isprime(const char* bit_list, size_t num) {
	return !!(bit_list[(num - 1) / 8]
	          & (1 << ((num + 7) % 8)));
}

void _setprime(char* bit_list, size_t num) {
	bit_list[(num - 1) / 8] |= (1 << ((num + 7) % 8));
}

int prime_list_init(struct prime_list_t* prime_list,
                    size_t max_num) {
	prime_list->max_num = max_num;
	prime_list->max_size = (max_num + 7) / 8;
	prime_list->bit_list =
	    (char*)calloc(prime_list->max_size, sizeof(char));

	_setprime(prime_list->bit_list, 2);
	for(size_t i = 3; i <= max_num; i++) {
		int isprime = 1;
		for(size_t j = 2; j <= (size_t)sqrt((double)i) + 1;
		    j++) {
			if(!_isprime(prime_list->bit_list, j))
				continue;
			if(!(i % j)) {
				isprime = 0;
				break;
			}
		}
		if(isprime)
			_setprime(prime_list->bit_list, i);
	}

	return 0;
}

void prime_list_free(struct prime_list_t* prime_list) {
	prime_list->max_size = prime_list->max_num = 0;
	free(prime_list->bit_list);
}
