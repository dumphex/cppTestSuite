#ifndef SORT_H_
#define SORT_H_

#include <memory>

class Sort {
 public:
  Sort();
  virtual ~Sort();
  virtual void run() = 0;
  static void dump(const int *buf, size_t count);
};

// BubbleSort
class BubbleSort : public Sort {
 public:
  BubbleSort(const int* buf, size_t count);
  ~BubbleSort();

 private:
  void run();

  std::string m_name;
  size_t m_count;
  std::unique_ptr<int[]> m_buf;
};

// SelectionSort
class SelectionSort : public Sort {
 public:
  SelectionSort(const int* buf, size_t count);
  ~SelectionSort();

 private:
  void run();

  std::string m_name;
  size_t m_count;
  std::unique_ptr<int[]> m_buf;
};


// InsertionSort
class InsertionSort : public Sort {
 public:
  InsertionSort(const int* buf, size_t count);
  ~InsertionSort();

 private:
  void run();

  std::string m_name;
  size_t m_count;
  std::unique_ptr<int[]> m_buf;
};


// MergeSort
class MergeSort : public Sort {
 public:
  MergeSort(const int* buf, size_t count);
  ~MergeSort();

 private:
  void run();
  void recur(int *buf, size_t l, size_t r);
  void merge(int *buf, size_t l, size_t m, size_t r);

  std::string m_name;
  size_t m_count;
  std::unique_ptr<int[]> m_buf;
};

// QuickSort
class QuickSort : public Sort {
 public:
  QuickSort(const int* buf, size_t count);
  ~QuickSort();

 private:
  void run();
  void recur(int *buf, int l, int r);
  int partition(int *buf, int l, int r);

  std::string m_name;
  size_t m_count;
  std::unique_ptr<int[]> m_buf;
};

// QSort
class QSort : public Sort {
 public:
  QSort(const int* buf, size_t count);
  ~QSort();
  static int compare(const void* a, const void* b);

 private:
  void run();

  std::string m_name;
  size_t m_count;
  std::unique_ptr<int[]> m_buf;
};

// StdSort
class StdSort : public Sort {
 public:
  StdSort(const int* buf, size_t count);
  ~StdSort();

 private:
  void run();

  std::string m_name;
  size_t m_count;
  std::unique_ptr<int[]> m_buf;
};
// HeapSort
class HeapSort : public Sort {
 public:
  HeapSort(const int* buf, size_t count);
  ~HeapSort();

 private:
  void run();
  void max_heapify(size_t i);

  std::string m_name;
  size_t m_count;
  std::unique_ptr<int[]> m_buf;
};

#endif
