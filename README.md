# J2000-JNow
Compare libraries providing J2000 to JNow for astrometry

example-output :
```
./testAstropy.py
Julian date: 2457939.37702610
Astropy JNOW (RA,Dec in degrees): 346.19803710,28.24499310

./comparelibNOVA-NOVAS-SOFA-ERFA
libNOVA UTC JNow  2457939.377027183305
NOVAS   TT  JNow  2457939.377827924211
                                                   Δ J2000             Δ NOVAS             Δ SOFA Atco13
                  ra°             ,dec°            ra″      ,dec″      ra″      ,dec″      ra″      ,dec″
J2000             345.986294056000,28.150389198100
libNOVA equ_prec2 346.198036730897,28.245001652639   762.274,  340.605    -0.001,    0.032   728.542,  -85.017
NOVAS precession  346.198037120057,28.244992738192   762.275,  340.573                       728.543,  -85.050
SOFA Atci13       346.199762382022,28.242610508506   768.486,  331.997     6.211,   -8.576   734.754,  -93.626
SOFA Atco13       345.995664054232,28.268617623628    33.732,  425.622  -728.543,   85.050
SOFA Atco13 NO eo 345.773721053797,28.268617623628  -765.263,  425.622 -1527.538,   85.050  -798.995,    0.000
ERFA Atco13       345.995664057255,28.268617625268    33.732,  425.622  -728.543,   85.050     0.000,    0.000
```
