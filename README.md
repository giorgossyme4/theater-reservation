# theater-reservation

Σκοπός : Στη δεύτερη εργασία θα επεκτείνετε το σύστημα αγοράς θέσεων σε θεατρικές παραστάσεις που κατασκευάσατε στην πρώτη εργασία έτσι ώστε να γίνει πιο ρεαλιστικό, χρησιμοποιώντας πάλι το πακέτο νημάτων POSIX threads (pthreads). Ο κώδικάς σας θα πρέπει να λειτουργεί σωστά στην εικονική μηχανή που διατίθεται στα CSLAB και στο διαδίκτυο. Η εργασία είναι ομαδική και είναι σχεδιασμένη για ομάδες τριών (3) ατόμων, μπορείτε όμως να την υλοποιήσετε και σε μικρότερες ομάδες. Ο βαθμός της 2ης εργασίας θα είναι το 10% του τελικού βαθμού (δηλαδή, 1 μονάδα στις 10).

Αντικείμενο: Το σύστημα αγοράς θέσεων διαθέτει έναν λογαριασμό στην τράπεζα, έναν μετρητή συναλλαγών, ένα τηλεφωνικό κέντρο με Ntel τηλεφωνητές οι οποίοι εξυπηρετούν τους πελάτες (βρίσκουν θέσεις) και Ncash ταμίες οι οποίοι εκτελούν τις πληρωμές (χρεώνουν τις πιστωτικές κάρτες). Οι θέσεις του θεάτρου έχουν ορθογώνια διάταξη, με κάθε σειρά να έχει Nseat θέσεις και οι σειρές να χωρίζονται σε τρεις κατηγορίες με διαφορετικό κόστος ανά θέση: οι πρώτες NzoneA σειρές κοστίζουν CzoneA ευρώ ανά θέση, οι επόμενες NzoneΒ σειρές κοστίζουν CzoneΒ ευρώ ανά θέση, και οι τελευταίες NzoneC σειρές κοστίζουν CzoneC ευρώ ανά θέση. Όταν όλοι οι τηλεφωνητές είναι απασχολημένοι, οι πελάτες περιμένουν τον επόμενο διαθέσιμο τηλεφωνητή. Όταν ένας πελάτης συνδεθεί με κάποιον τηλεφωνητή, επιλέγει τυχαία μία ζώνη με πιθανότητα PzoneA, PzoneB, PzoneC, κι έναν τυχαίο ακέραιο αριθμό εισιτηρίων στο διάστημα [Nseatlow, Nseathigh] και ο τηλεφωνητής χρειάζεται ένα τυχαίο ακέραιο πλήθος δευτερολέπτων στο διάστημα [tseatlow,tseathigh] για να εξετάσει αν υπάρχουν αρκετές συνεχόμενες θέσεις σε κάποια σειρά στη συγκεκριμένη ζώνη. Αν δεν υπάρχουν συνεχόμενες θέσεις, ο πελάτης λαμβάνει ένα μήνυμα λάθους και ολοκληρώνει την κλήση. Αν υπάρχουν συνεχόμενες θέσεις, δεσμεύονται στο πλάνο του θεάτρου, υπολογίζεται το συνολικό τους κόστος, και προχωράμε στην πληρωμή με πιστωτική κάρτα. Όταν όλοι οι ταμίες είναι απασχολημένοι, οι πελάτες περιμένουν τον επόμενο διαθέσιμο ταμία. Όταν ο πελάτης συνδεθεί με τον ταμία, ο ταμίας χρειάζεται ένα τυχαίο ακέραιο πλήθος δευτερολέπτων στο διάστημα [tcashlow,tcashhigh] για να δοκιμάσει να κάνει την πληρωμή. Με πιθανότητα Pcardsucces η πληρωμή γίνεται αποδεκτή, ο πελάτης χρεώνεται το κατάλληλο κόστος, τα χρήματα μεταφέρονται στο λογαριασμό της εταιρείας και ο πελάτης ενημερώνεται για το συνολικό κόστος, τις θέσεις του στην επιλεγμένη ζώνη και τον αριθμό συναλλαγής. Αν η πληρωμή αποτύχει, οι θέσεις επιστρέφονται στο πλάνο του θεάτρου από τον ταμία και ο πελάτης λαμβάνει ένα μήνυμα λάθους. Όταν επεξεργαστεί Ncust πελάτες, το σύστημα τυπώνει τα αποτελέσματά του.

Είσοδος και δεδομένα: Το αρχικό ποσό στο λογαριασμό της εταιρείας είναι 0 ευρώ και ο αρχικός αριθμός συναλλαγής είναι 0. Οι ακόλουθες σταθερές θα ορίζονται σε ένα αρχείο δηλώσεων:

- Ntel=8 τηλεφωνητές, Ncash=4 ταμίες
- Nseat= 10 θέσεις
- NzoneA=5 σειρές, NzoneB= 10 σειρές, NzoneC= 10 σειρές
- PzoneA=20%, PzoneB= 4 0%, PzoneC= 4 0%,
- CzoneA= 30 ευρώ, CzoneB= 25 ευρώ, CzoneC= 20 ευρώ,
- Nseatlow=1 θέση, Nseathigh=5 θέσεις
- tseatlow=5 sec, tseathigh=10 sec
- tcashlow=2 sec, tcashhigh=4 sec
- Pcardsucces=90%

Το πρόγραμμά σας θα δέχεται δύο (ακριβώς) παραμέτρους με το πλήθος των πελατών προς εξυπηρέτηση, Ncust, και τον τυχαίο σπόρο για τη γεννήτρια των τυχαίων αριθμών.

Έξοδος εργασίας: Τα μηνύματα εξόδου ανά κράτηση είναι τα ίδια με αυτά της πρώτης εργασίας, η μόνη διαφορά είναι ότι μια κράτηση ματαιώνεται όχι όταν δεν υπάρχουν γενικά αρκετές θέσεις, αλλά όταν δεν υπάρχουν αρκετές συνεχόμενες θέσεις στη συγκεκριμένη ζώνη. Η σειρά των γραμμών που θα τυπώνονται ανά κράτηση θα είναι τυχαία, αλλά οι γραμμές δεν πρέπει να μπλέκονται μεταξύ τους. Στο τέλος της εκτέλεσης, το σύστημα θα τυπώνει τα ακόλουθα:

Το πλάνο των θέσεων, π.χ. Ζώνη Α / Θέση 1 / Πελάτης 3, Ζώνη 2 / Θέση 2 / Πελάτης 4, κ.λπ.
Τα συνολικά έσοδα από τις πωλήσεις.
Το ποσοστό των συναλλαγών που ολοκληρώνεται με κάθε έναν από τους παραπάνω τέσσερις τρόπους.
Το μέσο χρόνο αναμονής των πελατών (από τη στιγμή που εμφανίζεται ο πελάτης, μέχρι να μιλήσει με τον τηλεφωνητή και από τη στιγμή που τελειώνει ο τηλεφωνητής μέχρι τη στιγμή που αναλαμβάνει ο ταμίας, αν η συναλλαγή δεν ματαιωθεί νωρίτερα).
Το μέσο χρόνο εξυπηρέτησης των πελατών (από τη στιγμή που εμφανίζεται ο πελάτης, μέχρι να ολοκληρωθεί η κράτηση, επιτυχώς ή ανεπιτυχώς).
Δομή κώδικα και υποδείξεις : Πέρα από αυτά που χρειάζονται και στην πρώτη εργασία, θα χρειαστείτε τουλάχιστον τα ακόλουθα:

Μία ακέραιη μεταβλητή και ένα mutex για να μετράτε το πλήθος των διαθέσιμων ταμιών και μία μεταβλητή συνθήκης για να συγχρονίσετε τους ταμίες με τους πελάτες, έτσι ώστε όταν δεν υπάρχουν διαθέσιμοι ταμίες να μπλοκάρονται οι πελάτες.
Έναν πίνακα με το πλάνο των θέσεων ανά ζώνη κι ένα mutex για να τον κλειδώνετε (μην ξεχνάτε ότι χρειάζεται κλείδωμα και στη δέσμευση και στην αποδέσμευση θέσεων). Προσοχή στο ότι οι θέσεις κάθε κράτησης πρέπει να είναι συνεχόμενες και στην ίδια σειρά. Σκεφτείτε πώς μπορείτε να επιταχύνετε τη διαδικασία.
Προσοχή στο ότι οι χρόνοι αναμονής μπορεί να περιλαμβάνουν δύο στάδια αναμονής.
Παραδοτέα: Ο κώδικάς σας πρέπει να αποτελείται από ένα αρχείο με δηλώσεις (συμπεριλαμβανομένων των σταθερών) και ένα αρχείο κώδικα C για το πρόγραμμα. Τα αρχεία αυτά πρέπει να έχουν ονόματα της μορφής p3x-p3y-p3z-res2.h για τις δηλώσεις, p3x-p3y-p3z-res2.c για τον κώδικα C , όπου και p3x-p3y-p3z είναι οι αριθμοί μητρώου σα. Εκτός από τον κώδικα, θα πρέπει να γράψετε μία αναφορά η οποία να περιγράφει τη δομή του κώδικά σας και να αναφέρει τυχόν περιορισμούς ή πρόσθετα χαρακτηριστικά που έχετε υλοποιήσει. Η αναφορά πρέπει να είναι ένα αρχείο σε μορφή PDF με όνομα της μορφής p3x-p3y-p3z-res2.pdf. Τέλος, θα πρέπει να συμπεριλάβετε ένα αρχείο με όνομα test-res2.sh το οποίο θα μεταγλωττίζει και θα εκτελεί το πρόγραμμά σας με παραμέτρους 100 πελάτες και αρχικό σπόρο 1000. Αυτά τα τέσσερα αρχεία (και τίποτα άλλο) θα πρέπει να συμπιεστούν σε ένα αρχείο σε μορφή 7zip με όνομα της μορφής p3x-p3y-p3z-res2.7z και να υποβληθούν από ένα μόνο μέλος της ομάδας μέσω της υποβολής εργασιών του eclass.

Προθεσμία υποβολής: Τα συμπιεσμένα αρχεία με τις εργασίες σας θα πρέπει να παραδοθούν μέσω του eclass μέχρι την Δευτέρα 20/5/2019 και ώρα 23:59.

Βαθμολόγηση και εξέταση: Αρχεία που δεν θα έχουν την ακριβή ονοματολογία που ζητείται παραπάνω θα μηδενιστούν. Εργασίες με ομοιότητες που υποδεικνύουν αντιγραφή θα μηδενιστούν όλες (θα γίνει έλεγχος με ειδικό πρόγραμμα). Δειγματοληπτικά, θα κληθούν ορισμένες ομάδες για προφορική εξέταση στα CSLAB. Μέλη ομάδων, ή και ολόκληρες ομάδες, που δεν θα προσέλθουν στην προφορική εξέταση, θα μηδενιστούν.
