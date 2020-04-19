/* generic point */
struct point {
  double x, y;
};

/* generic line */
/* for a segment, store the rectangle contained between the two points 
	(as in, leftx, rightx, bottomy, topy)
	then use that for comparisons
*/
struct line {
  double m, b;
  double val(double x) {
    return m * x + b;
  }
};

typedef struct line line;

/* get the line between two points */
line between(point pa, point pb) {
  double m = (pb.y - pa.y) / (pb.x - pa.x);
  double b = (pa.y - m * pa.x);
  line s = {m, b};
  return s;
}

/* generic distance */
double dist(point p1, point p2) {
  return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

/* comparison */
const int delta = 1e-15;
bool within(double d1, double d2) {
  return (d1 > d2 - delta) && (d1 < d2 + delta);
}

/* is a point on a line */
bool on(line s, point p) {
  return within(p.y, s.val(p.x));
}