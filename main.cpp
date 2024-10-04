#include <bits/stdc++.h>
using namespace std;

class TrieNode{
public:
	bool isTerminal;
	TrieNode* child[26];
	TrieNode(){
		isTerminal=false;
		for(int i=0;i<26;i++) child[i]=NULL;
	}
};
TrieNode* root=new TrieNode();
void insertNode(string s){
	TrieNode* head=root;
	for(char ch:s){
		int index=ch-'a';
		if(head->child[index]==NULL) head->child[index]=new TrieNode();
		head=head->child[index];
	}
	head->isTerminal=true;
}

void storeSuggestion(TrieNode* curr, vector<string>&temp,string &prefix){
	if(curr->isTerminal==true) temp.push_back(prefix);
	for(char ch='a';ch<='z';ch++){
		int index=ch-'a';
		TrieNode* next=curr->child[index];
		if(next!=NULL){
			temp.push_back(prefix);
			// cout<<prefix<<endl;
			storeSuggestion(next,temp,prefix);
			temp.pop_back();
		}
	}
}

vector<vector<string>> Suggestions(string s){
	TrieNode* prev=root;
	vector<vector<string>>ans;
	string prefix="";
	for(char ch:s){
		int index=ch-'a';
		TrieNode* curr=prev->child[index];
		if(curr==NULL) break;
		else{
			vector<string>temp;
			prefix.push_back(ch);
			storeSuggestion(curr,temp,prefix);
			ans.push_back(temp);
			prev=curr;
		}
	}
	return ans;
}

int main() {
	vector<string>inputs;
	inputs.push_back("dog");
	inputs.push_back("dogger");
	inputs.push_back("doggest");
	inputs.push_back("dogging");
	inputs.push_back("dodging");
	inputs.push_back("doggo");
	inputs.push_back("pogo");
	for(string s:inputs) insertNode(s);
	string search="dogge";
	vector<vector<string>>ans=Suggestions(search);
	for(int i=0;i<ans.size();i++){
		for(int j=0;j<ans[i].size();j++){
			cout<<ans[i][j]<<" ";
		}
		cout<<endl;
	}
	return 0;
}
