import resource
import argparse
import pandas as pd
from concurrent.futures import ThreadPoolExecutor
from time import sleep


from connection_engine_profiler import ConnectionEngineProfiler

class MemoryMonitor:
    def __init__(self):
        self.keep_measuring = True

    def measure_usage(self):
        max_usage = 0
        while self.keep_measuring:
            max_usage = max(
                max_usage,
                resource.getrusage(resource.RUSAGE_SELF).ru_maxrss
            )
            sleep(0.1)

        return max_usage

class RunMemoryTest:
    def __init__(self, pop_range=range(0,100,10)):
        self.pop_range = pop_range

    def output_results(self, filename, results_dir='./'):
        self.results.to_csv(results_dir + filename)

    def run(self):
        pop_sizes = []
        max_usages = []
        for pop_size in self.pop_range:
            # For each population size, run a memory test and output
            # the results to its own specific csv file.
            profiler = ConnectionEngineProfiler(pop_size)
            with ThreadPoolExecutor() as executor:
                monitor = MemoryMonitor()
                mem_thread = executor.submit(monitor.measure_usage)
                try:
                    fn_thread = executor.submit(profiler._single_pop_experiment)
                    result = fn_thread.result()
                finally:
                    monitor.keep_measuring = False
                    max_usage = mem_thread.result()
                    profiler.tearDown()
            pop_sizes.append(pop_size)
            max_usages.append(max_usage)
        data = {'pop_sizes': pop_sizes, 
                   'max_usages': max_usages}
        self.results = pd.DataFrame(data)

        # Write out the results to a file
        filename = "memory_results.csv"
        self.output_results(filename)

def _get_parser(arguments):
    parser = argparse.ArgumentParser()
    for names, args in arguments.items():
        parser.add_argument(*names, **args)
    return parser


memory_test_args = {
    ('-pr', '--pop_range'): {
        'help': (
            'population range to run timing tests over, including step size, like: <start>,<stop>,<step_size> \n(default: 10,100,10)'
        ),
        'type': str,
        'default': '10,100,10',
        'required': False
    },
}

def main():
    parser = _get_parser(memory_test_args)
    args = parser.parse_args()
    pop_range = args.pop_range
    # convert pop_range list values to integers
    pop_range_list = [int(i) for i in pop_range.split(',')]
    start, stop, step_size = pop_range_list
    memory_test = RunMemoryTest(range(start, stop + step_size, step_size))
    memory_test.run()

if __name__ == '__main__':
    main()