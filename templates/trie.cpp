struct node {
  node* ch[2];
  int cnt;

  node() {
    cnt = 0;
    ch[0] = nullptr;
    ch[1] = nullptr;
  }

  node* next(int b) {
    if (!ch[b]) ch[b] = new node;
    return ch[b];
  }
};

void ins(int x) {
  node* targ = root;
  for (int i = 29; i >= 0; --i) {
    int v = !!(x & (1 << i));
    targ = targ->next(v);
    ++targ->cnt;
  }
}

void del(int x) {
  node* targ = root;
  for (int i = 29; i >= 0; --i) {
    int v = !!(x & (1 << i));
    targ = targ->next(v);
    --targ->cnt;
  }
}

int best(int x) {
  node* targ = root;
  int ans = 0;
  for (int i = 29; i >= 0; --i) {
    int v = !!(x & (1 << i));
    if (targ->next(v)->cnt > 0) {
      targ = targ->next(v);
    } else {
      targ = targ->next(!v);
      ans += (1 << i);
    }
  }

  return ans;
}