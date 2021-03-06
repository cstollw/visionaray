// This file is distributed under the MIT license.
// See the LICENSE file for details.

#pragma once

#ifndef VSNRAY_SIMPLE_INL
#define VSNRAY_SIMPLE_INL

#include <visionaray/result_record.h>
#include <visionaray/surface.h>

#include "traverse.h"


namespace visionaray
{
namespace simple
{

template <typename Params>
struct kernel
{

    Params params;

    template <typename R>
    VSNRAY_FUNC result_record<typename R::scalar_type> operator()(R ray) const
    {
        using S = typename R::scalar_type;
        using C = typename result_record<S>::color_type;
        using V = typename result_record<S>::vec_type;

        result_record<S> result;

        auto hit_rec = closest_hit(ray, params.prims.begin, params.prims.end);

        if (any(hit_rec.hit))
        {
            hit_rec.isect_pos = ray.ori + ray.dir * hit_rec.t;

            auto surf = get_surface(hit_rec, params);
            auto ambient = C(surf.material.ambient(), S(1.0)) * C(params.ambient_color);
            C shaded_clr = select( hit_rec.hit, ambient, C(params.bg_color) );

            for (auto it = params.lights.begin; it != params.lights.end; ++it)
            {
                auto sr         = make_shade_record<Params, S>();
                sr.active       = hit_rec.hit;
                sr.isect_pos    = hit_rec.isect_pos;
                sr.view_dir     = -ray.dir;
                sr.light_dir    = normalize( V(it->position()) - hit_rec.isect_pos );
                sr.light        = it;
                auto clr        = surf.shade(sr);

                shaded_clr += select( hit_rec.hit, C(clr, S(1.0)), C(0.0) );
            }

            result.color     = shaded_clr;
            result.isect_pos = hit_rec.isect_pos;
        }
        else
        {
            result.color = C(params.bg_color);
        }

        result.hit = hit_rec.hit;
        return result;
    }
};

} // simple
} // visionaray

#endif // VSNRAY_SIMPLE_INL
