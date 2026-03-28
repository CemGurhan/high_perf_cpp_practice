template <class T, int N> 
class BufferWithCollapsingExample {
  std::array<T, N> buf_;

  // Here, we might experience reference collapsing. item being auto&&
  // forces this method to be a template function. std::forward
  // allows us to preserve whatever our reference collapsed to.
  void do_push(auto&& item, int i) {
    buf_[i] = std::forward<decltype(item)>(item);
  }

public:
// Due to reference collapsing, const T& here collapses to an lvalue
// and is copied in.
  void push(const T& item, int i) { do_push(item, i); }

  // T&& remains an rvalue and is moved in. 
  void push(T&& item, int i) { do_push(std::move(item), i); }
};
