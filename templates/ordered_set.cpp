#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 

template <typename num_t>
using ordered_set = tree<num_t, null_type, less<num_t>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename num_t>
struct ordered_multiset {
	ordered_set<pair<num_t, int> > vals;
	set<pair<int, int> > best; /* start at -1 */
	
	/* helper, find the lowest value that represents the element */
	int findbest (int val) {
		return (*best.upper_bound(make_pair(val - 1, 0))).second;
	}
	
	/* is element in set */
	bool contains(int val) {
		return vals.find(make_pair(val, -1)) != vals.end();
	}
	
	void insert(int val) {
		if (contains(val)) { /* already in, update lowest value and insert a new one */
			int loc = findbest(val);
			best.erase(make_pair(val, loc));
			best.insert(make_pair(val, loc - 1));
			vals.insert(make_pair(val, loc - 1));
		} else { /* make lowest value -1 and insert it */
			best.insert(make_pair(val, -1));
			vals.insert(make_pair(val, -1));
		}
	}
	
	void erase(int val) { /* erases one */
		if (!contains(val)) return; /* not in */
		int loc = findbest(val);
		
		/* remove the element and its best */
		best.erase(make_pair(val, loc));
		vals.erase(make_pair(val, loc));
		if (loc != -1) best.insert(make_pair(val, loc + 1)); /* more elements in set, update best */
	}
	
	/* unmodified functions */
	int find_by_order(int k) { return (*vals.find_by_order(k)).first; }
	int order_of_key(int k) { return vals.order_of_key(make_pair(k - 1, 0)); }
	pair<int, int>* begin() { return vals.begin(); }
	pair<int, int>* end() { return vals.end(); }
	pair<int, int>* rbegin() { return vals.rbegin(); }
	pair<int, int>* rend() { return vals.rend(); }
	int size() { return vals.size(); }
	void clear() { vals.clear(); best.clear(); }
	int count(int k) { return vals.order_of_key(k + 1) - vals.order_of_key(k); }
	pair<int, int>* lower_bound(int k) { return vals.lower_bound(make_pair(k - 1, 0)); }
	pair<int, int>* upper_bound(int k) { return vals.upper_bound(make_pair(k, 0)); }
};

/* ------------------------------------------------------------------------ COMMENTS ------------------------------------------------------------------------ */
/* supports things like k-th smallest element and find index of element in set */
/* all in pretty good O(lgn) */

/* example usage */
ordered_set<int> os;

/* extra functions (in addition to std::set operations):
	find_by_order(k) - returns a pointer to the k-th smallest element in the set (zero-indexed)
	order_of_key(k) - returns the number of elements in the set less than k (if k is in the set, this is the index of it)
*/

/* gfg: https://www.geeksforgeeks.org/ordered-set-gnu-c-pbds/ 
	examples:
	set = {1, 5, 6, 17, 88}
	find_by_order(1) - same as set[1] -> pointer to 5
	find_by_order(4) - same as set[4] -> pointer to 88
	order_of_key(6) -> 2
	order_of_key(88) -> 4
	order_of_key(400) -> 5
	order_of_key(0) -> 0
*/
