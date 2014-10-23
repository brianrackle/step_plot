plot \
     "{DAT}" index {0} title "Event" with points lc 1 ps 4 pt 3,\
     '' index {1} title "Radial" with linespoints lc 2 lw 2 pt 6,\
     '' index {2} title "Status" with linespoints lc 0 lw 1 pt 2,\
     '' index {2} using 1:2:(sprintf("%.15f,  %.15f", $1, $2)) with labels,