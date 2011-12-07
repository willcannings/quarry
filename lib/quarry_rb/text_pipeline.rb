module Quarry
  class TextPipeline
    attr_reader :text_pipeline
    def initialize(tp = nil)
      @text_pipeline = tp || Quarry::ImplTextPipeline.new
    end
    
    def process_text(data_set, text)
      Example.new(@text_pipeline.process_text(data_set, text))
    end
    
    def self.standard_pipeline
      new(Quarry::Preprocessing::Text.standard_pipeline)
    end
  end
end
