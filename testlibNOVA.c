#include <stdio.h>
#include <math.h>
#include <libnova/libnova.h>

int main(int argc, char **argv) {

    // from astrometry wcs
    double ra_center = 345.986294056;
    double dec_center = 28.1503891981;

    struct ln_equ_posn mean_position;
    struct ln_equ_posn position;

    mean_position.ra  = ra_center;
    mean_position.dec = dec_center;

    double JNow = ln_get_julian_from_sys();
//    JNow = 2457933.390539764427;
    printf("JNow  %.12f\n", JNow);

    ln_get_equ_prec2(&mean_position, JD2000, JNow, &position);

    double JNow_ra  = position.ra;
    double JNow_dec = position.dec;

    printf("J2000 ra,dec %.12f , %.12f\nJNow  ra,dec %.12f , %.12f\n", ra_center, dec_center, JNow_ra, JNow_dec);

    return(0);
}

