#include<iostream>
#include<memory>
#include<vector>
#include<string>

// Write template class Tab here
template <typename T>
class Tab {
public:
    std::string url;
    std::string name;
    T memory;
    std::shared_ptr<Tab<T>> next;
    std::shared_ptr<Tab<T>> prev;

    Tab(std::string url, std::string name, T memory)
        : url(url), name(name), memory(memory), next(nullptr), prev(nullptr) {}
};

// Template class Browser
template <typename T>
class Browser {
public:
    std::shared_ptr<Tab<T>> head;
    std::shared_ptr<Tab<T>> tail;
    std::shared_ptr<Tab<T>> current;
    std::vector<std::pair<std::string, std::string>> bookmarks;

    Browser() : head(nullptr), tail(nullptr), current(nullptr) {}

    void addNewTab(std::string url, std::string name, T memory) {
        auto newTab = std::make_shared<Tab<T>>(url, name, memory);
        if (!head) {
            head = tail = current = newTab;
        } else {
            tail->next = newTab;
            newTab->prev = tail;
            tail = newTab;
            current = newTab;
        }
    }

    void switchToPrevTab() {
        if (current && current->prev) {
            current = current->prev;
            std::cout << "Switched to previous tab: " << current->name
                      << " (" << current->url << "), Memory: " << current->memory << "MB" << std::endl;
        } else {
            std::cout << "No previous tab" << std::endl;
        }
    }

    void switchToNextTab() {
        if (current && current->next) {
            current = current->next;
            std::cout << "Switched to next tab: " << current->name
                      << " (" << current->url << "), Memory: " << current->memory << "MB" << std::endl;
        } else {
            std::cout << "No next tab" << std::endl;
        }
    }

    void closeCurrentTab() {
        if (!current) return;

        auto next = current->next;
        auto prev = current->prev;

        if (prev) prev->next = next;
        if (next) next->prev = prev;
        if (current == head) head = next;
        if (current == tail) tail = prev;

        std::cout << "Closed tab: " << current->name << std::endl;

        current = next ? next : prev;
        if (current) {
            std::cout << "Now the current tab = " << current->name << std::endl;
        }
    }


    void bookmarkCurrent() {
        if (current) {
            for (const auto& bookmark : bookmarks) {
                if (bookmark.first == current->name && bookmark.second == current->url) {
                    std::cout << "The bookmark is already added!!" << std::endl;
                    return;
                }
            }
            bookmarks.push_back({current->name, current->url});
            std::cout << "Bookmarked current tab: " << current->name << std::endl;
        }

    }

    void showBookmarkTab() {
        std::cout << "Bookmarks:\n";
        for (const auto& bookmark : bookmarks) {
            std::cout << bookmark.first << " (" << bookmark.second << ")" << std::endl;
        }
    }

    void moveCurrentToFirst() {
        if (current && current != head) {
            auto temp = current;

            if (temp->prev) temp->prev->next = temp->next;
            if (temp->next) temp->next->prev = temp->prev;
            if (temp == tail) tail = temp->prev;
            
            temp->next = head;
            temp->prev = nullptr;
            if (head) head->prev = temp;
            head = temp;
            current = head;

            std::cout << "Moved tab to first: " << current->name << std::endl;
        }
    }

    T total_memory() {
        T totalMemory = 0;
        auto tab = head;
        while (tab) {
            totalMemory += tab->memory;
            tab = tab->next;
        }
        return totalMemory;
    }

    void deleteTab() {
        if (!head) return;

        auto tab = head;
        auto maxMemoryTab = head;

        while (tab) {
            if (tab->memory > maxMemoryTab->memory) {
                maxMemoryTab = tab;
            }
            tab = tab->next;
        }

        std::cout << "Deleting tab: " << maxMemoryTab->name
                  << " with memory: " << maxMemoryTab->memory << "MB" << std::endl;

        if (maxMemoryTab->prev) maxMemoryTab->prev->next = maxMemoryTab->next;
        if (maxMemoryTab->next) maxMemoryTab->next->prev = maxMemoryTab->prev;
        if (maxMemoryTab == head) head = maxMemoryTab->next;
        if (maxMemoryTab == tail) tail = maxMemoryTab->prev;

        if (current == maxMemoryTab) current = maxMemoryTab->next ? maxMemoryTab->next : maxMemoryTab->prev;
    }

//Add display method in Browser template class 
    void display(){
            auto curr = head;
            std::cout<<"Browser tab list = "<<std::endl;
            while(curr){
                std::cout<<"| "<<curr->name<<"  x|-->";
                curr = curr->next;
            }
            std::cout<<std::endl;
            std::cout<<std::endl;
        }
};

int main(){
    
    Browser<double> b1;
    b1.addNewTab("https://www.google.com","Google",23.45);
    b1.display();
    std::cout<<"Switch to previous tab = "<<std::endl;
    b1.switchToPrevTab();
    std::cout<<"Switch to Next tab = "<<std::endl;
    b1.switchToNextTab();
    b1.addNewTab("https://www.youtube.com","YouTube",56);
    b1.bookmarkCurrent();
    b1.display();
    b1.addNewTab("https://www.geeksforgeeks.com","GeeksForGeeks",45.78);
    b1.bookmarkCurrent();
    b1.addNewTab("https://chat.openai.com","ChatGPT",129);
    b1.addNewTab("https://linkedin.com","LinkedIn",410);
    b1.bookmarkCurrent();
    b1.addNewTab("https://github.com","Github",110);
    b1.addNewTab("https://kaggle.com","Kaggle",310);
    b1.bookmarkCurrent();
    b1.display();
    std::cout<<"Total memory consumption = "<<b1.total_memory()<<"MB"<<std::endl;
    b1.showBookmarkTab();
    b1.moveCurrentToFirst();
    b1.display();
    b1.deleteTab();
    b1.display();
    std::cout<<"Switch to next tab = "<<std::endl;
    b1.switchToNextTab();
    std::cout<<"Switch to previous tab = "<<std::endl;
    b1.switchToPrevTab();
    b1.closeCurrentTab();
    b1.display();
    std::cout<<"Switch to previous tab = "<<std::endl;
    b1.switchToPrevTab();
    b1.closeCurrentTab();
    b1.display();
    b1.showBookmarkTab();
    std::cout<<"Total Memory Consumption = "<<b1.total_memory()<<"MB"<<std::endl;
    b1.deleteTab();
    b1.display();
    b1.addNewTab("https://docs.google.com/","Google Docs",102.34);
    b1.display();
    std::cout<<"Switch to previous tab = "<<std::endl;
    b1.switchToPrevTab();
    std::cout<<"Switch to previous tab = "<<std::endl;
    b1.switchToPrevTab();
    std::cout<<"Switch to previous tab = "<<std::endl;
    b1.switchToPrevTab();
    b1.bookmarkCurrent();
    b1.showBookmarkTab();
    b1.total_memory();
    b1.deleteTab();
    b1.display();
    return 0;
}