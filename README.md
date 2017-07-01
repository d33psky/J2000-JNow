# J2000-JNow
Compare libraries providing J2000 to JNow for astrometry

example-output :
```
./testAstropy.py
<SkyCoord (FK5: equinox=2457936.16843): (ra, dec) in deg
    ( 346.1979308,  28.24494524)>

./comparelibNOVA-NOVAS-SOFA-ERFA
libNOVA UTC JNow  2457936.168433984276
NOVAS   TT  JNow  2457936.169234724715
                                                   Δ J2000         Δ NOVAS
                  ra°             ,dec°            ra″    ,dec″    ra″    ,dec″
J2000             345.986294056000,28.150389198100
libNOVA equ_prec2 346.197930447378,28.244954155946 761.891,340.434   0.001,  0.032
NOVAS precession  346.197930830119,28.244945247822 761.892,340.402
SOFA Atci13       345.977533936405,28.242401931332  31.536,331.246
SOFA Atco13       345.982944420360,28.266809717758  12.059,419.114 773.951, 78.712
ERFA Atco13       345.982944422435,28.266809719124  12.059,419.114 773.951, 78.712
```
