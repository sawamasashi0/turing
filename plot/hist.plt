reset
set term gif enhanced animate delay 10 optimize size 500, 500
sim="sim_001"
data_file="2021.01.28"
set output "../figures/test_".sim.".gif"
set tics font "Times-Roman,21"   # 目盛りのフォントの変更
set ylabel font "Times-Roman,25" # ylabelのフォントの変更
set xlabel font "Times-Roman,25" # xlabelのフォントの変更
set bmargin 0
set lmargin 0
set rmargin 0
set tmargin 0
unset border
set xtics nomirror
set ytics nomirror
set format x "" 
set format y ""
set size ratio -1
unset colorbox
load "gnuplot-palettes-master/blues.pal"
do for[i=1:1000:1]{
    filename =sprintf('../test/test/hist_'.sim.'_%04d.dat', i)
    p filename u 1:2:3 ps 0.8 pt 5 lc palette notitle
}
rep
set terminal qt
set output
