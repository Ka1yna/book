#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>

#define println(x) std::cout << x << std::endl

std::string get_input();
static unsigned int gen_id(int range);

struct book {
  std::string name;
  std::string author;
  unsigned int ID;
  bool is_borrowed;
};

std::string get_input() {
  std::string i;
  std::getline(std::cin, i);
  return i;
}

static unsigned int gen_id(){
  return rand() % 1000;
}

class library {
  std::vector<book> booklist;
  unsigned int ID;
  std::string name;

  int get_place_in_booklist(unsigned int ID) {
    for (int i = 0; i < booklist.size(); i++) {
      if (booklist[i].ID == ID) return i;
    }
    return -1;
  }

  
public:
  library(){
    println("Library Name: ");
    std::string library_name = get_input();

    println("Enter first Book: ");
    std::string book_name = get_input();
    println("Enter Author Name: ");
    std::string book_author = get_input();

    this->name = library_name;
    booklist.push_back({
        book_name,
        book_author,
        gen_id(),
        false,
      });

    println("Bookshop " + this->name + "created!");
  }

  int add_book(std::string name, std::string author){
    unsigned int id = gen_id();
    booklist.push_back({
      name,
      author,
      id,
      false,
    });

    return id;
  }

  void remove_book(unsigned int book_id){
    int id = this->get_place_in_booklist(book_id);
    if (id == -1){
      println("Book not found.");
      return;
    }
    this->booklist.erase(booklist.begin() + (id));
  }

  bool borrow_book(unsigned int book_id){
    int place_in_vec = this->get_place_in_booklist(book_id);
    if (place_in_vec == -1)
      return false;
    
    if (this->booklist[place_in_vec].is_borrowed == true){
      return false;
    }   

    this->booklist[place_in_vec].is_borrowed = true;
    return true;
  }
  
  bool get_book_status(unsigned int book_id){
    int place_in_vec = this->get_place_in_booklist(book_id);
     if (place_in_vec == -1)
      return false;

    return this->booklist[place_in_vec].is_borrowed;
  };

  unsigned int get_book_id_by_title(std::string title) {
    for (int i = 0; i < booklist.size(); i++) {
      if (booklist[i].name == title) return booklist[i].ID;
    }
    return 0;  // Return 0 if not found
  }
};
