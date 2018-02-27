//===-- Option.h - Option class definition -------*- C++ -*-===//
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
/// Declarations @ref Window options class Option
//===----------------------------------------------------------------------===//

#ifndef TEXT_MENU_OPTION_H
#define TEXT_MENU_OPTION_H

#include <functional>
#include <utility>
#include "Menu.h"

/**
 * Option for @ref Window, used to pair a callback with some text
 */
struct Option {
    std::function<void(VirtualMenu *)> callback;
    const char * text;

    /**
     * Create a Option for a @ref Window
     * @param callback Function to be called when option is selected
     * @param text Name of the option to be displayed
     */
    Option(std::function<void(VirtualMenu *)> callback, const char *text) : callback(std::move(callback)), text(text) {}
};


#endif //TEXT_MENU_OPTION_H
