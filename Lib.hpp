#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>
#include <algorithm>

class Patron;        // forward declaration;

class Book {
public:
	Book() {
		patron = 0;
	}
	bool operator== (const Book& bk) const {
		return strcmp(title, bk.title) == 0;
	}
private:
	char *title;        //书名
	Patron *patron;//读者名
	std::ostream& printBook(std::ostream&) const;
	friend std::ostream& operator<< (std::ostream& out, const Book& bk) {
		return bk.printBook(out);
	}
	friend class CheckedOutBook;
	friend Patron;
	friend void includeBook();
	friend void checkOutBook();
	friend void returnBook();
};

class Author {
public:
	Author() {
	}
	bool operator== (const Author& ar) const {
		return strcmp(name, ar.name) == 0;
	}
private:
	char *name;                  //作者名
	std::list<Book> books;// 著作名
	std::ostream& printAuthor(std::ostream&) const;
	friend std::ostream& operator<< (std::ostream& out, const Author& ar) {
		return ar.printAuthor(out);
	}
	friend void includeBook();
	friend void checkOutBook();
	friend void returnBook();
	friend class CheckedOutBook;
	friend Patron;
};

class CheckedOutBook {
public:
	CheckedOutBook(std::list<Author>::iterator ar,
		std::list<Book>::iterator bk ) {
		author = ar;
		book = bk;
	}
	bool operator== (const CheckedOutBook& bk) const {
		return strcmp(author->name, bk.author->name) == 0 &&
			strcmp(book->title, bk.book->title) == 0;
	}
private:
	std::list<Author>::iterator author;//被借走的书的作者
	std::list<Book>::iterator book;     //被借书单
	friend void checkOutBook();
	friend void returnBook();
	friend Patron;
};

class Patron {
public:
	Patron() {
	}
	bool operator== (const Patron& pn) const {
		return strcmp(name, pn.name) == 0;
	}
private:
	char *name;                                     //借书人名字
	std::list<CheckedOutBook> books;//借书单
	std::ostream& printPatron(std::ostream&) const;
	friend std::ostream& operator<< (std::ostream& out, const Patron& pn) {
		return pn.printPatron(out);
	}
	friend void checkOutBook();
	friend void returnBook();
	friend Book;
};

std::list<Author> catalog['Z' + 1];//作者-=*name,list<Book> books(*title,*parton)
std::list<Patron> people['Z' + 1];  //读者--*name,list<CheckedOutBook> books(list<Author>::itrator,list<Book>::iterator)
//对于list，向其中添加或删除元素后，指向容器的迭代器（包括尾后迭代器和首前迭代器）、指针和引用仍有效

std::ostream& Author::printAuthor(std::ostream& out) const {
	out << name << std::endl;
	std::list<Book>::const_iterator ref = books.begin();
	for (; ref != books.end(); ++ref)
		out << *ref; // overloaded <<
	return out;
}

std::ostream& Book::printBook(std::ostream& out) const {
	out << "    * " << title;
	if (patron != 0)
		out << " - checked out to " << patron->name; // overloaded <<
	out << std::endl;
	return out;
}

std::ostream& Patron::printPatron(std::ostream& out) const {
	out << name;
	if (!books.empty()) {
		out << " has the following books:\n";
		std::list<CheckedOutBook>::const_iterator bk = books.begin();
		for (; bk != books.end(); bk++)
			out << "    * " << bk->author->name << ", "
			<< bk->book->title << std::endl;
	}
	else out << " has no books\n";
	return out;
}

template<typename T>
std::ostream& operator<< (std::ostream& out, const std::list<T>& lst) {
	for (std::list<T>::const_iterator ref = lst.begin(); ref != lst.end(); ++ref)
		out << *ref; // overloaded <<
	return out;
}

char* getString(const char *msg) {
	char s[82], i, *destin;
	std::cout << msg;
	std::cin.get(s, 80);
	while (std::cin.get(s[81]) && s[81] != '\n');  // discard overflowing
	destin = new char[strlen(s) + 1];           // characters;
	for (i = 0; destin[i] = toupper(s[i]); i++);
	return destin;
}

void status() {
	register int i;
	std::cout << "Library has the following books:\n\n";
	for (i = 'A'; i <= 'Z'; i++)
		if (!catalog[i].empty())
			std::cout << catalog[i];
	std::cout << "\nThe following people are using the library:\n\n";
	for (i = 'A'; i <= 'Z'; i++)
		if (!people[i].empty())
			std::cout << people[i];
}

void includeBook() {
	Author newAuthor;
	Book newBook;
	newAuthor.name = getString("Enter author's name: ");
	newBook.title = getString("Enter the title of the book: ");
	std::list<Author>::iterator oldAuthor =
		find(catalog[newAuthor.name[0]].begin(),
			catalog[newAuthor.name[0]].end(), newAuthor);
	if (oldAuthor == catalog[newAuthor.name[0]].end()) {
		newAuthor.books.push_front(newBook);
		catalog[newAuthor.name[0]].push_front(newAuthor);
	}
	else (*oldAuthor).books.push_front(newBook);
}

void checkOutBook() {
	Patron patron;
	Author author;
	Book book;
	std::list<Author>::iterator authorRef;
	std::list<Book>::iterator bookRef;
	patron.name = getString("Enter patron's name: ");
	while (true) {
		author.name = getString("Enter author's name: ");
		authorRef = find(catalog[author.name[0]].begin(),
			catalog[author.name[0]].end(), author);
		if (authorRef == catalog[author.name[0]].end())
			std::cout << "Misspelled author's name\n";
		else break;
	}
	while (true) {
		book.title = getString("Enter the title of the book: ");
		bookRef = find((*authorRef).books.begin(),
			(*authorRef).books.end(), book);
		if (bookRef == (*authorRef).books.end())
			std::cout << "Misspelled title\n";
		else break;
	}
	std::list<Patron>::iterator patronRef;
	patronRef = find(people[patron.name[0]].begin(),
		people[patron.name[0]].end(), patron);
	CheckedOutBook checkedOutBook(authorRef, bookRef);
	if (patronRef == people[patron.name[0]].end()) { // a new patron 
		patron.books.push_front(checkedOutBook);    // in the library;
		people[patron.name[0]].push_front(patron);
		(*bookRef).patron = &*people[patron.name[0]].begin();
	}
	else {
		(*patronRef).books.push_front(checkedOutBook);
		(*bookRef).patron = &*patronRef;
	}
}

void returnBook() {
	Patron patron;
	Book book;
	Author author;
	std::list<Patron>::iterator patronRef;
	std::list<Book>::iterator bookRef;
	std::list<Author>::iterator authorRef;
	while (true) {
		patron.name = getString("Enter patron's name: ");
		patronRef = find(people[patron.name[0]].begin(),
			people[patron.name[0]].end(), patron);
		if (patronRef == people[patron.name[0]].end())
			std::cout << "Patron's name misspelled\n";
		else break;
	}
	while (true) {
		author.name = getString("Enter author's name: ");
		authorRef = find(catalog[author.name[0]].begin(),
			catalog[author.name[0]].end(), author);
		if (authorRef == catalog[author.name[0]].end())
			std::cout << "Misspelled author's name\n";
		else break;
	}
	while (true) {
		book.title = getString("Enter the title of the book: ");
		bookRef = find((*authorRef).books.begin(),
			(*authorRef).books.end(), book);
		if (bookRef == (*authorRef).books.end())
			std::cout << "Misspelled title\n";
		else break;
	}
	CheckedOutBook checkedOutBook(authorRef, bookRef);
	(*bookRef).patron = 0;
	(*patronRef).books.remove(checkedOutBook);
}

int menu() {
	int option;
	std::cout << "\nEnter one of the following options:\n"
		<< "1. Include a book in the catalog\n2. Check out a book\n"
		<< "3. Return a book\n4. Status\n5. Exit\n"
		<< "Your option? ";
	std::cin >> option;
	std::cin.get();         // discard '\n';
	return option;
}
