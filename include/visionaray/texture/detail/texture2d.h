// This file is distributed under the MIT license.
// See the LICENSE file for details.

#pragma once

#ifndef VSNRAY_TEXTURE_TEXTURE2D_H
#define VSNRAY_TEXTURE_TEXTURE2D_H

#include <cstddef>

#include "texture_common.h"


namespace visionaray
{


template <typename Base, typename T, tex_read_mode ReadMode>
class texture_iface<Base, T, ReadMode, 2> : public Base
{
public:

    using base_type = Base;
    using value_type = T;

    static const size_t dimensions = 2;

    texture_iface() = default;

    texture_iface(size_t w, size_t h)
        : Base(w * h)
        , width_(w)
        , height_(h)
    {
    }


    value_type& operator()(size_t x, size_t y)
    {
        return base_type::data()[y * width_ + x];
    }

    value_type const& operator()(size_t x, size_t y) const
    {
        return base_type::data()[y * width_ + x];
    }


    size_t size() const { return width_ * height_; }

    size_t width() const { return width_; }
    size_t height() const { return height_; }

    void resize(size_t w, size_t h)
    {
        width_ = w;
        height_ = h;
    }

private:

    size_t width_;
    size_t height_;

};


} // visionaray


#endif // VSNRAY_TEXTURE_TEXTURE2D_H
