#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "novas.h"

int main(int argc, char **argv) {

    // from astrometry wcs
    double ra_center = 345.986294056;
    double dec_center = 28.1503891981;

    struct tm *ts;
    time_t tsec;
    tsec = time(0); // number of seconds since the Epoch, 1970-01-01 00:00:00 +0000 (UTC)
    time_t TAI = tsec + 37; // http://maia.usno.navy.mil/ser7/ser7.dat
    time_t TT = TAI + 32;   // and ignore the .184 fraction of 32.184
    ts = gmtime( &TT );
//    ts = gmtime( &tsec );
    double tjd_now = julian_date(
        (short)(ts->tm_year+1900),
        (short)(ts->tm_mon+1),
        (short)ts->tm_mday,
        ts->tm_hour + (ts->tm_min/60.0)+(ts->tm_sec/3600.0));
    printf("JNow  %.12f\n", tjd_now);

    double pos1[3];
    double pos2[3];

    // pos1[3] is a Position vector, geocentric equatorial rectangular
    // coordinates, referred to mean dynamical equator and equinox of first epoch
    radec2vector(ra_center / 15.0, dec_center, 1.0, pos1);

    // Formally, the current precession algorithm is a function of Barycentric
    // Dynamical Time (TDB), but using TT as the basis for the input Julian
    // dates results in a maximum error of only about 3 × 10-9 arcseconds,
    // which is totally negligible. Standard epoch J2000.0, although C-75
    // formally defined in the TT time scale, is the same in the TT and TDB
    // time scales to the precision given by double-precision Julian dates: at
    // J2000.0, TT − TDB ≈ 10^-4 second ≈ 10^-9 day. 

    // http://aa.usno.navy.mil/software/novas/novas_c/NOVAS_C3.1_Guide.pdf # C-74

    int result = 0;
    result = precession(2451545.0, pos1, tjd_now, pos2);
    if (result != 0) {
        printf("precession call failed\n");
        exit(1);
    }

    double JNow_ra  = 0.0;
    double JNow_dec = 0.0;

    result = vector2radec(pos2, &JNow_ra, &JNow_dec);
    if (result != 0) {
        printf("vector2radec call failed\n");
        exit(1);
    }
    JNow_ra *= 15.0;

    printf("J2000 ra,dec %.12f , %.12f\nJNow  ra,dec %.12f , %.12f\n", ra_center, dec_center, JNow_ra, JNow_dec);

    return(0);
}

