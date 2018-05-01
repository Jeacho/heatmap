
#ifndef PLOT_HEATMAP_STAMP_HPP
#define PLOT_HEATMAP_STAMP_HPP

#include <cstddef>
#include <cstring>

namespace plt {

class Stamp {

    // \brief The basic stamp's raw data.
    static float m_basic_data[];

    // \brief The raw color scheme data.
    float *m_data;

    // \brief The dimensions of this heat map.
    const std::size_t m_width;
    const std::size_t m_height;

public:

    // ctor.
    Stamp() : m_width(9), m_height(9) {
        m_data = m_basic_data;
    }

    Stamp(std::size_t wid, std::size_t hgt, const float *dat)
         : m_width(wid), m_height(hgt) {
        m_data = new float[m_width * m_height];
        memcpy(m_data, dat, m_width * m_height);
    }

    // dtor
    ~Stamp() {
        if (m_data != m_basic_data)
            delete[] m_data;
    }

    // \brief Returns the width of this Stamp in pixels.
    inline std::size_t width()     const { return m_width;     }

    // \brief Returns the height of this Stamp in pixels.
    inline std::size_t height()    const { return m_height;    }

    // \brief Returns a pointer to the raw data of this Heatmap.
    inline float *data() const { return m_data; }
};

} // namespace plt

#endif // PLOT_HEATMAP_STAMP_HPP
