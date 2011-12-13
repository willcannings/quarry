# -*- encoding: utf-8 -*-
$:.push File.expand_path('../lib', __FILE__)

Gem::Specification.new do |s|
  s.name = "thera"
  s.homepage = "http://github.com/willcannings/quarry"
  s.license = "Public Domain"
  s.summary = "Ruby Data Mining Library"
  s.description = "C++ Data Mining Library for Ruby"
  s.email = "me@willcannings.com"
  s.authors = ["Will Cannings"]
  s.version = '0.0.6'
  s.extensions = ["ext/extconf.rb"]

  s.files         = `git ls-files`.split("\n")
  s.test_files    = `git ls-files -- {test,spec,features}/*`.split("\n")
  s.executables   = `git ls-files -- bin/*`.split("\n").map{ |f| File.basename(f) }
  s.require_paths = ['lib', 'ext']
  
  s.add_runtime_dependency 'rice'
end
