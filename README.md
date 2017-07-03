# J2000-JNow
Compare libraries providing J2000 to JNow for astrometry

example-output :
```
./testAstropy.py
Julian date: 2457938.31295110
Astropy JNOW (RA,Dec in degrees): 346.19800210,28.24497710

./comparelibNOVA-NOVAS-SOFA-ERFA
libNOVA UTC JNow  2457938.312951703090
NOVAS   TT  JNow  2457938.313752443995
                                                   Δ J2000             Δ NOVAS             Δ SOFA Atco13
                  ra°             ,dec°            ra″      ,dec″      ra″      ,dec″      ra″      ,dec″
J2000             345.986294056000,28.150389198100
libNOVA equ_prec2 346.198001483768,28.244985901165   762.147,  340.548    -0.001,    0.032  1249.850, -157.642
NOVAS precession  346.198001870798,28.244976988815   762.148,  340.516                      1249.852, -157.675
SOFA Atci13       345.977725508703,28.242537011879   -30.847,  331.732  -792.995,   -8.784   456.857, -166.458
SOFA Atco13       345.850820815757,28.288775468177  -487.704,  498.191 -1249.852,  157.675
ERFA Atco13       345.850820817830,28.288775469726  -487.704,  498.191 -1249.852,  157.675     0.000,    0.000
```
