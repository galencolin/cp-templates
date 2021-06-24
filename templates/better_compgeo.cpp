// broken, check with codesprint

const lld eps = 1e-7;

inline bool close(lld a, lld b) {
	return abs(a - b) < eps;
}

struct point {
	lld x, y;
	static constexpr lld sent = 5281925819256.5219858219;
};
typedef struct point point;

ostream& operator << (ostream& cout, const point& p) {
	return cout << "(" << p.x << ", " << p.y << ")";
}

struct line {
	lld a, b, c; // ax + by = c
	
	line(point d, point e) {
		if (close(d.x, e.x)) {
			a = 1;
			b = 0;
			c = e.x;
		} else {
			lld m = (e.y - d.y) / (e.x - d.x);
			
			a = -m;
			b = 1;
			c = e.y - m * e.x;
		}
	}
	
	point isect(line d, line e) {
		point p;
		assert(!(close(d.a, 0) && close(d.b, 0)));
		
		// check if d.a / e.a == d.b / e.b -> d.a * e.b == d.b * e.a
		if (close(d.a * e.b, d.b * e.a)) return point{point::sent, point::sent}; // parallel
		
		if (close(d.a, 0)) {
			p.x = (e.c - (e.b / d.b) * d.c) / (e.a - (e.b / d.b) * d.a);
			p.y = (d.c - d.a * p.x) / d.b;
		} else {
			p.y = (e.c - (e.a / d.a) * d.c) / (e.b - (e.a / d.a) * d.b);
			p.x = (d.c - d.b * p.y) / d.a;
		}
		return p;
	}
	
	lld eval(lld x) {
		if (close(b, 0)) return c; // line is x = c, TODO define some protocol
		return (c - a * x) / b;
	}
	
	lld dist(point a, point b) {
		return sqrtl((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}
	
	// careful with epsilon here
	bool between(point a, point c, point b) { // {a, c, b}; is c between a and b
		return close(dist(a, c) + dist(c, b), dist(a, b));
	}
};
