//===-- Menu.h - Menu and VirtualMenu class definition -------*- C++ -*-===//
//
//                    MIT License
//
//	Copyright (c) 2018 Robert Bezem
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in all
//	copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//	SOFTWARE.
//
//===----------------------------------------------------------------------===//
/// \file
/// Declarations for Menu classes and helper functions
//===----------------------------------------------------------------------===//

#ifndef TEXT_MENU_MENU_H
#define TEXT_MENU_MENU_H

#include <cstddef>
#include <type_traits>
#include <tuple>
#include <cassert>

/**
 * Base class used for templated @ref Menu class so we can pass it around
 */
struct VirtualMenu {
    virtual void switch_window(size_t) = 0;

    virtual void print() = 0;
};

/**
 * Functor to handle handle calls of Menu
 */
struct WindowHandleFunctor {
    VirtualMenu *t;
    size_t index;

    WindowHandleFunctor(VirtualMenu *t, size_t index) : t(t), index(index) {}

    template<typename T>
    void operator()(T &tt) const { tt.handle(index, t); }
};

/* Thanks stack overflow
 * https://stackoverflow.com/questions/8194227/how-to-get-the-i-th-element-from-an-stdtuple-when-i-isnt-know-at-compile-time
 */
/**
 * Functor to print specified Window
 */
struct WindowPrintFunctor {
    template<typename T>
    void operator()(T &t) const { t.print(); }
};

/// \cond DO_NOT_DOCUMENT
template<size_t I = 0, typename FuncT, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
for_index(int, std::tuple<Tp...> &, FuncT) {};

template<std::size_t I = 0, typename FuncT, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type
for_index(int index, std::tuple<Tp...> &t, FuncT f) {
    if (index == 0) f(std::get<I>(t));
    for_index<I + 1, FuncT, Tp...>(index - 1, t, f);
};

/// \endcond

/**
 * Menu class, the base class for a text based menu
 * @tparam windows_t List of different windows that will be in the tuple
 */
template<typename ... windows_t>
struct Menu : public VirtualMenu {
    std::tuple<windows_t ...> windows;
    size_t current = 0;

    /**
     * Create a menu
     * For easier use, use @ref make_menu
     * @param windows All window used in this menu
     */
    explicit Menu(std::tuple<windows_t...> windows) : windows(std::move(windows)) {}

    /**
     * Set a new window as the active window
     * @param i 0 based index of new window
     */
    void switch_window(size_t i) override {
        assert(i < sizeof...(windows_t));
        current = i;
    }

    /**
     * Print currently active window
     */
    void print() override {
        for_index(current, windows, WindowPrintFunctor());
    }

    /**
     * Call handle function of window
     * @param option 0 based index of window to call handle function of
     * @see Window::handle
     */
    void handle(size_t option) {
        for_index(current, windows, WindowHandleFunctor(this, option));
    }
};

/**
 * Generate a Menu from a parameter list of Windows
 * @tparam Windows parameter list of Windows
 * @param w parameter list of windows
 * @return Menu with template type of windows
 * @see Window
 */
template<typename ...Windows>
constexpr auto make_menu(Windows ... w) -> Menu<Windows...> {
    return Menu<Windows ...>(std::make_tuple(w...));
};

#endif //TEXT_MENU_MENU_H
