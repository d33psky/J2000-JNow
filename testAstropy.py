#!/usr/bin/python

from datetime import datetime
from astropy.coordinates import FK5, SkyCoord
from astropy.time import Time
import astropy.units as u

ra = 345.986294056
dec = 28.1503891981

time_now = Time(datetime.utcnow(), scale='utc')

coord_j2000 = SkyCoord(ra*u.deg, dec*u.deg, frame=FK5)
fk5_now = FK5(equinox=Time(time_now.jd, format="jd", scale="utc"))
coord_now = coord_j2000.transform_to(fk5_now)

print("Julian date: %f10" % time_now.jd)
print("Astropy JNOW (RA,Dec in degrees): %f10,%f10" % (coord_now.ra.value,coord_now.dec.value))

