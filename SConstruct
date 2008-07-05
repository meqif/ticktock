"""
Set up install path.
"""
prefix = ARGUMENTS.get('prefix', '/usr/local')
install_dir = prefix + '/bin'

"""
Set up environment.
"""
env = Environment()
env['CFLAGS'] = Split('-Os -Wall')

"""
Compile the program.
"""
ticktock = env.Program('ticktock.c')

"""
Install the program.
"""
env.Install(install_dir, ticktock)

env.Alias('install', install_dir)

# vim: filetype=python
