[Assert triggers on deflate #39](https://github.com/vurtun/lib/issues/39)

Deflation of [input.txt](input.txt) fails with:

```
bug: sdefl.h:546: sdefl_seq: Assertion `s->seq_cnt + 2 < SDEFL_SEQ_SIZ' failed.
```
