
#ifndef PLOT_COLOR_COLOR_HPP
#define PLOT_COLOR_COLOR_HPP

#include <algorithm>
#include <cassert>
#include <cmath>

#include <plot/Color/HSV.hpp>

namespace plt {

namespace color {

template <typename float_type,
    typename = std::enable_if<std::is_floating_point<float_type>::value>>
struct rgb {
    // \brief Color components. The color components are normalized values
    // between 0 and 1.
    const float_type red;
    const float_type green;
    const float_type blue;

    // ctor.
    rgb(const float_type &r, const float_type &g, const float_type &b)
         : red(r), green(g), blue(b) { }
};

namespace get {

template <typename float_type,
    typename = std::enable_if<std::is_floating_point<float_type>::value>>
float_type red(const rgb<float_type> &from) {
    return from.red;
}

template <typename float_type,
    typename = std::enable_if<std::is_floating_point<float_type>::value>>
float_type green(const rgb<float_type> &from) {
    return from.green;
}

template <typename float_type,
    typename = std::enable_if<std::is_floating_point<float_type>::value>>
float_type blue(const rgb<float_type> &from) {
    return from.blue;
}

template <typename float_type,
    typename = std::enable_if<std::is_floating_point<float_type>::value>>
rgb<float_type> cast_rgb(const hsv<float_type> &from) {
    float_type r, g, b; // 0.0-1.0

    int   hi = (int)(hue(from) / 60.0f) % 6;
    float_type f  = (hue(from) / 60.0f) - hi;
    float_type p  = value(from) * (1.0f - saturation(from));
    float_type q  = value(from) * (1.0f - saturation(from) * f);
    float_type t  = value(from) * (1.0f - saturation(from) * (1.0f - f));

    switch(hi) {
        case 0: r = value(from), g = t, b = p; break;
        case 1: r = q, g = value(from), b = p; break;
        case 2: r = p, g = value(from), b = t; break;
        case 3: r = p, g = q, b = value(from); break;
        case 4: r = t, g = p, b = value(from); break;
        case 5: r = value(from), g = p, b = q; break;
    }

    return rgb<float_type>(r, g, b);
}

} // namespace get

} // namespace color

} // namespace plt

#endif // PLOT_COLOR_COLOR_HPP
