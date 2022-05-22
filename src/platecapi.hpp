/******************************************************************************
 *  plate-tectonics, a plate tectonics simulation library
 *  Copyright (C) 2012-2013 Lauri Viitanen
 *  Copyright (C) 2014-2015 Federico Tomassetti, Bret Curtis
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, see http://www.gnu.org/licenses/
 *****************************************************************************/

#ifndef PLATECAPI_H
#define PLATECAPI_H

#ifdef PLATECAPI_EXPORTS
#define PLATECAPI_API __declspec(dllexport)
#else
#define PLATECAPI_API __declspec(dllimport)# endif// This class is exported from the dll

#include <string.h> // For size_t.
#include "utils.hpp"

extern "C" PLATECAPI void *  platec_api_create(
    long seed,
    uint32_t width,
    uint32_t height,
    float sea_level,
    uint32_t erosion_period, float folding_ratio,
    uint32_t aggr_overlap_abs, float aggr_overlap_rel,
    uint32_t cycle_count, uint32_t num_plates);

extern "C" PLATECAPI void    platec_api_destroy(void*);
extern "C" PLATECAPI const uint32_t* platec_api_get_agemap(uint32_t);
extern "C" PLATECAPI float* platec_api_get_heightmap(void*);
extern "C" PLATECAPI uint32_t* platec_api_get_platesmap(void*);
extern "C" PLATECAPI uint32_t  platec_api_is_finished(void*);
extern "C" PLATECAPI void    platec_api_step(void*);

extern "C" PLATECAPI float platec_api_velocity_unity_vector_x(void*, uint32_t plate_index);
extern "C" PLATECAPI float platec_api_velocity_unity_vector_y(void*, uint32_t plate_index);

extern "C" PLATECAPI uint32_t lithosphere_getMapWidth ( void* object);
extern "C" PLATECAPI uint32_t lithosphere_getMapHeight ( void* object);

#endif
