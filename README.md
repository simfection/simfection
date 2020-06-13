# Simfection

Simfection is an open-source, stochastic, interactions-based infectious disease model.

# Getting Started

## Requirements
`simfection` has only been tested with Python 3.7.

## Using the Official Docker

First, pull the latest version of the docker image.

```shell
docker pull simfection/simfection:latest
```
Run the docker container, including a (2) port for the Jupyter notebooks.

```shell
docker run -d \
-p 8888:8888 \
-v $(pwd)/simfection_run:/home/jovyan/simfection_run \
--user root \
-e GRANT_SUDO=yes \
--name simfection \
simfection/simfection:latest start.sh jupyter notebook --NotebookApp.token=''
```

To execute a model run, use the following code. Replace `simfection -h` with any
command line command.

```shell
docker exec simfection bash -c 'simfection -h'
```

## Installing from PyPI

It is recommended that you install `simfection` in a virtual environment. A great place to keep your virtual environments is in a `$HOME/.venv/` directory. (The `.` prefix makes the directory [hidden](https://en.wikipedia.org/wiki/Hidden_file_and_hidden_directory).) If you do not already have such a directory, (1) navigate to your home directory, (2) create it, and (3) enter into the directory.

```shell
cd $HOME # $HOME may not be a defined variable for you. If not, navigate home.
mkdir .venv
cd .venv
```

First, (1) create the a virtual environment called `simfection` using the `venv` module. Next (2) activate the virtual environment and (3) install `simfection`. Finally, (4) copy the command line executable to your main environment and (5) deactivate the birtual environment. (Note: you may need to change the final path `/usr/local/bin` if you are running Windows.)

```shell
python3 -m venv simfection
source simfection/bin/activate
pip3 install simfection
cp simfection/bin/simfection /usr/local/bin/
deactivate
```
Installing `simfection` into a virtual environment and then making it accessible from within your main environment avoids any version conflicts with `simfection`'s dependencies.

## Confirm Installation

To confirm that `simfection` was successfully installed, execute `simfection -h` at command line. You should see a list of available parameters.

To run the default parameters, execute `simfection` at command line. You should output from the model print to your screen. When the run is finished, there will be a new directory called `simfection_run` in your current working directory.
