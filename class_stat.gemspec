# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'class_stat/version'
Gem::Specification.new do |spec|
  spec.name          = "class_stat"
  spec.version       = ClassStat::VERSION
  spec.authors       = ["Koichi Sasada"]
  spec.email         = ["ko1@atdot.net"]
  spec.summary       = %q{Collect statistics about Class and Modules.}
  spec.description   = %q{Collect statistics about Class and Modules.}
  spec.homepage      = "https://github.com/ko1/class_stat"
  spec.license       = "MIT"

  spec.extensions    = %w[ext/class_stat/extconf.rb]
  spec.required_ruby_version = '>= 2.1.0'

  spec.files         = `git ls-files -z`.split("\x0")
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ["lib"]

  spec.add_development_dependency "bundler"
  spec.add_development_dependency "rake", "~> 10.0"
  spec.add_development_dependency "rake-compiler"
  spec.add_development_dependency "minitest", "~> 5.0.0"
end
