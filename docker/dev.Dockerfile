ARG BASE_CONTAINER=jupyter/datascience-notebook:notebook-6.0.3
FROM $BASE_CONTAINER

RUN pip uninstall notebook -y && \
    pip install notebook==5.7.8 && \
    pip install autopep8 && \
    pip install jupyter_contrib_nbextensions && \
    jupyter contrib nbextension install --user && \
    pip install jupyterthemes && \
    pip install nose && \ 
    jt -t chesterish -tfs 11 -nfs 115 -cellw 95% -N

RUN git clone https://github.com/simfection/simfection.git && \
    cd simfection && \
    git checkout develop && \
    python setup.py install
