module Quarry
  module DataSet
    class DataSet
      attr_reader :data_set
      def initialize(data_set=nil)
        @data_set = data_set || ImplDataSet.new()
      end
      
      def name
        @data_set.get_name
      end
      
      def name=(new_name)
        @data_set.set_name(new_name)
      end
      
      def examples
        @examples ||= EnumerableHelper.new(self, @data_set, ::Quarry::DataSet::Example, :examples_size, :get_example_by_index)
      end
      
      def categories
        @categories ||= EnumerableHelper.new(self, @data_set, ::Quarry::DataSet::Category, :categories_size, :get_category_by_index)
      end
      
      def features
        @features ||= EnumerableHelper.new(self, @data_set, ::Quarry::DataSet::Feature, :features_size, :get_feature_by_index)
      end
      
      def stratify(classifier, folds, skip_fold)
        @data_set.stratify(classifier.classifier, folds, skip_fold)
      end
      
      def classify_fold(classifier, folds, fold)
        ConfusionMatrix.new(self, @data_set.classify_fold(classifier.classifier, folds, fold))
      end
      
      def cross_fold_validation(classifier, folds)
        ConfusionMatrix.new(self, @data_set.cross_fold_validation(classifier.classifier, folds))
      end
    end
  end
end
