module Quarry
  class ConfusionMatrix
    attr_reader :confusion_matrix
    attr_reader :data_set
    def initialize(data_set, matrix=nil)
      @data_set = data_set
      if matrix
        @confusion_matrix = matrix
      else
        @confusion_matrix = Quarry::ImplConfusionMatrix.new(data_set.data_set)
      end
    end
    
    def add(predicted, actual)
      @confusion_matrix.add(predicted.category, actual.category)
    end
    
    def accuracy
      @confusion_matrix.accuracy
    end
    
    def error
      @confusion_matrix.error
    end
    
    def tp(category)
      @confusion_matrix.tp(category.category)
    end
    
    def fp(category)
      @confusion_matrix.fp(category.category)
    end
    
    def tn(category)
      @confusion_matrix.tn(category.category)
    end
    
    def fn(category)
      @confusion_matrix.fn(category.category)
    end
    
    def precision(category)
      @confusion_matrix.precision(category)
    end
    
    def recall(category)
      @confusion_matrix.recall(category)
    end
    
    def fscore(category)
      @confusion_matrix.fscore(category)
    end
    
    def print_summary
      @confusion_matrix.print_summary
    end
  end
end
