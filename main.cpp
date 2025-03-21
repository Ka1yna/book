#include <memory>
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


#include <memory>
#include <iostream>

int main() {
  std::unique_ptr<library> l = std::make_unique<library>();
  std::string input;
  
  while (true) {
    println("\nLibrary Menu:");
    println("Option 1: Add Book");
    println("Option 2: Remove Book");
    println("Option 3: Borrow Book");
    println("Option 4: Check Book Status");
    println("Option 5: Exit");

    println("Select Option (1-5): ");
    input = get_input();
    
    // Ensure valid integer input
    int choice;
    try {
      choice = std::stoi(input);
    } catch (...) {
      println("Invalid input! Please enter a number between 1-5.");
      continue;
    }
    
    if (choice < 1 || choice > 5) {
      println("Invalid option. Try again.");
      continue;
    }
    
    switch (choice) {
    case 1: {  // Add Book
      println("Enter Book Name: ");
      std::string book_name = get_input();
      println("Enter Author Name: ");
      std::string author_name = get_input();
      
      int id = l->add_book(book_name, author_name);
      println("Book Added! ID is: " + std::to_string(id));
      break;
    }
    case 2: {  // Remove Book
      println("Enter Book ID to remove: ");
      std::string book_id_str = get_input();
      int book_id;
      try {
	book_id = std::stoi(book_id_str);
      } catch (...) {
	println("Invalid ID. Please enter a number.");
	continue;
      }
      
      l->remove_book(book_id);
      println("Book removed if it existed.");
      break;
    }
    case 3: {  // Borrow Book
      println("Enter Book ID to borrow: ");
      std::string book_id_str = get_input();
      int book_id;
      try {
	book_id = std::stoi(book_id_str);
      } catch (...) {
	println("Invalid ID. Please enter a number.");
	continue;
      }
      
      if (l->borrow_book(book_id)) {
	println("Book borrowed successfully.");
      } else {
	println("Book is either already borrowed or does not exist.");
      }
      break;
    }
    case 4: {  // Check Book Status
      println("Enter Book ID to check: ");
      std::string book_id_str = get_input();
      int book_id;
      try {
	book_id = std::stoi(book_id_str);
      } catch (...) {
	println("Invalid ID. Please enter a number.");
	continue;
      }
      
      if (l->get_book_status(book_id)) {
	println("The book is currently borrowed.");
      } else {
	println("The book is available.");
      }
      break;
    }
    case 5:  // Exit
      println("Exiting Library System. Goodbye!");
      return 0;
    }
  }
}
