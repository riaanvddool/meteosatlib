//-----------------------------------------------------------------------------
//
//  File        : Proj_Geos.cpp
//  Description : Mapping Algorithms interface - Geostationary Proj.
//  Project     : CETEMPS 2003
//  Author      : Graziano Giuliani (CETEMPS - University of L'Aquila
//  References  : LRIT/HRIT GLobal Specification par. 4.4 pag. 20-28
//                Doc. No. CGMS 03 Issue 2.6 12 August 1999
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#include <proj/Geos.h>
#include <proj/const.h>
#include <string.h>
#include <cmath>
#include <sstream>

namespace msat {
namespace proj {

Geos::Geos( ) { }

void Geos::mapToProjected(const MapPoint& m, ProjectedPoint& p)
{
	double lat = m.lat * M_PI / 180;
	double lon = (m.lon - sublon) * M_PI / 180;
  double c_lat;
  double r1,r2,r3,rn,rl;

  c_lat = atan( EARTH_1E2 * tan(lat) );
  rl    = EARTH_RPOL / ( sqrt(1.0 - EARTH_E2 * pow(cos(c_lat), 2.0)) );

  r1 = orbitRadius - \
        rl * cos(c_lat) * cos(lon);
  r2 = -rl * cos(c_lat) * sin(lon);
  r3 = rl * sin(c_lat);
  rn = sqrt( r1*r1 + r2*r2 + r3*r3 );

  p.x = atan(-r2 / r1) * 180 / M_PI;
  p.y = asin(-r3 / rn) * 180 / M_PI;
}

void Geos::projectedToMap(const ProjectedPoint& p, MapPoint& m)
{
	double x = p.x * M_PI / 180;
	double y = p.y * M_PI / 180;
  double sd,sn;
  double s1,s2,s3,sxy;

  sd = sqrt(pow((orbitRadius * cos(x) * cos(y)), 2.0) - \
       (pow(cos(y), 2.0) + EARTH_IE2 * pow(sin(y), 2.0)) * \
       1737121856 ); 
  sn = (orbitRadius * cos(x) * cos(y) - sd) / \
       (pow(cos(y), 2.0) + EARTH_IE2 * pow(sin(y), 2.0));

  s1 = orbitRadius - sn * cos(x) * cos(y);
  s2 = sn * sin(x) * cos(y);
  s3 = -sn * sin(y);
  sxy = sqrt( s1*s1 + s2*s2 );

  m.lon = atan(s2/s1) * 180 / M_PI + sublon;
  m.lat = atan(EARTH_IE2 * (s3 / sxy)) * 180 / M_PI;
}

std::string Geos::format()
{
	std::stringstream str;
	str << "GEOS(sublon: " << sublon << ", orbitRadius: " << orbitRadius << ")";
	return str.str();
}

}
}

// vim:set ts=2 sw=2:
