/*
 * Laigter: an automatic map generator for lighting effects.
 * Copyright (C) 2019  Pablo Ivan Fonovich
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * Contact: azagaya.games@gmail.com
 */

#ifndef LAIGTER_CIMG_H
#define LAIGTER_CIMG_H

/* CImg is not ours to clean up, so include it as a system header and let every
 * compiler keep quiet about it, instead of listing warnings that only some of
 * them understand */
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC system_header
#elif defined(_MSC_VER)
#pragma warning(push, 0)
#endif

#define cimg_display 0
#include "thirdparty/CImg.h"

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#endif // LAIGTER_CIMG_H
