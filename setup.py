
import setuptools
from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

ext_modules = [
    Extension(
        "network",
        sources=["./simfection/cpp_src/network.pyx"],
        language="c++",
        extra_compile_args=['-std=c++11', '-O3'],
    )
]

with open('README.md', 'r') as fh:
    long_description = fh.read()

with open("requirements.txt") as f:
    requirements = f.readlines()

install_requires = [r.strip() for r in requirements]

setuptools.setup(
    name='simfection',
    version='0.2.0',
    author='Simfection Research Group',
    author_email='simfectiongroup@gmail.com',
    description='A stochastic, interaction-based infectious disease model',
    long_description=long_description,
    long_description_content_type='text/markdown',
    url='https://github.com/simfection/simfection',
    packages=setuptools.find_packages(),
    install_requires=install_requires,
    classifiers=[
        'Programming Language :: Python :: 3',
        'License :: OSI Approved :: MIT License',
    ],
    python_requires='>=3.7',
    entry_points={
        'console_scripts': [
            'simfection = simfection.simulation_run:main'
        ],
    },
    test_suite='nose.collector',
    tests_require=['nose'],
    ext_modules=cythonize(ext_modules)
)
