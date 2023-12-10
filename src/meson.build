
sokol_dep = subproject('sokol').get_variable('sokol_dep')

src = ['main.cpp']
executable('daydream', sources : src, override_options : ['cpp_std=c++20'], dependencies : sokol_dep)
