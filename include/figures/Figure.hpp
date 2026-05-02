#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <concepts>
#include <utility>
#include "Renderer.hpp"

namespace figures {
template <class F>
concept FigureLike = requires(const F& f, Renderer& r) {
  requires std::copy_constructible<F>;
  { f.draw(r) } -> std::same_as<void>;
};

// Type erased class, value semantics, non-nullable
class Figure {
  struct VTable {
    void (*draw)(const void*, Renderer&);
    void* (*clone)(const void*);
    void* (*move)(void*);
    void (*destroy)(void*);
  };

  template <class F>
  static constexpr VTable V_TABLE = {
    [](const void* ptr, Renderer& r) { static_cast<const F*>(ptr)->draw(r); },
    [](const void* ptr) -> void* { return new F(*static_cast<const F*>(ptr)); },
    [](void* ptr) -> void* { return new F(std::move(*static_cast<F*>(ptr))); },
    [](void* ptr) { delete static_cast<F*>(ptr); }
  };

  void* v_ptr;
  const VTable* v_table;

public:
  template <class F>
    requires(!std::same_as<std::remove_cvref_t<F>, Figure>) && FigureLike<F>
  Figure(F&& figure_like) :
    v_ptr{new F(std::forward<F>(figure_like))},
    v_table{&V_TABLE<F>} {}

  template <class F, class... Args>
    requires(!std::same_as<std::remove_cvref_t<F>, Figure>) && FigureLike<F>
  explicit Figure(std::in_place_type_t<F>, Args&&... args) :
    v_ptr{new F(std::forward<Args>(args)...)},
    v_table{&V_TABLE<F>} {}

  Figure(const Figure& other) :
    v_ptr{other.v_table->clone(other.v_ptr)},
    v_table{other.v_table} {}

  Figure(Figure&& other) :
    v_ptr{other.v_table->move(other.v_ptr)},
    v_table{other.v_table} {}

  Figure& operator=(const Figure& other) {
    if (this != &other) {
      void* new_ptr = other.v_table->clone(other.v_ptr);
      v_table->destroy(v_ptr);
      v_ptr = new_ptr;
      v_table = other.v_table;
    }
    return *this;
  }

  Figure& operator=(Figure&& other) {
    if (this != &other) {
      void* new_ptr = other.v_table->move(other.v_ptr);
      v_table->destroy(v_ptr);
      v_ptr = new_ptr;
      v_table = other.v_table;
    }
    return *this;
  }

  ~Figure() noexcept {
    v_table->destroy(v_ptr);
  }

  void draw(Renderer& r) const {
    v_table->draw(v_ptr, r);
  }
};

static_assert(FigureLike<Figure>, "A figure is a figure");
} // namespace figures

#endif
