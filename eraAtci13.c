#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include <erfa.h>

int main(int argc, char **argv) {

    if (argc != 3) {
        printf("need ra dec\n");
        exit(1);
    }
    int result = 0;
    int   J2000_ra_ideg;
    int   J2000_ra_iamin;
    float J2000_ra_asec;
    sscanf(argv[1], "%d:%d:%g", &J2000_ra_ideg, &J2000_ra_iamin, &J2000_ra_asec);
    double J2000_ra; // in radians
    result = eraAf2a('+', J2000_ra_ideg, J2000_ra_iamin, (double) J2000_ra_asec, &J2000_ra);
    if (result != 0) {
        printf("eraAf2a call failed with %d\n", result);
        exit(1);
    }
    char  J2000_dec_sign;
    int   J2000_dec_ideg;
    int   J2000_dec_iamin;
    float J2000_dec_asec;
    sscanf(argv[2], "%c%d:%d:%g", &J2000_dec_sign, &J2000_dec_ideg, &J2000_dec_iamin, &J2000_dec_asec);
    double J2000_dec; // in radians
    result = eraAf2a(J2000_dec_sign, J2000_dec_ideg, J2000_dec_iamin, (double) J2000_dec_asec, &J2000_dec);
    if (result != 0) {
        printf("eraAf2a call failed with %d\n", result);
        exit(1);
    }

//    // from astrometry wcs
//    double ra_center = 345.986294056;
//    double dec_center = 28.1503891981;
    double ra_center = J2000_ra * ERFA_DR2D;
    double dec_center = J2000_dec * ERFA_DR2D;

    // SOFA http://www.iausofa.org/sofa_ast_c.pdf
    // https://github.com/liberfa/erfa/blob/master/src/atci13.c
    // eraAtci13 Given :
    double rc, dc; // ICRS [ α, δ ] at J2000.0 (radians, Note 1)
    double pr = 0.0;     // RA proper motion (radians/year; Note 2)
    double pd = 0.0;     // Dec proper motion (radians/year)
    double px = 0.0;     // parallax (arcsec)
    double rv = 0.0;     // radial velocity (km/s, positive if receding)
    double date1;   // TDB as a 2-part. . .
    double date2;   // . . . Julian Date (Note 3)
    // iauAtci13 Returned :
    double ri, di; // * CIRS geocentric RA,Dec (radians)
    double eo;     // * equation of the origins (ERA-GST, Note 5)

//    rc = ERFA_DD2R * ra_center; // Degrees to radians
//    dc = ERFA_DD2R * dec_center;
    rc = J2000_ra;
    dc = J2000_dec;

    time_t tsec;
    struct tm *ts;
    double utc1;   // UTC as a 2-part. . .
    double utc2;   // . . . quasi Julian Date (Notes 3,4)
    tsec = time(0); // number of seconds since the Epoch, 1970-01-01 00:00:00 +0000 (UTC)    
    ts = gmtime(&tsec);
    result = eraDtf2d ( "UTC", ts->tm_year+1900, ts->tm_mon+1, ts->tm_mday, ts->tm_hour, ts->tm_min, ts->tm_sec, &utc1, &utc2 );
    if (result != 0) {
        printf("eraDtf2d call failed\n");
        exit(1);
    }

    // Make TT julian date for Atci13 call
    double tai1, tai2;
    double tt1, tt2;
    result = eraUtctai( utc1, utc2, &tai1, &tai2 );
    if (result != 0) {
        printf("eraUtctai call failed\n");
        exit(1);
    }
    eraTaitt(  tai1, tai2, &tt1,  &tt2  );
    // don't bother checking result, always returns 0

    eraAtci13 ( rc, dc, pr, pd, px, rv, tt1, tt2, &ri, &di, &eo );

    double JNow_ra  = eraAnp(ri - eo) * ERFA_DR2D; // Convert CIO RA to equinox of date RA by subtracting the equation of the origins, Radians to degrees
    double JNow_dec = di * ERFA_DR2D;
    printf("J2000 ra,dec %.12f , %.12f\nJNow  ra,dec %.12f , %.12f\n", ra_center, dec_center, JNow_ra, JNow_dec);

    // Decompose radians into degrees, arcminutes, arcseconds, fraction.
    char ra_sign;
    int ra_idmsf[4];
    eraA2af(2, eraAnp(ri - eo), &ra_sign, ra_idmsf);
//    printf("JNow ra  %03d:%02d:%02d.%02d\n", ra_idmsf[0], ra_idmsf[1], ra_idmsf[2], ra_idmsf[3]);
    char dec_sign;
    int dec_idmsf[4];
    eraA2af(2, di, &dec_sign, dec_idmsf);
//    printf("JNow dec %c%02d:%02d:%02d.%02d\n", dec_sign, dec_idmsf[0], dec_idmsf[1], dec_idmsf[2], dec_idmsf[3]);
    printf("J2000 ra,dec  %s , %s\n", argv[1], argv[2]);
    printf("JNow  ra,dec  %d:%02d:%02d.%02d , %c%02d:%02d:%02d.%02d\n",
           ra_idmsf[0], ra_idmsf[1], ra_idmsf[2], ra_idmsf[3],
           dec_sign, dec_idmsf[0], dec_idmsf[1], dec_idmsf[2], dec_idmsf[3]);

    return(0);
}

