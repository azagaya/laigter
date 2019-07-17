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
uniform int radius;

float border(sampler2D texture, vec2 texCoord){
    if (texCoord.x < 0 || texCoord.y < 0 || texCoord.x > 1 || texCoord.y > 1)
        return 0;
    vec4 tex = texture2D(texture, texCoord);
    return float(tex.a != 0.0);
}

float distance(sampler2D texture, vec2 texCoord){
    /**** Alternative distances algorithm (too slow) ****/
        float pi =  3.14159265359;
        float dist = radius;
        bool d1 = false, d2 = false, d3 = false, d4 = false;
        if (border(texture, texCoord) == 0.0) return 0.0;
        for (int i =1; i <= radius; i++){
                for (int j = 0; j<=4*i; j++){
                        float angle = j * 2.0*pi/(4.0*i);
                        float len = i;
                        d1 = (border(texture, texCoord+vec2(cos(angle)*len*pixelSize.x,sin(angle)*len*pixelSize.y)) == 0.0);
                        if (d1 ){
                                dist = min(dist,len);
                        }
                }
                if (d1) break;
        }
        dist /= radius;
        dist = sqrt(1.0-pow((dist-1.0),2.0));
        return dist;
}

void main()
{
    vec4 tex = texture2D(texture,texCoord);
    FragColor = vec4(vec3(distance(texture,texCoord)),1.0);
}
