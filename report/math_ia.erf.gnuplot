set table "math_ia.erf.table"; set format "%.5f"
set format "%.7e";; set samples 100; set dummy x; plot [x=0:100] 0.4426*x*ln(x)+ 0.25*x**2 - 44.0429*x + 2850;
