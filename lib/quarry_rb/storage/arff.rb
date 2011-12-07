module Quarry
  class ARFF
    def initialize(path)
      @arff = Quarry::ImplARFF.new(path)
    end
    
    def read
      Quarry::DataSet::DataSet.new(@arff.read)
    end
  end
end