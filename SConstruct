"""
Set version.
"""
version = "0.2"

"""
Set up options.
"""
opts = Options()
opts.AddOptions(
  ('prefix', 'install architecture-independent files in', '/usr/local'),
  ('bindir', 'user executables', 'PREFIX/bin'),
)

"""
Set up environment.
"""
env = Environment(options = opts)
Help(opts.GenerateHelpText(env))
env['CFLAGS'] = Split('-Os -Wall')
env.Append(CFLAGS = ['-DVERSION=\\"%s\\"' % version])

"""
Set up install path.
"""
prefix  = env['prefix']
bin_dir = env['bindir'].replace('PREFIX', prefix)

"""
Compile the program.
"""
ticktock = env.Program('ticktock.c')

"""
Install the program.
"""
env.Install(bin_dir, ticktock)

env.Alias('install', prefix)

# vim: filetype=python
