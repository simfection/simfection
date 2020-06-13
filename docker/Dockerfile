ARG BASE_CONTAINER=jupyter/datascience-notebook:notebook-6.0.3
FROM $BASE_CONTAINER

RUN python3 -m pip uninstall notebook -y && \
    python3 -m pip install notebook==5.7.8 && \ # Extension not yet compatible with v6.x
    python3 -m pip install --upgrade pandas && \
    python3 -m pip install boto3  && \
    python3 -m pip install autopep8 && \
    python3 -m pip install missingpy && \
    python3 -m pip install pyarrow && \
    python3 -m pip install jupyter_contrib_nbextensions && \
    jupyter contrib nbextension install --user && \
    python3 -m pip istall awscli && \
    python3 -m pip install jupyterthemes && \
    jt -t chesterish -tfs 11 -nfs 115 -cellw 95% -N

RUN git clone https://github.com/simfection/simfection.git && \
    cd simfection && \
    python3 setup.py install
