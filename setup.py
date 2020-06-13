
import setuptools

with open('README.md', 'r') as fh:
    long_description = fh.read()


setuptools.setup(
    name='simfection',
    version='0.0.5',
    author='Grant Vermillion',
    author_email='grant.cates@gmail.com',
    description='A stochastic, interaction-based infectious disease model',
    long_description=long_description,
    long_description_content_type='text/markdown',
    url='https://github.com/simfection/simfection',
    packages=setuptools.find_packages(),
    requirements=[
        'pandas==1.0.4',
        'PyYAML>=5.0.0',
    ],
    classifiers=[
        'Programming Language :: Python :: 3',
        'License :: OSI Approved :: MIT License',
    ],
    python_requires='>=3.7',
    entry_points={
        'console_scripts': [
            'simfection = simfection.simulation_run:main'
        ]
    }
)
