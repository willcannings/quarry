module Quarry
  class Binary
    def initialize(path)
      @binary = Quarry::ImplBinary.new(path)
    end
    
    def read
      Quarry::DataSet::DataSet.new(@binary.read)
    end
    
    def write(data_set)
      @binary.write(data_set.data_set)
    end
    
    def read_model
      Quarry::Model.new(@binary.read_model)
    end
    
    def write_model(model)
      @binary.write_model(model.model)
    end
  end
end
