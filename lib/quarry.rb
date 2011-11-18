require 'quarry_toolkit'
Dir.chdir(File.dirname(__FILE__)) do
  require './quarry_rb/arff'
  require './quarry_rb/enumerable_helper'
  require './quarry_rb/confusion_matrix'
  
  require './quarry_rb/data_set/data_set'
  require './quarry_rb/data_set/example'
  require './quarry_rb/data_set/feature'
  
  require './quarry_rb/classifier/classifier'
  require './quarry_rb/classifier/naive_bayes_classifier'
end
