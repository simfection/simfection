
import setuptools

with open("README.md", "r") as fh:
    long_description = fh.read()

with open("requirements.txt") as f:
    requirements = f.readlines()

setuptools.setup(
    name="simfection",
    version="0.0.2",
    author="Grant Vermillion",
    author_email="grant.cates@gmail.com",
    description="A stochastic, interaction-based infectious disease model",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/gvermillion/simfection",
    packages=setuptools.find_packages(),
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
    python_requires='>=3.7',
)
