# Generic Linked List
A generic linked list implemented with a template

## Get catch

First, if you don't already have catch.hpp in your include path,
get the single-include catch header by running

```
wget -c https://github.com/catchorg/Catch2/releases/download/v2.5.0/catch.hpp
```

## Testing with bazel

WORKSPACE and BUILD are for bazel

Get bazel from the apt sources using [these directions](https://docs.bazel.build/versions/master/install-ubuntu.html#install-on-ubuntu).

To test:
```
bazel test --test_output=all --run_under=valgrind :test_linked_list
```

Though this is the easiest, it won't show colored output from the catch tests.
To get colored output you'll have to run the binary directly:

```
bazel build :test_linked_list && valgrind ./bazel-bin/test_linked_list
```

## Testing with scons

SConstruct is for scons.
Install scons with

```
sudo apt install scons
```


Then to build and run the test:

```
scons test_linked_list && valgrind ./test_linked_list
```
