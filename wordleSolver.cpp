#include <bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define yes cout << "YES\n"
#define no cout << "NO\n"

void fastio() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

void solve() {

    string GREEN = "green";
    string YELLOW = "yellow";
    string BLACK = "black";

    ifstream fin("wordle-dictionary.txt");
    string s;

    vector<string> lines;

    while (fin >> s) {
        s.erase(remove(s.begin(), s.end(), '"'), s.end());
        s.erase(remove(s.begin(), s.end(), ','), s.end());
        lines.push_back(s);
    }

    int n = lines.size();
    cout<<"ReadFileSize : "<<n<<endl;
    int noOfAttempts = 6; // no. of attempts

    while(noOfAttempts--){
        n = lines.size();
        map<string, int>mp;
        for(auto it : lines){
            mp[it]=1;
        }

        vector<vector<int>>hash(26);
        for(int i=0; i<n; i++){
            for(int j=0; j<5; j++){
                hash[lines[i][j]-'a'].push_back(i);
            }
        }
        vector<pair<char,int>> blackWords;
        vector<pair<char,int>>greenColorWords;
        vector<pair<char,int>>yellowColorWords;

        for(int i=0; i<5; i++){
            char ithWord;
            cout<<"enter word"<<endl;
            cin>>ithWord;

            cout<<"Enter Word Color"<<endl;
            string ithWordColor;
            int num;
            cin >> num;

            if (num == 1) {
                ithWordColor = BLACK;
            } else if (num == 2) {
                ithWordColor = YELLOW;
            } else {
                ithWordColor = GREEN;
            }

            if(ithWordColor == BLACK){
                blackWords.push_back({ithWord, i});
            } else if(ithWordColor == YELLOW){
                yellowColorWords.push_back({ithWord, i});
            } else {
                greenColorWords.push_back({ithWord, i});
            }
        }

        // Black Color
        // 1) For Both correct and guessed word have single frequency
        //      a) Simply remove all words that contain black letters
        // 2) If anyone contain a letter that have freq>1
        //      b) if color is yellow it means we have to remove all words 
        // 
        if(blackWords.size()>0){
            for(auto it : blackWords){
                bool flag = false;
                for(auto jt : greenColorWords){
                    if(jt.first == it.first) flag=true;
                }
                for(auto jt : yellowColorWords){
                    if(jt.first == it.first) flag=true;
                }
                if(!flag){
                    for(auto jt: hash[it.first-'a']){
                        mp[lines[jt]]=0;
                    }
                }
                // Removing from index
                for(auto jt : lines){
                    if(jt[it.second]==it.first){
                        mp[jt]=0;
                    }
                }
            }
        }

        // Green Color
        if(greenColorWords.size()>0){
            for(auto it : greenColorWords){
                for(int j=0; j<n; j++){
                    if(mp[lines[j]]){
                        if(lines[j][it.second]!=it.first){
                            mp[lines[j]]=0;
                        }
                    }
                }
            }
        } 

        // Yellow Color Words
        // 1) Remove all words that contain letter at that index
        // 2) and we have to remove all words that don't contain that letter
        // if(yellowColorWords.size()>0){
        //     for(int j=0; j<n; j++){
        //         if(mp[lines[j]]){
        //             bool find = false;
        //             for(int k=0; k<yellowColorWords.size(); k++){
        //                 for(int l=0; l<5; l++){ 
        //                     if (yellowColorWords[k].first == lines[j][l] && (yellowColorWords[k].second != l)) {
        //                         find=true;
        //                     } else if (yellowColorWords[k].second == l) {
        //                         break;
        //                     }
        //                 }
        //             }
        //             if (find) {
        //                 mp[lines[j]]=0;
        //             }
        //         }
        //     }
        // } 

        if(yellowColorWords.size()>0){
            for(int i=0; i<yellowColorWords.size(); i++){
                for(int j=0; j<n; j++){
                    if(mp[lines[j]]){
                        bool find = false;
                        bool isPresent = false;
                        for(int l=0; l<5; l++){ 
                            if (yellowColorWords[i].first == lines[j][l] ) {
                                isPresent = true;
                                if(yellowColorWords[i].second == l){
                                    mp[lines[j]]=0;
                                    break;
                                }
                            }
                        }
                        if (!isPresent && mp[lines[j]]) {
                            mp[lines[j]]=0;
                        }
                    }
                }
            }
        } 

        set<string>stTemp;
        for(auto it : mp){
            if(it.second==1){
                stTemp.insert(it.first);
            }
        }
        vector<string>filterWordsArray;
        cout<<"setSize : " << stTemp.size()<<endl;
        for(auto it : stTemp){
            filterWordsArray.push_back(it);
        }
        lines=filterWordsArray;
        cout<<"New Suggestions"<<endl;
        for(auto it : lines){
            cout<<it<<" ";
        }
        cout<<endl;
    }
}

int32_t main() {
    fastio();
    int t = 1;
    // cin >> t; // Uncomment for multiple test cases
    while (t--) solve();
    return 0;
}