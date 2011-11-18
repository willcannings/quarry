module Quarry
  module Classifier
    class Classifier
      attr_reader :classifier
      def initialize(data_set)
        @data_set = data_set
      end
      
      def prepare
        @classifier.prepare
      end
      
      def classify(example)
        @data_set.categories[@classifier.classify_to_index(example.example)]
      end
      
      def rank(example)
        @classifier.rank(example.example)
      end
    end
  end
end
