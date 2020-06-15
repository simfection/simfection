import signal
from invoke import run
import pandas as pd


def main():
    num_runs = 100
    columns_to_drop = ['population_make_dummy_runtime_seconds', 'Unnamed: 0']
    data = {}
    count = 0

    for i in range(0, num_runs):
        # Run a set of timing tests
        cmd = "python3 run_timing_test.py -pr=10,1000,10"
        result = run(cmd, hide=True, warn=True)

        cmd = "python3 analyze_timing_test.py"
        result = run(cmd, hide=True, warn=True)
        if result.ok:
            # The file timing_results.csv must exist, so aggregate it into a df to output in a single csv later
            if i == 0:
                main_df = pd.read_csv('./timing_results.csv')
                for column in columns_to_drop:
                    main_df = main_df.drop(column, axis=1)
                main_df = main_df.set_index('pop_size')
            elif i > 0:
                aux_df = pd.read_csv('./timing_results.csv')
                for column in columns_to_drop:
                    aux_df = aux_df.drop(column, axis=1)
                rsuffix = '_run_' + str(i)
                main_df = main_df.join(aux_df.set_index('pop_size'), rsuffix=rsuffix)
            # Delete all the results files
            cmd = "rm ./results/* ./timing_results.csv"
            result = run(cmd, hide=True, warn=True)
        else:
            print("Unable to run analyze_timing_test.py")
        count += 1
        percent_complete = (count / num_runs) * 100
        print(f'percent profiling complete: {percent_complete}')

    main_df.to_csv('./profile_timing_results_' + str(num_runs) + '_runs.csv')

def Exit_gracefully(signal, frame):
    print("Exiting the program. No files will be saved.")
    sys.exit(0)
        
if __name__ == '__main__':
    signal.signal(signal.SIGINT, Exit_gracefully)
    main()