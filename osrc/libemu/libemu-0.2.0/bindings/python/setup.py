#!/usr/bin/python

from distutils.core import setup, Extension

libemu = Extension('libemu',
                    sources = ['libemu_module.c'],
                    include_dirs = ['${prefix}/include'],
                    library_dirs = ['${exec_prefix}/lib'],
                    libraries = ['emu'],
                    )

setup (name = 'libemu',
       version = '0.2.0',
       description = 'Python interface to the libemu x86 emulator.',
       author = 'Georg Wicherski',
       author_email = 'gw@mwcollect.org',
       url = 'http://libemu.mwcollect.org/',
       ext_modules = [libemu])
