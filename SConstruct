import os

env = Environment(
    ENV = os.environ,
    CXXFLAGS= ['-g', '-Wall', '-Wextra', '-pedantic-errors', '-std=c++17'],
    LIBPATH='.')

env.Library('linked_list', ['linked_list.cpp'])
env.Program('test_linked_list', ['test_linked_list.cpp', 'test_main.cpp'], LIBS=['linked_list'])
