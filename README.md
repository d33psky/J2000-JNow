# J2000-JNow
Compare libraries providing J2000 to JNow for astrometry

example-output :
```
./comparelibNOVA-NOVAS-SOFA
libNOVA UTC JNow  2457936.092064388096
NOVAS   TT  JNow  2457936.092865129001
                                              Δ J2000         Δ NOVAS
             ra°             ,dec°            ra″    ,dec″    ra″    ,dec″
J2000        345.986294056000,28.150389198100
libNOVA JNow 346.197927917663,28.244953025450 761.882,340.430   0.001,  0.032
NOVAS   JNow 346.197928300251,28.244944117476 761.883,340.398
SOFA    JNow 346.043243809592,28.284716103300 205.019,483.577 556.864,143.179
```
