#!/sh/bash

day=5


rm ./png/*.png
rm ./output/*.dat

g++ covid19_simulate.cc -std=c++11 -o covid19_simulate
./covid19_simulate $day

python3 plot.py $day
cd png
convert step*png simulate.gif
cd ..

