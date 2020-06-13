ARG BASE_CONTAINER=jupyter/datascience-notebook:notebook-6.0.3
FROM $BASE_CONTAINER

RUN pip uninstall notebook -y && \
    pip install notebook==5.7.8 && \ # Extension not yet compatible with v6.x
    pip install --upgrade pandas && \
    pip install boto3  && \
    pip install autopep8 && \
    pip install missingpy && \
    pip install pyarrow && \
    pip install jupyter_contrib_nbextensions && \
    jupyter contrib nbextension install --user && \
    pip istall awscli && \
    pip install jupyterthemes && \
    jt -t chesterish -tfs 11 -nfs 115 -cellw 95% -N

RUN git clone https://github.com/simfection/simfection.git && \
    cd simfection && \
    python setup.py install
