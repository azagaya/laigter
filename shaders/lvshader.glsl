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
#version 110
attribute vec3 aPos;
attribute vec2 aTexCoord;
varying vec2 texCoord;
uniform mat4 transform;
uniform mat4 view;
uniform mat4 projection;
void main()
{
  gl_Position = projection * view * transform * vec4(aPos, 1.0);
  gl_Position.z = 0.0;
  texCoord = aTexCoord;
}
