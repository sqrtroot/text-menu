//===-- Window.h - Window class definition -------*- C++ -*-===//
//
//                    MIT License
//
//  Copyright (c) 2018 Robert Bezem
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//
//===----------------------------------------------------------------------===//
/// \file
/// Declarations for Window class and helper function
//===----------------------------------------------------------------------===//

#ifndef TEXT_MENU_WINDOW_H
#define TEXT_MENU_WINDOW_H

#include <cstddef>
#include <iostream>
#include <complex>
#include "Option.h"

/**
 * One window of a menu, holds some @ref Option's
 * @tparam size Amount of options in this Window
 */
template<size_t size>
struct Window {
    const char * title;
    const char * footer;
    std::array<Option, size> options;

    /**
     * Create a window
     * For easier use, use @ref make_window
     * @param title Title of the window printed at the top
     * @param footer Text to print at bottom of window
     * @param options Array of possible options of window
     */
    Window(const char *title, const char *footer, const std::array<Option, size> &options) : title(title),
                                                                                             footer(footer),
                                                                                             options(options) {}
    /**
     * Print all options of this window
     */
    void print() {
        std::cout << title << "\n";
        std::cout << "--------------------------------------------" << "\n";
        for (size_t i = 0; i < size; i++) {
            std::cout << i + 1 << "| " << options[i].text << "\n";
        }
        std::cout << "--------------------------------------------" << "\n";
        std::cout << footer << "\n";
    }

    /**
     * Call callback of option specified by i
     * @param i Option index (0 based) to call
     * The 0 based index differs from the 1 based index used in printing the menu
     * @param menu Pointer to the menu that handles this window
     */
    void handle(size_t i, VirtualMenu * menu){
        if(i >= size){
            std::cout << "Invalid Option\n";
            return;
        }
        options[i].callback(menu);
    }
};

/**
 * Generate a Window from a list of options.
 * Easyier than directly using the constructor of Window
 * @tparam options List of options, should only be Option type
 * @param title Title of window
 * @param footer Footer of window
 * @param o parameter list of options for this window
 * @return Window with template parameter size as the amount of options
 */
template<typename ...options>
constexpr auto make_window(const char * title, const char * footer, options... o) -> Window<sizeof...(options)>{
    return Window<sizeof...(options)>(title, footer, {o...});
};

#endif //TEXT_MENU_WINDOW_H
