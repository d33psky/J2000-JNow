# J2000-JNow
Compare libraries providing J2000 to JNow for astrometry

example-output :
```
./testAstropy.py
Julian date: 2457943.45744910
Astropy JNOW (RA,Dec in degrees): 346.19817210,28.24505310

./comparelibNOVA-NOVAS-SOFA-ERFA
libNOVA UTC JNow  2457943.457450550981
NOVAS   TT  JNow  2457943.458251291886
                                                   Δ J2000             Δ NOVAS             Δ SOFA Atco13
                  ra°             ,dec°            ra″      ,dec″      ra″      ,dec″      ra″      ,dec″
J2000             345.986294056000,28.150389198100
libNOVA equ_prec2 346.198171893533,28.245062055035   762.760,  340.822    -0.001,    0.032   257.624,   39.366
NOVAS precession  346.198172290866,28.245053132545   762.762,  340.790                       257.625,   39.334
SOFA Atci13       346.200314432640,28.242916271123   770.473,  333.097     7.712,   -7.693   265.337,   31.641
SOFA Atco13       346.126609694039,28.234127042381   505.136,  301.456  -257.625,  -39.334
SOFA Atco13 NO r  346.200341996467,28.242875808109   770.573,  332.952     7.811,   -7.838   265.436,   31.496
SOFA Atco13 NO eo 345.904450889408,28.234127042381  -294.635,  301.456 -1057.397,  -39.334  -799.772,    0.000
ERFA Atco13       346.126609697111,28.234127044120   505.136,  301.456  -257.625,  -39.334     0.000,    0.000

```
