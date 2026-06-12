#include "HashTable.h"
#include <fstream> // Βιβλιοθήκη για διαχείριση αρχείων
#include <sstream> // Βιβλιοθήκη για επεξεργασία συμβολοσειρών
#include <stdexcept> // Βιβλιοθήκη για διαχείριση εξαιρέσεων
#include <iomanip> // Βιβλιοθήκη για διαμόρφωση εξόδου
#include <iostream> // Βιβλιοθήκη για εισόδου/εξόδου

using namespace std;

// Κατασκευαστής της κλάσης HashTable
HashTable::HashTable() : capacity(10), size(0) {
    table = new Node*[capacity]; // Δέσμευση μνήμης για τον πίνακα κατακερματισμού με χωρητικότητα capacity
    for (int i = 0; i < capacity; ++i) {
        table[i] = nullptr; // Αρχικοποίηση κάθε θέσης του πίνακα με nullptr
    }
}

// Καταστροφέας της κλάσης HashTable
HashTable::~HashTable() {
    clearTable(); // Εκκαθάριση του πίνακα κατακερματισμού
    delete[] table; // Απελευθέρωση της μνήμης που δεσμεύτηκε για τον πίνακα
}

// Συνάρτηση buildFromFile για την κατασκευή του πίνακα από ένα αρχείο
void HashTable::buildFromFile(const string& filename) {
    ifstream file(filename); // Άνοιγμα του αρχείου
    if (!file.is_open()) {
        throw runtime_error("Could not open file " + filename); // Αν το αρχείο δεν μπορεί να ανοίξει, ρίχνουμε εξαίρεση
    }

    int key;
    while (file >> key) {
        insert(key); // Εισαγωγή κάθε αριθμού από το αρχείο στον πίνακα
    }
}

// Συνάρτηση insert για την εισαγωγή ενός στοιχείου στον πίνακα κατακερματισμού
void HashTable::insert(int key) {
    int index = hashFunction(key); // Υπολογισμός της θέσης του κλειδιού με τη συνάρτηση κατακερματισμού
    Node* newNode = new Node{key, table[index]}; // Δημιουργία νέου κόμβου που δείχνει στον προηγούμενο κόμβο της θέσης
    table[index] = newNode; // Τοποθέτηση του νέου κόμβου στην αρχή της λίστας
    size++; // Αύξηση του μεγέθους του πίνακα
}

// Συνάρτηση search για την αναζήτηση ενός στοιχείου στον πίνακα κατακερματισμού
bool HashTable::search(int key) const {
    int index = hashFunction(key); // Υπολογισμός της θέσης του κλειδιού με τη συνάρτηση κατακερματισμού
    Node* current = table[index]; // Ανάθεση της κεφαλής της λίστας στον δείκτη current
    while (current != nullptr) {
        if (current->key == key) {
            return true; // Αν βρεθεί το κλειδί, επιστρέφεται true
        }
        current = current->next; // Μετάβαση στον επόμενο κόμβο της λίστας
    }
    return false; // Αν δεν βρεθεί το κλειδί, επιστρέφεται false
}

// Συνάρτηση getSize για την επιστροφή του μεγέθους του πίνακα κατακερματισμού
int HashTable::getSize() const {
    return size; // Επιστροφή του μεγέθους του πίνακα
}

// Συνάρτηση toString για την επιστροφή του περιεχομένου του πίνακα κατακερματισμού ως συμβολοσειρά
string HashTable::toString() const {
    ostringstream oss; // Αντικείμενο για τη δημιουργία της συμβολοσειράς εξόδου
    for (int i = 0; i < capacity; ++i) {
        oss << i << "-->"; // Εκτύπωση του δείκτη της θέσης του πίνακα
        Node* current = table[i]; // Ανάθεση της κεφαλής της λίστας στον δείκτη current
        while (current != nullptr) {
            oss << fixed << setprecision(2) << current->key << ".00"; // Εκτύπωση του κλειδιού του κόμβου με δύο δεκαδικά ψηφία
            if (current->next != nullptr) {
                oss << "-->"; // Διαχωριστικό μεταξύ των κόμβων της λίστας
            }
            current = current->next; // Μετάβαση στον επόμενο κόμβο της λίστας
        }
        oss << endl; // Νέα γραμμή μετά την ολοκλήρωση της λίστας για την τρέχουσα θέση του πίνακα
    }
    return oss.str(); // Επιστροφή της τελικής συμβολοσειράς
}

// Συνάρτηση hashFunction για τον υπολογισμό της θέσης ενός κλειδιού στον πίνακα κατακερματισμού
int HashTable::hashFunction(int key) const {
    return key % capacity; // Υπολογισμός της θέσης με βάση το υπόλοιπο της διαίρεσης του κλειδιού με τη χωρητικότητα
}

// Συνάρτηση clearTable για την εκκαθάριση του πίνακα κατακερματισμού
void HashTable::clearTable() {
    for (int i = 0; i < capacity; ++i) {
        Node* current = table[i]; // Ανάθεση της κεφαλής της λίστας στον δείκτη current
        while (current != nullptr) {
            Node* temp = current; // Προσωρινή αποθήκευση του τρέχοντος κόμβου
            current = current->next; // Μετάβαση στον επόμενο κόμβο
            delete temp; // Διαγραφή του τρέχοντος κόμβου
        }
        table[i] = nullptr; // Αρχικοποίηση της θέσης του πίνακα με nullptr
    }
}
