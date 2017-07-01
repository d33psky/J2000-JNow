#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <math.h>
#include <libnova/libnova.h>
#include <sofa.h>
#include "novas.h"

int main(int argc, char **argv) {

    // from astrometry wcs
    double ra_center = 345.986294056;
    double dec_center = 28.1503891981;

    time_t tsec;
    //    tsec = time(0); // number of seconds since the Epoch, 1970-01-01 00:00:00 +0000 (UTC)
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz); // number of seconds since the Epoch, 1970-01-01 00:00:00 +0000 (UTC) with microsecond precision
    tsec = tv.tv_sec; // for later use in NOVAS who builds TT from UTC and uses it as TDB
    struct tm *utc_tm;
    utc_tm = gmtime(&tv.tv_sec); // UTC time used by libNOVA and SOFA

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // libNOVA 
    ////////////////////////////////////////////////////////////////////////////////////////////////
    struct ln_equ_posn mean_position;
    struct ln_equ_posn position;

    mean_position.ra  = ra_center;
    mean_position.dec = dec_center;

    //    double JNow = ln_get_julian_from_sys();
    struct ln_date date;
    date.seconds = utc_tm->tm_sec + ((double)tv.tv_usec / 1000000);
    date.minutes = utc_tm->tm_min;
    date.hours   = utc_tm->tm_hour;
    date.days    = utc_tm->tm_mday;
    date.months  = utc_tm->tm_mon + 1;
    date.years   = utc_tm->tm_year + 1900;
    double JNow = ln_get_julian_day(&date);
    printf("libNOVA UTC JNow  %.12f\n", JNow);

    ln_get_equ_prec2(&mean_position, JD2000, JNow, &position);

    double libNOVA_JNow_ra  = position.ra;
    double libNOVA_JNow_dec = position.dec;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // NOVAS
    ////////////////////////////////////////////////////////////////////////////////////////////////
    struct tm *ts;
    time_t TAI = tsec + 37; // http://maia.usno.navy.mil/ser7/ser7.dat
    time_t TT = TAI + 32;   // and ignore the .184 fraction of 32.184 here, add it later
    ts = gmtime( &TT );
    double tjd_now = julian_date(
        (short)(ts->tm_year+1900),
        (short)(ts->tm_mon+1),
        (short)ts->tm_mday,
        ts->tm_hour + (ts->tm_min/60.0)+((ts->tm_sec + 0.184)/3600.0) + ((double)tv.tv_usec/3600.0/1000000));
    printf("NOVAS   TT  JNow  %.12f\n", tjd_now);

    double pos1[3];
    double pos2[3];
    radec2vector(ra_center / 15.0, dec_center, 1.0, pos1);

    int result = 0;
    result = precession(2451545.0, pos1, tjd_now, pos2);
    if (result != 0) {
        printf("precession call failed\n");
        exit(1);
    }

    double NOVAS_JNow_ra  = 0.0;
    double NOVAS_JNow_dec = 0.0;

    result = vector2radec(pos2, &NOVAS_JNow_ra, &NOVAS_JNow_dec);
    if (result != 0) {
        printf("vector2radec call failed\n");
        exit(1);
    }
    NOVAS_JNow_ra *= 15.0;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // SOFA
    ////////////////////////////////////////////////////////////////////////////////////////////////
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
    double rh = 0.5;     // relative humidity at the observer (range 0-1)
    double wl = 0.5;     // wavelength (micrometers, Note 9)
    // iauAtco13 Returned :
    double aob; // * observed azimuth (radians: N=0◦ , E=90◦)
    double zob; // * observed zenith distance (radians)
    double hob; // * observed hour angle (radians)
    double dob; // * observed declination (radians)
    double rob; // * observed right ascension (CIO-based, radians)
    double eo;  // * equation of the origins (ERA−GST)

    rc = DD2R * ra_center; // Degrees to radians
    dc = DD2R * dec_center;

    dut1 = 0.36; // http://maia.usno.navy.mil/ser7/ser7.dat

    result = iauDtf2d ( "UTC", utc_tm->tm_year+1900, utc_tm->tm_mon+1, utc_tm->tm_mday, utc_tm->tm_hour, utc_tm->tm_min, utc_tm->tm_sec + ((double)tv.tv_usec / 1000000), &utc1, &utc2 );
    if (result != 0) {
        printf("iauDtf2d call failed\n");
        exit(1);
    }

    result = iauAtco13 ( rc, dc, pr, pd, px, rv, utc1, utc2, dut1, elong, phi, hm, xp, yp, phpa, tc, rh, wl, &aob, &zob, &hob, &dob, &rob, &eo );
    if (result != 0) {
        printf("iauAtco13 call failed\n");
        exit(1);
    }

    double SOFA_JNow_ra  = rob * DR2D; // Radians to degrees
    double SOFA_JNow_dec = dob * DR2D;

    ////////////////////////////////////////////////////////////////////////////////////////////////
    // presentation
    ////////////////////////////////////////////////////////////////////////////////////////////////

    // calculate differences in arc seconds using DD2R and DR2AS from sofam.h 
    double libNOVA_ra_das  = fabs(libNOVA_JNow_ra - ra_center)  * DD2R * DR2AS;
    double libNOVA_dec_das = fabs(libNOVA_JNow_dec - dec_center) * DD2R * DR2AS;
    double NOVAS_ra_das  = fabs(NOVAS_JNow_ra - ra_center)  * DD2R * DR2AS;
    double NOVAS_dec_das = fabs(NOVAS_JNow_dec - dec_center) * DD2R * DR2AS;
    double SOFA_ra_das  = fabs(SOFA_JNow_ra - ra_center)  * DD2R * DR2AS;
    double SOFA_dec_das = fabs(SOFA_JNow_dec - dec_center) * DD2R * DR2AS;

    double libNOVA_NOVAS_ra_das = fabs(NOVAS_JNow_ra - libNOVA_JNow_ra) * DD2R * DR2AS;
    double libNOVA_NOVAS_dec_das = fabs(NOVAS_JNow_dec - libNOVA_JNow_dec) * DD2R * DR2AS;
    double NOVAS_SOFA_ra_das = fabs(NOVAS_JNow_ra - SOFA_JNow_ra) * DD2R * DR2AS;
    double NOVAS_SOFA_dec_das = fabs(NOVAS_JNow_dec - SOFA_JNow_dec) * DD2R * DR2AS;

    printf("                                              Δ J2000         Δ NOVAS \n");
    printf("             ra°             ,dec°            ra″    ,dec″    ra″    ,dec″ \n");
    printf("J2000        %.12f,%.12f\n", ra_center, dec_center);
    printf("libNOVA JNow %.12f,%.12f %.3f,%.3f %7.3f,%7.3f\n", libNOVA_JNow_ra, libNOVA_JNow_dec, libNOVA_ra_das, libNOVA_dec_das, libNOVA_NOVAS_ra_das, libNOVA_NOVAS_dec_das);
    printf("NOVAS   JNow %.12f,%.12f %.3f,%.3f\n", NOVAS_JNow_ra, NOVAS_JNow_dec, NOVAS_ra_das, NOVAS_dec_das);
    printf("SOFA    JNow %.12f,%.12f %.3f,%.3f %.3f,%.3f\n", SOFA_JNow_ra, SOFA_JNow_dec, SOFA_ra_das, SOFA_dec_das, NOVAS_SOFA_ra_das, NOVAS_SOFA_dec_das);

    return(0);
}

