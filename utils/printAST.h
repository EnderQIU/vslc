#include <iostream>
#include <vector>
#include <string>
#include "../syntax/structure/ast.h"

using namespace std;

string PREFIX_BRANCH = "©À©¤";//Ê÷Ö¦
string PREFIX_TRUNK = "©¦ ";//Ê÷¸É
string PREFIX_LEAF = "©¸©¤";//Ò¶×Ó
string PREFIX_EMP = "  ";//¿Õ

string&   replace_all_distinct(string& str, const string& old_value, const string& new_value) {
	for (string::size_type pos(0); pos != string::npos; pos += new_value.length()) {
		if ((pos = str.find(old_value, pos)) != string::npos)
			str.replace(pos, old_value.length(), new_value);
		else
			break;
	}
	return  str;
}

void printAST(vector<AST*> nodes, string prefix) {
	prefix = replace_all_distinct(prefix, PREFIX_BRANCH, PREFIX_TRUNK);
	prefix = replace_all_distinct(prefix, PREFIX_LEAF, PREFIX_EMP);
	for (int i = 0; i < nodes.size(); i++) {
		if (i == nodes.size() - 1) {
			cout << prefix << PREFIX_LEAF << "  " << nodes[i]->getSymbol().getTypeName() << endl;
			if (!nodes[i]->isLeaf()) {
				printAST(nodes[i]->children, prefix + PREFIX_LEAF);
			}
		}
		else {
			cout << prefix << PREFIX_BRANCH << "  " << nodes[i]->getSymbol().getTypeName() << endl;
			if (!nodes[i]->isLeaf()) {
				printAST(nodes[i]->children, prefix + PREFIX_TRUNK);
			}
		}
	}
}

void printAST(AST root) {
	cout << PREFIX_LEAF << "  " << root.getSymbol().getTypeName() << endl;
	printAST(root.children, PREFIX_LEAF);
}