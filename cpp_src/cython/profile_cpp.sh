#!/bin/bash

# build the program; For our demo program, we specify -DWITHGPERFTOOLS to enable the gperftools specific #ifdefs
g++ -std=c++11 -DWITHGPERFTOOLS -lprofiler -g -Wl,--no-as-needed -lprofiler -Wl,--as-needed ./simfection_cpp.cpp -o simfection

# run the program; generates the profiling data file (profile.log in our example)
./simfection

# generate the simfection.prof file 
LD_PRELOAD=libprofiler.so CPUPROFILE=./simfection.prof CPUPROFILESIGNAL=12 ./simfection

# open call graph
google-pprof --web ./simfection simfection.prof

