#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <erfa.h>

int main(int argc, char **argv) {

    // from astrometry wcs
    double ra_center = 345.986294056;
    double dec_center = 28.1503891981;

    // http://www.iausofa.org/sofa_ast_c.pdf
    // iauAtco13 Given :
    double rc, dc; // ICRS [ α, δ ] at J2000.0 (radians, Note 1)
    double pr = 0.0;     // RA proper motion (radians/year; Note 2)
    double pd = 0.0;     // Dec proper motion (radians/year)
    double px = 0.0;     // parallax (arcsec)
    double rv = 0.0;     // radial velocity (km/s, positive if receding)
    double utc1;   // UTC as a 2-part. . .
    double utc2;   // . . . quasi Julian Date (Notes 3,4)
    double dut1;   // UT1−UTC (seconds, Note 5)
    double elong = 0.0;  // longitude (radians, east-positive, Note 6)
    double phi   = 0.0;  // geodetic latitude (radians, Note 6)
    double hm = 0;     // height above ellipsoid (m, geodetic Notes 6,8)
    double xp = 0.0, yp = 0.0; // polar motion coordinates (radians, Note 7)
    double phpa = 1000.0;   // pressure at the observer (hPa ≡ mB, Note 8)
    double tc = 0.0;     // ambient temperature at the observer (deg C)
    double rh = 0.0;     // relative humidity at the observer (range 0-1)
    double wl = 0.5;     // wavelength (micrometers, Note 9)
    // iauAtco13 Returned :
    double aob; // * observed azimuth (radians: N=0◦ , E=90◦)
    double zob; // * observed zenith distance (radians)
    double hob; // * observed hour angle (radians)
    double dob; // * observed declination (radians)
    double rob; // * observed right ascension (CIO-based, radians)
    double eo;  // * equation of the origins (ERA−GST)

    rc = ERFA_DD2R * ra_center; // Degrees to radians
    dc = ERFA_DD2R * dec_center;

    dut1 = 0.36; // http://maia.usno.navy.mil/ser7/ser7.dat

    time_t tsec;
    struct tm *ts;
    tsec = time(0); // number of seconds since the Epoch, 1970-01-01 00:00:00 +0000 (UTC)    
    ts = gmtime(&tsec);
    int result = 0;
    result = eraDtf2d ( "UTC", ts->tm_year+1900, ts->tm_mon+1, ts->tm_mday, ts->tm_hour, ts->tm_min, ts->tm_sec, &utc1, &utc2 );
    if (result != 0) {
        printf("eraDtf2d call failed\n");
        exit(1);
    }

    result = eraAtco13 ( rc, dc, pr, pd, px, rv, utc1, utc2, dut1, elong, phi, hm, xp, yp, phpa, tc, rh, wl, &aob, &zob, &hob, &dob, &rob, &eo );
    if (result != 0) {
        printf("eraAtco13 call failed\n");
        exit(1);
    }

    double JNow_ra  = eraAnp(rob - eo) * ERFA_DR2D; // Convert CIO RA to equinox of date RA by subtracting the equation of the origins, Radians to degrees
    double JNow_dec = dob * ERFA_DR2D;

    printf("J2000 ra,dec %.12f , %.12f\nJNow  ra,dec %.12f , %.12f\n", ra_center, dec_center, JNow_ra, JNow_dec);

    return(0);
}

