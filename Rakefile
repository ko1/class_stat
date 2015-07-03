require "bundler/gem_tasks"
require "rake/extensiontask"
require 'rake/testtask'

spec = Gem::Specification.load('class_stat.gemspec')

Rake::ExtensionTask.new("class_stat", spec){|ext|
  ext.lib_dir = "lib/class_stat"
}

Rake::TestTask.new 'test' => 'compile' do |t|
  t.libs << 'test'
  t.pattern = "test/*_test.rb"
end

task :run => 'compile' do
  ruby %q{-I ./lib test.rb}
end
