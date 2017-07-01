#!/usr/bin/python

from astropy.coordinates import FK5, SkyCoord
from astropy.time import Time
from datetime import datetime
import astropy.units as u

ra = 345.986294056
dec = 28.1503891981

ut = Time(datetime.utcnow(), scale='utc')
time_now = ut.jd
#time_now = 2457936.120665675029

coord_j2000 = SkyCoord(ra*u.deg, dec*u.deg, frame=FK5)
fk5_now = FK5(equinox=Time(time_now, format="jd", scale="utc"))

coord_now = coord_j2000.transform_to(fk5_now)
print(coord_now)

