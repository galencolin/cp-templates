namespace speedy_io {
	int read_nonneg() {
		int c;
		while ((c = getchar_unlocked()) < '0' || c > '9');
		int v = c - '0';
		while ((c = getchar_unlocked()) >= '0' && c <= '9') {
			v = (v << 3) + (v << 1) + (c - '0');
		}
		return v;
	}
	
	const int max_ll_size = 20;
	void put_nonneg(ll n) { 
		int i = max_ll_size; 
		char output_buffer[max_ll_size]; 
		do { 
			output_buffer[--i] = (n % 10) + '0'; 
			n /= 10; 
		} while (n); 
		do { 
			putchar_unlocked(output_buffer[i]); 
		} while (++i < max_ll_size); 
	}
}

using namespace speedy_io;