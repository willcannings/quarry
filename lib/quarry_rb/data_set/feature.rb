module Quarry
  module DataSet
    class Feature
      attr_reader :feature
      
      def initialize(feature, data_set)
        @data_set = data_set
        @feature  = feature
      end
      
      def name
        @feature.get_name
      end
      
      def name=(new_name)
        @feature.set_name(new_name)
      end
      
      def type
        @feature.get_type
      end
      
      def type=(new_type)
        @feature.set_type(new_type)
      end
    end
  end
end
