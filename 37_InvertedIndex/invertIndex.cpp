/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-01-13 ����3:38
@description:
*/

#include <iostream>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <unordered_map>

#undef UNICODE
#include <algorithm>
#include <Windows.h>
using namespace std;

struct InvertTerm {
    InvertTerm(string docid, int freqs, int location)
        : docid_(docid)
        , freqs_(freqs) {
        locations_.emplace_back(location);
    }

    bool operator==(const InvertTerm& term) const {
        return docid_ == term.docid_;
    }

    bool operator<(const InvertTerm& term) const {
        return docid_ < term.docid_;
    }

    string docid_;
    int freqs_;
    list<int> locations_;
};

class InvertList {
public:
    void addTerm(string docid, int location) {
        for (auto& term : termList_) {
            if (term.docid_ == docid) {
                term.freqs_++;
                term.locations_.emplace_back(location);
                return;
            }
        }

        termList_.emplace_back(docid, 1, location);
    }

    const list<InvertTerm>& getInvertList() const {
        return termList_;
    }

private:
    list<InvertTerm> termList_;
};

class invertIndex {
public:
    void setSearchPath(string path) {
        cout << "�����ļ�...";
        getAllFile(path.c_str());
        cout << "��ɣ�" << endl;

        cout << "��ʼ������������";
        createInvertIndex();
        cout << "���!" << endl;
    }

    void query(string phrase) {
        vector<string> wordList;
        char* word = strtok(const_cast<char*>(phrase.c_str(), " "));

        while (word != nullptr) {
            word = trim(word);

            if (strlen(word) > 0)
                wordList.emplace_back(word);

            word = strtok(nullptr, " ");
        }

        if (wordList.empty())
            return;

        if (wordList.size() == 1) {
            auto it = invertMap_.find(wordList[0]);
            if (it == invertMap_.end()) {
                cout << "δ�������κ�ƥ������ݣ�" << endl;
                return;
            }

            for (auto& term : it->second.getInvertList())
                cout << term.docid_ << "freqs:" << term.freqs_ << endl;
        } else {
            vector<InvertList> invertList;

            for (int i = 0; i < wordList.size(); i++) {
                auto it = invertMap_.find(wordList[i]);

                if (it != invertMap_.end())
                    invertList.emplace_back(it->second);
            }

            vector<InvertTerm> termShared;
            vector<InvertTerm> v1(invertList[0].getInvertList().begin(),
                invertList[0].getInvertList().end());

            for (int i = 1; i < invertList.size(); i++) {
                vector<InvertTerm> v2(invertList[i].getInvertList().begin(),
                    invertList[i].getInvertList().end());

                sort(v1.begin(), v1.end());
                sort(v2.begin(), v2.end());

                set_intersection(v1.begin(), v1.end(),
                    v2.begin(), v2.end(),
                    back_inserter(termShared));

                v1.swap(termShared);
                termShared.clear();
            }

            for (auto& term : v1){
                cout << term.docid_ << " freqs:" << term.freqs_ << endl;
                cout << "locations:";
            }
        }
    }

    void setSuffix(string suffix){
        suffix_ = suffix;
    }

private:
    int getAllFile(const char* Path)
    {
        char szFind[MAX_PATH];
        WIN32_FIND_DATA FindFileData;
        strcpy(szFind, Path);
        strcat(szFind, "\\*.*");
        HANDLE hFind = FindFirstFile(szFind, &FindFileData);
        if (INVALID_HANDLE_VALUE == hFind)
            return -1;

        do {
            if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0) {
                    char szFile[MAX_PATH] = { 0 };
                    strcpy(szFile, Path);
                    strcat(szFile, "\\");
                    strcat(szFile, FindFileData.cFileName);
                    getAllFile(szFile);
                }
            } else {
                string fileName(FindFileData.cFileName);
                int pos = fileName.find(suffix_);  // abcd.cpp   pos:4 +4

                if (pos != string::npos && pos + suffix_.size() == fileName.size()){
                    // std::cout << Path << "\\" << FindFileData.cFileName << std::endl;
                    string filePath(Path);
                    filePath.append("\\");
                    filePath.append(fileName);
                    fileList_.emplace_back(filePath);
                }
            }
        } while (FindNextFile(hFind, &FindFileData));

        FindClose(hFind);

        return 0;
    }

    int createInvertIndex() {
        for (string& filePath : fileList_) {
            cout << ".";
            FILE* pf = fopen(filePath.c_str(), "r");

            if (pf == nullptr) {
                cerr << filePath << "...��ʧ�ܣ�" << endl;
                continue;;
            }

            vector<string> wordList;
            int location = 0;
            const int LINE_SIZE = 2048;
            char line[LINE_SIZE] = {0};

            while (!feof(pf)) {
                fgets(line, LINE_SIZE, pf);
                char* word = strtok(line, " ");

                while (word != nullptr) {
                    word = trim(word);

                    if (strlen(word) > 0) {
                        wordList.emplace_back(word);
                    }

                    word = strtok(nullptr, " ");
                }

                for (string& w : wordList) {
                    location++;
                    auto it = invertMap_.find(w);

                    if (it == invertMap_.end()) {
                        InvertList list;
                        list.addTerm(filePath, location);
                        invertMap_.emplace(w, list);
                    } else {
                        it->second.addTerm(filePath, location>);
                    }
                }
            }

            fclose(pf);
        }
    }

    char* trim(char* word){
        int i = 0;

        while (word[i] != '\0'){
            if (word[i] == ' ' || word[i] == '\t' || word[i] == '\n')
                i++;
            else
                break;
        }

        int j = i;
        while (word[j] != '\0')
        {
            if (word[j] == ' ' || word[j] == '\t' || word[j] == '\n')
                break;

            j++;
        }

        word[j] = '\0';
        return word + i;
    }

private:
    string suffix_;
    list<string> fileList_;
    unordered_map<string, InvertList> invertMap_;
};

int main() {

    return 0;
}

// // 37_��������.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
// //
//
// #include <iostream>
// #include <string>
// #include <list>
// #include <vector>
// #include <unordered_map>
// #include <algorithm>
// using namespace std;
//
// #undef UNICODE
// #include <Windows.h>
//
// // ������
// struct InvertTerm
// {
// 	InvertTerm(string docid, int freqs, int location)
// 		: docid_(docid)
// 		, freqs_(freqs)
// 	{
// 		locations_.emplace_back(location);
// 	}
// 	bool operator==(const InvertTerm& term) const
// 	{
// 		return docid_ == term.docid_;
// 	}
// 	bool operator<(const InvertTerm& term) const
// 	{
// 		return docid_ < term.docid_;
// 	}
// 	string docid_;        // �������ڵ��ĵ�
// 	int freqs_;           // ���ʳ��ֵĴ���
// 	list<int> locations_; // ���ʳ��ֵ�λ��
// };
//
// // �����б�
// class InvertList
// {
// public:
// 	// ��ӵ�����
// 	void addTerm(string docid, int location)
// 	{
// 		for (auto& term : termList_)
// 		{
// 			if (term.docid_ == docid) // docid�Ѿ�������
// 			{
// 				term.freqs_++;
// 				term.locations_.emplace_back(location);
// 				return;
// 			}
// 		}
//
// 		// ��һ�δ���docid�ĵ��ĵ�����
// 		termList_.emplace_back(docid, 1, location);
// 	}
//
// 	// ��ȡ�����б�����
// 	const list<InvertTerm>& getInvertList() const
// 	{
// 		return termList_;
// 	}
// private:
// 	list<InvertTerm> termList_;  // �洢��ǰ�����б����еĵ�����
// };
//
// // ��������
// class InvertIndex
// {
// public:
// 	// �����ĵ������ĸ�·��
// 	void setSearchPath(string path)
// 	{
// 		cout << "�����ļ�...";
// 		getAllFile(path.c_str());
// 		cout << "���!" << endl;
//
// 		cout << "��ʼ������������";
// 		createInvertIndex();
// 		cout << "���!" << endl;
// 	}
//
// 	// ��ѯ�ӿ�
// 	void query(string phrase)
// 	{
// 		// �Ƚ��о��ӷִʲ���
// 		vector<string> wordList;
// 		char* word = strtok(const_cast<char*>(phrase.c_str()), " ");
// 		while (word != nullptr)
// 		{
// 			word = trim(word);
// 			if (strlen(word) > 0)
// 			{
// 				wordList.emplace_back(word);
// 			}
// 			word = strtok(nullptr, " ");
// 		}
//
// 		if (wordList.empty())
// 			return;
//
// 		if (wordList.size() == 1)
// 		{
// 			auto it = invertMap_.find(wordList[0]);
// 			if (it == invertMap_.end())
// 			{
// 				cout << "δ�������κ�ƥ�������!" << endl;
// 				return;
// 			}
//
// 			for (auto& term : it->second.getInvertList())
// 			{
// 				cout << term.docid_ << " freqs:" << term.freqs_ << endl;
// 			}
// 		}
// 		else
// 		{
// 			// ������ʵ�����������кϲ�����
// 			vector<InvertList> invertList;
// 			for (int i = 0; i < wordList.size(); i++)
// 			{
// 				// invertList.emplace_back(invertMap_[wordList[i]]);
// 				auto it = invertMap_.find(wordList[i]);
// 				if (it != invertMap_.end())
// 				{
// 					invertList.emplace_back(it->second);
// 				}
// 			}
//
// 			// ��ʼ�������еĵ����б������浹����Ľ���
// 			vector<InvertTerm> termShared;
// 			vector<InvertTerm> v1(invertList[0].getInvertList().begin(),
// 				invertList[0].getInvertList().end());
// 			for (int i = 1; i < invertList.size(); i++)
// 			{
// 				vector<InvertTerm> v2(invertList[i].getInvertList().begin(),
// 					invertList[i].getInvertList().end());
//
// 				sort(v1.begin(), v1.end());
// 				sort(v2.begin(), v2.end());
//
// 				// �����������б����浹����Ľ���
// 				// set_intersection�󼯺Ͻ���ʱ�����뱣֤v1��v2�������
// 				set_intersection(v1.begin(), v1.end(),
// 					v2.begin(), v2.end(),
// 					back_inserter(termShared));
//
// 				v1.swap(termShared);
// 				termShared.clear();
// 			}
//
// 			// �÷������Ƚϸߵĵ�����
// 			for (auto& term : v1)
// 			{
// 				cout << term.docid_ << " freqs:" << term.freqs_ << endl;
// 				cout << "locations:";
// 				/*for (int pos : term.locations_)
// 				{
// 					cout << pos << " ";
// 				}
// 				cout << endl;*/
// 			}
//
// 			// �ѳ��ֲ��ֵ��ʵĵ��������ݴ�ӡ����
//
// 		}
// 	}
//
// 	// �����ĵ������ĺ�׺������
// 	void setSuffix(string suffix)
// 	{
// 		suffix_ = suffix;
// 	}
// private:
// 	// �������������ṹ
// 	void createInvertIndex()
// 	{
// 		for (string& filePath : fileList_)
// 		{
// 			cout << ".";
// 			FILE* pf = fopen(filePath.c_str(), "r");
// 			if (pf == nullptr)
// 			{
// 				cerr << filePath << " ......��ʧ�ܣ�" << endl;
// 				continue;
// 			}
//
// 			// ���ж�ȡ�ļ���������ݣ�����" "�ո���зִ�
// 			vector<string> wordList;
// 			int location = 0;
// 			const int LINE_SIZE = 2048;
// 			char line[LINE_SIZE] = { 0 };
//
// 			while (!feof(pf))
// 			{
// 				// ��һ���ļ�����
// 				fgets(line, LINE_SIZE, pf);
//
// 				// ����" "�ո���зִ� split   strtok
// 				char* word = strtok(line, " ");
// 				while (word != nullptr)
// 				{
// 					// ����һ��wordǰ��Ķ���Ŀո�  \t  \n
// 					word = trim(word);
// 					if (strlen(word) > 0)
// 					{
// 						wordList.emplace_back(word);
// 					}
// 					word = strtok(nullptr, " ");
// 				}
//
// 				// ��ʼ��wordList����ĵ��ʴ��������޸ĵ����б�
// 				for (string& w : wordList)
// 				{
// 					location++;
// 					auto it = invertMap_.find(w);
// 					if (it == invertMap_.end())
// 					{
// 						// �½�w���ʵĵ����б�
// 						InvertList list;
// 						list.addTerm(filePath, location);
// 						invertMap_.emplace(w, list);
// 					}
// 					else
// 					{
// 						it->second.addTerm(filePath, location);
// 					}
// 				}
// 			}
//
// 			fclose(pf);
// 		}
// 	}
//
// 	// ȥ���ִʺ�  ����ǰ�������ַ� \t\t\tsdfads\t\n
// 	char* trim(char* word)
// 	{
// 		int i = 0;
// 		while (word[i] != '\0')
// 		{
// 			if (word[i] == ' ' || word[i] == '\t' || word[i] == '\n')
// 			{
// 				i++;
// 			}
// 			else
// 			{
// 				break;
// 			}
// 		}
//
// 		int j = i;
// 		while (word[j] != '\0')
// 		{
// 			if (word[j] == ' ' || word[j] == '\t' || word[j] == '\n')
// 			{
// 				break;
// 			}
// 			j++;
// 		}
// 		word[j] = '\0';
//
// 		return word + i;
// 	}
//
// 	// �ݹ�ɨ��·���������е��ļ�
// 	int getAllFile(const char* Path)
// 	{
// 		char szFind[MAX_PATH];
// 		WIN32_FIND_DATA FindFileData;
// 		strcpy(szFind, Path);
// 		strcat(szFind, "\\*.*");
// 		HANDLE hFind = FindFirstFile(szFind, &FindFileData);
// 		if (INVALID_HANDLE_VALUE == hFind)
// 			return -1;
//
// 		do
// 		{
// 			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
// 			{
// 				if (strcmp(FindFileData.cFileName, ".") != 0 && strcmp(FindFileData.cFileName, "..") != 0)
// 				{
// 					//������Ŀ¼���ݹ�֮
// 					char szFile[MAX_PATH] = { 0 };
// 					strcpy(szFile, Path);
// 					strcat(szFile, "\\");
// 					strcat(szFile, FindFileData.cFileName);
// 					getAllFile(szFile);
// 				}
// 			}
// 			else
// 			{
// 				//�ҵ��ļ�������֮
// 				string fileName(FindFileData.cFileName);
// 				int pos = fileName.find(suffix_);  // abcd.cpp   pos:4 +4
// 				if (pos != string::npos && pos + suffix_.size() == fileName.size())
// 				{
// 					// std::cout << Path << "\\" << FindFileData.cFileName << std::endl;
// 					string filePath(Path);
// 					filePath.append("\\");
// 					filePath.append(fileName);
// 					fileList_.emplace_back(filePath);
// 				}
// 			}
// 		} while (FindNextFile(hFind, &FindFileData));
//
// 		FindClose(hFind);
//
// 		return 0;
// 	}
// private:
// 	string suffix_;  // �����ĵ���׺   .cpp .cc .cxx .c
// 	list<string> fileList_;  // �洢������Ҫ�������ŵ��ļ�
// 	unordered_map<string, InvertList> invertMap_; // �ʵ�+�����б�
// };
//
// int main()
// {
// 	InvertIndex index;
// 	index.setSuffix(".cpp");
// 	index.setSearchPath("D:\\cpp code\\C++ȫ�����ݽṹ�㷨����");
//
// 	for (;;)
// 	{
// 		char buf[128] = { 0 };
// 		cout << "��������:";
// 		cin.getline(buf, 128);
//
// 		index.query(buf);  // grep
// 	}
// 	cout << endl;
// }

