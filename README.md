# J2000-JNow
Compare libraries providing J2000 to JNow for astrometry

example-output :
```
./testAstropy.py
<SkyCoord (FK5: equinox=2457936.13422): (ra, dec) in deg
    ( 346.19792967,  28.24494473)>

./comparelibNOVA-NOVAS-SOFA-ERFA
libNOVA UTC JNow  2457936.134221310727
NOVAS   TT  JNow  2457936.135022051632
                                              Δ J2000         Δ NOVAS
             ra°             ,dec°            ra″    ,dec″    ra″    ,dec″
J2000        345.986294056000,28.150389198100
libNOVA JNow 346.197929314096,28.244953649497 761.887,340.432   0.001,  0.032
NOVAS   JNow 346.197929696768,28.244944741440 761.888,340.400
SOFA    JNow 346.001232253098,28.273436127852  53.778,442.969 708.111,102.569
ERFA    JNow 346.001232255176,28.273436129217  53.778,442.969 708.111,102.569
```
