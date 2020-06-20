from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

ext_modules=[
    Extension(
        "network",
        sources=["./cpp_src/network.pyx"],
        language="c++",
        extra_compile_args=['-std=c++11', '-O3'],
    )
]
setup(
    name = "network",
    ext_modules = cythonize(ext_modules)
)
