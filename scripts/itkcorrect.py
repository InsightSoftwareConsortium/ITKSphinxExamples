#! /usr/bin/env python

import sys, re, collections

def words(text):
  temp = re.findall( 'itk[A-Z][a-zA-Z_0-9]+', text )
  for i in range( len(temp) ):
    var=temp[i]
    temp[i] = var[3:]
  return temp

def train(features):
    model = collections.defaultdict(lambda: 1)
    for f in features:
        model[f] += 1
    return model

NWORDS = train(words(file('listofITKheaders').read()))

alphabet = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789'

def edits1(word):
   splits     = [(word[:i], word[i:]) for i in range(len(word) + 1)]
   deletes    = [a + b[1:] for a, b in splits if b]
   transposes = [a + b[1] + b[0] + b[2:] for a, b in splits if len(b)>1]
   replaces   = [a + c + b[1:] for a, b in splits for c in alphabet if b]
   inserts    = [a + c + b     for a, b in splits for c in alphabet]
   lowercases = [a + b[0].lower() + b[1:] for a, b in splits if b]
   uppercases = [a + b[0].upper() + b[1:] for a, b in splits if b]
   all_lowercase = [ word[:].lower() ]
#   all_uppercase = [ word[:].upper() ]
   one_uppercase = [ a[:].lower() + b[0].upper() + b[1:].lower() for a,b in splits if b]

   return set(deletes + transposes + replaces + inserts + lowercases + uppercases + all_lowercase + one_uppercase )
#all_uppercase )

def known_edits2(word):
    return set(e2 for e1 in edits1(word) for e2 in edits1(e1) if e2 in NWORDS)

def known(words): return set(w for w in words if w in NWORDS)

def correct(word):
    candidates = known([word]) or known(edits1(word)) or known_edits2(word) or [word]
#    print edits1( word )
    return max(candidates, key=NWORDS.get)

entry=sys.argv[1]
print correct( entry )
