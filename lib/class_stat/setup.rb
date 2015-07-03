require 'class_stat'
require 'pp'

END{
  file = ENV['CLASS_STAT_FILE']
  $stdout =  open(file, 'w') if file

  iclass, methods = ClassStat.stat
  total_dup = 0
  total_iclasses = 0
  total_methods = 0

  iclass.map{|k, v|
    [k, v, methods[k] * v]
  }.sort_by{|(k, n, t)|
    [-t, k.to_s]
  }.each{|(k, v, t)|
    total_dup += t
    total_iclasses += v
    puts "#{k}\t#{v}\t#{t}"
  }
  puts '-- '

  methods.sort_by{|k, v|
    [-v, k.to_s]
  }.each{|k, v|
    total_methods += v
    puts "#{k}\t#{v}"
  }

  puts '-- '
  puts "total_klasses\t#{methods.size}"
  puts "total_included\t#{iclass.size}"
  puts "total_iclasses\t#{total_iclasses}"
  puts "total_methods\t#{total_methods}"
  puts "total_dup\t#{total_dup}"
}
