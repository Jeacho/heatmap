
#ifndef PLOT_COLOR_HSV_HPP
#define PLOT_COLOR_HSV_HPP

#include <algorithm>
#include <cassert>
#include <iostream>

namespace plt {

namespace color {

template <typename float_type,
    typename = std::enable_if<std::is_floating_point<float_type>::value>>
struct hsv {

    const float_type hue;

    const float_type saturation;

    const float_type value;

    // ctor.
    constexpr hsv(float_type h, float_type s, float_type v)
         : hue(h), saturation(s), value(v) { }

};

namespace get {

template <typename float_type,
    typename = std::enable_if<std::is_floating_point<float_type>::value>>
float_type hue(const hsv<float_type> &from) {
    return from.hue;
}

template <typename float_type,
    typename = std::enable_if<std::is_floating_point<float_type>::value>>
float_type saturation(const hsv<float_type> &from) {
    return from.saturation;
}

template <typename float_type,
    typename = std::enable_if<std::is_floating_point<float_type>::value>>
float_type value(const hsv<float_type> &from) {
    return from.value;
}

} // namespace get

template <typename float_type,
    typename = std::enable_if<std::is_floating_point<float_type>::value>>
float_type linear(float_type from, float_type to, float step) {
    return from * (1.0f - step) + to * step;
}

template <typename float_type,
    typename = std::enable_if<std::is_floating_point<float_type>::value>>
hsv<float_type> interpolate(const hsv<float_type> &from,
                            const hsv<float_type> &to, float step) {
    return hsv<float_type>(linear(get::hue(from), get::hue(to), step),
        linear(get::saturation(from), get::saturation(to), step),
        linear(get::value(from), get::value(to), step));
}

} // namespace color

} // namespace plt

#endif // PLOT_COLOR_HSV_HPP
