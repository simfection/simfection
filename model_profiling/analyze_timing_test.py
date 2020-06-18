import os
import pandas as pd
import numpy as np

filepath = './results/'

files = {}
for (dirpath, dirnames, filenames) in os.walk(filepath):
    for filename in filenames:
        this_filepath = dirpath + filename
        name, extension = os.path.splitext(this_filepath)
        if extension == '.csv':
            pop_size = filename.split('_')[3][:-4]
            files[pop_size] = filename
    break

pop_sizes = []
cc_cumtime = []
interact_all_cumtime = []
simulation_run_cumtime = []
for pop_size, filename in sorted(files.items()): 
    columns = ['ncalls', 'tottime', 'tottime_percall','cumtime','cumtime_percall','function_call']
    df = pd.read_csv(filepath + filename, header=0, names=columns)
    function_column = 'function_call'

    create_connections = '../simfection/connection_engine.py:175(create_connections)'
    interact_all = '../simfection/interaction_engine.py:154(interact_all)'
    simulation_run = '../simfection/simulation_run.py:46(run)'

    cc_query = function_column + ' == \'' + create_connections + '\''
    interact_all_query = function_column + ' == \'' + interact_all + '\''
    simulation_run_query = function_column + ' == \'' + simulation_run + '\''

    pop_sizes.append(int(pop_size))
    # These are pd.Series, so we'll actually grab the value out of the pd.Series
    for value in df.query(cc_query)['cumtime_percall']:
        cc_cumtime.append(value)
    for value in df.query(interact_all_query)['cumtime_percall']:
        interact_all_cumtime.append(value)
    for value in df.query(simulation_run_query)['cumtime_percall']:
        simulation_run_cumtime.append(value)

# Exoprt the dataframe with the results to csv:
data = {'pop_size': pop_sizes, 
        'create_connections_runtime_seconds': cc_cumtime, 
        'interact_all_runtime_seconds': interact_all_cumtime,
        'simulation_run_runtime_seconds': simulation_run_cumtime,
}
results = pd.DataFrame(data)

results.to_csv('./timing_results.csv')