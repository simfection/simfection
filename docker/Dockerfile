ARG BASE_CONTAINER=jupyter/datascience-notebook:notebook-5.7.8
FROM $BASE_CONTAINER

RUN pip install jupyter_contrib_nbextensions && \
    jupyter contrib nbextension install --user && \
    pip install jupyterthemes && \
    jt -t chesterish -tfs 11 -nfs 115 -cellw 95% -N

RUN git clone https://github.com/simfection/simfection.git && \
    cd simfection && \
    python setup.py install
