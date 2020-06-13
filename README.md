# Simfection

Simfection is an open-source, stochastic, interactions-based infectious disease model.

# Getting Started

## Requirements
`simfection` has only been tested with Python 3.7.

## Installing from PyPI

It is recommended that you install `simfection` in a virtual environment. A great place to keep your virtual environments is in a `$HOME/.venv/` directory. If you do not already have such a directory, (1) navigate to your home directory, (2) create it, and (3) enter into the directory.

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

To execute a model run, (1) change our of the `.venv` directory and (2) execute `simfection`.

```shell
cd $HOME
simfection
```
