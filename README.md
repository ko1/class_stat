# ClassStat

Collect statistics about Class and Modules.

## Installation

Add this line to your application's Gemfile:

```ruby
gem 'class_stat'
```

And then execute:

    $ bundle

Or install it yourself as:

    $ gem install class_stat

## Usage

Please add this line into your application.

```ruby
require 'class_stat/setup'
```

And you will have a statistics result at the end of application.

All of result puts on STDOUT. If you want to store it into a file,
then use 'CLASS_STAT_FILE' environment variable.

```
$ CLASS_STAT_FILE=/tmp/class_stat_result ruby ...
```

Please send your result to Koichi Sasada <ko1@atdot.net>.
This information will help me to improve MRI.

## Contributing

1. Fork it ( https://github.com/[my-github-username]/class_stat/fork )
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create a new Pull Request
