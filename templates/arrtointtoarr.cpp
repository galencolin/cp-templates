/* {1, 2, 3, 4} becomes 1234 */
inline int arrtoint(int* arr, int size) {
  int num = 0;

  for (int i = 0; i < size; i++) {
    num *= 10;
    num += *(arr++);
  }

  return num;
}

/* 1234 becomes {1, 2, 3, 4} */
inline int* inttoarr(int v, int dig) {
  int* arr = (int*)malloc(sizeof(int) * dig);

  for (int i = 0; i < dig; i++) {
    *(arr++) = v % 10;
    v /= 10;
  }

  reverse(arr - dig, arr);

  return arr - dig;
}