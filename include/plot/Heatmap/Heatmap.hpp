
#ifndef PLOT_PLOT_HEATMAP_HPP
#define PLOT_PLOT_HEATMAP_HPP

#include <cassert>
#include <utility>

#include "plot/Color/RGB.hpp"
#include "plot/Color/HSV.hpp"
#include "plot/Heatmap/Stamp.hpp"
#include "plot/Support/Interval.hpp"

namespace plt {

template<typename float_type,
    typename = std::enable_if<std::is_floating_point<float_type>::value>>
class Heatmap {

    // \brief The dimensions of this heat map.
    const std::size_t m_width;
    const std::size_t m_height;

    // \brief The range of the heatmaps data.
    interval<float_type> m_range;

    // \brief The raw normalized heat map data.
    float_type *m_data;

public:

    // ctor.
    Heatmap(std::size_t wid, std::size_t hgt)
         : m_width(wid), m_height(hgt), m_range(0.0f, 0.0f) {
        m_data = new float_type[m_width * m_height];
        memset(m_data, 0.0f, m_width * m_height);
    }

    Heatmap(const Heatmap &other) = delete;
    Heatmap &operator=( Heatmap &) = delete;

    // \brief Returns the width of this Heatmap in pxiels.
    inline std::size_t width()     const { return m_width;     }

    // \brief Returns the height of this Heatmap in pxiels.
    inline std::size_t height()    const { return m_height;    }

    // \brief Returns the range of this Heatmap.
    inline float_type max() const { return m_range.max(); }
    inline float_type min() const { return m_range.min(); }

    // \brief Returns a pointer to the raw data of this Heatmap.
    inline float_type *data() const { return m_data; }

    // \brief Adds a new point of interest onto the Heatmap with either the
    // stamp specified or Stamp::basic.
    void point(std::size_t x, std::size_t y, float_type weight = 1.0f,
         const Stamp &stamp = Stamp()) {

        if(x >= width() || y >= height())
            return;

        const unsigned x0 = x < stamp.width()/2
            ? (stamp.width()/2 - x)
            : 0;

        const unsigned y0 = y < stamp.height()/2
            ? (stamp.height()/2 - y)
            : 0;

        const unsigned x1 = (x + stamp.width()/2) < width()
            ? stamp.width()
            : stamp.width()/2 + (width() - x);

        const unsigned y1 = (y + stamp.height()/2) < height()
            ? stamp.height()
            : stamp.height()/2 + (height() - y);

        for(std::size_t iy = y0 ; iy < y1 ; ++iy) {
            float* line = m_data + ((y + iy) - stamp.height()/2)*width() + (x + x0) - stamp.width()/2;
            const float* stampline = stamp.data() + iy * stamp.width() + x0;

            for(std::size_t ix = x0 ; ix < x1 ; ++ix, ++line, ++stampline) {
                assert(*stampline >= 0.0f);

                *line += *stampline * abs(weight);
                m_range.apply(*line);

                assert(*line >= 0.0f);
            }
        }
    }

    // \brief Sets the point specified to the value specified.
    void set(std::size_t x, std::size_t y, float value) {
        if(x >= width() || y >= height())
            return;

        m_data[y * m_width + x] = value;
        m_range.apply(value);
    }

    // \brief Maps each value in this heatmaps data set to a color within the
    // color scheme specified and stores those values into a specified array.
    unsigned char *render(unsigned char *mem, float sat = 1.0f) {
        assert(sat > 0.0f && "saturation must be > 0.0f");

        for (std::size_t y = 0; y < m_height; ++y) {
            unsigned char* colorline = mem + 4 * y * m_width;

            for (std::size_t x = 0; x < m_width; ++x) {
                float step = (m_data[y * m_width + x] / max());

                color::rgb<float> color = color::get::cast_rgb(
                    color::hsv<float>(240.0f - 240.0f * step, 1.0f, 1.0f));

                colorline[0] = color::get::red(color) * 255.0f;
                colorline[1] = color::get::green(color) * 255.0f;
                colorline[2] = color::get::blue(color) * 255.0f;
                colorline[3] = 1.0f;

                colorline += 4;
            }
        }

        return mem;
    }

    // \brief Support overload that allocates a new array to store the rendering.
    unsigned char *render(float sat = 1.0f)  {
        return render(new unsigned char[m_width * m_height * 4], sat);
    }
};

} // namespace plt

#endif // PLOT_PLOT_HEATMAP_HPP
