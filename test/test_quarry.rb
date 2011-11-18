require 'helper'

class TestQuarry < Test::Unit::TestCase
  should 'load' do
    require 'quarry'
    Quarry
  end
  
  should 'expose ARFF' do
    Quarry::ARFF
  end
  
  should 'allow creating ARFF objects' do
    a = Quarry::ARFF.new("/Users/will/dev/classifier/src/categories.arff")
  end
  
  should 'read ARFF objects' do
    a = Quarry::ARFF.new("/Users/will/Desktop/test_reduced.arff")
    ds = a.read
    
    puts "\nFeatures: #{ds.features.size}, examples: #{ds.examples.size}"
    classifier = Quarry::Classifier::NaiveBayesClassifier.new(ds)
    print "Created classifier\n"
    cm = ds.cross_fold_validation(classifier, 2)
    print "Cross fold done\n"
    cm.print_summary
    
    #ds.stratify(classifier, 10, 0)
    #classifier.classify(ds.examples[0])
    #cm = ds.classify_fold(classifier, 10, 0)
    #cm.print_summary
  end
end
