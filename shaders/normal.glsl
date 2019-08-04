#version 130

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
uniform sampler2D texture;
uniform vec2 pixelSize;
uniform float depth;
uniform float normalInvertX, normalInvertY;

vec3 normal();
float gray_sacale(vec2 texCord);

void main()
{
    vec4 tex = texture2D(texture,texCoord);
    FragColor = vec4(normal(),1.0);
}

float gray_scale(vec2 texCoord){
    vec4 tex = texture2D(texture, texCoord);
    return (tex.r + tex.g + tex.g)/3.0;
}

vec3 normal(){
    vec2 textureSize = 1.0/pixelSize;
    float dx = -gray_scale(texCoord - vec2(pixelSize.x,0.0))+gray_scale(texCoord + vec2(pixelSize.x,0.0));
    float dy = -gray_scale(texCoord - vec2(0.0,pixelSize.y))+gray_scale(texCoord + vec2(0.0,pixelSize.y));
    vec3 n = normalize(vec3(-dx*(depth/1000.0)*normalInvertX*255.0,
                    dy*(depth/1000.0)*normalInvertY*255.0,
                    1))*0.5+0.5;
    return n;
}
