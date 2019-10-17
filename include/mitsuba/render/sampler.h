#pragma once

#include <mitsuba/mitsuba.h>
#include <mitsuba/render/fwd.h>
#include <mitsuba/core/logger.h>
#include <mitsuba/core/object.h>
#include <mitsuba/core/vector.h>

NAMESPACE_BEGIN(mitsuba)

template <typename Float, typename Spectrum>
class MTS_EXPORT_RENDER Sampler : public Object {
public:
    MTS_IMPORT_TYPES()

    /**
     * \brief Create a clone of this sampler
     *
     * The clone is allowed to be different to some extent, e.g. a pseudorandom
     * generator should be based on a different random seed compared to the
     * original. All other parameters are copied exactly.
     *
     * May throw an exception if not supported. Cloning may also change the
     * state of the original sampler (e.g. by using the next 1D sample as a
     * seed for the clone).
     */
    virtual ref<Sampler> clone() = 0;

    /// Deterministically seed the underlying RNG, if any
    virtual void seed(size_t seed_value);
    /**
     * Deterministically seed the underlying RNG, if any.
     * Also reset the differentiable-mode RNG's state size (or initialize
     * it if it wasn't created).
     */
    // TODO: check if this is really the right interface
    virtual void seed(size_t seed_value, size_t size);

    /// Retrieve the next component value from the current sample
    virtual Float next_1d(Mask active = true);

    /// Retrieve the next two component values from the current sample
    virtual Point2f next_2d(Mask active = true);

    /// Return the number of samples per pixel
    size_t sample_count() const { return m_sample_count; }

    MTS_DECLARE_CLASS()

protected:
    Sampler(const Properties &props);
    virtual ~Sampler();

protected:
    size_t m_sample_count;
};

NAMESPACE_END(mitsuba)
