from distutils.core import setup, Extension

setup(
    name = "Temperature",
    version = "0.0.0.1",
    description = "Temperature convertion functions",
    author = "Raman Budny",
    ext_modules = [Extension("temperature",
                             sources = ['temperature/tmp_module.c'],
                             # link with asm lib
                             extra_link_args = ['temperature/asm/tmp.o']),],
)
