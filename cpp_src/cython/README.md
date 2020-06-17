Note to self for writing the Cython .pyx and .pyd files later:

Check out the following for ideas on using std::pair in Cython:
http://tillahoffmann.github.io/2016/04/18/Cpp-containers-in-cython.html

BUGS:
- The Interactions object doesn't update anything in the infectedByList of its Population object.
    I don't think my getter and setter functions are working correctly :( Will fix later. 