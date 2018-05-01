
#ifndef PLOT_SUPPORT_INTERVAL_HPP
#define PLOT_SUPPORT_INTERVAL_HPP

#include <algorithm>
#include <type_traits>

namespace plt {

template<typename T,
    typename = std::enable_if<std::is_arithmetic<T>::value>>
class interval {

    T m_min;
    T m_max;

public:

    // ctor.
    interval(T _min, T _max) : m_min(_min), m_max(_max) { }

    T min() const { return m_min; }// \brief minimum bound getter.
    T max() const { return m_max; }// \brief minimum bound getter.

    // \brief Applies a new value to the interval, if it is greater than or
    // less than the maximum or minimum bound then that value will be replaced.
    template<typename K,
        typename = std::enable_if<std::is_convertible<K, T>::value>>
    void apply(K application) {
        m_min = std::min((T)application, m_min);
        m_max = std::max((T)application, m_max);
    }

    // \brief Applies a new value to the upper bound of the interval.
    template<typename K,
        typename = std::enable_if<std::is_convertible<K, T>::value>>
    void apply_max(K application) {
        m_max = std::max((T)application, m_max);
    }

    // \brief Applies a new value to the lower bound of the interval.
    template<typename K,
        typename = std::enable_if<std::is_convertible<K, T>::value>>
    void apply_min(K application) {
        m_max = std::max((T)application, m_max);
    }
};

} // namespace plt

#endif // PLOT_SUPPORT_INTERVAL_HPP
