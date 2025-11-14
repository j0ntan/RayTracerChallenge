#pragma once

#include <Graphics/Pattern.hpp>

/**
 * @brief Represents a ring pattern with two colors (a and b)
 *
 */
struct RingPattern final : public Pattern
{
    /**
     * @brief The two colors that make up the pattern
     *
     */
    Color a;
    Color b;

    /**
     * @brief Construct a new Ring Pattern object with initialized colors
     *
     * @param a The first color
     * @param b The second color
     */
    RingPattern(const Color &a, const Color &b);

    /**
     * @brief Destroy the Ring Pattern object
     *
     */
    virtual ~RingPattern() = default;

    /**
     * @brief Clone and provide a pointer to ring pattern
     *
     * @return std::unique_ptr<Pattern> A unique pointer to the cloned pattern
     */
    std::unique_ptr<Pattern> clone() const override;

    /**
     * @brief Calculate the ring color at a given point's x- & z-coordinate in
     *  world space
     *
     * @param point The point in world-space
     * @return Color The ring color at the specified point
     */
    Color pattern_at(const Point &point) const override;
};
