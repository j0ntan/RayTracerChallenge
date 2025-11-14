#pragma once

#include <Graphics/Pattern.hpp>

/**
 * @brief Represents a stripe pattern with two colors (a and b)
 *
 */
struct StripePattern final : public Pattern
{
    /**
     * @brief The two colors that make up the pattern
     *
     */
    Color a;
    Color b;

    /**
     * @brief Construct a new Stripe Pattern object with initialized colors
     *
     * @param a The first color
     * @param b The second color
     */
    StripePattern(const Color &a, const Color &b);

    /**
     * @brief Select the color at a given point in the stripe pattern
     *
     * @note Dependent on x-coordinate only
     *
     */
    virtual ~StripePattern() = default;

    /**
     * @brief Clone and provide a pointer to stripe pattern
     *
     * @return std::unique_ptr<Pattern> A unique pointer to the cloned pattern
     */
    std::unique_ptr<Pattern> clone() const override;

    /**
     * @brief Select the color at a given point in the stripe pattern
     *
     * @note Dependent on x-coordinate only
     *
     * @param point The point in world-space
     * @return Color The stripe color at the specified point
     */
    Color pattern_at(const Point &point) const override;
};
