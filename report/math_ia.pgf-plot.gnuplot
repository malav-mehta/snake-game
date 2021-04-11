set table "math_ia.pgf-plot.table"; set format "%.5f"
set format "%.7e";; set samples 100; set dummy x; plot [x=0:100] 350*erf(5.0*(20*x-463.0)/(599.0*sqrt(2))) + 0.4426*x*log(x) + 0.25*x**2 - 44.0429*x + 2850;
