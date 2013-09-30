Memo * memo_create ();
void   memo_destroy (Memo * memo);
int    memo_get (Memo * memo, int ii);
void   memo_set (Memo * memo, int ii, int fi);


int fibMemo (int ii)
{
  static Memo * memo = NULL;
  int fi;
  if (NULL == memo) {
    memo = memo_create ();
  }
  fi = memo_get (memo, ii);
  if (0 < fi) {
    return fi;
  }
  fi = fibMemo (ii-1) + fibMemo (ii-2);
  memo_set (memo, ii, fi);
  return fi;
}
