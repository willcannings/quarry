module Quarry
  class Model
    attr_reader :model
    def initialize(m = nil)
      @model = m || Quarry::ImplModel.new
    end
    
    def data_set
      @data_set ||= Quarry::DataSet::DataSet.new(@model.get_data_set)
    end
    
    def data_set=(ds)
      @model.set_data_set(ds.data_set)
      @data_set = ds
    end
    
    # def classifier
    #   @model.get_classifier
    # end

    def classifier=(c)
      @model.set_classifier(c.classifier)
    end
    
    def text_pipeline
      @text_pipeline ||= TextPipeline.new(@model.get_text_pipeline)
    end
    
    def text_pipeline=(t)
      @model.set_text_pipeline(t.text_pipeline)
      @text_pipeline = t
    end
    
    def train(example)
      @model.train(example)
    end
    
    def train_text(text)
      @model.train_text(text)
    end
    
    def classify(example)
      @model.classify(example)
    end
    
    def classify_text(text)
      @model.classify_text(text)
    end
    
    def process_text(text, create_features = true)
      DataSet::Example.new(@model.process_text(text, create_features), data_set)
    end
    
    def add_text_example(text, category_name)
      @model.add_text_example(text, category_name)
    end
    
    def rank(example)
      @model.rank(example)
    end
    
    def rank_text(text)
      @model.rank_text(text)
    end
    
    def rank_text_names(text)
      @model.rank_text_names(text)
    end
  end
end
