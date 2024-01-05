# frozen_string_literal: true

require "test_helper"

class TestFiberBlocker < Minitest::Test
  def test_hello
    assert_equal 'Hello from FiberBlocker', FiberBlocker.hello
    # puts "FiberBlocker.test works."
  end

  def test_fiber_blocking_in_ruby
    scheduler = Scheduler.new
    Fiber.set_scheduler scheduler

    assert_same scheduler, Fiber.scheduler

    f1 = Fiber.schedule do
      puts "T1 BEGIN"
      scheduler.block("test", 2)
      puts "T1 END"
    end

    f2 = Fiber.schedule do
      puts "T2 BEGIN"
      sleep 0.5
      scheduler.unblock("test", f1)
    end

    Fiber.scheduler.run
  ensure
    Fiber.set_scheduler nil
  end

  def test_fiber_blocking_in_ext
    scheduler = Scheduler.new
    Fiber.set_scheduler scheduler

    assert_same scheduler, Fiber.scheduler

    f1 = Fiber.schedule do
      puts "T1 BEGIN"

      # FIXME: BUG (Segfault or "fatal: machine stack overflow in critical region")
      # FiberBlocker.block_fiber("test", 2)
      FiberBlocker.block_fiber2(scheduler, "test", 2) # this works

      puts "T1 END"
    end

    f2 = Fiber.schedule do
      puts "T2 BEGIN"
      sleep 0.5
      FiberBlocker.unblock_fiber(scheduler, "test", f1)
    end

    Fiber.scheduler.run
  ensure
    Fiber.set_scheduler nil
  end

  def xtest_fiber_blocker_current_fiber
    scheduler = Scheduler.new
    Fiber.set_scheduler scheduler

    Fiber.schedule do
      # FIXME: BUG (Segfault or "fatal: machine stack overflow in critical region")
      p FiberBlocker_current_fiber_scheduler: FiberBlocker.current_fiber_scheduler
    end
  ensure
    Fiber.set_scheduler nil
  end
end
