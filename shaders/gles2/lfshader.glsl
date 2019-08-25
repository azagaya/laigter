#version 100
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
uniform vec3 lightColor;
uniform sampler2D tex;
uniform vec2 pixelSize;
uniform bool selected;

void main()
{
    vec2 pixSize = 2.0*pixelSize;
    vec4 color = texture2D(tex,texCoord);
    float alpha = color.a;
    if (selected){
        alpha *= 1.5;
        color.xyz = mix(3.0*lightColor,color.xyz*(lightColor+vec3(0.8,0.8,0.8)),color.a);
    }else{
        color.xyz *= (lightColor+vec3(0.8,0.8,0.8));
    }
    gl_FragColor = vec4(color.xyz,alpha);
}
