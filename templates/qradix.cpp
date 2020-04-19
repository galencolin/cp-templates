/* overtakes stl sort around 8000000 elements */
struct radix {
	vector<vector<int> > r;

	void sort(int* start, int* end) {
		r = vector<vector<int> >(100000);

		for (int* pt = start; pt != end; pt++) {
			r[(*pt) % 100000].push_back(*pt);
		}

		int* pt = start;
		for (int i = 0; i < 100000; i++) {
			for (int j = 0; j < r[i].size(); j++) {
				*(pt++) = r[i][j];
			}
		}

		r = vector<vector<int> >(100000);

		for (int* pt = start; pt != end; pt++) {
			r[(*pt) / 100000].push_back(*pt);
		}

		pt = start;
		for (int i = 0; i < 100000; i++) {
			for (int j = 0; j < r[i].size(); j++) {
				*(pt++) = r[i][j];
			}
		}
	}
};