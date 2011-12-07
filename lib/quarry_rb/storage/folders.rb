module Quarry
  class Folders
    def initialize(path, pipeline)
      @folders = Quarry::ImplFolders.new(path, pipeline.text_pipeline)
    end
    
    def read
      Quarry::DataSet::DataSet.new(@folders.read)
    end
  end
end