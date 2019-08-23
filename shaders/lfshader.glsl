#version 410
#undef lowp
#undef mediump
#undef highp

precision highp float;
precision highp int;

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

in vec2 texCoord;
out vec4 FragColor;
uniform vec3 lightColor;
uniform sampler2D tex;

void main()
{
    vec4 tex = texture(tex,texCoord);
    FragColor = tex*(vec4(lightColor,tex.a)+vec4(0.8,0.8,0.8,1.0));
}
