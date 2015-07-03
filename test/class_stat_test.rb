require "minitest/autorun"
require 'class_stat'

class ClassStatTest < Minitest::Test
  def test_classstat
    s = ClassStat.stat
    assert_equal(2, s.size)
    assert_kind_of(Array, s)
    assert_kind_of(Hash, s[0])
    assert_kind_of(Hash, s[1])
  end
end
