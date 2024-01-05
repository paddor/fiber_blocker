# frozen_string_literal: true

require "bundler/gem_tasks"
require "minitest/test_task"

Minitest::TestTask.create

require "rake/extensiontask"

task build: :compile

GEMSPEC = Gem::Specification.load("fiber_blocker.gemspec")

Rake::ExtensionTask.new("fiber_blocker", GEMSPEC) do |ext|
  ext.lib_dir = "lib/fiber_blocker"
end

task default: %i[clobber compile]
