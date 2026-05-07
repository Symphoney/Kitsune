//
// Created by Rija on 4/14/2026.
//

#include <iostream>
#include "vector_raster.h"

int main() {
    // construct a line from (0, 0) to (3, 3)
    Line line{ Point{0, 0}, Point{3, 3} };

    LineToPointAdapter adapter(line);

    int idx = 0;
    for (const auto &p : adapter) {
        std::cout << "Point " << idx++ << ": " << p.x << ", " << p.y << '\n';
    }

    return 0;
}