# frozen_string_literal: true

require_relative "fiber_blocker/version"
require_relative "fiber_blocker/fiber_blocker"
require_relative "fiber_blocker/ruby_test_fiber_scheduler"

module FiberBlocker
  class Error < StandardError; end
end
