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
            pop_size = filename.split('_')[3]
            files[pop_size] = filename
    break

pop_sizes = []
cc_cumtime = []
make_dummy_cumtime = []
for pop_size, filename in sorted(files.items()): 
    columns = ['ncalls', 'tottime', 'tottime_percall','cumtime','cumtime_percall','function_call']
    df = pd.read_csv(filepath + filename, header=0, names=columns)
    function_column = 'function_call'
    create_connections = '../simfection/connection_engine.py:175(create_connections)'
    make_dummy = '../simfection/population_engine.py:72(make_dummy)'
    cc_query = function_column + ' == \'' + create_connections + '\''
    make_dummy_query = function_column + ' == \'' + make_dummy + '\''

    pop_sizes.append(int(pop_size))
    # These are pd.Series, so we'll actually grab the value out of the pd.Series
    for value in df.query(cc_query)['cumtime_percall']:
        cc_cumtime.append(value)
    for value in df.query(make_dummy_query)['cumtime_percall']:
        make_dummy_cumtime.append(value)

# Exoprt the dataframe with the results to csv:
data = {'pop_size': pop_sizes, 
        'create_connections runtime (s)': cc_cumtime, 
        'population.make_dummy runtime (s)': make_dummy_cumtime}
results = pd.DataFrame(data)

results.to_csv('./timing_results.csv')