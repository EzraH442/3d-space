project('3d-space', 'cpp')

sfml_dep = dependency('sfml-all')

include = include_directories('include')

subdir('src')

dep = declare_dependency(include_directories: include, sources: foo_sources, dependencies: sfml_dep)

executable('3d-space', 'main.cpp', dependencies: [dep])
