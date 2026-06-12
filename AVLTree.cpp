#include "AVLTree.h"
#include <iostream>
#include <fstream> // Βιβλιοθήκη για διαχείριση αρχείων
#include <sstream> // Βιβλιοθήκη για επεξεργασία συμβολοσειρών
#include <stdexcept> // Βιβλιοθήκη για διαχείριση εξαιρέσεων

// Κατασκευαστής της κλάσης AVLTree
AVLTree::AVLTree() : root(nullptr), size(0) {}

// Καταστροφέας της κλάσης AVLTree
AVLTree::~AVLTree() {
    clear(root); // Εκκαθάριση του δέντρου
}

// Συνάρτηση clear για την αναδρομική διαγραφή όλων των κόμβων του δέντρου
void AVLTree::clear(Node* node) {
    if (node != nullptr) { // Αν ο κόμβος δεν είναι κενός
        clear(node->left); // Εκκαθάριση του αριστερού υποδέντρου
        clear(node->right); // Εκκαθάριση του δεξιού υποδέντρου
        delete node; // Διαγραφή του κόμβου
    }
}

// Συνάρτηση height για την επιστροφή του ύψους ενός κόμβου
int AVLTree::height(Node* node) {
    if (node == nullptr) // Αν ο κόμβος είναι κενός
        return 0; // Το ύψος είναι 0
    return node->height; // Επιστροφή του ύψους του κόμβου
}

// Συνάρτηση getBalance για την επιστροφή της διαφοράς ύψους μεταξύ των υποδέντρων ενός κόμβου
int AVLTree::getBalance(Node* node) {
    if (node == nullptr) // Αν ο κόμβος είναι κενός
        return 0; // Η διαφορά ύψους είναι 0
    return height(node->left) - height(node->right); // Επιστροφή της διαφοράς ύψους
}

// Συνάρτηση rightRotate για τη δεξιά περιστροφή ενός υποδέντρου
AVLTree::Node* AVLTree::rightRotate(Node* y) {
    Node* x = y->left; // Ο νέος ριζικός κόμβος γίνεται το αριστερό παιδί
    Node* T2 = x->right; // Το δεξί παιδί του νέου ριζικού κόμβου γίνεται το αριστερό παιδί του παλιού ριζικού κόμβου
    x->right = y; // Το δεξί παιδί του νέου ριζικού κόμβου γίνεται ο παλιός ριζικός κόμβος
    y->left = T2; // Το αριστερό παιδί του παλιού ριζικού κόμβου γίνεται το δεξί παιδί του νέου ριζικού κόμβου
    y->height = max(height(y->left), height(y->right)) + 1; // Ενημέρωση του ύψους του παλιού ριζικού κόμβου
    x->height = max(height(x->left), height(x->right)) + 1; // Ενημέρωση του ύψους του νέου ριζικού κόμβου
    return x; // Επιστροφή του νέου ριζικού κόμβου
}

// Συνάρτηση leftRotate για την αριστερή περιστροφή ενός υποδέντρου
AVLTree::Node* AVLTree::leftRotate(Node* x) {
    Node* y = x->right; // Ο νέος ριζικός κόμβος γίνεται το δεξί παιδί
    Node* T2 = y->left; // Το αριστερό παιδί του νέου ριζικού κόμβου γίνεται το δεξί παιδί του παλιού ριζικού κόμβου
    y->left = x; // Το αριστερό παιδί του νέου ριζικού κόμβου γίνεται ο παλιός ριζικός κόμβος
    x->right = T2; // Το δεξί παιδί του παλιού ριζικού κόμβου γίνεται το αριστερό παιδί του νέου ριζικού κόμβου
    x->height = max(height(x->left), height(x->right)) + 1; // Ενημέρωση του ύψους του παλιού ριζικού κόμβου
    y->height = max(height(y->left), height(y->right)) + 1; // Ενημέρωση του ύψους του νέου ριζικού κόμβου
    return y; // Επιστροφή του νέου ριζικού κόμβου
}

// Αναδρομική συνάρτηση insert για την εισαγωγή ενός νέου κλειδιού στο δέντρο
AVLTree::Node* AVLTree::insert(Node* node, int key) {
    if (node == nullptr) { // Αν ο κόμβος είναι κενός
        size++; // Αύξηση του μεγέθους του δέντρου
        return new Node(key); // Δημιουργία νέου κόμβου και επιστροφή του
    }

    if (key < node->key) // Αν το κλειδί είναι μικρότερο από το κλειδί του κόμβου
        node->left = insert(node->left, key); // Εισαγωγή στο αριστερό υποδέντρο
    else if (key > node->key) // Αν το κλειδί είναι μεγαλύτερο από το κλειδί του κόμβου
        node->right = insert(node->right, key); // Εισαγωγή στο δεξί υποδέντρο
    else
        return node; // Αν το κλειδί είναι ίσο, δεν κάνουμε τίποτα

    node->height = 1 + max(height(node->left), height(node->right)); // Ενημέρωση του ύψους του κόμβου

    int balance = getBalance(node); // Υπολογισμός της διαφοράς ύψους του κόμβου

    if (balance > 1 && key < node->left->key) // Αν η διαφορά ύψους είναι μεγαλύτερη από 1 και το κλειδί είναι μικρότερο από το αριστερό παιδί
        return rightRotate(node); // Δεξιά περιστροφή

    if (balance < -1 && key > node->right->key) // Αν η διαφορά ύψους είναι μικρότερη από -1 και το κλειδί είναι μεγαλύτερο από το δεξί παιδί
        return leftRotate(node); // Αριστερή περιστροφή

    if (balance > 1 && key > node->left->key) { // Αν η διαφορά ύψους είναι μεγαλύτερη από 1 και το κλειδί είναι μεγαλύτερο από το αριστερό παιδί
        node->left = leftRotate(node->left); // Αριστερή περιστροφή του αριστερού παιδιού
        return rightRotate(node); // Δεξιά περιστροφή
    }

    if (balance < -1 && key < node->right->key) { // Αν η διαφορά ύψους είναι μικρότερη από -1 και το κλειδί είναι μικρότερο από το δεξί παιδί
        node->right = rightRotate(node->right); // Δεξιά περιστροφή του δεξιού παιδιού
        return leftRotate(node); // Αριστερή περιστροφή
    }

    return node; // Επιστροφή του κόμβου
}

// Αναδρομική συνάρτηση deleteNode για τη διαγραφή ενός κλειδιού από το δέντρο
AVLTree::Node* AVLTree::deleteNode(Node* root, int key) {
    if (root == nullptr) // Αν ο κόμβος είναι κενός
        return root;

    if (key < root->key) // Αν το κλειδί είναι μικρότερο από το κλειδί του κόμβου
        root->left = deleteNode(root->left, key); // Διαγραφή από το αριστερό υποδέντρο
    else if (key > root->key) // Αν το κλειδί είναι μεγαλύτερο από το κλειδί του κόμβου
        root->right = deleteNode(root->right, key); // Διαγραφή από το δεξί υποδέντρο
    else {
        if ((root->left == nullptr) || (root->right == nullptr)) { // Αν ο κόμβος έχει 0 ή 1 παιδί
            Node* temp = root->left ? root->left : root->right; // Ανάθεση του μοναδικού παιδιού στον temp

            if (temp == nullptr) { // Αν δεν υπάρχει παιδί
                temp = root;
                root = nullptr; // Ο κόμβος γίνεται κενός
            } else
                *root = *temp; // Αντιγραφή του παιδιού στον κόμβο
            delete temp; // Διαγραφή του παλιού κόμβου
            size--; // Μείωση του μεγέθους του δέντρου
        } else { // Αν ο κόμβος έχει 2 παιδιά
            Node* temp = minValueNode(root->right); // Εύρεση του μικρότερου κόμβου στο δεξί υποδέντρο
            root->key = temp->key; // Αντικατάσταση του κλειδιού του κόμβου με το κλειδί του μικρότερου κόμβου
            root->right = deleteNode(root->right, temp->key); // Διαγραφή του μικρότερου κόμβου από το δεξί υποδέντρο
        }
    }

    if (root == nullptr) // Αν ο κόμβος είναι κενός
        return root;

    root->height = 1 + max(height(root->left), height(root->right)); // Ενημέρωση του ύψους του κόμβου

    int balance = getBalance(root); // Υπολογισμός της διαφοράς ύψους του κόμβου

    if (balance > 1 && getBalance(root->left) >= 0) // Αν η διαφορά ύψους είναι μεγαλύτερη από 1 και η διαφορά ύψους του αριστερού παιδιού είναι μη αρνητική
        return rightRotate(root); // Δεξιά περιστροφή

    if (balance > 1 && getBalance(root->left) < 0) { // Αν η διαφορά ύψους είναι μεγαλύτερη από 1 και η διαφορά ύψους του αριστερού παιδιού είναι αρνητική
        root->left = leftRotate(root->left); // Αριστερή περιστροφή του αριστερού παιδιού
        return rightRotate(root); // Δεξιά περιστροφή
    }

    if (balance < -1 && getBalance(root->right) <= 0) // Αν η διαφορά ύψους είναι μικρότερη από -1 και η διαφορά ύψους του δεξιού παιδιού είναι μη θετική
        return leftRotate(root); // Αριστερή περιστροφή

    if (balance < -1 && getBalance(root->right) > 0) { // Αν η διαφορά ύψους είναι μικρότερη από -1 και η διαφορά ύψους του δεξιού παιδιού είναι θετική
        root->right = rightRotate(root->right); // Δεξιά περιστροφή του δεξιού παιδιού
        return leftRotate(root); // Αριστερή περιστροφή
    }

    return root; // Επιστροφή του κόμβου
}

// Συνάρτηση minValueNode για την εύρεση του κόμβου με το μικρότερο κλειδί σε ένα υποδέντρο
AVLTree::Node* AVLTree::minValueNode(Node* node) {
    Node* current = node; // Ανάθεση του αρχικού κόμβου στον current
    while (current->left != nullptr) // Ενώ υπάρχει αριστερό παιδί
        current = current->left; // Μετάβαση στο αριστερό παιδί
    return current; // Επιστροφή του κόμβου με το μικρότερο κλειδί
}

// Συνάρτηση insert για την εισαγωγή ενός νέου κλειδιού στο δέντρο
void AVLTree::insert(int key) {
    root = insert(root, key); // Εισαγωγή του κλειδιού από τη ρίζα
}

// Συνάρτηση search για την αναζήτηση ενός κλειδιού στο δέντρο
bool AVLTree::search(int key) const {
    return search(root, key); // Αναζήτηση του κλειδιού από τη ρίζα
}

// Αναδρομική συνάρτηση search για την αναζήτηση ενός κλειδιού σε ένα υποδέντρο
bool AVLTree::search(Node* root, int key) const {
    if (root == nullptr) // Αν ο κόμβος είναι κενός
        return false; // Το κλειδί δεν βρέθηκε
    if (root->key == key) // Αν το κλειδί του κόμβου είναι το ζητούμενο κλειδί
        return true; // Το κλειδί βρέθηκε
    if (root->key < key) // Αν το κλειδί του κόμβου είναι μικρότερο από το ζητούμενο κλειδί
        return search(root->right, key); // Αναζήτηση στο δεξί υποδέντρο
    return search(root->left, key); // Αναζήτηση στο αριστερό υποδέντρο
}

// Συνάρτηση deleteKey για τη διαγραφή ενός κλειδιού από το δέντρο
void AVLTree::deleteKey(int key) {
    root = deleteNode(root, key); // Διαγραφή του κλειδιού από τη ρίζα
}

// Συνάρτηση findMin για την εύρεση του μικρότερου κλειδιού στο δέντρο
int AVLTree::findMin() const {
    if (root == nullptr) // Αν το δέντρο είναι κενό
        throw runtime_error("Tree is empty"); // Ρίχνουμε εξαίρεση
    Node* node = root; // Ανάθεση της ρίζας στον δείκτη node
    while (node->left != nullptr) // Ενώ υπάρχει αριστερό παιδί
        node = node->left; // Μετάβαση στο αριστερό παιδί
    return node->key; // Επιστροφή του μικρότερου κλειδιού
}

// Συνάρτηση getSize για την επιστροφή του μεγέθους του δέντρου
int AVLTree::getSize() const {
    return size; // Επιστροφή του μεγέθους του δέντρου
}

// Συνάρτηση buildFromFile για την κατασκευή του δέντρου από ένα αρχείο
void AVLTree::buildFromFile(const string& filename) {
    ifstream file(filename); // Άνοιγμα του αρχείου
    if (!file.is_open()) {
        throw runtime_error("Could not open file " + filename); // Αν το αρχείο δεν μπορεί να ανοίξει, ρίχνουμε εξαίρεση
    }

    int number;
    while (file >> number) {
        insert(number); // Εισαγωγή κάθε αριθμού από το αρχείο στο δέντρο
    }
}

// Συνάρτηση toString για την επιστροφή του περιεχομένου του δέντρου ως συμβολοσειρά
string AVLTree::toString() {
    ostringstream oss; // Αντικείμενο για τη δημιουργία της συμβολοσειράς εξόδου
    oss << "Tree: "; // Έναρξη της συμβολοσειράς με την περιγραφή του δέντρου
    inOrder(root, oss); // Προσθήκη των στοιχείων του δέντρου σε in-order διάταξη
    return oss.str(); // Επιστροφή της τελικής συμβολοσειράς
}

// Αναδρομική συνάρτηση inOrder για την in-order διάταξη των στοιχείων του δέντρου
void AVLTree::inOrder(Node* root, ostream& os) {
    if (root != nullptr) { // Αν ο κόμβος δεν είναι κενός
        inOrder(root->left, os); // Προσθήκη των στοιχείων του αριστερού υποδέντρου
        os << root->key << " "; // Προσθήκη του κλειδιού του κόμβου
        inOrder(root->right, os); // Προσθήκη των στοιχείων του δεξιού υποδέντρου
    }
}