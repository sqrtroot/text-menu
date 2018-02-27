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

#ifndef TEXT_MENU_WINDOW_H
#define TEXT_MENU_WINDOW_H

#include <cstddef>
#include <iostream>
#include <complex>
#include "Option.h"

template<size_t size>
struct Window {
    const char * title;
    const char * footer;
    std::array<Option, size> options;

    Window(const char *title, const char *footer, const std::array<Option, size> &options) : title(title),
                                                                                             footer(footer),
                                                                                             options(options) {}
    void print() {
        std::cout << title << "\n";
        std::cout << "--------------------------------------------" << "\n";
        for (size_t i = 0; i < size; i++) {
            std::cout << i + 1 << "| " << options[i].text << "\n";
        }
        std::cout << "--------------------------------------------" << "\n";
        std::cout << footer << "\n";
    }

    void handle(size_t i, VirtualMenu * menu){
        if(i >= size){
            std::cout << "Invalid Option\n";
            return;
        }
        options[i].callback(menu);
    }
};

template<typename ...options>
constexpr auto make_window(const char * title, const char * footer, options... o) -> Window<sizeof...(options)>{
    return Window<sizeof...(options)>(title, footer, {o...});
};

#endif //TEXT_MENU_WINDOW_H
