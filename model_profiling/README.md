# Profiling Modules

Currently the process for profiling module execution time goes like this:
1. Create a module profiler which sets up the module and has a function defined for running a single execution of the module. 
2. Use RunTimingTest class to setup the profiler and provide CLI access for running the experiment. 
3. Run run_timing_test.py from the CLI
4. Run analyze_timing_test.py from the CLI to aggregate the results into a single file
5. Examine results CSV in spreadsheet program

To start a timing test, run:
$ python3 run_timing_test.py -r=10 -pr=100,1000,100

For explanations on the flags, run:
$ python3 run_timing_test.py --help