#!/usr/local/bin/python

import os
import os.path

def filtered_glob(env, pattern, omit=[],
  ondisk=True, source=False, strings=False):
    return filter(
      lambda f: os.path.basename(f.path) not in omit,
      env.Glob(pattern))


env = Environment(ENV = os.environ,
                  CPPPATH = ['src'],
                  CPPDEFINES = ['WIN32'])

env.AddMethod(filtered_glob, "FilteredGlob");

libs = ['sfml-graphics', 'sfml-window', 'sfml-system', 'opengl32']

sources  = env.Glob('src/*cpp')
sources += env.Glob('src/Box2D/Collision/*cpp')
sources += env.Glob('src/Box2D/Collision/Shapes/*cpp')
sources += env.Glob('src/Box2D/Common/*cpp')
sources += env.Glob('src/Box2D/Dynamics/*cpp')
sources += env.Glob('src/Box2D/Dynamics/Contacts/*cpp')
sources += env.Glob('src/Box2D/Dynamics/Joints/*cpp')
sources += env.Glob('src/Box2D/Rope/*cpp')
sources += env.FilteredGlob('IMGUI/src/*cpp', ['main.cpp'])

env.Program('demo', sources, LIBS=libs)
