#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>


#define INDEX(num)  (((num)-1) / 8)
#define OFFSET(num) (((num) + 7) % 8)

struct prime_list_t {
	size_t max_size;
	size_t max_num;
	char* bit_list;
};

static int _isnotprime(const char* bit_list, size_t num) {
	return bit_list[INDEX(num)] & (1 << OFFSET(num));
}

static void _setnotprime(char* bit_list, size_t num) {
	bit_list[INDEX(num)] |= 1 << OFFSET(num);
}

int prime_list_init(struct prime_list_t* prime_list,
                    size_t max_num) {
	prime_list->max_num = max_num;
	prime_list->max_size = (max_num + 7) / 8;
	prime_list->bit_list =
	    (char*)calloc(prime_list->max_size, sizeof(char));

	for(size_t i = 2; i <= max_num; i++) {
		for(size_t j = 2; j * i <= prime_list->max_num;
		    j++) {
			_setnotprime(prime_list->bit_list, j * i);
		}
	}

	return 0;
}

void prime_list_free(struct prime_list_t* prime_list) {
	prime_list->max_size = prime_list->max_num = 0;
	free(prime_list->bit_list);
}

size_t prime_list_print(struct prime_list_t* prime_list,
                        size_t cnt) {
	if(cnt == 0)
		cnt = SIZE_MAX;

	size_t _cnt = 0;
	size_t num = 1;
	while(_cnt < cnt) {
		while(_isnotprime(prime_list->bit_list, ++num));
		if(num > prime_list->max_num)
			break;
		printf(&",%lu"[!_cnt], num);
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
	       prime_list_print(&prime_list, 0));

	prime_list_free(&prime_list);
	return 0;
}
