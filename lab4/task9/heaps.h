#pragma once

#ifndef FUNDAMENTAL_ALGORITHMS_HEAPS_H
#define FUNDAMENTAL_ALGORITHMS_HEAPS_H

#include "ticket.h"

#include "heaps/binary/binary.h"
#include "heaps/skew/skew.h"
#include "heaps/leftist/leftist.h"
#include "heaps/binomial/binomial.h"
#include "heaps/fibonacci/fibonacci.h"
#include "heaps/treap/treap.h"

int merge_leftist_heap_errcode(LeftistHeap *a, LeftistHeap *b, LeftistHeap *result);
int merge_skew_heap_errcode(SkewHeap *a, SkewHeap *b, SkewHeap *result);
int merge_binomial_heap_errcode(BinomialHeap *a, BinomialHeap *b, BinomialHeap *result);
int merge_fibonacci_heap_errcode(FibonacciHeap *a, FibonacciHeap *b, FibonacciHeap *result);
int merge_treap_errcode(Treap *a, Treap *b, Treap *result);

#endif //FUNDAMENTAL_ALGORITHMS_HEAPS_H
