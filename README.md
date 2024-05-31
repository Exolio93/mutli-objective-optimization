Compilation and execution with MinGW:

cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
dev.exe


##############################################

Dijkstra dim = 2 :
------------------
50 graphs | 100 nodes | 50% of arcs

Random choice for pivot : ~8,3s
it choice for pivot : ~10,00s


#############################################
Test :
Measure of the number of passages in the while loop for the 20 instances of graphs (N = 50, rho =0.5, val_max = 20) : 

----RANDOM
number of passages in while loop:
658 1031 748 729 799 798 793 880 984 739 
922 1014 712 841 738 1264 759 898 615 930
mean : 860
number of labels processed :
18858 23681 17599 20482 20896 20562 17608 25163 22464 17853 
20099 29849 14227 15879 22634 24938 22717 22546 16762 19764 
mean : 21100
total time : 1,4s

---- LEXICOGRAPHIC 
number of passages in while loop:
397 640 503 484 554 397 464 591 607 451 
610 659 398 434 557 546 611 474 479 607
mean : 555
number of label processed : 
10481 15522 12151 12413 13160 10017 11316 14884 14511 11612 
15755 16637 9737 10714 14120 13839 16006 11834 11779 16089
mean : 13400
total time : 2,4s

---- FORMER ALGORITHM
number of passages in while loop :
184 305 200 151 191 291 214 218 224 180 
194 207 196 180 208 207 240 202 188 198
number of labels processed :
17409 43237 25791 17551 27292 24654 25586 29393 36069 22840 
27301 33129 18749 23502 34811 24732 31846 30690 23008 35188
mean : 27400
total time : 0,8s





