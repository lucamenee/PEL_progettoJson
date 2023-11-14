#include"json.hpp"

/*-------------------------------------
		DEFINIZIONE LISTE JSON
-------------------------------------*/
struct list{
//public:

	list();
	list(list const&l);
	~list();
	void set_null();
	list& operator=(list const& l);
	void push_back(json const& el);
	void push_front(json const& el);
	bool is_null() {return head == nullptr;}

	//per debugging
	void print() {
		pCell temp = head;
		while (temp) {
			std::cout << temp->info << std::endl;
			temp = temp->next;
		}
	}
	

//private:
	struct cell {
		json info;
		cell* next;
	};	
	typedef cell* pCell;

	pCell head;
	pCell tail;
};

list::list() : head(nullptr), tail(nullptr) {} //default constructor

void list::set_null() {
	pCell temp = head;
	while (head) {
		temp = head;
		head = head->next;
		delete temp;
	}
	head = nullptr;
	tail = nullptr;
}

list::~list() {	//destructor
	set_null();
}

void list::push_front(json const& el) {
	pCell temp = new cell;
	temp->info = el;
	temp->next = head;
	head = temp;

	if (tail == nullptr) {
		tail = head;
	}
}


void list::push_back(json const& el) {
	if (head == nullptr) {
		head = new cell;
		head->info = el;
		head->next = nullptr;
		tail = head;
	} else {
		tail->next = new cell;
		tail->next->info = el;
		tail->next->next = nullptr;
		tail = tail->next;
	}
}

list& list::operator=(list const& l) { //copy assignment
	if (l.head) {
		if (l.head != head) {
			set_null();
			
			pCell temp = l.head;
			while (temp) {
				push_back(temp->info);
				temp = temp->next;
			}
		}
	}
	return *this;
}

list::list(list const& l) : list() { //copy constructor
	*this = l;
}







/*-------------------------------------
		DEFINIZIONE DIZIONARI JSON
-------------------------------------*/

class dictionary {
public:

	dictionary();
	dictionary(dictionary const& d);
	~dictionary();
	void set_null();
	dictionary& operator=(dictionary const& d);
	void insert(std::pair<std::string, json> const& info);
	bool is_null() {return head == nullptr;}

	 
	void print() { //per debugging
		pCell temp = head;
		while (temp) {
			std::cout << temp->info.first << ", " << temp->info.second << std::endl;
			temp = temp->next;
		}
	}


	struct cell {
		std::pair<std::string, json> info;
		cell* next;
	};	
	typedef cell* pCell;

	pCell head;
	pCell tail;
};

dictionary::dictionary() : head(nullptr), tail(nullptr) {}
	
void dictionary::set_null() {
	pCell temp;
	while (head) {
		temp = head;
		head = head->next;
		delete temp;
	}
	head = nullptr;
	tail = nullptr;
}

dictionary::~dictionary() {
	set_null();
}

void dictionary::insert(std::pair<std::string, json> const& p) {
	if (head == nullptr) {
		head = new cell;
		head->info = p;
		head->next = nullptr;
		tail = head;
	} else {
		tail->next = new cell;
		tail = tail->next;
		tail->info = p;
		tail->next = nullptr;
	}
}

dictionary& dictionary::operator=(dictionary const& d) {
	if (d.head) {
		if (d.head != head) {
			set_null();

			pCell temp = d.head;
			while (temp) {
				insert(temp->info);
				temp = temp->next;
			}
		}
	}
	return *this;
}

dictionary::dictionary(dictionary const& d) : dictionary() {
	*this = d;
}






/*-------------------------------------
				impl JSON
-------------------------------------*/
struct json::impl {

	double* num;
	bool* boolean;
	std::string* stringa;
	list* lista;
	dictionary* dict;
	

};



/*------------------------
		ITERATORI
-------------------------*/

struct json::list_iterator {

	using list_pointer = json*;
	using list_reference = json&;

	list_iterator(list::pCell p) : ptr(p) {}

	list_iterator& operator++() { //prefix
		ptr = ptr->next;
		return *this;
	}

	list_iterator operator++(int) { //postfix
		auto temp = ptr;
		ptr = ptr->next;
		return temp;
	} 

	list_reference operator*() const {
		return ptr->info;
	}

	list_pointer operator->() const {
		return &(ptr->info);
	}

	bool operator==(list_iterator const& rhs) const {
		return ptr == rhs.ptr;
	}

	bool operator!=(list_iterator const& rhs) const {
		return not (*this == rhs);
	}

	operator bool() const {
		return ptr != nullptr;
	}

private:
	list::pCell ptr;
};


struct json::dictionary_iterator {

	using dictionary_pointer = std::pair<std::string, json>*;
	using dictionary_reference = std::pair<std::string, json>&;

	dictionary_iterator(dictionary::pCell p) : ptr(p) {}

	dictionary_iterator& operator++() { //prefix
		ptr = ptr->next;
		return *this;
	}

	dictionary_iterator operator++(int) { //postfix
		auto temp = ptr;
		ptr = ptr->next;
		return temp;
	} 

	dictionary_reference operator*() const {
		return ptr->info;
	}

	dictionary_pointer operator->() const {
		return &(ptr->info);
	}

	bool operator==(dictionary_iterator const& rhs) const {
		return ptr == rhs.ptr;
	}

	bool operator!=(dictionary_iterator const& rhs) const {
		return not (*this == rhs);
	}

	operator bool() const {
		return ptr != nullptr;
	}

private:
	dictionary::pCell ptr;
};


struct json::const_list_iterator {

	using const_list_pointer = json const*;
	using const_list_reference = json const&;

	const_list_iterator(list::pCell p) : ptr(p) {}

	const_list_iterator& operator++() { //prefix
		ptr = ptr->next;
		return *this;
	}

	const_list_iterator operator++(int) { //postfix
		auto temp = ptr;
		ptr = ptr->next;
		return temp;
	} 

	const_list_reference operator*() const {
		return ptr->info;
	}

	const_list_pointer operator->() const {
		return &(ptr->info);
	}

	bool operator==(const_list_iterator const& rhs) const {
		return ptr == rhs.ptr;
	}

	bool operator!=(const_list_iterator const& rhs) const {
		return not (*this == rhs);
	}

	operator bool() const {
		return ptr != nullptr;
	}

private:
	list::pCell ptr;
};

struct json::const_dictionary_iterator {

	using const_dictionary_pointer = std::pair<std::string, json> const*;
	using const_dictionary_reference = std::pair<std::string, json> const&;

	const_dictionary_iterator(dictionary::pCell p) : ptr(p) {}

	const_dictionary_iterator& operator++() { //prefix
		ptr = ptr->next;
		return *this;
	}

	const_dictionary_iterator operator++(int) { //postfix
		auto temp = ptr;
		ptr = ptr->next;
		return temp;
	} 

	const_dictionary_reference operator*() const {
		return ptr->info;
	}

	const_dictionary_pointer operator->() const {
		return &(ptr->info);
	}

	bool operator==(const_dictionary_iterator const& rhs) const {
		return ptr == rhs.ptr;
	}

	bool operator!=(const_dictionary_iterator const& rhs) const {
		return not (*this == rhs);
	}

	operator bool() const {
		return ptr != nullptr;
	}

private:
	dictionary::pCell ptr;
};




typename json::list_iterator json::begin_list() {
	if (not is_list()) throw json_exception {"function begin_list() called in a non-list object"};

	return pimpl->lista->head;
}
typename json::const_list_iterator json::begin_list() const {
	if (not is_list()) throw json_exception {"function begin_list() called in a non-list object"};

	return pimpl->lista->head;
}
typename json::list_iterator json::end_list() {
	if (not is_list()) throw json_exception {"function end_list() called in a non-list object"};

	return nullptr;
}
typename json::const_list_iterator json::end_list() const {
	if (not is_list()) throw json_exception {"function end_list() called in a non-list object"};

	return nullptr;
}


typename json::dictionary_iterator json::begin_dictionary() {
	if (not is_dictionary()) throw json_exception {"function begin_dictionary() called in a non-dictionary object"};

	return pimpl->dict->head;
}
typename json::const_dictionary_iterator json::begin_dictionary() const {
	if (not is_dictionary()) throw json_exception {"function begin_dictionary() called in a non-dictionary object"};

	return pimpl->dict->head;
}
typename json::dictionary_iterator json::end_dictionary() {
	if (not is_dictionary()) throw json_exception {"function end_dictionary() called in a non-dictionary object"};

	return nullptr;
}
typename json::const_dictionary_iterator json::end_dictionary() const {
	if (not is_dictionary()) throw json_exception {"function end_dictionary() called in a non-dictionary object"};

	return nullptr;
}






/*--------------------------------------------------
					METODI JSON
--------------------------------------------------*/





json::json() { // default constructor
	pimpl = new impl;
	pimpl->num = nullptr;
	pimpl->boolean = nullptr;
	pimpl->stringa = nullptr;
	pimpl->lista = nullptr;
	pimpl->dict = nullptr;
}

json::json(json const& j) : json() { // copy constructor
	*this = j;
}

json::json(json&& j) : json() { // move constructor
	*this = j;
}

json::~json() { // destructor
	if(pimpl) {
		set_null();
		delete pimpl;
	}
}


// assignements
json& json::operator=(json const& j) { //copy assignment
	if (pimpl != j.pimpl) { //guardia da auto assegnamento
		set_null();
		
		if (not (j.is_null())) {
			if (j.is_bool()) {
				set_bool(j.get_bool());
			} else if (j.is_number()) {
				set_number(j.get_number());
			} else if (j.is_string()) {
				set_string(j.get_string());
			} else if (j.is_list()) {
				set_list();
				auto i = j.begin_list();
				while (i != end_list()) {
					push_back(*i);
					i++;
				}
			} else if (j.is_dictionary()) {
				set_dictionary();
				auto i = j.begin_dictionary();
				while (i != end_dictionary()) {
					insert(*i);
					i++;
				}
			}
		}
	}
	return *this;
}

json& json::operator=(json&& j) { // move assignment
	if (pimpl != j.pimpl) {
		set_null();
		delete pimpl;

		pimpl = j.pimpl;
		j.pimpl = nullptr;
	}
	return *this;
}




// METODI "bool"
bool json::is_list() const {
	return pimpl->lista;
}
bool json::is_dictionary() const {
	return pimpl->dict;
}
bool json::is_string() const {
	return pimpl->stringa;
}
bool json::is_number() const {
	return pimpl->num;
}
bool json::is_bool() const {
	return pimpl->boolean;
}
bool json::is_null() const {
	return not (is_bool() or is_number() or is_string() or is_dictionary() or is_list());
}








// METODI "set"
void json::set_null() {
	//pimpl->num = pimpl->inf;

	delete pimpl->num;
	delete pimpl->boolean;
	delete pimpl->stringa;
	delete pimpl->lista;
	delete pimpl->dict;	

	pimpl->num = nullptr;
	pimpl->boolean = nullptr;
	pimpl->stringa = nullptr;
	pimpl->lista = nullptr;
	pimpl->dict = nullptr; 
}

void json::set_string(std::string const& s) {
	set_null();
	pimpl->stringa = new std::string;
	*(pimpl->stringa) = s;
}
void json::set_bool(bool b) {
	set_null();
	pimpl->boolean = new bool;
	*(pimpl->boolean) = b;
}
void json::set_number(double d) {
	set_null();
	pimpl->num = new double;
	*(pimpl->num) = d;
}
void json::set_list() {
	set_null();
	pimpl->lista = new list;
}
void json::set_dictionary() {
	set_null();
	pimpl->dict = new dictionary;
}



// METODI "get"
double& json::get_number() {
	if (not is_number()) throw json_exception {"function get_number() called in a non-double object"};

	return *(pimpl->num);
}
double const& json::get_number() const {
	if (not is_number()) throw json_exception {"function get_number() called in a non-double object"};

	return *(pimpl->num);
}

bool& json::get_bool() {
	if (not is_bool()) throw json_exception {"function get_bool() called in a non-bool object"};

	return *(pimpl->boolean);
}
bool const& json::get_bool() const {
	if (not is_bool()) throw json_exception {"function get_bool() called in a non-bool object"};

	return *(pimpl->boolean);
}

std::string& json::get_string() {
	if (not is_string()) throw json_exception {"function get_string() called in a non-std::string object"};

	return *(pimpl->stringa);
}
std::string const& json::get_string() const {
	if (not is_string()) throw json_exception {"function get_string() called in a non-std::string object"};

	return *(pimpl->stringa);
}






//altri metodi di inserimento
void json::push_front(json const& j) {
	if (not is_list()) throw json_exception {"function push_front() called in a non-list object"};

	pimpl->lista->push_front(j);
}
void json::push_back(json const& j) {
	if (not is_list()) throw json_exception {"function push_back() called in a non-list object"};

	pimpl->lista->push_back(j);
}

void json::insert(std::pair<std::string,json> const& p) {
	if (not is_dictionary()) throw json_exception {"function insert() called in a non-dictionary object"};

	pimpl->dict->insert(p);
}






// operator[]
json& json::operator[](std::string const& s) {
	if (not is_dictionary()) throw json_exception {"operator[] called in a non-dictionary object"};
	
	auto i = begin_dictionary();
	while (i != end_dictionary()) {
		if (i->first == s) 
			return i->second;
		i++;
	}
	std::pair<std::string, json> nuovo;
	nuovo.first = s;
	nuovo.second;
	insert(nuovo);
	return this->operator[](s);
}

json const& json::operator[](std::string const& s) const {
	if (not is_dictionary()) throw json_exception {"operator[] called in a non-dictionary object"};
	
	auto i = begin_dictionary();
	while (i != end_dictionary()) {
		if (i->first == s) 
			return i->second;
		i++;
	}
	throw json_exception {"\"" + s + "\" key not found"};
}







/*-------------------------
	STREAM OPERATORS
-------------------------*/
void tolower(std::string& s) {
	for (char& c : s) {
		if (c >= 'A' and c <= 'Z')
			c += 32;
	}
}
void tolower(char& c) {
	if (c>='A' and c<='Z') c+=32;
}


std::ostream& operator<<(std::ostream& lhs, json const& rhs) { 
	if (rhs.is_null())
		lhs << "null";
	else if (rhs.is_bool()) {
		bool b = rhs.get_bool();
		if (b) 
			lhs << "true";
		else 
			lhs << "false";
	}
	else if (rhs.is_number())
		lhs << rhs.get_number();
	else if (rhs.is_string())
		lhs << "\""<< rhs.get_string() << "\"";
	else if (rhs.is_list()) {

		auto temp = rhs.begin_list();
		lhs << "[";
		bool entered = false;
		while (temp != rhs.end_list()) {
			entered = true;
			lhs << *temp << ", ";
			temp++;
		}
		if (entered) lhs << "\b\b"; // deleting the last ','
		lhs << "]";

	} else if (rhs.is_dictionary()) {

		auto temp = rhs.begin_dictionary();
		bool entered = false;
		lhs << "{";				
		while (temp != rhs.end_dictionary()) {
			entered = true;
			lhs << " \"" << temp->first << "\": " << temp->second;
			lhs << ",";
			temp++;
		}
		if (entered) lhs << "\b";
		lhs << "}";
	}
	return lhs;
}



json rNumber(std::istream& lhs) {
	double n = 0;
	lhs >> n;
	json nuovo;
	nuovo.set_number(n);
	return nuovo;
}

json rString(std::istream& lhs) {
	std::string s = "";
	char c;
	lhs.get(c);
	bool precSlash = false;
	while (c != '"' or precSlash) {
		s.resize(s.size() + 1);
		s.at(s.size()-1) = c;
		
		if (c == '\\') 
			precSlash = true;
		else 
			precSlash = false;

		lhs.get(c);
	}
	
	if (c != '"') throw json_exception {s + " missing '\"' in input string"};
	json nuovo;
	nuovo.set_string(s);
	return nuovo;
}

json rBool(std::istream& lhs) {
	bool b;
	lhs >> b;
	json nuovo;
	nuovo.set_bool(b);
	return nuovo;
}

json rList(std::istream& lhs) {
	json lista, contenuto;
	lista.set_list();
	char c;
	lhs >> c;
	lhs.putback(c);
	while (c != ']') {
		
		lhs >> contenuto;
		
		lista.push_back(contenuto);
		lhs >> c;
		if (c != ',' and c != ']') { 
			//std::cout << contenuto;
			throw json_exception{ "missing ',' in list stream"};
		}

	}
	
	if (c != ']') throw json_exception{"missing ']' in list stream"};
	return lista;
}

json rDictionary(std::istream& lhs) {
	json dizio, chiave, contenuto;
	dizio.set_dictionary();
	char c;
	lhs >> c;
	lhs.putback(c);
	while (c != '}') {
		
		lhs >> chiave;
		lhs >> c;
		if (c != ':') throw json_exception{"missing ':' in dictionary stream"};
		
		lhs >> contenuto;

		lhs >> c;

		if (not chiave.is_string()) throw json_exception{"dictionary key is not a string type"};
		std::pair<std::string, json> p;
		p.first = chiave.get_string();
		p.second = contenuto;
		dizio.insert(p);


		if (c != ',' and c != '}') { 
			//std::cout << contenuto;
			throw json_exception{ "missing ',' in list stream"};
		}

	}
	
	if (c != '}') throw json_exception{"missing '}' in list stream"};
	return dizio;
}


std::istream& operator>>(std::istream& lhs, json& rhs) {
	rhs.set_null();
	char c;
	lhs >> c;
	if (c >= '0' and c <= '9') { //lhs contains only a number
		lhs.putback(c);
		rhs = rNumber(lhs);
	} else if (c == '"') {
		rhs = rString(lhs);
	} else if (c == 't' or c == 'T' or c == 'f' or c == 'F' or c == 'n' or c =='N'){
		lhs.putback(c); 
		std::string s;
		char singoloC = c;
		s.resize(4);
		for(int i=0; i<4; i++) {
			lhs.get(c);
			if (c == '\n' and s.size() < 3) throw json_exception{"non valid token on std::cin"};
			s.at(i) = c;
		}
		
		
		tolower(s);
		if (s == "fals") { // case false
			lhs.get(c);
			tolower(c);
			s.resize(5);
			s.at(4) = c;
		}
		if (s == "true") {
			rhs.set_bool(true);
		} else if (s == "false") {
			rhs.set_bool(false);
		} else if (s == "null") {
			rhs.set_null();
		} else throw json_exception{"\"" + s + "\" token is not a json type"};
	} else if (c == '[') {
		rhs = rList(lhs);
	} else if (c == '{') {
		rhs = rDictionary(lhs);
	} else throw json_exception{"non valid token on std::cin"};
	
	return lhs;
}











/*-------------------------------
		MAIN DI PROVA
-------------------------------*/

void print_valori(json const& prova) {
	std::cout << "Stringa: " << prova.is_string() << std::endl;
	std::cout << "Double: " << prova.is_number() << std::endl;
	std::cout << "Bool: " << prova.is_bool() << std::endl;
	std::cout << "List: " << prova.is_list() << std::endl;
	std::cout << "Dictionary: " << prova.is_dictionary() << std::endl;
	std::cout << "Null: " << prova.is_null() << std::endl;
	std::cout << std::endl;
}

