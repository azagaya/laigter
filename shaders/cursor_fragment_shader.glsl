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

varying vec2 texCoord;
uniform vec3 lightColor;
uniform sampler2D tex;
uniform vec2 pixelSize;
uniform bool selected;
uniform float scale;

void main() {
  vec2 pixSize = 2.0 * pixelSize;
  vec4 color = texture2D(tex, texCoord);
  float alpha = color.a;

  float l = length(texCoord-0.5);

  if (l < 0.5 && l > 0.5 - 1.0*(pixelSize.x / scale))
    color = vec4(0.6,0.6,1.0,1.0);
  if (l < 0.5 - 2.0*(pixelSize.x / scale) && l > 0.5 - 3.0*(pixelSize.x / scale))
    color = vec4(0.0,0.0,0.4,1.0);

  gl_FragColor = vec4(color);
}
