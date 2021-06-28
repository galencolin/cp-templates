#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds; 

template <typename num_t>
using ordered_set = tree<num_t, null_type, less<num_t>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename num_t>
struct ordered_multiset {
	ordered_set<pair<num_t, int> > vals;
	set<pair<num_t, int> > best; /* start at -1 */
	
	/* helper, find the lowest value that represents the element */
	int findbest(num_t val) {
		return (*best.upper_bound(make_pair(val - 1, 0))).second;
	}
	
	/* is element in set */
	bool contains(num_t val) {
		return vals.find(make_pair(val, -1)) != vals.end();
	}
	
	void insert(num_t val) {
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
	
	void erase(num_t val) { /* erases one */
		if (!contains(val)) return; /* not in */
		num_t loc = findbest(val);
		
		/* remove the element and its best */
		best.erase(make_pair(val, loc));
		vals.erase(make_pair(val, loc));
		if (loc != -1) best.insert(make_pair(val, loc + 1)); /* more elements in set, update best */
	}
	
	/* unmodified functions */
	num_t find_by_order(int k) { return (*vals.find_by_order(k)).first; }
	int order_of_key(num_t k) { return vals.order_of_key(make_pair(k - 1, 0)); }
	auto begin() { return vals.begin(); }
	auto end() { return vals.end(); }
	auto rbegin() { return vals.rbegin(); }
	auto rend() { return vals.rend(); }
	int size() { return vals.size(); }
	void clear() { vals.clear(); best.clear(); }
	int count(num_t k) { return vals.order_of_key({k, 0}) - vals.order_of_key({k - 1, 0}); }
	auto lower_bound(num_t k) { return vals.lower_bound(make_pair(k - 1, 0)); }
	auto upper_bound(num_t k) { return vals.upper_bound(make_pair(k, 0)); }
};

int main()
{
	/*ordered_set<long long> os;
	os.insert(5);
	os.insert(23);
	os.insert(24);
	os.insert(25);
	os.insert(39);
	for(auto x:os)
	{
		cout<<x<<" ";
	}
	cout<<endl;*/

	ordered_multiset<long long> oms;
	// 5 23 23 24 24 24 25 39 39 100
	oms.insert(5);
	oms.insert(23);
	oms.insert(23);
	oms.insert(24);
	oms.insert(24);
	oms.insert(24);
	oms.insert(25);
	oms.insert(39);
	oms.insert(39);
	oms.insert(100);

	for(auto m:oms) // iterate over ordered multiset
	{
		cout<<m.first<<" ";
	}
	cout<<endl;
	cout<<oms.find_by_order(2)<<endl;
	cout<<oms.order_of_key(26)<<endl;
	cout<<oms.count(24)<<endl;
	cout<<oms.lower_bound(24)->first<<endl; // use in this way
	cout<<oms.upper_bound(23)->first<<endl;

	return 0;
}

/* ------------------------------------------------------------------------ COMMENTS ------------------------------------------------------------------------ */
/* supports things like k-th smallest element and find index of element in set */
/* all in pretty good O(lgn) */

/* example usage */
//ordered_set<int> os;

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
