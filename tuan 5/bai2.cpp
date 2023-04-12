#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <unordered_map>
#include <algorithm>

int main(){
#ifndef ONLINE_JUDGE
    std::freopen("input.in", "r", stdin);
    std::freopen("output.out", "w", stdout);

    std::string s;
    std::getline(std::cin, s);
    std::vector<std::string> sentences;

    std::string delimiters = ".?!";
    size_t pos = 0, end_pos;
    while((end_pos = s.find_first_of(delimiters, pos)) != std::string::npos){
        char delimiter = s[end_pos];
        if(delimiter == '.' || delimiter == '?' || delimiter == '!'){
            std::string sentence = s.substr(pos, end_pos - pos + 1);

            int i = 0;
            while(sentence[i] == ' ') i++;
            sentence.erase(0,i);

            sentences.push_back(sentence);
            pos = end_pos + 1;
        } else {
            pos = end_pos + 1;
        }
    }
    std::string last_sentence = s.substr(pos);
    if (!last_sentence.empty()){ // kiểm tra xem dấu chấm cuối cùng có phải ở cuối câu hay không
        sentences.push_back(last_sentence); // thêm câu cuối cùng
    }

    // Hàng thứ 1 Xuất ra số lượng câu
    std::cout << sentences.size() << "\n";

    for (const auto& sentence : sentences){
        std::istringstream iss(sentence);
        size_t word_count = std::distance(std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>());
        std::cout << word_count << "\n"; // Từ hàng thứ 2 xuất đến (hàng thứ 2 + số câu - 1) xuất ra số lượng từ mỗi câu
    }

    std::unordered_map<std::string, size_t> word_count_map;
    for (const auto& sentence : sentences) {
        std::istringstream iss(sentence);
        std::vector<std::string> words(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{});
        for (const auto& word : words) {
            ++word_count_map[word];
        }
    }

    // tìm từ xuất hiện nhiều nhất trong văn bản
    std::vector<std::string> most_frequent_words;
    size_t max_count = 0;

    for (const auto& pair : word_count_map){
        if (pair.second > max_count){ // nếu tìm thấy từ xuất hiện nhiều hơn
            most_frequent_words.clear();
            most_frequent_words.push_back(pair.first);
            max_count = pair.second;
        } 
        else if (pair.second == max_count){ // nếu tìm thấy từ xuất hiện bằng nhau
            most_frequent_words.push_back(pair.first);
        }
    }

    // hiển thị kết quả
    for (const auto& word : most_frequent_words) {
        std::cout << word;
        if(word != most_frequent_words.back()){//kiểm tra xem có phải khác vị trí cuối không
            std::cout << ", "; // hàng này xuất ra các từ xuất hiện nhiều nhất 
        }
        else std::cout << "\n";
    }

    //nếu yêu cầu xuất thêm bao nhiêu lần thì uncomment hàng bên dưới hàm này
    //std::cout << "(" << max_count << " times)" << "\n";

    for (auto sentence : sentences){
        // Tách dấu câu ra khỏi câu
        char last_char = sentence.back();
        sentence.pop_back();

        // Tách các từ trong câu
        std::vector<std::string> words;
        std::string word;
        for (auto c : sentence) {
            if (std::isalnum(c)) {
                word += c;
            } else {
                if (!word.empty()) {
                    words.push_back(word);
                    word.clear();
                }
            }
        }
        if (!word.empty()) {
            words.push_back(word);
        }

        // Sắp xếp các từ trong câu theo thứ tự bảng chữ cái
        std::sort(words.begin(), words.end());

        // Thêm dấu câu vào cuối câu
        std::string sorted_sentence;
        for (int i = 0; i < words.size(); i++) {
            sorted_sentence += words[i];
            if (i != words.size() - 1) {
                sorted_sentence += " ";
            }
        }
        sorted_sentence += last_char;

        std::cout << sorted_sentence <<" ";
    }
#endif
    return 0;
}        