#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <vector>
#include "utils.h"
#include "sort.h"

Sort::Sort() {
  // std::cout << __FUNCTION__ << " is called." << std::endl;
}

Sort::~Sort() {
  // std::cout << __FUNCTION__ << " is called." << std::endl << std::endl;
}

void Sort::dump(const int *buf, size_t count) {
  for(size_t i = 0; i < count; i++) {
    std::cout << buf[i] << " " ;
  }

  std::cout << std::endl;
}

// BubbleSort
BubbleSort::BubbleSort(const int* buf, size_t count) : m_name(__FUNCTION__) {
  // std::cout << __FUNCTION__ << " is called." << std::endl;
  m_buf.reset(new int[count]);
  memcpy(m_buf.get(), buf, count * sizeof(int));
  m_count = count;
}

BubbleSort::~BubbleSort() {
  // std::cout << __FUNCTION__ << " is called." << std::endl;
  // dump(m_buf.get(), m_count);
}

void BubbleSort::run() {
  int *buf = m_buf.get();
  std::cout << m_name << ": ";

  ScopedTiming st(__FUNCTION__);
  bool flag = false;
  for (size_t i = 0; i < m_count - 1; i++) {
    for(size_t j = 0; j < m_count - i - 1; j++) {
      if (buf[j] > buf[j + 1]) {
        std::swap(buf[j], buf[j + 1]);
        flag = true;
      }
    }

    if (!flag) {
      break;
    }
  }
}

// SelectionSort
SelectionSort::SelectionSort(const int* buf, size_t count) : m_name(__FUNCTION__) {
  // std::cout << __FUNCTION__ << " is called." << std::endl;
  m_buf.reset(new int[count]);
  memcpy(m_buf.get(), buf, count * sizeof(int));
  m_count = count;
}

SelectionSort::~SelectionSort() {
  // std::cout << __FUNCTION__ << " is called." << std::endl;
  // dump(m_buf.get(), m_count);
}

void SelectionSort::run() {
  int *buf = m_buf.get();
  std::cout << m_name << ": ";

  ScopedTiming st(__FUNCTION__);
  size_t min = 0;
  for (size_t i = 0; i < m_count - 1; i++) {
    min = i;
    for(size_t j = i + 1; j < m_count; j++) {
      if(buf[j] < buf[min]) {
        min = j;
      }
    }

    if (i != min) {
      std::swap(buf[i], buf[min]);
    }
  }
}

// InsertionSort
InsertionSort::InsertionSort(const int* buf, size_t count) : m_name(__FUNCTION__) {
  // std::cout << __FUNCTION__ << " is called." << std::endl;
  m_buf.reset(new int[count]);
  memcpy(m_buf.get(), buf, count * sizeof(int));
  m_count = count;
}

InsertionSort::~InsertionSort() {
  // std::cout << __FUNCTION__ << " is called." << std::endl;
  // dump(m_buf.get(), m_count);
}

void InsertionSort::run() {
  int *buf = m_buf.get();
  std::cout << m_name << ": ";

  ScopedTiming st(__FUNCTION__);
  int j = 0;
  for (int i = 0; i < m_count - 1; i++) {
    int key = buf[i + 1];
    for (j = i; j >= 0; j--) {
      if (key < buf[j]) {
        buf[j + 1] = buf[j];
      } else {
        break;
      }
    }
    buf[j + 1] = key;
  }
}

// MergeSort
MergeSort::MergeSort(const int* buf, size_t count) : m_name(__FUNCTION__) {
  // std::cout << __FUNCTION__ << " is called." << std::endl;
  m_buf.reset(new int[count]);
  memcpy(m_buf.get(), buf, count * sizeof(int));
  m_count = count;
}

MergeSort::~MergeSort() {
  // std::cout << __FUNCTION__ << " is called." << std::endl;
  // dump(m_buf.get(), m_count);
}

void MergeSort::run() {
  std::cout << m_name << ": ";
  ScopedTiming st(__FUNCTION__);
  recur(m_buf.get(), 0, m_count - 1);
}

void MergeSort::recur(int *buf, size_t l, size_t r) {
  //std::cout << "l = " << l << ", r = " << r << std::endl;
  if (l < r) {
    size_t m = l + (r - l) / 2;
    recur(buf, l, m);
    recur(buf, m + 1, r);
    merge(buf, l, m, r);
  }
}

void MergeSort::merge(int *buf, size_t l, size_t m, size_t r) {
  int len1 = m - l + 1;
  int len2 = r - m;
  int buf1[len1], *p1 = buf1;
  int buf2[len2], *p2 = buf2;

  int i = 0, j = 0, k = 0;
  while (i < len1) {
    buf1[i] = buf[l + i];
    i++;
  }

  while (j < len2) {
    buf2[j] = buf[m + 1 + j];
    j++;
  }

  i = j = k = 0;
  while ((i < len1) && (j < len2)) {
    if (buf1[i] < buf2[j]) {
      buf[l + k++] = buf1[i++];
    } else {
      buf[l + k++] = buf2[j++];
    }
  }

  while (i < len1) {
    buf[l + k++] = buf1[i++];
  }

  while (j < len2) {
    buf[l + k++] = buf2[j++];
  }
}

// QuickSort
QuickSort::QuickSort(const int* buf, size_t count) : m_name(__FUNCTION__) {
  // std::cout << __FUNCTION__ << " is called." << std::endl;
  m_buf.reset(new int[count]);
  memcpy(m_buf.get(), buf, count * sizeof(int));
  m_count = count;
}

QuickSort::~QuickSort() {
  // std::cout << __FUNCTION__ << " is called." << std::endl;
  // dump(m_buf.get(), m_count);
}

void QuickSort::run() {
  std::cout << m_name << ": ";
  ScopedTiming st(__FUNCTION__);
  recur(m_buf.get(), 0, m_count - 1);
}

void QuickSort::recur(int *buf, int lo, int hi) {
  if (lo >= hi) {
    return;
  }

  int pivot = partition(buf, lo, hi);
  recur(buf, lo, pivot - 1);
  recur(buf, pivot + 1, hi);
}

#if 1
// first element as pivot
int QuickSort::partition(int *buf, int lo, int hi) {
  int i = lo;
  int j = hi + 1;
  int pivot = buf[lo];

  while(true) {
    while(++i < hi && buf[i] < pivot);
    while(--j > lo && buf[j] > pivot);

    if (i >= j) {
        break;
    }
    
    std::swap(buf[i], buf[j]);
  }

  std::swap(buf[lo], buf[j]);

  return j;
}

#else

// last element as pivot
int QuickSort::partition(int *buf, int l, int r) {
  int i = l - 1;
  int &key = buf[r];

  //std::cout << " l = " << l << ", r = " << r << " key=" << key<<std::endl;
  for(int j = l; j < r; j++) {
    if (buf[j] <= key) {
      std::swap(buf[j], buf[++i]);
    }
  }

  std::swap(buf[i + 1], key);
  //dump();
  //std::cout << "this pass: pivot = " << i+1<<std::endl;
  return i + 1;
}
#endif

// QSort
QSort::QSort(const int* buf, size_t count) : m_name(__FUNCTION__) {
  m_buf.reset(new int[count]);
  memcpy(m_buf.get(), buf, count * sizeof(int));
  m_count = count;
}

QSort::~QSort() {
  // std::cout << __FUNCTION__ << " is called." << std::endl;
  // dump(m_buf.get(), m_count);
}

void QSort::run() {
  std::cout << m_name << ": ";
  ScopedTiming st(__FUNCTION__);
  qsort(m_buf.get(), m_count, sizeof(int), compare);
}

int QSort::compare(const void * a, const void * b) {
  return *static_cast<const int *>(a) < *static_cast<const int *>(b);
}

// StdSort
StdSort::StdSort(const int* buf, size_t count) : m_name(__FUNCTION__) {
  m_buf.reset(new int[count]);
  memcpy(m_buf.get(), buf, count * sizeof(int));
  m_count = count;
}

StdSort::~StdSort() {
  // std::cout << __FUNCTION__ << " is called." << std::endl;
  // dump(m_buf.get(), m_count);
}

void StdSort::run() {
  std::cout << m_name << ": ";
  ScopedTiming st(__FUNCTION__);
  std::sort(m_buf.get(), m_buf.get() + m_count);
}

// HeapSort
HeapSort::HeapSort(const int* buf, size_t count) : m_name(__FUNCTION__) {
  // std::cout << __FUNCTION__ << " is called." << std::endl;
  m_buf.reset(new int[count]);
  memcpy(m_buf.get(), buf, count * sizeof(int));
  m_count = count;
}

HeapSort::~HeapSort() {
  // std::cout << __FUNCTION__ << " is called." << std::endl;
  // dump(m_buf.get(), m_count);
}

void HeapSort::run() {
  std::cout << m_name << ": ";
  ScopedTiming st(__FUNCTION__);
  size_t len = m_count;

  // build max heap
  for (int i = len / 2 - 1; i >= 0; i--) {
    max_heapify(i);
  }

  // heap sort
  int *ptr = m_buf.get();
  for(size_t i = len - 1; i > 0; i--) {
    std::swap(ptr[0], ptr[i]);
    m_count--;
    max_heapify(0);
  }

  m_count = len;
}

#if 0
// recursion version
void HeapSort::max_heapify(size_t i) {
  int *ptr = m_buf.get();

  size_t l = 2 * i + 1;
  size_t r = 2 * i + 2;
  size_t max = i;

  if (l < m_count && ptr[l] > ptr[max]) {
    max = l;
  }

  if (r < m_count && ptr[r] > ptr[max]) {
    max = r;
  }

  if (i != max) {
    std::swap(ptr[i], ptr[max]);
    max_heapify(max);
  }
}
#else
// iteration version
void HeapSort::max_heapify(size_t i) {
  int *ptr = m_buf.get();

  size_t max = i;
  while (true) {
    size_t l = 2 * i + 1;
    size_t r = 2 * i + 2;

    if (l < m_count && ptr[l] > ptr[max]) {
      max = l;
    }

    if (r < m_count && ptr[r] > ptr[max]) {
      max = r;
    }

    if (i != max) {
      std::swap(ptr[i], ptr[max]);
      i = max;
    } else {
      break;
    }
  }
}
#endif
