#pragma once

#include <Graphics/Pattern.hpp>

/**
 * @brief Represents a linear gradient pattern with two colors (a and b)
 *
 */
struct GradientPattern final : public Pattern
{
    /**
     * @brief The two colors that make up the pattern
     *
     */
    Color a;
    Color b;

    /**
     * @brief Construct a new Gradient Pattern object with initialized colors
     *
     * @param a The first color
     * @param b The second color
     */
    GradientPattern(const Color &a, const Color &b);

    /**
     * @brief Destroy the Gradient Pattern object
     *
     */
    virtual ~GradientPattern() = default;

    /**
     * @brief Clone and provide a pointer to gradient pattern
     *
     * @return std::unique_ptr<Pattern> A unique pointer to the cloned pattern
     */
    std::unique_ptr<Pattern> clone() const override;

    /**
     * @brief Calculate the gradient color at a given point'x coordinate in
     *  world space
     *
     * @param point The point in world-space
     * @return Color The stripe color at the specified point
     */
    Color pattern_at(const Point &point) const override;
};
