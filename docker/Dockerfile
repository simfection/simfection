ARG BASE_CONTAINER=jupyter/datascience-notebook:notebook-6.0.3
FROM $BASE_CONTAINER

# Update
RUN apt-get update

# Install Python 3.7
# Ref: https://tecadmin.net/install-python-3-7-on-ubuntu-linuxmint/
#RUN apt-get install -y build-essential checkinstall # Doesn't seem to be needed for geopatial 3.6.2
RUN apt-get install -y libreadline-gplv2-dev libncursesw5-dev libssl-dev libsqlite3-dev tk-dev libgdbm-dev libc6-dev libbz2-dev libffi-dev zlib1g-dev
RUN cd /usr/src && \
    wget https://www.python.org/ftp/python/3.7.3/Python-3.7.3.tgz && \
    tar xzf Python-3.7.3.tgz && \
    cd Python-3.7.3 && \
    ./configure --enable-optimizations && \
    make altinstall
