{IGNORE:""
PLOT_COUNT = 3}

{VARIABLES:""
DATA_FILE = "{DAT}"}
 
{PLOT:"Standard"
     DATA_FILE index {INDEX:0} title "Event" with points lc 1 ps 4 pt 3,\
     '' index {INDEX:1} title "Radial" with linespoints lc 2 lw 2 pt 6,\
     '' index {INDEX:2} title "Status" with linespoints lc 0 lw 1 pt 2}

{PLOT:"StatusCoords"
     DATA_FILE index {INDEX:0} title "Event" with points lc 1 ps 4 pt 3,\
     '' index {INDEX:1} title "Radial" with linespoints lc 2 lw 2 pt 6,\
     '' index {INDEX:2} title "Status" with linespoints lc 0 lw 1 pt 2,\
     '' index {INDEX:2} title "Coords" using 1:2:(sprintf("%.15f   %.15f", $1, $2)) with labels}

{PLOT:"RadialCoords"
     DATA_FILE index {INDEX:0} title "Event" with points lc 1 ps 4 pt 3,\
     '' index {INDEX:1} title "Radial" with linespoints lc 2 lw 2 pt 6,\
     '' index {INDEX:2} title "Status" with linespoints lc 0 lw 1 pt 2,\
     '' index {INDEX:1} title "Coords" using 1:2:(sprintf("%.15f   %.15f", $1, $2)) with labels}