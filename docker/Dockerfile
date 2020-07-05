ARG BASE_CONTAINER=jupyter/datascience-notebook:notebook-6.0.3
FROM $BASE_CONTAINER

RUN git clone https://github.com/simfection/simfection.git && \
    cd simfection && \
    python setup.py install
RUN jupyter contrib nbextension install --user
RUN jt -t chesterish -tfs 11 -nfs 115 -cellw 95% -N
