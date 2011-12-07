module Quarry
  class TextPipeline
    attr_reader :text_pipeline
    def initialize(tp = nil)
      @text_pipeline = tp || Quarry::ImplTextPipeline.new
    end
    
    def process_text(data_set, text, create_features = false)
      ::Quarry::DataSet::Example.new(@text_pipeline.process_text(data_set.data_set, text, create_features))
    end
    
    def self.standard_pipeline
      new(Quarry::Preprocessing::Text.standard_pipeline)
    end
  end
end
