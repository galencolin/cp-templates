// tested on leetcode https://leetcode.com/problems/sliding-window-maximum... can it be trusted?

template<typename T>
struct sliding_max {
	vector<T> frontv, backv;
	vector<T> frontmx, backmx;
	
	void push(T v) {
		frontv.push_back(v);
		if (frontmx.size()) frontmx.push_back(max(frontmx.back(), v)); // combine
		else frontmx.push_back(v);
	}
	
	void pop() {
		if (!backv.size()) {
			while (frontv.size()) {
				backv.push_back(frontv.back());
				if (backmx.size()) backmx.push_back(max(backmx.back(), frontv.back())); // combine
				else backmx.push_back(frontv.back());
				frontv.pop_back();
			}
			frontmx.clear();
		}
		if (!backv.size()) return; // popping nothing, btw
		backv.pop_back();
		backmx.pop_back();
	}
	
	T query() {
		if (frontmx.size() && backmx.size()) return max(frontmx.back(), backmx.back()); // combine
		if (frontmx.size()) return frontmx.back();
		if (backmx.size()) return backmx.back();
		return T{-1e9, -1}; // sentinel
	}
};