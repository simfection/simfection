import signal
import sys
import time
from invoke import run
import pandas as pd

class TimingProfiler:
    def __init__(self, num_runs=100, columns_to_drop=['create_connections_runtime_seconds', 'interact_all_runtime_seconds', 'Unnamed: 0']):
        self.num_runs = num_runs
        self.columns_to_drop = columns_to_drop

    def save_output(self):
        if hasattr(self, 'main_df'):
            self.main_df.to_csv('./profile_timing_results_' + str(self.num_runs) + '_runs.csv')
            print("Profiler output saved.")
        else: 
            print("No output to be saved.")

    def cleanup(self):
        cmd = "rm ./results/* ./timing_results.csv"
        result = run(cmd, hide=True, warn=True)

    def run_profiler(self):
        count = 0
        for i in range(1, self.num_runs + 1):
            start = time.time()
            # Run a set of timing tests
            cmd = "python3 run_timing_test.py -pr=5000,7000,1000 -m=simulation_run"
            result = run(cmd, hide=True, warn=True)

            cmd = "python3 analyze_timing_test.py"
            result = run(cmd, hide=True, warn=True)
            if result.ok:
                # The file timing_results.csv must exist, so aggregate it into a df to output in a single csv later
                if i == 1:
                    self.main_df = pd.read_csv('./timing_results.csv')
                    # Drop unwanted columns
                    for column in self.columns_to_drop:
                        self.main_df = self.main_df.drop(column, axis=1)
                    self.main_df = self.main_df.set_index('pop_size')
                elif i > 1:
                    aux_df = pd.read_csv('./timing_results.csv')
                    # Drop unwanted columns
                    for column in self.columns_to_drop:
                        aux_df = aux_df.drop(column, axis=1)
                    rsuffix = '_run_' + str(i)
                    self.main_df = self.main_df.join(aux_df.set_index('pop_size'), rsuffix=rsuffix)
                # Delete all the results files
                cmd = "rm -r ./results/* ./timing_results.csv ./simfection_run"
                result = run(cmd, hide=True, warn=True)
            else:
                print("Unable to run analyze_timing_test.py")
            count += 1
            percent_complete = (count / self.num_runs) * 100
            print(f'Percent profiling complete: {percent_complete}')
            end = time.time()
            single_runtime = end - start
            estimated_total_runtime = single_runtime * self.num_runs
            remaining_runtime = estimated_total_runtime - single_runtime * i
            print("Remaining profiling runtime: " + str(remaining_runtime/60) + " minutes.")


        self.save_output()
    
    def Exit_gracefully(self, signal, frame):
        print("Exiting the program")
        self.save_output()
        self.cleanup()
        sys.exit(0)

        
if __name__ == '__main__':
    timing_profiler = TimingProfiler(num_runs=100)
    signal.signal(signal.SIGINT, timing_profiler.Exit_gracefully)
    timing_profiler.run_profiler()