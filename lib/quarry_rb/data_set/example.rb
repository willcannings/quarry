module Quarry
  module DataSet
    class Example
      attr_reader :example
      
      def initialize(example, data_set)
        @data_set = data_set
        @example  = example
      end
      
      def [](index)
        @example.get_value(index)
      end
      
      def []=(index, value)
        @example.set_value(index, value)
      end
      
      def category
        @data_set.categories[@example.get_category_index]
      end
      
      def category_index
        @example.get_category_index
      end
      
      def category=(new_category)
        @example.set_category_index(@data_set.data_set, new_category)
      end
    end
  end
end
