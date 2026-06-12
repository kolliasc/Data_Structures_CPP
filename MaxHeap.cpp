#include "MaxHeap.h"
#include <fstream> // Βιβλιοθήκη για διαχείριση αρχείων
#include <sstream> // Βιβλιοθήκη για επεξεργασία συμβολοσειρών

using namespace std;

// Κατασκευαστής της κλάσης MaxHeap
MaxHeap::MaxHeap(int cap) : capacity(cap), size(0) {
    heap = new int[capacity]; // Δέσμευση μνήμης για τον πίνακα heap με χωρητικότητα cap
}

// Καταστροφέας της κλάσης MaxHeap
MaxHeap::~MaxHeap() {
    delete[] heap; // Απελευθέρωση της μνήμης που δεσμεύτηκε για τον πίνακα heap
}

// Συνάρτηση heapifyUp για τη διατήρηση της ιδιότητας του μέγιστου σωρού προς τα πάνω
void MaxHeap::heapifyUp(int index) {
    while (index > 0) { // Ενώ ο δείκτης δεν είναι στη ρίζα
        int parent = (index - 1) / 2; // Υπολογισμός του δείκτη του γονέα
        if (heap[index] <= heap[parent]) break; // Αν το στοιχείο είναι μικρότερο ή ίσο με τον γονέα, σταματάμε
        swap(heap[index], heap[parent]); // Αντιστροφή θέσεων με τον γονέα
        index = parent; // Μετακίνηση του δείκτη στη θέση του γονέα
    }
}

// Συνάρτηση heapifyDown για τη διατήρηση της ιδιότητας του μέγιστου σωρού προς τα κάτω
void MaxHeap::heapifyDown(int index) {
    while (index < size) { // Ενώ ο δείκτης είναι εντός των ορίων του σωρού
        int leftChild = 2 * index + 1; // Υπολογισμός του δείκτη του αριστερού παιδιού
        int rightChild = 2 * index + 2; // Υπολογισμός του δείκτη του δεξιού παιδιού
        int largest = index; // Αρχικά θεωρούμε ότι το μεγαλύτερο είναι το ίδιο το στοιχείο

        if (leftChild < size && heap[leftChild] > heap[largest]) {
            largest = leftChild; // Αν το αριστερό παιδί είναι μεγαλύτερο, ενημερώνουμε το largest
        }
        if (rightChild < size && heap[rightChild] > heap[largest]) {
            largest = rightChild; // Αν το δεξί παιδί είναι μεγαλύτερο, ενημερώνουμε το largest
        }
        if (largest == index) break; // Αν το largest είναι το ίδιο το στοιχείο, σταματάμε
        swap(heap[index], heap[largest]); // Αντιστροφή θέσεων με το μεγαλύτερο παιδί
        index = largest; // Μετακίνηση του δείκτη στη θέση του μεγαλύτερου παιδιού
    }
}

// Συνάρτηση resize για την αύξηση της χωρητικότητας του σωρού
void MaxHeap::resize() {
    int* newHeap = new int[capacity * 2]; // Δημιουργία νέου πίνακα με διπλάσια χωρητικότητα
    for (int i = 0; i < size; ++i) {
        newHeap[i] = heap[i]; // Αντιγραφή των στοιχείων από τον παλιό πίνακα στο νέο
    }
    delete[] heap; // Απελευθέρωση της μνήμης του παλιού πίνακα
    heap = newHeap; // Ενημέρωση του δείκτη στον νέο πίνακα
    capacity *= 2; // Διπλασιασμός της χωρητικότητας
}

// Συνάρτηση insert για την εισαγωγή στοιχείου στον σωρό
void MaxHeap::insert(int number) {
    if (size == capacity) {
        resize(); // Αν ο σωρός είναι πλήρης, αυξάνουμε τη χωρητικότητα
    }
    heap[size] = number; // Τοποθέτηση του νέου στοιχείου στο τέλος του σωρού
    heapifyUp(size); // Διατήρηση της ιδιότητας του σωρού προς τα πάνω
    size++; // Αύξηση του μεγέθους του σωρού
}

// Συνάρτηση findMax για την εύρεση του μέγιστου στοιχείου
int MaxHeap::findMax() {
    if (size == 0) throw runtime_error("Heap is empty"); // Αν ο σωρός είναι κενός, ρίχνουμε εξαίρεση
    return heap[0]; // Επιστροφή του μέγιστου στοιχείου (ρίζα του σωρού)
}

// Συνάρτηση deleteMax για τη διαγραφή του μέγιστου στοιχείου
void MaxHeap::deleteMax() {
    if (size == 0) throw runtime_error("Heap is empty"); // Αν ο σωρός είναι κενός, ρίχνουμε εξαίρεση
    heap[0] = heap[size - 1]; // Αντικατάσταση της ρίζας με το τελευταίο στοιχείο
    size--; // Μείωση του μεγέθους του σωρού
    heapifyDown(0); // Διατήρηση της ιδιότητας του σωρού προς τα κάτω
}

// Συνάρτηση getSize για την επιστροφή του μεγέθους του σωρού
int MaxHeap::getSize() {
    return size; // Επιστροφή του μεγέθους του σωρού
}

// Συνάρτηση buildFromFile για την κατασκευή του σωρού από ένα αρχείο
void MaxHeap::buildFromFile(const string& filename) {
    ifstream file(filename); // Άνοιγμα του αρχείου
    if (!file.is_open()) {
        throw runtime_error("Could not open file " + filename); // Αν το αρχείο δεν μπορεί να ανοίξει, ρίχνουμε εξαίρεση
    }

    int number;
    while (file >> number) {
        insert(number); // Εισαγωγή κάθε αριθμού από το αρχείο στον σωρό
    }
}

// Συνάρτηση toString για την επιστροφή του περιεχομένου του σωρού ως συμβολοσειρά
string MaxHeap::toString() {
    ostringstream oss; // Αντικείμενο για τη δημιουργία της συμβολοσειράς εξόδου
    oss << "Heap: ["; // Έναρξη της συμβολοσειράς με την περιγραφή του σωρού
    for (int i = 0; i < size; ++i) {
        oss << heap[i]; // Προσθήκη κάθε στοιχείου του σωρού στη συμβολοσειρά
        if (i < size - 1) {
            oss << ", "; // Διαχωριστικό μεταξύ των στοιχείων
        }
    }
    oss << "]"; // Κλείσιμο της συμβολοσειράς με αγκύλη
    return oss.str(); // Επιστροφή της τελικής συμβολοσειράς
}