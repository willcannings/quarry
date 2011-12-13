require 'mkmf-rice'

QUARRY_H      = 'quarry.h'
MARKER        = 'mkmf_marker'
cflags        = '-x c++'
quarry_dir    = File.join(File.dirname(__FILE__), '..', 'lib', 'quarry')
quarry_obj    = File.join(quarry_dir, 'obj')
quarry_src    = File.join(quarry_dir, 'src')
quarry_header = File.join(quarry_src, QUARRY_H)

# compile quarry as a static lib
Dir.chdir(quarry_dir) do
  if RUBY_PLATFORM =~ /darwin/
    puts "Compiling quarry (OS X mode)"
    `make -f Makefile.osx clean`
    `make -f Makefile.osx`
  else
    cflags += ' -std=gnu++0x -Wno-multichar -frtti'
    puts "Compiling quarry (linux mode)"
    `make -f Makefile.linux clean`
    `make -f Makefile.linux`
  end
end

# the cflags are required to make mkmf compile in c++ mode
with_cflags(cflags) do
  find_header(QUARRY_H, quarry_src)
  $LIBPATH << quarry_obj
  have_library('quarry', MARKER, quarry_header)
  create_makefile('quarry_toolkit', 'quarry')
end
