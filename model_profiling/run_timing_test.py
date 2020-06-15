# TODO(aogle): Implement the following for execution time, CPU utilization, and memory profiling:
# https://stackoverflow.com/questions/13507205/finding-memory-usage-cpu-utilization-execution-time-for-running-a-python-scrip
# Helpful for visualizing: 
# https://stackoverflow.com/questions/582336/how-can-you-profile-a-python-script

import cProfile
import pstats, math
import os
import io
import pandas as pd
import argparse

from connection_engine_profiler import ConnectionEngineProfiler
 

class RunTimingTest:
    def __init__(self, pop_range=range(0,1000,100)):
        self.pop_range = pop_range

    def output_results(self, filename, results_dir='./results/'):
        result = io.StringIO()

        pstats.Stats(self.pr,stream=result).sort_stats('cumulative').print_stats()
        result=result.getvalue()
        # Chop the string into a csv-like buffer
        result='ncalls'+result.split('ncalls')[-1]
        result='\n'.join([','.join(line.rstrip().split(None,5)) for line in result.split('\n')])
        # Save it to file
        # Make sure the results folder exists
        if(not os.path.isdir(results_dir)):
            os.mkdir('./results/')
        filepath = results_dir + filename
        with open(filepath, 'w+') as f:
            f.write(result)
            f.close()

    def run(self):
        count = 0
        for pop_size in self.pop_range:
            # For each population size, run a timing test and output
            # the results to its own specific csv file.
            self.pr = cProfile.Profile()
            profiler = ConnectionEngineProfiler(pop_size=pop_size)
            self.pr.enable()
            profiler.run_single_pop_test()
            self.pr.disable()
            profiler.tearDown()

            # Write out the results to a file
            filename = "timing_" + "pop_size_" + str(pop_size) + ".csv"
            self.output_results(filename)
            count += 1
            percent_complete = (count / len(self.pop_range)) * 100
            print(f'timing test percent complete: {percent_complete}')

def _get_parser(arguments):
    parser = argparse.ArgumentParser()
    for names, args in arguments.items():
        parser.add_argument(*names, **args)
    return parser


timing_test_args = {
    ('-pr', '--pop_range'): {
        'help': (
            'population range to run timing tests over, including step size, like: <start>,<stop>,<step_size> \n(default: 100,1000,100)'
        ),
        'type': str,
        'default': '10,100,10',
        'required': False
    },
}

def main():
    parser = _get_parser(timing_test_args)
    args = parser.parse_args()
    pop_range = args.pop_range
    # convert pop_range list values to integers
    pop_range_list = [int(i) for i in pop_range.split(',')]
    start, stop, step_size = pop_range_list
    timing_test = RunTimingTest(range(start, stop + step_size, step_size))
    timing_test.run()

if __name__ == '__main__':
    main()

