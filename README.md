# text-menu
Header only C++ Text Menu Implementation
These classes should help you make easy text menus for your programs

# Example
Here is an simple example to show you how to use text menu:
```c++
#include <iostream>
#include <functional>
#include <cstdlib>
#include "Window.h"

int main() {
    std::string mqtt_host = "localhost";
    size_t      mqtt_port = 1883;
    auto w1 = make_window("Main Menu", "",
                          Option([](VirtualMenu *menu) { menu->switch_window(1); }, "MQTT Settings"),
                          Option([](VirtualMenu *) { exit(0); }, "Exit")
    );
    auto w2 = make_window("MQTT Settings", "",
                          Option([&](VirtualMenu *) {
                              std::cout << "Type new hostname\n";
                              std::cin >> mqtt_host;
                              std::cout << "New host is " << mqtt_host << '\n';
                          }, "Set Hostname"),
                          Option([&](VirtualMenu *) {
                              std::cout << "Type new port\n";
                              std::cin >> mqtt_port;
                              std::cout << "New host is " << mqtt_port << '\n';
                          }, "Set Port"),
                          Option([&](VirtualMenu *) {
                              std::cout << "Hostname: " << mqtt_host << '\n' << "Port: " << mqtt_port << '\n';
                          }, "Print Settings"),
                          Option([](VirtualMenu *menu) { menu->switch_window(0); }, "Return")
    );
    auto menu = make_menu(w1, w2);
    while (true) {
        menu.print();
        size_t x;
        std::cin >> x;
        x--;
        menu.handle(x);
        std::cout << "\n";
    }
}
```

This would produce the following output:
[![asciicast](https://asciinema.org/a/L8ik6IPnd7cTjBzi4Bk4eg1H5.png)](https://asciinema.org/a/L8ik6IPnd7cTjBzi4Bk4eg1H5)


# License
This project is licensed under the MIT license.
See the LICENSE file for the full license.

# Todo
- [ ] Make abstraction for printing so it works on other devices (think arduino etc)
