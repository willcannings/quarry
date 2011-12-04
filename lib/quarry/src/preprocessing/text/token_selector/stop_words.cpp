#include "stop_words.h"
#include <tr1/unordered_map>
using namespace tr1;

static unordered_set<string> stop_words;
static int stop_word_count = 586;
static string stop_word_list[] = {
  "a", "able", "about", "above", "abroad", "according", "accordingly", "across", "actually", "adj"
  "after", "afterwards", "again", "against", "ago", "ahead", "all", "allow", "allows", "almost"
  "alone", "along", "alongside", "already", "also", "although", "always", "am", "amid", "amidst"
  "among", "amongst", "an", "and", "another", "any", "anybody", "anyhow", "anyone", "anything"
  "anyway", "anyways", "anywhere", "apart", "appear", "appreciate", "appropriate", "are", "around", "as"
  "aside", "ask", "asking", "associated", "at", "available", "away", "awfully", "b", "back"
  "backward", "backwards", "be", "became", "because", "become", "becomes", "becoming", "been", "before"
  "beforehand", "begin", "behind", "being", "believe", "below", "beside", "besides", "best", "better"
  "between", "beyond", "both", "brief", "but", "by", "c", "came", "can", "cannot"
  "cant", "caption", "cause", "causes", "certain", "certainly", "changes", "clearly", "co", "com"
  "come", "comes", "concerning", "consequently", "consider", "considering", "contain", "containing", "contains", "corresponding"
  "could", "course", "currently", "d", "dare", "definitely", "described", "despite", "did", "different"
  "directly", "do", "does", "doing", "done", "down", "downwards", "during", "e", "each"
  "edu", "eg", "eight", "eighty", "either", "else", "elsewhere", "end", "ending", "enough"
  "entirely", "especially", "et", "etc", "even", "ever", "evermore", "every", "everybody", "everyone"
  "everything", "everywhere", "ex", "exactly", "example", "except", "f", "fairly", "far", "farther"
  "few", "fewer", "fifth", "first", "five", "followed", "following", "follows", "for", "forever"
  "former", "formerly", "forth", "forward", "found", "four", "from", "further", "furthermore", "g"
  "get", "gets", "getting", "given", "gives", "go", "goes", "going", "gone", "got"
  "gotten", "greetings", "h", "had", "half", "happens", "hardly", "has", "have", "having"
  "he", "hello", "help", "hence", "her", "here", "hereafter", "hereby", "herein", "hereupon"
  "hers", "herself", "hi", "him", "himself", "his", "hither", "hopefully", "how", "howbeit"
  "however", "hundred", "i", "ie", "if", "ignored", "immediate", "in", "inasmuch", "inc"
  "indeed", "indicate", "indicated", "indicates", "inner", "inside", "insofar", "instead", "into", "inward"
  "is", "it", "its", "itself", "j", "just", "k", "keep", "keeps", "kept"
  "know", "known", "knows", "l", "last", "lately", "later", "latter", "latterly", "least"
  "less", "lest", "let", "like", "liked", "likely", "likewise", "little", "look", "looking"
  "looks", "low", "lower", "ltd", "m", "made", "mainly", "make", "makes", "many"
  "may", "maybe", "me", "mean", "meantime", "meanwhile", "merely", "might", "mine", "minus"
  "miss", "more", "moreover", "most", "mostly", "mr", "mrs", "much", "must", "my"
  "myself", "n", "name", "namely", "nd", "near", "nearly", "necessary", "need", "needs"
  "neither", "never", "neverf", "neverless", "nevertheless", "new", "next", "nine", "ninety", "no"
  "nobody", "non", "none", "nonetheless", "noone", "nor", "normally", "not", "nothing", "notwithstanding"
  "novel", "now", "nowhere", "o", "obviously", "of", "off", "often", "oh", "ok"
  "okay", "old", "on", "once", "one", "ones", "only", "onto", "opposite", "or"
  "other", "others", "otherwise", "ought", "our", "ours", "ourselves", "out", "outside", "over"
  "overall", "own", "p", "particular", "particularly", "past", "per", "perhaps", "placed", "please"
  "plus", "possible", "presumably", "probably", "provided", "provides", "q", "que", "quite", "qv"
  "r", "rather", "rd", "re", "really", "reasonably", "recent", "recently", "regarding", "regardless"
  "regards", "relatively", "respectively", "right", "round", "s", "said", "same", "saw", "say"
  "saying", "says", "second", "secondly", "see", "seeing", "seem", "seemed", "seeming", "seems"
  "seen", "self", "selves", "sensible", "sent", "serious", "seriously", "seven", "several", "shall"
  "she", "should", "since", "six", "so", "some", "somebody", "someday", "somehow", "someone"
  "something", "sometime", "sometimes", "somewhat", "somewhere", "soon", "sorry", "specified", "specify", "specifying"
  "still", "sub", "such", "sup", "sure", "t", "take", "taken", "taking", "tell"
  "tends", "th", "than", "thank", "thanks", "thanx", "that", "thats", "the", "their"
  "theirs", "them", "themselves", "then", "thence", "there", "thereafter", "thereby", "therefore", "therein"
  "theres", "thereupon", "these", "they", "thing", "things", "think", "third", "thirty", "this"
  "thorough", "thoroughly", "those", "though", "three", "through", "throughout", "thru", "thus", "till"
  "to", "together", "too", "took", "toward", "towards", "tried", "tries", "truly", "try"
  "trying", "twice", "two", "u", "un", "under", "underneath", "undoing", "unfortunately", "unless"
  "unlike", "unlikely", "until", "unto", "up", "upon", "upwards", "us", "use", "used"
  "useful", "uses", "using", "usually", "v", "value", "various", "versus", "very", "via"
  "viz", "vs", "w", "want", "wants", "was", "way", "we", "welcome", "well"
  "went", "were", "what", "whatever", "when", "whence", "whenever", "where", "whereafter", "whereas"
  "whereby", "wherein", "whereupon", "wherever", "whether", "which", "whichever", "while", "whilst", "whither"
  "who", "whoever", "whole", "whom", "whomever", "whose", "why", "will", "willing", "wish"
  "with", "within", "without", "wonder", "would", "x", "y", "yes", "yet", "you"
  "your", "yours", "yourself", "yourselves", "z", "zero"
};

Preprocessing::Text::StopWords::StopWords() : TokenSelector() {
  for(int i = 0; i < stop_word_count; i++)
    stop_words.insert(stop_word_list[i]);
}

bool Preprocessing::Text::StopWords::select(char *start, char *end) {
  string token = string(start, (end - start) + 1);
  return stop_words.count(token) == 0;
}
