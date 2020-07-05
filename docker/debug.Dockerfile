ARG BASE_CONTAINER=jupyter/datascience-notebook:notebook-6.0.3
ARG COMMIT
FROM $BASE_CONTAINER

# Install requirements and set Jupyter environment
COPY requirements.txt requirements.txt
#WORKDIR /
RUN pip install -r requirements.txt
RUN jupyter contrib nbextension install --user
RUN jt -t chesterish -tfs 11 -nfs 115 -cellw 95% -N
#RUN sudo yum install -y git

# Pass COMMIT to next block
ARG COMMIT

# Install Simfection
RUN git clone https://github.com/simfection/simfection.git && \
    cd simfection && \
    git checkout $COMMIT && \
    python setup.py install
