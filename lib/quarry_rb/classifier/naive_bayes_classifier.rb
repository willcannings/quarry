module Quarry
  module Classifier
    class NaiveBayesClassifier < Classifier
      def initialize(data_set)
        puts "!!!! CREATING"
        @classifier = Quarry::Classifier::ImplNaiveBayesClassifier.new(data_set.data_set)
        puts "!!!! DONE"
        super(data_set)
      end
    end
  end
end
