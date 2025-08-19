
import email
import math
import os


def load_tokens(email_path):
    tokens = list()
    file = open(email_path, 'r', encoding='utf-8', errors='ignore')
    message = email.message_from_file(file)

    for line in email.iterators.body_line_iterator(message):
        curr_tokens = line.strip().split()
        tokens.extend(curr_tokens)
    
    return tokens

def log_probs(email_paths, smoothing):
    
    # get all tokens
    tokens = list()
    for path in email_paths:
        tokens.extend(load_tokens(path))

    # get total word count = sum over w' in V (count(w'))
    word_count = len(tokens)
    
    # get unique words by converting to set and then back to list
    # len(unique_vocab) = V
    unique_vocab = list(set(tokens))
    
    occur = dict()
    prob = dict()

    # get count(w)
    for w in tokens:
        if occur.get(w) == None:
            occur[w] = 1
        else:
            occur[w] += 1
    
    denom = (word_count + (smoothing * (len(unique_vocab) + 1)))

    # prob(w) = (count(w) + alpha) / denom
    for v in unique_vocab:
        prob[v] = math.log((occur[v] + smoothing) / denom)
    
    # prob("<UNK>") = alpha / denom
    prob["<UNK>"] = math.log(smoothing / denom)

    return prob

class SpamFilter(object):

    def __init__(self, spam_dir, ham_dir, smoothing):

        # get all files from directory
        spam_files = [spam_dir + '/' + name for name in os.listdir(spam_dir)]
        ham_files = [ham_dir + '/' + name for name in os.listdir(ham_dir)]
        
        # create spam and ham dictionaries
        self.spam_dict = log_probs(spam_files, smoothing)
        self.ham_dict = log_probs(ham_files, smoothing)

        num_spam = len(spam_files)
        num_ham = len(ham_files)

        self.p_spam = num_spam / (num_spam + num_ham)
        self.p_ham = num_ham / (num_spam + num_ham)


    def is_spam(self, email_path):
        # log P(C|X) ~ log P(C) + sum over i to n (log P(xi|C))
        tokens = load_tokens(email_path)
        p_spam_doc = math.log(self.p_spam)
        p_ham_doc = math.log(self.p_ham)
        
        # if token is not found in dictionary, convert into special word "<UNK>"
        for t in tokens:
            p_spam_doc += self.spam_dict.get(t, self.spam_dict["<UNK>"])
            p_ham_doc += self.ham_dict.get(t, self.ham_dict.get("<UNK>"))
    
        return (p_spam_doc > p_ham_doc)
        

    def most_indicative_spam(self, n):
        # log(P(w|spam) / P(w)) = log(P(w|spam) / (P(w|spam) + P(w|ham))) = log P(w|spam) - log (P(w|spam) + P(w|ham))
        # heuristic given in hint: Spam indication = log P(w|spam) - log P(w|ham)

        # get words that only appear in both spam and ham emails
        shared_words = set(self.spam_dict.keys()) & set(self.ham_dict.keys())
        shared_words.remove("<UNK>")

        # get all spam indication values
        # store in list as tuple of (word, value)
        indication_vals = list()
        for w in shared_words:
            spam_ind = self.spam_dict[w] - self.ham_dict[w]
            indication_vals.append((w, spam_ind))
        
        # sort list by indication values
        def keyFunc(e):
            return e[1]

        indication_vals.sort(key=keyFunc, reverse=True)
        return [w[0] for w in indication_vals[:n]]



    def most_indicative_ham(self, n):
        # get words that only appear in both spam and ham emails
        shared_words = set(self.spam_dict.keys()) & set(self.ham_dict.keys())
        shared_words.remove("<UNK>")

        # get all ham3 indication values
        # store in list as tuple of (word, value)
        indication_vals = list()
        for w in shared_words:
            ham_ind = self.ham_dict[w] - self.spam_dict[w]
            indication_vals.append((w, ham_ind))
        
        # sort list by indication values
        def keyFunc(e):
            return e[1]

        indication_vals.sort(key=keyFunc, reverse=True)
        return [w[0] for w in indication_vals[:n]]



