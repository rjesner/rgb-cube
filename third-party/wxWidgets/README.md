# wxWidgets

Download the compressed folder of wxWidgets-3.2.3 and put the uncompressed one inside this directory. Then, build the library.

```shell
$> mkdir cmake-build
$> cd cmake-build
$> cmake -G "MinGW Makefiles" -D wxBUILD_SHARED=ON -D wxBUILD_MONOLITHIC=ON ..
```
