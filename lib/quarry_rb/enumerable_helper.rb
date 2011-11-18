module Quarry
  class EnumerableHelper
    include Enumerable
    attr_reader :size
    
    def initialize(data_set, container, klass, size, get_fn)
      @size = container.send(size)
      @container = container
      @data_set = data_set
      @get_fn = get_fn
      @klass = klass
      
      # because of the way the Ruby GC works, it's easier to store
      # references to enumerated objects here than from the C++ side.
      # by keeping a reference to returned objects in this object,
      # iterated objects that shouldn't be released (e.g Examples)
      # won't be until the data set is released.
      @objects = Hash.new {|hash, index| hash[index] = @klass.new(@container.send(@get_fn, index), @data_set)}
    end
    
    def [](index)
      return nil if (index < 0) || (index >= @size)
      @objects[index]
    end
    
    def each
      (0...@size).each do |index|
        yield @objects[index]
      end
    end
  end
end
