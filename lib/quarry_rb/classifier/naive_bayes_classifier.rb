module Quarry
  module Classifier
    class NaiveBayesClassifier < Classifier
      def initialize(data_set)
        @classifier = Quarry::Classifier::ImplNaiveBayesClassifier.new(data_set.data_set)
        super(data_set)
      end
    end
  end
end
