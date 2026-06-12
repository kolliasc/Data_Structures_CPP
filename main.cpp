#include <iostream> // Βιβλιοθήκη για εισόδου/εξόδου
#include <fstream> // Βιβλιοθήκη για διαχείριση αρχείων
#include <sstream> // Βιβλιοθήκη για επεξεργασία συμβολοσειρών
#include <string> // Βιβλιοθήκη για διαχείριση συμβολοσειρών
#include <chrono> // Βιβλιοθήκη για μέτρηση χρόνου εκτέλεσης
#include "MinHeap.h" 
#include "MaxHeap.h" 
#include "AVLTree.h" 
#include "HashTable.h" 

using namespace std;

// Συνάρτηση για την εκτύπωση του περιεχομένου μιας δομής δεδομένων σε αρχείο εξόδου
void printStructure(ofstream& outFile, const string& structureType, const string& structureContent) {
    outFile << structureType << " CONTENTS:\n" << structureContent << endl; 
}

int main() {
    MinHeap minHeap; 
    MaxHeap maxHeap; 
    AVLTree avlTree; 
    HashTable hashtable; 

    ifstream inFile("commands.txt"); // Άνοιγμα αρχείου εισόδου για ανάγνωση εντολών
    ofstream outFile("output.txt"); // Άνοιγμα αρχείου εξόδου για εγγραφή αποτελεσμάτων
    string line; // Μεταβλητή για αποθήκευση κάθε γραμμής από το αρχείο εισόδου

    // Έλεγχος αν τα αρχεία άνοιξαν επιτυχώς
    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Error opening file." << endl; 
        return 1; 
    }
    // Διαβάζουμε κάθε γραμμή του αρχείου εισόδου
    while (getline(inFile, line)) {
        istringstream iss(line); // Δημιουργία αντικειμένου istringstream για την επεξεργασία της γραμμής
        string command; // Μεταβλητή για αποθήκευση της εντολής
        iss >> command; // Ανάγνωση της πρώτης λέξης της γραμμής ως εντολή

        // Καταγραφή του χρόνου εκτέλεσης της εντολής
        auto start = chrono::high_resolution_clock::now(); // Έναρξη χρονόμετρου

        if (command == "BUILD") {
            string structureType, filename; // Μεταβλητές για τον τύπο της δομής και το όνομα του αρχείου
            iss >> structureType >> filename; // Ανάγνωση του τύπου της δομής και του ονόματος του αρχείου
            if (structureType == "MINHEAP") {
                try {
                    minHeap.buildFromFile(filename); 
                    outFile << "MinHeap built from file " << filename << endl; // Εκτύπωση μηνύματος επιτυχίας
                } catch (const runtime_error& e) {
                    outFile << e.what() << endl; // Εκτύπωση μηνύματος σφάλματος
                }
            } else if (structureType == "MAXHEAP") {
                try {
                    maxHeap.buildFromFile(filename); 
                    outFile << "MaxHeap built from file " << filename << endl; // Εκτύπωση μηνύματος επιτυχίας
                } catch (const runtime_error& e) {
                    outFile << e.what() << endl; // Εκτύπωση μηνύματος σφάλματος
                }
            } else if (structureType == "AVLTREE") {
                try {
                    avlTree.buildFromFile(filename); 
                    outFile << "AVLTree built from file " << filename << endl; // Εκτύπωση μηνύματος επιτυχίας
                } catch (const runtime_error& e) {
                    outFile << e.what() << endl; // Εκτύπωση μηνύματος σφάλματος
                }
            } else if (structureType == "HASHTABLE") {
                try {
                    hashtable.buildFromFile(filename); 
                    outFile << "Hashtable built from file " << filename << endl; // Εκτύπωση μηνύματος επιτυχίας
                } catch (const runtime_error& e) {
                    outFile << e.what() << endl; // Εκτύπωση μηνύματος σφάλματος
                }
            }
        }
        else if (command == "INSERT") {
            string structureType; // Μεταβλητή για τον τύπο της δομής
            int number; // Μεταβλητή για τον αριθμό προς εισαγωγή
            iss >> structureType >> number; // Ανάγνωση του τύπου της δομής και του αριθμού
            if (structureType == "MINHEAP" && !iss.fail()) {
                minHeap.insert(number); // Εισαγωγή αριθμού στο MinHeap
                outFile << "Inserted " << number << " into MinHeap" << endl; // Εκτύπωση μηνύματος επιτυχίας
            } else if (structureType == "MAXHEAP" && !iss.fail()) {
                maxHeap.insert(number); // Εισαγωγή αριθμού στο MaxHeap
                outFile << "Inserted " << number << " into MaxHeap" << endl; // Εκτύπωση μηνύματος επιτυχίας
            } else if (structureType == "AVLTREE" && !iss.fail()) {
                avlTree.insert(number); // Εισαγωγή αριθμού στο AVLTree
                outFile << "Inserted " << number << " into AVLTree" << endl; // Εκτύπωση μηνύματος επιτυχίας
            } else if (structureType == "HASHTABLE" && !iss.fail()) {
                hashtable.insert(number); // Εισαγωγή αριθμού στο HashTable
                outFile << "Inserted " << number << " into Hashtable" << endl; // Εκτύπωση μηνύματος επιτυχίας
            } else {
                cerr << "Failed to read number from insert command" << endl; // Εκτύπωση μηνύματος σφάλματος
                continue; // Παράβλεψη της εντολής σε περίπτωση αποτυχίας
            }
        }
        else if (command == "FINDMIN") {
            string structureType; // Μεταβλητή για τον τύπο της δομής
            iss >> structureType; // Ανάγνωση του τύπου της δομής
            if (structureType == "MINHEAP") {
                try {
                    int min = minHeap.findMin(); // Εύρεση του ελάχιστου στοιχείου στο MinHeap
                    outFile << "Min in MinHeap is " << min << endl; // Εκτύπωση του ελάχιστου στοιχείου
                } catch (const runtime_error& e) {
                    outFile << e.what() << endl; // Εκτύπωση μηνύματος σφάλματος
                }
            } else if (structureType == "AVLTREE") {
                try {
                    int min = avlTree.findMin(); // Εύρεση του ελάχιστου στοιχείου στο AVLTree
                    outFile << "Min in AVLTree is " << min << endl; // Εκτύπωση του ελάχιστου στοιχείου
                } catch (const runtime_error& e) {
                    outFile << e.what() << endl; // Εκτύπωση μηνύματος σφάλματος
                }
            }
        }
        else if (command == "FINDMAX") {
            string structureType; // Μεταβλητή για τον τύπο της δομής
            iss >> structureType; // Ανάγνωση του τύπου της δομής
            if (structureType == "MAXHEAP") {
                try {
                    int max = maxHeap.findMax(); // Εύρεση του μέγιστου στοιχείου στο MaxHeap
                    outFile << "Max in MaxHeap is " << max << endl; // Εκτύπωση του μέγιστου στοιχείου
                } catch (const runtime_error& e) {
                    outFile << e.what() << endl; // Εκτύπωση μηνύματος σφάλματος
                }
            }
        }
        else if (command == "SEARCH") {
            string structureType; // Μεταβλητή για τον τύπο της δομής
            int number; // Μεταβλητή για τον αριθμό προς αναζήτηση
            iss >> structureType >> number; // Ανάγνωση του τύπου της δομής και του αριθμού
            if (structureType == "AVLTREE" && !iss.fail()) {
                bool found = avlTree.search(number); // Αναζήτηση του αριθμού στο AVLTree
                outFile << "Search in AVLTree for " << number << " was " << (found ? "SUCCESS" : "FAILURE") << endl; // Εκτύπωση του αποτελέσματος της αναζήτησης
            } else if (structureType == "HASHTABLE" && !iss.fail()) {
                bool found = hashtable.search(number); // Αναζήτηση του αριθμού στο HashTable
                outFile << "Search in Hashtable for " << number << " was " << (found ? "SUCCESS" : "FAILURE") << endl; // Εκτύπωση του αποτελέσματος της αναζήτησης
            }
        }
        else if (command == "DELETE") {
            string structureType; // Μεταβλητή για τον τύπο της δομής
            int number; // Μεταβλητή για τον αριθμό προς διαγραφή
            iss >> structureType >> number; // Ανάγνωση του τύπου της δομής και του αριθμού
            if (structureType == "MINHEAP" && !iss.fail()) {
                try {
                    minHeap.deleteMin(); // Διαγραφή του ελάχιστου στοιχείου από το MinHeap
                    outFile << "Deleted min from MinHeap" << endl; // Εκτύπωση μηνύματος επιτυχίας
                } catch (const runtime_error& e) {
                    outFile << e.what() << endl; // Εκτύπωση μηνύματος σφάλματος
                }
            } else if (structureType == "MAXHEAP" && !iss.fail()) {
                try {
                    maxHeap.deleteMax(); // Διαγραφή του μέγιστου στοιχείου από το MaxHeap
                    outFile << "Deleted max from MaxHeap" << endl; // Εκτύπωση μηνύματος επιτυχίας
                } catch (const runtime_error& e) {
                    outFile << e.what() << endl; // Εκτύπωση μηνύματος σφάλματος
                }
            } else if (structureType == "AVLTREE" && !iss.fail()) {
                try {
                    avlTree.deleteKey(number); // Διαγραφή του συγκεκριμένου στοιχείου από το AVLTree
                    outFile << "Deleted " << number << " from AVLTree" << endl; // Εκτύπωση μηνύματος επιτυχίας
                } catch (const runtime_error& e) {
                    outFile << e.what() << endl; // Εκτύπωση μηνύματος σφάλματος
                }
            }
        }
        else if (command == "GETSIZE") {
            string structureType; // Μεταβλητή για τον τύπο της δομής
            iss >> structureType; // Ανάγνωση του τύπου της δομής
            if (structureType == "MINHEAP") {
                int size = minHeap.getSize(); // Εύρεση του μεγέθους του MinHeap
                outFile << "Size of MinHeap is " << size << endl; // Εκτύπωση του μεγέθους του MinHeap
            } else if (structureType == "MAXHEAP") {
                int size = maxHeap.getSize(); // Εύρεση του μεγέθους του MaxHeap
                outFile << "Size of MaxHeap is " << size << endl; // Εκτύπωση του μεγέθους του MaxHeap
            } else if (structureType == "AVLTREE") {
                int size = avlTree.getSize(); // Εύρεση του μεγέθους του AVLTree
                outFile << "Size of AVLTree is " << size << endl; // Εκτύπωση του μεγέθους του AVLTree
            } else if (structureType == "HASHTABLE") {
                int size = hashtable.getSize(); // Εύρεση του μεγέθους του HashTable
                outFile << "Size of Hashtable is " << size << endl; // Εκτύπωση του μεγέθους του HashTable
            }
        }

        // Καταγραφή του χρόνου εκτέλεσης της εντολής
        auto end = chrono::high_resolution_clock::now(); // Λήξη χρονόμετρου
        chrono::duration<double> duration = end - start; // Υπολογισμός της διάρκειας εκτέλεσης
        outFile << "Execution time: " << duration.count() << " seconds" << endl; // Εκτύπωση της διάρκειας εκτέλεσης

        // Εκτύπωση των δομών δεδομένων μετά από κάθε εντολή
        printStructure(outFile, "MinHeap", minHeap.toString()); // Εκτύπωση του περιεχομένου του MinHeap
        printStructure(outFile, "MaxHeap", maxHeap.toString()); // Εκτύπωση του περιεχομένου του MaxHeap
        printStructure(outFile, "AVLTree", avlTree.toString()); // Εκτύπωση του περιεχομένου του AVLTree
        printStructure(outFile, "Hashtable", hashtable.toString()); // Εκτύπωση του περιεχομένου του HashTable
        outFile << "-------------------------------------" << endl; 
    }

    // Κλείσιμο των αρχείων
    inFile.close(); 
    outFile.close(); 
    return 0; 
}