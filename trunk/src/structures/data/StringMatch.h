#ifndef STRINGMATCH_H_
#define STRINGMATCH_H_

/**
 * Esta clase debería contener la posición en donde
 * fué encontrado determinado String
 */
struct StringMatch {
	int document;
	int position;
	StringMatch(int document, int position);
};

#endif /* STRINGMATCH_H_ */
