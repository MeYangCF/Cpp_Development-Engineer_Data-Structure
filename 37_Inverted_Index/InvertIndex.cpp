/*
@author: Yang ChengFeng
@email: meyangcf@163.com
@date: 2025-01-13 下午3:38
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

class InvertIndex {
public:
    void setSearchPath(string path) {
        cout << "搜索文件...";
        getAllFile(path.c_str());
        cout << "完成！" << endl;

        cout << "开始创建倒排索引";
        createInvertIndex();
        cout << "完成!" << endl;
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
                cout << "未搜索到任何匹配的内容！" << endl;
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
                cerr << filePath << "...打开失败！" << endl;
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